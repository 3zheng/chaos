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

	std::vector<TLPlayerRoundResult> vec_round_result;			//游戏结果

   

   string			m_str_last_recordinfo;			//局况记录
public:
   twomajongGameLogic ( void );
   virtual ~twomajongGameLogic ( void );

   void OnTestZuoPai();			//测试时使用，配置文件里的做牌功能

public:
   virtual void StartRound ( TLRoundInfo *pInfo, IMatchTableFrame*pFrame, std::vector<struct TLTablePlayer*> *uid_arr );


   /// nMS 表示 这局开始之后的毫秒数,大概每500ms调用一次
   virtual void OnPulse ( uint64_t ms );

   // 玩家动作
   //virtual void OnPlayerAct(int nSeatIndex,void *pData,size_t nBytes)=0;
   //  IMsgReader 的生存由框架管理
   virtual void OnPlayerMsg ( int nSeatIndex, const std::string & data, uint32_t cmd_subid );

   virtual void OnWatcherMsg ( uint64_t session_id, const std::string & data, uint32_t cmd_subid );

   // 玩家掉线重新回来了，立即重新发送局况信息给他
   //virtual void OnPlayerBack ( int nSeatIndex ) = 0;

   /*
   *
   注意：nActType 对应的是常规动作报文的操作类型
   nActType=0 表示pass
   nActType=1 表示认输
   nActType=2 逃跑
   nActType=3 确认委托
   nActType=4 解除委托
   =7 站立(财富类游戏有用)
   */
   virtual void OnPlayerOtherAction ( int nSeatIndex, int nActType );

   virtual void Destroy ( );


   //一个新的旁观者进来了
   /*
   @param watcher_sessionid 表示旁观者的userid 或者连接id
   */
   // virtual void OnNewWatcher ( uint64_t watcher_sessionid, int seat_index ) = 0;

   // 取得最近一局的牌局记录信息
   /*
   *
   类似于如下行
   "keyword":"春天 4炸 火箭",
   "actions":[
   {"type":"trust","time":1354258305","seat":"1", "animation":"","objects":""},
   {"type":"play","time":1354258305","seat":"3", "animation":"","objects":"黑3方3"},
   {"type":"play","time":1354258308","seat":"1", "animation":"","objects":"黑K红K"},
   {"type":"play","time":1354258310","seat":"2", "animation":"","objects":"黑A梅A"},
   {"type":"play","time":1354258311","seat":"3", "animation":"火箭","objects":"大M小M"},
   {"type":"play","time":1354258312","seat":"3", "animation":"", "objects":"红Q"}
   ],
   */
   virtual const char* GetLastRecordInfo ( );

   // 取得当前局的各玩家局况特征
   // 
   virtual const PlayerRoundFeature * GetLastRoundFeature ( int nSeatIndex );

   // 要求牌桌逻辑立刻中断本局，放弃本局
   virtual void ToEndRoundWithBreak ( );

   // 写分结果，session_id 是WriteTableScore与WriteUserScore 的结果,result_code = 0 表示成功。
   virtual void OnWriteScoreFinish ( uint32_t session_id, int result_code );

   virtual void BS_OnGameRoundSceneReq ( uint32_t seat_index, uint64_t watcher_id, bool is_watcher, const  std::string & data_req );

   virtual void BS_GetSupectPlayer ( std::vector<uint64_t>& users, std::vector<std::string>&reason_words, std::vector<uint32_t>& judge_type ) override;
   ////////////报文处理

   virtual void OnBuyResult ( uint64_t session_id, uint64_t user_id, uint32_t result_code, const std::string & result_info ) override;
  virtual void OnRecvCommandFromApp ( uint64_t session, const std::string &data, uint32_t cmd_kind, uint32_t cmd_subid, uint32_t src_apptype, uint32_t src_appid ) override;

public:
   FunctionArray<twomajongGameLogic, bs::twomajong::CMDID_Twomajong::IDLast> function_twoddz_;
   void on_game_begin ( bool newTurn );	// 一局游戏开始
   void on_pro_bid_score ( bs::CMD_base* req );
   void on_pro_giveup_first(bs::CMD_base* req);		//让先
   void ReFapaiToPlayer ( int seat_id );				//向seat_id重发牌
   void on_pro_out_cards_req ( bs::CMD_base* req );
   void on_pro_set_auto ( bs::CMD_base* req );
   void on_pro_game_data_req ( bs::CMD_base* req );
   void on_pro_expresssion ( bs::CMD_base* req );
   void on_game_end ( int esc = -1 );		// 一局游戏结束
   void on_pro_gotofailure(bs::CMD_base* req);		//认输

   void gotobidscoreend();			//直接叫分结束(针对擂台赛)

   int find_bomb_for_gotofailure(int seat);			//返回炸弹个数

   void SendToAllPlayerInTable ( CMDID_Twomajong cmdid, string buff );			//发送给桌子内的所有玩家
   void SendToAllPlayerInTable(CMDID_Twomajong cmdid, bs::CMD_base* pro);
   void SendToOnePlayerBySeatid(CMDID_Twomajong cmdid, bs::CMD_base* pro, uint32_t seat_id);

   //辅助使用
public:
   int	GetPlayerSeatID ( uint64_t user_id );
   uint64_t	GetPlayerUserID ( int seat_id );
   uint64_t	GetFundBySeatID ( int seat_id );			//通过座位号获取玩家的本局统计货币(血量或者是积分，以是否自由赛来做区分)

   bool		isRobot ( uint64_t user_id );			//是否是机器人

   ////////////逻辑处理
