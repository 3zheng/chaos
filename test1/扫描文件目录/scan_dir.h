#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>
#include <time.h>

using namespace std;

struct FilesGroup
{
	FILE *fp = nullptr;	//文件指针
	int num = 1;	//文件序号
};

class LogFileManage
{
public:
	void DealFileContent(const char * file_name);
	string GetContentBetweenBrakets(const char *input);	//取字符串第一组括号里的内容
	string GetClassNameFromContent(const char *input);	//取得文件名

	void CloseAllFiles();
	//Convert(strA_in,strB_out,CP_UTF8,CP_ACP) UTF8转换ANSI
	//Convert(strA_out, strB_in, CP_ACP, CP_UTF8) ANSI转换UTF8
	void ConvertCode(const char* strIn, char* strOut, int sourceCodepage, int targetCodepage );	//编码转换，UTF8和ANSIC
	
	LogFileManage();
protected:
private:
	map<string, FilesGroup> m_files;
	char *m_buff;
	char *m_head;	//指向m_buff分配时刚开始的地址，用于释放用和重新定位用，因为m_buff会在中途发生变动
	string m_dir;	//新生成的文件存放目录
};