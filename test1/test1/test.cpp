#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include <set>
#include <winsock.h>
#include <inttypes.h> 

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

void TestMaxRand()
{
	printf("%x\n", RAND_MAX);
}

void TestStdPlusPlus()	//����Map��Ԫ���Ƿ���ֱ�ӽ���++����
{
	static vector<int> vec_test = {0, 6, 0};
	static map<int, int> map_test = { { 1, 4 }, { 5, 22 } };

	vec_test[1]++;
	auto it = map_test.find(5);
	if (it != map_test.end())
	{
		it->second++;
	}
	
	printf("%d, %d\n", vec_test[1], it->second);
	return;
}

void TestVectorPoint()	//����ָ��Ԫ�ص�vector���﷨
{
	struct MyStruct
	{
		int one = 2;
	};
	MyStruct *p1 = new MyStruct;
	MyStruct *p2 = new MyStruct;
	p2->one = 6;
	vector<MyStruct*> vec_test = { p1, p2 };

	for (auto it = vec_test.begin(); it != vec_test.end(); it++)
	{
		(*it)->one;	//������it->one���У�it->->oneҲ����
	}
}

void TestFreadByDifferentSize()
{
	char *buff = new char[1000000];	//����1M�ڴ�
	memset(buff, 0, 1000000);
	FILE *fp = fopen("adt-bundle-windows-x86-20130917.rar", "rb");
//	FILE *fp = fopen("20150207-2013.log", "r");
	if (nullptr == fp)
	{
		return;
	}

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);

	struct _timeb now, end_now;	
	//��1MΪ����
	_ftime(&now);
	printf("����%lld:%hd\n", now.time, now.millitm);
	FILE *fpwrite = fopen("test1M", "wb");
	fseek(fp, 0, SEEK_SET);
	int ref = 0;
	while (!feof(fp))
	{
		int ret = fread(buff, 1000000, 1, fp);
		fwrite(buff, 1000000, 1, fpwrite);
	}
	fclose(fpwrite);
	_ftime(&end_now);
	printf("1M���������%lld:%hd����ʱ%lld:%d\n", end_now.time, end_now.millitm, end_now.time - now.time, end_now.millitm - now.millitm);
	//��1KΪ����
	_ftime(&now);
	printf("����%lld:%d\n", now.time, now.millitm);
	fpwrite = fopen("test1K", "wb");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		int ret = fread(buff, 1000, 1000, fp);
		
		fwrite(buff, 1000000, 1, fpwrite);
	}
	fclose(fpwrite);
	_ftime(&end_now);
	printf("1K���������%lld:%hd����ʱ%lld:%d\n", end_now.time, end_now.millitm, end_now.time - now.time, end_now.millitm - now.millitm);
	//��1BΪ����
	_ftime(&now);
	printf("����%lld:%d\n", now.time, now.millitm);
	fpwrite = fopen("test1B", "wb");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		int ret = fread(buff, 1, 1000000, fp);
		fwrite(buff, 1000000, 1, fpwrite);
	}
	fclose(fpwrite);
	_ftime(&end_now);
	printf("1B���������%lld:%d����ʱ%lld:%d\n", end_now.time, end_now.millitm, end_now.time - now.time, end_now.millitm - now.millitm);

	fpwrite = nullptr;
	fclose(fp);
	fp = nullptr;

	delete buff;
}

//���������ĵ�������erase�Ժ��ָ������
void TestContainIterator()
{
	map<int, string> map_test = { { 5, "�������ҵ�����" }, { 2, "����ҽ�ҵ�����" }, { 19, "���ϸ���ʦ�ҵ�����" }, { 12, "ALL BLUE���Ҷ���" } };

	auto it = map_test.find(5);
	if (it == map_test.end())
	{
		return;
	}

	it = map_test.begin();
//	it += 2;
	return;

	//��ô�������ɾ����5�Ժ󣬲�����++it�����ж�it�Ƿ����map_test.end()�������
	map_test.erase(5);
	if (++it == map_test.end())
	{
		return;
	}
	else
	{
		printf("%d˵:%s\n", it->first, it->second.c_str());
	}
	
}

