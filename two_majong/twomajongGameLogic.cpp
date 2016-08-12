

#include "interface/base/itf_base.h"
#include "twomajongGameLogic.h"

#include "public/common/singleton.h"

#include "../ddz_share/getstringit.h"
#include "public/common/aw_convert.h"
#include <io.h>
#include <unordered_map>

#include "../ddz_share/CardsToCal.h"
#include "MjChewPongKongHuTingHelper.h"
#include <algorithm>

#pragma comment(lib, "libprotobuf.lib")

TABLE_SINK_API IGameTableSink *		CreateGameSink ( )
{
   return new twomajongGameLogic ( );
}

twomajongGameLogic::twomajongGameLogic ( void )
{
   function_twoddz_.InitTarget ( this );
   function_twoddz_.InitFunction(bs::twomajong::CMDID_Twomajong::IDGameOutCardsReq, &twomajongGameLogic::on_pro_out_cards_req);
   function_twoddz_.InitFunction(bs::twomajong::CMDID_Twomajong::IDGameSetAuto, &twomajongGameLogic::on_pro_set_auto);
   function_twoddz_.InitFunction(bs::twomajong::CMDID_Twomajong::IDGameExpression, &twomajongGameLogic::on_pro_expresssion);
   function_twoddz_.InitFunction(bs::twomajong::CMDID_Twomajong::IDGameDataReq, &twomajongGameLogic::on_pro_game_data_req);
   function_twoddz_.InitFunction(bs::twomajong::CMDID_Twomajong::IDGameGotoFailure, &twomajongGameLogic::on_pro_gotofailure);
   init ( );

   m_total_fapaitime = 0;
   m_total_round = 0;
   m_mapCalCardsOKCount.clear();
   m_maphandsCnt.clear();
}

twomajongGameLogic::~twomajongGameLogic ( void )
{

}
//初始化
void twomajongGameLogic::init()
{
	m_players.clear();

	//预先分配数据，因为m_players是以座位号为下标，而座位号又是从1开始的，所以要MAX_USERS+1,[0]数据是空的
	m_players.resize(MAX_USERS + 1);
}

void twomajongGameLogic::OnPulse(uint64_t nMS)
{
	time_t now_time = time(nullptr);
	time_t diff_time = now_time - m_begin_time;	//时间差

	switch (m_state_step)	//游戏阶段
	{
	case FAPAI:
		if (diff_time > m_out_time)	//发牌结束进入下个阶段
		{
			m_state_step = GameState::CHUPAI;
			CMDTwomajong_TurnToPlayer rsp;
			TurnToPlayer &turn = rsp.my_message_;
			m_current_seatid = m_pFrame->GetRand() % 2 + 1;	//从第一个开始
			turn.set_u8seatid(m_current_seatid);	//座位号不变
			turn.set_u32gameticket(time(nullptr));
			turn.set_u32lastmicroticket(m_out_time - (time(nullptr) - m_begin_time));
			//发送给所有玩家
			SendToAllPlayerInTable(IDGameTurnToPlayer, &rsp);

			m_begin_time = now_time;	//重设开始时间
		}
		break;
	case CHUPAI:
		if (diff_time > m_out_time)
		{
			//超时把当前玩家设为托管
			
		}
		break;
	default:
		break;
	}

	
}

void twomajongGameLogic::StartRound ( TLRoundInfo *pInfo, IMatchTableFrame *pFrame, std::vector<struct TLTablePlayer*> *uid_arr )
{
   //srand ( GetTickCount ( ) + ::GetCurrentThreadId ( ) + GetCurrentProcessId ( ) );
   round_info_ = pInfo;
   m_pFrame = pFrame;
   players_ = uid_arr;
   //赋值seat_id和user_id给m_players
   for (auto it = uid_arr->begin(); it != uid_arr->end(); it++)
   {
	   if (nullptr == *it)
	   {
		   continue;
	   }
	   if (0 == (*it)->seat_index)
	   {
		   continue;
	   }
	   uint32_t index = (*it)->seat_index;
	   m_players[index].seat_id = index;
	   m_players[index].user_id = (*it)->player_id;
   }

   m_total_round++;

   

   if ( m_str_last_recordinfo.empty ( ) )
      m_str_last_recordinfo.clear ( );

   m_str_last_recordinfo = "\n\t\"actions\":\n\t[";

   

   on_game_begin ( pInfo->is_newturn);
}


