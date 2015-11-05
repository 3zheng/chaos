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

void TestStdPlusPlus()	//测试Map的元素是否能直接进行++操作
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

void TestVectorPoint()	//测试指针元素的vector的语法
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
		(*it)->one;	//不好玩it->one不行，it->->one也不行
	}
}

void TestFreadByDifferentSize()
{
	char *buff = new char[1000000];	//申请1M内存
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
	//以1M为步长
	_ftime(&now);
	printf("现在%lld:%hd\n", now.time, now.millitm);
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
	printf("1M结果，现在%lld:%hd，耗时%lld:%d\n", end_now.time, end_now.millitm, end_now.time - now.time, end_now.millitm - now.millitm);
	//以1K为步长
	_ftime(&now);
	printf("现在%lld:%d\n", now.time, now.millitm);
	fpwrite = fopen("test1K", "wb");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		int ret = fread(buff, 1000, 1000, fp);
		
		fwrite(buff, 1000000, 1, fpwrite);
	}
	fclose(fpwrite);
	_ftime(&end_now);
	printf("1K结果，现在%lld:%hd，耗时%lld:%d\n", end_now.time, end_now.millitm, end_now.time - now.time, end_now.millitm - now.millitm);
	//以1B为步长
	_ftime(&now);
	printf("现在%lld:%d\n", now.time, now.millitm);
	fpwrite = fopen("test1B", "wb");
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp))
	{
		int ret = fread(buff, 1, 1000000, fp);
		fwrite(buff, 1000000, 1, fpwrite);
	}
	fclose(fpwrite);
	_ftime(&end_now);
	printf("1B结果，现在%lld:%d，耗时%lld:%d\n", end_now.time, end_now.millitm, end_now.time - now.time, end_now.millitm - now.millitm);

	fpwrite = nullptr;
	fclose(fp);
	fp = nullptr;

	delete buff;
}

//测试容器的迭代器被erase以后的指向问题
void TestContainIterator()
{
	map<int, string> map_test = { { 5, "海贼王我当定了" }, { 2, "名船医我当定了" }, { 19, "海上钢琴师我当定了" }, { 12, "ALL BLUE我找定了" } };

	auto it = map_test.find(5);
	if (it == map_test.end())
	{
		return;
	}

	it = map_test.begin();
//	it += 2;
	return;

	//这么做会出错，删除了5以后，不管是++it还是判断it是否等于map_test.end()都会出错
	map_test.erase(5);
	if (++it == map_test.end())
	{
		return;
	}
	else
	{
		printf("%d说:%s\n", it->first, it->second.c_str());
	}
	
}

//如果已知vector的一个元素位置，并想对他进行删除，可以实用it = vector.begin() + 位置下标的方式来实现快速删除
void InterestingIterator()
{
	vector<int> vec_test = { 2, 4, 6, 8, 1, 342, 32, 65, 76, 25 };
	//假设我已知要删除的vector元素下标为4，即上面值为1的元素，那么我可以这么操作
	auto it = vec_test.begin() + 4;
	vec_test.erase(it);

	//1已被删除
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
			//				delete pbuff;	这里会造成二次释放哦
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
	//查找1这key的多个值
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
//游戏房间列表结构
struct tagGameServer
{
	WORD								wGameType;							//GAME_TYPE_INNER=0,GAME_TYPE_OUTER=1 （xuweiqun 2015-4-29）
	WORD								wServerType;						//房间标识
	WORD								wMatchType;							//比赛类型
	WORD								wSortID;							//排序号码
	WORD								wKindID;							//名称号码
	WORD								wServerID;							//房间号码
	WORD								wStationID;							//站点号码
	WORD								wMaxConnect;						//最大连接
	WORD								wServerPort;						//房间端口
	DWORD								dwServerAddr[SERVERADDR_NUM];		//房间地址(电信、移动、联通)
	DWORD								dwOnLineCount;						//在线人数
	DWORD								dwMatchJoinCount;					//报名人数
	DWORD								dwMatchStartCount;					//开赛人数(普通场作特殊配置用0x0001用户列表乱序 0x0002禁止用户设置密码)
	DWORD								dwSpreaderID;						//房间推广ID
	LONG								lCellScore;							//单位积分
	__int64								lLessScore;							//最低积分
	__int64								lMaxScore;							//最高积分
	LONG								lMatchGold;							//金币(报名费)
	LONG								lMatchProve;						//参赛卷(报名费)
	__time64_t							tMatchStartTime;					//开始时间
	__time64_t							tMatchEndTime;						//结束时间
	LONG								lDefaulSortCol;						//默认用户列表排序列(比赛房间作大厅右侧排序ID)
	TCHAR								szServerName[SERVER_LEN];			//房间名称
	TCHAR								szRoomType[SERVER_LEN];				//房间类型
	TCHAR								szRewardInfo[SERVER_LEN];			//奖励信息
	TCHAR								szPrizeImageFileName[SERVER_LEN];	//奖品图片名称
};
struct CMD_CS_RegGameServer
{
	tagGameServer						GameServer;						//房间信息
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
	//测试指针类型被改变后是否还能释放
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

void TestStaticMember()	//测试静态成员变量
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
* 将一个串拆分出来
*
* @param arr        输出的字符串组
* @param strSource  源串
* @param strDelimit 分隔字符
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
	vector<string> update_files;	//替换文件
	string path;	//文件路径
	bool is_ready = false;	//是否已经准备好更新,就是是否已经收到AppStopRsp的回复报文

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
	vector<string> paths;	//路径
	vector<string> update_files;	//替换文件
	//app_type
	fscanf(fp, "%s", buff);
	char *p_sub = strstr(buff, "app_type=");
	if (!p_sub)
	{
		
		return false;
	}
	p_sub = p_sub + 9;
	app_type = atoi(p_sub);
	//可执行程序名
	fscanf(fp, "%s", buff);
	p_sub = strstr(buff, "可执行程序名=");
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
	
	//app路径
	fscanf(fp, "%s", buff);
	p_sub = strstr(buff, "app路径=");
	if (!p_sub)
	{
		
		return false;
	}
	p_sub = p_sub + 8;
	split(paths, p_sub, "|");
	//更新文件
	fscanf(fp, "%s", buff);
	p_sub = strstr(buff, "更新的文件=");
	if (!p_sub)
	{
	
		return false;
	}
	p_sub = p_sub + 11;
	split(update_files, p_sub, "|");
	//替换文件

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

	Sleep(1000);	//先延时1秒

	//复制更新
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
	InterestingIterator();	//如果已知vector的一个元素位置，并想对他进行删除，可以实用it = vector.begin() + 位置下标的方式来实现快速删除
	Construct();
	TestSizeOfEveryType();
	TestEnum();
	TestMutilmap();
	TestUnsigned();
	RepalceFile();
//	TestPrintf();	//string赋值0会赋值nullptr
//	TestIPChange();
//	TestDeleteMemory();
//	TestDosCommand();
//	TestTime();
//	TestStaticMember();
	
	return 0;
}