//�����֪vector��һ��Ԫ��λ�ã������������ɾ��������ʵ��it = vector.begin() + λ���±�ķ�ʽ��ʵ�ֿ���ɾ��
void InterestingIterator()
{
	vector<int> vec_test = { 2, 4, 6, 8, 1, 342, 32, 65, 76, 25 };
	//��������֪Ҫɾ����vectorԪ���±�Ϊ4��������ֵΪ1��Ԫ�أ���ô�ҿ�����ô����
	auto it = vec_test.begin() + 4;
	vec_test.erase(it);

	//1�ѱ�ɾ��
	for (it = vec_test.begin(); it != vec_test.end(); it++)
	{
		printf("%d ", *it);
	}
	printf("\n");
}

class ST_C2
{
public:
	int c2[10];
};

class C1
{
	
public:
	int num = 0;
	char *pbuff = nullptr;
	
	static ST_C2 *st2;
public:
	C1(){
	//	printf("C1 is constructed\n");
	}

	~C1()
	{
	//	printf("C1 is destroyed\n");
		if (pbuff != nullptr)
		{
			//				delete pbuff;	�������ɶ����ͷ�Ŷ
			pbuff = nullptr;
		}
	}

	ST_C2 *GetC2()
	{
		return st2;
	}
};

ST_C2 *C1::st2 = nullptr;
void Construct()
{

	C1 c1;
	c1.num = 1;
	c1.pbuff = new char[10];
	strcpy(c1.pbuff, "hello");
	map<int, C1> map_test;
	
	map_test.insert(map<int, C1>::value_type(3, c1));

	int i = 0;
	i++;
}

void TestSizeOfEveryType()
{
	int size = 0;
	size = sizeof(long);
	printf("long is %d\n", size);
}

void TestEnum()
{
	enum MyEnum
	{
		ENUM1 = 3,
		ENUM2 = 3
	};

	MyEnum test1 = ENUM1;
	MyEnum test2 = ENUM2;
	printf("%d,%d\n", test1, test2);
}

void TestMutilmap()
{
	multimap<int, string> multimap_test1 = { { 1, "hello " }, { 1, "world " }, { 1, "monkey " }, { 6, "luffy " }, { 1, "hello" } };

	int size =  multimap_test1.size();
	auto pos = multimap_test1.equal_range(9);
	for (auto it = pos.first; it != pos.second; it++)
	{
		printf("%s", it->second.c_str());
	}
	//����1��key�Ķ��ֵ
	pos = multimap_test1.equal_range(1);
	for (auto it = pos.first; it != pos.second; it++)
	{
		printf("%s", it->second.c_str());
	}

	pos = multimap_test1.equal_range(6);
	for (auto it = pos.first; it != pos.second; it++)
	{
		printf("%s", it->second.c_str());
	}

	pos = multimap_test1.equal_range(4);
	for (auto it = pos.first; it != pos.second; it++)
	{
		printf("%s", it->second.c_str());
	}

	printf("\n");

	typedef struct GroupT
	{
		int id = 0;
		string name = "";
		inline bool operator<(const GroupT &Right) const
		{
			return this->id < Right.id;
		}
	}Group;

	Group group_test1;
	group_test1.id = 4;
	group_test1.name = "hello";
	set<Group> set_test1 = { group_test1 };

	Group group_test2;
	group_test2.id = 4;
	group_test2.name = "world";
	auto it = set_test1.find(group_test2);
	printf("%s\n", it->name.c_str());
	set_test1.insert(group_test2);

}

void TestUnsigned()
{
	unsigned int a = 99;
	int b = -34;

	unsigned int c = static_cast<int>(a) + b;
}

void TestPrintf()
{
	int a = 0x4fa5ef;
	printf("d is %08d, x is %08x\n", a, a);
	string b = 0;
	printf("%d\n", b);
}

void TestIPChange()
{
	unsigned long Ip = 0x0a0101c0;
	int i_test = Ip % 0;

	in_addr address;
	address.S_un.S_addr = Ip;
	string strIp = inet_ntoa(address);
	
	string strTest, strTest2, strTest3;
	char buff[100] = "";
	for (int i = 0; i < 100; i++)
	{
		buff[i] = static_cast<char>(i);
	}
	strTest.assign(buff, 50);
	strTest = buff;
	for (const char *pstr = strTest.c_str(); *pstr != 99; *pstr++)
	{
		printf("%c", *pstr);
	}
	strTest2.assign(strTest);
	strTest3 = strTest;
}



