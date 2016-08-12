//#include "StdAfx.h"
#include "game_majong.h"

#include <assert.h>
#include "time.h"
#include <windows.h>
//#include "command\comd_configdefine.h"
__declspec(dllexport)
	IGameTableSink *		CreateGameSink()
{
	return new game_majong2();
}

game_majong2::game_majong2(void)
{
	init();
}

game_majong2::~game_majong2(void)
{
}

const PlayerRoundFeature * game_majong2::GetLastRoundFeature( int nSeatIndex )
{

	return & m_arrRoundFeatures[nSeatIndex-1];
}

//��ʼ��
void game_majong2::init()
{
	m_players.clear();
	
	m_state = mj_s_preparing;
	m_timeout = out_timeout;

	m_money_rate = 1;
	m_score_rate = 1;

	m_nLastPulseMS = 0;

	m_last_pai = id_unknown;

	for(int i=0;i<=MAX_PLAYER_PER_GAME;++i)
	{
		PlayerRoundFeature rf;
		memset(&rf,0,sizeof(rf));
		m_arrRoundFeatures.push_back(rf);
	}
	m_wstr_last_recordinfo.clear();
//	m_check_hu = id_unknown;
//	LoadChewTable();
}

//////////////////////////////////////////////////////�ӿ�ʵ��
void game_majong2::StartRound ( int nTableId, bool newTurn, IMatchTableFrame*pFrame, int nPlayerCount/*=0*/, const char *pAttRule/*=0*/ )
{
	m_nCurrentTableId = nTableId;
	m_pFrame = pFrame;
	m_attRules = pAttRule ? pAttRule : "";
	//////////////////////////////////////////////////////////////////////////
	if(m_wstr_last_recordinfo.empty())
		m_wstr_last_recordinfo.clear();

	m_wstr_last_recordinfo = L"\n\t\"actions\":\n\t[";
	m_begin = 0;
	on_game_begin(newTurn);
}

void game_majong2::OnPulse ( int nMS )
{
	// ��¼�ϴ�OnPulse��ʱ��
	m_nLastPulseMS = nMS;
	uint64_t nDiff = nMS - m_begin;
	if (m_players.size() == 0)
	{
		m_begin = m_nLastPulseMS;//��Ϸδ����������ң�����һֱreturn
		return;
	}
	if (m_state == mj_begin_and_shaizi)//���Ӷ���2�룬���ƶ���3�룬Ⱥȥ������3��
	{
		if (nDiff < 8000)
		{
			return;
		}
		else
		{
			//���λ���������
			IMsgWriter *w = CreateMsgWriter();
			pro_add_flower_count add_flower_count;
			add_flower_count.seat_id = 1;
			add_flower_count.total_flowers = ((char)(m_players[0].m_pais_flowers.size()));
			add_flower_count.ToWriter(w);
			for(int i = 1; i <= MAX_PLAYER_PER_GAME;i++)
			{
				m_pFrame->SendDataToPlayer ( w, i );
			}

			add_flower_count.seat_id = 2;
			add_flower_count.total_flowers = (char)(m_players[1].m_pais_flowers.size());
			add_flower_count.ToWriter(w);
			for(int i = 1; i <= MAX_PLAYER_PER_GAME;i++)
			{
				m_pFrame->SendDataToPlayer ( w, i );
			}
			w->Release();
			//
			m_begin = m_nLastPulseMS;
			m_state = mj_s_out;
			m_current_player = m_banker;//���赱ǰ���Ϊׯ��
			m_players[m_current_player-1].SetMyZiMoStatus();
			SendACardNormal();
			ZiMoSendBtn();
			ChangeTurnNotify();
		}
	}
	else if(m_state == mj_s_out)
	{
		if(nDiff > 2000 && (m_players[m_current_player-1].is_auto || m_players[m_current_player-1].is_ting))
		{
			do_auto();
			m_begin = m_nLastPulseMS;
		}
		else if ( nDiff > 1000 * m_timeout )
		{

			m_players[m_current_player-1].is_auto = true;//�����Զ�

			IMsgWriter *ww = CreateMsgWriter();
			pro_ting_notify_s pro_tuo_notify;
			pro_tuo_notify.seat_id = m_current_player;
			pro_tuo_notify.kind = 1;
			pro_tuo_notify.ToWriter(ww);
			for (uint32_t i = 1; i <= 2; i++)
			{
				m_pFrame->SendDataToPlayer(ww,i);
			}
			ww->Release();
			m_pFrame->PlayerIsTimeOut(m_current_player);		//֪ͨ�����ҳ�ʱ

			do_auto();
			m_begin = m_nLastPulseMS;
		}
	}
}
void game_majong2::OnPlayerMsg(int nSeatIndex,IMsgReader * rr )
{
	if(MKD_DDZ != rr->MessageKind())
		return;
	if (PRO_CLICK_CHEW_AND_SO_ON_BTN == rr->MessageId())
	{
		pro_click_btn_c pro;
		if ( !pro.FromReader(rr))
			return;
		m_log_str.Format("���Կͻ��˵ĵ�OnClickBtn");
		if (!m_game_is_over)
		{
			OnClickBtn(pro);
		}
		m_begin = m_nLastPulseMS;
	}
	if (PRO_GAME_DATA_REQ == rr->MessageId())
	{
		pro_game_data_req pro;
		if (!pro.FromReader(rr))
			return;
		on_pro_game_data_req(nSeatIndex);
		if (nSeatIndex == m_current_player && m_players[m_current_player-1].m_current_status == 2)
		{
			ProcessFangQiReq(0);
		}
		else if (nSeatIndex == m_current_player && m_players[m_current_player-1].m_current_status == 1)
		{
			ZiMoSendBtn();
		}
	}
	if (PRO_EXPRESSION == rr->MessageId())
	{
		pro_expression pro;
		if (!pro.FromReader(rr))
			return;
		on_pro_expresssion(nSeatIndex, pro);
	}
}
void game_majong2::OnPlayerBack ( int SeatID )
{
	on_pro_game_data_req(SeatID);
	if (SeatID == m_current_player && m_players[m_current_player-1].m_current_status == 2)
	{
		ProcessFangQiReq(0);
	}
	else if (SeatID == m_current_player && m_players[m_current_player-1].m_current_status == 1)
	{
		ZiMoSendBtn();
	}
}
void game_majong2::OnPlayerOtherAction(int nSeatIndex,int nActType)
{

}
void game_majong2::GetLookonData(int nSeatIndex,int nLookonFlags,int & msgCount, IMsgWriter * & pOut)
{

}
void game_majong2::Destroy()
{
	delete this;
}

void game_majong2::OnNewLookon(int nSeatIndex,uint64_t nlooked_connid,int nLookonFlags)
{

}
const wchar_t * game_majong2::GetLastRecordInfo()
{
	return m_wstr_last_recordinfo.c_str();
}
wstring	game_majong2::GetCardStr(int cid)
{
	if (cid < bamboo_1A || cid > flower_chrysanthemum)
		return L"������ֵ";
	switch(cid)
	{
	case bamboo_1A:
	case bamboo_1B:
	case bamboo_1C:
	case bamboo_1D:
		return L"һ��";
	case bamboo_2A:
	case bamboo_2B:
	case bamboo_2C:
	case bamboo_2D:
		return L"����";
	case bamboo_3A:
	case bamboo_3B:
	case bamboo_3C:
	case bamboo_3D:
		return L"����";
	case bamboo_4A:
	case bamboo_4B:
	case bamboo_4C:
	case bamboo_4D:
		return L"����";
	case bamboo_5A:
	case bamboo_5B:
	case bamboo_5C:
	case bamboo_5D:
		return L"����";
	case bamboo_6A:
	case bamboo_6B:
	case bamboo_6C:
	case bamboo_6D:
		return L"����";
	case bamboo_7A:
	case bamboo_7B:
	case bamboo_7C:
	case bamboo_7D:
		return L"����";
	case bamboo_8A:
	case bamboo_8B:
	case bamboo_8C:
	case bamboo_8D:
		return L"����";
	case bamboo_9A:
	case bamboo_9B:
	case bamboo_9C:
	case bamboo_9D:
		return L"����";
	case east_wind_A:
	case east_wind_B:
	case east_wind_C:
	case east_wind_D:
		return L"����";
	case south_wind_A:
	case south_wind_B:
	case south_wind_C:
	case south_wind_D:
		return L"�Ϸ�";
	case west_wind_A:
	case west_wind_B:
	case west_wind_C:
	case west_wind_D:
		return L"����";
	case north_wind_A:
	case north_wind_B:
	case north_wind_C:
	case north_wind_D:
		return L"����";
	case red_dragon_A:
	case red_dragon_B:
	case red_dragon_C:
	case red_dragon_D:
		return L"����";
	case green_dragon_A:
	case green_dragon_B:
	case green_dragon_C:
	case green_dragon_D:
		return L"����";
	case white_dragon_A:
	case white_dragon_B:
	case white_dragon_C:
	case white_dragon_D:
		return L"�װ�";
	case flower_spring:
	case flower_summer:
	case flower_autumn:
	case flower_winter:
	case flower_plum:
	case flower_orchid:
	case flower_bamboo:
	case flower_chrysanthemum:
		return L"��";
	}
	return L"";
}
//////////////////////////////////////////////////////�ӿ�ʵ��

