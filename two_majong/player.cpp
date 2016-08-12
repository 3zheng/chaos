#include "player.h"

//排序手上的牌，依据真值由小到大
void player::HandPaiSort()
{
	pai_kind temp;
	for(uint32_t i = 0; i < m_pais_in_hand.size() - 1;i++)
	{
		for (uint32_t j = i + 1; j < m_pais_in_hand.size(); j++)
		{
			if (m_pais_in_hand[i].u32ValueCard > m_pais_in_hand[j].u32ValueCard)
			{
				temp = m_pais_in_hand[i];
				m_pais_in_hand[i] = m_pais_in_hand[j];
				m_pais_in_hand[j] = temp;
			}
		}
	}
}
//新一局游戏开始时调用初始化每个玩家
void player::on_new_game()	// 开始一局游戏时调用
{
	is_auto = false;
	is_drop = false;
	m_pais_in_hand.clear();
	m_pais_on_table.clear();
	m_pais_chew_pong_kong.clear();
	m_pais_flowers.clear();
	m_ting_cards.clear();
	is_ting = false;
	m_double = 1;
	m_ming_gang_count1 = 0;
	m_ming_gang_count2 = 0;
	m_an_gang_count = 0;

	LoadChewTable();
	m_last_pai = id_unknown;
	ClearAllJudge();
	JIANG = 0;
	m_oppisite_player = NULL;
	m_current_status = 0;
	m_is_get_a_card = true;
	m_is_jia_bei_check_ting = false;

	
	m_fan_helper.m_is_miao_shou_hui_chun = false;
	m_fan_helper.m_is_gang_shang_kai_hua = false;
	m_fan_helper.m_is_hai_di_lao_yue = false;
	m_fan_helper.m_is_qiang_gang_hu = false;
	m_hu_clock_when_is_ting = 0;
	m_miao_shou_hui_chun = false;		// 四种特殊番型：妙手回春
	m_hai_di_lao_yue = false;			// 四种特殊番型：海底捞月
	m_gang_shang_kai_hua = false;		// 四种特殊番型：杠上开花
	m_qiang_gang_hu = false;			// 四种特殊番型：抢杠胡
	m_flag_for_ming_an[0] = 0;
	m_flag_for_ming_an[1] = 0;
	m_flag_for_ming_an[2] = 0;
	m_flag_for_ming_an[3] = 0;
}
//载入吃型表
void player::LoadChewTable()
{
	std::vector<chew_struct_data> vec_data;
	chew_struct_data chew_data;
	//一条
	vec_data.clear();
	chew_data.pai1 = value_bamboo_2;
	chew_data.pai2 = value_bamboo_3;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_1,vec_data));
	//二条
	vec_data.clear();
	chew_data.pai1 = value_bamboo_1;
	chew_data.pai2 = value_bamboo_3;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_3;
	chew_data.pai2 = value_bamboo_4;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_2,vec_data));
	//三条
	vec_data.clear();
	chew_data.pai1 = value_bamboo_1;
	chew_data.pai2 = value_bamboo_2;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_2;
	chew_data.pai2 = value_bamboo_4;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_4;
	chew_data.pai2 = value_bamboo_5;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_3,vec_data));
	//四条
	vec_data.clear();
	chew_data.pai1 = value_bamboo_2;
	chew_data.pai2 = value_bamboo_3;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_3;
	chew_data.pai2 = value_bamboo_5;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_5;
	chew_data.pai2 = value_bamboo_6;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_4,vec_data));
	//五条
	vec_data.clear();
	chew_data.pai1 = value_bamboo_3;
	chew_data.pai2 = value_bamboo_4;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_4;
	chew_data.pai2 = value_bamboo_6;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_6;
	chew_data.pai2 = value_bamboo_7;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_5,vec_data));
	//六条
	vec_data.clear();
	chew_data.pai1 = value_bamboo_4;
	chew_data.pai2 = value_bamboo_5;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_5;
	chew_data.pai2 = value_bamboo_7;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_7;
	chew_data.pai2 = value_bamboo_8;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_6,vec_data));
	//七条
	vec_data.clear();
	chew_data.pai1 = value_bamboo_5;
	chew_data.pai2 = value_bamboo_6;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_6;
	chew_data.pai2 = value_bamboo_8;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_8;
	chew_data.pai2 = value_bamboo_9;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_7,vec_data));
	//八条
	vec_data.clear();
	chew_data.pai1 = value_bamboo_6;
	chew_data.pai2 = value_bamboo_7;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_7;
	chew_data.pai2 = value_bamboo_9;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_8,vec_data));
	//九条
	vec_data.clear();
	chew_data.pai1 = value_bamboo_7;
	chew_data.pai2 = value_bamboo_8;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_9,vec_data));
}
//清除所有的判断表,调用CheckAllJudge前先调用此函数，以清除前一次的
void player::ClearAllJudge()													
	{
		//清理判断的暂存列表
		m_vec_check_chew.clear();
		m_vec_check_peng.clear();
		m_vec_check_an_gang.clear();
		m_vec_check_ming_gang1.clear();
		m_vec_check_ming_gang2.clear();
		for (uint32_t i = 0; i < 2; i++)
		{
			for (uint32_t j = 0; j < 16; j++)
			{
				for (uint32_t k = 0; k < 16; k++)
				{
					m_check_ting[i][j][k]=value_unknown;
				}
			}
		}
		for (uint32_t i = 0; i < 2; i++)
		{
			m_check_hu[i]=id_unknown;
		}
		//清理标记列表
		for (uint32_t i = 0; i < 7; i++)
		{
			m_judge_flag[i] = 0;
		}
	}