#define SERVERADDR_NUM 3
#define SERVER_LEN 30
//��Ϸ�����б�ṹ
struct tagGameServer
{
	WORD								wGameType;							//GAME_TYPE_INNER=0,GAME_TYPE_OUTER=1 ��xuweiqun 2015-4-29��
	WORD								wServerType;						//�����ʶ
	WORD								wMatchType;							//��������
	WORD								wSortID;							//�������
	WORD								wKindID;							//���ƺ���
	WORD								wServerID;							//�������
	WORD								wStationID;							//վ�����
	WORD								wMaxConnect;						//�������
	WORD								wServerPort;						//����˿�
	DWORD								dwServerAddr[SERVERADDR_NUM];		//�����ַ(���š��ƶ�����ͨ)
	DWORD								dwOnLineCount;						//��������
	DWORD								dwMatchJoinCount;					//��������
	DWORD								dwMatchStartCount;					//��������(��ͨ��������������0x0001�û��б����� 0x0002��ֹ�û���������)
	DWORD								dwSpreaderID;						//�����ƹ�ID
	LONG								lCellScore;							//��λ����
	__int64								lLessScore;							//��ͻ���
	__int64								lMaxScore;							//��߻���
	LONG								lMatchGold;							//���(������)
	LONG								lMatchProve;						//������(������)
	__time64_t							tMatchStartTime;					//��ʼʱ��
	__time64_t							tMatchEndTime;						//����ʱ��
	LONG								lDefaulSortCol;						//Ĭ���û��б�������(���������������Ҳ�����ID)
	TCHAR								szServerName[SERVER_LEN];			//��������
	TCHAR								szRoomType[SERVER_LEN];				//��������
	TCHAR								szRewardInfo[SERVER_LEN];			//������Ϣ
	TCHAR								szPrizeImageFileName[SERVER_LEN];	//��ƷͼƬ����
};
struct CMD_CS_RegGameServer
{
	tagGameServer						GameServer;						//������Ϣ
};

struct MyStruct
{
	char seg1[7];
	int seg2;
	uint64_t seg3;
};

void TestDeleteMemory()
{
	int size = sizeof(CMD_CS_RegGameServer);
	size = sizeof(MyStruct);
	char **rec = new char*[6000000];
	//����ָ�����ͱ��ı���Ƿ����ͷ�
	for (int i = 0; i < 6000000; i++)
	{
		MyStruct *p_new = new MyStruct;
		rec[i] = static_cast<char*>((void*)p_new);
		//delete rec[i].pbuff;
		
	}

	for (int i = 0; i < 6000000; i++)
	{
		delete rec[i];
	}
	delete rec;
}

void TestDosCommand()
{
	system("rd funny\\SogouWP /q /s");
}

void TestTime()
{
	time_t now = 1434441600;
	struct tm *tm_now = nullptr;
	tm_now = localtime(&now);
}

void TestStaticMember()	//���Ծ�̬��Ա����
{
	C1 ob[10];
	ST_C2 *p_c2 = ob[0].GetC2();
	p_c2->c2[1] = 9;
	p_c2->c2[4] = 664;

	int tmp = ob[1].st2->c2[1];
}

void WriteFile(string content)
{
	FILE *fp = nullptr;
	fp = fopen("gate_user_detail.log", "a");
	if (nullptr == fp)
	{
		return;
	}
	fseek(fp, 0L, SEEK_END);
	fwrite(content.c_str(), 1, content.size(), fp);
	fclose(fp);
}

/**
* ��һ������ֳ���
*
* @param arr        ������ַ�����
* @param strSource  Դ��
* @param strDelimit �ָ��ַ�
*
* @example
* 	char string[] = "A string\tof ,,tokens\nand some  more tokens";
* 	char seps[]   = " ,\t\n";
*
* 	std::vector<std::string> arr;
* 	split(arr,string,seps);
*
* 	for(size_t i=0;i<arr.size();i++)
*       printf("arr[%d]=\"%s\"\n",i,arr[i]);
*/
inline void split(std::vector<std::string> & arr,
	char * strSource,
	const char*  strDelimit)
{
	arr.clear();
	char * token = strtok(strSource, strDelimit);
	while (token != NULL)
	{
		arr.push_back(token);
		token = strtok(NULL, strDelimit);
	}
}

