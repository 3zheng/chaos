#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include <inttypes.h> 
#include <winsock.h>
using namespace std;

#define ONE_WEEK 60*60*24*7

inline char * convertWide2Ascii(const wchar_t* wstr, char * out)
{
	out[0] = 0;

	if (0 == wstr) return 0;
	int nRet = ::WideCharToMultiByte(GetACP(), 0, wstr, -1, out, wcslen(wstr) * 2 + 2, 0, 0);
	out[nRet] = 0;
	return out;
}

void RemoveWholeDir(const char *dir)
{
	char cmd[200] = "";
	sprintf(cmd, "rd %s /q /s", dir);	//调用dos命令删除文件夹以及文件夹下的子目录
	system(cmd);
}


void  FileTimeToTime_t(FILETIME  ft, time_t  *t)
{
	LONGLONG  ll;

	ULARGE_INTEGER            ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;

	ll = ft.dwHighDateTime << 32 + ft.dwLowDateTime;

	*t = ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
}

void RemoveOldFile(const wchar_t *file_path = nullptr)
{
	WIN32_FIND_DATA find_data;
	int ret;
	//获取当前目录句柄，并关联find_data,这里FindFirstFile的第一个参数不能填'.'（当前目录）,而是要填'*'或者'.\\*'，否则当程序找到当前文件名为'.'的当前目录就跳出循环了
	HANDLE hFind = nullptr;
	wchar_t buff[10] = L".";
	if (!file_path)
	{
		hFind = ::FindFirstFile(L"*", &find_data);
		file_path = buff;
	}
	else
	{
		wstring find_path = file_path;
		find_path += L"\\*";
		hFind = ::FindFirstFile(find_path.c_str(), &find_data);
	}

	if (INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}

	char file_name[100] = "";
	do
	{
		find_data.cFileName;
		convertWide2Ascii(find_data.cFileName, file_name);
		time_t write_time;
		FileTimeToTime_t(find_data.ftLastWriteTime, &write_time);
		time_t now = time(nullptr);
		//如果是文件夹
		if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))	//如果文件类型是文件夹，那么continue
		{
			if (0 == strcmp(file_name, ".") || 0 == strcmp(file_name, ".."))
			{
				continue;	//当前目录或上级目录都不管
			}

			if (now - write_time > ONE_WEEK)	//七天前的文件
			{
				char remove_path[200] = "";
				convertWide2Ascii(file_path, remove_path);
				string all_remove_path = remove_path;
				all_remove_path += "\\";
				all_remove_path += file_name;
				RemoveWholeDir(all_remove_path.c_str());
			}
			else
			{
				wstring all_file_path = file_path;
				all_file_path += L"\\";
				all_file_path += find_data.cFileName;

				RemoveOldFile(all_file_path.c_str());	//递归进入子文件夹
			}
		}
		else if (find_data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)
		{

			if (now - write_time > ONE_WEEK)	//七天前的文件
			{
				char remove_path[200] = "";
				convertWide2Ascii(file_path, remove_path);
				string all_remove_path = remove_path;
				all_remove_path += "\\";
				all_remove_path += file_name;
				int ret = remove(all_remove_path.c_str());
			}
		}

	} while ((ret = ::FindNextFile(hFind, &find_data)) != 0);

	char dis_buff[300] = "";
	wprintf(L"traverse %s is over\n", file_path);
}


int main()
{
	RemoveOldFile();
}