#include "player.h"

//�������ϵ��ƣ�������ֵ��С����
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
//��һ����Ϸ��ʼʱ���ó�ʼ��ÿ�����
void player::on_new_game()	// ��ʼһ����Ϸʱ����
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
	m_miao_shou_hui_chun = false;		// �������ⷬ�ͣ����ֻش�
	m_hai_di_lao_yue = false;			// �������ⷬ�ͣ���������
	m_gang_shang_kai_hua = false;		// �������ⷬ�ͣ����Ͽ���
	m_qiang_gang_hu = false;			// �������ⷬ�ͣ����ܺ�
	m_flag_for_ming_an[0] = 0;
	m_flag_for_ming_an[1] = 0;
	m_flag_for_ming_an[2] = 0;
	m_flag_for_ming_an[3] = 0;
}
//������ͱ�
void player::LoadChewTable()
{
	std::vector<chew_struct_data> vec_data;
	chew_struct_data chew_data;
	//һ��
	vec_data.clear();
	chew_data.pai1 = value_bamboo_2;
	chew_data.pai2 = value_bamboo_3;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_1,vec_data));
	//����
	vec_data.clear();
	chew_data.pai1 = value_bamboo_1;
	chew_data.pai2 = value_bamboo_3;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_3;
	chew_data.pai2 = value_bamboo_4;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_2,vec_data));
	//����
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
	//����
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
	//����
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
	//����
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
	//����
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
	//����
	vec_data.clear();
	chew_data.pai1 = value_bamboo_6;
	chew_data.pai2 = value_bamboo_7;
	vec_data.push_back(chew_data);
	chew_data.pai1 = value_bamboo_7;
	chew_data.pai2 = value_bamboo_9;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_8,vec_data));
	//����
	vec_data.clear();
	chew_data.pai1 = value_bamboo_7;
	chew_data.pai2 = value_bamboo_8;
	vec_data.push_back(chew_data);
	m_map_table_for_chew.insert(std::make_pair(value_bamboo_9,vec_data));
}
//������е��жϱ�,����CheckAllJudgeǰ�ȵ��ô˺����������ǰһ�ε�
void player::ClearAllJudge()													
	{
		//�����жϵ��ݴ��б�
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
		//�������б�
		for (uint32_t i = 0; i < 7; i++)
		{
			m_judge_flag[i] = 0;
		}
	}
