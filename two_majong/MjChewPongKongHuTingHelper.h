#ifndef _MJ_CHEW_PONG_KONG_HU_TING_HELPER_
#define _MJ_CHEW_PONG_KONG_HU_TING_HELPER_

#include <stdint.h>
class MjChewPongKongHuTingHelper
{
public:
	void Reset();
	uint32_t Hu();
	uint32_t Remain();
	uint32_t Ting();
	bool RemainTing();
	bool IsQiDuiTing();
	uint32_t JIANG;
	int m_PAI[17];	//�����±�ֵ��ӦΪmajong_pai.h���card_valueֵ [0]��ȱ������
};























#endif