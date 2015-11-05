
#include "combination.h"
#include <time.h>
#include <algorithm>



Analyse::Analyse()
{
	//��ʼ������
	int blank = 0;

	for (int i = 1; i <= 13; i++)	//13*4,52������
	{
		for (int j = 0; j < 4; j++)
		{
			m_all_data.push_back(i);
		}
	}
	sort(m_all_data.begin(), m_all_data.end());
	int r_num = 0;
	srand(time(nullptr));
	for (int i = 0; i < 17; i++)
	{
		r_num = rand() % m_all_data.size();
		m_test_data.push_back(m_all_data[r_num]);
		auto it = m_all_data.begin() + r_num;
		m_all_data.erase(it);	//ɾ���Ѿ�push��ֵ�������ظ�ɾ��
	}

	/*
	m_test_data.clear();
	for (int i = 1; i < 14; i++)
	{
		if (1 == i || 2 == i )
		{
			continue;
		}
		m_test_data.push_back(i);
	}
	m_test_data.push_back(7);
	m_test_data.push_back(9);
	m_test_data.push_back(10);
	m_test_data.push_back(11);
	m_test_data.push_back(11);
	m_test_data.push_back(13);
	*/

	sort(m_test_data.begin(), m_test_data.end());
	int last_num = 0;
	/*
	for (auto it = m_test_data.begin(); it != m_test_data.end(); it++)
	{
		if (last_num != *it)
		{
			printf("\n");
		}
		printf("%d ", *it);
		last_num = *it;
	}
	*/
	m_store_data = m_test_data;
}

void Analyse::ClearCombina()
{
	//ǰ�ĸ������ǲ��ظ���
	m_single_card.clear();
	m_double_card.clear();
	m_three_card.clear();
	m_four_card.clear();
	//��3�������ǿ��������������ظ���
	m_single_line_card.clear();
	m_double_line_card.clear();
	m_three_line_card.clear();
}

void Analyse::CombinaCardSplit()
{
	//�Ȳ�ɵ��������ӣ�������ը���������ͣ����ĸ���������������ǻ����
	GetBase(m_test_data);
	//�ٲ����ͨ˳�ӣ����ԣ��ɻ��������������ͣ��������͵����ǿ��Կ��Խ����
	GetSingleLine();
	GetDoubleLine();
	GetThreeLine();
}

void Analyse::GetBase(vector<int> src_data)
{
	int lastcard = 0;
	int size = src_data.size();

	for (int i = 0; i < src_data.size(); i++)
	{
		if (i < size - 1 && src_data[i] == src_data[i + 1])	//������
		{
			if (i < size - 2 && src_data[i + 1] == src_data[i + 2])	//��������
			{
				if (i < size - 3 && src_data[i + 2] == src_data[i + 3])	//����
				{
					CombinaCard comb;
					for (int j = i; j < i + 4; j++)
					{
						comb.data.push_back(src_data[j]);
						comb.type = CT_BOMB_CARD;
					}
					m_four_card.push_back(comb);
					i = i + 3;	//���õ�ĩ��
					continue;
				}
				else
				{
					//����
					CombinaCard comb;
					for (int j = i; j < i + 3; j++)
					{
						comb.data.push_back(src_data[j]);
						comb.type = CT_THREE;
					}
					m_three_card.push_back(comb);
					i = i + 2;	//���õ�ĩ��
					continue;
				}
			}
			else
			{
				//����
				CombinaCard comb;
				for (int j = i; j < i + 2; j++)
				{
					comb.data.push_back(src_data[j]);
					comb.type = CT_DOUBLE;
				}
				m_double_card.push_back(comb);
				i = i + 1;	//���õ�ĩ��
				continue;
			}
		}
		else
		{
			CombinaCard comb;
			comb.data.push_back(src_data[i]);
			comb.type = CT_SINGLE;
			m_single_card.push_back(comb);
			continue;
		}
	}
}