//�������
void player::CheckAllJudge()
{
	ClearAllJudge();
	CStringA log_str;log_str.Format(" ����CheckAllJudge����,m_current_status=%d",m_current_status);//WriteLog(log_str);
	
	if (is_ting)//�Ѿ����˾�ֻ����
	{
		log_str.Format(" is_ting=true");//WriteLog(log_str);
		CheckHu();
		if (m_check_hu[0] != id_unknown)//���˿ɺ����������10������
		{
			m_hu_clock_when_is_ting = 0;
		}
		return;
	}
	//else if (is_auto)//����������ֻ���йܣ�ʲô��ʾ��������ֱ�ӷ��ƴ���
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
	//���˷�����ӱ��󣬴˱��������true��ֱ���´β�������������ڼ�����������Ϊfalse���Ͳ���Ӱ�쵽�Ժ�ļ��
	m_is_jia_bei_check_ting = false;
	
	log_str.Format("����CheckAllJudge����,m_judge_flag[6]=%d,m_judge_flag[5]=%d",m_judge_flag[6],m_judge_flag[5]);//WriteLog(log_str);
}
//����
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
	for (uint32_t i = 0; i < iter->second.size();i++)//�����ɳԱ�
	{
		temp_data.init();
		for (uint32_t j = 0; j < m_pais_in_hand.size();j++)//����������
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
//�����
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
//��ⰵ��
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
//�������1
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
				count++;//�����Ʋ���ǰ��
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
//�������2
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
//����
void player::CheckHu()
{
	m_hu_status = 0;//�ȸ�Ĭ��ֵ
	//��ͨ��
	pai_kind pai_kind_;
	uint32_t PAI[16] = {0};
	uint32_t tempPAI[16]={0};//�������˻������������������
	for (uint32_t i = 0; i < m_pais_in_hand.size(); i++)
	{
		if (m_pais_in_hand[i].u32ValueCard == value_flower)
		{
			return;//�л����ܺ�
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
		//ʹ�øĽ���ķ��ͼ�����
		PreProcess();
		int fan = m_normal_fan_helper.CountFan();
		m_check_hu[1] = fan;
		//CStringA log_str;log_str.Format("�·��ͼ���������ķ�����%d",fan);WriteLog(log_str);
		//
		m_judge_flag[6] = 1;//��ֻ��һ��
		m_hu_status = 1;
	}
	else
	{
		//����������������
		//�߶�
		if(m_pais_chew_pong_kong.size()>0)
		{
			return;//ֻҪ�г����ܵģ��Ͳ����߶�
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
				pair_count += 2;//�˶�ֻΪ�ĸ�ͷ�ж�Ϊ����
			}
		}
		if (pair_count == 7)
		{
			m_check_hu[0] = m_last_pai;
			//m_check_hu[1] = GetHuFan();
			m_judge_flag[6] = 1;//��ֻ��һ��
			//ʹ�øĽ���ķ��ͼ�����
			PreProcess2(tempPAI);
			int fan = m_qidui_fan_helper.CountFan();
			m_check_hu[1] = fan;
			//CStringA log_str;log_str.Format("�·����߶Լ���������ķ�����%d",fan);WriteLog(log_str);
			//
			m_hu_status = 2;
		}
	}
}
//�����
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
			//ȥ��һ��i������һ��j
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
			
			//�߶��ж�
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
					pair_count+=2;//�˶�ֻΪ�ĸ�ͷ�ж�Ϊ����
				}
			}
			if (pair_count == 7)
			{
				isqidui = true;
			}
			//�߶��ж�
			if (Hu(input_pai) || isqidui)//���ü�������������
			{
				bool only_once = false;
				//��ѯʣ�»��м���
				for (uint32_t k = 0;k < m_all_pais.size();k++)
				{
					if (m_all_pais[k].u32ValueCard == j+1)
					{
						m_check_ting[0][i][j]++;
						m_judge_flag[5]++;
						if (!only_once)
						{
							m_check_ting[1][i][j] = GetTingFan(j+1,i+1);
							only_once = true;//ֻ����һ�Σ����Ч��
						}
					}
				}
				//���˲�ѯʣ�µ��ƣ���Ҫ��ѯ�Լ����ϵ��ƣ�������Ҫ���밵�ܣ�
				for (uint32_t k = 0; k < m_oppisite_player->m_pais_in_hand.size(); k++)
				{
					if (m_oppisite_player->m_pais_in_hand[k].u32ValueCard == j+1)
					{
						m_check_ting[0][i][j]++;
						m_judge_flag[5]++;
						if (!only_once)
						{
							m_check_ting[1][i][j] = GetTingFan(j+1,i+1);
							only_once = true;//ֻ����һ�Σ����Ч��
						}
					}
				}
			}
			if (j > 15 || j < 0 || i > 15 || i < 0)
			{
				CStringA log_str;log_str.Format("CheckTing����Խ�磬i=%d��j=%d",i,j);WriteLog(log_str);
				return;
			}
			PAI[j]--;
			PAI[i]++;
		}
	}
}
//�����жϺ���
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
//�����βΰ�һ����������Ȼ���������з��ױ��
uint32_t player::Remain(uint32_t PAI[16])
{
	int sum = 0; 
	for(int i=0;i<16;i++) 
		sum += PAI[i]; 
	return sum;
}
//���������
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
	m_fan_helper.pai_in_hand_count = m_pais_in_hand.size();//���ϵ�������
	m_fan_helper.m_ming_gang_count1 = m_ming_gang_count1;
	m_fan_helper.m_ming_gang_count2 = m_ming_gang_count2;
	m_fan_helper.m_an_gang_count = m_an_gang_count;
	m_fan_helper.m_flowers = m_pais_flowers.size();
	m_fan_helper.m_is_quan_dai_yao = false;
	m_fan_helper.m_total_gang_count = m_fan_helper.m_ming_gang_count1 + m_fan_helper.m_ming_gang_count2 + m_fan_helper.m_an_gang_count;
	int64_t temp;//û��
	return GetFan(temp,false);
}
//����������
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
	//ɾһ��
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
	//��һ��
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
	m_fan_helper.pai_in_hand_count = m_pais_in_hand.size();//���ϵ�������
	m_fan_helper.m_ming_gang_count1 = m_ming_gang_count1;
	m_fan_helper.m_ming_gang_count2 = m_ming_gang_count2;
	m_fan_helper.m_an_gang_count = m_an_gang_count;
	m_fan_helper.m_flowers = m_pais_flowers.size();
	m_fan_helper.m_is_quan_dai_yao = false;
	m_fan_helper.m_total_gang_count = m_fan_helper.m_ming_gang_count1 + m_fan_helper.m_ming_gang_count2 + m_fan_helper.m_an_gang_count;
	int64_t temp = 0;//û��
	return GetFan(temp,false);
}
//���㷬��
uint32_t player::GetFan(int64_t &fan_flag,bool bComputeIt)
{
	bool bWriteFanXing = false;
	CStringA log_str;log_str.Format("���㷬�ͣ�");if(bWriteFanXing)WriteLog(log_str);
	uint32_t total_fan_count = m_fan_helper.m_flowers;
	if (m_fan_helper.IsDaSiXi())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("����ϲ");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000001;
		}
	}
	if (m_fan_helper.IsDaSanYuan())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("����Ԫ");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000002;
		}
	}
	if (m_fan_helper.IsLvYiSe())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("��һɫ");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000004;
		}
	}
	if (m_fan_helper.IsJiuLianBaoDeng())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("��������");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000008;
		}
	}
	if (m_fan_helper.IsSiGang())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("�ĸ�");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000010;
		}
	}
	if (m_fan_helper.IsLianQiDui())
	{
		total_fan_count += 88;
		CStringA log_str;log_str.Format("���߶�");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000020;
		}
	}
	if (m_fan_helper.IsXiaoSiXi())
	{
		total_fan_count += 64;
		CStringA log_str;log_str.Format("С��ϲ");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000040;
		}
	}
	if (m_fan_helper.IsXiaoSanYuan())
	{
		total_fan_count += 64;
		CStringA log_str;log_str.Format("С��Ԫ");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000080;
		}
	}
	if (m_fan_helper.IsZiYiSe())
	{
		total_fan_count += 64;
		CStringA log_str;log_str.Format("��һɫ");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000100;
		}
	}
	if (m_fan_helper.IsSiAnKe())
	{
		total_fan_count += 64;
		CStringA log_str;log_str.Format("�İ���");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000200;
		}
	}
	if (m_fan_helper.IsYiSeShuangLongHui())
	{
		total_fan_count += 64;
		CStringA log_str;log_str.Format("һɫ˫����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000400;
		}
	}
	if (m_fan_helper.IsYiSeSiTongShun())
	{
		total_fan_count += 48;
		CStringA log_str;log_str.Format("һɫ��ͬ˳");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000000800;
		}
	}
	if (m_fan_helper.IsYiSeSiJieGao())
	{
		total_fan_count += 48;
		CStringA log_str;log_str.Format("һɫ�Ľڸ�");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000001000;
		}
	}
	if (m_fan_helper.IsYiSeSiBuGao())
	{
		total_fan_count += 32;
		CStringA log_str;log_str.Format("һɫ�Ĳ���");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000002000;
		}
	}
	if (m_fan_helper.IsSanGang())
	{
		total_fan_count += 32;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000004000;
		}
	}
	if (m_fan_helper.IsHunYaoJiu())
	{
		total_fan_count += 32;
		CStringA log_str;log_str.Format("���۾�");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000008000;
		}
	}
	if (m_fan_helper.IsQiDui())
	{
		total_fan_count += 24;
		CStringA log_str;log_str.Format("�߶�");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000010000;
		}
	}
	if (m_fan_helper.IsQingYiSe())
	{
		total_fan_count += 24;
		CStringA log_str;log_str.Format("��һɫ");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000020000;
		}
	}
	if (m_fan_helper.IsYiSeSanTongShun())
	{
		total_fan_count += 24;
		CStringA log_str;log_str.Format("һɫ��ͬ˳");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000040000;
		}
	}
	if (m_fan_helper.IsYiSeSanJieGao())
	{
		total_fan_count += 24;
		CStringA log_str;log_str.Format("һɫ���ڸ�");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000080000;
		}
	}
	if (m_fan_helper.IsQingLong())
	{
		total_fan_count += 16;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000100000;
		}
	}
	if (m_fan_helper.IsYiSeSanBuGao())
	{
		total_fan_count += 16;
		CStringA log_str;log_str.Format("һɫ������");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000200000;
		}
	}
	if (m_fan_helper.IsSanAnKe())
	{
		total_fan_count += 16;
		CStringA log_str;log_str.Format("������");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000400000;
		}
	}
	if (m_fan_helper.IsDaYuWu())
	{
		total_fan_count += 12;
		CStringA log_str;log_str.Format("������");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000000800000;
		}
	}
	if (m_fan_helper.IsXiaoYuWu())
	{
		total_fan_count += 12;
		CStringA log_str;log_str.Format("С����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000001000000;
		}
	}
	if (m_fan_helper.IsSanFengKe())
	{
		total_fan_count += 12;
		CStringA log_str;log_str.Format("�����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000002000000;
		}
	}
	if (m_fan_helper.IsTuiBuDao())
	{
		total_fan_count += 8;
		CStringA log_str;log_str.Format("�Ʋ���");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000004000000;
		}
	}
	if (m_fan_helper.IsSanSeSanTongShun())
	{
		total_fan_count += 8;
		CStringA log_str;log_str.Format("��ɫ��ͬ˳");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000008000000;
		}
	}
	if (m_fan_helper.IsSanSeSanJieGao())
	{
		total_fan_count += 8;
		CStringA log_str;log_str.Format("��ɫ���ڸ�");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000010000000;
		}
	}
	if (m_fan_helper.IsWuFanHu())
	{
		total_fan_count += 8;
		CStringA log_str;log_str.Format("�޷���");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000020000000;
		}
	}
	if (m_fan_helper.IsPengPengHu())
	{
		total_fan_count += 6;
		CStringA log_str;log_str.Format("������");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000040000000;
		}
	}
	if (m_fan_helper.IsHunYiSe())
	{
		total_fan_count += 6;
		CStringA log_str;log_str.Format("��һɫ");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000080000000;
		}
	}
	if (m_fan_helper.IsQuanQiuRen())
	{
		total_fan_count += 6;
		CStringA log_str;log_str.Format("ȫ����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000100000000;
		}
	}
	if (m_fan_helper.IsShuangAnGang())
	{
		total_fan_count += 6;
		CStringA log_str;log_str.Format("˫����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000200000000;
		}
	}
	if (m_fan_helper.IsShuangJianKe())
	{
		total_fan_count += 6;
		CStringA log_str;log_str.Format("˫����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000400000000;
		}
	}
	if (m_fan_helper.IsQuanDaiYao())
	{
		total_fan_count += 4;
		CStringA log_str;log_str.Format("ȫ����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000000800000000;
		}
	}
	if (m_fan_helper.IsBuQiuRen())
	{
		total_fan_count += 4;
		CStringA log_str;log_str.Format("������");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000001000000000;
		}
	}
	if (m_fan_helper.IsShuangMingGang())
	{
		total_fan_count += 4;
		CStringA log_str;log_str.Format("˫����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000002000000000;
		}
	}
	if (m_fan_helper.IsJianKe())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000004000000000;
		}
	}
	if (m_fan_helper.IsMenQianQing())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("��ǰ��");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000008000000000;
		}
	}
	if (m_fan_helper.IsPingHu())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("ƽ��");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000010000000000;
		}
	}
	if (m_fan_helper.IsSiGuiYi())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("�Ĺ�һ");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000020000000000;
		}
	}
	if (m_fan_helper.IsShuangAnKe())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("˫����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000040000000000;
		}
	}
	if (m_fan_helper.IsAnGang())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000080000000000;
		}
	}
	if (m_fan_helper.IsDuanYao())
	{
		total_fan_count += 2;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000100000000000;
		}
	}
	if (m_fan_helper.IsYiBanGao())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("һ���");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000200000000000;
		}
	}
	if (m_fan_helper.IsXiXiangFeng())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("ϲ���");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000400000000000;
		}
	}
	if (m_fan_helper.IsLianLiu())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0000800000000000;
		}
	}
	if (m_fan_helper.IsLaoShaoFu())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("���ٸ�");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0001000000000000;
		}
	}
	if (m_fan_helper.IsYaoJiuKe())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("�۾ſ�");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0002000000000000;
		}
	}
	if (m_fan_helper.IsMingGang())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0004000000000000;
		}
	}
	if (m_fan_helper.IsQueYiMen())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("ȱһ��");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0008000000000000;
		}
	}
	if (m_fan_helper.IsWuZi())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0010000000000000;
		}
	}
	if (m_fan_helper.IsBianZhang())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0020000000000000;
		}
	}
	if (m_fan_helper.IsKanZhang())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0040000000000000;
		}
	}
	if (m_fan_helper.IsDanDiaoJiang())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("������");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0080000000000000;
		}
	}
	if (m_fan_helper.IsZiMo())
	{
		total_fan_count += 1;
		CStringA log_str;log_str.Format("����");if(bWriteFanXing)WriteLog(log_str);
		if (bComputeIt)
		{
			fan_flag = fan_flag | 0x0100000000000000;
		}
	}
	return total_fan_count;
}
//����Ƿ������л�,�У����ػ���Ψһֵ���񣬷���0
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
//�����������油�������ƣ�Ψһֵ
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
//��һ����,����Ψһֵ
void player::AddACard(uint32_t u32RealCard)
{
	pai_kind pai_kind_;
	pai_kind_.u32RealCard = u32RealCard;
	pai_kind_.u32Status = status_in_hand_normal;
	pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
	m_pais_in_hand.push_back(pai_kind_);
}
//���öԼ���������״̬
void player::SetOppisiteZiMoStatus()
{
	m_oppisite_player->m_current_status = 2;
}
//�����Լ���������״̬
void player::SetMyZiMoStatus()
{
	m_current_status = 1;
}
//�����������
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
	m_fan_helper.m_is_gang_shang_kai_hua = false;//�������Ƶ�ʱ��ظܱ��
	m_fan_helper.m_is_qiang_gang_hu = false;//�Լ������ˣ��ر����ܺ�
	m_gang_shang_kai_hua = false;
	m_qiang_gang_hu = false;
	return true;
}
//�������
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
			//�쳣�����ƾ������ȴ����½��ܳ�������
			return false;
		}

		//temp_vec.push_back(m_oppisite_player->m_pais_on_table[m_oppisite_player->m_pais_on_table.size()-1]);//������
		//ret0 = m_oppisite_player->m_pais_on_table[m_oppisite_player->m_pais_on_table.size()-1].u32RealCard;
		//���������ʱ��֪��ʲôԭ�򣬾ͷŽ���8����9�������磬���Ÿ���һ��m_last_pai
		pai_kind pai_kind_;
		pai_kind_.u32RealCard = m_last_pai;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		pai_kind_.u32Status = status_chew_self;
		temp_vec.push_back(pai_kind_);
		ret0 = m_last_pai;
		ret1 = m_vec_check_chew[index].pai1;
		ret2 = m_vec_check_chew[index].pai2;
		m_pais_chew_pong_kong.push_back(temp_vec);
		//CStringA log_str;log_str.Format("ProcessChi��m_pais_chew_pong_kong������һ��vector�����ڴ�С��%d",m_pais_chew_pong_kong.size());WriteLog(log_str);
		//if (m_pais_chew_pong_kong.size() > 4)
		//{
		//	//�쳣
		//	int xxx[2] = {0};
		//	xxx[2] = 1;
		//}
		m_oppisite_player->m_pais_on_table.pop_back();
		return true;
	}
	return false;
}
//��������
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
			//�쳣
			return false;
		}
		//temp_vec.push_back(m_oppisite_player->m_pais_on_table[m_oppisite_player->m_pais_on_table.size()-1]);//������
		//ret0 = m_oppisite_player->m_pais_on_table[m_oppisite_player->m_pais_on_table.size()-1].u32RealCard;
		//��Ҳ����ͬ��һ�����㷨
		pai_kind pai_kind_;
		pai_kind_.u32RealCard = m_last_pai;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		pai_kind_.u32Status = status_pong_self;
		temp_vec.push_back(pai_kind_);
		ret0 = m_last_pai;
		ret1 = m_vec_check_peng[index].pai1;
		ret2 = m_vec_check_peng[index].pai2;
		m_pais_chew_pong_kong.push_back(temp_vec);
		//CStringA log_str;log_str.Format("ProcessPeng��m_pais_chew_pong_kong������һ��vector�����ڴ�С��%d",m_pais_chew_pong_kong.size());WriteLog(log_str);
		//if (m_pais_chew_pong_kong.size() > 4)
		//{
		//	//�쳣
		//	int xxx[2] = {0};
		//	xxx[2] = 1;
		//}
		m_oppisite_player->m_pais_on_table.pop_back();
		return true;
	}

	return false;
}
//������
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
				iter->u32Status = status_kong_oppisite;//�˴�����ʵ����1
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
			//�쳣
			return false;
		}
		//temp_vec.push_back(m_oppisite_player->m_pais_on_table[m_oppisite_player->m_pais_on_table.size()-1]);//������
		pai_kind pai_kind_;
		pai_kind_.u32RealCard = m_last_pai;
		pai_kind_.u32Status = status_kong_oppisite;
		pai_kind_.u32ValueCard = pai_kind_.GetValueFromRealCard(pai_kind_.u32RealCard);
		temp_vec.push_back(pai_kind_);
		m_pais_chew_pong_kong.push_back(temp_vec);
		m_flag_for_ming_an[m_pais_chew_pong_kong.size()-1] = 1;
		//CStringA log_str;log_str.Format("ProcessAnGang��m_pais_chew_pong_kong������һ��vector�����ڴ�С��%d",m_pais_chew_pong_kong.size());WriteLog(log_str);
		//if (m_pais_chew_pong_kong.size() > 4)
		//{
		//	//�쳣
		//	int xxx[2] = {0};
		//	xxx[2] = 1;
		//}
		m_oppisite_player->m_pais_on_table.pop_back();
		m_fan_helper.m_is_gang_shang_kai_hua = true;
		m_oppisite_player->m_fan_helper.m_is_qiang_gang_hu = true;
		m_fan_helper.m_is_qiang_gang_hu = false;//�Լ����ˣ��ر����ܺ�

		m_gang_shang_kai_hua = true;
		m_qiang_gang_hu = false;
		m_oppisite_player->m_qiang_gang_hu = true;
		return true;
	}
	return false;
}
//��������1
bool player::ProcessMingGang1(uint32_t u32Value)
{
	int count_exception = 0;
	std::vector<pai_kind>::iterator iter = m_pais_in_hand.begin();
	std::vector<pai_kind> temp_vec;
	for (; iter != m_pais_in_hand.end();)
	{
		if ((*iter).u32ValueCard == u32Value)
		{
			iter->u32Status = status_kong_self;//�˴���1��ʵ��
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
		//�쳣
		return false;
	}
	m_pais_chew_pong_kong.push_back(temp_vec);
	m_flag_for_ming_an[m_pais_chew_pong_kong.size()-1] = 2;
	//CStringA log_str;log_str.Format("ProcessMingGang1��m_pais_chew_pong_kong������һ��vector�����ڴ�С��%d",m_pais_chew_pong_kong.size());WriteLog(log_str);
	//if (m_pais_chew_pong_kong.size() > 4)
	//{
	//	//�쳣
	//	int xxx[2] = {0};
	//	xxx[2] = 1;
	//}
	m_ming_gang_count1++;
	m_fan_helper.m_is_gang_shang_kai_hua = true;
	m_fan_helper.m_is_qiang_gang_hu = false;//�Լ����ˣ��ر����ܺ�
	m_gang_shang_kai_hua = true;
	m_qiang_gang_hu = false;
	return true;
}
//��������2
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
		//�쳣
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
	m_fan_helper.m_is_qiang_gang_hu = false;//�Լ����ˣ��ر����ܺ�

	m_gang_shang_kai_hua = true;
	m_oppisite_player->m_qiang_gang_hu = true;
	m_qiang_gang_hu = false;
	return true;
}
//�������
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
//������
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
				if(m_check_ting[0][i][j] > 0)//����Ĳ���Ϊ0���ɻ�����Ҫ����ʱ�򴫽����ģ����������������
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
//����ӱ�
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
//�������һ����
void player::SetLastPai(uint32_t pai)
{
	m_last_pai = pai;
}
//����һ��������
void player::SetAllPai(std::vector<pai_kind> pai_group)
{
	m_all_pais = pai_group;
}

