
#include "MjChewPongKongHuTingHelper.h"

uint32_t MjChewPongKongHuTingHelper::Hu()
{
	//1胡 0不胡
	//static int JIANG = 0;
	if (m_PAI[0] != 0)
	{
		//card_value的value_unknown的牌存在
		return 0;
	}

	if(!Remain())return 1;
	int i = 0;
	for(; !m_PAI[i] && i < 17;i++);
	if (m_PAI[i] == 4)	//是否存在杠
	{
		m_PAI[i] = 0;
		//
		if(Hu())return 1;
		//
		m_PAI[i] = 4;
	}
	if (m_PAI[i] >= 3)	//是否存在碰
	{
		m_PAI[i] -= 3;
		if(Hu())return 1;
		m_PAI[i] += 3;
	}
	if (!JIANG && m_PAI[i] >= 2)	//是否存在将头
	{
		JIANG = 1;
		m_PAI[i] -= 2;
		if(Hu()) return 1;
		m_PAI[i] += 2;
		JIANG = 0;
	}
	if(i > 8)return 0;	//是否存在吃
	if (i >= 0 && i < 7 && m_PAI[i+1] && m_PAI[i+2])
	{
		m_PAI[i]--;
		m_PAI[i+1]--;
		m_PAI[i+2]--;
		if(Hu())return 1;
		m_PAI[i]++;
		m_PAI[i+1]++;
		m_PAI[i+2]++;
	}
	return 0;
}

uint32_t MjChewPongKongHuTingHelper::Remain()
{
	int sum = 0; 
	for(int i=0;i<17;i++) 
		sum += m_PAI[i]; 
	return sum; 
}


void MjChewPongKongHuTingHelper::Reset()
{
	JIANG = 0;
	for (int i = 0; i < 17; i++)
		m_PAI[i] = 0;
}

uint32_t MjChewPongKongHuTingHelper::Ting()
{
	//先判断七对听这个特殊牌型
	if (IsQiDuiTing())
	{
		return 1;
	}

	if (RemainTing())return 1;
	int i = 0;
	for (; !m_PAI[i] && i < 17; i++);
	if (m_PAI[i] == 4)	//是否存在杠
	{
		m_PAI[i] = 0;
		//
		if (Ting())return 1;
		//
		m_PAI[i] = 4;
	}
	if (m_PAI[i] >= 3)	//是否存在碰
	{
		m_PAI[i] -= 3;
		if (Ting())return 1;
		m_PAI[i] += 3;
	}
	if (!JIANG && m_PAI[i] >= 2)	//是否存在将头
	{
		JIANG = 1;
		m_PAI[i] -= 2;
		if (Ting()) return 1;
		m_PAI[i] += 2;
		JIANG = 0;
	}
	if (i > 8)return 0;	//是否存在吃
	if (i >= 0 && i < 7 && m_PAI[i + 1] && m_PAI[i + 2])
	{
		m_PAI[i]--;
		m_PAI[i + 1]--;
		m_PAI[i + 2]--;
		if (Ting())return 1;
		m_PAI[i]++;
		m_PAI[i + 1]++;
		m_PAI[i + 2]++;
	}
	return 0;
}

bool MjChewPongKongHuTingHelper::RemainTing()
{
	//判断剩下的牌是否可以听，剩下的牌要要么是1要么是2,1的话就是单钓将，2的话可能是吃听也可能是碰听
	int sum = 0;

	int remain_1 = -1, remain_2 = -1;	//剩下的牌
	for (int i = 0; i < 16; i++)
	{
		sum += m_PAI[i];
		if (m_PAI[i] == 1)
		{
			if (remain_1 == -1)
			{
				remain_1 = i;
			}
			else if (remain_2 == -1)
			{
				remain_2 = i;
			}
		}

		if (m_PAI[i] == 2)
		{
			remain_1 = i;
			remain_2 = i;
		}
	}
	
	//因为remain_2比remain_1晚赋值，所以remain_2>=remain_1
	if (remain_2 < remain_1)
	{
		return false;
	}
	//剩余牌数大于2不听
	if (sum > 2)
	{
		return false;
	}
	//单钓将
	if (1 == sum)
	{
		return true;
	}

	//判断是否吃听
	if (remain_1 != remain_2)
	{
		if (remain_2 > 8)	//remain_2是字牌
		{
			return false;
		}
		if (remain_2 - remain_1 > 2)	//剩下的两张牌不能构成吃听
		{
			return false;
		}

		return true;
	}

	//判断是否碰听
	if (remain_1 == remain_2)
	{
		return true;
	}
	
	return false;
}

bool MjChewPongKongHuTingHelper::IsQiDuiTing()
{
	int dui_num = 0;
	for (int i = 0; i < 16; i++)
	{
		if (m_PAI[i] == 2)
		{
			dui_num++;
		}
	}

	//对子数是否为6
	if (dui_num != 6)
	{
		return false;
	}

	return true;
}