void twomajongGameLogic::OnPlayerMsg ( int nSeatIndex, const std::string & data, uint32_t cmd_subid )
{
   if ( !players_ )
   {
      return;
   }
   auto game_cmd = CreateCommand_Twomajong ( bs::EnumCommandKind::Game, cmd_subid, data );
   if ( game_cmd )
   {
      SetCommonFinishHandler ( game_cmd );
      auto pl = ( *players_ )[nSeatIndex];
      game_cmd->address_.gate_user_id = pl->player_id;
      game_cmd->address_.gate_conn_id = pl->conn_id;

	  if (game_cmd->cmd_subid_ == IDGameSetAuto)			//玩家主动托管
	  {
// 		  auto apply_cmd = (CMDTwoddz_set_auto*)game_cmd;
// 		  auto &apply_msg = apply_cmd->my_message_;
// 		  if (apply_msg.is_auto())
// 			  apply_msg.set_auto_type(AutoType::emActiveAuto);
// 		  else
// 			  apply_msg.set_auto_type(AutoType::emAutoNone);
	  }

      function_twoddz_.ProcessReq ( game_cmd );
      game_cmd->finish_handler_->Fire ( );
   }

}

void twomajongGameLogic::OnPlayerOtherAction ( int nSeatIndex, int nActType )
{

}

void twomajongGameLogic::OnWatcherMsg ( uint64_t session_id, const std::string & data, uint32_t cmd_subid )
{

}

const PlayerRoundFeature * twomajongGameLogic::GetLastRoundFeature ( int nSeatIndex )
{
   return nullptr;

}

void twomajongGameLogic::OnWriteScoreFinish ( uint32_t session_id, int result_code )
{

}

void twomajongGameLogic::Destroy ( )
{
   delete this;

}

const char* twomajongGameLogic::GetLastRecordInfo ( )
{
   return m_str_last_recordinfo.c_str ( );
}

void twomajongGameLogic::ToEndRoundWithBreak ( )
{
   //on_game_end();
}

int twomajongGameLogic::GetPlayerSeatID ( uint64_t user_id )
{
   for ( auto rr : *players_ )
   {
      if ( rr != NULL )
      {
         if ( rr->player_id == user_id )
            return rr->seat_index;
      }
   }

   return 0;
}

uint64_t twomajongGameLogic::GetPlayerUserID ( int seat_id )
{
   for ( auto rr : *players_ )
   {
      if ( rr != NULL )
      {
         if ( rr->seat_index == seat_id )
            return rr->player_id;
      }
   }

   return 0;
}

uint64_t twomajongGameLogic::GetFundBySeatID ( int seat_id )
{
   for ( auto rr : *players_ )
   {
      if ( rr != NULL )
      {
         if ( rr->seat_index == seat_id )
         {
            if ( round_info_->is_freematch )
               return rr->health;
            else
               return rr->score;
         }
      }
   }

   return 0;
}

bool twomajongGameLogic::isRobot ( uint64_t user_id )
{
   bool ret = false;
   for ( auto rr : *players_ )
   {
      if ( rr != NULL )
      {
         if ( rr->player_id == user_id )
         {
            /////////检测是否是机器人身份FIXME
            if ( rr->role_type == rr->ROLE_ROBOT )
            {
               ret = true;
            }
            break;
         }
      }
   }
   return ret;
}

void twomajongGameLogic::BS_OnGameRoundSceneReq ( uint32_t seat_index, uint64_t watcher_id, bool is_watcher, const std::string & data_req )
{
   return;
}

/////////////////////////////////////////////////////ddz游戏逻辑处理
void twomajongGameLogic::SendToAllPlayerInTable(CMDID_Twomajong cmdid, string buff)
{
   for ( int chairid = 1; chairid < ( int ) m_players.size ( ); chairid++ )
   {
      m_pFrame->SendDataToPlayer ( chairid, cmdid, buff.c_str ( ), buff.length ( ) );
   }
}

void twomajongGameLogic::SendToAllPlayerInTable(CMDID_Twomajong cmdid, bs::CMD_base* pro)
{
   std::string buff;
   pro->ToBuffer ( buff );

   for ( int chairid = 1; chairid < ( int ) m_players.size ( ); chairid++ )
   {
      m_pFrame->SendDataToPlayer ( chairid, cmdid, buff.c_str ( ), buff.length ( ) );
   }
}

