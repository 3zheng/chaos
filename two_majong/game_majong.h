#pragma once

#include "games/server_share/include/match_table.h"
#include <string>
#include "player.h"
//#include "config.h"
#include "game_msg.h"



using namespace std;


class game_majong2 :public IGameTableSink
{
	IMatchTableFrame * m_pFrame;
	std::string m_attRules;
	uint64_t m_nLastPulseMS;

	int m_nCurrentTableId;
private:
	// 各位玩家的局况特性
	vector<PlayerRoundFeature> m_arrRoundFeatures;
public:
	//麻将游戏状态，分为准备，出牌
	enum status_mj {mj_s_preparing,mj_begin_and_shaizi,mj_fa_pai,mj_del_flower,mj_s_out,mj_tuo_guan,mj_ting};

	static const int	ready_timeout = 125;		// 开始游戏超时时间
	static const int	bid_timeout = 10;		// 叫分超时时间
	static const int	out_timeout = 15;		// 出牌超时时间
	void do_auto();

public:
	game_majong2(void);
	virtual ~game_majong2(void);
	const PlayerRoundFeature * GetLastRoundFeature(int nSeatIndex);
	void init();

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

	void on_game_begin(bool newTurn);				// 一局游戏开始
	void on_pro_expresssion(int seat_id, pro_expression &pro);//表情
	std::vector<pai_kind> mycard();					// 测试用，由自己填牌
	void WashCards();								// 洗牌
	void SendCards();								// 发牌
	uint32_t GetACard();							// 摸一张牌,返回唯一值
	
	void ChangeTurnNotify();						// 箭头指向

	void SendACard();								// 通用抓一张
	void SendACardNormal();							// 正向抓一张
	void SendACardReverse();						// 反向抓一张
	void OnClickBtn(pro_click_btn_c pro);
	
	void ZiMoSendBtn();
	void DianPaoSendBtn();

	//处理
	void ProcessOutCardReq(uint32_t u32RealCard);
	void ProcessChiReq(uint32_t index);
	void ProcessPengReq(uint32_t index);
	void ProcessGangReq(uint32_t index);
	void ProcessMingGang1Req(uint32_t index);
	void ProcessMingGang2Req(uint32_t index);
	void ProcessHuReq(uint32_t index);
	void ProcessTingReq(uint32_t &index);//参数为去掉的那张
	void ProcessFangQiReq(uint32_t index);
	void ProcessJiaBei(uint32_t index);
	void ProcessHuang();
	void RoundRecord(bool bWin = true);

public:
	std::vector<pai_kind>	m_all_pais;				// 所有牌
	uint32_t				m_order_recorder[4];	// 客户端桌面留牌记录器,0和1记录骰子，2记录顺时针的号，3记录逆时针的号
	std::vector<player>		m_players;
	status_mj				m_state;
	int						m_timeout;				// 当前游戏状态的超时时间
	int						m_banker;				// 庄家座位号,1or2
	int						m_money_rate;			// 游戏币倍数
	int						m_score_rate;			// 积分倍数
	int						m_current_player;		// 当前玩家
	uint64_t				m_begin;				// 当前游戏状态的开始时间
	uint32_t				m_last_pai;				// 最后的牌，打出的或自摸的
	//uint32_t				JIANG;					// 将牌
	//std::map<uint32_t,std::vector<chew_struct_data>> m_map_table_for_chew;//存储可吃牌的表数据,key:例如一条，value：例如一个chew_struct_data包含了二条和三条////////
	//std::vector<chew_struct_data>m_vec_check_chew;  // 检测出来的吃表//////
	//chew_struct_data		m_check_peng;			// 检测出来的碰///////
	//chew_struct_data		m_check_gang;			// 检测出来的杠//////
	//chew_struct_data		m_check_ming_gang1;		// 检测出来的明杠1///////
	//chew_struct_data        m_check_ming_gang2;		// 检测出来的明杠2///////
	//uint32_t				m_check_ting[16][16];	// 检测出来的听牌,=0不可听，=n表示可听n张///////
	//uint32_t				m_check_hu;				// 检测出来胡的哪张牌///////
	CStringA				m_log_str;				// 日志记录
	//MjHuPaiFanShuComputer   m_fan_helper;			// 番数帮助///////
	bool					m_game_is_over;			// 一局游戏是否结束
public:		//IGameTableSink中的接口
	void StartRound(int nTableId,bool newTurn,IMatchTableFrame*pFrame,int nPlayerCount=0,const char *pAttRule=0);
	void OnPulse(int nMS);
	void OnPlayerMsg(int nSeatIndex,IMsgReader * rr );
	void OnPlayerBack ( int SeatID );
	void OnPlayerOtherAction(int nSeatIndex,int nActType);
	void on_pro_game_data_req(int seat_id, bool bLookon=false, uint64_t nPlayerId=0, int nLookonFlags=0);		//是否是旁观，如果是旁观nPlayerId需要赋值为旁观玩家的id号用于发送给其数据
	//virtual IMsgWriter *GetLookonData(int nSeatIndex,int nLookonFlags) {return NULL;}
	virtual void GetLookonData(int nSeatIndex,int nLookonFlags,int & msgCount, IMsgWriter * & pOut);
	void Destroy(); 
	virtual void OnNewLookon(int nSeatIndex,uint64_t nlooked_connid,int nLookonFlags);
private:
	int SetRoundFeatures(int nSeat, int nIdx, int nValue = 0)
	{
		if (m_arrRoundFeatures[nSeat].feature_count >= 0 && m_arrRoundFeatures[nSeat].feature_count < RF_MAX_COUNT)
		{
			m_arrRoundFeatures[nSeat].itemid_arr[m_arrRoundFeatures[nSeat].feature_count] = nIdx;
			m_arrRoundFeatures[nSeat].itemdata_arr[m_arrRoundFeatures[nSeat].feature_count] = nValue;
			m_arrRoundFeatures[nSeat].feature_count++;
			return 0;
		}
		else
		{
			CStringA str1;
			str1.Format("m_arrRoundFeatures[%d].feature count越界 =%d",nSeat,m_arrRoundFeatures[nSeat].feature_count);
			WriteLog(str1);
			return -1;
		}
	}
	virtual const wchar_t * GetLastRecordInfo();
	wstring		m_wstr_last_recordinfo;	// 游戏过程信息
	wstring		GetCardStr(int cid);		//获得牌字符串
	//virtual char* GetRoundRecord(int &nDataSize){return NULL;}

	//void SetInitPaisInPlayerHand();

};

