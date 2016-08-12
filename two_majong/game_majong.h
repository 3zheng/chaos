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
	// ��λ��ҵľֿ�����
	vector<PlayerRoundFeature> m_arrRoundFeatures;
public:
	//�齫��Ϸ״̬����Ϊ׼��������
	enum status_mj {mj_s_preparing,mj_begin_and_shaizi,mj_fa_pai,mj_del_flower,mj_s_out,mj_tuo_guan,mj_ting};

	static const int	ready_timeout = 125;		// ��ʼ��Ϸ��ʱʱ��
	static const int	bid_timeout = 10;		// �зֳ�ʱʱ��
	static const int	out_timeout = 15;		// ���Ƴ�ʱʱ��
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

	void on_game_begin(bool newTurn);				// һ����Ϸ��ʼ
	void on_pro_expresssion(int seat_id, pro_expression &pro);//����
	std::vector<pai_kind> mycard();					// �����ã����Լ�����
	void WashCards();								// ϴ��
	void SendCards();								// ����
	uint32_t GetACard();							// ��һ����,����Ψһֵ
	
	void ChangeTurnNotify();						// ��ͷָ��

	void SendACard();								// ͨ��ץһ��
	void SendACardNormal();							// ����ץһ��
	void SendACardReverse();						// ����ץһ��
	void OnClickBtn(pro_click_btn_c pro);
	
	void ZiMoSendBtn();
	void DianPaoSendBtn();

	//����
	void ProcessOutCardReq(uint32_t u32RealCard);
	void ProcessChiReq(uint32_t index);
	void ProcessPengReq(uint32_t index);
	void ProcessGangReq(uint32_t index);
	void ProcessMingGang1Req(uint32_t index);
	void ProcessMingGang2Req(uint32_t index);
	void ProcessHuReq(uint32_t index);
	void ProcessTingReq(uint32_t &index);//����Ϊȥ��������
	void ProcessFangQiReq(uint32_t index);
	void ProcessJiaBei(uint32_t index);
	void ProcessHuang();
	void RoundRecord(bool bWin = true);

public:
	std::vector<pai_kind>	m_all_pais;				// ������
	uint32_t				m_order_recorder[4];	// �ͻ����������Ƽ�¼��,0��1��¼���ӣ�2��¼˳ʱ��ĺţ�3��¼��ʱ��ĺ�
	std::vector<player>		m_players;
	status_mj				m_state;
	int						m_timeout;				// ��ǰ��Ϸ״̬�ĳ�ʱʱ��
	int						m_banker;				// ׯ����λ��,1or2
	int						m_money_rate;			// ��Ϸ�ұ���
	int						m_score_rate;			// ���ֱ���
	int						m_current_player;		// ��ǰ���
	uint64_t				m_begin;				// ��ǰ��Ϸ״̬�Ŀ�ʼʱ��
	uint32_t				m_last_pai;				// �����ƣ�����Ļ�������
	//uint32_t				JIANG;					// ����
	//std::map<uint32_t,std::vector<chew_struct_data>> m_map_table_for_chew;//�洢�ɳ��Ƶı�����,key:����һ����value������һ��chew_struct_data�����˶���������////////
	//std::vector<chew_struct_data>m_vec_check_chew;  // �������ĳԱ�//////
	//chew_struct_data		m_check_peng;			// ����������///////
	//chew_struct_data		m_check_gang;			// �������ĸ�//////
	//chew_struct_data		m_check_ming_gang1;		// ������������1///////
	//chew_struct_data        m_check_ming_gang2;		// ������������2///////
	//uint32_t				m_check_ting[16][16];	// ������������,=0��������=n��ʾ����n��///////
	//uint32_t				m_check_hu;				// ����������������///////
	CStringA				m_log_str;				// ��־��¼
	//MjHuPaiFanShuComputer   m_fan_helper;			// ��������///////
	bool					m_game_is_over;			// һ����Ϸ�Ƿ����
public:		//IGameTableSink�еĽӿ�
	void StartRound(int nTableId,bool newTurn,IMatchTableFrame*pFrame,int nPlayerCount=0,const char *pAttRule=0);
	void OnPulse(int nMS);
	void OnPlayerMsg(int nSeatIndex,IMsgReader * rr );
	void OnPlayerBack ( int SeatID );
	void OnPlayerOtherAction(int nSeatIndex,int nActType);
	void on_pro_game_data_req(int seat_id, bool bLookon=false, uint64_t nPlayerId=0, int nLookonFlags=0);		//�Ƿ����Թۣ�������Թ�nPlayerId��Ҫ��ֵΪ�Թ���ҵ�id�����ڷ��͸�������
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
			str1.Format("m_arrRoundFeatures[%d].feature countԽ�� =%d",nSeat,m_arrRoundFeatures[nSeat].feature_count);
			WriteLog(str1);
			return -1;
		}
	}
	virtual const wchar_t * GetLastRecordInfo();
	wstring		m_wstr_last_recordinfo;	// ��Ϸ������Ϣ
	wstring		GetCardStr(int cid);		//������ַ���
	//virtual char* GetRoundRecord(int &nDataSize){return NULL;}

	//void SetInitPaisInPlayerHand();

};