void twomajongGameLogic::SendToOnePlayerBySeatid(CMDID_Twomajong cmdid, bs::CMD_base* pro, uint32_t seat_id)
{
	std::string buff;
	pro->ToBuffer(buff);

	
	m_pFrame->SendDataToPlayer(seat_id, cmdid, buff.c_str(), buff.length());
	
}

void twomajongGameLogic::do_auto_once ( )
{
   
}

void twomajongGameLogic::do_auto ( )
{
   
}


void twomajongGameLogic::on_game_begin ( bool newTurn )
{
   printf ( "\n---------on_game_begin-----\n" );
   

   ShufflePai ( newTurn );


   FaPai();
}

void twomajongGameLogic::ShufflePai ( bool newTurn )
{	
	//先把牌放入一个数组中
	m_all_pai.clear();
	struct MajongPai data;
	for (int i = 1; i <= 72; i++)
	{
		data.pai_id = (enum CardId)i;
		data.pai_value = PaiKind::GetValueFromRealCard(i);
		m_all_pai.push_back(data);
	}

	//洗牌，原理是遍历all_pai的每个元素，随机选取一个位置的值和当前遍历所在位置的元素值交换
	//srand((unsigned int)time(nullptr));
	for (auto it = m_all_pai.begin(); it != m_all_pai.end(); it++)
	{
		int change_index = m_pFrame->GetRand() % 72;
		struct MajongPai tmp_value = m_all_pai[change_index];
		m_all_pai[change_index] = *it;
		*it = tmp_value;
	}
	
   //BSLOG_DEBUG ( ( "游戏逻辑" ), "游戏开始时发牌:" << cardStr4Log );
}