void game_majong2::do_auto()
{
	if (m_game_is_over)
	{
		return;
	}
	if (m_players[m_current_player-1].is_ting)
	{
		if (m_players[m_current_player-1].m_check_hu[0] != id_unknown)
		{
			m_players[m_current_player-1].m_hu_clock_when_is_ting++;
			if (m_players[m_current_player-1].m_hu_clock_when_is_ting >= 5)
			{
				ProcessHuReq(m_players[m_current_player-1].m_current_status);
				m_players[m_current_player-1].m_hu_clock_when_is_ting = 0;
			}
		}
		else
		{
			ProcessOutCardReq(m_players[m_current_player-1].m_last_pai);
		}
	}
	else
	{
		pro_click_btn_c req;
		req.seat_id = m_current_player;
		////////////////////////////////һ���йܻ�����//////////////////////////////////////////
		//if (m_players[m_current_player-1].m_check_hu[0] != id_unknown)
		//{
		//	//�����ȼ����
		//	ProcessHuReq(m_players[m_current_player-1].m_current_status);
		//}
		//else if (m_players[m_current_player-1].m_vec_check_ming_gang1.size() > 0)
		//{
		//	//���Ϊ��1
		//	ProcessMingGang1Req(0);
		//	m_players[m_current_player-1].ClearAllJudge();
		//}
		//else if(m_players[m_current_player-1].m_vec_check_ming_gang2.size() > 0)
		//{
		//	//�����Ϊ��2
		//	ProcessMingGang2Req(0);
		//	m_players[m_current_player-1].ClearAllJudge();
		//}
		//else if(m_players[m_current_player-1].m_vec_check_an_gang.size() > 0)
		//{
		//	//�����Ϊ����
		//	ProcessGangReq(0);
		//	m_players[m_current_player-1].ClearAllJudge();
		//}
		//else if(m_players[m_current_player-1].m_vec_check_peng.size() > 0)
		//{
		//	//�����Ϊ��
		//	ProcessPengReq(0);
		//	m_players[m_current_player-1].ClearAllJudge();
		//}
		//else if(m_players[m_current_player-1].m_vec_check_chew.size() > 0)
		//{
		//	//���Ϊ��
		//	ProcessChiReq(0);
		//	m_players[m_current_player-1].ClearAllJudge();
		//}
		//else if (m_players[m_current_player-1].m_current_status == 1)
		//{
		//	//�������
		//	uint32_t pai_count[16] = {0};
		//	for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_in_hand.size(); i++)
		//	{
		//		pai_count[m_players[m_current_player-1].m_pais_in_hand[i].u32ValueCard-1]++;
		//	}
		//	//���������е����ȳ�
		//	for (uint32_t i = 9; i < 16;i++)
		//	{
		//		if (pai_count[i] == 1)
		//		{
		//			for (uint32_t j = 0; j < m_players[m_current_player-1].m_pais_in_hand.size();j++)
		//			{
		//				if (i == m_players[m_current_player-1].m_pais_in_hand[j].u32ValueCard-1)
		//				{
		//					ProcessOutCardReq( m_players[m_current_player-1].m_pais_in_hand[j].u32RealCard);
		//					return;
		//				}
		//			}
		//			return;
		//		}
		//	}
		//	//��1����9���ɵ͵��ߣ���ֻ�е��ŵ�
		//	for (uint32_t i = 0; i < 9;i++)
		//	{
		//		if (pai_count[i] == 1)
		//		{
		//			for (uint32_t j = 0; j < m_players[m_current_player-1].m_pais_in_hand.size();j++)
		//			{
		//				if (i == m_players[m_current_player-1].m_pais_in_hand[j].u32ValueCard-1)
		//				{
		//					ProcessOutCardReq( m_players[m_current_player-1].m_pais_in_hand[j].u32RealCard);
		//					return;
		//				}
		//			}
		//			return;
		//		}
		//	}
			//Ĭ��
			if (m_players[m_current_player-1].m_pais_in_hand.size() <= 0)
			{
				//�յ����ǲ������������С�ڵ���0�����
				m_log_str.Format("m_players[%d].m_pais_in_hand.size()=%d ",m_current_player-1,m_players[m_current_player-1].m_pais_in_hand.size());WriteLog(m_log_str);
				return;
			}
			if (m_players[m_current_player-1].m_current_status == 1)
			{
				ProcessOutCardReq( m_players[m_current_player-1].m_pais_in_hand[0].u32RealCard);
			}
			else if (m_players[m_current_player-1].m_current_status == 2)
			{
				ProcessFangQiReq(0);
			}
		//}
		////////////////////////////////////////////////////////////////////////////////////////
		/*if (m_players[m_current_player-1].m_vec_check_chew.size() > 0 ||
			m_players[m_current_player-1].m_vec_check_peng.size() > 0 ||
			m_players[m_current_player-1].m_vec_check_an_gang.size() > 0 ||
			m_players[m_current_player-1].m_vec_check_ming_gang1.size() > 0 ||
			m_players[m_current_player-1].m_vec_check_ming_gang2.size() > 0)
		{
			req.kind = btn_id_fangqi;
			if (m_players[m_current_player-1].m_current_status == 1)
			{
				req.index = 0;
			}
			else if (m_players[m_current_player-1].m_current_status == 2)
			{
				req.index = 1;
			}
			OnClickBtn(req);
		}
		if (m_players[m_current_player-1].m_current_status == 1)
		{
			req.kind = btn_id_normal;
			req.index = m_players[m_current_player-1].m_last_pai;
			OnClickBtn(req);
		}*/	
	}
}

void game_majong2::on_game_begin(bool newTurn)	// һ����Ϸ��ʼ
{
	m_log_str.Format(" ��Ϸ��ʼ-------------------------------------");//WriteLog(m_log_str);

	for(int i=0;i<=MAX_PLAYER_PER_GAME;++i)
	{
		PlayerRoundFeature *rf =&m_arrRoundFeatures[i];
		memset(rf,0,sizeof(PlayerRoundFeature));
	}

	m_state = mj_begin_and_shaizi;
	m_all_pais.clear();													//�������ÿ�
	m_game_is_over = false;												//һ����Ϸ��������÷�
	for (uint32_t i = 0; i < 4; i++)									//����δץ���Ʊ����0
	{
		m_order_recorder[i]=0;
	}

	m_timeout = out_timeout;											//��ʱ��ֵ
	
	//m_banker = 1;					
	m_banker = 1 + m_pFrame->GetRand() % MAX_PLAYER_PER_GAME;			//�����ȡ����
	m_current_player = m_banker;
	m_players.clear();													//�������б�
	player player_;
	player_.on_new_game();												//�����������
	m_players.push_back(player_);										//����������
	m_players.push_back(player_);
	m_players[0].m_oppisite_player = &m_players[1];
	m_players[1].m_oppisite_player = &m_players[0];
	m_money_rate = 1;													//��ұ�������
	m_score_rate = 1;													//������������
	
	pro_game_begin_s	pro;
	pro.money_rate = m_money_rate;										//���ͽ�Һͷ���
	pro.score_rate = m_score_rate;
	m_last_pai = id_unknown;
	
	//����4��������,��������Ӱ�죬ֻӰ��ͻ��˵Ķ�����ץ��
	for (uint32_t i = 0; i < 4; i++)
	{
		pro.shaizi[i] = m_pFrame->GetRand() % 6 + 1;
	}
	m_order_recorder[0] = pro.shaizi[0] + pro.shaizi[1];
	m_order_recorder[1] = pro.shaizi[2] + pro.shaizi[3];
	m_order_recorder[2] = 0;
	m_order_recorder[3] = 0;
	IMsgWriter * w = CreateMsgWriter();
	for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
	{
		pro.svr_seat_id = i;
		if (m_banker == i)
			pro.is_banker = 1;
		else
			pro.is_banker = 0;
		pro.ToWriter(w);
		m_pFrame->SendDataToPlayer ( w, i);
	}
	w->Release();
	m_log_str.Format(" �ѷ�����Ϸ��ʼ֪ͨ���ͻ���");//WriteLog(m_log_str);
	
	//ϴ��
	WashCards();
	SendCards();
	//�����ƣ��ֿ���¼
	wstring strCards;
	strCards.clear();
	for(uint32_t j=0; j<m_players.size(); j++)
	{
		for(uint32_t m=0; m<m_players[j].m_pais_in_hand.size(); m++)
			strCards += GetCardStr(m_players[j].m_pais_in_hand[m].u32RealCard);
		if(j < MAX_PLAYER_PER_GAME)
			strCards += L"|";
	}
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"4shaizi   \",\"time\":%I64d,\"seat\":%d,\"objects\":\"%d %d %d %d\"},",m_nLastPulseMS,m_banker-1,pro.shaizi[0],pro.shaizi[1],pro.shaizi[2],pro.shaizi[3]);
	m_wstr_last_recordinfo += buff;
	swprintf_s(buff, L"\n\t\t{\"type\":\"deals     \",\"time\":%I64d,\"seat\":%d,\"objects\":\"%s\"},",m_nLastPulseMS,m_banker-1,strCards.c_str());
	m_wstr_last_recordinfo += buff;
}

void game_majong2::on_pro_expresssion(int seat_id, pro_expression &pro)
{
	assert(seat_id >0 && seat_id <= MAX_PLAYER_PER_GAME);

	IMsgWriter *w = CreateMsgWriter();
	pro.ToWriter(w);
	for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
		m_pFrame->SendDataToPlayer(w, i, true);
	w->Release();
}

void game_majong2::on_pro_game_data_req(int seat_id, bool bLookon, uint64_t nPlayerId, int nLookonFlags)
{
	assert(seat_id >0 && seat_id <= MAX_PLAYER_PER_GAME);

	pro_game_data_reply		reply;
	reply.plrdata.reset();
	reply.state = m_state;
	reply.current_player = m_current_player;
	reply.my_seat_id = seat_id;
	int		passed_time = m_nLastPulseMS - m_begin;
	reply.timeout = (m_timeout*1000 >= passed_time) ? ((m_timeout*1000 - passed_time)/1000) : 0;
	reply.banker = m_banker;
	reply.multiple = m_players[seat_id-1].m_double;
	for (uint32_t i = 0; i < m_players[seat_id-1].m_pais_chew_pong_kong.size(); i++)
	{//�ҵĳ�����
		reply.plrdata.my_chi_peng_gang[i*5] = (char)(m_players[seat_id-1].m_pais_chew_pong_kong[i][0].u32RealCard);
		reply.plrdata.my_chi_peng_gang[i*5+1] = (char)(m_players[seat_id-1].m_pais_chew_pong_kong[i][1].u32RealCard);
		reply.plrdata.my_chi_peng_gang[i*5+2] = (char)(m_players[seat_id-1].m_pais_chew_pong_kong[i][2].u32RealCard);
	
		if (m_players[seat_id-1].m_pais_chew_pong_kong[i].size() == 4)//��
		{
			reply.plrdata.my_chi_peng_gang[i*5+3] = (char)(m_players[seat_id-1].m_pais_chew_pong_kong[i][3].u32RealCard);
			reply.plrdata.my_chi_peng_gang[i*5+4] = m_players[seat_id-1].m_flag_for_ming_an[i];
		}
	}
	for (uint32_t i = 0; i < m_players[seat_id-1].m_pais_on_table.size();i++)
	{//�ҵĳ���
		reply.plrdata.my_out_cards[i] = (char)(m_players[seat_id-1].m_pais_on_table[i].u32RealCard);
	}
	for (uint32_t i = 0; i < m_players[seat_id-1].m_oppisite_player->m_pais_chew_pong_kong.size(); i++)
	{//�Լҵĳ�����
		reply.plrdata.oppisite_chi_peng_gang[i*5] = (char)(m_players[seat_id-1].m_oppisite_player->m_pais_chew_pong_kong[i][0].u32RealCard);
		reply.plrdata.oppisite_chi_peng_gang[i*5+1] = (char)(m_players[seat_id-1].m_oppisite_player->m_pais_chew_pong_kong[i][1].u32RealCard);
		reply.plrdata.oppisite_chi_peng_gang[i*5+2] = (char)(m_players[seat_id-1].m_oppisite_player->m_pais_chew_pong_kong[i][2].u32RealCard);

		if (m_players[seat_id-1].m_oppisite_player->m_pais_chew_pong_kong[i].size() == 4)//��
		{
			reply.plrdata.oppisite_chi_peng_gang[i*5+3] = (char)(m_players[seat_id-1].m_oppisite_player->m_pais_chew_pong_kong[i][3].u32RealCard);
			reply.plrdata.oppisite_chi_peng_gang[i*5+4] = m_players[seat_id-1].m_oppisite_player->m_flag_for_ming_an[i];
		}
	}
	for (uint32_t i = 0; i < m_players[seat_id-1].m_oppisite_player->m_pais_on_table.size();i++)
	{//�Լҵĳ���
		reply.plrdata.oppisite_out_cards[i] = (char)(m_players[seat_id-1].m_oppisite_player->m_pais_on_table[i].u32RealCard);
	}
	for (uint32_t i = 0; i < m_players[seat_id-1].m_pais_in_hand.size(); i++)
	{//�ҵ�������
		reply.plrdata.my_cards_group[i] = (char)(m_players[seat_id-1].m_pais_in_hand[i].u32RealCard);
	}
	for (int i = 0; i < 4; i++)
	{//��������Ƶ��ĸ�����
		reply.plrdata.table_update[i] = (char)(m_order_recorder[i]);
	}
	reply.plrdata.my_flowers_count = (char)(m_players[seat_id-1].m_pais_flowers.size());
	reply.plrdata.oppisite_card_count = (char)(m_players[seat_id-1].m_oppisite_player->m_pais_in_hand.size());
	reply.plrdata.oppisite_flower_count = (char)(m_players[seat_id-1].m_oppisite_player->m_pais_flowers.size());
	if (m_players[seat_id-1].is_ting)
	{
		reply.plrdata.is_tuo_guan = 2;
	}
	else if (m_players[seat_id-1].is_auto)
	{
		reply.plrdata.is_tuo_guan = 1;
	}
	IMsgWriter *w = CreateMsgWriter();
	reply.ToWriter(w);
	if(!bLookon)
		m_pFrame->SendDataToPlayer(w, seat_id);
	else
		m_pFrame->SendDataToWatcher(w, nPlayerId);
	w->Release();
}

