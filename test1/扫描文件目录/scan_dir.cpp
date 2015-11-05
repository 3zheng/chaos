#include "scan_dir.h"
#include <direct.h>

//处理文件的文本
#define LOG_MAX_SIZE 102400	//100K


void ScanCurrentDirectory()
{
	static LogFileManage file_op;
	WIN32_FIND_DATA find_data;
	int ret;
	//获取当前目录句柄，并关联find_data,这里FindFirstFile的第一个参数不能填'.'（当前目录）,而是要填'*'或者'.\\*'，否则当程序找到当前文件名为'.'的当前目录就跳出循环了
	HANDLE hFind = ::FindFirstFile("*", &find_data);	
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}

	do 
	{
		if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))	//如果文件类型是文件夹，那么continue
		{
			continue;
		}

		file_op.DealFileContent(find_data.cFileName);
	} while ((ret = ::FindNextFile(hFind, &find_data)) != 0);


	FindClose(hFind);
	//把所有文件指针close并置空
	file_op.CloseAllFiles();
	
}


int main()
{
	ScanCurrentDirectory();
	return 0;
}

void LogFileManage::DealFileContent(const char * file_name)
{
	FILE *fp = nullptr;
	fopen_s(&fp, file_name, "r");
	if (nullptr == fp)
	{
		return;
	}
	//直到文件结尾才跳出
	while (!feof(fp))
	{
		int current_offset = ftell(fp);
		int line_num = 0;
		int count = fread(m_buff, 1, 10000, fp);
		if (count <= 0)
		{
			continue;
		}
		char *pline = nullptr;
		for (pline = m_buff; *pline != '\n'; pline++)
		{
			current_offset++;
			line_num++;
			if (line_num > 10000)
			{
				break;
			}
		}
		//如果字数超出了限定长度，转下一个循环
		if (line_num > 10000)
		{
			continue;
		}
		current_offset++;
		*pline = '\0';	//置0，把m_buff在pline位置后的字符串无效化
		fseek(fp, current_offset, SEEK_SET);	//把文件指针移回正确的位置,因为有很多没用到的有效数据已经读进了m_buff中，要重新读取

		//校验日志行的头字符
		if (m_buff[0] != '$' || m_buff[1] != '$')
		{
			continue;
		}

		string classname = GetClassNameFromContent(m_buff);
		char out[500] = "";
		//把UTF8转成ANSCI
		ConvertCode(classname.c_str(), out, CP_UTF8, CP_ACP);
		classname = out;

		char dir[100] = "";	//新建的文件名
		auto it = m_files.find(classname);
		if (it == m_files.end())
		{
			FilesGroup files_group;
			sprintf(dir, ".\\%s\\%s%03d.log", m_dir.c_str(), classname.c_str(), files_group.num);
			files_group.fp = fopen(dir, "w");
			m_files.insert(map<string, FilesGroup>::value_type(classname, files_group));
			it = m_files.find(classname);
		}
		
		if (it == m_files.end() || nullptr == it->second.fp)
		{
			printf("报报报告大王，指针为空也%d\n", (it->second.fp == nullptr) ? 1 : 0);
			continue;
		}

		FILE *fpwrite = it->second.fp;
		fseek(fpwrite, 0, SEEK_END);
		fprintf(fpwrite, "%s\r\n", m_buff);
		if (ftell(fpwrite) >= LOG_MAX_SIZE)
		{
			//超过了最大文本大小，新建一个文件
			it->second.num++;
			fclose(it->second.fp);

			sprintf(dir, ".\\%s\\%s%03d.log", m_dir.c_str(), classname.c_str(), it->second.num);
			it->second.fp = fopen(dir, "w");
		}

	}

	
	
	
}

LogFileManage::LogFileManage()
{
	m_buff = (char*)malloc(1000000);	//分配1M的内存
	memset(m_buff, 0, 1000000);
	m_head = m_buff;

	time_t now_time = time(nullptr);
	struct tm *now_tm = localtime(&now_time);
	char str_time[100] = "";
	sprintf(str_time, "%02d%02d%02d", now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);
	_mkdir(str_time);	//建一个以时间命名的文件夹
	m_dir = str_time;
}

std::string LogFileManage::GetContentBetweenBrakets(const char *input)
{
	string content;
	bool is_find_leftbraket = false;
	for (const char *pcur = input; *pcur != ']'; pcur++)
	{
		//找到了左括号
		if (true == is_find_leftbraket)
		{
			content += *pcur;	//填充字符
		}
		else //还没找到左括号
		{
			if ('[' == *pcur)
			{
				is_find_leftbraket = true;
			}
		}
	}

	return content;
}

std::string LogFileManage::GetClassNameFromContent(const char *input)
{
	string content;
	bool is_find_head = false;
	for (const char *pcur = input; *pcur != ' '; pcur++)
	{
		//到字符串尾了，跳出循环
		if ('\0' == *pcur)
		{
			break;
		}
		//找到了文件头
		if (true == is_find_head)
		{
			content += *pcur;	//填充字符
		}
		else //还没找到左括号
		{
			if (' ' == *pcur)
			{
				continue;
			}
			if ('$' == *pcur && '$' == *(++pcur))
			{
				is_find_head = true;
			}
		}
	}

	return content;
}

void LogFileManage::ConvertCode(const char* strIn, char* strOut, int sourceCodepage, int targetCodepage)
{
	int len = lstrlen(strIn);
	int unicodeLen = MultiByteToWideChar(sourceCodepage, 0, strIn, -1, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));
	MultiByteToWideChar(sourceCodepage, 0, strIn, -1, (LPWSTR)pUnicode, unicodeLen);
	BYTE * pTargetData = NULL;
	int targetLen = WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, 0, NULL, NULL);
	pTargetData = new BYTE[targetLen + 1];
	memset(pTargetData, 0, targetLen + 1);
	WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, targetLen, NULL, NULL);
	lstrcpy(strOut, (char*)pTargetData);
	delete pUnicode;
	delete pTargetData;
}

void LogFileManage::CloseAllFiles()
{
	for (auto it = m_files.begin(); it != m_files.end(); it++)
	{
		if (nullptr == it->second.fp)
		{
			continue;
		}
		fclose(it->second.fp);
		it->second.fp = nullptr;
	}
}