//���ͼ���ǰ��Ԥ����
void player::PreProcess()
{
	m_normal_fan_helper.ResetAllData();
	//�Ѿ������ܵ���
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
				//����
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
	//δ�����ܵ���
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
		if (vec_value[k] > 100 && vec_value[k] < 1000)//����
		{
			pai_group pai_group_;
			pai_group_.value1 = vec_value[k]-100;
			pai_group_.value_type = value_kezi_weipeng;
			m_normal_fan_helper.SetData(pai_group_ ,l);
			l++;
		}
		else if (vec_value[k] > 1000)//˳��
		{
			pai_group pai_group_;
			pai_group_.value1 = vec_value[k]-1000;
			pai_group_.value2 = vec_value[k+1]-1000;
			pai_group_.value3 = vec_value[k+2]-1000;
			pai_group_.value_type = value_shunzi_weichi;
			//����
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
	CStringA log_str;log_str.Format("m_normal_fan_helper�������ƣ�һ%d��%d,%d,%d.��%d,%d,%d,%d,��%d,%d,%d,%d,��%d,%d,%d,%d,��%d,%d,%d,%d",
		m_normal_fan_helper.m_5zupai[0].value1,m_normal_fan_helper.m_5zupai[0].value2,m_normal_fan_helper.m_5zupai[0].value3,m_normal_fan_helper.m_5zupai[0].value_type,
		m_normal_fan_helper.m_5zupai[1].value1,m_normal_fan_helper.m_5zupai[1].value2,m_normal_fan_helper.m_5zupai[1].value3,m_normal_fan_helper.m_5zupai[1].value_type,
		m_normal_fan_helper.m_5zupai[2].value1,m_normal_fan_helper.m_5zupai[2].value2,m_normal_fan_helper.m_5zupai[2].value3,m_normal_fan_helper.m_5zupai[2].value_type,
		m_normal_fan_helper.m_5zupai[3].value1,m_normal_fan_helper.m_5zupai[3].value2,m_normal_fan_helper.m_5zupai[3].value3,m_normal_fan_helper.m_5zupai[3].value_type,
		m_normal_fan_helper.m_5zupai[4].value1,m_normal_fan_helper.m_5zupai[4].value2,m_normal_fan_helper.m_5zupai[4].value3,m_normal_fan_helper.m_5zupai[4].value_type);//WriteLog(log_str);
	m_normal_fan_helper.CheckAllFan();
	m_normal_fan_helper.DeleteAllRepeat();

}
//���ͼ��㣨�߶�ר�ã�
void player::PreProcess2(uint32_t qiduipai[16])
{
	m_qidui_fan_helper.ResetAllData();
	//�߶Խ���δ�����ܵ���
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
	CStringA log_str;log_str.Format("m_qidui_fan_helper�������ƣ�һ%d,%d,��%d,%d,��%d,%d,��%d,%d,��%d,%d,��%d,%d,��%d,%d",
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
//�����󽫷���Ҳ�����ͻ���ʱ�õ�
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
//���ͼ��㸨������
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
		vec_value.push_back(i+1+100);//���100Ϊ����
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
		vec_value.push_back(i+3+1000);//���1000Ϊ˳��
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
