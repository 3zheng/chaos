

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
//��ʼ��
void twomajongGameLogic::init()
{
	m_players.clear();

	//Ԥ�ȷ������ݣ���Ϊm_players������λ��Ϊ�±꣬����λ�����Ǵ�1��ʼ�ģ�����ҪMAX_USERS+1,[0]�����ǿյ�
	m_players.resize(MAX_USERS + 1);
}

void twomajongGameLogic::OnPulse(uint64_t nMS)
{
	time_t now_time = time(nullptr);
	time_t diff_time = now_time - m_begin_time;	//ʱ���

	switch (m_state_step)	//��Ϸ�׶�
	{
	case FAPAI:
		if (diff_time > m_out_time)	//���ƽ��������¸��׶�
		{
			m_state_step = GameState::CHUPAI;
			CMDTwomajong_TurnToPlayer rsp;
			TurnToPlayer &turn = rsp.my_message_;
			m_current_seatid = m_pFrame->GetRand() % 2 + 1;	//�ӵ�һ����ʼ
			turn.set_u8seatid(m_current_seatid);	//��λ�Ų���
			turn.set_u32gameticket(time(nullptr));
			turn.set_u32lastmicroticket(m_out_time - (time(nullptr) - m_begin_time));
			//���͸��������
			SendToAllPlayerInTable(IDGameTurnToPlayer, &rsp);

			m_begin_time = now_time;	//���迪ʼʱ��
		}
		break;
	case CHUPAI:
		if (diff_time > m_out_time)
		{
			//��ʱ�ѵ�ǰ�����Ϊ�й�
			
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
   //��ֵseat_id��user_id��m_players
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

	  if (game_cmd->cmd_subid_ == IDGameSetAuto)			//��������й�
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
            /////////����Ƿ��ǻ��������FIXME
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

/////////////////////////////////////////////////////ddz��Ϸ�߼�����
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
	//�Ȱ��Ʒ���һ��������
	m_all_pai.clear();
	struct MajongPai data;
	for (int i = 1; i <= 72; i++)
	{
		data.pai_id = (enum CardId)i;
		data.pai_value = PaiKind::GetValueFromRealCard(i);
		m_all_pai.push_back(data);
	}

	//ϴ�ƣ�ԭ���Ǳ���all_pai��ÿ��Ԫ�أ����ѡȡһ��λ�õ�ֵ�͵�ǰ��������λ�õ�Ԫ��ֵ����
	//srand((unsigned int)time(nullptr));
	for (auto it = m_all_pai.begin(); it != m_all_pai.end(); it++)
	{
		int change_index = m_pFrame->GetRand() % 72;
		struct MajongPai tmp_value = m_all_pai[change_index];
		m_all_pai[change_index] = *it;
		*it = tmp_value;
	}
	
   //BSLOG_DEBUG ( ( "��Ϸ�߼�" ), "��Ϸ��ʼʱ����:" << cardStr4Log );
}

void twomajongGameLogic::FaPai()
{
	//����
	CMDTwomajong_DealCards deal_cards;
	auto &msg = deal_cards.my_message_;
	char hand_pai1[26] = "";	//��λ1������,���ķ�����,��card_id
	char hand_pai2[26] = "";	//��λ2������,���ķ�����,��card_id
	uint32_t hand_value_pai1[17] = { 0 };	//���ڳ������������߼��ж�,��card_value
	uint32_t hand_value_pai2[17] = { 0 };	//���ڳ������������߼��ж�,��card_value

	for (int i = 0; i < 26; i++)
	{
		if (i < 13)
		{
			hand_pai1[i] = (char)m_all_pai[i].pai_id;
			hand_pai2[i] = '\0';
			int value_index = m_all_pai[i].pai_value;
			if (value_index > 0 && value_index < 17)	//���������߼��жϷ�Χ
			{
				hand_value_pai1[value_index]++;
			}
		}
		else
		{
			hand_pai1[i] = '\0';
			hand_pai2[i] = (char)m_all_pai[i].pai_id;
			int value_index = m_all_pai[i].pai_value;
			if (value_index > 0 && value_index < 17)	//���������߼��жϷ�Χ
			{
				hand_value_pai2[value_index]++;
			}
		}
		
	}
	m_current_get_index = 26;	//��ǰ���Ƶ�λ����Ϊ26

	//���Ʒ�����Ӧ�û�
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		//��m_players[0]�ǿյ�
		if (0 == it->seat_id)
		{
			continue;
		}

		msg.set_u8seatid(it->seat_id);
		if (it->seat_id == 0)
		{
			msg.set_cards(hand_pai1, 26);
			for (int i = 0; i < 17; i++)	//����Ӧ��ҵ����Ƹ�ֵ
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
		
		//���͸��û�
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

	//��ȡseat_id
	int seat_id = GetPlayerSeatID(req->address_.gate_user_id);
	if (m_current_seatid != seat_id)
	{
		BSLOG_DEBUG(("��Ϸ�߼�"), "û���ֵ�seat_id =" << seat_id << "����ҳ���,��ǰ������Ƶ��û���λ" << m_current_seatid);
		return;
	}
		
	bool ret = false;
	PlayerData &player_data = m_players[seat_id];

	//У���Ƿ��ж�Ӧ������
	if (IsPaiExist(msg.out_cards(), player_data.hand_card_id) == false)
	{
		return;
	}

	//У��׶�
	switch (msg.player_action())
	{
	case Action::CHI:	//��
		ret = CheckChi(msg, player_data);
		break;
	case Action::PENG:	//��
		ret = CheckPeng(msg, player_data);
		break;
	case Action::GANG:	//��
		ret = CheckGang(msg, player_data);
		break;
	case Action::TING:	//��
		ret = CheckTing(msg, player_data);
		break;
	case Action::HU:	//��
		ret = CheckHu(msg, player_data);
		break;
	case Action::GETCARD:	//ץ��
		ret = CheckGetCard(msg, player_data);
		break;
	case Action::EXCHANGE_HUA:	//����
		ret = CheckExchangeHua(msg, player_data);
		break;
	case Action::OUTCARD:	//��������
		ret = CheckOutCard(msg, player_data);
		break;
	default:
		break;
	}

	//��ֵ�ͼ�¼�׶�
	CMDTwomajong_OutCardsReply rsp;
	OutCardsReply &rsp_msg = rsp.my_message_;
	rsp_msg.set_u8seatid(seat_id);
	rsp_msg.set_player_action(msg.player_action());
	//У��ͨ��������ƽ��м�¼
	switch (msg.player_action())
	{
	case Action::CHI:	//��		
	case Action::PENG:	//��		
		GetNewOutCard(msg, rsp_msg, player_data);	//ֻ�õ���ǰ������
		break;
	case Action::GANG:	//��
		//�õ���ǰ�����ƣ����Ҵ��ƺ���ץһ���Ʋ�������
		GetNewOutCard(msg, rsp_msg, player_data);	
		SupplyHandCard(msg, rsp_msg, player_data);
		break;
	case Action::TING:	//��
		
	case Action::HU:	//��
		
		break;
	case Action::GETCARD:	//ץ��
		SupplyHandCard(msg, rsp_msg, player_data);
		break;
	case Action::EXCHANGE_HUA:	//����
		RemoveFromHandPai(msg.out_cards(), seat_id);
		SupplyHandCard(msg, rsp_msg, player_data);
		break;
	case Action::OUTCARD:	//��������
		DropHandCard(msg, rsp_msg, player_data);
		break;
	default:
		break;
	}

	//���ͱ��Ľ׶�
	switch (msg.player_action())
	{
	case Action::CHI:	//��		
	case Action::PENG:	//��		
	case Action::GANG:	//��
	case Action::TING:	//��
	case Action::HU:	//��
	case Action::OUTCARD:	//��������
		//������ҷ�����ͬ�ı���
		SendToAllPlayerInTable(IDGameOutCardsReply, &rsp);
		break;
	case Action::GETCARD:	//ץ��
	case Action::EXCHANGE_HUA:	//����
		//��������ҷ��������ı���
		SendToOnePlayerBySeatid(IDGameOutCardsReply, &rsp, seat_id);
		//��Լҷ��Ͳ���cards���ݵı���
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
	if (msg.got_cards().size() != 1 || msg.out_cards().size() != 2)	//У������
	{
		return false;
	}
	if (m_new_outcard.pai_id != msg.got_cards().c_str()[0])	//У��Ե���ֵ
	{
		return false;
	}

	//���У���Ƿ���Գ�
	enum CardValue tmp_value;
	tmp_value = PaiKind::GetValueFromRealCard(msg.got_cards().c_str()[0]);
	check_data.push_back(tmp_value);
	tmp_value = PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[0]);
	check_data.push_back(tmp_value);
	tmp_value = PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[1]);
	check_data.push_back(tmp_value);
	//����
	std::sort(check_data.begin(), check_data.end());
	//card_value�ķ�Χ������value_bamboo_1��value_bamboo_9֮��
	if (check_data[0] < CardValue::value_bamboo_1 || check_data[2] > CardValue::value_east_wind)
	{
		return false;
	}
	//�ԵĶ�����[0][1][2]����1
	if (check_data[1] - check_data[0] != 1 || check_data[2] - check_data[1] != 1)
	{
		return false;
	}


	return true;
}

bool twomajongGameLogic::CheckPeng(OutCardsReq &msg, struct PlayerData &player_data)
{
	vector<enum CardValue> check_data;
	if (msg.got_cards().size() != 1 || msg.out_cards().size() != 2)	//У������
	{
		return false;
	}
	if (m_new_outcard.pai_id != msg.got_cards().c_str()[0])	//У��������ֵ
	{
		return false;
	}

	//���У���Ƿ������
	enum CardValue tmp_value;
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.got_cards().c_str()[0]));
	check_data.push_back(tmp_value);
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[0]));
	check_data.push_back(tmp_value);
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[1]));
	check_data.push_back(tmp_value);
	//ֻ�г���Ҫ����
	//���Ķ�����[0][1][2]����ͬ
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
	if (msg.got_cards().size() != 1 || msg.out_cards().size() != 3)	//У������
	{
		return false;
	}
	if (m_new_outcard.pai_id != msg.got_cards().c_str()[0])	//У��ܵ���ֵ
	{
		return false;
	}

	//���У���Ƿ���Ը�
	enum CardValue tmp_value;
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.got_cards().c_str()[0]));
	check_data.push_back(tmp_value);
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[0]));
	check_data.push_back(tmp_value);
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[1]));
	check_data.push_back(tmp_value);
	tmp_value = static_cast<enum CardValue>(PaiKind::GetValueFromRealCard(msg.out_cards().c_str()[2]));
	check_data.push_back(tmp_value);

	//�ܵĶ�����[0][1][2][3]����ͬ
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
	if (msg.out_cards().size() != 1)	//У������
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
	//�ı���Ӧ�������
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
			return false;	//������ǻ��Ʒ��ش���
		}
	}

	return true;
}

