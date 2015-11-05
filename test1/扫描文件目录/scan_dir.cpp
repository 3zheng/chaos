#include "scan_dir.h"
#include <direct.h>

//�����ļ����ı�
#define LOG_MAX_SIZE 102400	//100K


void ScanCurrentDirectory()
{
	static LogFileManage file_op;
	WIN32_FIND_DATA find_data;
	int ret;
	//��ȡ��ǰĿ¼�����������find_data,����FindFirstFile�ĵ�һ������������'.'����ǰĿ¼��,����Ҫ��'*'����'.\\*'�����򵱳����ҵ���ǰ�ļ���Ϊ'.'�ĵ�ǰĿ¼������ѭ����
	HANDLE hFind = ::FindFirstFile("*", &find_data);	
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}

	do 
	{
		if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))	//����ļ��������ļ��У���ôcontinue
		{
			continue;
		}

		file_op.DealFileContent(find_data.cFileName);
	} while ((ret = ::FindNextFile(hFind, &find_data)) != 0);


	FindClose(hFind);
	//�������ļ�ָ��close���ÿ�
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
	//ֱ���ļ���β������
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
		//��������������޶����ȣ�ת��һ��ѭ��
		if (line_num > 10000)
		{
			continue;
		}
		current_offset++;
		*pline = '\0';	//��0����m_buff��plineλ�ú���ַ�����Ч��
		fseek(fp, current_offset, SEEK_SET);	//���ļ�ָ���ƻ���ȷ��λ��,��Ϊ�кܶ�û�õ�����Ч�����Ѿ�������m_buff�У�Ҫ���¶�ȡ

		//У����־�е�ͷ�ַ�
		if (m_buff[0] != '$' || m_buff[1] != '$')
		{
			continue;
		}

		string classname = GetClassNameFromContent(m_buff);
		char out[500] = "";
		//��UTF8ת��ANSCI
		ConvertCode(classname.c_str(), out, CP_UTF8, CP_ACP);
		classname = out;

		char dir[100] = "";	//�½����ļ���
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
			printf("�������������ָ��Ϊ��Ҳ%d\n", (it->second.fp == nullptr) ? 1 : 0);
			continue;
		}

		FILE *fpwrite = it->second.fp;
		fseek(fpwrite, 0, SEEK_END);
		fprintf(fpwrite, "%s\r\n", m_buff);
		if (ftell(fpwrite) >= LOG_MAX_SIZE)
		{
			//����������ı���С���½�һ���ļ�
			it->second.num++;
			fclose(it->second.fp);

			sprintf(dir, ".\\%s\\%s%03d.log", m_dir.c_str(), classname.c_str(), it->second.num);
			it->second.fp = fopen(dir, "w");
		}

	}

	
	
	
}

LogFileManage::LogFileManage()
{
	m_buff = (char*)malloc(1000000);	//����1M���ڴ�
	memset(m_buff, 0, 1000000);
	m_head = m_buff;

	time_t now_time = time(nullptr);
	struct tm *now_tm = localtime(&now_time);
	char str_time[100] = "";
	sprintf(str_time, "%02d%02d%02d", now_tm->tm_hour, now_tm->tm_min, now_tm->tm_sec);
	_mkdir(str_time);	//��һ����ʱ���������ļ���
	m_dir = str_time;
}

std::string LogFileManage::GetContentBetweenBrakets(const char *input)
{
	string content;
	bool is_find_leftbraket = false;
	for (const char *pcur = input; *pcur != ']'; pcur++)
	{
		//�ҵ���������
		if (true == is_find_leftbraket)
		{
			content += *pcur;	//����ַ�
		}
		else //��û�ҵ�������
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
		//���ַ���β�ˣ�����ѭ��
		if ('\0' == *pcur)
		{
			break;
		}
		//�ҵ����ļ�ͷ
		if (true == is_find_head)
		{
			content += *pcur;	//����ַ�
		}
		else //��û�ҵ�������
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