void game_majong2::WashCards()
{
	CStringA sss;
	m_all_pais.clear();
	pai_kind pai_kind_;
	for(int i=0; i<72; i++)
	{
		pai_kind_.u32RealCard = i + bamboo_1A;
		pai_kind_.u32Status = status_sleep;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		m_all_pais.push_back(pai_kind_);
	}

	vector<pai_kind>	tmpPaisLeft;
	for(uint32_t i=0; i<m_all_pais.size(); i++)
		tmpPaisLeft.push_back(m_all_pais[i]);

	for(uint32_t i=0; i<m_all_pais.size(); i++)
	{
		m_all_pais[i] = tmpPaisLeft[m_pFrame->GetRand()%tmpPaisLeft.size()];
		for (vector<pai_kind>::iterator iter = tmpPaisLeft.begin();iter != tmpPaisLeft.end();iter++)
		{
			if ((*iter).u32RealCard == m_all_pais[i].u32RealCard)
			{
				tmpPaisLeft.erase(iter);
				break;
			}
		}
	}
	//m_all_pais = mycard();//�Լ�ָ����
}

void game_majong2::SendCards()
{
	m_log_str.Format("����SendCards");
	
	pai_kind pai_kind_;
	if(m_banker == 1)
	{
		for (uint32_t i = 0; i < 3; i++)
		{
			for (uint32_t j =0; j < 4; j++)
			{
				pai_kind_.u32RealCard = GetACard();
				if (pai_kind_.u32RealCard == id_unknown)
				{
					CStringA log_str;log_str.Format("SendCards1��GetACard����id_unknown");WriteLog(log_str);
				}
				m_order_recorder[2]++;
				pai_kind_.u32Status = status_in_hand_normal;
				pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
				m_players[0].m_pais_in_hand.push_back(pai_kind_);
				while(m_players[0].CheckFlower() != id_unknown)
				{
					m_players[0].m_pais_flowers.push_back(pai_kind_);
					m_players[0].m_pais_in_hand.pop_back();
					pai_kind_.u32RealCard = GetACard();
					if (pai_kind_.u32RealCard == id_unknown)
					{
						CStringA log_str;log_str.Format("SendCards2��GetACard����id_unknown");WriteLog(log_str);
					}
					m_order_recorder[3]++;
					pai_kind_.u32Status = status_in_hand_normal;
					pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
					m_players[0].m_pais_in_hand.push_back(pai_kind_);
				}
			}
			for(uint32_t j = 0; j < 4; j++)
			{
				pai_kind_.u32RealCard = GetACard();
				if (pai_kind_.u32RealCard == id_unknown)
				{
					CStringA log_str;log_str.Format("SendCards3��GetACard����id_unknown");WriteLog(log_str);
				}
				m_order_recorder[2]++;
				pai_kind_.u32Status = status_in_hand_normal;
				pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
				m_players[1].m_pais_in_hand.push_back(pai_kind_);
				while(m_players[1].CheckFlower() != id_unknown)
				{
					m_players[1].m_pais_flowers.push_back(pai_kind_);
					m_players[1].m_pais_in_hand.pop_back();
					pai_kind_.u32RealCard = GetACard();
					if (pai_kind_.u32RealCard == id_unknown)
					{
						CStringA log_str;log_str.Format("SendCards4��GetACard����id_unknown");WriteLog(log_str);
					}
					m_order_recorder[3]++;
					pai_kind_.u32Status = status_in_hand_normal;
					pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
					m_players[1].m_pais_in_hand.push_back(pai_kind_);
				}
			}
		}//����12�ţ�����1�ţ����ȸ�13��
		pai_kind_.u32RealCard = GetACard();
		if (pai_kind_.u32RealCard == id_unknown)
		{
			CStringA log_str;log_str.Format("SendCards5��GetACard����id_unknown");WriteLog(log_str);
		}
		m_order_recorder[2]++;
		pai_kind_.u32Status = status_in_hand_normal;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		m_players[0].m_pais_in_hand.push_back(pai_kind_);
		while(m_players[0].CheckFlower() != id_unknown)
		{
			m_players[0].m_pais_flowers.push_back(pai_kind_);
			m_players[0].m_pais_in_hand.pop_back();
			pai_kind_.u32RealCard = GetACard();
			if (pai_kind_.u32RealCard == id_unknown)
			{
				CStringA log_str;log_str.Format("SendCards6��GetACard����id_unknown");WriteLog(log_str);
			}
			m_order_recorder[3]++;
			pai_kind_.u32Status = status_in_hand_normal;
			pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
			m_players[0].m_pais_in_hand.push_back(pai_kind_);
		}
		m_players[0].HandPaiSort();
		pai_kind_.u32RealCard = GetACard();
		if (pai_kind_.u32RealCard == id_unknown)
		{
			CStringA log_str;log_str.Format("SendCards7��GetACard����id_unknown");WriteLog(log_str);
		}
		m_order_recorder[2]++;
		pai_kind_.u32Status = status_in_hand_normal;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		m_players[1].m_pais_in_hand.push_back(pai_kind_);
		while(m_players[1].CheckFlower() != id_unknown)
		{
			m_players[1].m_pais_flowers.push_back(pai_kind_);
			m_players[1].m_pais_in_hand.pop_back();
			pai_kind_.u32RealCard = GetACard();
			if (pai_kind_.u32RealCard == id_unknown)
			{
				CStringA log_str;log_str.Format("SendCards8��GetACard����id_unknown");WriteLog(log_str);
			}
			m_order_recorder[3]++;
			pai_kind_.u32Status = status_in_hand_normal;
			pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
			m_players[1].m_pais_in_hand.push_back(pai_kind_);
		}
		m_players[1].HandPaiSort();
	}	
	else if (m_banker == 2)
	{
		for (uint32_t i = 0; i < 3; i++)
		{
			for (uint32_t j =0; j < 4; j++)
			{
				pai_kind_.u32RealCard = GetACard();
				if (pai_kind_.u32RealCard == id_unknown)
				{
					CStringA log_str;log_str.Format("SendCards9��GetACard����id_unknown");WriteLog(log_str);
				}
				m_order_recorder[2]++;
				pai_kind_.u32Status = status_in_hand_normal;
				pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
				m_players[1].m_pais_in_hand.push_back(pai_kind_);
				while(m_players[1].CheckFlower() != id_unknown)
				{
					m_players[1].m_pais_flowers.push_back(pai_kind_);
					m_players[1].m_pais_in_hand.pop_back();
					pai_kind_.u32RealCard = GetACard();
					if (pai_kind_.u32RealCard == id_unknown)
					{
						CStringA log_str;log_str.Format("SendCards10��GetACard����id_unknown");WriteLog(log_str);
					}
					m_order_recorder[3]++;
					pai_kind_.u32Status = status_in_hand_normal;
					pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
					m_players[1].m_pais_in_hand.push_back(pai_kind_);
				}
			}
			for (uint32_t j = 0; j < 4; j++)
			{
				pai_kind_.u32RealCard = GetACard();
				if (pai_kind_.u32RealCard == id_unknown)
				{
					CStringA log_str;log_str.Format("SendCards11��GetACard����id_unknown");WriteLog(log_str);
				}
				m_order_recorder[2]++;
				pai_kind_.u32Status = status_in_hand_normal;
				pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
				m_players[0].m_pais_in_hand.push_back(pai_kind_);
				while(m_players[0].CheckFlower() != id_unknown)
				{
					m_players[0].m_pais_flowers.push_back(pai_kind_);
					m_players[0].m_pais_in_hand.pop_back();
					pai_kind_.u32RealCard = GetACard();
					if (pai_kind_.u32RealCard == id_unknown)
					{
						CStringA log_str;log_str.Format("SendCards12��GetACard����id_unknown");WriteLog(log_str);
					}
					m_order_recorder[3]++;
					pai_kind_.u32Status = status_in_hand_normal;
					pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
					m_players[0].m_pais_in_hand.push_back(pai_kind_);
				}
			}
		}//����12�ţ�����1�ţ����ȸ�13��
		pai_kind_.u32RealCard = GetACard();
		if (pai_kind_.u32RealCard == id_unknown)
		{
			CStringA log_str;log_str.Format("SendCards13��GetACard����id_unknown");WriteLog(log_str);
		}
		m_order_recorder[2]++;
		pai_kind_.u32Status = status_in_hand_normal;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		m_players[1].m_pais_in_hand.push_back(pai_kind_);
		while(m_players[1].CheckFlower() != id_unknown)
		{
			m_players[1].m_pais_flowers.push_back(pai_kind_);
			m_players[1].m_pais_in_hand.pop_back();
			pai_kind_.u32RealCard = GetACard();
			if (pai_kind_.u32RealCard == id_unknown)
			{
				CStringA log_str;log_str.Format("SendCards14��GetACard����id_unknown");WriteLog(log_str);
			}
			m_order_recorder[3]++;
			pai_kind_.u32Status = status_in_hand_normal;
			pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
			m_players[1].m_pais_in_hand.push_back(pai_kind_);
		}
		m_players[1].HandPaiSort();
		pai_kind_.u32RealCard = GetACard();
		if (pai_kind_.u32RealCard == id_unknown)
		{
			CStringA log_str;log_str.Format("SendCards15��GetACard����id_unknown");WriteLog(log_str);
		}
		m_order_recorder[2]++;
		pai_kind_.u32Status = status_in_hand_normal;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		m_players[0].m_pais_in_hand.push_back(pai_kind_);
		while(m_players[0].CheckFlower() != id_unknown)
		{
			m_players[0].m_pais_flowers.push_back(pai_kind_);
			m_players[0].m_pais_in_hand.pop_back();
			pai_kind_.u32RealCard = GetACard();
			if (pai_kind_.u32RealCard == id_unknown)
			{
				CStringA log_str;log_str.Format("SendCards16��GetACard����id_unknown");WriteLog(log_str);
			}
			m_order_recorder[3]++;
			pai_kind_.u32Status = status_in_hand_normal;
			pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
			m_players[0].m_pais_in_hand.push_back(pai_kind_);
		}
		m_players[0].HandPaiSort();
	}
	
	//pro_send_pai_s pro_send;
	pro_group_send_pai_s pro_send;
	pro_send.seat_id = 1;
	//pro_send.kind = 0;
	for (uint32_t i = 0; i < m_players[0].m_pais_in_hand.size(); i++)
	{
		pro_send.pais[i] = ((char)(m_players[0].m_pais_in_hand[i].u32RealCard));
		//pro_send.pais.push_back(m_players[0].m_pais_in_hand[i].u32RealCard);
	}
	IMsgWriter * w = CreateMsgWriter();
	pro_send.ToWriter(w);
	m_pFrame->SendDataToPlayer ( w, 1 );

	pro_send.seat_id = 2;
	//pro_send.pais.clear();
	for (uint32_t i = 0; i < m_players[1].m_pais_in_hand.size(); i++)
	{
		pro_send.pais[i] = ((char)(m_players[1].m_pais_in_hand[i].u32RealCard));
		//pro_send.pais.push_back(m_players[1].m_pais_in_hand[i].u32RealCard);
	}
	pro_send.ToWriter(w);
	m_pFrame->SendDataToPlayer ( w, 2 );

	//����ͬʱ�����������
	//pro_update_table_ungot_cards_s pro_update;
	//pro_update.normal_count = m_order_recorder[2];
	//pro_update.reverse_count = m_order_recorder[3];
	//pro_update.kind = 1;
	//pro_update.ToWriter(w);
	//for(int i = 1; i <= MAX_PLAYER_PER_GAME;i++)
	//{
	//	m_pFrame->SendDataToPlayer ( w, i );
	//}
	//
	//if (m_players[0].m_pais_in_hand.size() != 13)
	//{
	//	//�쳣
	//	int xxx[2] = {0};
	//	xxx[2] = 1;
	//}
	w->Release();
}

