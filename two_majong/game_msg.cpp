#include "game_msg.h"

bool pro_game_begin_s::FromReader(IMsgReader *r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_GAME_BEGIN);
	CHECK_FIELD_INT32(r,0,money_rate);
	CHECK_FIELD_INT32(r,1,score_rate);
	CHECK_FIELD_INT32(r,2,shaizi[0]);
	CHECK_FIELD_INT32(r,3,shaizi[1]);
	CHECK_FIELD_INT32(r,4,shaizi[2]);
	CHECK_FIELD_INT32(r,5,shaizi[3]);
	CHECK_FIELD_INT32(r,6,svr_seat_id);
	CHECK_FIELD_INT32(r,7,is_banker);
	return true;
}

void pro_game_begin_s::ToWriter(IMsgWriter *w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_GAME_BEGIN );
	w->SetInt32(0, money_rate);
	w->SetInt32(1, score_rate);
	w->SetInt32(2, shaizi[0]);
	w->SetInt32(3, shaizi[1]);
	w->SetInt32(4, shaizi[2]);
	w->SetInt32(5, shaizi[3]);
	w->SetInt32(6, svr_seat_id);
	w->SetInt32(7, is_banker);
}

bool pro_group_send_pai_s::FromReader( IMsgReader*  r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_GROUP_SEND_PAI);
	CHECK_FIELD_INT32(r,0,seat_id);
	memset ( pais, 0, sizeof ( pais ) );
	memcpy ( pais, r->AsAnsiString ( 1 ), 13 );
	return true;
}
void pro_group_send_pai_s::ToWriter( IMsgWriter * w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_GROUP_SEND_PAI );
	w->SetInt32(0,seat_id);
	w->SetBuffer(1, 13, pais);
}
bool pro_same_with_svr::FromReader( IMsgReader*  r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_SAME_WITH_SVR);
	CHECK_FIELD_INT32(r,0,seat_id);
	memset ( pais, 0, sizeof ( pais ) );
	memcpy ( pais, r->AsAnsiString ( 1 ), 14 );
	memset ( &index, 0, sizeof ( index ) );
	memcpy ( &index, r->AsAnsiString ( 2 ), 1 );
	return true;
}
void pro_same_with_svr::ToWriter( IMsgWriter * w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_SAME_WITH_SVR );
	w->SetInt32(0,seat_id);
	w->SetBuffer(1, 14, pais);
	w->SetBuffer(2,	1,&index);
}
bool pro_single_send_pai_s::FromReader( IMsgReader* r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_SINGLE_SEND_PAI);
	CHECK_FIELD_INT32(r,0,seat_id);
	memset ( &pai, 0, sizeof ( &pai ) );
	memcpy ( &pai, r->AsAnsiString ( 1 ), 1 );
	return true;
}
void pro_single_send_pai_s::ToWriter( IMsgWriter * w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_SINGLE_SEND_PAI );
	w->SetInt32(0,seat_id);
	w->SetBuffer(1, 1, &pai);
}
bool pro_add_flower_count::FromReader( IMsgReader* r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_ADD_FLOWER);
	CHECK_FIELD_INT32(r,0,seat_id);
	memset ( &total_flowers, 0, sizeof ( &total_flowers ) );
	memcpy ( &total_flowers, r->AsAnsiString ( 1 ), 1 );
	return true;
}
void pro_add_flower_count::ToWriter( IMsgWriter * w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_ADD_FLOWER );
	w->SetInt32(0, seat_id);
	w->SetBuffer(1, 1, &total_flowers);
}

bool pro_update_table_ungot_cards_s::FromReader( IMsgReader* r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_UPDATE_TABLE_UNGOT_CARDS);
	CHECK_FIELD_INT32(r,0,normal_count);
	CHECK_FIELD_INT32(r,1,reverse_count);
	CHECK_FIELD_INT32(r,2,kind);
	return true;
}