void Analyse::GetSingleLine()
{
	vector<int> src_data;
	int line_num = 1;
	set<int> diff_data;	//���ظ���ֵ
	//�Ȼ�ȡ���еĶԣ���m_single,m_double_card��m_three_card��m_four_card��ȡ
	for (auto it = m_single_card.begin(); it != m_single_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}
	for (auto it = m_double_card.begin(); it != m_double_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}
	for (auto it = m_three_card.begin(); it != m_three_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}
	for (auto it = m_four_card.begin(); it != m_four_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}

	src_data.clear();	//ȥ��
	for (auto it = diff_data.begin(); it != diff_data.end(); it++)
	{
		src_data.push_back(*it);
	}
	
	vector<CombinaCard> tmp_data;
	CombinaCard comb;
	int size = src_data.size();
	for (int i = 0; i < src_data.size(); i++)
	{
		for (int j = i; j < src_data.size(); j++)
		{
			if (j < size - 1 && src_data[j] + 1 == src_data[j + 1])
			{
				line_num++;
			}
			else
			{
				if (line_num >= 5)	//����Ҫ5��
				{
					//�����5�����ϣ��Ͱ�5��6��7��8������Ϊ˳���Ʋ���tmp_data�������Ѿ��ҵ�3456789������7������ô34567��345678��3456789����������������tmp_data
					for (int k = i; k < i + 5; k++)
					{
						comb.data.push_back(src_data[k]);
						comb.type = CT_SINGLE_LINE;
					}
					
					tmp_data.push_back(comb);
					for (int k = i + 5; k < j + 1; k++)
					{
						comb.data.push_back(src_data[k]);
						comb.type = CT_SINGLE_LINE;
						tmp_data.push_back(comb);
					}
					comb.data.clear();
				}
				line_num = 1;
				break;	//����ѭ��
			}
		}
	}

	m_single_line_card = tmp_data;
}

void Analyse::GetDoubleLine()
{
	vector<int> src_data;
	int line_num = 1;
	set<int> diff_data;	//���ظ���ֵ
	//�Ȼ�ȡ���еĶԣ���m_double_card��m_three_card��m_four_card��ȡ
	for (auto it = m_double_card.begin(); it != m_double_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}
	for (auto it = m_three_card.begin(); it != m_three_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}
	for (auto it = m_four_card.begin(); it != m_four_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}
	src_data.clear();	//ȥ��
	for (auto it = diff_data.begin(); it != diff_data.end(); it++)
	{
		src_data.push_back(*it);
	}

	vector<CombinaCard> tmp_data;
	CombinaCard comb;
	int size = src_data.size();
	for (int i = 0; i < src_data.size(); i++)
	{
		for (int j = i; j < src_data.size(); j++)
		{
			if (j < size - 1 && src_data[j] + 1 == src_data[j + 1])
			{
				line_num++;
			}
			else
			{
				if (line_num >= 3)	//����ֻҪ3��
				{
					//�����3�����ϣ��Ͱ�3��4������Ϊ˳���Ʋ���tmp_data�������Ѿ��ҵ�33445566������4������ô334455��33445566��������������tmp_data
					for (int k = i; k < i + 3; k++)
					{
						comb.data.push_back(src_data[k]);	//��Ϊ��2��ͷ����push2��
						comb.data.push_back(src_data[k]);
						comb.type = CT_DOUBLE_LINE;
					}

					tmp_data.push_back(comb);
					for (int k = i + 3; k < j + 1; k++)
					{
						comb.data.push_back(src_data[k]);
						comb.data.push_back(src_data[k]);
						comb.type = CT_DOUBLE_LINE;
						tmp_data.push_back(comb);
					}
					comb.data.clear();
				}
				line_num = 1;
				break;	//����ѭ��
			}
		}
	}
	m_double_line_card = tmp_data;
}