uint32_t game_majong2::GetACard()
{
	m_log_str.Format("����GetACard");//WriteLog(m_log_str);
	if (m_all_pais.size()>0)
	{
		uint32_t temp = m_all_pais[m_all_pais.size()-1].u32RealCard;
		m_all_pais.pop_back();
		return temp;
	}
	else
	{
		//�ж��Ƿ�ץ���ƣ��Ի�ׯ����
		ProcessHuang();
	}
	return id_unknown;
}

//�Լ�ָ����
std::vector<pai_kind> game_majong2::mycard()
{
	pai_kind pai_kind_;
	std::vector<pai_kind> pais;

	uint32_t rampai[72] = {
		flower_orchid,		bamboo_8D,			 	flower_plum,	white_dragon_D,		east_wind_D,	bamboo_5A,		bamboo_8B,		bamboo_4A,
		flower_spring,	flower_chrysanthemum,	bamboo_6A,		bamboo_7A,		white_dragon_A,	red_dragon_A,	north_wind_A,	west_wind_A,
		flower_summer,	bamboo_8A,				flower_winter,		flower_bamboo,	south_wind_A,	bamboo_7D,		bamboo_2B,		white_dragon_C,
		white_dragon_B,	flower_autumn,			red_dragon_B,	north_wind_B,	west_wind_B,	south_wind_B,	red_dragon_C,	bamboo_5B,
		bamboo_6B,		east_wind_B,			bamboo_9A,		east_wind_A,	bamboo_9B,		bamboo_6C,		bamboo_7C,		bamboo_7B,
		bamboo_5C,		west_wind_C,			bamboo_3A,		north_wind_C,		bamboo_3D,		bamboo_3C,		bamboo_3B,		bamboo_4B,
		bamboo_5D,		bamboo_9C,				east_wind_C,	south_wind_C,	bamboo_4D,		bamboo_4C,		bamboo_1C,		bamboo_1B,
		red_dragon_D,	north_wind_D,			west_wind_D,	south_wind_D,	bamboo_2A,		bamboo_2C,		bamboo_2D,		bamboo_1D,
		bamboo_9D,		bamboo_6D,				bamboo_8C,		green_dragon_C,	bamboo_1A	,	green_dragon_D,	green_dragon_B,	green_dragon_A};
	for(uint32_t i = 0; i < 72;i++)
	{
		pai_kind_.u32RealCard = rampai[i];
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		pai_kind_.u32Status = status_sleep;
		pais.push_back(pai_kind_);
	}
	return pais;
}

void game_majong2::ChangeTurnNotify()
{
	if (m_players.size() != 2 || m_game_is_over)
	{
		//û����ң�������Ϸ�ѽ���
		return;
	}
	IMsgWriter *w = CreateMsgWriter();
	try
	{
		pro_turn_current_player_s pro;
		pro.current_player_seat_id = m_current_player;
		pro.ToWriter(w);
		for(int i = 1; i <= MAX_PLAYER_PER_GAME;i++)
			m_pFrame->SendDataToPlayer ( w, i );
	}
	catch (...)
	{
		CStringA temp_str;
		temp_str.Format("��ǰ���������%d",m_current_player-1);WriteLog(temp_str);
		for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_in_hand.size();i++)
		{
			temp_str.Format("%d",m_players[m_current_player-1].m_pais_in_hand[i].u32ValueCard);WriteLog(temp_str);
		}
	}
	w->Release();
}

void game_majong2::ZiMoSendBtn()
{
	if (m_game_is_over)
	{
		return;
	}
	m_players[m_current_player-1].SetAllPai(m_all_pais);
	m_players[m_current_player-1].CheckAllJudge();
	//���͸��ְ�ť
	
	//pro_chew_pong_kong_hu_ting_notify_s pro;
	usual_btn_send usual_btn_send_;
	usual_btn_send_.btn_flag = 0;
	usual_btn_send_.last_pai = ((char)(m_players[m_current_player-1].m_last_pai));
	usual_btn_send_.special_fan_for_hu = 0;
	
	//chew_pong_kong_hu_ting_data tmp;
	if (m_players[m_current_player-1].m_judge_flag[3] > 0)
	{
		//��������1
		/*std::vector<chew_struct_data>::iterator iter = m_players[m_current_player-1].m_vec_check_ming_gang1.begin();
		tmp.kind = 3;
		for (;iter != m_players[m_current_player-1].m_vec_check_ming_gang1.end();iter++)
		{
		tmp.pai1 = (*iter).pai1;
		tmp.pai2 = (*iter).pai2;
		tmp.pai3 = (*iter).pai3;
		tmp.last_out = (*iter).pai4;
		pro.vec_data.push_back(tmp);	
		}*/
		usual_btn_send_.btn_flag = usual_btn_send_.btn_flag | 0x08;
	}
	if (m_players[m_current_player-1].m_judge_flag[4] > 0)
	{
		//��������2
		/*std::vector<chew_struct_data>::iterator iter = m_players[m_current_player-1].m_vec_check_ming_gang2.begin();
		tmp.kind = 4;
		for (;iter != m_players[m_current_player-1].m_vec_check_ming_gang2.end();iter++)
		{
			tmp.pai1 = (*iter).pai1;
			pro.vec_data.push_back(tmp);
			
		}*/
		usual_btn_send_.btn_flag = usual_btn_send_.btn_flag | 0x10;
	}
	if (m_players[m_current_player-1].m_judge_flag[5] > 0)
	{
		//������
		//pro_send_ting_data_s pro_send_ting;
		//for (uint32_t j = 0;j<16;j++)
		//{
		//	for (uint32_t k = 0;k<16;k++)
		//	{
		//		pro_send_ting.ting_data[j][k] = m_players[m_current_player-1].m_check_ting[0][j][k] + m_players[m_current_player-1].m_check_ting[1][j][k] * 100;
		//		if (m_players[m_current_player-1].m_check_ting[0][j][k] > 0)
		//		{
		//			m_log_str.Format("����j:%d,k:%d,value:%d",j,k,m_players[m_current_player-1].m_check_ting[0][j][k]);//WriteLog(m_log_str);
		//		}

		//	}
		//}
		//pro_send_ting.ToWriter(ww);
		//m_pFrame->SendDataToPlayer ( ww, m_current_player );
		usual_btn_send_.btn_flag = usual_btn_send_.btn_flag | 0x40;
	}
	if (m_players[m_current_player-1].m_judge_flag[6] > 0)
	{
		//���ͺ�
		//tmp.kind = 5;
		//tmp.last_out = m_players[m_current_player-1].m_check_hu[0];//������
		//tmp.pai1 = m_players[m_current_player-1].m_check_hu[1];//����
		//pro.vec_data.push_back(tmp);
		//m_log_str.Format("�����ţ�%d",m_players[m_current_player-1].m_check_hu[0]);//WriteLog(m_log_str);
		usual_btn_send_.btn_flag = usual_btn_send_.btn_flag | 0x20;
		//���ֻش�
		if (m_all_pais.size() == 0)
		{
			m_players[m_current_player-1].m_fan_helper.m_is_miao_shou_hui_chun = true;
			m_players[m_current_player-1].m_fan_helper.m_is_hai_di_lao_yue = false;
			m_players[m_current_player-1].m_miao_shou_hui_chun = true;
			m_players[m_current_player-1].m_hai_di_lao_yue = false;
		}
		if (m_players[m_current_player-1].m_miao_shou_hui_chun)
		{
			usual_btn_send_.special_fan_for_hu = usual_btn_send_.special_fan_for_hu | 0x01;
		}
		if (m_players[m_current_player-1].m_hai_di_lao_yue)
		{
			usual_btn_send_.special_fan_for_hu = usual_btn_send_.special_fan_for_hu | 0x02;
		}
		if (m_players[m_current_player-1].m_gang_shang_kai_hua)
		{
			usual_btn_send_.special_fan_for_hu = usual_btn_send_.special_fan_for_hu | 0x04;
		}
		if (m_players[m_current_player-1].m_qiang_gang_hu)
		{
			usual_btn_send_.special_fan_for_hu = usual_btn_send_.special_fan_for_hu | 0x08;
		}
	}
	/*if (pro.vec_data.size() > 0 && m_players[m_current_player-1].m_is_get_a_card)
	{
		pro.ToWriter(ww);
		m_pFrame->SendDataToPlayer ( ww, m_current_player );
	}*/
	//if ((usual_btn_send_.btn_flag & 0x20) != 0)
	//{
	//	m_log_str.Format("��ǰ��ң�%d,�����ϵ��ƣ�",m_current_player);WriteLog(m_log_str);
	//	for (int ii = 0; ii < m_players[m_current_player-1].m_pais_in_hand.size();ii++)
	//	{
	//		m_log_str.Format("%d",m_players[m_current_player-1].m_pais_in_hand[ii].u32ValueCard);WriteLog(m_log_str);
	//	}
	//}
	//��������󣬲����������������ȥ�������
	if (m_players[m_current_player-1].m_is_get_a_card == false)
	{
		usual_btn_send_.btn_flag = usual_btn_send_.btn_flag & 0xDF;
	}
	//if (usual_btn_send_.btn_flag != 0 )//&& m_players[m_current_player-1].m_is_get_a_card)
	IMsgWriter *ww = CreateMsgWriter();
	usual_btn_send_.ToWriter(ww);
	m_pFrame->SendDataToPlayer(ww,m_current_player);
	//}
	//m_log_str.Format("��ǰ��ң�%d,����˰�ť��ǣ�%d",m_current_player,usual_btn_send_.btn_flag);WriteLog(m_log_str);
	
	ww->Release();
	//m_log_str.Format("���1���ϵ��ƣ�",m_current_player);WriteLog(m_log_str);
	//for (int ii = 0; ii < m_players[0].m_pais_in_hand.size();ii++)
	//{
	//	m_log_str.Format("%d",m_players[0].m_pais_in_hand[ii].u32ValueCard);WriteLog(m_log_str);
	//}
	//m_log_str.Format("���2���ϵ��ƣ�",m_current_player);WriteLog(m_log_str);
	//for (int ii = 0; ii < m_players[1].m_pais_in_hand.size();ii++)
	//{
	//	m_log_str.Format("%d",m_players[1].m_pais_in_hand[ii].u32ValueCard);WriteLog(m_log_str);
	//}
}

