#pragma once
#include "games/server_share/include/match_table.h"
#include "interface/helper/simple_timer_manager.h"
//#include "games/server_share/include/round_timer.h"
#include "../cmd/twomajong.pb.h"

#include "logger/cmd_log.h"
#include "interface/helper/function_array.h"

#include "../cmd/cmd_twomajong.h"
#include "majong_pai.h"
#include "twomajong_share.h"

#include <string>



using namespace bs::twomajong;
using namespace std;

class twomajongGameLogic : public IGameTableSink
{

	struct MajongPai
	{
		enum CardId pai_id;
		enum CardValue pai_value;
	};

	IMatchTableFrame * m_pFrame;

	TLRoundInfo * round_info_ = nullptr;

	std::vector<struct TLTablePlayer*> *players_;

	size_t pulse_count_ = 0;
	SimpleTimerManager round_timer_;

	std::vector<TLPlayerRoundResult> vec_round_result;			//��Ϸ���

   

   string			m_str_last_recordinfo;			//�ֿ���¼
public:
   twomajongGameLogic ( void );
   virtual ~twomajongGameLogic ( void );

   void OnTestZuoPai();			//����ʱʹ�ã������ļ�������ƹ���

public:
   virtual void StartRound ( TLRoundInfo *pInfo, IMatchTableFrame*pFrame, std::vector<struct TLTablePlayer*> *uid_arr );


   /// nMS ��ʾ ��ֿ�ʼ֮��ĺ�����,���ÿ500ms����һ��
   virtual void OnPulse ( uint64_t ms );

   // ��Ҷ���
   //virtual void OnPlayerAct(int nSeatIndex,void *pData,size_t nBytes)=0;
   //  IMsgReader �������ɿ�ܹ���
   virtual void OnPlayerMsg ( int nSeatIndex, const std::string & data, uint32_t cmd_subid );

   virtual void OnWatcherMsg ( uint64_t session_id, const std::string & data, uint32_t cmd_subid );

   // ��ҵ������»����ˣ��������·��;ֿ���Ϣ����
   //virtual void OnPlayerBack ( int nSeatIndex ) = 0;

   /*
   *
   ע�⣺nActType ��Ӧ���ǳ��涯�����ĵĲ�������
   nActType=0 ��ʾpass
   nActType=1 ��ʾ����
   nActType=2 ����
   nActType=3 ȷ��ί��
   nActType=4 ���ί��
   =7 վ��(�Ƹ�����Ϸ����)
   */
   virtual void OnPlayerOtherAction ( int nSeatIndex, int nActType );

   virtual void Destroy ( );


   //һ���µ��Թ��߽�����
   /*
   @param watcher_sessionid ��ʾ�Թ��ߵ�userid ��������id
   */
   // virtual void OnNewWatcher ( uint64_t watcher_sessionid, int seat_index ) = 0;

   // ȡ�����һ�ֵ��ƾּ�¼��Ϣ
   /*
   *
   ������������
   "keyword":"���� 4ը ���",
   "actions":[
   {"type":"trust","time":1354258305","seat":"1", "animation":"","objects":""},
   {"type":"play","time":1354258305","seat":"3", "animation":"","objects":"��3��3"},
   {"type":"play","time":1354258308","seat":"1", "animation":"","objects":"��K��K"},
   {"type":"play","time":1354258310","seat":"2", "animation":"","objects":"��A÷A"},
   {"type":"play","time":1354258311","seat":"3", "animation":"���","objects":"��MСM"},
   {"type":"play","time":1354258312","seat":"3", "animation":"", "objects":"��Q"}
   ],
   */
   virtual const char* GetLastRecordInfo ( );

   // ȡ�õ�ǰ�ֵĸ���Ҿֿ�����
   // 
   virtual const PlayerRoundFeature * GetLastRoundFeature ( int nSeatIndex );

   // Ҫ�������߼������жϱ��֣���������
   virtual void ToEndRoundWithBreak ( );

   // д�ֽ����session_id ��WriteTableScore��WriteUserScore �Ľ��,result_code = 0 ��ʾ�ɹ���
   virtual void OnWriteScoreFinish ( uint32_t session_id, int result_code );

   virtual void BS_OnGameRoundSceneReq ( uint32_t seat_index, uint64_t watcher_id, bool is_watcher, const  std::string & data_req );