void Analyse::GetThreeLine()
{
	vector<int> src_data;
	int line_num = 1;
	set<int> diff_data;	//���ظ���ֵ
	//�Ȼ�ȡ���еĶԣ���m_double_card��m_three_card��m_four_card��ȡ
	for (auto it = m_three_card.begin(); it != m_three_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}
	for (auto it = m_four_card.begin(); it != m_four_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}
	src_data.clear();	//ȥ��
	for (auto it = diff_data.begin(); it != diff_data.end(); it++)
	{
		src_data.push_back(*it);
	}

	vector<CombinaCard> tmp_data;
	CombinaCard comb;
	int size = src_data.size();
	for (int i = 0; i < src_data.size(); i++)
	{
		for (int j = i; j < src_data.size(); j++)
		{
			if (j < size - 1 && src_data[j] + 1 == src_data[j + 1])
			{
				line_num++;
			}
			else
			{
				if (line_num >= 2)	//3��ͷֻҪ2��
				{
					for (int k = i; k < i + 2; k++)
					{
						comb.data.push_back(src_data[k]);	//��Ϊ��3��ͷ����push3��
						comb.data.push_back(src_data[k]);
						comb.data.push_back(src_data[k]);
						comb.type = CT_DOUBLE_LINE;
					}

					tmp_data.push_back(comb);
					for (int k = i + 2; k < j + 1; k++)
					{
						comb.data.push_back(src_data[k]);
						comb.data.push_back(src_data[k]);
						comb.data.push_back(src_data[k]);
						comb.type = CT_DOUBLE_LINE;
						tmp_data.push_back(comb);
					}
					comb.data.clear();
				}
				line_num = 1;
				break;	//����ѭ��
			}
		}
	}
	m_three_line_card = tmp_data;
}