void game_majong2::DianPaoSendBtn()
{
	m_players[m_current_player-1].SetAllPai(m_all_pais);
	m_players[m_current_player-1].CheckAllJudge();
	//���͸��ְ�ť
	
	//pro_chew_pong_kong_hu_ting_notify_s pro;
	//chew_pong_kong_hu_ting_data tmp;
	usual_btn_send usual_btn_send_;
	usual_btn_send_.btn_flag = 0;
	usual_btn_send_.last_pai = ((char)(m_players[m_current_player-1].m_last_pai));
	usual_btn_send_.special_fan_for_hu = 0;
	//��
	if (m_players[m_current_player-1].m_judge_flag[0] > 0)
	{
		usual_btn_send_.btn_flag = usual_btn_send_.btn_flag | 0x01;
	}
	//��
	if (m_players[m_current_player-1].m_judge_flag[1] > 0)
	{
		usual_btn_send_.btn_flag = usual_btn_send_.btn_flag | 0x02;
	}
	//����
	if (m_players[m_current_player-1].m_judge_flag[2] > 0)
	{
		usual_btn_send_.btn_flag = usual_btn_send_.btn_flag | 0x04;
	}
	//���ͺ�
	if (m_players[m_current_player-1].m_judge_flag[6] > 0)
	{
		//��������
		if (m_all_pais.size() == 0)
		{
			m_players[m_current_player-1].m_fan_helper.m_is_hai_di_lao_yue = true;
			m_players[m_current_player-1].m_fan_helper.m_is_miao_shou_hui_chun = false;//�������º����ֻش������ų�
			m_players[m_current_player-1].m_hai_di_lao_yue = true;
			m_players[m_current_player-1].m_miao_shou_hui_chun = false;//�������º����ֻش������ų�
		}
		usual_btn_send_.btn_flag = usual_btn_send_.btn_flag | 0x20;
		if (m_players[m_current_player-1].m_miao_shou_hui_chun)
		{
			usual_btn_send_.special_fan_for_hu = usual_btn_send_.special_fan_for_hu | 0x01;
		}
		if (m_players[m_current_player-1].m_hai_di_lao_yue)
		{
			usual_btn_send_.special_fan_for_hu = usual_btn_send_.special_fan_for_hu | 0x02;
		}
		if (m_players[m_current_player-1].m_gang_shang_kai_hua)
		{
			usual_btn_send_.special_fan_for_hu = usual_btn_send_.special_fan_for_hu | 0x04;
		}
		if (m_players[m_current_player-1].m_qiang_gang_hu)
		{
			usual_btn_send_.special_fan_for_hu = usual_btn_send_.special_fan_for_hu | 0x08;
		}
	}
	if (usual_btn_send_.btn_flag != 0)
	{
		IMsgWriter *ww = CreateMsgWriter();
		usual_btn_send_.ToWriter(ww);
		m_pFrame->SendDataToPlayer(ww,m_current_player);
		ww->Release();
	}
	else
	{
		//�ް�ť����һ���ƣ�ȥ��
		m_players[m_current_player-1].SetMyZiMoStatus();
		SendACardNormal();
		ZiMoSendBtn();
	}
}

void game_majong2::SendACard()
{
	uint32_t u32RealCard = GetACard();
	if (u32RealCard == id_unknown)
	{
		CStringA log_str;log_str.Format("SendCards17��GetACard����id_unknown");WriteLog(log_str);
		return;
	}
	pai_kind pai_kind_;
	pai_kind_.u32RealCard = u32RealCard;
	pai_kind_.u32Status = status_in_hand_normal;
	pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
	m_players[m_current_player-1].m_pais_in_hand.push_back(pai_kind_);
	while(m_players[m_current_player-1].CheckFlower() != id_unknown)
	{
		m_players[m_current_player-1].m_pais_flowers.push_back(pai_kind_);
		m_players[m_current_player-1].m_pais_in_hand.pop_back();
		//�ֿ�
		wstring strCards;
		strCards = GetCardStr(pai_kind_.u32RealCard);
		wchar_t buff[512];
		swprintf_s(buff, L"\n\t\t{\"type\":\"flower    \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
		m_wstr_last_recordinfo += buff;
		//�ֿ�
		pai_kind_.u32RealCard = GetACard();
		if (pai_kind_.u32RealCard == id_unknown)
		{
			CStringA log_str;log_str.Format("SendCards18��GetACard����id_unknown");WriteLog(log_str);
			return;
		}
		m_order_recorder[3]++;
		pai_kind_.u32Status = status_in_hand_normal;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		m_players[m_current_player-1].m_pais_in_hand.push_back(pai_kind_);
		pro_add_flower_count add_flower_count;
		add_flower_count.seat_id = m_current_player;
		add_flower_count.total_flowers = ((char)(m_players[m_current_player-1].m_pais_flowers.size()));
		IMsgWriter *w = CreateMsgWriter();
		add_flower_count.ToWriter(w);
		for(int i = 1; i <= MAX_PLAYER_PER_GAME;i++)
		{
			m_pFrame->SendDataToPlayer ( w, i );
		}
		
		//����ͬʱ����
		pro_update_table_ungot_cards_s pro_update;
		pro_update.normal_count = m_order_recorder[2];
		pro_update.reverse_count = m_order_recorder[3];
		pro_update.kind = 1;
		pro_update.ToWriter(w);
		for(int i = 1; i <= MAX_PLAYER_PER_GAME;i++)
		{
			m_pFrame->SendDataToPlayer ( w, i );
		}
		//
		w->Release();
	}

	m_players[0].m_last_pai = m_players[m_current_player-1].m_pais_in_hand[m_players[m_current_player-1].m_pais_in_hand.size()-1].u32RealCard;
	m_players[1].m_last_pai = m_players[m_current_player-1].m_pais_in_hand[m_players[m_current_player-1].m_pais_in_hand.size()-1].u32RealCard;
	
	m_players[m_current_player-1].m_is_get_a_card = true;

	m_players[m_current_player-1].HandPaiSort();
	//pro_send_pai_s pro_send;
	pro_single_send_pai_s pro_send;
	pro_send.seat_id = m_current_player;
	//pro_send.kind = 1;
	//pro_send.pais.push_back(pai_kind_.u32RealCard);
	pro_send.pai = (char)(pai_kind_.u32RealCard);
	IMsgWriter *w = CreateMsgWriter();
	pro_send.ToWriter(w);
	for(int i = 1; i <= MAX_PLAYER_PER_GAME;i++)
	{
		m_pFrame->SendDataToPlayer ( w, i );
	}
	w->Release();
	//�ֿ�
	wstring strCards;
	strCards = GetCardStr(pai_kind_.u32RealCard);
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"SendACard \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
	m_log_str.Format("��ң�%d��SendACard:%d",m_current_player,u32RealCard);//WriteLog(m_log_str);
	//if (m_players[m_current_player-1].m_pais_in_hand.size() > 14)
	//{
	//	//�쳣
	//	int xxx[2] = {0};
	//	xxx[2] = 1;
	//}
}

void game_majong2::SendACardNormal()
{
	m_log_str.Format("����SendACardNormal");//WriteLog(m_log_str);
	SendACard();
	if (m_game_is_over)
	{
		return;
	}
	IMsgWriter *w = CreateMsgWriter();
	//�Ӹ�������δץ��
	m_order_recorder[2]++;
	pro_update_table_ungot_cards_s pro;
	pro.kind = 2; pro.normal_count = m_order_recorder[2]; pro.reverse_count = m_order_recorder[3];pro.ToWriter(w);

	for(int i = 1; i <= MAX_PLAYER_PER_GAME;i++)
		m_pFrame->SendDataToPlayer ( w, i );
	w->Release();
	
}

void game_majong2::SendACardReverse()
{
	m_log_str.Format("����SendACardReverse");//WriteLog(m_log_str);
	SendACard();
	if (m_game_is_over)
	{
		return;
	}
	IMsgWriter *w = CreateMsgWriter();
	//�Ӹ�������δץ�ƣ������������ڴˣ�
	m_order_recorder[3]++;
	pro_update_table_ungot_cards_s pro;
	pro.kind = 3;pro.normal_count = m_order_recorder[2];pro.reverse_count = m_order_recorder[3];pro.ToWriter(w);

	for(int i = 1; i <= MAX_PLAYER_PER_GAME;i++)
		m_pFrame->SendDataToPlayer ( w, i );
	w->Release();
}

void game_majong2::OnClickBtn(pro_click_btn_c pro)
{

	m_log_str.Format("����OnClickBtn");//WriteLog(m_log_str);
	switch(pro.kind)
	{
	case btn_id_normal://��ͨ
		{
			if (m_players[pro.seat_id-1].is_auto || m_players[pro.seat_id-1].is_ting || pro.seat_id != m_current_player)
			{
				return;
			}
			ProcessOutCardReq(pro.index);
			break;
		}
	case btn_id_chi://��
		{
			if (m_players[pro.seat_id-1].is_auto || m_players[pro.seat_id-1].is_ting || pro.seat_id != m_current_player)
			{
				return;
			}
			ProcessChiReq(pro.index);
			break;
		}
	case btn_id_peng://��
		{
			if (m_players[pro.seat_id-1].is_auto || m_players[pro.seat_id-1].is_ting || pro.seat_id != m_current_player)
			{
				return;
			}
			ProcessPengReq(pro.index);
			break;
		}
	case btn_id_an_gang://����
		{
			if (m_players[pro.seat_id-1].is_auto || m_players[pro.seat_id-1].is_ting || pro.seat_id != m_current_player)
			{
				return;
			}
			ProcessGangReq(pro.index);
			break;
		}
	case btn_id_ming_gang_1://����1
		{
			if (m_players[pro.seat_id-1].is_auto || m_players[pro.seat_id-1].is_ting || pro.seat_id != m_current_player)
			{
				return;
			}
			ProcessMingGang1Req(pro.index);
			break;
		}
	case btn_id_ming_gang_2://����2
		{
			if (m_players[pro.seat_id-1].is_auto || m_players[pro.seat_id-1].is_ting || pro.seat_id != m_current_player)
			{
				return;
			}
			ProcessMingGang2Req(pro.index);
			break;
		}
	case btn_id_hu://��
		{
			if (m_players[pro.seat_id-1].is_auto || pro.seat_id != m_current_player)
			{
				return;
			}
			ProcessHuReq(pro.index);
			break;
		}
	case btn_id_ting://��
		{
			if (m_players[pro.seat_id-1].is_auto || m_players[pro.seat_id-1].is_ting || pro.seat_id != m_current_player)
			{
				return;
			}
			if (pro.index == 0)
			{
				uint32_t robot_ting_index = 0;
				ProcessTingReq(robot_ting_index);
				for (uint32_t i = 0; i < m_players[pro.seat_id-1].m_pais_in_hand.size(); i++)
				{
					if (m_players[pro.seat_id-1].m_pais_in_hand[i].u32ValueCard == robot_ting_index)
					{
						robot_ting_index = m_players[pro.seat_id-1].m_pais_in_hand[i].u32RealCard;
						break;
					}
				}
				ProcessOutCardReq(robot_ting_index);
			}
			else
			{
				uint32_t ch2u32 = (uint32_t)(pro.index);
				ProcessTingReq(ch2u32);
				ProcessOutCardReq(pro.index);
			}
			break;
		}
	case btn_id_tuo_guan://�й�
		{
			break;
		}
	case btn_id_qu_xiao_tuo_guan://ȡ���й�
		{
			m_players[pro.seat_id-1].is_auto = false;
			pro_ting_notify_s pro_tuo_notify;
			pro_tuo_notify.seat_id = pro.seat_id;
			pro_tuo_notify.kind = 2;
			IMsgWriter *ww = CreateMsgWriter();
			pro_tuo_notify.ToWriter(ww);
			for (uint32_t i = 1; i <= 2; i++)
			{
				m_pFrame->SendDataToPlayer(ww,i);
			}
			ww->Release();//ȡ���йܺ����·���ť
			if (m_players[pro.seat_id-1].m_current_status == 1)
			{
				ZiMoSendBtn();
			}
			else if (m_players[pro.seat_id-1].m_current_status == 2)
			{
				DianPaoSendBtn();
			}
			break;
		}
	case btn_id_fangqi:
		{
			//if (m_players[pro.seat_id-1].is_auto || m_players[pro.seat_id-1].is_ting || pro.seat_id != m_current_player)
			if (m_players[pro.seat_id-1].is_auto ||  pro.seat_id != m_current_player)
			{
				return;
			}
			ProcessFangQiReq(pro.index);
			break;
		}
	case btn_id_jiabei:
		{
			//if (m_players[pro.seat_id-1].is_auto || m_players[pro.seat_id-1].is_ting || pro.seat_id != m_current_player)
			if (m_players[pro.seat_id-1].is_auto || pro.seat_id != m_current_player)
			{
				return;
			}
			ProcessJiaBei(pro.index);
			break;
		}
	}
}

void game_majong2::ProcessOutCardReq(uint32_t u32RealCard)
{
	m_log_str.Format("�յ�%d��������������Ϊ��%d",m_current_player,u32RealCard);//WriteLog(m_log_str);
	
	if(false == m_players[m_current_player-1].ProcessOutACard(u32RealCard))
	{
		/*printf("��ǰ���%d���Ƴ����ˣ�\r\n",m_current_player);
		if (m_players[m_current_player-1].is_ting)
		{
		printf("��ʱ��������״̬��\r\n");
		}
		else
		{
		printf("��ʱ����������״̬��\r\n");
		}
		for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_in_hand.size(); i++)
		{
		printf("Ψһֵ��%d����ֵ��%d\r\n",m_players[m_current_player-1].m_pais_in_hand[i].u32RealCard,m_players[m_current_player-1].m_pais_in_hand[i].u32ValueCard);
		}*/
		pro_same_with_svr same_with_svr;
		same_with_svr.seat_id = m_current_player;
		memset(same_with_svr.pais,0,14);
		same_with_svr.index = 0;
		for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_in_hand.size(); i++)
		{
			same_with_svr.pais[i] = (char)(m_players[m_current_player-1].m_pais_in_hand[i].u32RealCard); 
		}
		IMsgWriter *w = CreateMsgWriter();
		same_with_svr.ToWriter(w);
		for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
		{
			m_pFrame->SendDataToPlayer ( w, i );
		}
		w->Release();
		m_log_str.Format("������������");WriteLog(m_log_str);
		return;
	}
	//��ǰ��ҳ���
	pro_out_card_notify_s notify;
	m_players[m_current_player-1].SetOppisiteZiMoStatus();//������һ��Ϊ����״̬
	IMsgWriter *w = CreateMsgWriter();
	notify.seat_id = m_current_player;notify.kind = btn_id_normal;notify.pai[0] = u32RealCard;notify.ToWriter(w);
	for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
	{
		m_pFrame->SendDataToPlayer ( w, i );
	}
	w->Release();
	
	m_players[0].m_last_pai = u32RealCard;
	m_players[1].m_last_pai = u32RealCard;
	
	m_current_player++;//��ͨ�ƴ���󣬱任��ǰ���
	if (m_current_player > MAX_PLAYER_PER_GAME)
	{
		m_current_player = 1;
	}
	//�ֿ�
	wstring strCards;
	strCards = GetCardStr(u32RealCard);
	if (strCards == L"")
	{
		int x = 0;
	}
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"normal    \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
	DianPaoSendBtn();
	ChangeTurnNotify();
}

