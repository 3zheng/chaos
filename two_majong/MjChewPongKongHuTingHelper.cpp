
#include "MjChewPongKongHuTingHelper.h"

uint32_t MjChewPongKongHuTingHelper::Hu()
{
	//1�� 0����
	//static int JIANG = 0;
	if (m_PAI[0] != 0)
	{
		//card_value��value_unknown���ƴ���
		return 0;
	}

	if(!Remain())return 1;
	int i = 0;
	for(; !m_PAI[i] && i < 17;i++);
	if (m_PAI[i] == 4)	//�Ƿ���ڸ�
	{
		m_PAI[i] = 0;
		//
		if(Hu())return 1;
		//
		m_PAI[i] = 4;
	}
	if (m_PAI[i] >= 3)	//�Ƿ������
	{
		m_PAI[i] -= 3;
		if(Hu())return 1;
		m_PAI[i] += 3;
	}
	if (!JIANG && m_PAI[i] >= 2)	//�Ƿ���ڽ�ͷ
	{
		JIANG = 1;
		m_PAI[i] -= 2;
		if(Hu()) return 1;
		m_PAI[i] += 2;
		JIANG = 0;
	}
	if(i > 8)return 0;	//�Ƿ���ڳ�
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
	//���ж��߶��������������
	if (IsQiDuiTing())
	{
		return 1;
	}

	if (RemainTing())return 1;
	int i = 0;
	for (; !m_PAI[i] && i < 17; i++);
	if (m_PAI[i] == 4)	//�Ƿ���ڸ�
	{
		m_PAI[i] = 0;
		//
		if (Ting())return 1;
		//
		m_PAI[i] = 4;
	}
	if (m_PAI[i] >= 3)	//�Ƿ������
	{
		m_PAI[i] -= 3;
		if (Ting())return 1;
		m_PAI[i] += 3;
	}
	if (!JIANG && m_PAI[i] >= 2)	//�Ƿ���ڽ�ͷ
	{
		JIANG = 1;
		m_PAI[i] -= 2;
		if (Ting()) return 1;
		m_PAI[i] += 2;
		JIANG = 0;
	}
	if (i > 8)return 0;	//�Ƿ���ڳ�
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
	//�ж�ʣ�µ����Ƿ��������ʣ�µ���ҪҪô��1Ҫô��2,1�Ļ����ǵ�������2�Ļ������ǳ���Ҳ����������
	int sum = 0;

	int remain_1 = -1, remain_2 = -1;	//ʣ�µ���
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
	
	//��Ϊremain_2��remain_1��ֵ������remain_2>=remain_1
	if (remain_2 < remain_1)
	{
		return false;
	}
	//ʣ����������2����
	if (sum > 2)
	{
		return false;
	}
	//������
	if (1 == sum)
	{
		return true;
	}

	//�ж��Ƿ����
	if (remain_1 != remain_2)
	{
		if (remain_2 > 8)	//remain_2������
		{
			return false;
		}
		if (remain_2 - remain_1 > 2)	//ʣ�µ������Ʋ��ܹ��ɳ���
		{
			return false;
		}

		return true;
	}

	//�ж��Ƿ�����
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

	//�������Ƿ�Ϊ6
	if (dui_num != 6)
	{
		return false;
	}

	return true;
}