int Analyse::GetCardCombNum(vector<int> src_data, vector<CombinaCard> &final_comb, int extra_reduce_num)
{
	//����������㷨����˼·�ǣ��������ͷ�Ϊ3�֣��ٷ����͡��ڿ�����������Ƶ����͡��ۿ��ܲ����·��Ƶ����͡�
	//������ָ���ǵ��ţ��������ֵ���������������õ��ƣ�������������Ƶ�������ָ�������߷ɻ����ֿ��Դ����Ƶ����ͣ����ܲ����·��Ƶ�������ָ˳�����������������˷��ƺ���ܲ����µķ��Ƶ�����
	//ÿȥ�������͵�һ���ƺ�Ͱ������Ƶ�����ʹ��RemoveSubDataFromSrcData��Դ������ȥ����ȥ��������ʱ��Ϊ���Դ�������Ҫ
	int min_comb = 0;
	int comb_num = 0;
	int compare_comb = 0;
	int extra_num = 0;	//����Ĵ�����
	
	ClearCombina();	//������ڵݹ�ʱҪ������ʹ�õĳ�Ա����
	m_test_data = src_data;
	CombinaCardSplit();	//�ֽ�����

	auto single_card = m_single_card;
	auto double_card = m_double_card;
	auto three_card = m_three_card;
	auto four_card = m_four_card;
	//��3�������ǿ��������������ظ���
	auto single_line_card = m_single_line_card;
	auto double_line_card = m_double_line_card;
	auto three_line_card = m_three_line_card;

	min_comb = single_card.size() + double_card.size();
	int three = three_card.size();
	//��Ϊ3�����Դ��ƣ����Կ��Ժ��������鱻������������֣���0����
	if (extra_reduce_num != 0)
	{
		if (single_card.size() >= extra_reduce_num || double_card.size() >= extra_reduce_num)	
		{
			min_comb = min_comb - extra_reduce_num;	//����˵�ɻ���444555��ʣ��6,7����66��77
		}
		else if (m_single_card.size() + m_double_card.size() >= extra_reduce_num)
		{
			min_comb = min_comb - extra_reduce_num + 1;	//����˵�ɻ���444555��ʣ��6��77
		}
	}
	if (min_comb < three)	//�������m_single_card��m_double_card��������С����������������ôҪ��3��������
	{
		min_comb = three;
	}
	//��������������˾�˵��single_card.size()+double_card.size+three_card.size������������������Ҫ��ȥ�������ĺͷɻ�����
	if (single_line_card.size() <= 0 && double_line_card.size() <= 0 && three_line_card.size() <= 0)
	{
		final_comb.clear();
		for (auto it_three = three_card.begin(); it_three != three_card.end(); it_three++)
		{
			final_comb.push_back(*it_three);
		}
		for (auto it_double : double_card)
		{
			final_comb.push_back(it_double);
		}
		for (auto it_single : single_card)
		{
			final_comb.push_back(it_single);
		}
		for (auto it_four : four_card)
		{
			final_comb.push_back(it_four);
		}
		if (four_card.size() > 0)
		{
			min_comb = min_comb - four_card.size();
		}
		return min_comb;
	}
	else
	{
		vector<int> store_data = m_test_data;
		compare_comb = min_comb;
		CombinaCard min_comb;
		//��˳�ӷ���
		for (auto it_single = single_line_card.begin(); it_single != single_line_card.end(); it_single++)	//˳��
		{
			vector<int> current_data = store_data;
			vector<CombinaCard> store_comb;
			RemoveSubDataFromSrcData(current_data, it_single->data);
			comb_num = GetCardCombNum(current_data, store_comb, extra_reduce_num);
			if (comb_num + 1 < compare_comb)	//+1�����ϵ�ǰ��
			{
				compare_comb = comb_num+1;
				min_comb = *it_single;
				final_comb.clear();
				final_comb = store_comb;
			}
			
		}
		//�����Է���
		for (auto it_double = double_line_card.begin(); it_double != double_line_card.end(); it_double++)	//����
		{
			vector<int> current_data = store_data;
			vector<CombinaCard> store_comb;
			RemoveSubDataFromSrcData(current_data, it_double->data);
			comb_num = GetCardCombNum(current_data, store_comb, extra_reduce_num);
			
			
			if (comb_num + 1 < compare_comb)	//+1�����ϵ�ǰ��
			{
				compare_comb = comb_num + 1;
				min_comb = *it_double;
				final_comb.clear();
				final_comb = store_comb;
			}
			
		}
		//�ӷɻ�����
		for (auto it_three = three_line_card.begin(); it_three != three_line_card.end(); it_three++)	//����
		{
			vector<int> current_data = store_data;
			vector<CombinaCard> store_comb;
			RemoveSubDataFromSrcData(current_data, it_three->data);
			comb_num = GetCardCombNum(current_data, store_comb, extra_reduce_num + it_three->data.size() / 3);	//���Ͽ��Զ������������
			//extra_num = ;
			if (comb_num + 1 < compare_comb)	//+1�����ϵ�ǰ��
			{
				compare_comb = comb_num + 1;
				min_comb = *it_three;
				final_comb.clear();
				final_comb = store_comb;
			}
		}
		if (min_comb.type != 0)
		{
			final_comb.push_back(min_comb);
		}
	}

	return compare_comb;
}

void Analyse::RemoveSubDataFromSrcData(vector<int> &src_data, vector<int> sub_data)
{
	for (auto it_sub : sub_data)
	{
		for (auto it_src = src_data.begin(); it_src != src_data.end(); it_src++)
		{
			if (it_sub == *it_src)
			{
				src_data.erase(it_src);
				break;
			}
		}
	}
}



int main()
{
	time_t now = time(nullptr);
	printf("now = %lld\n", now);
	int i = 0;
	while (1)
	{
		Analyse C1;
		C1.m_store_data = C1.m_test_data;
		vector<CombinaCard> final_comb;
		int num = C1.GetCardCombNum(C1.m_test_data, final_comb);
		i++;
		if (i > 10000)
		{
			break;
		}
	}
	
	now = time(nullptr);
	printf("now = %lld\n", now);

	return 0;
}