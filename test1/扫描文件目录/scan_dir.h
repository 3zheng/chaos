#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>
#include <time.h>

using namespace std;

struct FilesGroup
{
	FILE *fp = nullptr;	//�ļ�ָ��
	int num = 1;	//�ļ����
};

class LogFileManage
{
public:
	void DealFileContent(const char * file_name);
	string GetContentBetweenBrakets(const char *input);	//ȡ�ַ�����һ�������������
	string GetClassNameFromContent(const char *input);	//ȡ���ļ���

	void CloseAllFiles();
	//Convert(strA_in,strB_out,CP_UTF8,CP_ACP) UTF8ת��ANSI
	//Convert(strA_out, strB_in, CP_ACP, CP_UTF8) ANSIת��UTF8
	void ConvertCode(const char* strIn, char* strOut, int sourceCodepage, int targetCodepage );	//����ת����UTF8��ANSIC
	
	LogFileManage();
protected:
private:
	map<string, FilesGroup> m_files;
	char *m_buff;
	char *m_head;	//ָ��m_buff����ʱ�տ�ʼ�ĵ�ַ�������ͷ��ú����¶�λ�ã���Ϊm_buff������;�����䶯
	string m_dir;	//�����ɵ��ļ����Ŀ¼
};