bool twomajongGameLogic::CheckOutCard(OutCardsReq &msg, struct PlayerData &player_data)
{
	//��֤���Ƿ�����Ѿ�������ˣ���ʱ��Ҫ��֤����
	return true;
}

bool twomajongGameLogic::IsPaiExist(string sub_pai, bool hand_card_id[73])
{
	for (int i = 0; i < sub_pai.size(); i++)
	{
		int index = sub_pai.c_str()[i];
		if (false == hand_card_id[index])
		{
			//����������ﲻ����sub_pai����
			return false;
		}
	}

	return true;
}

void twomajongGameLogic::GetNewOutCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data)
{
	string show_card;	//������Ҷ����õ���չʾ��
	int count = msg.out_cards().size() + 1;	//���������ϵõ���һ����
	show_card.assign(msg.out_cards());
	show_card.append(msg.got_cards());

	//�������а����ڳ����ܵ��Ƹ�ȥ��������������������
	RemoveFromHandPai(msg.out_cards(), player_data.seat_id);

	//�����ܶ�������µĹ̶�������
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
	turn.set_u8seatid(player_data.seat_id);	//��λ�Ų���
	turn.set_u32gameticket(time(nullptr));
	turn.set_u32lastmicroticket(m_out_time - (time(nullptr) - m_begin_time));
	//��ֵ u8seatid player_action�ں����⸳ֵ��cards�������SupplyHandCard�����︳ֵ
	rsp_msg.mutable_turn()->CopyFrom(turn);
	rsp_msg.set_show_cards(show_card);
	rsp_msg.set_show_count(count);

}