public:
   void init ( );
   void ShufflePai ( bool newTurn );			//洗牌
   void FaPai ( );							//发牌
   void DealNormalCards(int& next_card_idx);		//普通发牌(火箭出现时，再随机一次)
   void DealGoodCards ( int& next_card_idx );		//发好牌
   void do_auto ( );
   void do_auto_once ( );

   bool CheckChi(OutCardsReq &msg, struct PlayerData &player_data);		//校验吃
   bool CheckPeng(OutCardsReq &msg, struct PlayerData &player_data);	//校验碰
   bool CheckGang(OutCardsReq &msg, struct PlayerData &player_data);	//校验杠
   bool CheckTing(OutCardsReq &msg, struct PlayerData &player_data);	//校验听
   bool CheckHu(OutCardsReq &msg, struct PlayerData &player_data);	//校验胡
   bool CheckGetCard(OutCardsReq &msg, struct PlayerData &player_data);	//校验抓牌
   bool CheckExchangeHua(OutCardsReq &msg, struct PlayerData &player_data);	//校验补花
   bool CheckOutCard(OutCardsReq &msg, struct PlayerData &player_data); //校验出牌

   bool IsPaiExist(string sub_pai, bool hand_card_id[73]);	//判断sub_pai是否在hand_card_id存在
   //从座位号为seat_id的玩家的手牌中把sub_pai对应的牌移除
   void RemoveFromHandPai(string sub_pai, int seat_id);	
   //通过吃碰杠获得当前出的牌
   void GetNewOutCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data);
   //从牌河里补充手牌
   void SupplyHandCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data);
   //正常出牌（丢牌），这时候要turnto换人操作了
   void DropHandCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data);
   //服务端超时自动托管设置
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
   //int next_player(int p) { return (++p) % MAX_USERS; }	// 下一个玩家
   //int prev_player(int p) { return (--p + MAX_USERS) % MAX_USERS; }	// 上一个玩家

   int PlayerTimeoutMinus ( int seat_id );
   int punishFarmer ( );
   void ToGameEnd ( unsigned short nWinChairID, bool bWinIsBank );

   void verifyMoney ( );			//校验增加和扣除的金额(输到0，赢只能赢自己所带的钱数)

//   string GetCardStr ( PAI pai );

	uint64_t CheckPlayerSupect(int seat, string& str, SupectJudgeType& judgetype);			//检测玩家是否有异常动作,返回玩家userid，填写文字描述和判断异常的类型

	vector<struct MajongPai>			m_all_pai;			//所有的牌72张
	int m_current_get_index;	//当前要被玩家抓的牌在m_all_pai的下标
	GameState		m_state_step;				// 当前游戏状态
	int				m_current_seatid;		// 当前轮到玩家的座位号
	MajongPai	m_new_outcard;	//当前出的牌值

	time_t m_begin_time;	//计时开始时间
	time_t m_out_time;		//超时时间

	std::vector<PlayerData>	m_players;				// 玩家游戏数据，不含旁观，按座位号存放,[0]没有意义
public:
   static const int	ready_timeout = 99;		// 开始游戏超时时间
   static const int	bid_timeout = 10;		// 叫地主超时时间
   static const int	first_out_timeout = 30;		// 首出牌超时时间
   static const int	out_timeout = 15;		// 出牌超时时间

   static const int giveupfirst_timeout = 15;		//让先时间

   static const int	dealcard_timeout = 5;		// 发牌时间

	//////////////////////test
	//static const int	ready_timeout = 99;		// 开始游戏超时时间
	//static const int	bid_timeout = 99;		// 叫地主超时时间
	//static const int	first_out_timeout = 99;		// 首出牌超时时间
	//static const int	out_timeout = 99;		// 出牌超时时间

	//static const int giveupfirst_timeout = 99;		//让先时间

	//static const int	dealcard_timeout = 20;		// 发牌时间
	//////////////////////test

   static const int	game_end_timeout = 1;			//游戏结果下发的超时时间
   static const int	round_end_timeout = 2;			//一局结束通知框架的超时时间
   static const int	waited_drop_timeout = 15;		// 每次等待掉线的玩家时长 
   static const int	waited_drop_times = 1;		// 每局等待掉线的玩家最大次数
protected:
	
   int                 m_nRoomType;										//房间类型

//   CGameData			m_GameData;											// 游戏数据
//   CGameConfig			m_GameConfig;

//   CMDTwoddz_game_end		proEnd;

   std::map<int, std::vector<std::vector<uint8_t>>>			m_playeroutcards;

   bool bWinIsBank = false;				//是否是地主赢

   uint32_t		m_outcards_step = 0;			//出牌的序列号(每次打牌时turnto的时候下发，递增)

   uint32_t			m_redeal_cards_cnt = 0;			//重新发牌的次数(每局清空)
   uint32_t			m_total_redealcards_cnt = 0;		//总的发牌次数

   bool				m_bCalCardsOk = false;			//是否已经算过牌
   uint32_t			m_total_round = 0;			//总局数
   uint32_t			m_cur_fapaitime = 0;		//本局发牌耗时
   uint64_t			m_total_fapaitime = 0;		//总发牌耗时

   map<int, int>		m_maphandsCnt;			//每个手数的牌出现的次数
   map<int, int>		m_mapCalCardsOKCount;		///发牌ok的统计(每一次需要重发多少次才能达标)

//   PAI					m_label_card;			//游戏发牌时选出来的牌，发牌时使用
   int					m_giveup_first = 0;			//是否让先
};