void twomajongGameLogic::FaPai()
{
	//发牌
	CMDTwomajong_DealCards deal_cards;
	auto &msg = deal_cards.my_message_;
	char hand_pai1[26] = "";	//座位1的手牌,报文发送用,存card_id
	char hand_pai2[26] = "";	//座位2的手牌,报文发送用,存card_id
	uint32_t hand_value_pai1[17] = { 0 };	//用于吃碰杠听胡的逻辑判断,存card_value
	uint32_t hand_value_pai2[17] = { 0 };	//用于吃碰杠听胡的逻辑判断,存card_value

	for (int i = 0; i < 26; i++)
	{
		if (i < 13)
		{
			hand_pai1[i] = (char)m_all_pai[i].pai_id;
			hand_pai2[i] = '\0';
			int value_index = m_all_pai[i].pai_value;
			if (value_index > 0 && value_index < 17)	//花不属于逻辑判断范围
			{
				hand_value_pai1[value_index]++;
			}
		}
		else
		{
			hand_pai1[i] = '\0';
			hand_pai2[i] = (char)m_all_pai[i].pai_id;
			int value_index = m_all_pai[i].pai_value;
			if (value_index > 0 && value_index < 17)	//花不属于逻辑判断范围
			{
				hand_value_pai2[value_index]++;
			}
		}
		
	}
	m_current_get_index = 26;	//当前发牌的位置设为26

	//把牌发给对应用户
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		//把m_players[0]是空的
		if (0 == it->seat_id)
		{
			continue;
		}

		msg.set_u8seatid(it->seat_id);
		if (it->seat_id == 0)
		{
			msg.set_cards(hand_pai1, 26);
			for (int i = 0; i < 17; i++)	//给相应玩家的手牌赋值
			{
				it->hand_pai[i] = hand_value_pai1[i];
			}
			for (int i = 0; i < 13; i++)
			{
				int index = hand_pai1[i];
				it->hand_card_id[index] = true;
			}
		}
		else
		{
			msg.set_cards(hand_pai2, 26);
			for (int i = 0; i < 17; i++)
			{
				it->hand_pai[i] = hand_value_pai2[i];
			}
			for (int i = 13; i < 26; i++)
			{
				int index = hand_pai2[i];
				it->hand_card_id[index] = true;
			}
		}
		
		//发送给用户
		SendToOnePlayerBySeatid(CMDID_Twomajong::IDGameDealCards, &deal_cards, it->seat_id);
// 		for (int chairid = 1; chairid < (int)m_players.size(); chairid++)
// 		{
// 			m_pFrame->SendDataToPlayer(chairid, cmdid, buff.c_str(), buff.length());
// 		}	
	}
}
void  twomajongGameLogic::on_pro_out_cards_req(bs::CMD_base* req)
{
	CMDTwomajong_OutCardsReq *p = dynamic_cast<CMDTwomajong_OutCardsReq*>(req);
	if (!p)
	{
		return;
	}
	OutCardsReq &msg = p->my_message_;

	//获取seat_id
	int seat_id = GetPlayerSeatID(req->address_.gate_user_id);
	if (m_current_seatid != seat_id)
	{
		BSLOG_DEBUG(("游戏逻辑"), "没有轮到seat_id =" << seat_id << "的玩家出牌,当前允许出牌的用户座位" << m_current_seatid);
		return;
	}
		
	bool ret = false;
	PlayerData &player_data = m_players[seat_id];

	//校验是否有对应的手牌
	if (IsPaiExist(msg.out_cards(), player_data.hand_card_id) == false)
	{
		return;
	}

	//校验阶段
	switch (msg.player_action())
	{
	case Action::CHI:	//吃
		ret = CheckChi(msg, player_data);
		break;
	case Action::PENG:	//碰
		ret = CheckPeng(msg, player_data);
		break;
	case Action::GANG:	//杠
		ret = CheckGang(msg, player_data);
		break;
	case Action::TING:	//听
		ret = CheckTing(msg, player_data);
		break;
	case Action::HU:	//胡
		ret = CheckHu(msg, player_data);
		break;
	case Action::GETCARD:	//抓牌
		ret = CheckGetCard(msg, player_data);
		break;
	case Action::EXCHANGE_HUA:	//补花
		ret = CheckExchangeHua(msg, player_data);
		break;
	case Action::OUTCARD:	//正常出牌
		ret = CheckOutCard(msg, player_data);
		break;
	default:
		break;
	}

	//赋值和记录阶段
	CMDTwomajong_OutCardsReply rsp;
	OutCardsReply &rsp_msg = rsp.my_message_;
	rsp_msg.set_u8seatid(seat_id);
	rsp_msg.set_player_action(msg.player_action());
	//校验通过后对手牌进行记录
	switch (msg.player_action())
	{
	case Action::CHI:	//吃		
	case Action::PENG:	//碰		
		GetNewOutCard(msg, rsp_msg, player_data);	//只得到当前出的牌
		break;
	case Action::GANG:	//杠
		//得到当前出的牌，并且从牌河里抓一张牌补充手牌
		GetNewOutCard(msg, rsp_msg, player_data);	
		SupplyHandCard(msg, rsp_msg, player_data);
		break;
	case Action::TING:	//听
		
	case Action::HU:	//胡
		
		break;
	case Action::GETCARD:	//抓牌
		SupplyHandCard(msg, rsp_msg, player_data);
		break;
	case Action::EXCHANGE_HUA:	//补花
		RemoveFromHandPai(msg.out_cards(), seat_id);
		SupplyHandCard(msg, rsp_msg, player_data);
		break;
	case Action::OUTCARD:	//正常出牌
		DropHandCard(msg, rsp_msg, player_data);
		break;
	default:
		break;
	}

	//发送报文阶段
	switch (msg.player_action())
	{
	case Action::CHI:	//吃		
	case Action::PENG:	//碰		
	case Action::GANG:	//杠
	case Action::TING:	//听
	case Action::HU:	//胡
	case Action::OUTCARD:	//正常出牌
		//所有玩家发送相同的报文
		SendToAllPlayerInTable(IDGameOutCardsReply, &rsp);
		break;
	case Action::GETCARD:	//抓牌
	case Action::EXCHANGE_HUA:	//补花
		//向请求玩家发送完整的报文
		SendToOnePlayerBySeatid(IDGameOutCardsReply, &rsp, seat_id);
		//向对家发送不含cards数据的报文
		rsp_msg.set_cards("");
		SendToOnePlayerBySeatid(IDGameOutCardsReply, &rsp, next_player(seat_id));
		break;
	default:
		break;
	}
}

void twomajongGameLogic::OnTestZuoPai()
{
	
}

void twomajongGameLogic::BS_GetSupectPlayer(std::vector<uint64_t>& users, std::vector<std::string>&reason_words, std::vector<uint32_t>& judge_type)
{

}