void twomajongGameLogic::SupplyHandCard(OutCardsReq &msg, OutCardsReply &rsp_msg, struct PlayerData &player_data)
{
	if (msg.player_action() == bs::twomajong::Action::EXCHANGE_HUA)
	{
		//�����ж����Ų�������
		char buff[100] = "";
		//�����׶β���out_card��size�����ж�
		for (int i = 0; i < msg.out_cards().size(); i++)
		{
			//���Ʋ�����hand_paiͳ����
			//ץ��
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
		turn.set_u8seatid(player_data.seat_id);	//��λ�Ų���
		turn.set_u32gameticket(time(0));
		turn.set_u32lastmicroticket(m_timeout - (time(0) - m_begin));
		//��ֵ u8seatid player_action�ں����⸳ֵ��cards�������SupplyHandCard�����︳ֵ
		rsp_msg.mutable_turn()->CopyFrom(turn);
		rsp_msg.set_cards(buff, msg.out_cards().size());
	}
	else
	{
		char buff[100] = "";
		//�ܺ�ץ��ֻ�ܲ�һ��
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
		turn.set_u8seatid(player_data.seat_id);	//��λ�Ų���
		turn.set_u32gameticket(time(0));
		turn.set_u32lastmicroticket(m_timeout - (time(0) - m_begin));
		//��ֵ u8seatid player_action�ں����⸳ֵ��cards�������SupplyHandCard�����︳ֵ
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
		m_players[seat_id].hand_card_id[tmp_id] = false;	//id��Ϊfalse
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
	//���������Ƴ���������
	RemoveFromHandPai(msg.out_cards(), player_data.seat_id);
	m_new_outcard.pai_id = static_cast<CardId>(msg.out_cards()[0]);
	m_new_outcard.pai_value = PaiKind::GetValueFromRealCard(msg.out_cards()[0]);

	TurnToPlayer turn;
	uint32_t next_seat_id = next_player(player_data.seat_id);
	turn.set_u8seatid(next_seat_id);	//��λ�Ż�Ϊ��һ�����
	turn.set_u32gameticket(time(0));
	turn.set_u32lastmicroticket(m_out_time - (time(0) - m_begin_time));
	rsp_msg.mutable_turn()->CopyFrom(turn);
	rsp_msg.set_u8count(msg.out_cards().size());
	rsp_msg.set_cards(msg.out_cards());

}

void twomajongGameLogic::SetTimeOutAuto(int seat_id)
{
	//�����йܺͳ�����������
	//�����Զ��й�
	m_new_outcard = m_all_pai[m_current_get_index];
	
	//�������û���Ϊ�йܣ�Ȼ�����й���Ϣ
	m_players[seat_id].auto_type = AutoType::emPassiveAuto;
	CMDTwomajong_SetAuto rsp1;
	auto &rsp1_msg = rsp1.my_message_;
	rsp1_msg.set_u8seatid(seat_id);
	rsp1_msg.set_is_auto(1);
	rsp1_msg.set_auto_type(AutoType::emPassiveAuto);
	SendToAllPlayerInTable(IDGameSetAuto, &rsp1);
	//��ʱ����

	int next_seat_id = next_player(seat_id);

	CMDTwomajong_OutCardsReply rsp;
	auto &rsp_msg = rsp.my_message_;
	rsp_msg.set_u8seatid(seat_id);
	TurnToPlayer turn;
	turn.set_u8seatid(next_seat_id);
	turn.set_u32gameticket(time(nullptr));
	turn.set_u32lastmicroticket(m_out_time - (time(nullptr) - m_begin_time));
	rsp_msg.mutable_turn()->CopyFrom(turn);
	//���͸��������
	SendToAllPlayerInTable(IDGameTurnToPlayer, &rsp);
}