   virtual void BS_GetSupectPlayer ( std::vector<uint64_t>& users, std::vector<std::string>&reason_words, std::vector<uint32_t>& judge_type ) override;
   ////////////���Ĵ���

   virtual void OnBuyResult ( uint64_t session_id, uint64_t user_id, uint32_t result_code, const std::string & result_info ) override;
  virtual void OnRecvCommandFromApp ( uint64_t session, const std::string &data, uint32_t cmd_kind, uint32_t cmd_subid, uint32_t src_apptype, uint32_t src_appid ) override;

public:
   FunctionArray<twomajongGameLogic, bs::twomajong::CMDID_Twomajong::IDLast> function_twoddz_;
   void on_game_begin ( bool newTurn );	// һ����Ϸ��ʼ
   void on_pro_bid_score ( bs::CMD_base* req );
   void on_pro_giveup_first(bs::CMD_base* req);		//����
   void ReFapaiToPlayer ( int seat_id );				//��seat_id�ط���
   void on_pro_out_cards_req ( bs::CMD_base* req );
   void on_pro_set_auto ( bs::CMD_base* req );
   void on_pro_game_data_req ( bs::CMD_base* req );
   void on_pro_expresssion ( bs::CMD_base* req );
   void on_game_end ( int esc = -1 );		// һ����Ϸ����
   void on_pro_gotofailure(bs::CMD_base* req);		//����

   void gotobidscoreend();			//ֱ�ӽзֽ���(�����̨��)

   int find_bomb_for_gotofailure(int seat);			//����ը������

   void SendToAllPlayerInTable ( CMDID_Twomajong cmdid, string buff );			//���͸������ڵ��������
   void SendToAllPlayerInTable(CMDID_Twomajong cmdid, bs::CMD_base* pro);
   void SendToOnePlayerBySeatid(CMDID_Twomajong cmdid, bs::CMD_base* pro, uint32_t seat_id);

   //����ʹ��
public:
   int	GetPlayerSeatID ( uint64_t user_id );
   uint64_t	GetPlayerUserID ( int seat_id );
   uint64_t	GetFundBySeatID ( int seat_id );			//ͨ����λ�Ż�ȡ��ҵı���ͳ�ƻ���(Ѫ�������ǻ��֣����Ƿ���������������)

   bool		isRobot ( uint64_t user_id );			//�Ƿ��ǻ�����

   ////////////�߼�����
public:
   void init ( );
   void ShufflePai ( bool newTurn );			//ϴ��
   void FaPai ( );							//����
   void DealNormalCards(int& next_card_idx);		//��ͨ����(�������ʱ�������һ��)
   void DealGoodCards ( int& next_card_idx );		//������
   void do_auto ( );
   void do_auto_once ( );

   bool CheckChi(OutCardsReq &msg, struct PlayerData &player_data);		//У���
   bool CheckPeng(OutCardsReq &msg, struct PlayerData &player_data);	//У����
   bool CheckGang(OutCardsReq &msg, struct PlayerData &player_data);	//У���
   bool CheckTing(OutCardsReq &msg, struct PlayerData &player_data);	//У����
   bool CheckHu(OutCardsReq &msg, struct PlayerData &player_data);	//У���
   bool CheckGetCard(OutCardsReq &msg, struct PlayerData &player_data);	//У��ץ��
   bool CheckExchangeHua(OutCardsReq &msg, struct PlayerData &player_data);	//У�鲹��
   bool CheckOutCard(OutCardsReq &msg, struct PlayerData &player_data); //У�����

   bool IsPaiExist(string sub_pai, bool hand_card_id[73]);	//�ж�sub_pai�Ƿ���hand_card_id����
   //����λ��Ϊseat_id����ҵ������а�sub_pai��Ӧ�����Ƴ�
   void RemoveFromHandPai(string sub_pai, int seat_id);	
   //ͨ�������ܻ�õ�ǰ������
   void GetNewOutCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data);
   //���ƺ��ﲹ������
   void SupplyHandCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data);
   //�������ƣ����ƣ�����ʱ��Ҫturnto���˲�����
   void DropHandCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data);
   //����˳�ʱ�Զ��й�����
   void SetTimeOutAuto(int seat_id);

   int next_player ( int p )
   {
      if ( p == MAX_USERS )
         return 1;
      else
         return ( p + 1 );
   }
   int prev_player ( int p )
   {
      if ( p == 1 )
         return MAX_USERS;
      else
         return ( p - 1 );
   }
   //int next_player(int p) { return (++p) % MAX_USERS; }	// ��һ�����
   //int prev_player(int p) { return (--p + MAX_USERS) % MAX_USERS; }	// ��һ�����

   int PlayerTimeoutMinus ( int seat_id );
   int punishFarmer ( );
   void ToGameEnd ( unsigned short nWinChairID, bool bWinIsBank );

   void verifyMoney ( );			//У�����ӺͿ۳��Ľ��(�䵽0��Ӯֻ��Ӯ�Լ�������Ǯ��)