void twomajongGameLogic::OnBuyResult(uint64_t session_id, uint64_t user_id, uint32_t result_code, const std::string & result_info)
{

}

void twomajongGameLogic::OnRecvCommandFromApp(uint64_t session, const std::string &data, uint32_t cmd_kind, uint32_t cmd_subid, uint32_t src_apptype, uint32_t src_appid)
{

}

void twomajongGameLogic::on_pro_set_auto(bs::CMD_base* req)
{

}

void twomajongGameLogic::on_pro_game_data_req(bs::CMD_base* req)
{

}

void twomajongGameLogic::on_pro_expresssion(bs::CMD_base* req)
{

}

void twomajongGameLogic::on_pro_gotofailure(bs::CMD_base* req)
{

}

bool twomajongGameLogic::CheckChi(OutCardsReq &msg, struct PlayerData &player_data)
{

	vector<enum CardValue> check_data;
	if (msg.got_cards().size() != 1 || msg.out_cards().size() != 2)	//校验张数
	{
		return false;
	}
	if (m_new_outcard.pai_id != msg.got_cards().c_str()[0])	//校验吃的牌值
	{
		return false;
	}

	//最后校验是否可以吃
	enum CardValue tmp_value;
	tmp_value = PaiKind::GetValueFromRealCard(msg.got_cards().c_str()[0]);
	check_data.push_back(tmp_value);
	tmp_value = PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[0]);
	check_data.push_back(tmp_value);
	tmp_value = PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[1]);
	check_data.push_back(tmp_value);
	//排序
	std::sort(check_data.begin(), check_data.end());
	//card_value的范围必须在value_bamboo_1到value_bamboo_9之间
	if (check_data[0] < CardValue::value_bamboo_1 || check_data[2] > CardValue::value_east_wind)
	{
		return false;
	}
	//吃的定义是[0][1][2]递增1
	if (check_data[1] - check_data[0] != 1 || check_data[2] - check_data[1] != 1)
	{
		return false;
	}


	return true;
}

bool twomajongGameLogic::CheckPeng(OutCardsReq &msg, struct PlayerData &player_data)
{
	vector<enum CardValue> check_data;
	if (msg.got_cards().size() != 1 || msg.out_cards().size() != 2)	//校验张数
	{
		return false;
	}
	if (m_new_outcard.pai_id != msg.got_cards().c_str()[0])	//校验碰的牌值
	{
		return false;
	}

	//最后校验是否可以碰
	enum CardValue tmp_value;
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.got_cards().c_str()[0]));
	check_data.push_back(tmp_value);
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[0]));
	check_data.push_back(tmp_value);
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[1]));
	check_data.push_back(tmp_value);
	//只有吃需要排序
	//碰的定义是[0][1][2]都相同
	if (check_data[0] != check_data[1] || check_data[0] != check_data[2])
	{
		return false;
	}
	if (check_data[0] < CardValue::value_bamboo_1 || check_data[0] > CardValue::value_white_dragon)
	{
		return false;
	}


	return true;
}

bool twomajongGameLogic::CheckGang(OutCardsReq &msg, struct PlayerData &player_data)
{
	vector<enum CardValue> check_data;
	if (msg.got_cards().size() != 1 || msg.out_cards().size() != 3)	//校验张数
	{
		return false;
	}
	if (m_new_outcard.pai_id != msg.got_cards().c_str()[0])	//校验杠的牌值
	{
		return false;
	}

	//最后校验是否可以杠
	enum CardValue tmp_value;
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.got_cards().c_str()[0]));
	check_data.push_back(tmp_value);
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[0]));
	check_data.push_back(tmp_value);
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[1]));
	check_data.push_back(tmp_value);
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[2]));
	check_data.push_back(tmp_value);

	//杠的定义是[0][1][2][3]都相同
	if (check_data[0] != check_data[1] || check_data[0] != check_data[2] || check_data[0] != check_data[3])
	{
		return false;
	}
	if (check_data[0] < CardValue::value_bamboo_1 || check_data[0] > CardValue::value_white_dragon)
	{
		return false;
	}


	return true;
}

bool twomajongGameLogic::CheckTing(OutCardsReq &msg, struct PlayerData &player_data)
{
	if (msg.out_cards().size() != 1)	//校验张数
	{
		return false;
	}

	MjChewPongKongHuTingHelper helper;
	for (int i = 0; i < 17; i++)
	{
		helper.m_PAI[i] = player_data.hand_pai[i];
	}
	if (helper.Ting() == 0)
	{
		return false;
	}

	return true;
}