struct MyFileInfo
{
	uint32_t app_id = 0;
	uint32_t app_type = 0;
	string exe_name = "";
	vector<string> update_files;	//�滻�ļ�
	string path;	//�ļ�·��
	bool is_ready = false;	//�Ƿ��Ѿ�׼���ø���,�����Ƿ��Ѿ��յ�AppStopRsp�Ļظ�����

	bool operator==(const MyFileInfo &Right) const
	{
		return this->app_id == Right.app_id && this->app_type == Right.app_type;
	}
};

bool RepalceFile()
{
	char file_name[100] = "fund.cfg";
	FILE *fp = fopen(file_name, "r");
	if (!fp)
	{
		
		return false;
	}
	char buff[100] = "";
	uint32_t app_type = 0;
	string exe_name;
	vector<string> app_ids;	//app_id
	vector<string> paths;	//·��
	vector<string> update_files;	//�滻�ļ�
	//app_type
	fscanf(fp, "%s", buff);
	char *p_sub = strstr(buff, "app_type=");
	if (!p_sub)
	{
		
		return false;
	}
	p_sub = p_sub + 9;
	app_type = atoi(p_sub);
	//��ִ�г�����
	fscanf(fp, "%s", buff);
	p_sub = strstr(buff, "��ִ�г�����=");
	if (!p_sub)
	{
		
		return false;
	}
	p_sub = p_sub + 13;
	exe_name = p_sub;
	//app_id
	fscanf(fp, "%s", buff);
	p_sub = strstr(buff, "app_id=");
	if (!p_sub)
	{
		
		return false;
	}
	p_sub = p_sub + 7;
	split(app_ids, p_sub, "|");
	
	//app·��
	fscanf(fp, "%s", buff);
	p_sub = strstr(buff, "app·��=");
	if (!p_sub)
	{
		
		return false;
	}
	p_sub = p_sub + 8;
	split(paths, p_sub, "|");
	//�����ļ�
	fscanf(fp, "%s", buff);
	p_sub = strstr(buff, "���µ��ļ�=");
	if (!p_sub)
	{
	
		return false;
	}
	p_sub = p_sub + 11;
	split(update_files, p_sub, "|");
	//�滻�ļ�

	if (app_ids.size() != paths.size())
	{
		
		return false;
	}

	vector<MyFileInfo> m_file_info;
	for (int i = 0; i < app_ids.size(); i++)
	{
		MyFileInfo info;
		info.app_type = app_type;
		info.exe_name = exe_name;
		info.app_id = atoi(app_ids[i].c_str());
		info.path = paths[i];
		info.update_files = update_files;

		m_file_info.push_back(info);
	}

	Sleep(1000);	//����ʱ1��

	//���Ƹ���
	for (auto it_file = m_file_info.begin(); it_file != m_file_info.end(); it_file++)
	{
		for (auto it_update = it_file->update_files.begin(); it_update != it_file->update_files.end(); it_update++)
		{
			sprintf(buff, "copy /y %s %s", it_update->c_str(), it_file->path.c_str());
			system(buff);
		}
		sprintf(buff, "%s\\%s", it_file->path.c_str(), it_file->exe_name.c_str());
		system(buff);
	}
	
}

int main()
{
	TestMaxRand();
	TestStdPlusPlus();
//	TestFreadByDifferentSize();
	TestContainIterator();
	InterestingIterator();	//�����֪vector��һ��Ԫ��λ�ã������������ɾ��������ʵ��it = vector.begin() + λ���±�ķ�ʽ��ʵ�ֿ���ɾ��
	Construct();
	TestSizeOfEveryType();
	TestEnum();
	TestMutilmap();
	TestUnsigned();
	RepalceFile();
//	TestPrintf();	//string��ֵ0�ḳֵnullptr
//	TestIPChange();
//	TestDeleteMemory();
//	TestDosCommand();
//	TestTime();
//	TestStaticMember();
	
	return 0;
}