void pro_update_table_ungot_cards_s::ToWriter( IMsgWriter * w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_UPDATE_TABLE_UNGOT_CARDS );
	w->SetInt32(0, normal_count);
	w->SetInt32(1, reverse_count);
	w->SetInt32(2, kind);
}

bool usual_btn_send::FromReader( IMsgReader* r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_BTN_SEND);
	memset ( &btn_flag, 0, sizeof ( &btn_flag ) );
	memcpy ( &btn_flag, r->AsAnsiString ( 1 ), 1 );
	memset ( &last_pai, 0, sizeof ( &last_pai ) );
	memcpy ( &last_pai, r->AsAnsiString ( 2 ), 1 );
	memset ( &special_fan_for_hu, 0, sizeof ( &special_fan_for_hu ) );
	memcpy ( &special_fan_for_hu, r->AsAnsiString ( 3 ), 1 );
	return true;
}

void usual_btn_send::ToWriter( IMsgWriter * w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_BTN_SEND );
	w->SetBuffer(1, 1, &btn_flag);
	w->SetBuffer(2, 1, &last_pai);
	w->SetBuffer(3, 1, &special_fan_for_hu);
}

bool pro_click_btn_c::FromReader( IMsgReader* r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_CLICK_CHEW_AND_SO_ON_BTN);
	CHECK_FIELD_INT32(r,0,seat_id);
	memset ( &kind,			0,						sizeof (kind)  );
	memcpy ( &kind,			r->AsAnsiString ( 1 ),  1 );
	memset ( &index,		0,						sizeof (index)  );
	memcpy ( &index,		r->AsAnsiString ( 2 ),  1 );
	return true;
}
void pro_click_btn_c::ToWriter(IMsgWriter *w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_CLICK_CHEW_AND_SO_ON_BTN );
	w->SetInt32(0, seat_id);
	w->SetBuffer(1, 1,  &kind);
	w->SetBuffer(2, 1,  &index);
}

bool pro_out_card_notify_s::FromReader( IMsgReader* r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_OUT_CARD_NOTIFY);
	CHECK_FIELD_INT32(r,0,seat_id);
	CHECK_FIELD_INT32(r,1,kind);
	CHECK_FIELD_INT32(r,2,pai[0]);
	CHECK_FIELD_INT32(r,3,pai[1]);
	CHECK_FIELD_INT32(r,4,pai[2]);
	CHECK_FIELD_INT32(r,5,pai[3]);
	return true;
}

void pro_out_card_notify_s::ToWriter( IMsgWriter * w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_OUT_CARD_NOTIFY );
	w->SetInt32(0, seat_id);
	w->SetInt32(1, kind);
	w->SetInt32(2, pai[0]);
	w->SetInt32(3, pai[1]);
	w->SetInt32(4, pai[2]);
	w->SetInt32(5, pai[3]);
}

void pro_end_a_game_s::init_data()
{
	hu_na_zhi = 0;
	seat_id1 = 0;
	count1 = 0;
	beishu = 1;
	other_fan = 0;
	for(uint32_t i = 0; i < 14;i++)
	{
		pai1[i] = 0;
	}
	for (uint32_t i = 0; i < 4;i++)
	{
		index1[i] = 0;
	}
	zimo_or_dianpao = 0;
	for (uint32_t i = 0; i < 3; i++)
	{
		fan[i] = 0;
	}
	total_fan = 0;
	win_lose_point = 0;
}

bool pro_end_a_game_s::FromReader( IMsgReader* r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_END_GAME);
	memset ( &hu_na_zhi,			0,						sizeof (hu_na_zhi)  );
	memcpy ( &hu_na_zhi,			r->AsAnsiString ( 0 ),  1 );
	CHECK_FIELD_INT32(r,1,seat_id1);
	memset ( pai1,			0,						sizeof (pai1)  );
	memcpy ( pai1,			r->AsAnsiString ( 2 ),  14 );
	memset ( &count1,			0,						sizeof (count1)  );
	memcpy ( &count1,			r->AsAnsiString ( 3 ),  1 );
	memset ( index1,			0,						sizeof (index1)  );
	memcpy ( index1,			r->AsAnsiString ( 4 ),  4 );
	CHECK_FIELD_INT32(r,5,beishu);
	CHECK_FIELD_INT32(r,6,other_fan);
	memset(&zimo_or_dianpao,0,sizeof(zimo_or_dianpao));
	memcpy(&zimo_or_dianpao,r->AsAnsiString(7),1);
	CHECK_FIELD_INT32(r,8,fan[0]);
	CHECK_FIELD_INT32(r,9,fan[1]);
	CHECK_FIELD_INT32(r,10,fan[2]);
	CHECK_FIELD_INT32(r,11,total_fan);
	CHECK_FIELD_INT64(r,12,win_lose_point);
	return true;
}