//   string GetCardStr ( PAI pai );

	uint64_t CheckPlayerSupect(int seat, string& str, SupectJudgeType& judgetype);			//�������Ƿ����쳣����,�������userid����д�����������ж��쳣������

	vector<struct MajongPai>			m_all_pai;			//���е���72��
	int m_current_get_index;	//��ǰҪ�����ץ������m_all_pai���±�
	GameState		m_state_step;				// ��ǰ��Ϸ״̬
	int				m_current_seatid;		// ��ǰ�ֵ���ҵ���λ��
	MajongPai	m_new_outcard;	//��ǰ������ֵ

	time_t m_begin_time;	//��ʱ��ʼʱ��
	time_t m_out_time;		//��ʱʱ��

	std::vector<PlayerData>	m_players;				// �����Ϸ���ݣ������Թۣ�����λ�Ŵ��,[0]û������
public:
   static const int	ready_timeout = 99;		// ��ʼ��Ϸ��ʱʱ��
   static const int	bid_timeout = 10;		// �е�����ʱʱ��
   static const int	first_out_timeout = 30;		// �׳��Ƴ�ʱʱ��
   static const int	out_timeout = 15;		// ���Ƴ�ʱʱ��

   static const int giveupfirst_timeout = 15;		//����ʱ��

   static const int	dealcard_timeout = 5;		// ����ʱ��

	//////////////////////test
	//static const int	ready_timeout = 99;		// ��ʼ��Ϸ��ʱʱ��
	//static const int	bid_timeout = 99;		// �е�����ʱʱ��
	//static const int	first_out_timeout = 99;		// �׳��Ƴ�ʱʱ��
	//static const int	out_timeout = 99;		// ���Ƴ�ʱʱ��

	//static const int giveupfirst_timeout = 99;		//����ʱ��

	//static const int	dealcard_timeout = 20;		// ����ʱ��
	//////////////////////test

   static const int	game_end_timeout = 1;			//��Ϸ����·��ĳ�ʱʱ��
   static const int	round_end_timeout = 2;			//һ�ֽ���֪ͨ��ܵĳ�ʱʱ��
   static const int	waited_drop_timeout = 15;		// ÿ�εȴ����ߵ����ʱ�� 
   static const int	waited_drop_times = 1;		// ÿ�ֵȴ����ߵ����������
protected:
	
   int                 m_nRoomType;										//��������

//   CGameData			m_GameData;											// ��Ϸ����
//   CGameConfig			m_GameConfig;

//   CMDTwoddz_game_end		proEnd;

   std::map<int, std::vector<std::vector<uint8_t>>>			m_playeroutcards;

   bool bWinIsBank = false;				//�Ƿ��ǵ���Ӯ

   uint32_t		m_outcards_step = 0;			//���Ƶ����к�(ÿ�δ���ʱturnto��ʱ���·�������)

   uint32_t			m_redeal_cards_cnt = 0;			//���·��ƵĴ���(ÿ�����)
   uint32_t			m_total_redealcards_cnt = 0;		//�ܵķ��ƴ���

   bool				m_bCalCardsOk = false;			//�Ƿ��Ѿ������
   uint32_t			m_total_round = 0;			//�ܾ���
   uint32_t			m_cur_fapaitime = 0;		//���ַ��ƺ�ʱ
   uint64_t			m_total_fapaitime = 0;		//�ܷ��ƺ�ʱ

   map<int, int>		m_maphandsCnt;			//ÿ���������Ƴ��ֵĴ���
   map<int, int>		m_mapCalCardsOKCount;		///����ok��ͳ��(ÿһ����Ҫ�ط����ٴβ��ܴ��)

//   PAI					m_label_card;			//��Ϸ����ʱѡ�������ƣ�����ʱʹ��
   int					m_giveup_first = 0;			//�Ƿ�����
};