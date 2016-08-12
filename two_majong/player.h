#pragma once

#include "poke.h"
using namespace std;




struct player
{

	player() : userid(0), is_auto(false), is_drop(false),m_hu_status(0) {}

	void WriteLog(CStringA str)
	{
		ofstream f;
		SYSTEMTIME systime;
		GetLocalTime(&systime);
		TCHAR szCurrentPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szCurrentPath);
		CStringA strPath,strpathall;
		strPath = "\\log\\ddzlog.txt";
		strPath.Format("\\log\\ddzlog_%d-%d-%d.txt", systime.wYear, systime.wMonth, systime.wDay);
		strpathall = szCurrentPath + strPath;
		f.open(strpathall, ios::app|ios::out);
		CStringA strInfo;
		strInfo.Format("%d-%02d-%02d %02d:%02d:%02d.%03d  ", systime.wYear, systime.wMonth, systime.wDay, 
			systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds);
		f << strInfo;
		f << str << endl;
		f.close();
	}

	long long									userid;
	bool										is_auto;					// 是否托管
	bool										is_drop;					// 是否断线
	bool										is_ting;					// 是否听牌
	int											m_double;					// 加倍
	char										m_ming_gang_count1;			// 明杠数1
	char										m_ming_gang_count2;			// 明杠数2
	char										m_an_gang_count;			// 暗杠数
	
	uint32_t									m_current_status;			// 当前抓牌状态，=1自摸，=2点炮
	bool										m_is_get_a_card;			// 实际发到一张牌，因为当认为吃碰是无发牌时抓牌，会出现本来不应该胡的检测到胡了

	uint32_t									m_hu_clock_when_is_ting;	// 听时胡牌计时10秒

	bool										m_miao_shou_hui_chun;		// 四种特殊番型：妙手回春
	bool										m_hai_di_lao_yue;			// 四种特殊番型：海底捞月
	bool										m_gang_shang_kai_hua;		// 四种特殊番型：杠上开花
	bool										m_qiang_gang_hu;			// 四种特殊番型：抢杠胡

	std::vector<pai_kind>						m_pais_in_hand;				// 手上的牌
	std::vector<pai_kind>						m_pais_on_table;			// 打出后在桌上的牌，包括花
	std::vector<pai_kind>						m_pais_flowers;				// 打出的花
	std::vector<std::vector<pai_kind>>			m_pais_chew_pong_kong;		// 吃碰杠出的牌
	char										m_flag_for_ming_an[4];		// 明暗杠标记，为断线重连用=1暗，=2明1，=3明2
	std::vector<uint32_t>						m_ting_cards;				// 所听的那些牌,真值表示，非唯一值
	uint32_t									m_last_pai;					// 最后的那张牌，唯一值
	uint32_t									JIANG;						// 将牌
	player										*m_oppisite_player;			// 指向另一家的指针
	std::vector<pai_kind>						m_all_pais;					// 所有牌()

	bool										m_is_jia_bei_check_ting;	// 用于听和胡同时出现时，听不显示，而需要点放弃或加倍后，再次检查
	uint32_t									m_sort_jiang;				// 新的番型辅助变量
	//服务器共同判断吃，碰，杠，胡，听的函数统一移到玩家这里,降低服务器逻辑复杂度
	std::map<uint32_t,std::vector<chew_struct_data>> m_map_table_for_chew;	// 存储可吃牌的表数据,key:例如一条，value：例如一个chew_struct_data包含了二条和三条
	std::vector<chew_struct_data>				m_vec_check_chew;			// 检测出来的可吃表，存的是唯一值
	std::vector<chew_struct_data>				m_vec_check_peng;			// 检测出来的可碰表，存的是唯一值
	std::vector<chew_struct_data>				m_vec_check_an_gang;		// 检测出来的可暗杠表，存的是唯一值
	std::vector<chew_struct_data>				m_vec_check_ming_gang1;		// 检测出来的可明杠1表,四张牌不分先后，存的是唯一值
	std::vector<chew_struct_data>				m_vec_check_ming_gang2;		// 检测出来的可明杠2表，只有第一张有效，存的是唯一值
	uint32_t									m_check_ting[2][16][16];	// 检测出来的可听表，一维：=0表示还有几张，=1表示几番。二维：去掉的牌，三维：增加的牌，均为真值
	int											m_check_hu[2];				// 检测出来胡可胡表,=0胡哪张,唯一值，=1番数
	uint32_t									m_judge_flag[7];			// 待用标记，实际数量表示有多少个，如吃有多少个，便于查询，第一个，吃，第二个，碰，
																			// 第三个，暗杠，第四个，明杠1，第五个，明杠2，第六个，听，第七个，胡
	MjHuPaiFanShuComputer						m_fan_helper;				// 番数帮助

	NewHuPaiFanShuComputer						m_normal_fan_helper;		// 重新设计的番数计算器普通版
	NewHuPaiFanShuComputer2						m_qidui_fan_helper;			// 重新设计的番数计算器七对版

	int											m_hu_status;				// 胡的情况，普通胡=1，2=七对胡，可能还有其他
	//排序手上的牌，依据真值由小到大
	void HandPaiSort();
	//新一局游戏开始时调用初始化每个玩家
	void on_new_game();
	//载入吃型表
	void LoadChewTable();
	//清除所有的判断表,调用CheckAllJudge前先调用此函数，以清除前一次的
	void ClearAllJudge();
	//检测所有
	void CheckAllJudge();
	//检测吃
	void CheckChi();
	//检测碰
	void CheckPeng();
	//检测暗杠
	void CheckAnGang();
	//检测明杠1
	void CheckMingGang1();
	//检测明杠2
	void CheckMingGang2();
	//检测胡
	void CheckHu();
	//检测听
	void CheckTing();
	//胡牌判断函数
	uint32_t Hu(uint32_t PAI[16]);
	//传入形参按一条至九条，然后东南西北中发白编号
	uint32_t Remain(uint32_t PAI[16]);
	//计算胡番数
	uint32_t GetHuFan();
	//计算听番数
	uint32_t GetTingFan(uint32_t u32Add,uint32_t u32Minus);
	//计算番数
	uint32_t GetFan(int64_t &fan_flag,bool bComputeIt=false);
	//检测是否手上有花,有，返回花的唯一值，否，返回0
	uint32_t CheckFlower();
	//补花，返回替补的那张牌，唯一值
	void DeleteACard(uint32_t flower);
	//加一张牌,参数唯一值
	void AddACard(uint32_t u32RealCard);
	//设置对家自摸点炮状态
	void SetOppisiteZiMoStatus();
	//设置自己自摸点炮状态
	void SetMyZiMoStatus();
	//处理出单张牌
	bool ProcessOutACard(uint32_t u32RealCard);
	//处理吃牌
	bool ProcessChi(uint32_t index,uint32_t &ret0,uint32_t &ret1,uint32_t &ret2);
	//处理碰牌
	bool ProcessPeng(uint32_t index,uint32_t &ret0,uint32_t &ret1,uint32_t &ret2);
	//处理暗杠
	bool ProcessAnGang(uint32_t u32Value);
	//处理明杠1
	bool ProcessMingGang1(uint32_t u32Value);
	//处理明杠2
	bool ProcessMingGang2(uint32_t u32RealCard);
	//处理放弃
	void ProcessFangQi();
	//处理听
	void ProcessTing(uint32_t &index);
	//处理加倍
	void ProcessJiaBei();
	//设置最后一次牌
	void SetLastPai(uint32_t pai);
	//设置一次所有牌
	void SetAllPai(std::vector<pai_kind> pai_group);
	//番型计算
	void PreProcess();
	//番型计算辅助函数
	uint32_t SortFanCards(uint32_t PAI[16],std::vector<uint32_t> &vec_value,std::vector<uint32_t> &vec_jiang_value);
	//番型计算（七对专用）
	void PreProcess2(uint32_t qiduipai[16]);
	//结束后将番型也传给客户端时用到
	void SetResultFan(int &fan0,int &fan1,int &fan2,bool bIsNormal = true);
	//类似判断胡
	//uint32_t Remain(uint32_t PAI[16]);
};