void pro_end_a_game_s::ToWriter( IMsgWriter * w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_END_GAME );
	w->SetBuffer(0, 1, &hu_na_zhi);
	w->SetInt32(1,seat_id1);
	w->SetBuffer(2, 14, pai1);
	w->SetBuffer(3, 1,  &count1);
	w->SetBuffer(4, 4, index1);
	w->SetInt32(5,beishu);
	w->SetInt32(6,other_fan);
	w->SetBuffer(7,1,&zimo_or_dianpao);
	w->SetInt32(8,fan[0]);
	w->SetInt32(9,fan[1]);
	w->SetInt32(10,fan[2]);
	w->SetInt32(11,total_fan);
	w->SetInt64(12,win_lose_point);
}

bool pro_oppisite_left_cards::FromReader( IMsgReader* r)
{
	if ( MKD_MAJONG2 != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_OPPISITE_LEFT_CARD);
	memset ( pai,0,sizeof ( pai)  );
	memcpy ( pai,r->AsAnsiString ( 0 ), 14 );
	return true;
}
void pro_oppisite_left_cards::ToWriter( IMsgWriter * w)
{
	w->SetMessageKind ( MKD_MAJONG2 );
	w->SetMessageId ( PRO_OPPISITE_LEFT_CARD );
	w->SetBuffer(0, 14, pai);
}

bool pro_turn_current_player_s::FromReader(IMsgReader *r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_TURN_CURRENT_PLAYER);
	CHECK_FIELD_INT32(r,0,current_player_seat_id);
	return true;
}
void pro_turn_current_player_s::ToWriter(IMsgWriter *w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_TURN_CURRENT_PLAYER );
	w->SetInt32(0,current_player_seat_id);
}

bool pro_ting_notify_s::FromReader( IMsgReader* r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_SEND_TING_NOTIFY);
	CHECK_FIELD_INT32(r,0,seat_id);
	CHECK_FIELD_INT32(r,1,kind);
	return true;
}
void pro_ting_notify_s::ToWriter( IMsgWriter * w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_SEND_TING_NOTIFY );
	w->SetInt32(0,seat_id);
	w->SetInt32(1,kind);
}

