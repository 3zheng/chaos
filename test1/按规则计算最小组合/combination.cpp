
#include "combination.h"
#include <time.h>
#include <algorithm>



Analyse::Analyse()
{
	//初始化数据
	int blank = 0;

	for (int i = 1; i <= 13; i++)	//13*4,52个数据
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
		m_all_data.erase(it);	//删除已经push的值，避免重复删除
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
	//前四个数据是不重复的
	m_single_card.clear();
	m_double_card.clear();
	m_three_card.clear();
	m_four_card.clear();
	//后3个数据是可以与其他数据重复的
	m_single_line_card.clear();
	m_double_line_card.clear();
	m_three_line_card.clear();
}

void Analyse::CombinaCardSplit()
{
	//先拆成单个，对子，三个，炸弹基本牌型，这四个基本牌型里的牌是互斥的
	GetBase(m_test_data);
	//再拆成普通顺子，连对，飞机这样的特殊牌型，特殊牌型的牌是可以可以交叉的
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
		if (i < size - 1 && src_data[i] == src_data[i + 1])	//对以上
		{
			if (i < size - 2 && src_data[i + 1] == src_data[i + 2])	//三张以上
			{
				if (i < size - 3 && src_data[i + 2] == src_data[i + 3])	//四张
				{
					CombinaCard comb;
					for (int j = i; j < i + 4; j++)
					{
						comb.data.push_back(src_data[j]);
						comb.type = CT_BOMB_CARD;
					}
					m_four_card.push_back(comb);
					i = i + 3;	//设置到末张
					continue;
				}
				else
				{
					//三张
					CombinaCard comb;
					for (int j = i; j < i + 3; j++)
					{
						comb.data.push_back(src_data[j]);
						comb.type = CT_THREE;
					}
					m_three_card.push_back(comb);
					i = i + 2;	//设置到末张
					continue;
				}
			}
			else
			{
				//对子
				CombinaCard comb;
				for (int j = i; j < i + 2; j++)
				{
					comb.data.push_back(src_data[j]);
					comb.type = CT_DOUBLE;
				}
				m_double_card.push_back(comb);
				i = i + 1;	//设置到末张
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
	set<int> diff_data;	//不重复的值
	//先获取所有的对，从m_single,m_double_card，m_three_card，m_four_card里取
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

	src_data.clear();	//去重
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
				if (line_num >= 5)	//单个要5连
				{
					//如果是5连以上，就把5、6、7、8连都作为顺子牌插入tmp_data，比如已经找到3456789这样的7连，那么34567、345678、3456789这样的三连都插入tmp_data
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
				break;	//跳出循环
			}
		}
	}

	m_single_line_card = tmp_data;
}

void Analyse::GetDoubleLine()
{
	vector<int> src_data;
	int line_num = 1;
	set<int> diff_data;	//不重复的值
	//先获取所有的对，从m_double_card，m_three_card，m_four_card里取
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
	src_data.clear();	//去重
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
				if (line_num >= 3)	//对子只要3连
				{
					//如果是3连以上，就把3，4连都作为顺子牌插入tmp_data，比如已经找到33445566这样的4连，那么334455、33445566这样的连都插入tmp_data
					for (int k = i; k < i + 3; k++)
					{
						comb.data.push_back(src_data[k]);	//因为是2个头所以push2次
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
				break;	//跳出循环
			}
		}
	}
	m_double_line_card = tmp_data;
}

void Analyse::GetThreeLine()
{
	vector<int> src_data;
	int line_num = 1;
	set<int> diff_data;	//不重复的值
	//先获取所有的对，从m_double_card，m_three_card，m_four_card里取
	for (auto it = m_three_card.begin(); it != m_three_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}
	for (auto it = m_four_card.begin(); it != m_four_card.end(); it++)
	{
		diff_data.insert(it->data[0]);
	}
	src_data.clear();	//去重
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
				if (line_num >= 2)	//3个头只要2连
				{
					for (int k = i; k < i + 2; k++)
					{
						comb.data.push_back(src_data[k]);	//因为是3个头所以push3次
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
				break;	//跳出循环
			}
		}
	}
	m_three_line_card = tmp_data;
}