void game_majong2::ProcessChiReq(uint32_t index)
{
	m_log_str.Format("�յ�������������Ϊ��%d",index);//WriteLog(m_log_str);
	
	pro_out_card_notify_s notify;
	if(index >= m_players[m_current_player-1].m_vec_check_chew.size())
		return;
	notify.seat_id = m_current_player;
	notify.kind = btn_id_chi;
	//if (index < 0 || index >= m_players[m_current_player-1].m_vec_check_chew.size())
	//{
	//	return;//����������
	//}
	if(m_players[m_current_player-1].ProcessChi(index,notify.pai[0],notify.pai[1],notify.pai[2]) == false) 
	{
		m_log_str.Format("����ʱ�Լ����������ƣ����棡");WriteLog(m_log_str);
		pro_same_with_svr same_with_svr;
		same_with_svr.seat_id = m_current_player;
		memset(same_with_svr.pais,0,14);
		same_with_svr.index = 1;
		for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_in_hand.size(); i++)
		{
			same_with_svr.pais[i] = (char)(m_players[m_current_player-1].m_pais_in_hand[i].u32RealCard); 
		}
		IMsgWriter *w = CreateMsgWriter();
		same_with_svr.ToWriter(w);
		for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
		{
			m_pFrame->SendDataToPlayer ( w, i );
		}
		w->Release();
		m_log_str.Format("������������");WriteLog(m_log_str);
		DianPaoSendBtn();//�����ƺ��ٴη��͵��ڰ�ť
		return;
	}
	m_log_str.Format("�Ե������ƣ�%d,%d,%d",notify.pai[0],notify.pai[1],notify.pai[2]);//WriteLog(m_log_str);
	IMsgWriter *w = CreateMsgWriter();
	notify.ToWriter(w);
	for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
	{
		m_pFrame->SendDataToPlayer ( w, i );
	}
	w->Release();
	//�ֿ�
	wstring strCards;
	strCards = GetCardStr(notify.pai[0]);
	strCards += GetCardStr(notify.pai[1]);
	strCards += GetCardStr(notify.pai[2]);
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"chew      \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
	//�밵����ȣ���Ϊ��ץ��ʱ������ʽ
	m_players[m_current_player-1].SetMyZiMoStatus();
	m_players[m_current_player-1].m_is_get_a_card = false;

	//����������ť
	ZiMoSendBtn();
}

void game_majong2::ProcessPengReq(uint32_t index)
{
	
	pro_out_card_notify_s notify;

	notify.seat_id = m_current_player;
	notify.kind = btn_id_peng;
	notify.pai[0]=id_unknown;notify.pai[1]=id_unknown;notify.pai[2]=id_unknown;notify.pai[3]=id_unknown;
	//if (index < 0 || index >= m_players[m_current_player-1].m_vec_check_peng.size())
	//{
	//	return;//����������
	//}
	if(m_players[m_current_player-1].ProcessPeng(index,notify.pai[0],notify.pai[1],notify.pai[2]) == false)
	{
		m_log_str.Format("����ʱ�Լ����������ƣ����棡");WriteLog(m_log_str);
		pro_same_with_svr same_with_svr;
		same_with_svr.seat_id = m_current_player;
		memset(same_with_svr.pais,0,14);
		same_with_svr.index = 1;
		for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_in_hand.size(); i++)
		{
			same_with_svr.pais[i] = (char)(m_players[m_current_player-1].m_pais_in_hand[i].u32RealCard); 
		}
		IMsgWriter *w = CreateMsgWriter();
		same_with_svr.ToWriter(w);
		for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
		{
			m_pFrame->SendDataToPlayer ( w, i );
		}
		w->Release();
		m_log_str.Format("������������");WriteLog(m_log_str);
		DianPaoSendBtn();//�����ƺ��ٴη��͵��ڰ�ť
		return;
	}
	IMsgWriter *w = CreateMsgWriter();
	notify.ToWriter(w);
	for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
	{
		m_pFrame->SendDataToPlayer ( w, i );
	}
	w->Release();
	//�ֿ�
	wstring strCards;
	strCards = GetCardStr(notify.pai[0]);
	strCards += GetCardStr(notify.pai[1]);
	strCards += GetCardStr(notify.pai[2]);
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"pong      \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
	//�밵����ȣ���Ϊ��ץ��ʱ������ʽ
	m_players[m_current_player-1].SetMyZiMoStatus();
	m_players[m_current_player-1].m_is_get_a_card = false;
	
	//����������ť
	ZiMoSendBtn();
}

void game_majong2::ProcessGangReq(uint32_t index)
{
	
	pro_out_card_notify_s notify;
	pai_kind pai_kind_;
	uint32_t u32Value = pai_kind_.GetValueFromRealCard(m_players[m_current_player-1].m_vec_check_an_gang[index].pai1);

	if(m_players[m_current_player-1].ProcessAnGang(u32Value) == false)
	{
		m_log_str.Format("����ʱ�Լ����������ƣ����棡");WriteLog(m_log_str);
		pro_same_with_svr same_with_svr;
		same_with_svr.seat_id = m_current_player;
		memset(same_with_svr.pais,0,14);
		same_with_svr.index = 1;
		for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_in_hand.size(); i++)
		{
			same_with_svr.pais[i] = (char)(m_players[m_current_player-1].m_pais_in_hand[i].u32RealCard); 
		}
		IMsgWriter *w = CreateMsgWriter();
		same_with_svr.ToWriter(w);
		for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
		{
			m_pFrame->SendDataToPlayer ( w, i );
		}
		w->Release();
		m_log_str.Format("��������������");WriteLog(m_log_str);
		DianPaoSendBtn();//�����ƺ��ٴη��͵��ڰ�ť
		return;
	}
	IMsgWriter *w = CreateMsgWriter();
	notify.seat_id = m_current_player;notify.kind = btn_id_an_gang;notify.pai[0] = u32Value;notify.ToWriter(w);
	for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
	{
		m_pFrame->SendDataToPlayer ( w, i );
	}

	w->Release();
	//�ֿ�
	wstring strCards;
	strCards = GetCardStr(m_players[m_current_player-1].m_vec_check_an_gang[index].pai1);
	strCards += GetCardStr(m_players[m_current_player-1].m_vec_check_an_gang[index].pai1);
	strCards += GetCardStr(m_players[m_current_player-1].m_vec_check_an_gang[index].pai1);
	strCards += GetCardStr(m_players[m_current_player-1].m_vec_check_an_gang[index].pai1);
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"mingkong1 \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
	//���ܺ��ٷ���һ����
	m_players[m_current_player-1].SetMyZiMoStatus();
	SendACardReverse();
	
	//����������ť
	ZiMoSendBtn();
}