bool twomajongGameLogic::CheckHu(OutCardsReq &msg, struct PlayerData &player_data)
{
	return true;
}

bool twomajongGameLogic::CheckGetCard(OutCardsReq &msg, struct PlayerData &player_data)
{
	//改变相应玩家数据
	CardId catch_id = m_all_pai[m_current_get_index].pai_id;
	CardValue catch_value = m_all_pai[m_current_get_index].pai_value;
	m_current_get_index++;

	player_data.hand_card_id[catch_id] = true;
	(player_data.hand_pai[catch_value])++;
	return true;
}

bool twomajongGameLogic::CheckExchangeHua(OutCardsReq &msg, struct PlayerData &player_data)
{
	CardValue tmp_value;
	for (auto it = msg.out_cards().begin(); it != msg.out_cards().end(); it++)
	{
		tmp_value = static_cast<CardValue>(PaiKind::GetValueFromRealCard(*it));
		if (tmp_value != CardValue::value_flower)
		{
			return false;	//如果不是花牌返回错误
		}
	}

	return true;
}

bool twomajongGameLogic::CheckOutCard(OutCardsReq &msg, struct PlayerData &player_data)
{
	//验证牌是否存在已经处理过了，暂时不要验证其他
	return true;
}

bool twomajongGameLogic::IsPaiExist(string sub_pai, bool hand_card_id[73])
{
	for (int i = 0; i < sub_pai.size(); i++)
	{
		int index = sub_pai.c_str()[i];
		if (false == hand_card_id[index])
		{
			//如果有手牌里不存在sub_pai返回
			return false;
		}
	}

	return true;
}

void twomajongGameLogic::GetNewOutCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data)
{
	string show_card;	//所有玩家都看得到的展示牌
	int count = msg.out_cards().size() + 1;	//出牌数加上得到的一个牌
	show_card.assign(msg.out_cards());
	show_card.append(msg.got_cards());

	//从手牌中把用于吃碰杠的牌给去掉，处理服务端自身数据
	RemoveFromHandPai(msg.out_cards(), player_data.seat_id);

	//吃碰杠都会产生新的固定组数据
	if (msg.player_action() == Action::CHI || msg.player_action() == Action::PENG || msg.player_action() == Action::GANG)
	{
		FixedCard fixed;
		fixed.type = static_cast<FixedType>(msg.player_action());
		fixed.card_group[0] = PaiKind::GetValueFromRealCard(msg.got_cards()[0]);
		for (int i = 1; i <= msg.out_cards().size(); i++)
		{
			fixed.card_group[i] = PaiKind::GetValueFromRealCard(msg.out_cards()[i - 1]);
		}
		player_data.fixed_card.push_back(fixed);
	}


	TurnToPlayer turn;
	turn.set_u8seatid(player_data.seat_id);	//座位号不变
	turn.set_u32gameticket(time(nullptr));
	turn.set_u32lastmicroticket(m_out_time - (time(nullptr) - m_begin_time));
	//赋值 u8seatid player_action在函数外赋值，cards如果有在SupplyHandCard函数里赋值
	rsp_msg.mutable_turn()->CopyFrom(turn);
	rsp_msg.set_show_cards(show_card);
	rsp_msg.set_show_count(count);

}