int Analyse::GetCardCombNum(vector<int> src_data, vector<CombinaCard> &final_comb, int extra_reduce_num)
{
	//这个函数的算法基本思路是，所有牌型分为3种，①废牌型、②可消耗任意废牌的牌型、③可能产生新废牌的牌型。
	//废牌型指的是单张，单对这种单独计算对手数无用的牌；可消耗任意废牌的牌型是指三个或者飞机这种可以带废牌的牌型；可能产生新废牌的牌型是指顺子连对这种在消耗了废牌后可能产生新的废牌的牌型
	//每去掉③牌型的一手牌后就把这手牌的数据使用RemoveSubDataFromSrcData从源数据中去掉，去掉②牌型时因为可以带牌所以要
	int min_comb = 0;
	int comb_num = 0;
	int compare_comb = 0;
	int extra_num = 0;	//额外的带牌数
	
	ClearCombina();	//先清掉在递归时要被反复使用的成员变量
	m_test_data = src_data;
	CombinaCardSplit();	//分解牌型

	auto single_card = m_single_card;
	auto double_card = m_double_card;
	auto three_card = m_three_card;
	auto four_card = m_four_card;
	//后3个数据是可以与其他数据重复的
	auto single_line_card = m_single_line_card;
	auto double_line_card = m_double_line_card;
	auto three_line_card = m_three_line_card;

	min_comb = single_card.size() + double_card.size();
	int three = three_card.size();
	//因为3个可以带牌，所以可以和其他牌组被带掉的手数相抵，算0手数
	if (extra_reduce_num != 0)
	{
		if (single_card.size() >= extra_reduce_num || double_card.size() >= extra_reduce_num)	
		{
			min_comb = min_comb - extra_reduce_num;	//假如说飞机是444555，剩下6,7或者66，77
		}
		else if (m_single_card.size() + m_double_card.size() >= extra_reduce_num)
		{
			min_comb = min_comb - extra_reduce_num + 1;	//假如说飞机是444555，剩下6和77
		}
	}
	if (min_comb < three)	//但是如果m_single_card和m_double_card总手数都小于三个的手数，那么要算3个的手数
	{
		min_comb = three;
	}
	//如果不存在连牌了就说明single_card.size()+double_card.size+three_card.size就是最终手数，但是要减去三个带的和飞机带的
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
		//从顺子分析
		for (auto it_single = single_line_card.begin(); it_single != single_line_card.end(); it_single++)	//顺子
		{
			vector<int> current_data = store_data;
			vector<CombinaCard> store_comb;
			RemoveSubDataFromSrcData(current_data, it_single->data);
			comb_num = GetCardCombNum(current_data, store_comb, extra_reduce_num);
			if (comb_num + 1 < compare_comb)	//+1是算上当前手
			{
				compare_comb = comb_num+1;
				min_comb = *it_single;
				final_comb.clear();
				final_comb = store_comb;
			}
			
		}
		//从连对分析
		for (auto it_double = double_line_card.begin(); it_double != double_line_card.end(); it_double++)	//连对
		{
			vector<int> current_data = store_data;
			vector<CombinaCard> store_comb;
			RemoveSubDataFromSrcData(current_data, it_double->data);
			comb_num = GetCardCombNum(current_data, store_comb, extra_reduce_num);
			
			
			if (comb_num + 1 < compare_comb)	//+1是算上当前手
			{
				compare_comb = comb_num + 1;
				min_comb = *it_double;
				final_comb.clear();
				final_comb = store_comb;
			}
			
		}
		//从飞机分析
		for (auto it_three = three_line_card.begin(); it_three != three_line_card.end(); it_three++)	//三个
		{
			vector<int> current_data = store_data;
			vector<CombinaCard> store_comb;
			RemoveSubDataFromSrcData(current_data, it_three->data);
			comb_num = GetCardCombNum(current_data, store_comb, extra_reduce_num + it_three->data.size() / 3);	//加上可以额外带掉的手牌
			//extra_num = ;
			if (comb_num + 1 < compare_comb)	//+1是算上当前手
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