//检测所有
void player::CheckAllJudge()
{
	ClearAllJudge();
	CStringA log_str;log_str.Format(" 进入CheckAllJudge函数,m_current_status=%d",m_current_status);//WriteLog(log_str);
	
	if (is_ting)//已经听了就只检查胡
	{
		log_str.Format(" is_ting=true");//WriteLog(log_str);
		CheckHu();
		if (m_check_hu[0] != id_unknown)//听了可胡，开启标记10秒左右
		{
			m_hu_clock_when_is_ting = 0;
		}
		return;
	}
	//else if (is_auto)//若不是听，只是托管，什么提示都不给，直接发牌打牌
	//{
	//	log_str.Format(" is_auto=true");WriteLog(log_str);
	//	return;
	//}
	if (m_current_status == 1)
	{
		CheckMingGang1();
		CheckMingGang2();
		if(!is_auto)
			CheckTing();
	}
	else if(m_current_status == 2)
	{
		CheckChi();
		CheckPeng();
		CheckAnGang();
	}
	if (!m_is_jia_bei_check_ting)
	{
		log_str.Format(" m_is_jia_bei_check_ting=false");//WriteLog(log_str);
		CheckHu();
	}
	//点了放弃或加倍后，此变量变成了true，直接下次不会检查胡，但是在检查完后立刻置为false，就不会影响到以后的检测
	m_is_jia_bei_check_ting = false;
	
	log_str.Format("出来CheckAllJudge函数,m_judge_flag[6]=%d,m_judge_flag[5]=%d",m_judge_flag[6],m_judge_flag[5]);//WriteLog(log_str);
}
//检测吃
void player::CheckChi()
{
	pai_kind pai_kind_;
	uint32_t u32Value = pai_kind_.GetValueFromRealCard(m_last_pai);
	if ( u32Value > value_bamboo_9 || u32Value < value_bamboo_1)
		return ;

	std::map<uint32_t,std::vector<chew_struct_data>>::iterator iter = m_map_table_for_chew.find(u32Value);
	if (iter  == m_map_table_for_chew.end())
		return ;

	chew_struct_data temp_data;
	for (uint32_t i = 0; i < iter->second.size();i++)//遍历可吃表
	{
		temp_data.init();
		for (uint32_t j = 0; j < m_pais_in_hand.size();j++)//遍历手中牌
		{
			if (m_pais_in_hand[j].u32ValueCard == iter->second[i].pai1)
			{
				temp_data.pai1 = m_pais_in_hand[j].u32RealCard;
				continue;
			}
			if ( temp_data.pai1 != id_unknown && m_pais_in_hand[j].u32ValueCard == iter->second[i].pai2)
			{
				temp_data.pai2 = m_pais_in_hand[j].u32RealCard;
				if (temp_data.pai1 != id_unknown && temp_data.pai2 != id_unknown)
				{
					temp_data.pai3 = m_last_pai;
					m_vec_check_chew.push_back(temp_data);
				}
				break;
			}
		}
	}
	if (m_vec_check_chew.size() > 0)
	{
		m_judge_flag[0]++;
	}	
}
//检测碰
void player::CheckPeng()
{
	pai_kind pai_kind_;
	uint32_t u32Value = pai_kind_.GetValueFromRealCard(m_last_pai);
	uint32_t count = 0;
	chew_struct_data temp_data;
	temp_data.init();
	for (uint32_t i = 0; i < m_pais_in_hand.size(); i++)
	{
		if (u32Value != m_pais_in_hand[i].u32ValueCard)
		{
			continue;
		}
		count++;
		if (temp_data.pai1 == id_unknown)
		{
			temp_data.pai1 = m_pais_in_hand[i].u32RealCard;
		}
		else
		{
			temp_data.pai2 = m_pais_in_hand[i].u32RealCard;
		}
		if (count>=2)
		{
			temp_data.pai3 = m_last_pai;
			m_vec_check_peng.push_back(temp_data);
			m_judge_flag[1]++;
			break;
		}
	}
}
//检测暗杠
void player::CheckAnGang()
{
	pai_kind pai_kind_;
	uint32_t u32Value = pai_kind_.GetValueFromRealCard(m_last_pai);
	uint32_t count = 0;
	chew_struct_data temp_data;
	temp_data.init();
	for (uint32_t i = 0; i < m_pais_in_hand.size();i++)
	{
		if (u32Value != m_pais_in_hand[i].u32ValueCard)
		{
			continue;
		}
		count++;
		if (temp_data.pai1 == id_unknown)
		{
			temp_data.pai1 = m_pais_in_hand[i].u32RealCard;
		}
		else if(temp_data.pai2 == id_unknown)
		{
			temp_data.pai2 = m_pais_in_hand[i].u32RealCard;
		}
		else
		{
			temp_data.pai3 = m_pais_in_hand[i].u32RealCard;
		}
		if (count>=3)
		{
			temp_data.pai4 = m_last_pai;
			m_vec_check_an_gang.push_back(temp_data);
			m_judge_flag[2]++;
			break;
		}
	}
}
//检测明杠1
void player::CheckMingGang1()
{
	uint32_t count = 0;
	chew_struct_data temp_data;
	for(uint32_t i = value_bamboo_1; i < value_flower; i++)
	{
		temp_data.init();
		count = 0;
		for (uint32_t j = 0; j < m_pais_in_hand.size();j++)
		{
			if (i == m_pais_in_hand[j].u32ValueCard)
			{
				count++;//四张牌不分前后
				if (temp_data.pai1 == id_unknown)
				{
					temp_data.pai1 = m_pais_in_hand[j].u32RealCard;
				}
				else if(temp_data.pai2 == id_unknown)
				{
					temp_data.pai2 = m_pais_in_hand[j].u32RealCard;
				}
				else if(temp_data.pai3 == id_unknown)
				{
					temp_data.pai3 = m_pais_in_hand[j].u32RealCard;
				}
				else
				{
					temp_data.pai4 = m_pais_in_hand[j].u32RealCard;
				}
			}
		}
		if (count >= 4)
		{
			m_vec_check_ming_gang1.push_back(temp_data);
			m_judge_flag[3]++;
		}
	}
}
//检测明杠2
void player::CheckMingGang2()
{
	uint32_t pongs[4] = {0};
	for (uint32_t i = 0; i < m_pais_chew_pong_kong.size();i++)
	{
		if (m_pais_chew_pong_kong[i].size() > 0)
		{
			if(m_pais_chew_pong_kong[i][0].u32ValueCard == m_pais_chew_pong_kong[i][1].u32ValueCard)
			{
				pongs[i] =m_pais_chew_pong_kong[i][0].u32ValueCard;
			}
		}
	}
	chew_struct_data temp_data;

	for (int i = 0; i < 4; i++)
	{
		temp_data.init();
		if (pongs[i] <= 0)
		{
			continue;
		}
		for (uint32_t j = 0; j <m_pais_in_hand.size(); j++)
		{
			if (m_pais_in_hand[j].u32ValueCard == pongs[i])
			{
				temp_data.pai1 = m_pais_in_hand[j].u32RealCard;
				m_vec_check_ming_gang2.push_back(temp_data);
				m_judge_flag[4]++;
				break;
			}
		}
	}
}
//检测胡
void player::CheckHu()
{
	m_hu_status = 0;//先给默认值
	//普通胡
	pai_kind pai_kind_;
	uint32_t PAI[16] = {0};
	uint32_t tempPAI[16]={0};//用作除了基本胡型外的其他胡型
	for (uint32_t i = 0; i < m_pais_in_hand.size(); i++)
	{
		if (m_pais_in_hand[i].u32ValueCard == value_flower)
		{
			return;//有花不能胡
		}
		if (m_pais_in_hand[i].u32ValueCard-1 > 15 || m_pais_in_hand[i].u32ValueCard-1 < 0)
		{
			CStringA log_str;log_str.Format("i>=16,m_pais_in_hand[i].u32ValueCard-1 = %d",m_pais_in_hand[i].u32ValueCard-1);WriteLog(log_str);
			return;
		}
		PAI[m_pais_in_hand[i].u32ValueCard-1]++;
	}
	if (m_current_status == 2)
	{
		if (pai_kind_.GetValueFromRealCard(m_last_pai) - 1 > 15 || pai_kind_.GetValueFromRealCard(m_last_pai)-1 < 0)
		{
			CStringA log_str;log_str.Format("i>=16,pai_kind_.GetValueFromRealCard(m_last_pai) - 1=%d",pai_kind_.GetValueFromRealCard(m_last_pai) - 1);WriteLog(log_str);
			return;
		}
		PAI[pai_kind_.GetValueFromRealCard(m_last_pai) - 1]++;
	}

	for (uint32_t i = 0; i < 16; i++)
	{
		tempPAI[i] = PAI[i];
	}
	JIANG = 0;
	if(Hu(PAI))
	{
		m_check_hu[0] = m_last_pai;
		//m_check_hu[1] = GetHuFan();
		//使用改进后的番型计算器
		PreProcess();
		int fan = m_normal_fan_helper.CountFan();
		m_check_hu[1] = fan;
		//CStringA log_str;log_str.Format("新番型计算器计算的番数：%d",fan);WriteLog(log_str);
		//
		m_judge_flag[6] = 1;//胡只有一个
		m_hu_status = 1;
	}
	else
	{
		//增加其他胡的牌型
		//七对
		if(m_pais_chew_pong_kong.size()>0)
		{
			return;//只要有吃碰杠的，就不是七对
		}
		uint32_t pair_count = 0;
		for (uint32_t i = value_bamboo_1; i <= value_white_dragon; i++)
		{
			if (tempPAI[i-1] == 2)
			{
				pair_count++;
			}
			if (tempPAI[i-1] == 4)
			{
				pair_count += 2;//此段只为四个头判定为两对
			}
		}
		if (pair_count == 7)
		{
			m_check_hu[0] = m_last_pai;
			//m_check_hu[1] = GetHuFan();
			m_judge_flag[6] = 1;//胡只有一个
			//使用改进后的番型计算器
			PreProcess2(tempPAI);
			int fan = m_qidui_fan_helper.CountFan();
			m_check_hu[1] = fan;
			//CStringA log_str;log_str.Format("新番型七对计算器计算的番数：%d",fan);WriteLog(log_str);
			//
			m_hu_status = 2;
		}
	}
}
//检测听
void player::CheckTing()
{
	uint32_t PAI[16]={0};
	for (uint32_t i = 0; i < m_pais_in_hand.size();i++)
	{
		if (m_pais_in_hand[i].u32ValueCard-1 > 15 || m_pais_in_hand[i].u32ValueCard-1 < 0)
		{
			return;
		}
		PAI[m_pais_in_hand[i].u32ValueCard-1]++;
	}
	for (uint32_t i = 0; i < 16;i++)
	{
		for (uint32_t j = 0; j < 16;j++)
		{
			//去掉一张i，增加一张j
			if(PAI[i] == 0)
				continue;
			PAI[i]--;
			PAI[j]++;
			JIANG = 0;
			uint32_t input_pai[16];
			for (uint32_t m = 0; m < 16;m++)
			{
				input_pai[m]=PAI[m];
			}
			
			//七对判断
			bool isqidui = false;
			uint32_t temp_input_pai[16];
			for (uint32_t n = 0; n < 16; n++)
			{
				temp_input_pai[n] = input_pai[n];
			}
			uint32_t pair_count = 0;
			for (uint32_t l = value_bamboo_1; l <= value_white_dragon; l++)
			{
				if (temp_input_pai[l-1] == 2)
				{
					pair_count++;
				}
				if (temp_input_pai[l-1] == 4)
				{
					pair_count+=2;//此段只为四个头判定为两对
				}
			}
			if (pair_count == 7)
			{
				isqidui = true;
			}
			//七对判断
			if (Hu(input_pai) || isqidui)//还得加上其他的牌型
			{
				bool only_once = false;
				//查询剩下还有几张
				for (uint32_t k = 0;k < m_all_pais.size();k++)
				{
					if (m_all_pais[k].u32ValueCard == j+1)
					{
						m_check_ting[0][i][j]++;
						m_judge_flag[5]++;
						if (!only_once)
						{
							m_check_ting[1][i][j] = GetTingFan(j+1,i+1);
							only_once = true;//只计算一次，提高效率
						}
					}
				}
				//除了查询剩下的牌，还要查询对家手上的牌（可能需要加入暗杠）
				for (uint32_t k = 0; k < m_oppisite_player->m_pais_in_hand.size(); k++)
				{
					if (m_oppisite_player->m_pais_in_hand[k].u32ValueCard == j+1)
					{
						m_check_ting[0][i][j]++;
						m_judge_flag[5]++;
						if (!only_once)
						{
							m_check_ting[1][i][j] = GetTingFan(j+1,i+1);
							only_once = true;//只计算一次，提高效率
						}
					}
				}
			}
			if (j > 15 || j < 0 || i > 15 || i < 0)
			{
				CStringA log_str;log_str.Format("CheckTing数组越界，i=%d，j=%d",i,j);WriteLog(log_str);
				return;
			}
			PAI[j]--;
			PAI[i]++;
		}
	}
}
//胡牌判断函数
uint32_t player::Hu(uint32_t PAI[16])
{
	if(!Remain(PAI))return 1;
	int i = 0;
	for(; !PAI[i] && i < 16;i++);
	if (i >= 16)
	{
		CStringA log_str;log_str.Format("i>=16");WriteLog(log_str);
		return 0;
	}
	//if (PAI[i] == 4)
	//{
	//	PAI[i] = 0;
		//
	//	if(Hu(PAI))return 1;
		//
	//	PAI[i] = 4;
	//}
	if (PAI[i] >= 3)
	{
		PAI[i] -= 3;
		if(Hu(PAI))return 1;
		PAI[i] += 3;
	}
	if (!JIANG && PAI[i] >= 2)
	{
		JIANG = 1;
		PAI[i] -= 2;
		if(Hu(PAI)) return 1;
		PAI[i] += 2;
		JIANG = 0;
	}
	if(i > 8)return 0;
	if (i >= 0 && i < 7 && PAI[i+1] && PAI[i+2])
	{
		PAI[i]--;
		PAI[i+1]--;
		PAI[i+2]--;
		if(Hu(PAI))return 1;
		PAI[i]++;
		PAI[i+1]++;
		PAI[i+2]++;
	}
	return 0;
}
//传入形参按一条至九条，然后东南西北中发白编号
uint32_t player::Remain(uint32_t PAI[16])
{
	int sum = 0; 
	for(int i=0;i<16;i++) 
		sum += PAI[i]; 
	return sum;
}
//计算胡番数
uint32_t player::GetHuFan()
{
	pai_kind pai_kind_;
	std::vector<uint32_t> all_pai;
	std::vector<uint32_t> hand_pai;
	for (uint32_t i = 0; i < m_pais_in_hand.size();i++)
	{
		all_pai.push_back(m_pais_in_hand[i].u32ValueCard);
		hand_pai.push_back(m_pais_in_hand[i].u32ValueCard);
	}
	for (uint32_t i = 0; i < m_pais_chew_pong_kong.size();i++)
	{
		all_pai.push_back(m_pais_chew_pong_kong[i][0].u32ValueCard);
		all_pai.push_back(m_pais_chew_pong_kong[i][1].u32ValueCard);
		all_pai.push_back(m_pais_chew_pong_kong[i][2].u32ValueCard);
	}
	if (m_current_status == 1)
	{
		m_fan_helper.m_is_zi_mo = true;
	}
	else if(m_current_status == 2)
	{
		m_fan_helper.m_is_zi_mo = false;
		all_pai.push_back(pai_kind_.GetValueFromRealCard(m_last_pai));
		//hand_pai.push_back(pai_kind_.GetValueFromRealCard(m_last_pai));
	}
	m_fan_helper.SetAllData(all_pai);
	m_fan_helper.SetHandData(hand_pai);
	m_fan_helper.pai_in_hand_count = m_pais_in_hand.size();//手上的牌数量
	m_fan_helper.m_ming_gang_count1 = m_ming_gang_count1;
	m_fan_helper.m_ming_gang_count2 = m_ming_gang_count2;
	m_fan_helper.m_an_gang_count = m_an_gang_count;
	m_fan_helper.m_flowers = m_pais_flowers.size();
	m_fan_helper.m_is_quan_dai_yao = false;
	m_fan_helper.m_total_gang_count = m_fan_helper.m_ming_gang_count1 + m_fan_helper.m_ming_gang_count2 + m_fan_helper.m_an_gang_count;
	int64_t temp;//没用
	return GetFan(temp,false);
}
//计算听番数
uint32_t player::GetTingFan(uint32_t u32Add,uint32_t u32Minus)
{
	std::vector<uint32_t> all_pai;
	std::vector<uint32_t> hand_pai;
	for (uint32_t i = 0; i < m_pais_in_hand.size();i++)
	{
		all_pai.push_back(m_pais_in_hand[i].u32ValueCard);
		hand_pai.push_back(m_pais_in_hand[i].u32ValueCard);
	}
	for (uint32_t i = 0; i < m_pais_chew_pong_kong.size();i++)
	{
		all_pai.push_back(m_pais_chew_pong_kong[i][0].u32ValueCard);
		all_pai.push_back(m_pais_chew_pong_kong[i][1].u32ValueCard);
		all_pai.push_back(m_pais_chew_pong_kong[i][2].u32ValueCard);
	}
	//删一个
	//ASSERT(all_pai.size() == 14);
	for (uint32_t i = 0; i < all_pai.size(); i++)
	{
		if (all_pai[i] == u32Minus)
		{
			all_pai.erase(all_pai.begin() + i);
			break;
		}
	}
	//ASSERT(all_pai.size() == 13);
	//加一个
	all_pai.push_back(u32Add);
	hand_pai.push_back(u32Add);
	if (m_current_status == 1)
	{
		m_fan_helper.m_is_zi_mo = true;
	}
	else if (m_current_status == 2)
	{
		m_fan_helper.m_is_zi_mo = false;
	}
	m_fan_helper.SetAllData(all_pai);
	m_fan_helper.SetHandData(hand_pai);
	m_fan_helper.pai_in_hand_count = m_pais_in_hand.size();//手上的牌数量
	m_fan_helper.m_ming_gang_count1 = m_ming_gang_count1;
	m_fan_helper.m_ming_gang_count2 = m_ming_gang_count2;
	m_fan_helper.m_an_gang_count = m_an_gang_count;
	m_fan_helper.m_flowers = m_pais_flowers.size();
	m_fan_helper.m_is_quan_dai_yao = false;
	m_fan_helper.m_total_gang_count = m_fan_helper.m_ming_gang_count1 + m_fan_helper.m_ming_gang_count2 + m_fan_helper.m_an_gang_count;
	int64_t temp = 0;//没用
	return GetFan(temp,false);
}
//计算番数
uint32_t player::GetFan(int64_t &fan_flag,bool bComputeIt)
{
	bool bWriteFanXing = false;
	CStringA log_str;log_str.Format("计算番型：");if(bWriteFanXing)WriteLog(log_str);
	uint32_t total_fan_count = m_fan_helper.m_flowers;
	if (m_fan_helper.IsDaSiXi())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("大四喜");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000001;
		}
	}
	if (m_fan_helper.IsDaSanYuan())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("大三元");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000002;
		}
	}
	if (m_fan_helper.IsLvYiSe())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("绿一色");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000004;
		}
	}
	if (m_fan_helper.IsJiuLianBaoDeng())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("九莲宝灯");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000008;
		}
	}
	if (m_fan_helper.IsSiGang())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("四杠");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000010;
		}
	}
	if (m_fan_helper.IsLianQiDui())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("连七对");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000020;
		}
	}
	if (m_fan_helper.IsXiaoSiXi())
	{
		total_fan_count += 64;
		CStringA log_str;log_str.Format("小四喜");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000040;
		}
	}
	if (m_fan_helper.IsXiaoSanYuan())
	{
		total_fan_count += 64;
		CStringA log_str;log_str.Format("小三元");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000080;
		}
	}
	if (m_fan_helper.IsZiYiSe())
	{
		total_fan_count += 64;
		CStringA log_str;log_str.Format("字一色");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000100;
		}
	}
	if (m_fan_helper.IsSiAnKe())
	{
		total_fan_count += 64;
		CStringA log_str;log_str.Format("四暗刻");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000200;
		}
	}
	if (m_fan_helper.IsYiSeShuangLongHui())
	{
		total_fan_count += 64;
		CStringA log_str;log_str.Format("一色双龙会");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000400;
		}
	}
	if (m_fan_helper.IsYiSeSiTongShun())
	{
		total_fan_count += 48;
		CStringA log_str;log_str.Format("一色四同顺");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000800;
		}
	}
	if (m_fan_helper.IsYiSeSiJieGao())
	{
		total_fan_count += 48;
		CStringA log_str;log_str.Format("一色四节高");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000001000;
		}
	}
	if (m_fan_helper.IsYiSeSiBuGao())
	{
		total_fan_count += 32;
		CStringA log_str;log_str.Format("一色四步高");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000002000;
		}
	}
	if (m_fan_helper.IsSanGang())
	{
		total_fan_count += 32;
		CStringA log_str;log_str.Format("三杠");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000004000;
		}
	}
	if (m_fan_helper.IsHunYaoJiu())
	{
		total_fan_count += 32;
		CStringA log_str;log_str.Format("混幺九");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000008000;
		}
	}
	if (m_fan_helper.IsQiDui())
	{
		total_fan_count += 24;
		CStringA log_str;log_str.Format("七对");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000010000;
		}
	}
	if (m_fan_helper.IsQingYiSe())
	{
		total_fan_count += 24;
		CStringA log_str;log_str.Format("清一色");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000020000;
		}
	}
	if (m_fan_helper.IsYiSeSanTongShun())
	{
		total_fan_count += 24;
		CStringA log_str;log_str.Format("一色三同顺");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000040000;
		}
	}
	if (m_fan_helper.IsYiSeSanJieGao())
	{
		total_fan_count += 24;
		CStringA log_str;log_str.Format("一色三节高");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000080000;
		}
	}
	if (m_fan_helper.IsQingLong())
	{
		total_fan_count += 16;
		CStringA log_str;log_str.Format("清龙");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000100000;
		}
	}
	if (m_fan_helper.IsYiSeSanBuGao())
	{
		total_fan_count += 16;
		CStringA log_str;log_str.Format("一色三步高");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000200000;
		}
	}
	if (m_fan_helper.IsSanAnKe())
	{
		total_fan_count += 16;
		CStringA log_str;log_str.Format("三暗刻");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000400000;
		}
	}
	if (m_fan_helper.IsDaYuWu())
	{
		total_fan_count += 12;
		CStringA log_str;log_str.Format("大于五");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000800000;
		}
	}
	if (m_fan_helper.IsXiaoYuWu())
	{
		total_fan_count += 12;
		CStringA log_str;log_str.Format("小于五");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000001000000;
		}
	}
	if (m_fan_helper.IsSanFengKe())
	{
		total_fan_count += 12;
		CStringA log_str;log_str.Format("三风刻");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000002000000;
		}
	}
	if (m_fan_helper.IsTuiBuDao())
	{
		total_fan_count += 8;
		CStringA log_str;log_str.Format("推不倒");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000004000000;
		}
	}
	if (m_fan_helper.IsSanSeSanTongShun())
	{
		total_fan_count += 8;
		CStringA log_str;log_str.Format("三色三同顺");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000008000000;
		}
	}
	if (m_fan_helper.IsSanSeSanJieGao())
	{
		total_fan_count += 8;
		CStringA log_str;log_str.Format("三色三节高");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000010000000;
		}
	}
	if (m_fan_helper.IsWuFanHu())
	{
		total_fan_count += 8;
		CStringA log_str;log_str.Format("无番胡");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000020000000;
		}
	}
	if (m_fan_helper.IsPengPengHu())
	{
		total_fan_count += 6;
		CStringA log_str;log_str.Format("碰碰胡");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000040000000;
		}
	}
	if (m_fan_helper.IsHunYiSe())
	{
		total_fan_count += 6;
		CStringA log_str;log_str.Format("混一色");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000080000000;
		}
	}
	if (m_fan_helper.IsQuanQiuRen())
	{
		total_fan_count += 6;
		CStringA log_str;log_str.Format("全求人");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000100000000;
		}
	}
	if (m_fan_helper.IsShuangAnGang())
	{
		total_fan_count += 6;
		CStringA log_str;log_str.Format("双暗杠");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000200000000;
		}
	}
	if (m_fan_helper.IsShuangJianKe())
	{
		total_fan_count += 6;
		CStringA log_str;log_str.Format("双箭刻");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000400000000;
		}
	}
	if (m_fan_helper.IsQuanDaiYao())
	{
		total_fan_count += 4;
		CStringA log_str;log_str.Format("全带幺");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000800000000;
		}
	}
	if (m_fan_helper.IsBuQiuRen())
	{
		total_fan_count += 4;
		CStringA log_str;log_str.Format("不求人");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000001000000000;
		}
	}
	if (m_fan_helper.IsShuangMingGang())
	{
		total_fan_count += 4;
		CStringA log_str;log_str.Format("双明杠");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000002000000000;
		}
	}
	if (m_fan_helper.IsJianKe())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("箭刻");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000004000000000;
		}
	}
	if (m_fan_helper.IsMenQianQing())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("门前清");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000008000000000;
		}
	}
	if (m_fan_helper.IsPingHu())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("平胡");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000010000000000;
		}
	}
	if (m_fan_helper.IsSiGuiYi())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("四归一");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000020000000000;
		}
	}
	if (m_fan_helper.IsShuangAnKe())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("双暗刻");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000040000000000;
		}
	}
	if (m_fan_helper.IsAnGang())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("暗杠");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000080000000000;
		}
	}
	if (m_fan_helper.IsDuanYao())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("断幺");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000100000000000;
		}
	}
	if (m_fan_helper.IsYiBanGao())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("一般高");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000200000000000;
		}
	}
	if (m_fan_helper.IsXiXiangFeng())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("喜相逢");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000400000000000;
		}
	}
	if (m_fan_helper.IsLianLiu())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("连六");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000800000000000;
		}
	}
	if (m_fan_helper.IsLaoShaoFu())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("老少副");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0001000000000000;
		}
	}
	if (m_fan_helper.IsYaoJiuKe())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("幺九刻");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0002000000000000;
		}
	}
	if (m_fan_helper.IsMingGang())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("明杠");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0004000000000000;
		}
	}
	if (m_fan_helper.IsQueYiMen())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("缺一门");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0008000000000000;
		}
	}
	if (m_fan_helper.IsWuZi())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("无字");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0010000000000000;
		}
	}
	if (m_fan_helper.IsBianZhang())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("边张");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0020000000000000;
		}
	}
	if (m_fan_helper.IsKanZhang())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("坎张");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0040000000000000;
		}
	}
	if (m_fan_helper.IsDanDiaoJiang())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("单钓将");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0080000000000000;
		}
	}
	if (m_fan_helper.IsZiMo())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("自摸");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0100000000000000;
		}
	}
	return total_fan_count;
}
//检测是否手上有花,有，返回花的唯一值，否，返回0
uint32_t player::CheckFlower()
{
	for (uint32_t i = m_pais_in_hand.size(); i > 0 ; i--)
	{
		if (m_pais_in_hand[i-1].u32ValueCard == value_flower)
		{
			return m_pais_in_hand[i-1].u32RealCard;
		}
	}
	return id_unknown;
}
//补花，返回替补的那张牌，唯一值
void player::DeleteACard(uint32_t flower)
{
	for (std::vector<pai_kind>::iterator iter = m_pais_in_hand.begin(); iter != m_pais_in_hand.end(); iter++)
	{
		if (iter->u32RealCard == flower)
		{
			m_pais_in_hand.erase(iter);
			break;
		}
	}
}
//加一张牌,参数唯一值
void player::AddACard(uint32_t u32RealCard)
{
	pai_kind pai_kind_;
	pai_kind_.u32RealCard = u32RealCard;
	pai_kind_.u32Status = status_in_hand_normal;
	pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
	m_pais_in_hand.push_back(pai_kind_);
}
//设置对家自摸点炮状态
void player::SetOppisiteZiMoStatus()
{
	m_oppisite_player->m_current_status = 2;
}
//设置自己自摸点炮状态
void player::SetMyZiMoStatus()
{
	m_current_status = 1;
}
//处理出单张牌
bool player::ProcessOutACard(uint32_t u32RealCard)
{
	int count_exception = 0;
	std::vector<pai_kind>::iterator iter = m_pais_in_hand.begin();
	for (; iter != m_pais_in_hand.end();iter++)
	{
		if (u32RealCard==(*iter).u32RealCard)
		{
			m_pais_on_table.push_back(*iter);
			m_pais_in_hand.erase(iter);
			count_exception++;
			break;
		}
	}
	if (count_exception != 1)
	{
		return false;
	}
	SetLastPai(u32RealCard);
	m_oppisite_player->SetLastPai(u32RealCard);
	m_fan_helper.m_is_gang_shang_kai_hua = false;//出单张牌的时候关杠标记
	m_fan_helper.m_is_qiang_gang_hu = false;//自己出单了，关闭抢杠胡
	m_gang_shang_kai_hua = false;
	m_qiang_gang_hu = false;
	return true;
}
//处理吃牌
bool player::ProcessChi(uint32_t index,uint32_t &ret0,uint32_t &ret1,uint32_t &ret2)
{
	if (m_oppisite_player->m_pais_on_table.size() > 0)
	{
		int count_exception = 0;
		std::vector<pai_kind>::iterator iter = m_pais_in_hand.begin();
		std::vector<pai_kind> temp_vec;
		for (; iter != m_pais_in_hand.end();)
		{
			if (m_vec_check_chew[index].pai1 == (*iter).u32RealCard || m_vec_check_chew[index].pai2 == (*iter).u32RealCard)
			{
				iter->u32Status = status_chew_self;
				temp_vec.push_back(*iter);
				iter = m_pais_in_hand.erase(iter);
				count_exception++;
			}
			else
			{
				iter++;
			}
		}
		if (count_exception != 2)
		{
			//异常，手牌纠正，等待重新接受吃牌数据
			return false;
		}

		//temp_vec.push_back(m_oppisite_player->m_pais_on_table[m_oppisite_player->m_pais_on_table.size()-1]);//最后的牌
		//ret0 = m_oppisite_player->m_pais_on_table[m_oppisite_player->m_pais_on_table.size()-1].u32RealCard;
		//上面这句有时候不知道什么原因，就放进了8条，9条，北风，试着改用一下m_last_pai
		pai_kind pai_kind_;
		pai_kind_.u32RealCard = m_last_pai;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		pai_kind_.u32Status = status_chew_self;
		temp_vec.push_back(pai_kind_);
		ret0 = m_last_pai;
		ret1 = m_vec_check_chew[index].pai1;
		ret2 = m_vec_check_chew[index].pai2;
		m_pais_chew_pong_kong.push_back(temp_vec);
		//CStringA log_str;log_str.Format("ProcessChi的m_pais_chew_pong_kong放入了一个vector，现在大小：%d",m_pais_chew_pong_kong.size());WriteLog(log_str);
		//if (m_pais_chew_pong_kong.size() > 4)
		//{
		//	//异常
		//	int xxx[2] = {0};
		//	xxx[2] = 1;
		//}
		m_oppisite_player->m_pais_on_table.pop_back();
		return true;
	}
	return false;
}
//处理碰牌
bool player::ProcessPeng(uint32_t index,uint32_t &ret0,uint32_t &ret1,uint32_t &ret2)
{
	if (m_oppisite_player->m_pais_on_table.size() > 0)
	{
		int count_exception = 0;
		std::vector<pai_kind>::iterator iter = m_pais_in_hand.begin();
		std::vector<pai_kind> temp_vec;
		for (; iter != m_pais_in_hand.end();)
		{
			if (m_vec_check_peng[index].pai1 == (*iter).u32RealCard || m_vec_check_peng[index].pai2 == (*iter).u32RealCard)
			{
				iter->u32Status = status_pong_self;
				temp_vec.push_back(*iter);
				iter = m_pais_in_hand.erase(iter);
				count_exception++;
			}
			else
			{
				iter++;
			}
		}
		if (count_exception != 2)
		{
			//异常
			return false;
		}
		//temp_vec.push_back(m_oppisite_player->m_pais_on_table[m_oppisite_player->m_pais_on_table.size()-1]);//最后的牌
		//ret0 = m_oppisite_player->m_pais_on_table[m_oppisite_player->m_pais_on_table.size()-1].u32RealCard;
		//碰也试试同吃一样的算法
		pai_kind pai_kind_;
		pai_kind_.u32RealCard = m_last_pai;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		pai_kind_.u32Status = status_pong_self;
		temp_vec.push_back(pai_kind_);
		ret0 = m_last_pai;
		ret1 = m_vec_check_peng[index].pai1;
		ret2 = m_vec_check_peng[index].pai2;
		m_pais_chew_pong_kong.push_back(temp_vec);
		//CStringA log_str;log_str.Format("ProcessPeng的m_pais_chew_pong_kong放入了一个vector，现在大小：%d",m_pais_chew_pong_kong.size());WriteLog(log_str);
		//if (m_pais_chew_pong_kong.size() > 4)
		//{
		//	//异常
		//	int xxx[2] = {0};
		//	xxx[2] = 1;
		//}
		m_oppisite_player->m_pais_on_table.pop_back();
		return true;
	}

	return false;
}
//处理暗杠
bool player::ProcessAnGang(uint32_t u32Value)
{
	if (m_oppisite_player->m_pais_on_table.size() > 0)
	{
		int count_exception = 0;
		std::vector<pai_kind>::iterator iter = m_pais_in_hand.begin();
		std::vector<pai_kind> temp_vec;
		for (; iter != m_pais_in_hand.end();)
		{
			if (u32Value == (*iter).u32ValueCard)
			{
				iter->u32Status = status_kong_oppisite;//此处暗，实则明1
				temp_vec.push_back(*iter);
				iter = m_pais_in_hand.erase(iter);
				count_exception++;
			}
			else
			{
				iter++;
			}
		}
		if (count_exception != 3)
		{
			//异常
			return false;
		}
		//temp_vec.push_back(m_oppisite_player->m_pais_on_table[m_oppisite_player->m_pais_on_table.size()-1]);//最后的牌
		pai_kind pai_kind_;
		pai_kind_.u32RealCard = m_last_pai;
		pai_kind_.u32Status = status_kong_oppisite;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		temp_vec.push_back(pai_kind_);
		m_pais_chew_pong_kong.push_back(temp_vec);
		m_flag_for_ming_an[m_pais_chew_pong_kong.size()-1] = 1;
		//CStringA log_str;log_str.Format("ProcessAnGang的m_pais_chew_pong_kong放入了一个vector，现在大小：%d",m_pais_chew_pong_kong.size());WriteLog(log_str);
		//if (m_pais_chew_pong_kong.size() > 4)
		//{
		//	//异常
		//	int xxx[2] = {0};
		//	xxx[2] = 1;
		//}
		m_oppisite_player->m_pais_on_table.pop_back();
		m_fan_helper.m_is_gang_shang_kai_hua = true;
		m_oppisite_player->m_fan_helper.m_is_qiang_gang_hu = true;
		m_fan_helper.m_is_qiang_gang_hu = false;//自己杠了，关闭抢杠胡

		m_gang_shang_kai_hua = true;
		m_qiang_gang_hu = false;
		m_oppisite_player->m_qiang_gang_hu = true;
		return true;
	}
	return false;
}
//处理明杠1
bool player::ProcessMingGang1(uint32_t u32Value)
{
	int count_exception = 0;
	std::vector<pai_kind>::iterator iter = m_pais_in_hand.begin();
	std::vector<pai_kind> temp_vec;
	for (; iter != m_pais_in_hand.end();)
	{
		if ((*iter).u32ValueCard == u32Value)
		{
			iter->u32Status = status_kong_self;//此处明1，实则暗
			temp_vec.push_back(*iter);
			iter = m_pais_in_hand.erase(iter);
			count_exception++;
		}
		else
		{
			iter++;
		}
	}
	if (count_exception != 4)
	{
		//异常
		return false;
	}
	m_pais_chew_pong_kong.push_back(temp_vec);
	m_flag_for_ming_an[m_pais_chew_pong_kong.size()-1] = 2;
	//CStringA log_str;log_str.Format("ProcessMingGang1的m_pais_chew_pong_kong放入了一个vector，现在大小：%d",m_pais_chew_pong_kong.size());WriteLog(log_str);
	//if (m_pais_chew_pong_kong.size() > 4)
	//{
	//	//异常
	//	int xxx[2] = {0};
	//	xxx[2] = 1;
	//}
	m_ming_gang_count1++;
	m_fan_helper.m_is_gang_shang_kai_hua = true;
	m_fan_helper.m_is_qiang_gang_hu = false;//自己杠了，关闭抢杠胡
	m_gang_shang_kai_hua = true;
	m_qiang_gang_hu = false;
	return true;
}
//处理明杠2
bool player::ProcessMingGang2(uint32_t u32RealCard)
{
	int count_exception = 0;
	pai_kind pai_kind_;
	pai_kind_.u32RealCard = u32RealCard;
	pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
	std::vector<pai_kind>::iterator iter = m_pais_in_hand.begin();
	for (; iter != m_pais_in_hand.end();iter++)
	{
		if ((*iter).u32ValueCard == pai_kind_.u32ValueCard)
		{
			m_pais_in_hand.erase(iter);
			count_exception++;
			break;
		}
	}
	if (count_exception != 1)
	{
		//异常
		return false;
	}
	std::vector<std::vector<pai_kind>>::iterator iter2 = m_pais_chew_pong_kong.begin();
	int count_for_flag = 0;
	for (;iter2 != m_pais_chew_pong_kong.end();iter2++)
	{
		count_for_flag++;
		if ((*iter2)[0].u32ValueCard == (*iter2)[1].u32ValueCard && (*iter2)[0].u32ValueCard == pai_kind_.u32ValueCard)
		{
			(*iter2)[0].u32Status = status_kong_oppisite;
			(*iter2)[1].u32Status = status_kong_oppisite;
			(*iter2)[2].u32Status = status_kong_oppisite;
			pai_kind_.u32Status = status_kong_oppisite;
			iter2->push_back(pai_kind_);
			m_flag_for_ming_an[count_for_flag-1] = 3;
			break;
		}
	}
	m_ming_gang_count2++;
	m_fan_helper.m_is_gang_shang_kai_hua = true;
	m_oppisite_player->m_fan_helper.m_is_qiang_gang_hu = true;
	m_fan_helper.m_is_qiang_gang_hu = false;//自己杠了，关闭抢杠胡

	m_gang_shang_kai_hua = true;
	m_oppisite_player->m_qiang_gang_hu = true;
	m_qiang_gang_hu = false;
	return true;
}
//处理放弃
void player::ProcessFangQi()
{
	m_vec_check_chew.clear();
	m_vec_check_peng.clear();
	m_vec_check_an_gang.clear();
	m_vec_check_ming_gang1.clear();
	m_vec_check_ming_gang2.clear();
	if (is_ting)
	{
		m_hu_clock_when_is_ting = 0;
	}
	//m_is_jia_bei_check_ting = true;

}
//处理听
void player::ProcessTing(uint32_t &index)
{
	pai_kind pai_kind_;
	if (index == 0)
	{
		bool ting_which = false;
		for (uint32_t i = 0; i < 16; i++)
		{
			for (uint32_t j = 0; j < 16; j++)
			{
				if(m_check_ting[0][i][j] > 0)//传入的参数为0是由机器人要听的时候传进来的，听最早检测出的那张
				{
					ting_which = true;
					index = i+1;
					m_ting_cards.push_back(j+1);
				}
			}
			if (ting_which == true)
			{
				break;
			}
		}
	}
	else
	{
		for (uint32_t j = 0 ; j < 16;j++)
		{
			if(m_check_ting[0][pai_kind_.GetValueFromRealCard(index)-1][j] > 0)
			{
				m_ting_cards.push_back(j+1);
			}
		}
	}
	is_ting = true;
}
//处理加倍
void player::ProcessJiaBei()
{
	m_double = m_double * 2;
	m_vec_check_chew.clear();
	m_vec_check_peng.clear();
	m_vec_check_an_gang.clear();
	m_vec_check_ming_gang1.clear();
	m_vec_check_ming_gang2.clear();
	if (is_ting)
	{
		m_hu_clock_when_is_ting = 0;
	}
	//m_is_jia_bei_check_ting = true;
}
//设置最后一次牌
void player::SetLastPai(uint32_t pai)
{
	m_last_pai = pai;
}
//设置一次所有牌
void player::SetAllPai(std::vector<pai_kind> pai_group)
{
	m_all_pais = pai_group;
}