void game_majong2::ProcessMingGang1Req(uint32_t index)
{
	
	
	pro_out_card_notify_s notify;
	pai_kind pai_kind_;
	uint32_t u32Value = pai_kind_.GetValueFromRealCard(m_players[m_current_player-1].m_vec_check_ming_gang1[index].pai1);
	if(false == m_players[m_current_player-1].ProcessMingGang1(u32Value))
	{
		pro_same_with_svr same_with_svr;
		same_with_svr.seat_id = m_current_player;
		memset(same_with_svr.pais,0,14);
		same_with_svr.index = 1;
		for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_in_hand.size(); i++)
		{
			same_with_svr.pais[i] = (char)(m_players[m_current_player-1].m_pais_in_hand[i].u32RealCard); 
		}
		IMsgWriter *w = CreateMsgWriter();
		same_with_svr.ToWriter(w);
		for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
		{
			m_pFrame->SendDataToPlayer ( w, i );
		}
		w->Release();
		m_log_str.Format("��������1������");WriteLog(m_log_str);
		ZiMoSendBtn();//�����ƺ��ٴη���������ť
		return;
	}

	notify.seat_id = m_current_player;
	IMsgWriter *w = CreateMsgWriter();
	notify.kind = btn_id_ming_gang_1;notify.pai[0] = u32Value;notify.pai[1] = value_unknown;notify.pai[2] = value_unknown;notify.pai[3] = value_unknown;notify.ToWriter(w);
	for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
	{
		m_pFrame->SendDataToPlayer ( w, i );
	}
	w->Release();
	//�ֿ�
	wstring strCards;
	strCards = GetCardStr(m_players[m_current_player-1].m_vec_check_ming_gang1[index].pai1);
	strCards += GetCardStr(m_players[m_current_player-1].m_vec_check_ming_gang1[index].pai1);
	strCards += GetCardStr(m_players[m_current_player-1].m_vec_check_ming_gang1[index].pai1);
	strCards += GetCardStr(m_players[m_current_player-1].m_vec_check_ming_gang1[index].pai1);
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"ankong    \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
	//�ܺ��ٷ���һ����
	m_players[m_current_player-1].SetMyZiMoStatus();
	SendACardReverse();
	
	//����������ť
	ZiMoSendBtn();
}

void game_majong2::ProcessMingGang2Req(uint32_t index)
{
	m_log_str.Format("�յ�����2������last_pai��%d",m_last_pai);//WriteLog(m_log_str);
	

	pro_out_card_notify_s notify;
	uint32_t u32RealCard = m_players[m_current_player-1].m_vec_check_ming_gang2[index].pai1;
	if(false == m_players[m_current_player-1].ProcessMingGang2(u32RealCard))
	{
		pro_same_with_svr same_with_svr;
		same_with_svr.seat_id = m_current_player;
		memset(same_with_svr.pais,0,14);
		same_with_svr.index = 1;
		for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_in_hand.size(); i++)
		{
			same_with_svr.pais[i] = (char)(m_players[m_current_player-1].m_pais_in_hand[i].u32RealCard); 
		}
		IMsgWriter *w = CreateMsgWriter();
		same_with_svr.ToWriter(w);
		for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
		{
			m_pFrame->SendDataToPlayer ( w, i );
		}
		w->Release();
		m_log_str.Format("��������2������");WriteLog(m_log_str);
		ZiMoSendBtn();//�����ƺ��ٴη��͵��ڰ�ť
		return;
	}
	IMsgWriter *w = CreateMsgWriter();
	notify.seat_id = m_current_player;notify.kind = btn_id_ming_gang_2;notify.pai[0] = u32RealCard;notify.ToWriter(w);
	for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
	{
		m_pFrame->SendDataToPlayer ( w, i );
	}
	w->Release();
	//�ֿ�
	wstring strCards;
	strCards = GetCardStr(u32RealCard);
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"mingkong2 \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
	//�ܺ��ٷ���һ����
	m_players[m_current_player-1].SetMyZiMoStatus();
	SendACardReverse();
	//����������ť
	ZiMoSendBtn();
}

void game_majong2::ProcessHuReq(uint32_t index)
{
	m_log_str.Format("����ProcessHuReq");//WriteLog(m_log_str);
	//���ּ���
	//�ܷ� = ���� �� ���� �� ����
	//������͸���ܵ�����
	int				arrResult[MAX_PLAYER_PER_GAME+1];
	long long		arrScore[MAX_PLAYER_PER_GAME+1];
	char			attData[64];
	int				arrAttDataSize[MAX_PLAYER_PER_GAME+1];
	for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
	{
		arrResult[i]		= 0;
		arrScore[i]			= 0;
		arrAttDataSize[i]	= 0;
	}
	memset(attData, -1, 64);
	m_wstr_last_recordinfo += L"\n\t],\n";//�ֿ�
	RoundRecord(true);
	pro_end_a_game_s pro_end;
	pro_end.init_data();
	if (m_current_player == 1)
	{
		arrResult[1]=1;
		arrResult[2]=2;
		arrScore[1]=m_players[0].m_check_hu[1] * m_players[0].m_double;
		arrScore[2]=-arrScore[1];
		pro_end.zimo_or_dianpao = m_players[0].m_current_status;
		if(m_players[0].m_hu_status == 1)
			m_players[0].SetResultFan(pro_end.fan[0],pro_end.fan[1],pro_end.fan[2],true);
		else if(m_players[0].m_hu_status == 2)
			m_players[0].SetResultFan(pro_end.fan[0],pro_end.fan[1],pro_end.fan[2],false);
		pro_end.total_fan = m_players[0].m_check_hu[1];
		pro_end.win_lose_point = arrScore[1];
	}
	else if (m_current_player == 2)
	{
		arrResult[1]=2;
		arrResult[2]=1;
		arrScore[2]=m_players[1].m_check_hu[1] * m_players[1].m_double;
		arrScore[1]=-arrScore[2];
		pro_end.zimo_or_dianpao = m_players[1].m_current_status;
		if(m_players[1].m_hu_status == 1)
			m_players[1].SetResultFan(pro_end.fan[0],pro_end.fan[1],pro_end.fan[2],true);
		else if(m_players[1].m_hu_status == 2)
			m_players[1].SetResultFan(pro_end.fan[0],pro_end.fan[1],pro_end.fan[2],false);
		pro_end.total_fan = m_players[1].m_check_hu[1];
		pro_end.win_lose_point = arrScore[2];
	}
	//CStringA log_str;log_str.Format("arrResult[1]:%d,arrResult[2]:%d,arrScore[1]��%lld,arrScore[2]:%lld",arrResult[1],arrResult[2],arrScore[1],arrScore[2]);WriteLog(log_str);
	//����һ����Ϸ����֪ͨ
	
	
	pro_end.hu_na_zhi = (char)(m_players[m_current_player-1].m_check_hu[0]);
	pro_end.seat_id1 = m_current_player;
	//��ǰ��ҵĳ����ܳ�����
	for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_chew_pong_kong.size();i++)
	{
		for (uint32_t j = 0; j < 3;j++)
		{
			pro_end.pai1[3*i+j] = (char)((m_players[m_current_player-1].m_pais_chew_pong_kong[i])[j].u32RealCard);
		}
		if (m_players[m_current_player-1].m_pais_chew_pong_kong[i].size() == 4 && m_players[m_current_player-1].m_pais_chew_pong_kong[i][0].u32Status == status_kong_self)
		{
			pro_end.index1[i]=2;
		}
		else if (m_players[m_current_player-1].m_pais_chew_pong_kong[i].size() == 4 && m_players[m_current_player-1].m_pais_chew_pong_kong[i][0].u32Status == status_kong_oppisite)
		{
			pro_end.index1[i]=1;
		}
		else
		{
			pro_end.index1[i]=0;
		}
	}
	pro_end.count1 = (char)(m_players[m_current_player-1].m_pais_chew_pong_kong.size());
	//��ǰ���ʣ�����ϵ���
	for (uint32_t i = 0; i < m_players[m_current_player-1].m_pais_in_hand.size();i++)
	{
		pro_end.pai1[pro_end.count1*3 + i] = (char)(m_players[m_current_player-1].m_pais_in_hand[i].u32RealCard);
	}
	if (m_players[m_current_player-1].m_current_status == 2)
	{
		pro_end.pai1[13] = (char)(m_players[m_current_player-1].m_last_pai);
	}
	
	pro_end.beishu = m_players[m_current_player-1].m_double;
	if (m_players[m_current_player-1].m_fan_helper.m_is_miao_shou_hui_chun)
	{
		pro_end.other_fan = 1;
	}
	if (m_players[m_current_player-1].m_fan_helper.m_is_hai_di_lao_yue)
	{
		pro_end.other_fan += 10;
	}
	if (m_players[m_current_player-1].m_fan_helper.m_is_gang_shang_kai_hua)
	{
		pro_end.other_fan += 100;
	}
	if (m_players[m_current_player-1].m_fan_helper.m_is_qiang_gang_hu)
	{
		pro_end.other_fan += 1000;
	}
	m_log_str.Format("���ı�����%d",pro_end.beishu);//WriteLog(m_log_str);
	m_log_str.Format("ʣ���ƣ�pai0:%d,pai1:%d,pai2:%d,pai3:%d,pai4:%d,pai5:%d,pai6:%d,pai7:%d,pai8:%d,pai9:%d,pai10:%d,pai11:%d,pai12:%d,pai13:%d",
		pro_end.pai1[0],pro_end.pai1[1],pro_end.pai1[2],pro_end.pai1[3],pro_end.pai1[4],pro_end.pai1[5],pro_end.pai1[6],pro_end.pai1[7],
		pro_end.pai1[8],pro_end.pai1[9],pro_end.pai1[10],pro_end.pai1[11],pro_end.pai1[12],pro_end.pai1[13]);//WriteLog(m_log_str);
	IMsgWriter *w = CreateMsgWriter();
	pro_end.ToWriter(w);
	for (uint32_t k = 1; k <= MAX_PLAYER_PER_GAME;k++)
	{
		m_pFrame->SendDataToPlayer(w,k);
	}
	//֪ͨ���ǰ���ͶԼ���
	pro_oppisite_left_cards oppisite_left_cards[2];
	for (uint32_t i = 0; i < m_players[0].m_pais_in_hand.size(); i++)
		oppisite_left_cards[0].pai[i] = m_players[0].m_pais_in_hand[i].u32RealCard;

	for (uint32_t i = 0; i < m_players[1].m_pais_in_hand.size(); i++)
		oppisite_left_cards[1].pai[i] = m_players[1].m_pais_in_hand[i].u32RealCard;

	oppisite_left_cards[0].ToWriter(w);
	m_pFrame->SendDataToPlayer(w,2);//��Ϊ�ǶԼ��ƣ����Խ��淢��

	oppisite_left_cards[1].ToWriter(w);
	m_pFrame->SendDataToPlayer(w,1);
	//arrResult = 0 ��ʾƽ =1 ��ʾwin =2 ��ʾ��
	//arrScore ��ʾ����ֵĵ÷� ������ʾ�����

	//if(esc < 0)
	m_pFrame->OnRoundEnd(MAX_PLAYER_PER_GAME, arrResult+1, arrScore+1, attData, arrAttDataSize+1);
	m_game_is_over = true;
	m_state = mj_s_preparing;
	w->Release();
}