void twomajongGameLogic::SupplyHandCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data)
{
	if (msg.player_action() == bs::twomajong::Action::EXCHANGE_HUA)
	{
		//补花有多少张补多少张
		char buff[100] = "";
		//补花阶段不对out_card的size进行判断
		for (int i = 0; i < msg.out_cards().size(); i++)
		{
			//花牌不放入hand_pai统计中
			//抓牌
			CardId supply_id = m_all_pai[m_current_get_index].pai_id;
			CardValue supply_value = m_all_pai[m_current_get_index].pai_value;
			m_current_get_index++;

			player_data.hand_card_id[supply_id] = true;
			if (supply_value > 0 && supply_value < 17)
			{
				(player_data.hand_pai[supply_value])++;
			}
			buff[i] = static_cast<char>(supply_id);
		}
		player_data.remain_hidden_count++;

		TurnToPlayer turn;
		turn.set_u8seatid(player_data.seat_id);	//座位号不变
		turn.set_u32gameticket(time(0));
		turn.set_u32lastmicroticket(m_timeout - (time(0) - m_begin));
		//赋值 u8seatid player_action在函数外赋值，cards如果有在SupplyHandCard函数里赋值
		rsp_msg.mutable_turn()->CopyFrom(turn);
		rsp_msg.set_cards(buff, msg.out_cards().size());
	}
	else
	{
		char buff[100] = "";
		//杠和抓牌只能补一张
		CardId supply_id = m_all_pai[m_current_get_index].pai_id;
		CardValue supply_value = m_all_pai[m_current_get_index].pai_value;
		m_current_get_index++;

		player_data.hand_card_id[supply_id] = true;
		if (supply_value > 0 && supply_value < 17)
		{
			(player_data.hand_pai[supply_value])++;
		}
		player_data.remain_hidden_count++;
		buff[0] = static_cast<char>(supply_id);

		TurnToPlayer turn;
		turn.set_u8seatid(player_data.seat_id);	//座位号不变
		turn.set_u32gameticket(time(0));
		turn.set_u32lastmicroticket(m_timeout - (time(0) - m_begin));
		//赋值 u8seatid player_action在函数外赋值，cards如果有在SupplyHandCard函数里赋值
		rsp_msg.mutable_turn()->CopyFrom(turn);
		rsp_msg.set_cards(buff, 1);
	}
}


void twomajongGameLogic::RemoveFromHandPai(string sub_pai, int seat_id)
{
	CardId tmp_id;
	CardValue tmp_value;
	for (auto it = sub_pai.begin(); it != sub_pai.end(); it++)
	{
		tmp_id = static_cast<CardId>(*it);
		tmp_value = PaiKind::GetValueFromRealCard(*it);
		m_players[seat_id].hand_card_id[tmp_id] = false;	//id置为false
		if (tmp_value > 0 && tmp_value < 17)
		{
			(m_players[seat_id].hand_pai[tmp_value])--;	//value - 1
		}
		m_players[seat_id].remain_hidden_count--;
	}
}

void twomajongGameLogic::DropHandCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data)
{
	//msg.out_cards().size();
	//从手牌中移除出掉的牌
	RemoveFromHandPai(msg.out_cards(), player_data.seat_id);
	m_new_outcard.pai_id = static_cast<CardId>(msg.out_cards()[0]);
	m_new_outcard.pai_value = PaiKind::GetValueFromRealCard(msg.out_cards()[0]);

	TurnToPlayer turn;
	uint32_t next_seat_id = next_player(player_data.seat_id);
	turn.set_u8seatid(next_seat_id);	//座位号换为下一个玩家
	turn.set_u32gameticket(time(0));
	turn.set_u32lastmicroticket(m_out_time - (time(0) - m_begin_time));
	rsp_msg.mutable_turn()->CopyFrom(turn);
	rsp_msg.set_u8count(msg.out_cards().size());
	rsp_msg.set_cards(msg.out_cards());

}

void twomajongGameLogic::SetTimeOutAuto(int seat_id)
{
	//发送托管和出牌两个报文
	//发送自动托管
	m_new_outcard = m_all_pai[m_current_get_index];
	
	//讲当天用户设为托管，然后发送托管信息
	m_players[seat_id].auto_type = AutoType::emPassiveAuto;
	CMDTwomajong_SetAuto rsp1;
	auto &rsp1_msg = rsp1.my_message_;
	rsp1_msg.set_u8seatid(seat_id);
	rsp1_msg.set_is_auto(1);
	rsp1_msg.set_auto_type(AutoType::emPassiveAuto);
	SendToAllPlayerInTable(IDGameSetAuto, &rsp1);
	//超时换人

	int next_seat_id = next_player(seat_id);

	CMDTwomajong_OutCardsReply rsp;
	auto &rsp_msg = rsp.my_message_;
	rsp_msg.set_u8seatid(seat_id);
	TurnToPlayer turn;
	turn.set_u8seatid(next_seat_id);
	turn.set_u32gameticket(time(nullptr));
	turn.set_u32lastmicroticket(m_out_time - (time(nullptr) - m_begin_time));
	rsp_msg.mutable_turn()->CopyFrom(turn);
	//发送给所有玩家
	SendToAllPlayerInTable(IDGameTurnToPlayer, &rsp);
}