//番型计算前的预处理
void player::PreProcess()
{
	m_normal_fan_helper.ResetAllData();
	//已经吃碰杠的牌
	int l = 0;
	for (uint32_t i = 0; i < m_pais_chew_pong_kong.size(); i++)
	{
		if (m_pais_chew_pong_kong[i].size() >= 3)
		{
			if (m_pais_chew_pong_kong[i][0].u32Status == status_chew_self)
			{
				pai_group pai_group_;
				pai_group_.value1 = m_pais_chew_pong_kong[i][0].u32ValueCard;
				pai_group_.value2 = m_pais_chew_pong_kong[i][1].u32ValueCard;
				pai_group_.value3 = m_pais_chew_pong_kong[i][2].u32ValueCard;
				pai_group_.value_type = value_shunzi_chide;
				//排序
				if (pai_group_.value1 > pai_group_.value2)
				{
					uint32_t temp = pai_group_.value1;
					pai_group_.value1 = pai_group_.value2;
					pai_group_.value2 = temp;
				}
				if (pai_group_.value1 > pai_group_.value3)
				{
					uint32_t temp = pai_group_.value1;
					pai_group_.value1 = pai_group_.value3;
					pai_group_.value3 = temp;
				}
				if (pai_group_.value2 > pai_group_.value3)
				{
					uint32_t temp = pai_group_.value2;
					pai_group_.value2 = pai_group_.value3;
					pai_group_.value3 = temp;
				}
				m_normal_fan_helper.SetData(pai_group_ ,l);
				l++;
			}
			else if (m_pais_chew_pong_kong[i][0].u32Status == status_pong_self)
			{
				pai_group pai_group_;
				pai_group_.value1 = m_pais_chew_pong_kong[i][0].u32ValueCard;
				pai_group_.value_type = value_kezi_pengde;
				m_normal_fan_helper.SetData(pai_group_ ,l);
				l++;
			}
			else if (m_pais_chew_pong_kong[i][0].u32Status == status_kong_self)
			{
				pai_group pai_group_;
				pai_group_.value1 = m_pais_chew_pong_kong[i][0].u32ValueCard;
				pai_group_.value_type = value_angang;
				m_normal_fan_helper.SetData(pai_group_ ,l);
				l++;
			}
			else if (m_pais_chew_pong_kong[i][0].u32Status == status_kong_oppisite)
			{
				pai_group pai_group_;
				pai_group_.value1 = m_pais_chew_pong_kong[i][0].u32ValueCard;
				pai_group_.value_type = value_minggang1;
				m_normal_fan_helper.SetData(pai_group_ ,l);
				l++;
			}
		}
	}
	//未吃碰杠的牌
	uint32_t left_pai[16] = {0};
	m_sort_jiang = 0;
	std::vector<uint32_t> vec_value,vec_jiang_value;
	for (uint32_t i = 0; i < m_pais_in_hand.size(); i++)
	{
		if (m_pais_in_hand[i].u32ValueCard - 1 < 0 || m_pais_in_hand[i].u32ValueCard - 1 >= 16)
		{
			return;
		}
		left_pai[m_pais_in_hand[i].u32ValueCard - 1]++;
	}
	if (m_current_status == 2)
	{
		pai_kind pai_kind_;
		if (pai_kind_.GetValueFromRealCard(m_last_pai)-1 < 0 || pai_kind_.GetValueFromRealCard(m_last_pai)-1 >= 16)
		{
			return;
		}
		left_pai[pai_kind_.GetValueFromRealCard(m_last_pai)-1]++;
	}
	SortFanCards(left_pai,vec_value,vec_jiang_value);
	for (uint32_t k = 0; k < vec_value.size(); k=k+3)
	{
		if (vec_value[k] > 100 && vec_value[k] < 1000)//刻子
		{
			pai_group pai_group_;
			pai_group_.value1 = vec_value[k]-100;
			pai_group_.value_type = value_kezi_weipeng;
			m_normal_fan_helper.SetData(pai_group_ ,l);
			l++;
		}
		else if (vec_value[k] > 1000)//顺子
		{
			pai_group pai_group_;
			pai_group_.value1 = vec_value[k]-1000;
			pai_group_.value2 = vec_value[k+1]-1000;
			pai_group_.value3 = vec_value[k+2]-1000;
			pai_group_.value_type = value_shunzi_weichi;
			//排序
			if (pai_group_.value1 > pai_group_.value2)
			{
				uint32_t temp = pai_group_.value1;
				pai_group_.value1 = pai_group_.value2;
				pai_group_.value2 = temp;
			}
			if (pai_group_.value1 > pai_group_.value3)
			{
				uint32_t temp = pai_group_.value1;
				pai_group_.value1 = pai_group_.value3;
				pai_group_.value3 = temp;
			}
			if (pai_group_.value2 > pai_group_.value3)
			{
				uint32_t temp = pai_group_.value2;
				pai_group_.value2 = pai_group_.value3;
				pai_group_.value3 = temp;
			}
			m_normal_fan_helper.SetData(pai_group_ ,l);
			l++;
		}
	}
	if (vec_jiang_value.size() > 0)
	{
		pai_group pai_group_;
		pai_group_.value1 = vec_jiang_value[0];
		pai_group_.value_type = value_jiangzi;
		m_normal_fan_helper.SetData(pai_group_ ,l);
		l++;
	}
	m_normal_fan_helper.SetZiMo(m_current_status == 1);
	m_normal_fan_helper.SetFlowers(m_pais_flowers.size());
	m_normal_fan_helper.SetMiaoShouHuiChun(m_miao_shou_hui_chun);
	m_normal_fan_helper.SetHaiDiLaoYue(m_hai_di_lao_yue);
	m_normal_fan_helper.SetGangShangKaiHua(m_gang_shang_kai_hua);
	m_normal_fan_helper.SetQiangGangHu(m_qiang_gang_hu);
	CStringA log_str;log_str.Format("m_normal_fan_helper的五组牌：一%d，%d,%d,%d.二%d,%d,%d,%d,三%d,%d,%d,%d,四%d,%d,%d,%d,五%d,%d,%d,%d",
		m_normal_fan_helper.m_5zupai[0].value1,m_normal_fan_helper.m_5zupai[0].value2,m_normal_fan_helper.m_5zupai[0].value3,m_normal_fan_helper.m_5zupai[0].value_type,
		m_normal_fan_helper.m_5zupai[1].value1,m_normal_fan_helper.m_5zupai[1].value2,m_normal_fan_helper.m_5zupai[1].value3,m_normal_fan_helper.m_5zupai[1].value_type,
		m_normal_fan_helper.m_5zupai[2].value1,m_normal_fan_helper.m_5zupai[2].value2,m_normal_fan_helper.m_5zupai[2].value3,m_normal_fan_helper.m_5zupai[2].value_type,
		m_normal_fan_helper.m_5zupai[3].value1,m_normal_fan_helper.m_5zupai[3].value2,m_normal_fan_helper.m_5zupai[3].value3,m_normal_fan_helper.m_5zupai[3].value_type,
		m_normal_fan_helper.m_5zupai[4].value1,m_normal_fan_helper.m_5zupai[4].value2,m_normal_fan_helper.m_5zupai[4].value3,m_normal_fan_helper.m_5zupai[4].value_type);//WriteLog(log_str);
	m_normal_fan_helper.CheckAllFan();
	m_normal_fan_helper.DeleteAllRepeat();

}
//番型计算（七对专用）
void player::PreProcess2(uint32_t qiduipai[16])
{
	m_qidui_fan_helper.ResetAllData();
	//七对皆是未吃碰杠的牌
	int l = 0;
	for (int i = 0 ; i < 16; i++)
	{
		if (qiduipai[i] == 2)
		{
			pai_group pai_group_;
			pai_group_.value_type = value_jiangzi;
			pai_group_.value1 = i+1;
			m_qidui_fan_helper.SetData(pai_group_,l);
			l++;
		}
	}
	
	m_qidui_fan_helper.SetZiMo(m_current_status == 1);
	m_qidui_fan_helper.SetFlowers(m_pais_flowers.size());
	m_qidui_fan_helper.SetMiaoShouHuiChun(m_miao_shou_hui_chun);
	m_qidui_fan_helper.SetHaiDiLaoYue(m_hai_di_lao_yue);
	m_qidui_fan_helper.SetGangShangKaiHua(m_gang_shang_kai_hua);
	m_qidui_fan_helper.SetQiangGangHu(m_qiang_gang_hu);
	CStringA log_str;log_str.Format("m_qidui_fan_helper的七组牌：一%d,%d,二%d,%d,三%d,%d,四%d,%d,五%d,%d,六%d,%d,七%d,%d",
		m_qidui_fan_helper.m_7zupai[0].value1,m_qidui_fan_helper.m_7zupai[0].value_type,
		m_qidui_fan_helper.m_7zupai[1].value1,m_qidui_fan_helper.m_7zupai[1].value_type,
		m_qidui_fan_helper.m_7zupai[2].value1,m_qidui_fan_helper.m_7zupai[2].value_type,
		m_qidui_fan_helper.m_7zupai[3].value1,m_qidui_fan_helper.m_7zupai[3].value_type,
		m_qidui_fan_helper.m_7zupai[4].value1,m_qidui_fan_helper.m_7zupai[4].value_type,
		m_qidui_fan_helper.m_7zupai[5].value1,m_qidui_fan_helper.m_7zupai[5].value_type,
		m_qidui_fan_helper.m_7zupai[6].value1,m_qidui_fan_helper.m_7zupai[6].value_type);//WriteLog(log_str);
	m_qidui_fan_helper.CheckAllFan();
	m_qidui_fan_helper.DeleteAllRepeat();
}
//结束后将番型也传给客户端时用到
void player::SetResultFan(int &fan0,int &fan1,int &fan2,bool bIsNormal)
{
	fan0 = 0; fan1 = 0; fan2 = 0;
	if (bIsNormal)
	{
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_DASIXI))
			fan0 = fan0 | 0x00000001;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_DASANYUAN))
			fan0 = fan0 | 0x00000002;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_LVYISE))
			fan0 = fan0 | 0x00000004;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_JIULIANBAODENG))
			fan0 = fan0 | 0x00000008;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SIGANG))
			fan0 = fan0 | 0x00000010;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_LIANQIDUI))
			fan0 = fan0 | 0x00000020;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SHISANYAO))
			fan0 = fan0 | 0x00000040;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QINGYAOJIU))
			fan0 = fan0 | 0x00000080;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_XIAOSIXI))
			fan0 = fan0 | 0x00000100;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_XIAOSANYUAN))
			fan0 = fan0 | 0x00000200;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_ZIYISE))
			fan0 = fan0 | 0x00000400;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SIANKE))
			fan0 = fan0 | 0x00000800;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_YISESHUANGLONGHUI))
			fan0 = fan0 | 0x00001000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_YISESITONGSHUN))
			fan0 = fan0 | 0x00002000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_YISESIJIEGAO))
			fan0 = fan0 | 0x00004000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_YISESIBUGAO))
			fan0 = fan0 | 0x00008000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SANGANG))
			fan0 = fan0 | 0x00010000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_HUNYAOJIU))
			fan0 = fan0 | 0x00020000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QIDUI))
			fan0 = fan0 | 0x00040000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QIXINGBUKAO))
			fan0 = fan0 | 0x00080000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QUANSHUANGKE))
			fan0 = fan0 | 0x00100000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QINGYISE))
			fan0 = fan0 | 0x00200000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_YISESANTONGSHUN))
			fan0 = fan0 | 0x00400000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_YISESANJIEGAO))
			fan0 = fan0 | 0x00800000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QUANDA))
			fan0 = fan0 | 0x01000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QUANZHONG))
			fan0 = fan0 | 0x02000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QUANXIAO))
			fan0 = fan0 | 0x04000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QINGLONG))
			fan0 = fan0 | 0x08000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SANSESHUANGLONGHUI))
			fan0 = fan0 | 0x10000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_YISESANBUGAO))
			fan0 = fan0 | 0x20000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QUANDAIWU))
			fan0 = fan0 | 0x40000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SANTONGKE))
			fan0 = fan0 | 0x80000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SANANKE))
			fan1 = fan1 | 0x00000001;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QUANBUKAO))
			fan1 = fan1 | 0x00000002;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_ZUHELONG))
			fan1 = fan1 | 0x00000004;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_DAYUWU))
			fan1 = fan1 | 0x00000008;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_XIAOYUWU))
			fan1 = fan1 | 0x00000010;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SANFENGKE))
			fan1 = fan1 | 0x00000020;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_HUALONG))
			fan1 = fan1 | 0x00000040;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_TUIBUDAO))
			fan1 = fan1 | 0x00000080;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SANSESANTONGSHUN))
			fan1 = fan1 | 0x00000100;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SANSESANJIEGAO))
			fan1 = fan1 | 0x00000200;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_WUFANHU))
			fan1 = fan1 | 0x00000400;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_MIAOSHOUHUICHUN))
			fan1 = fan1 | 0x00000800;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_HAIDILAOYUE))
			fan1 = fan1 | 0x00001000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_GANGSHANGKAIHUA))
			fan1 = fan1 | 0x00002000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QIANGGANGHU))
			fan1 = fan1 | 0x00004000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_PENGPENGHU))
			fan1 = fan1 | 0x00008000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_HUNYISE))
			fan1 = fan1 | 0x00010000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SANSESANBUGAO))
			fan1 = fan1 | 0x00020000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_WUMENQI))
			fan1 = fan1 | 0x00040000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QUANQIUREN))
			fan1 = fan1 | 0x00080000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SHUANGANGANG))
			fan1 = fan1 | 0x00100000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SHUANGJIANKE))
			fan1 = fan1 | 0x00200000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QUANDAIYAO))
			fan1 = fan1 | 0x00400000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_BUQIUREN))
			fan1 = fan1 | 0x00800000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SHUANGMINGGANG))
			fan1 = fan1 | 0x01000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_HUJUEZHANG))
			fan1 = fan1 | 0x02000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_JIANKE))
			fan1 = fan1 | 0x04000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QUANFENGKE))
			fan1 = fan1 | 0x08000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_MENFENGKE))
			fan1 = fan1 | 0x10000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_MENQIANQING))
			fan1 = fan1 | 0x20000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_TUIBUDAO))
			fan1 = fan1 | 0x40000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SIGUIYI))
			fan1 = fan1 | 0x80000000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SHUANGTONGKE))
			fan2 = fan2 | 0x00000001;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_SHUANGANKE))
			fan2 = fan2 | 0x00000002;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_ANGANG))
			fan2 = fan2 | 0x00000004;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_DUANYAO))
			fan2 = fan2 | 0x00000008;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_YIBANGAO))
			fan2 = fan2 | 0x00000010;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_XIXIANGFENG))
			fan2 = fan2 | 0x00000020;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_LIANLIU))
			fan2 = fan2 | 0x00000040;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_LAOSHAOFU))
			fan2 = fan2 | 0x00000080;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_YAOJIUKE))
			fan2 = fan2 | 0x00000100;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_MINGGANG))
			fan2 = fan2 | 0x00000200;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_QUEYIMEN))
			fan2 = fan2 | 0x00000400;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_WUZI))
			fan2 = fan2 | 0x00000800;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_BIANZHANG))
			fan2 = fan2 | 0x00001000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_KANZHANG))
			fan2 = fan2 | 0x00002000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_DANDIAOJIANG))
			fan2 = fan2 | 0x00004000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_HUAPAI))
			fan2 = fan2 | 0x00008000;
		if (m_normal_fan_helper.GetSomeFan(ID_FAN_ZIMO))
			fan2 = fan2 | 0x00010000;
	}
	else
	{
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_DASIXI))
			fan0 = fan0 | 0x00000001;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_DASANYUAN))
			fan0 = fan0 | 0x00000002;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_LVYISE))
			fan0 = fan0 | 0x00000004;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_JIULIANBAODENG))
			fan0 = fan0 | 0x00000008;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SIGANG))
			fan0 = fan0 | 0x00000010;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_LIANQIDUI))
			fan0 = fan0 | 0x00000020;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SHISANYAO))
			fan0 = fan0 | 0x00000040;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QINGYAOJIU))
			fan0 = fan0 | 0x00000080;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_XIAOSIXI))
			fan0 = fan0 | 0x00000100;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_XIAOSANYUAN))
			fan0 = fan0 | 0x00000200;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_ZIYISE))
			fan0 = fan0 | 0x00000400;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SIANKE))
			fan0 = fan0 | 0x00000800;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_YISESHUANGLONGHUI))
			fan0 = fan0 | 0x00001000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_YISESITONGSHUN))
			fan0 = fan0 | 0x00002000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_YISESIJIEGAO))
			fan0 = fan0 | 0x00004000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_YISESIBUGAO))
			fan0 = fan0 | 0x00008000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SANGANG))
			fan0 = fan0 | 0x00010000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_HUNYAOJIU))
			fan0 = fan0 | 0x00020000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QIDUI))
			fan0 = fan0 | 0x00040000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QIXINGBUKAO))
			fan0 = fan0 | 0x00080000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QUANSHUANGKE))
			fan0 = fan0 | 0x00100000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QINGYISE))
			fan0 = fan0 | 0x00200000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_YISESANTONGSHUN))
			fan0 = fan0 | 0x00400000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_YISESANJIEGAO))
			fan0 = fan0 | 0x00800000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QUANDA))
			fan0 = fan0 | 0x01000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QUANZHONG))
			fan0 = fan0 | 0x02000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QUANXIAO))
			fan0 = fan0 | 0x04000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QINGLONG))
			fan0 = fan0 | 0x08000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SANSESHUANGLONGHUI))
			fan0 = fan0 | 0x10000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_YISESANBUGAO))
			fan0 = fan0 | 0x20000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QUANDAIWU))
			fan0 = fan0 | 0x40000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SANTONGKE))
			fan0 = fan0 | 0x80000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SANANKE))
			fan1 = fan1 | 0x00000001;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QUANBUKAO))
			fan1 = fan1 | 0x00000002;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_ZUHELONG))
			fan1 = fan1 | 0x00000004;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_DAYUWU))
			fan1 = fan1 | 0x00000008;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_XIAOYUWU))
			fan1 = fan1 | 0x00000010;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SANFENGKE))
			fan1 = fan1 | 0x00000020;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_HUALONG))
			fan1 = fan1 | 0x00000040;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_TUIBUDAO))
			fan1 = fan1 | 0x00000080;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SANSESANTONGSHUN))
			fan1 = fan1 | 0x00000100;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SANSESANJIEGAO))
			fan1 = fan1 | 0x00000200;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_WUFANHU))
			fan1 = fan1 | 0x00000400;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_MIAOSHOUHUICHUN))
			fan1 = fan1 | 0x00000800;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_HAIDILAOYUE))
			fan1 = fan1 | 0x00001000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_GANGSHANGKAIHUA))
			fan1 = fan1 | 0x00002000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QIANGGANGHU))
			fan1 = fan1 | 0x00004000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_PENGPENGHU))
			fan1 = fan1 | 0x00008000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_HUNYISE))
			fan1 = fan1 | 0x00010000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SANSESANBUGAO))
			fan1 = fan1 | 0x00020000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_WUMENQI))
			fan1 = fan1 | 0x00040000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QUANQIUREN))
			fan1 = fan1 | 0x00080000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SHUANGANGANG))
			fan1 = fan1 | 0x00100000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SHUANGJIANKE))
			fan1 = fan1 | 0x00200000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QUANDAIYAO))
			fan1 = fan1 | 0x00400000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_BUQIUREN))
			fan1 = fan1 | 0x00800000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SHUANGMINGGANG))
			fan1 = fan1 | 0x01000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_HUJUEZHANG))
			fan1 = fan1 | 0x02000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_JIANKE))
			fan1 = fan1 | 0x04000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QUANFENGKE))
			fan1 = fan1 | 0x08000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_MENFENGKE))
			fan1 = fan1 | 0x10000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_MENQIANQING))
			fan1 = fan1 | 0x20000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_TUIBUDAO))
			fan1 = fan1 | 0x40000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SIGUIYI))
			fan1 = fan1 | 0x80000000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SHUANGTONGKE))
			fan2 = fan2 | 0x00000001;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_SHUANGANKE))
			fan2 = fan2 | 0x00000002;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_ANGANG))
			fan2 = fan2 | 0x00000004;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_DUANYAO))
			fan2 = fan2 | 0x00000008;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_YIBANGAO))
			fan2 = fan2 | 0x00000010;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_XIXIANGFENG))
			fan2 = fan2 | 0x00000020;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_LIANLIU))
			fan2 = fan2 | 0x00000040;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_LAOSHAOFU))
			fan2 = fan2 | 0x00000080;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_YAOJIUKE))
			fan2 = fan2 | 0x00000100;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_MINGGANG))
			fan2 = fan2 | 0x00000200;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_QUEYIMEN))
			fan2 = fan2 | 0x00000400;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_WUZI))
			fan2 = fan2 | 0x00000800;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_BIANZHANG))
			fan2 = fan2 | 0x00001000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_KANZHANG))
			fan2 = fan2 | 0x00002000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_DANDIAOJIANG))
			fan2 = fan2 | 0x00004000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_HUAPAI))
			fan2 = fan2 | 0x00008000;
		if (m_qidui_fan_helper.GetSomeFan(ID_FAN_ZIMO))
			fan2 = fan2 | 0x00010000;
	}
}
//番型计算辅助函数
uint32_t player::SortFanCards(uint32_t PAI[16],std::vector<uint32_t> &vec_value,std::vector<uint32_t> &vec_jiang_value)
{
	if (!Remain(PAI))return 1;
	int i = 0;
	for (;!PAI[i] && i < 16;i++);
	if (i >= 16)
	{
		return 0;
	}
	if (PAI[i] >= 3)
	{
		PAI[i] -= 3;
		vec_value.push_back(i+1+100);
		vec_value.push_back(i+1+100);
		vec_value.push_back(i+1+100);//标记100为刻子
		if(SortFanCards(PAI,vec_value,vec_jiang_value))return 1;
		PAI[i] += 3;
		vec_value.pop_back();
		vec_value.pop_back();
		vec_value.pop_back();
	}
	if (!m_sort_jiang && PAI[i] >= 2)
	{
		m_sort_jiang = 1;
		PAI[i] -= 2;
		vec_jiang_value.push_back(i+1);
		vec_jiang_value.push_back(i+1);
		if (SortFanCards(PAI,vec_value,vec_jiang_value))return 1;
		PAI[i] += 2;
		vec_jiang_value.pop_back();
		vec_jiang_value.pop_back();
		m_sort_jiang = 0;
	}
	if (i > 8)return 0;
	if (i >= 0 && i < 7 && PAI[i+1] && PAI[i+2])
	{
		PAI[i]--;
		PAI[i+1]--;
		PAI[i+2]--;
		vec_value.push_back(i+1+1000);
		vec_value.push_back(i+2+1000);
		vec_value.push_back(i+3+1000);//标记1000为顺子
		if(SortFanCards(PAI,vec_value,vec_jiang_value))return 1;
		PAI[i]++;
		PAI[i+1]++;
		PAI[i+2]++;
		vec_value.pop_back();
		vec_value.pop_back();
		vec_value.pop_back();
	}
	return 0;
}

//uint32_t player::Remain(uint32_t PAI[16])
//{
//	int sum = 0; 
//	for(int i=0;i<16;i++) 
//		sum += PAI[i]; 
//	return sum;
//}