bool pro_game_data_reply::FromReader( IMsgReader *r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	CHECK_MSGID(r,PRO_GAME_DATA_REPLY);
	CHECK_FIELD_INT32(r,0,state);
	CHECK_FIELD_INT32(r,1,current_player);
	CHECK_FIELD_INT32(r,2,timeout);
	CHECK_FIELD_INT32(r,3,banker);
	CHECK_FIELD_INT32(r,4,multiple);

	memset ( plrdata.my_chi_peng_gang,			0,						sizeof ( plrdata.my_chi_peng_gang)  );
	memcpy ( plrdata.my_chi_peng_gang,			r->AsAnsiString ( 5 ),  20 );
	memset ( plrdata.my_out_cards,				0,						sizeof ( plrdata.my_out_cards)  );
	memcpy ( plrdata.my_out_cards,				r->AsAnsiString ( 6 ),	20 );
	memset ( plrdata.oppisite_chi_peng_gang,	0,						sizeof ( plrdata.oppisite_chi_peng_gang)  );
	memcpy ( plrdata.oppisite_chi_peng_gang,	r->AsAnsiString ( 7 ),	20 );
	memset ( plrdata.oppisite_out_cards,		0,						sizeof ( plrdata.oppisite_out_cards)  );
	memcpy ( plrdata.oppisite_out_cards,		r->AsAnsiString ( 8 ),	20 );
	memset ( plrdata.my_cards_group,			0,						sizeof ( plrdata.my_cards_group)  );
	memcpy ( plrdata.my_cards_group,			r->AsAnsiString ( 9 ),	14 );
	memset ( plrdata.table_update,				0,						sizeof ( plrdata.table_update)  );
	memcpy ( plrdata.table_update,				r->AsAnsiString ( 10 ), 4 );
	memset ( &(plrdata.my_flowers_count),		0,						sizeof ( plrdata.my_flowers_count)  );
	memcpy ( &(plrdata.my_flowers_count),		r->AsAnsiString ( 11 ), 1 );
	memset ( &(plrdata.oppisite_card_count),	0,						sizeof ( plrdata.oppisite_card_count)  );
	memcpy ( &(plrdata.oppisite_card_count),	r->AsAnsiString ( 12 ), 1 );
	memset ( &(plrdata.oppisite_flower_count),	0,						sizeof ( plrdata.oppisite_flower_count)  );
	memcpy ( &(plrdata.oppisite_flower_count),	r->AsAnsiString ( 13 ), 1 );
	memset ( &(plrdata.is_tuo_guan),			0,						sizeof ( plrdata.is_tuo_guan)  );
	memcpy ( &(plrdata.is_tuo_guan),			r->AsAnsiString ( 14 ), 1 );

	CHECK_FIELD_INT32(r,15,my_seat_id);
	return true;
}
void pro_game_data_reply::ToWriter( IMsgWriter *w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_GAME_DATA_REPLY );
	w->SetInt32(0,state);
	w->SetInt32(1,current_player);
	w->SetInt32(2,timeout);
	w->SetInt32(3,banker);
	w->SetInt32(4,multiple);

	w->SetBuffer(5, 20, plrdata.my_chi_peng_gang);
	w->SetBuffer(6, 20, plrdata.my_out_cards);
	w->SetBuffer(7, 20, plrdata.oppisite_chi_peng_gang);
	w->SetBuffer(8, 20, plrdata.oppisite_out_cards);
	w->SetBuffer(9, 14, plrdata.my_cards_group);
	w->SetBuffer(10, 4, plrdata.table_update);
	w->SetBuffer(11, 1, &(plrdata.my_flowers_count));
	w->SetBuffer(12, 1, &(plrdata.oppisite_card_count));
	w->SetBuffer(13, 1, &(plrdata.oppisite_flower_count));
	w->SetBuffer(14, 1, &(plrdata.is_tuo_guan));

	w->SetInt32(15, my_seat_id);
}

bool pro_game_data_req::FromReader( IMsgReader *r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	if ( PRO_GAME_DATA_REQ != r->MessageId() )
		return false;

	return true;
}
void pro_game_data_req::ToWriter( IMsgWriter *w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_GAME_DATA_REQ );
}
bool pro_expression::FromReader( IMsgReader *r)
{
	if ( MKD_DDZ != r->MessageKind() )
		return false;
	if ( PRO_EXPRESSION != r->MessageId() )
		return false;


	if ( !r->FieldExist ( 0 ) || !r->FieldExist ( 1 ))
		return false;

	if ( 4 != r->FieldSize ( 0 ) || MFT_INT32 != r->FieldType ( 0 ) ) return false;
	seatid = r->AsInt32 ( 0 );

	if ( 4 != r->FieldSize ( 1 ) || MFT_INT32 != r->FieldType ( 1 ) ) return false;
	expressionid = r->AsInt32 ( 1 );

	return true;
}
void pro_expression::ToWriter( IMsgWriter *w)
{
	w->SetMessageKind ( MKD_DDZ );
	w->SetMessageId ( PRO_EXPRESSION );

	w->SetInt32(0, seatid);
	w->SetInt32(1, expressionid);
}