void game_majong2::ProcessTingReq(uint32_t &index)
{
	m_log_str.Format("����ProcessTingReq");//WriteLog(m_log_str);
	m_players[m_current_player-1].ProcessTing(index);
	pro_ting_notify_s notify;
	IMsgWriter *w = CreateMsgWriter();
	notify.seat_id = m_current_player;notify.kind = 0;notify.ToWriter(w);
	for (uint32_t i = 1;i<=MAX_PLAYER_PER_GAME;i++)
	{
		m_pFrame->SendDataToPlayer(w,i);
	}
	w->Release();
	//�ֿ�
	wstring strCards;
	strCards = GetCardStr(index);
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"ting      \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
	//���������
	m_players[m_current_player-1].ClearAllJudge();
}

void game_majong2::ProcessFangQiReq(uint32_t index)
{
	m_log_str.Format("����ProcessFangQiReq");//WriteLog(m_log_str);
	m_players[m_current_player-1].ProcessFangQi();
	if(m_players[m_current_player-1].m_current_status == 2)//����״̬
	{
		//�����Լ�����
		m_players[m_current_player-1].SetMyZiMoStatus();
		SendACardNormal();
		ZiMoSendBtn();
	}
	else if (m_players[m_current_player-1].is_ting && m_players[m_current_player-1].m_current_status == 1)
	{
		ProcessOutCardReq(m_players[m_current_player-1].m_last_pai);//��״̬�����˷�����ӱ����������ץ����������
	}
	//�ֿ�
	wstring strCards;
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"fangqi    \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
}

void game_majong2::ProcessJiaBei(uint32_t index)
{
	m_players[m_current_player-1].ProcessJiaBei();
	if (m_players[m_current_player-1].m_current_status == 2)//����
	{
		//����
		SendACardNormal();
		m_players[m_current_player-1].SetMyZiMoStatus();
		ZiMoSendBtn();
	}
	else if (m_players[m_current_player-1].is_ting && m_players[m_current_player-1].m_current_status == 1)
	{
		ProcessOutCardReq(m_players[m_current_player-1].m_last_pai);//��״̬�����˷�����ӱ����������ץ����������
	}
	//�ֿ�
	wstring strCards;
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"jiabei    \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
}

void game_majong2::ProcessHuang()
{
	m_wstr_last_recordinfo += L"\n\t],\n";//�ֿ�
	//���ּ���
	//�ܷ� = ���� �� ���� �� ����
	//������͸���ܵ�����
	int				arrResult[MAX_PLAYER_PER_GAME+1];
	long long		arrScore[MAX_PLAYER_PER_GAME+1];
	char			attData[64];
	int				arrAttDataSize[MAX_PLAYER_PER_GAME+1];
	for(int i=1; i<=MAX_PLAYER_PER_GAME; i++)
	{
		arrResult[i]		= 0;
		arrScore[i]			= 0;
		arrAttDataSize[i]	= 0;
	}
	memset(attData, -1, 64);

	RoundRecord(false);
	//����һ����Ϸ����֪ͨ,�յ�����
	IMsgWriter *w = CreateMsgWriter();
	pro_end_a_game_s pro_end;
	pro_end.init_data();
	pro_end.ToWriter(w);
	for (uint32_t k = 1; k <= MAX_PLAYER_PER_GAME;k++)
	{
		m_pFrame->SendDataToPlayer(w,k);
	}

	pro_oppisite_left_cards oppisite_left_cards[2];
	for (uint32_t i = 0; i < m_players[0].m_pais_in_hand.size(); i++)
		oppisite_left_cards[0].pai[i] = m_players[0].m_pais_in_hand[i].u32RealCard;

	for (uint32_t i = 0; i < m_players[1].m_pais_in_hand.size(); i++)
		oppisite_left_cards[1].pai[i] = m_players[1].m_pais_in_hand[i].u32RealCard;

	oppisite_left_cards[0].ToWriter(w);
	m_pFrame->SendDataToPlayer(w,2);//��Ϊ�ǶԼ��ƣ����Խ��淢��

	oppisite_left_cards[1].ToWriter(w);
	m_pFrame->SendDataToPlayer(w,1);

	//arrResult = 0 ��ʾƽ =1 ��ʾwin =2 ��ʾ��
	//arrScore ��ʾ����ֵĵ÷� ������ʾ�����

	//if(esc < 0)
	m_pFrame->OnRoundEnd(MAX_PLAYER_PER_GAME, arrResult+1, arrScore+1, attData, arrAttDataSize+1);
	m_game_is_over = true;
	m_state = mj_s_preparing;
	w->Release();
	//�ֿ�
	wstring strCards;
	wchar_t buff[512];
	swprintf_s(buff, L"\n\t\t{\"type\":\"jiabei    \",\"time\":%I64d,\"seat\":%d,\"act\":%d,\"objects\":\"%s\"},", m_nLastPulseMS, m_current_player-1, m_players[m_current_player-1].is_auto ? 1 : 0, strCards.c_str());
	m_wstr_last_recordinfo += buff;
	//�ֿ�
}

void game_majong2::RoundRecord(bool bWin)
{
	if (bWin && m_current_player == 1)
	{
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_ISWIN,1);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_ISWIN,0);

		if (m_players[0].m_normal_fan_helper.GetZiMo())
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_HUPAI,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_HUPAI,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_HUPAI,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_HUPAI,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_DASIXI))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_DASIXI,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_DASIXI,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_DASIXI,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_DASIXI,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_DASANYUAN))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_DASANYUAN,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_DASANYUAN,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_DASANYUAN,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_DASANYUAN,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_LVYISE))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_LUYISE,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_LUYISE,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_LUYISE,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_LUYISE,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_JIULIANBAODENG))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_JIUBAOLIANDENG,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_JIUBAOLIANDENG,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_JIUBAOLIANDENG,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_JIUBAOLIANDENG,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_SIGANG))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_SIGANG,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_SIGANG,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_SIGANG,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_SIGANG,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_LIANQIDUI))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_LIAQIDUI,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_LIAQIDUI,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_LIAQIDUI,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_LIAQIDUI,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_MIAOSHOUHUICHUN))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MISHUCHUN,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MISHUCHUN,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MISHUCHUN,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MISHUCHUN,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_HAIDILAOYUE))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_HADILAYUE,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_HADILAYUE,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_HADILAYUE,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_HADILAYUE,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_GANGSHANGKAIHUA))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_GASKAHUA,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_GASKAHUA,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_GASKAHUA,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_GASKAHUA,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_PENGPENGHU))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_PPHU,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_PPHU,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_PPHU,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_PPHU,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_QINGYISE))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_QINGYISE,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_QINGYISE,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_QINGYISE,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_QINGYISE,0);
		}

		if(m_players[0].m_normal_fan_helper.GetSomeFan(ID_FAN_QINGLONG))
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_QINGLONG,1);//���������
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_QINGLONG,1);
		}
		else
		{
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_QINGLONG,0);
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_QINGLONG,0);
		}

		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_FANNUMBER,m_players[0].m_normal_fan_helper.CountFan());//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_FANNUMBER,m_players[0].m_normal_fan_helper.CountFan());

		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MIGANGNUMBER,m_players[0].m_an_gang_count + m_players[0].m_ming_gang_count2);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MIGANGNUMBER,m_players[0].m_an_gang_count + m_players[0].m_ming_gang_count2);

		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_ANGANGNUMBER,m_players[0].m_ming_gang_count1);//��������ã���ǰ���õ���1���ǰ��ܣ�����Ϊ��1���������õ�ʱ��ע���»�����
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_ANGANGNUMBER,m_players[0].m_ming_gang_count1);

		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MULTIPLE,m_players[0].m_double);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MULTIPLE,m_players[0].m_double);
	}
	else if (bWin && m_current_player == 2)
	{
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_ISWIN,1);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_ISWIN,0);

		if (m_players[1].m_normal_fan_helper.GetZiMo())
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_HUPAI,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_HUPAI,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_HUPAI,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_HUPAI,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_DASIXI))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_DASIXI,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_DASIXI,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_DASIXI,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_DASIXI,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_DASANYUAN))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_DASANYUAN,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_DASANYUAN,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_DASANYUAN,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_DASANYUAN,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_LVYISE))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_LUYISE,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_LUYISE,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_LUYISE,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_LUYISE,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_JIULIANBAODENG))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_JIUBAOLIANDENG,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_JIUBAOLIANDENG,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_JIUBAOLIANDENG,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_JIUBAOLIANDENG,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_SIGANG))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_SIGANG,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_SIGANG,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_SIGANG,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_SIGANG,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_LIANQIDUI))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_LIAQIDUI,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_LIAQIDUI,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_LIAQIDUI,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_LIAQIDUI,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_MIAOSHOUHUICHUN))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MISHUCHUN,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MISHUCHUN,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MISHUCHUN,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MISHUCHUN,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_HAIDILAOYUE))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_HADILAYUE,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_HADILAYUE,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_HADILAYUE,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_HADILAYUE,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_GANGSHANGKAIHUA))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_GASKAHUA,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_GASKAHUA,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_GASKAHUA,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_GASKAHUA,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_PENGPENGHU))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_PPHU,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_PPHU,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_PPHU,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_PPHU,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_QINGYISE))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_QINGYISE,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_QINGYISE,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_QINGYISE,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_QINGYISE,0);
		}

		if(m_players[1].m_normal_fan_helper.GetSomeFan(ID_FAN_QINGLONG))
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_QINGLONG,1);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_QINGLONG,1);
		}
		else
		{
			SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_QINGLONG,0);//���������
			SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_QINGLONG,0);
		}

		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_FANNUMBER,m_players[1].m_normal_fan_helper.CountFan());//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_FANNUMBER,m_players[1].m_normal_fan_helper.CountFan());

		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MIGANGNUMBER,m_players[1].m_an_gang_count + m_players[1].m_ming_gang_count2);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MIGANGNUMBER,m_players[1].m_an_gang_count + m_players[1].m_ming_gang_count2);

		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_ANGANGNUMBER,m_players[1].m_ming_gang_count1);//���������,��ǰ���õ���1���ǰ��ܣ�����Ϊ��1���������õ�ʱ��ע���»�����
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_ANGANGNUMBER,m_players[1].m_ming_gang_count1);

		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MULTIPLE,m_players[1].m_double);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MULTIPLE,m_players[1].m_double);
	}
	else
	{
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_ISWIN,2);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_ISWIN,2);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_HUPAI,2);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_HUPAI,2);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MULTIPLE,1);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MULTIPLE,1);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_FANNUMBER,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_FANNUMBER,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_DASIXI,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_DASIXI,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_DASANYUAN,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_DASANYUAN,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_LUYISE,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_LUYISE,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_JIUBAOLIANDENG,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_JIUBAOLIANDENG,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_SIGANG,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_SIGANG,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_LIAQIDUI,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_LIAQIDUI,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MISHUCHUN,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MISHUCHUN,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_HADILAYUE,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_HADILAYUE,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_GASKAHUA,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_GASKAHUA,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_PPHU,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_PPHU,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_QINGYISE,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_QINGYISE,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_QINGLONG,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_QINGLONG,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_MIGANGNUMBER,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_MIGANGNUMBER,0);//���������
		SetRoundFeatures(0,TASK_MAHJONG_CONFIGID_ANGANGNUMBER,0);//���������
		SetRoundFeatures(1,TASK_MAHJONG_CONFIGID_ANGANGNUMBER,0);//���������
	}
}
