#include "majong_pai.h"

void MjHuPaiFanShuComputer::CountData()
{
	for (uint32_t i = 0; i < 16; i++)
	{
		data_count[i] = 0;
	}
	for (uint32_t i = 0; i < vec_all_cards.size(); i++)
	{
		data_count[vec_all_cards[i]-1]++;
	}
}
void MjHuPaiFanShuComputer::CountData2()
{
	for (uint32_t i = 0; i < 16; i++)
	{
		data_count2[i] = 0;
	}
	for (uint32_t i = 0; i < vec_hand_cards.size(); i++)
	{
		data_count2[vec_hand_cards[i]-1]++;
	}
}
bool MjHuPaiFanShuComputer::IsDaSiXi()
{
	CountData();
	if (data_count[value_east_wind-1] == 3 && data_count[value_south_wind-1] == 3 
		&& data_count[value_west_wind-1] == 3 && data_count[value_north_wind-1] == 3)
	{
		for (std::vector<uint32_t>::iterator it = vec_all_cards.begin(); it != vec_all_cards.end(); )
		{
			if ((*it) == value_east_wind || (*it) == value_south_wind || (*it) == value_west_wind || (*it) == value_north_wind)
			{
				it = vec_all_cards.erase(it);
			}
			else
			{
				it++;
			}
		}
		if (vec_all_cards.size() == 2 && vec_all_cards[0] == vec_all_cards[1])
		{
			return true;
		}
	}
	return false;
}

//大三元
bool MjHuPaiFanShuComputer::IsDaSanYuan()
{
	CountData();
	if (data_count[value_red_dragon-1] == 3 && data_count[value_green_dragon-1] == 3 && data_count[value_white_dragon-1] == 3)
	{
		return true;
	}
	return false;
}

//绿一色
bool MjHuPaiFanShuComputer::IsLvYiSe()
{
	CountData();
	if (data_count[value_bamboo_1-1]==0 && data_count[value_bamboo_5-1]==0 
		&& data_count[value_bamboo_7-1]==0 && data_count[value_bamboo_9-1]==0
		&& data_count[value_red_dragon-1]==0 && data_count[value_white_dragon-1]==0
		&& data_count[value_east_wind-1]==0 && data_count[value_south_wind-1]==0
		&& data_count[value_west_wind-1]==0 && data_count[value_north_wind-1]==0)
	{
		return true;
	}
	return false;
}

//九莲宝灯
bool MjHuPaiFanShuComputer::IsJiuLianBaoDeng()
{
	CountData();
	if (data_count[value_bamboo_1-1]>=3 && data_count[value_bamboo_2-1]>=1
		&& data_count[value_bamboo_3-1]>=1 && data_count[value_bamboo_4-1]>=1
		&& data_count[value_bamboo_5-1]>=1 && data_count[value_bamboo_6-1]>=1
		&& data_count[value_bamboo_7-1]>=1 && data_count[value_bamboo_8-1]>=1
		&& data_count[value_bamboo_9-1]>=3 && data_count[value_east_wind-1]==0
		&& data_count[value_south_wind-1]==0 && data_count[value_west_wind-1]==0
		&& data_count[value_north_wind-1]==0 && data_count[value_red_dragon-1]==0
		&& data_count[value_green_dragon-1]==0 && data_count[value_white_dragon-1]==0)
	{
		return true;
	}
	return false;
}

//四杠
bool MjHuPaiFanShuComputer::IsSiGang()
{
	//加一个记录杠牌数即可判断
	if (m_total_gang_count == 4)
		return true;
	return false;
}

//连七对
bool MjHuPaiFanShuComputer::IsLianQiDui()
{
	CountData();
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_3; i++)
	{
		uint32_t j = i;
		for (; j <= i + 6; j++)
		{
			if (data_count[j-1] != 2)
				break;
		}
		if (j == i + 7)
			return true;
	}
	return false;
}

//十三幺,二人麻将里不会出现
bool MjHuPaiFanShuComputer::IsShiSanYao()
{
	return false;
}


//64番
//清幺九,二人麻将里不会出现
bool MjHuPaiFanShuComputer::IsQingYaoJiu()
{
	return false;
}

//小四喜
bool MjHuPaiFanShuComputer::IsXiaoSiXi()
{
	CountData();
	if (   data_count[value_east_wind-1]==3 && data_count[value_south_wind-1]==3 && data_count[value_west_wind-1]==3 && data_count[value_north_wind-1]==2
		|| data_count[value_east_wind-1]==3 && data_count[value_south_wind-1]==3 && data_count[value_west_wind-1]==2 && data_count[value_north_wind-1]==3
		|| data_count[value_east_wind-1]==3 && data_count[value_south_wind-1]==2 && data_count[value_west_wind-1]==3 && data_count[value_north_wind-1]==3
		|| data_count[value_east_wind-1]==2 && data_count[value_south_wind-1]==3 && data_count[value_west_wind-1]==3 && data_count[value_north_wind-1]==3)
	{
		return true;
	}
	return false;
}

//小三元
bool MjHuPaiFanShuComputer::IsXiaoSanYuan()
{
	CountData();
	if (   data_count[value_red_dragon-1]==3 && data_count[value_green_dragon-1]==3 && data_count[value_white_dragon-1]==2
		|| data_count[value_red_dragon-1]==3 && data_count[value_green_dragon-1]==2 && data_count[value_white_dragon-1]==3
		|| data_count[value_red_dragon-1]==2 && data_count[value_green_dragon-1]==3 && data_count[value_white_dragon-1]==3)
	{
		return true;
	}
	return false;
}

//字一色
bool MjHuPaiFanShuComputer::IsZiYiSe()
{
	CountData();
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_9; i++)
	{
		if (data_count[i-1] > 0)
		{
			return false;
		}
	}
	return true;
}

//四暗刻
bool MjHuPaiFanShuComputer::IsSiAnKe()
{
	CountData2();
	uint32_t u32Count=0;
	for (uint32_t i = 0; i < 16;i++)
	{
		if(	data_count2[i]>=3)
		{
			u32Count++;
		}
	}
	if (u32Count >= 4)
	{
		return true;
	}
	return false;
}

//一色双龙会
bool MjHuPaiFanShuComputer::IsYiSeShuangLongHui()
{
	CountData();
	if (data_count[value_bamboo_1-1]==2 && data_count[value_bamboo_2-1]==2 && data_count[value_bamboo_3-1]==2
		&& data_count[value_bamboo_5-1]==2 && data_count[value_bamboo_7-1]==2 && data_count[value_bamboo_8-1]==2
		&& data_count[value_bamboo_9-1]==2)
	{
		return true;
	}
	return false;
}

//48番
//一色四同顺
bool MjHuPaiFanShuComputer::IsYiSeSiTongShun()
{
	CountData();
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_7; i++)
	{
		uint32_t j = i;
		for (;j <= i+2; j++)
		{
			if (data_count[j-1] != 4)
			{
				break;
			}
		}
		if (j == i+3)
		{
			return true;
		}
	}
	return false;
}

//一色四节高
bool MjHuPaiFanShuComputer::IsYiSeSiJieGao()
{
	CountData();
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_6; i++)
	{
		uint32_t j = i;
		for (;j <= i+3;j++)
		{
			if (data_count[j-1] != 3)
			{
				break;
			}
		}
		if (j == i+4)
		{
			return true;
		}
	}
	return false;
}

//32番
//一色四步高
bool MjHuPaiFanShuComputer::IsYiSeSiBuGao()
{
	CountData();
	//依次递增一位
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_4; i++)
	{
		uint32_t j = i;
		for (;j <= value_bamboo_4;j++)
		{
			if (data_count[j-1]>=1 && data_count[j+1-1]>=2 && data_count[j+2-1]>=3
				&& data_count[j+3-1]>=3 && data_count[j+4-1]>=2 && data_count[j+5-1]>=1)
			{
				return true;
			}
		}
	}
	//依次递增二位
	if (data_count[value_bamboo_1-1]>=1 && data_count[value_bamboo_2-1]>=1 && data_count[value_bamboo_3-1]>=2
		&& data_count[value_bamboo_4-1]>=1 && data_count[value_bamboo_5-1]>=2 && data_count[value_bamboo_6-1]>=1
		&& data_count[value_bamboo_7-1]>=2 && data_count[value_bamboo_8-1]>=1 && data_count[value_bamboo_9-1]>=1)
	{
		return true;
	}
	return false;
}

//三杠,杠牌时记录一下数量即可，类似四杠
bool MjHuPaiFanShuComputer::IsSanGang()
{
	if (m_total_gang_count >= 3)
		return true;
	return false;
}

//混幺九
bool MjHuPaiFanShuComputer::IsHunYaoJiu()
{
	if (IsQingYaoJiu() || IsZiYiSe())
	{
		return false;
	}
	CountData();
	for (uint32_t i = value_bamboo_2; i <= value_bamboo_8; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	return true;
}

//24番
//七对,可能与胡牌冲突，也可能不冲突，因此判断时需调用两次
bool MjHuPaiFanShuComputer::IsQiDui()
{
	if (IsLianQiDui() || IsYiSeShuangLongHui())
	{
		return false;
	}
	CountData();
	uint32_t pair_count = 0;
	for (uint32_t i = value_bamboo_1; i <= value_white_dragon; i++)
	{
		if (data_count[i-1] == 2)
		{
			pair_count++;
		}
		if (data_count[i-1] == 4)
		{
			pair_count += 2;//此段只为四个头判定为两对
		}
	}
	if (pair_count == 7)
	{
		return true;
	}
	return false;
}

//七星不靠,二人麻将里不会出现
bool MjHuPaiFanShuComputer::IsQiXinBuKao()
{
	return false;
}

//全双刻
bool MjHuPaiFanShuComputer::IsQuanShuangKe()
{
	CountData();
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_9;i = i+2)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	for (uint32_t i = value_east_wind; i <= value_white_dragon; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	return true;
}

//清一色
bool MjHuPaiFanShuComputer::IsQingYiSe()
{
	//重复判断
	if (IsJiuLianBaoDeng() || IsLianQiDui() || IsYiSeShuangLongHui())
	{
		return false;
	}
	CountData();
	for (uint32_t i = value_east_wind; i <= value_white_dragon; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	return true;
}

//一色三同顺
bool MjHuPaiFanShuComputer::IsYiSeSanTongShun()
{
	if (IsYiSeSiTongShun() || IsYiSeSiJieGao())
	{
		return false;
	}
	CountData();
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_7; i++)
	{
		uint32_t j = i;
		for (;j <= i+2; j++)
		{
			if (data_count[j-1] < 3)
			{
				break;
			}
		}
		if (j == i+3)
		{
			return true;
		}
	}
	return false;
}

//一色三节高
bool MjHuPaiFanShuComputer::IsYiSeSanJieGao()
{
	if(IsYiSeSiTongShun() || IsYiSeSiJieGao() || IsYiSeSanTongShun())
	{
		return false;
	}
	return IsYiSeSanTongShun();
}

//全大
bool MjHuPaiFanShuComputer::IsQuanDa()
{
	CountData();
	for(uint32_t i = value_bamboo_1; i <= value_bamboo_6; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	for (uint32_t i = value_east_wind; i <= value_white_dragon; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	return true;
}

//全中
bool MjHuPaiFanShuComputer::IsQuanZhong()
{
	CountData();
	for(uint32_t i = value_bamboo_1; i <= value_bamboo_3; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	for (uint32_t i = value_bamboo_7; i <= value_white_dragon; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	return true;
}

//全小
bool MjHuPaiFanShuComputer::IsQuanXiao()
{
	CountData();
	for (uint32_t i = value_bamboo_4; i <= value_white_dragon; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	return true;
}

//16番
//清龙
bool MjHuPaiFanShuComputer::IsQingLong()
{
	CountData();
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_9; i++)
	{
		if (data_count[i-1] == 0)
		{
			return false;
		}
	}
	return true;
}

//三色双龙会,二人麻将里不会出现
bool MjHuPaiFanShuComputer::IsSanSeShuangLongHui()
{
	return false;
}

//一色三步高
bool MjHuPaiFanShuComputer::IsYiSeSanBuGao()
{
	if (IsYiSeSiBuGao())
	{
		return false;
	}
	CountData();
	//依次递增一位
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_5; i++)
	{
		uint32_t j = i;
		for (;j <= value_bamboo_5;j++)
		{
			if (data_count[j-1]>=1 && data_count[j+1-1]>=2 && data_count[j+2-1]>=3
				&& data_count[j+3-1]>=2 && data_count[j+4-1]>=1)
			{
				return true;
			}
		}
	}
	//依次递增二位
	if (data_count[value_bamboo_1-1]>=1 && data_count[value_bamboo_2-1]>=1 && data_count[value_bamboo_3-1]>=2
		&& data_count[value_bamboo_4-1]>=1 && data_count[value_bamboo_5-1]>=2 && data_count[value_bamboo_6-1]>=1 && data_count[value_bamboo_7-1]>=1 
		|| data_count[value_bamboo_2-1]>=1 && data_count[value_bamboo_3-1]>=1 && data_count[value_bamboo_4-1]>=2
		&& data_count[value_bamboo_5-1]>=1 && data_count[value_bamboo_6-1]>=2 && data_count[value_bamboo_7-1]>=1 && data_count[value_bamboo_8-1]>=1
		|| data_count[value_bamboo_3-1]>=1 && data_count[value_bamboo_4-1]>=1 && data_count[value_bamboo_5-1]>=2
		&& data_count[value_bamboo_6-1]>=1 && data_count[value_bamboo_7-1]>=2 && data_count[value_bamboo_8-1]>=1 && data_count[value_bamboo_9-1]>=1)
	{
		return true;
	}
	return false;
}

//全带五
bool MjHuPaiFanShuComputer::IsQuanDaiWu()
{
	return false;
}

//三同刻
bool MjHuPaiFanShuComputer::IsSanTongKe()
{
	return false;
}

//三暗刻，杠牌时记录一下数量即可，类似四杠
bool MjHuPaiFanShuComputer::IsSanAnKe()
{
	if (IsSiAnKe())
	{
		return false;
	}
	CountData2();
	uint32_t u32Count=0;
	for (uint32_t i = 0; i < 16;i++)
	{
		if(	data_count2[i]>=3)
		{
			u32Count++;
		}
	}
	if (u32Count >= 3)
	{
		return true;
	}
	return false;
}

//12番
//全不靠,二人麻将里不会出现
bool MjHuPaiFanShuComputer::IsQuanBuKao()
{
	return false;
}

//组合龙,二人麻将里不会出现
bool MjHuPaiFanShuComputer::IsZuHeLong()
{
	return false;
}

//大于五
bool MjHuPaiFanShuComputer::IsDaYuWu()
{
	CountData();
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_5; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	for (uint32_t i = value_east_wind; i <= value_white_dragon; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	return true;
}

//小于五
bool MjHuPaiFanShuComputer::IsXiaoYuWu()
{
	CountData();
	for (uint32_t i = value_bamboo_5; i <= value_white_dragon; i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	return true;
}

//三风刻
bool MjHuPaiFanShuComputer::IsSanFengKe()
{
	//重复判断
	if (IsDaSiXi() || IsXiaoSiXi())
	{
		return false;
	}

	CountData();
	if (data_count[value_east_wind-1]==3 && data_count[value_south_wind-1]==3 && data_count[value_west_wind-1]==3 
		|| data_count[value_east_wind-1]==3 && data_count[value_south_wind-1]==3 && data_count[value_north_wind-1]==3
		|| data_count[value_east_wind-1]==3 && data_count[value_west_wind-1]==3 && data_count[value_north_wind-1]==3
		|| data_count[value_south_wind-1]==3 && data_count[value_west_wind-1]==3 && data_count[value_north_wind-1]==3 )
	{
		return true;
	}
	return false;
}

//8番
//花龙
bool MjHuPaiFanShuComputer::IsHuaLong()
{
	return false;
}

//推不倒
bool MjHuPaiFanShuComputer::IsTuiBuDao()
{
	CountData();
	if (data_count[value_bamboo_1-1]>0 || data_count[value_bamboo_3-1]>0 || data_count[value_bamboo_7-1]>0
		|| data_count[value_east_wind-1]>0 ||data_count[value_south_wind-1]>0 || data_count[value_west_wind-1]>0 
		|| data_count[value_north_wind-1]>0	|| data_count[value_red_dragon-1]>0 || data_count[value_green_dragon-1]>0)
	{
		return false;
	}
	return true;
}

//三色三同顺,二人麻将里不会出现
bool MjHuPaiFanShuComputer::IsSanSeSanTongShun()
{
	return false;
}

//三色三节高,二人麻将里不会出现
bool MjHuPaiFanShuComputer::IsSanSeSanJieGao()
{
	return false;
}

//无番胡,最后才计算
bool MjHuPaiFanShuComputer::IsWuFanHu()
{
	return false;
}
//妙手回春
bool MjHuPaiFanShuComputer::IsMiaoShouHuiChun()
{
	return m_is_miao_shou_hui_chun;
}
//海底捞月
bool MjHuPaiFanShuComputer::IsHaiDiLaoYue()
{
	return m_is_hai_di_lao_yue;
}
//杠上开花
bool MjHuPaiFanShuComputer::IsGangShangKaiHua()
{
	return m_is_gang_shang_kai_hua;
}
//抢杠胡
bool MjHuPaiFanShuComputer::IsQiangGangHu()
{
	return m_is_qiang_gang_hu;
}
//6番
//碰碰胡（注意：杠的牌不传四张，而传三张）
bool MjHuPaiFanShuComputer::IsPengPengHu()
{
	//重复判断
	if (IsDaSiXi() || IsQingYaoJiu() || IsZiYiSe() || IsSiAnKe() || IsYiSeSiJieGao() || IsQuanShuangKe())
	{
		return false;
	}
	CountData();
	uint32_t u32Ke = 0;
	uint32_t u32Jiang = 0;
	for (uint32_t i = 0; i < 16; i++)
	{
		if (data_count[i] == 3)
		{
			u32Ke++;
		}
		else if (data_count[i] == 2)
		{
			u32Jiang++;
		}
	}
	if (u32Ke == 4 && u32Jiang == 1)
	{
		return true;
	}
	return false;
}
//混一色
bool MjHuPaiFanShuComputer::IsHunYiSe()
{
	CountData();
	bool tiao = false;
	bool zi = false;
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_9; i++)
	{
		if (data_count[i-1]>0)
		{
			tiao = true;
			break;
		}
	}
	for (uint32_t i = value_east_wind; i <= value_white_dragon; i++)
	{
		if (data_count[i-1]>0)
		{
			zi = true;
			break;
		}
	}
	if (tiao && zi)
	{
		return true;
	}
	return false;
}
//三色三步高
bool MjHuPaiFanShuComputer::IsSanSeSanBuGao()
{
	return false;
}
//五门齐
bool MjHuPaiFanShuComputer::IsWuMenQi()
{
	return false;
}
//全求人
bool MjHuPaiFanShuComputer::IsQuanQiuRen()
{
	if (pai_in_hand_count == 1)
	{
		return true;
	}
	return false;
}
//双暗杠
bool MjHuPaiFanShuComputer::IsShuangAnGang()
{
	if (IsSiGang() || IsSanGang())
	{
		return false;
	}
	if (m_an_gang_count >= 2)
	{
		return true;
	}
	return false;
}
//双箭刻
bool MjHuPaiFanShuComputer::IsShuangJianKe()
{
	//重复判断
	if (IsDaSanYuan() || IsXiaoSanYuan())
	{
		return false;
	}

	CountData();
	uint32_t u32Count=0;
	if(data_count[value_red_dragon-1]>=3)
	{
		u32Count++;
	}
	if(data_count[value_green_dragon-1]>=3)
	{
		u32Count++;
	}
	if(data_count[value_white_dragon-1]>=3)
	{
		u32Count++;
	}
	if (u32Count >= 2)
	{
		return true;
	}
	return false;
}
//全带幺
bool MjHuPaiFanShuComputer::IsQuanDaiYao()
{
	if (IsQingYaoJiu() || IsZiYiSe())
	{
		return false;
	}
	return m_is_quan_dai_yao;
}
//不求人
bool MjHuPaiFanShuComputer::IsBuQiuRen()
{
	//重复判断
	if (IsJiuLianBaoDeng() || IsLianQiDui() || IsShiSanYao() || IsSiAnKe() || IsQiDui())
	{
		return false;
	}
	if (pai_in_hand_count == 14 && m_an_gang_count == 0 && m_ming_gang_count2 == 0 && m_is_zi_mo)
	{
		return true;
	}
	return false;
}
//双明杠
bool MjHuPaiFanShuComputer::IsShuangMingGang()
{
	//重复判断
	if (IsSiGang() || IsSanGang())
	{
		return false;
	}
	if (m_an_gang_count + m_ming_gang_count2 >= 2)
	{
		return true;
	}
	return false;
}
//胡绝张
bool MjHuPaiFanShuComputer::IsHuJueZhang()
{
	if (IsQiangGangHu())
	{
		return false;
	}
	return false;
}
//箭刻
bool MjHuPaiFanShuComputer::IsJianKe()
{
	//重复判断
	if (IsDaSanYuan() || IsXiaoSanYuan() || IsShuangJianKe())
	{
		return false;
	}

	CountData();
	uint32_t u32Count=0;
	if(data_count[value_red_dragon-1]>=3)
	{
		u32Count++;
	}
	if(data_count[value_green_dragon-1]>=3)
	{
		u32Count++;
	}
	if(data_count[value_white_dragon-1]>=3)
	{
		u32Count++;
	}
	if (u32Count >= 1)
	{
		return true;
	}
	return false;
}
//圈风刻，二人麻将貌似没有
bool MjHuPaiFanShuComputer::IsQuanFengKe()
{
	return false;
}
//门风刻
bool MjHuPaiFanShuComputer::IsMenFengKe()
{
	return false;
}
//门前清
bool MjHuPaiFanShuComputer::IsMenQianQing()
{
	//重复判断
	if (IsJiuLianBaoDeng() || IsLianQiDui() || IsQiDui() || IsQiXinBuKao() || IsQuanBuKao())
	{
		return false;
	}
	
	if (pai_in_hand_count == 13 && m_is_zi_mo == false)
	{
		return true;
	}
	return false;
}
//平胡//未写
bool MjHuPaiFanShuComputer::IsPingHu()
{
	if (IsYiSeShuangLongHui() || IsSanSeShuangLongHui())
	{
		return false;
	}
	return false;
}
//四归一//未明确
bool MjHuPaiFanShuComputer::IsSiGuiYi()
{
	if (IsYiSeSiTongShun())
	{
		return false;
	}
	CountData();
	for (uint32_t i = 0; i < 16;i++)
	{
		if(	data_count[i]>=4)
		{
			return true;
		}
	}
	return false;
}
//双同刻
bool MjHuPaiFanShuComputer::IsShuangTongKe()
{
	return false;
}
//双暗刻
bool MjHuPaiFanShuComputer::IsShuangAnKe()
{
	if (IsSiAnKe() || IsSanAnKe() || IsShuangAnGang())
	{
		return false;
	}
	CountData2();
	uint32_t u32Count=0;
	for (uint32_t i = 0; i < 16;i++)
	{
		if(	data_count2[i]>=3)
		{
			u32Count++;
		}
	}
	if (u32Count >= 2)
	{
		return true;
	}
	return false;
}
//暗杠
bool MjHuPaiFanShuComputer::IsAnGang()
{
	//重复判断
	if (IsSiGang() || IsSanGang())
	{
		return false;
	}
	if (m_ming_gang_count1 >= 1)
	{
		return true;
	}
	return false;
}
//断幺
bool MjHuPaiFanShuComputer::IsDuanYao()
{
	if (IsQuanShuangKe() || IsQuanDaiWu())
	{
		return false;
	}
	CountData();
	if (data_count[0] > 0)
	{
		return false;
	}
	for (uint32_t i = value_bamboo_9; i <= value_white_dragon;i++)
	{
		if (data_count[i-1] > 0)
		{
			return false;
		}
	}
	return true;
}
//一般高
bool MjHuPaiFanShuComputer::IsYiBanGao()
{
	if (IsYiSeShuangLongHui() || IsYiSeSiTongShun() || IsYiSeSanTongShun())
	{
		return false;
	}
	CountData();
	for (uint32_t i = value_bamboo_1; i<=value_bamboo_7;i++)
	{
		if (data_count[i-1] >= 2 && data_count[i] >= 2 && data_count[i+1]>=2)
		{
			return true;
		}
	}
	return false;
}
//喜相逢
bool MjHuPaiFanShuComputer::IsXiXiangFeng()
{
	if (IsSanSeShuangLongHui() || IsSanSeSanTongShun())
	{
		return false;
	}
	return false;
}
//连6
bool MjHuPaiFanShuComputer::IsLianLiu()
{
	if (IsQingLong())
	{
		return false;
	}
	CountData();
	for (uint32_t i = value_bamboo_1; i<=value_bamboo_4;i++)
	{
		if (data_count[i-1] >= 1 && data_count[i] >= 1 && data_count[i+1]>=1 && data_count[i+2]>=1 && data_count[i+3]>=1 && data_count[i+4]>=1)
		{
			return true;
		}
	}
	return false;
}
//老少副
bool MjHuPaiFanShuComputer::IsLaoShaoFu()
{
	if (IsYiSeShuangLongHui() || IsQingLong() || IsSanSeShuangLongHui())
	{
		return false;
	}
	CountData();
	if (data_count[value_bamboo_1-1] >= 1 && data_count[value_bamboo_2-1] >= 1 && data_count[value_bamboo_3-1] >= 1 && 
		data_count[value_bamboo_7-1] >= 1 && data_count[value_bamboo_8-1] >= 1 && data_count[value_bamboo_9-1] >=1)
	{
		return true;
	}
	return false;
}
//幺九刻
bool MjHuPaiFanShuComputer::IsYaoJiuKe()
{
	//重复判断
	if (IsDaSiXi() || IsJiuLianBaoDeng() || IsQingYaoJiu() || IsXiaoSiXi() || IsZiYiSe())
	{
		return false;
	}
	CountData();
	if (data_count[value_bamboo_9-1]>=3 || data_count[value_bamboo_1-1]>=3)
	{
		return true;
	}
	return false;
}
//明杠
bool MjHuPaiFanShuComputer::IsMingGang()
{
	//重复判断
	if (IsSiGang() || IsSanGang() || IsShuangMingGang())
	{
		return false;
	}
	if (m_an_gang_count + m_ming_gang_count2 > 0)
	{
		return true;
	}
	return false;
}
//缺一门
bool MjHuPaiFanShuComputer::IsQueYiMen()
{
	return false;
}
//无字
bool MjHuPaiFanShuComputer::IsWuZi()
{
	if (IsLianQiDui() || IsQingYaoJiu() || IsYiSeShuangLongHui() || IsQuanShuangKe() 
		|| IsQingYiSe() || IsSanSeShuangLongHui() || IsQuanDaiWu() || IsDaYuWu() || IsXiaoYuWu())
	{
		return false;
	}
	CountData();
	for (uint32_t i = value_east_wind;i<=value_white_dragon;i++)
	{
		if (data_count[i-1]>0)
		{
			return false;
		}
	}
	return true;
}
//单钓将
bool MjHuPaiFanShuComputer::IsDanDiaoJiang()
{
	//重复判断
	if (IsSiGang() || IsLianQiDui() || IsShiSanYao() || IsQiDui() || IsQiXinBuKao() || IsQuanBuKao() || IsQuanQiuRen())
	{
		return false;
	}
	if (pai_in_hand_count == 1)
	{
		return true;
	}
	return false;
}

//新的番型计算器
void NewHuPaiFanShuComputer::SetData(pai_group a_group,int index)
{
	if (index < 0 || index >= 5)
	{
		return;
	}
	m_5zupai[index].value1 = a_group.value1;
	m_5zupai[index].value2 = a_group.value2;
	m_5zupai[index].value3 = a_group.value3;
	m_5zupai[index].value_type = a_group.value_type;
}
void NewHuPaiFanShuComputer::ResetAllData()
{
	m_bIsZiMo = false;
	for (int i = 0; i < 5; i++)
	{
		m_5zupai[i].Reset();
	}
	for (int i = 0; i < 81; i++)
	{
		m_bFan[i] = false;
	}
}
void NewHuPaiFanShuComputer::CheckAllFan()
{
	for(int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == 0)
		{
			return;
		}
	}
	CheckDaSiXi();
	CheckDaSanYuan();
	CheckLvYiSe();
	CheckJiuLianBaoDeng();
	CheckSiGang();
	CheckXiaoSiXi();
	CheckXiaoSanYuan();
	CheckZiYiSe();
	CheckSiAnKe();
	CheckYiSeShuangLongHui();
	CheckYiSeSiTongShun();
	CheckYiSeSiJieGao();
	CheckYiSeSiBuGao();
	CheckSanGang();
	CheckHunYaoJiu();
	CheckQingYiSe();
	CheckYiSeSanTongShun();
	CheckYiSeSanJieGao();
	CheckQingLong();
	CheckYiSeSanBuGao();
	CheckSanAnKe();
	CheckDaYuWu();
	CheckXiaoYuWu();
	CheckSanFengKe();
	CheckTuiBuDao();
	CheckPengPengHu();
	CheckHunYiSe();
	CheckQuanQiuRen();
	CheckShuangAnGang();
	CheckShuangJianKe();
	CheckQuanDaiYao();
	CheckBuQiuRen();
	CheckShuangMingGang();
	CheckJianKe();
	CheckMenQianQing();
	CheckPingHu();
	CheckSiGuiYi();
	CheckShuangAnKe();
	CheckAnGang();
	CheckDuanYao();
	CheckYiBanGao();
	CheckLianLiu();
	CheckLaoShaoFu();
	CheckYaoJiuKe();
	CheckMingGang();
	CheckWuZi();
	CheckBianZhang();
	CheckKanZhang();
	CheckDanDiaoJiang();
	CheckHuaPai();
	CheckZiMo();
}
void NewHuPaiFanShuComputer::DeleteAllRepeat()
{
	//大四喜
	if (m_bFan[ID_FAN_DASIXI])
	{
		m_bFan[ID_FAN_QUANFENGKE] = false;
		m_bFan[ID_FAN_MENFENGKE] = false;
		m_bFan[ID_FAN_SANFENGKE] = false;
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
	}
	//大三元
	if (m_bFan[ID_FAN_DASANYUAN])
	{
		m_bFan[ID_FAN_JIANKE] = false;
		m_bFan[ID_FAN_SHUANGJIANKE] = false;
	}
	//九莲宝灯
	if (m_bFan[ID_FAN_JIULIANBAODENG])
	{
		m_bFan[ID_FAN_QINGYISE] = false;
		m_bFan[ID_FAN_BUQIUREN] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
	}
	//四杠
	if(m_bFan[ID_FAN_SIGANG])
	{
		m_bFan[ID_FAN_SHUANGANGANG] = false;
		m_bFan[ID_FAN_SHUANGMINGGANG] = false;
		m_bFan[ID_FAN_MINGGANG] = false;
		m_bFan[ID_FAN_ANGANG] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
	}
	//连七对
	if (m_bFan[ID_FAN_LIANQIDUI])
	{
		m_bFan[ID_FAN_QINGYISE] = false;
		m_bFan[ID_FAN_BUQIUREN] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_QIDUI] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
		m_bFan[ID_FAN_WUZI] = false;
	}
	//十三幺
	if (m_bFan[ID_FAN_SHISANYAO])
	{
		m_bFan[ID_FAN_WUMENQI] = false;
		m_bFan[ID_FAN_BUQIUREN] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_QUANDAIYAO] = false;
	}
	//清幺九
	if (m_bFan[ID_FAN_QINGYAOJIU])
	{
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_SHUANGTONGKE] = false;
		m_bFan[ID_FAN_WUZI] = false;
		m_bFan[ID_FAN_HUNYAOJIU] = false;
		m_bFan[ID_FAN_QUANDAIYAO] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
	}
	//小四喜
	if (m_bFan[ID_FAN_XIAOSIXI])
	{
		m_bFan[ID_FAN_SANFENGKE] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//小三元
	if (m_bFan[ID_FAN_XIAOSANYUAN])
	{
		m_bFan[ID_FAN_JIANKE] = false;
		m_bFan[ID_FAN_SHUANGJIANKE] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//字一色
	if (m_bFan[ID_FAN_ZIYISE])
	{
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_HUNYAOJIU] = false;
		m_bFan[ID_FAN_QUANDAIYAO] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//四暗刻
	if (m_bFan[ID_FAN_SIANKE])
	{
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_SANANKE] = false;
		m_bFan[ID_FAN_SHUANGANKE] = false;
		m_bFan[ID_FAN_BUQIUREN] = false;
	}
	//一色双龙会
	if (m_bFan[ID_FAN_YISESHUANGLONGHUI])
	{
		m_bFan[ID_FAN_PINGHU] = false;
		m_bFan[ID_FAN_QIDUI] = false;
		m_bFan[ID_FAN_QINGYISE] = false;
		m_bFan[ID_FAN_YIBANGAO] = false;
		m_bFan[ID_FAN_LAOSHAOFU] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
		m_bFan[ID_FAN_WUZI] = false;
	}
	//一色四同顺
	if (m_bFan[ID_FAN_YISESITONGSHUN])
	{
		m_bFan[ID_FAN_YISESANJIEGAO] = false;
		m_bFan[ID_FAN_YIBANGAO] = false;
		m_bFan[ID_FAN_SIGUIYI] = false;
		m_bFan[ID_FAN_YISESANTONGSHUN] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//一色四节高
	if (m_bFan[ID_FAN_YISESIJIEGAO])
	{
		m_bFan[ID_FAN_YISESANTONGSHUN] = false;
		m_bFan[ID_FAN_YISESANJIEGAO] = false;
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//一色四步高
	if (m_bFan[ID_FAN_YISESIBUGAO])
	{
		m_bFan[ID_FAN_YISESANBUGAO] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//三杠
	if (m_bFan[ID_FAN_SANGANG])
	{
		m_bFan[ID_FAN_SHUANGMINGGANG] = false;
		m_bFan[ID_FAN_SHUANGANGANG] = false;
		m_bFan[ID_FAN_MINGGANG] = false;
		m_bFan[ID_FAN_ANGANG] = false;
	}
	//混幺九
	if (m_bFan[ID_FAN_HUNYAOJIU])
	{
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
		m_bFan[ID_FAN_QUANDAIYAO] = false;
	}
	//七对
	if (m_bFan[ID_FAN_QIDUI])
	{
		m_bFan[ID_FAN_BUQIUREN] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
	}
	//七星不靠
	if (m_bFan[ID_FAN_QIXINGBUKAO])
	{
		m_bFan[ID_FAN_WUMENQI] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_QUANBUKAO] = false;
	}
	//全双刻
	if (m_bFan[ID_FAN_QUANSHUANGKE])
	{
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_DUANYAO] = false;
		m_bFan[ID_FAN_WUZI] = false;
	}
	//清一色
	if (m_bFan[ID_FAN_QINGYISE])
	{
		m_bFan[ID_FAN_WUZI] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//一色三同顺
	if (m_bFan[ID_FAN_YISESANTONGSHUN])
	{
		m_bFan[ID_FAN_YISESANJIEGAO] = false;
		m_bFan[ID_FAN_YIBANGAO] = false;
	}
	//一色三节高
	if (m_bFan[ID_FAN_YISESANJIEGAO])
	{
		m_bFan[ID_FAN_YISESANTONGSHUN] = false;
	}
	//全中
	if (m_bFan[ID_FAN_QUANZHONG])
	{
		m_bFan[ID_FAN_DUANYAO] = false;
		m_bFan[ID_FAN_WUZI] = false;
	}
	//全小
	if (m_bFan[ID_FAN_QUANXIAO])
	{
		m_bFan[ID_FAN_WUZI] = false;
		m_bFan[ID_FAN_XIAOYUWU] = false;
	}
	//清龙
	if (m_bFan[ID_FAN_QINGLONG])
	{
		m_bFan[ID_FAN_LIANLIU] = false;
		m_bFan[ID_FAN_LAOSHAOFU] = false;
	}
	//三色双龙会
	if (m_bFan[ID_FAN_SANSESHUANGLONGHUI])
	{
		m_bFan[ID_FAN_XIXIANGFENG] = false;
		m_bFan[ID_FAN_LAOSHAOFU] = false;
		m_bFan[ID_FAN_WUZI] = false;
		m_bFan[ID_FAN_PINGHU] = false;
	}
	//全带五
	if (m_bFan[ID_FAN_QUANDAIWU])
	{
		m_bFan[ID_FAN_DUANYAO] = false;
		m_bFan[ID_FAN_WUZI] = false;
	}
	//三同刻
	if (m_bFan[ID_FAN_SANTONGKE])
	{
		m_bFan[ID_FAN_SHUANGTONGKE] = false;
	}
	//三暗刻
	if (m_bFan[ID_FAN_SANANKE])
	{
		m_bFan[ID_FAN_SHUANGANKE] = false;
	}
	//全不靠
	if (m_bFan[ID_FAN_QUANBUKAO])
	{
		m_bFan[ID_FAN_WUMENQI] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
	}
	//大于五
	if (m_bFan[ID_FAN_DAYUWU])
	{
		m_bFan[ID_FAN_WUZI] = false;
	}
	//小于五
	if (m_bFan[ID_FAN_XIAOYUWU])
	{
		m_bFan[ID_FAN_WUZI] = false;
	}
	//三风刻
	if (m_bFan[ID_FAN_SANFENGKE])
	{
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//推不倒
	if (m_bFan[ID_FAN_TUIBUDAO])
	{
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//三色三同顺
	if (m_bFan[ID_FAN_SANSESANTONGSHUN])
	{
		m_bFan[ID_FAN_XIXIANGFENG] = false;
	}
	//妙手回春
	if (m_bFan[ID_FAN_MIAOSHOUHUICHUN])
	{
		m_bFan[ID_FAN_ZIMO] = false;
	}
	//杠上开花
	if (m_bFan[ID_FAN_GANGSHANGKAIHUA])
	{
		m_bFan[ID_FAN_ZIMO] = false;
	}
	//抢杠胡
	if (m_bFan[ID_FAN_QIANGGANGHU])
	{
		m_bFan[ID_FAN_HUJUEZHANG] = false;
	}
	//混一色
	if (m_bFan[ID_FAN_HUNYISE])
	{
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//全求人
	if (m_bFan[ID_FAN_QUANQIUREN])
	{
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
	}
	//双暗杠
	if (m_bFan[ID_FAN_SHUANGANGANG])
	{
		m_bFan[ID_FAN_SHUANGANKE] = false;
	}
	//双箭刻
	if (m_bFan[ID_FAN_SHUANGJIANKE])
	{
		m_bFan[ID_FAN_JIANKE] = false;
	}
	//不求人
	if (m_bFan[ID_FAN_BUQIUREN])
	{
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_ZIMO] = false;
	}
	//双明杠
	if (m_bFan[ID_FAN_SHUANGMINGGANG])
	{
		m_bFan[ID_FAN_MINGGANG] = false;
	}
	//门风刻
	if (m_bFan[ID_FAN_MENFENGKE])
	{
		m_bFan[ID_FAN_YAOJIUKE] = false;
	}
}
int  NewHuPaiFanShuComputer::CountFan()
{
	CStringA log_str;
	bool bWriteLog = false;
	log_str.Format("番型记录：");//if(bWriteLog)WriteLog(log_str);
	int total_fan = 0;
	if (GetSomeFan(ID_FAN_DASIXI)){total_fan += 88;log_str.Format("大四喜88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_DASANYUAN)){total_fan += 88;log_str.Format("大三元88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_LVYISE)){total_fan += 88;log_str.Format("绿一色88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_JIULIANBAODENG)){total_fan += 88;log_str.Format("九莲宝灯88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SIGANG)){total_fan += 88;log_str.Format("四杠88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_LIANQIDUI)){total_fan += 88;log_str.Format("连七对88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHISANYAO)){total_fan += 88;log_str.Format("十三幺88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QINGYAOJIU)){total_fan += 64;log_str.Format("清幺九64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_XIAOSIXI)){total_fan += 64;log_str.Format("小四喜64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_XIAOSANYUAN)){total_fan += 64;log_str.Format("小三元64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_ZIYISE)){total_fan += 64;log_str.Format("字一色64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SIANKE)){total_fan += 64;log_str.Format("四暗刻64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESHUANGLONGHUI)){total_fan += 64;log_str.Format("一色双龙会64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESITONGSHUN)){total_fan += 48;log_str.Format("一色四同顺48");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESIJIEGAO)){total_fan += 48;log_str.Format("一色四节高48");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESIBUGAO)){total_fan += 32;log_str.Format("一色四步高32");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANGANG)){total_fan += 32;log_str.Format("三杠32");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HUNYAOJIU)){total_fan += 32;log_str.Format("混幺九32");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QIDUI)){total_fan += 24;log_str.Format("七对24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QIXINGBUKAO)){total_fan += 24;log_str.Format("七星不靠24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANSHUANGKE)){total_fan += 24;log_str.Format("全双刻24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QINGYISE)){total_fan += 24;log_str.Format("清一色24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESANTONGSHUN)){total_fan += 24;log_str.Format("一色三同顺24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESANJIEGAO)){total_fan += 24;log_str.Format("一色三节高24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANDA)){total_fan += 24;log_str.Format("全大24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANZHONG)){total_fan += 24;log_str.Format("全中24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANXIAO)){total_fan += 24;log_str.Format("全小24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QINGLONG)){total_fan += 16;log_str.Format("清龙16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANSESHUANGLONGHUI)){total_fan += 16;log_str.Format("三色双龙会16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESANBUGAO)){total_fan += 16;log_str.Format("一色三步高16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANDAIWU)){total_fan += 16;log_str.Format("全带五16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANTONGKE)){total_fan += 16;log_str.Format("三同刻16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANANKE)){total_fan += 16;log_str.Format("三暗刻16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANBUKAO)){total_fan += 12;log_str.Format("全不靠12");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_ZUHELONG)){total_fan += 12;log_str.Format("组合龙12");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_DAYUWU)){total_fan += 12;log_str.Format("大于五12");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_XIAOYUWU)){total_fan += 12;log_str.Format("小于五12");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANFENGKE)){total_fan += 12;log_str.Format("三风刻12");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HUALONG)){total_fan += 8;log_str.Format("花龙8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_TUIBUDAO)){total_fan += 8;log_str.Format("推不倒8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANSESANTONGSHUN)){total_fan += 8;log_str.Format("三色三同顺8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANSESANJIEGAO)){total_fan += 8;log_str.Format("三色三节高8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_WUFANHU)){total_fan += 8;log_str.Format("无番胡8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_MIAOSHOUHUICHUN)){total_fan += 8;log_str.Format("妙手回春8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HAIDILAOYUE)){total_fan += 8;log_str.Format("海底捞月8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_GANGSHANGKAIHUA)){total_fan += 8;log_str.Format("杠上开花8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QIANGGANGHU)){total_fan += 8;log_str.Format("抢杠胡8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_PENGPENGHU)){total_fan += 6;log_str.Format("碰碰胡6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HUNYISE)){total_fan += 6;log_str.Format("混一色6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANSESANBUGAO)){total_fan += 6;log_str.Format("三色三步高6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_WUMENQI)){total_fan += 6;log_str.Format("五门齐6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANQIUREN)){total_fan += 6;log_str.Format("全求人6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHUANGANGANG)){total_fan += 6;log_str.Format("双暗杠6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHUANGJIANKE)){total_fan += 6;log_str.Format("双箭刻6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANDAIYAO)){total_fan += 4;log_str.Format("全带幺4");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_BUQIUREN)){total_fan += 4;log_str.Format("不求人4");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHUANGMINGGANG)){total_fan += 4;log_str.Format("双明杠4");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HUJUEZHANG)){total_fan += 4;log_str.Format("胡绝张4");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_JIANKE)){total_fan += 2;log_str.Format("箭刻2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANFENGKE)){total_fan += 2;log_str.Format("圈风刻2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_MENFENGKE)){total_fan += 2;log_str.Format("门风刻2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_MENQIANQING)){total_fan += 2;log_str.Format("门前清2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_PINGHU)){total_fan += 2;log_str.Format("平胡2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SIGUIYI)){total_fan += 2;log_str.Format("四归一2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHUANGTONGKE)){total_fan += 2;log_str.Format("双同刻2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHUANGANKE)){total_fan += 2;log_str.Format("双暗刻2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_ANGANG)){total_fan += 2;log_str.Format("暗杠2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_DUANYAO)){total_fan += 2;log_str.Format("断幺2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YIBANGAO)){total_fan += 1;log_str.Format("一般高1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_XIXIANGFENG)){total_fan += 1;log_str.Format("喜相逢1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_LIANLIU)){total_fan += 1;log_str.Format("连六1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_LAOSHAOFU)){total_fan += 1;log_str.Format("老少副1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YAOJIUKE)){total_fan += 1;log_str.Format("幺九刻1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_MINGGANG)){total_fan += 1;log_str.Format("明杠1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUEYIMEN)){total_fan += 1;log_str.Format("缺一门1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_WUZI)){total_fan += 1;log_str.Format("无字1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_BIANZHANG)){total_fan += 1;log_str.Format("边张1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_KANZHANG)){total_fan += 1;log_str.Format("坎张1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_DANDIAOJIANG)){total_fan += 1;log_str.Format("单钓将1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HUAPAI)){total_fan += m_flowers;log_str.Format("花牌%d",m_flowers);if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_ZIMO)){total_fan += 1;log_str.Format("自摸1");if(bWriteLog)WriteLog(log_str);}
	return total_fan;
}
//88番
//大四喜
void NewHuPaiFanShuComputer::CheckDaSiXi()
{
	int dong_nan_xi_bei = 0;
	for (int i = 0; i < 5; i++)
	{
		if ((m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 ||
			m_5zupai[i].value_type == value_minggang2 ) && 
			m_5zupai[i].value1 >= value_east_wind && m_5zupai[i].value1 <= value_north_wind)
		{
			dong_nan_xi_bei++;
		}
	}
	if (dong_nan_xi_bei == 4)
	{
		m_bFan[ID_FAN_DASIXI] = true;
	}
}
//大三元
void NewHuPaiFanShuComputer::CheckDaSanYuan()
{
	int kezi = 0;
	for (int i = 0; i < 5; i++)
	{
		if ((m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng) && 
			m_5zupai[i].value1 >= value_red_dragon && m_5zupai[i].value1 <= value_white_dragon)
		{
			kezi++;
		}
	}
	if (kezi == 3)
	{
		m_bFan[ID_FAN_DASANYUAN] = true;
	}
}
//绿一色
void NewHuPaiFanShuComputer::CheckLvYiSe()
{
	bool temp = false;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			if (m_5zupai[i].value1 != value_bamboo_2 && m_5zupai[i].value1 != value_bamboo_3 && 
				m_5zupai[i].value1 != value_bamboo_4 && m_5zupai[i].value1 != value_bamboo_6 &&
				m_5zupai[i].value1 != value_bamboo_8 && m_5zupai[i].value1 != value_green_dragon)
			{
				temp = true;
				break;
			}
			if (m_5zupai[i].value2 != value_bamboo_2 && m_5zupai[i].value2 != value_bamboo_3 && 
				m_5zupai[i].value2 != value_bamboo_4 && m_5zupai[i].value2 != value_bamboo_6 &&
				m_5zupai[i].value2 != value_bamboo_8 && m_5zupai[i].value1 != value_green_dragon)
			{
				temp = true;
				break;
			}
			if (m_5zupai[i].value3 != value_bamboo_2 && m_5zupai[i].value3 != value_bamboo_3 && 
				m_5zupai[i].value3 != value_bamboo_4 && m_5zupai[i].value3 != value_bamboo_6 &&
				m_5zupai[i].value3 != value_bamboo_8 && m_5zupai[i].value1 != value_green_dragon)
			{
				temp = true;
				break;
			}
		}
		else if (m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ||
				m_5zupai[i].value_type == value_jiangzi)
		{
			if (m_5zupai[i].value1 != value_bamboo_2 && m_5zupai[i].value1 != value_bamboo_3 && 
				m_5zupai[i].value1 != value_bamboo_4 && m_5zupai[i].value1 != value_bamboo_6 &&
				m_5zupai[i].value1 != value_bamboo_8 && m_5zupai[i].value1 != value_green_dragon)
			{
				temp = true;
				break;
			}
		}
		else
		{
			temp = true;
			break;
		}
	}
	if (!temp)
	{
		m_bFan[ID_FAN_LVYISE] = true;
	}
}
//九莲宝灯
void NewHuPaiFanShuComputer::CheckJiuLianBaoDeng()
{
	int values[9] = {0};
	for (int i = 0; i < 5; i++)
	{
		if(m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi &&
			(m_5zupai[i].value1 >= value_bamboo_1 && m_5zupai[i].value1 <= value_bamboo_9 &&
			m_5zupai[i].value2 >= value_bamboo_1 && m_5zupai[i].value2 <= value_bamboo_9 &&
			m_5zupai[i].value3 >= value_bamboo_1 && m_5zupai[i].value3 <= value_bamboo_9))
		{
			values[m_5zupai[i].value1 -1]++;
			values[m_5zupai[i].value2 -1]++;
			values[m_5zupai[i].value3 -1]++;
		}
		else if ((m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng)
			&& m_5zupai[i].value1 >= value_bamboo_1 && m_5zupai[i].value1 <= value_bamboo_9)
		{
			values[m_5zupai[i].value1 -1] = values[m_5zupai[i].value1 -1] + 3;
		}
		else if (m_5zupai[i].value_type == value_jiangzi
			&& m_5zupai[i].value1 >= value_bamboo_1 && m_5zupai[i].value1 <= value_bamboo_9)
		{
			values[m_5zupai[i].value1 -1] = values[m_5zupai[i].value1 -1] + 2;
		}
	}
	for (uint32_t i = value_bamboo_1; i <= value_bamboo_9; i++)
	{
		values[i-1]--;
		if (values[0] == 3 && values[1] == 1 && values[2] == 1 && values[3] == 1 && values[4] == 1 && values[5] == 1 && values[6] == 1 && values[7] == 1 && values[8] == 3)
		{
			m_bFan[ID_FAN_JIULIANBAODENG] = true;
			break;
		}
		values[i-1]++;
	}
}
//四杠,杠牌时记录一下数量即可
void NewHuPaiFanShuComputer::CheckSiGang()
{
	int sigang = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 ||
			m_5zupai[i].value_type == value_minggang2 )
		{
			sigang++;
		}
	}
	if (sigang == 4)
	{
		m_bFan[ID_FAN_SIGANG] = true;
	}
}
//连七对,另外作一个检测器
void NewHuPaiFanShuComputer::CheckLianQiDui()
{

}
//十三幺,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckShiSanYao()
{

}
//64番
//清幺九,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckQingYaoJiu()
{

}
//小四喜
void NewHuPaiFanShuComputer::CheckXiaoSiXi()
{
	int dong_nan_xi_bei = 0;
	int jiang = 0;
	for (int i = 0; i < 5; i++)
	{
		if ((m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng) && 
			m_5zupai[i].value1 >= value_east_wind && m_5zupai[i].value1 <= value_north_wind)
		{
			dong_nan_xi_bei++;
		}
		else if (m_5zupai[i].value_type == value_jiangzi && m_5zupai[i].value1 >= value_east_wind && m_5zupai[i].value1 <= value_north_wind)
		{
			jiang++;
		}
	}
	if (dong_nan_xi_bei == 3 && jiang == 1)
	{
		m_bFan[ID_FAN_XIAOSIXI] = true;
	}
}
//小三元
void NewHuPaiFanShuComputer::CheckXiaoSanYuan()
{
	int kezi = 0;
	int jiang = 0;
	for (int i = 0; i < 5; i++)
	{
		if ((m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ) && 
			m_5zupai[i].value1 >= value_red_dragon && m_5zupai[i].value1 <= value_white_dragon)
		{
			kezi++;
		}
		else if (m_5zupai[i].value_type == value_jiangzi && m_5zupai[i].value1 >= value_red_dragon && m_5zupai[i].value1 <= value_white_dragon)
		{
			jiang++;
		}
	}
	if (kezi == 2 && jiang == 1)
	{
		m_bFan[ID_FAN_XIAOSANYUAN] = true;
	}
}
//字一色
void NewHuPaiFanShuComputer::CheckZiYiSe()
{
	int kezi = 0;
	for (int i = 0; i < 5; i++)
	{
		if ((m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 ||
			m_5zupai[i].value_type == value_minggang2 || m_5zupai[i].value_type == value_jiangzi) &&
			m_5zupai[i].value1 >= value_east_wind && m_5zupai[i].value1 <= value_white_dragon)
		{
			kezi++;
		}
	}
	if (kezi == 5)
	{
		m_bFan[ID_FAN_ZIYISE] = true;
	}
}
//四暗刻，杠牌时记录一下数量即可，类似四杠
void NewHuPaiFanShuComputer::CheckSiAnKe()
{
	int si_an_ke = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_kezi_weipeng ||m_5zupai[i].value_type == value_angang )
		{
			si_an_ke++;
		}
	}
	if (si_an_ke == 4)
	{
		m_bFan[ID_FAN_SIANKE] = true;
	}
}
//一色双龙会
void NewHuPaiFanShuComputer::CheckYiSeShuangLongHui()
{
	int laoshaofu123 = 0;
	int laoshaofu789 = 0;
	int jiang5 = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide ||m_5zupai[i].value_type == value_shunzi_weichi )
		{
			if (m_5zupai[i].value1 == value_bamboo_1 && m_5zupai[i].value2 == value_bamboo_2 && m_5zupai[i].value3 == value_bamboo_3)
			{
				laoshaofu123++;
			}
			else if (m_5zupai[i].value1 == value_bamboo_7 && m_5zupai[i].value2 == value_bamboo_8 && m_5zupai[i].value3 == value_bamboo_9)
			{
				laoshaofu789++;
			}
		}
		else if (m_5zupai[i].value_type == value_jiangzi)
		{
			if (m_5zupai[i].value1 == value_bamboo_5)
			{
				jiang5++;
			}
		}
	}
	if (laoshaofu123 == 2 && laoshaofu789 == 2 && jiang5 == 1)
	{
		m_bFan[ID_FAN_YISESHUANGLONGHUI] = true;
	}
}
//48番
//一色四同顺
void NewHuPaiFanShuComputer::CheckYiSeSiTongShun()
{
	uint32_t value1 = 0,value2 = 0,value3 = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide ||m_5zupai[i].value_type == value_shunzi_weichi )
		{
			value1 = m_5zupai[i].value1;
			value2 = m_5zupai[i].value2;
			value3 = m_5zupai[i].value3;
			break;
		}
	}
	int temp = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide ||m_5zupai[i].value_type == value_shunzi_weichi )
		{
			if (m_5zupai[i].value1 == value1 && m_5zupai[i].value2 == value2 && m_5zupai[i].value3 == value3)
			{
				temp++;
			}
		}
	}
	if (temp == 4)
	{
		m_bFan[ID_FAN_YISESITONGSHUN] = true;
	}
	
}
//一色四节高
void NewHuPaiFanShuComputer::CheckYiSeSiJieGao()
{
	std::vector<uint32_t> vec_value;
	for (int i = 0; i < 5; i++)
	{
		if ((m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng) &&
			(m_5zupai[i].value1 >= value_bamboo_1 && m_5zupai[i].value1 <= value_bamboo_9))
		{
			vec_value.push_back(m_5zupai[i].value1);
		}
	}
	if (vec_value.size() >= 4)
	{
		for (uint32_t i = 0; i < vec_value.size(); i++)
		{
			for (uint32_t j = i + 1; j < vec_value.size(); j++)
			{
				if (vec_value[j] < vec_value[i])
				{
					uint32_t temp = vec_value[j];
					vec_value[j] = vec_value[i];
					vec_value[i] = temp;
				}
			}
		}
		if (vec_value[0] + 1 == vec_value[1] && vec_value[0] + 2 == vec_value[2] && vec_value[0] + 3 == vec_value[3])
		{
			m_bFan[ID_FAN_YISESIJIEGAO] = true;
		}
	}
}
//32番
//一色四步高
void NewHuPaiFanShuComputer::CheckYiSeSiBuGao()
{
	uint32_t values[4] = {0};
	int j = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			if (j>=4)
			{
				return;
			}
			values[j] = m_5zupai[i].value1;
			j++;
		}
	}
	if (values[0] == 0 || values[1] == 0 || values[2] == 0 || values[3] == 0)
	{
		return;
	}
	//排序
	for (int k = 0; k < 4;k++)
	{
		for (int l = k+1; l < 4; l++)
		{
			if (values[l] < values[k])
			{
				uint32_t temp = values[l];
				values[l] = values[k];
				values[k] = temp;
			}
		}
	}
	if (values[3] - values[2] == 1 && values[2] - values[1] == 1 && values[1] - values[0] == 1)
	{
		m_bFan[ID_FAN_YISESIBUGAO] = true;
	}
}
//三杠,杠牌时记录一下数量即可，类似四杠
void NewHuPaiFanShuComputer::CheckSanGang()
{
	int gang = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 || m_5zupai[i].value_type == value_minggang2)
		{
			gang++;
		}
	}
	if (gang == 3)
	{
		m_bFan[ID_FAN_SANGANG] = true;
	}
}
//混幺九
void NewHuPaiFanShuComputer::CheckHunYaoJiu()
{
	int hunyaojiu = 0;
	for (int i = 0; i < 5; i++)
	{
		if(m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng || m_5zupai[i].value_type == value_jiangzi)
		{
			if (m_5zupai[i].value1 == value_bamboo_1 || m_5zupai[i].value1 == value_bamboo_9 || 
				(m_5zupai[i].value1 >= value_east_wind && m_5zupai[i].value1 <= value_north_wind))
			{
				hunyaojiu++;
			}
		}
	}
	if (hunyaojiu == 5)
	{
		m_bFan[ID_FAN_HUNYAOJIU] = true;
	}
}
//24番
//七对,作到另一个地方
void NewHuPaiFanShuComputer::CheckQiDui()
{

}
//七星不靠,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckQiXinBuKao()
{

}
//全双刻,貌似二人麻将里出现不了这种情况
void NewHuPaiFanShuComputer::CheckQuanShuangKe()
{

}
//清一色
void NewHuPaiFanShuComputer::CheckQingYiSe()
{
	int qingyise = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value1 >= value_bamboo_1 && m_5zupai[i].value1 <= value_bamboo_9)
		{
			qingyise++;
		}
	}
	if (qingyise == 5)
	{
		m_bFan[ID_FAN_QINGYISE] = true;
	}
}
//一色三同顺
void NewHuPaiFanShuComputer::CheckYiSeSanTongShun()
{
	int yisesantongshun = 0;
	for (uint32_t index_value = value_bamboo_1; index_value <= value_bamboo_7; index_value++)
	{
		yisesantongshun = 0;
		for (int i =0; i < 5; i++)
		{
			if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
			{
				if (m_5zupai[i].value1 == index_value)
				{
					yisesantongshun++;
				}
			}
		}
		if (yisesantongshun == 3)
		{
			m_bFan[ID_FAN_YISESANTONGSHUN] = true;
			break;
		}

	}
	
}
//一色三节高
void NewHuPaiFanShuComputer::CheckYiSeSanJieGao()
{
	std::vector<uint32_t> vec_value;
	for (int i = 0; i < 5; i++)
	{
		if ((m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng) &&
			m_5zupai[i].value1 >= value_bamboo_1 && m_5zupai[i].value1 <= value_bamboo_9)
		{
			vec_value.push_back(m_5zupai[i].value1);
		}
	}
	if (vec_value.size() >= 3)
	{
		for (uint32_t i = 0; i < vec_value.size(); i++)
		{
			for (uint32_t j = i + 1; j < vec_value.size(); j++)
			{
				if (vec_value[j] < vec_value[i])
				{
					uint32_t temp = vec_value[j];
					vec_value[j] = vec_value[i];
					vec_value[i] = temp;
				}
			}
		}
		if (vec_value.size() == 3 && vec_value[0] + 1 == vec_value[1] && vec_value[0] + 2 == vec_value[2])
		{
			m_bFan[ID_FAN_YISESANJIEGAO] = true;
		}
		else if (vec_value.size() == 4)
		{
			if (vec_value[0] + 1 == vec_value[1] && vec_value[0] + 2 == vec_value[2])
			{
				m_bFan[ID_FAN_YISESANJIEGAO] = true;
			}
			else if (vec_value[1] + 1 == vec_value[2] && vec_value[1] + 2 == vec_value[3])
			{
				m_bFan[ID_FAN_YISESANJIEGAO] = true;
			}
		}
	}
}
//全大,貌似二人麻将里出现不了这种情况
void NewHuPaiFanShuComputer::CheckQuanDa()
{

}
//全中,貌似二人麻将里出现不了这种情况
void NewHuPaiFanShuComputer::CheckQuanZhong()
{

}
//全小,貌似二人麻将里出现不了这种情况
void NewHuPaiFanShuComputer::CheckQuanXiao()
{

}
//16番
//清龙
void NewHuPaiFanShuComputer::CheckQingLong()
{
	bool qinglong123 = false,qinglong456 = false,qinglong789 = false;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			if (m_5zupai[i].value1 == value_bamboo_1)
			{
				qinglong123 = true;
			}
			else if (m_5zupai[i].value1 == value_bamboo_4)
			{
				qinglong456 = true;
			}
			else if (m_5zupai[i].value1 == value_bamboo_7)
			{
				qinglong789 = true;
			}
		}
	}
	if (qinglong123 && qinglong456 && qinglong789)
	{
		m_bFan[ID_FAN_QINGLONG] = true;
	}
}
//三色双龙会,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckSanSeShuangLongHui()
{

}
//一色三步高
void NewHuPaiFanShuComputer::CheckYiSeSanBuGao()
{
	uint32_t values[4] = {0};
	int j = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			if (j>=4)
			{
				return;
			}
			values[j] = m_5zupai[i].value1;
			j++;
		}
	}
	if (values[0] == 0 || values[1] == 0 || values[2] == 0)
	{
		return;
	}
	//排序
	for (int k = 0; k < 4;k++)
	{
		for (int l = k+1; l < 4; l++)
		{
			if (values[l] < values[k])
			{
				uint32_t temp = values[l];
				values[l] = values[k];
				values[k] = temp;
			}
		}
	}
	if (j == 4)
	{
		if ((values[3] - values[2] == 1 && values[2] - values[1] == 1) || (values[2] - values[1] == 1 && values[1] - values[0] == 1))
		{
			m_bFan[ID_FAN_YISESANBUGAO] = true;
		}
	}
	else if (j == 3)
	{
		if (values[3] - values[2] == 1 && values[2] - values[1] == 1)
		{
			m_bFan[ID_FAN_YISESANBUGAO] = true;
		}
	}
}
//全带五,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckQuanDaiWu()
{

}
//三同刻,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckSanTongKe()
{

}
//三暗刻，杠牌时记录一下数量即可，类似四杠
void NewHuPaiFanShuComputer::CheckSanAnKe()
{
	int sananke = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_kezi_weipeng)
		{
			sananke++;
		}
	}
	if (sananke == 3)
	{
		m_bFan[ID_FAN_SANANKE] = true;
	}
}
//12番
//全不靠,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckQuanBuKao()
{

}
//组合龙,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckZuHeLong()
{

}
//大于五
void NewHuPaiFanShuComputer::CheckDaYuWu()
{
	int dayuwu = 0;
	for(int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi ||
			m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_jiangzi)
		{
			if (m_5zupai[i].value1 >= value_bamboo_6 && m_5zupai[i].value1 <= value_bamboo_9)
			{
				dayuwu++;
			}
		}
	}
	if (dayuwu == 5)
	{
		m_bFan[ID_FAN_DAYUWU] = true;
	}
}
//小于五
void NewHuPaiFanShuComputer::CheckXiaoYuWu()
{
	int dayuwu = 0;
	for(int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi ||
			m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_jiangzi)
		{
			if (m_5zupai[i].value1 >= value_bamboo_1 && m_5zupai[i].value1 <= value_bamboo_4)
			{
				dayuwu++;
			}
		}
	}
	if (dayuwu == 5)
	{
		m_bFan[ID_FAN_XIAOYUWU] = true;
	}
}
//三风刻
void NewHuPaiFanShuComputer::CheckSanFengKe()
{
	int sanfengke = 0;
	for(int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng)
		{
			if (m_5zupai[i].value1 >= value_east_wind && m_5zupai[i].value1 <= value_north_wind)
			{
				sanfengke++;
			}
		}
	}
	if (sanfengke == 3)
	{
		m_bFan[ID_FAN_SANFENGKE] = true;
	}
}
//8番
//花龙,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckHuaLong()
{

}
//推不倒
void NewHuPaiFanShuComputer::CheckTuiBuDao()
{
	int tuibudao = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			if (m_5zupai[i].value1 == value_bamboo_4)
			{
				tuibudao++;
			}
		}
		else if (m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 ||
			m_5zupai[i].value_type == value_minggang2 || m_5zupai[i].value_type == value_jiangzi)
		{
			if (m_5zupai[i].value1 == value_bamboo_2 || m_5zupai[i].value1 == value_bamboo_4 ||
				m_5zupai[i].value1 == value_bamboo_5 || m_5zupai[i].value1 == value_bamboo_6 ||
				m_5zupai[i].value1 == value_bamboo_8 || m_5zupai[i].value1 == value_bamboo_9)
			{
				tuibudao++;
			}
		}
	}
	if (tuibudao == 5)
	{
		m_bFan[ID_FAN_TUIBUDAO] = true;
	}
}
//三色三同顺,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckSanSeSanTongShun()
{

}
//三色三节高,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckSanSeSanJieGao()
{

}
//无番胡,二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckWuFanHu()
{

}
//妙手回春
void NewHuPaiFanShuComputer::CheckMiaoShouHuiChun()
{

}
//海底捞月
void NewHuPaiFanShuComputer::CheckHaiDiLaoYue()
{

}
//杠上开花
void NewHuPaiFanShuComputer::CheckGangShangKaiHua()
{

}
//抢杠胡
void NewHuPaiFanShuComputer::CheckQiangGangHu()
{

}
//6番
//碰碰胡
void NewHuPaiFanShuComputer::CheckPengPengHu()
{
	int pengpenghu = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 ||
			m_5zupai[i].value_type == value_minggang2 || m_5zupai[i].value_type == value_jiangzi)
		{
			pengpenghu++;
		}
	}
	if (pengpenghu == 5)
	{
		m_bFan[ID_FAN_PENGPENGHU] = true;
	}
}
//混一色
void NewHuPaiFanShuComputer::CheckHunYiSe()
{
	bool bamboo = false,zi = false;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value1 >= value_bamboo_1 && m_5zupai[i].value1 <= value_bamboo_9)
		{
			bamboo = true;
		}
		else if (m_5zupai[i].value1 >= value_east_wind && m_5zupai[i].value1 <= value_white_dragon)
		{
			zi = true;
		}
	}
	if (bamboo && zi)
	{
		m_bFan[ID_FAN_HUNYISE] = true;
	}
}
//三色三步高，二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckSanSeSanBuGao()
{

}
//五门齐，二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckWuMenQi()
{

}
//全求人
void NewHuPaiFanShuComputer::CheckQuanQiuRen()
{
	int quanqiuren = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_kezi_pengde ||
			m_5zupai[i].value_type == value_jiangzi)
		{
			quanqiuren++;
		}
	}
	if (quanqiuren == 5 && !m_bIsZiMo)
	{
		m_bFan[ID_FAN_QUANQIUREN] = true;
	}
}
//双暗杠
void NewHuPaiFanShuComputer::CheckShuangAnGang()
{
	int shuangangang = 0;
	for(int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_angang)
		{
			shuangangang++;
		}
	}
	if (shuangangang == 2)
	{
		m_bFan[ID_FAN_SHUANGANGANG] = true;
	}
}
//双箭刻
void NewHuPaiFanShuComputer::CheckShuangJianKe()
{
	int shuangjianke = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 ||
			m_5zupai[i].value_type == value_minggang2)
		{
			if (m_5zupai[i].value1 >= value_red_dragon && m_5zupai[i].value1 <= value_white_dragon)
			{
				shuangjianke++;
			}
		}
	}
	if (shuangjianke == 2)
	{
		m_bFan[ID_FAN_SHUANGJIANKE] = true;
	}
}
//4番
//全带幺
void NewHuPaiFanShuComputer::CheckQuanDaiYao()
{
	int quandaiyao = 0; 
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			if (m_5zupai[i].value1 == value_bamboo_1 || m_5zupai[i].value3 == value_bamboo_9)
			{
				quandaiyao++;
			}
		}
		else if (m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 ||
			m_5zupai[i].value_type == value_minggang2 ||m_5zupai[i].value_type == value_jiangzi)
		{
			if (m_5zupai[i].value1 == value_bamboo_1 || m_5zupai[i].value1 == value_bamboo_9 ||
				(m_5zupai[i].value1 >= value_east_wind && m_5zupai[i].value1 <= value_white_dragon))
			{
				quandaiyao++;
			}
		}
	}
	if (quandaiyao == 5)
	{
		m_bFan[ID_FAN_QUANDAIYAO] = true;
	}
}
//不求人
void NewHuPaiFanShuComputer::CheckBuQiuRen()
{
	int buqiuren = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_weichi || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_jiangzi)
		{
			buqiuren++;
		}
	}
	if (buqiuren == 5 && m_bIsZiMo)
	{
		m_bFan[ID_FAN_BUQIUREN] = true;
	}
}
//双明杠
void NewHuPaiFanShuComputer::CheckShuangMingGang()
{
	int shuangminggang = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_minggang1 || m_5zupai[i].value_type == value_minggang2)
		{
			shuangminggang++;
		}
	}
	if (shuangminggang == 2)
	{
		m_bFan[ID_FAN_SHUANGMINGGANG] = true;
	}
}
//胡绝张，二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckHuJueZhang()
{
	
}
//2番
//箭刻
void NewHuPaiFanShuComputer::CheckJianKe()
{
	for(int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng)
		{
			if (m_5zupai[i].value1 == value_red_dragon || m_5zupai[i].value1 == value_green_dragon || m_5zupai[i].value1 == value_white_dragon)
			{
				m_bFan[ID_FAN_JIANKE] = true;
			}
		}
	}
}
//圈风刻，二人麻将貌似没有
void NewHuPaiFanShuComputer::CheckQuanFengKe()
{

}
//门风刻，二人麻将貌似没有
void NewHuPaiFanShuComputer::CheckMenFengKe()
{

}
//门前清
void NewHuPaiFanShuComputer::CheckMenQianQing()
{
	int menqianqing = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_weichi || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_jiangzi)
		{
			menqianqing++;
		}
	}
	if (menqianqing == 5 && !m_bIsZiMo)
	{
		m_bFan[ID_FAN_MENQIANQING] = true;
	}
}
//平胡
void NewHuPaiFanShuComputer::CheckPingHu()
{
	int pinghu = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			pinghu++;
		}
		else if (m_5zupai[i].value_type == value_jiangzi && m_5zupai[i].value1 >= value_bamboo_1 && 
			m_5zupai[i].value1 <= value_bamboo_9)
		{
			pinghu++;
		}
	}
	if (pinghu == 5)
	{
		m_bFan[ID_FAN_PINGHU] = true;
	}
}
//四归一
void NewHuPaiFanShuComputer::CheckSiGuiYi()
{
	for (uint32_t i = value_bamboo_1; i < value_bamboo_9; i++)
	{
		int siguiyi = 0;
		for (int j = 0; j < 5; j++)
		{
			if (m_5zupai[j].value_type == value_shunzi_chide || m_5zupai[j].value_type == value_shunzi_weichi)
			{
				if (m_5zupai[j].value1 == i || m_5zupai[j].value2 == i || m_5zupai[j].value3 == i)
				{
					siguiyi++;
				}
			}
			else if (m_5zupai[j].value_type == value_kezi_pengde || m_5zupai[j].value_type == value_kezi_weipeng)
			{
				if (m_5zupai[j].value1 == i)
				{
					siguiyi = siguiyi + 3;
				}
			}
			else if (m_5zupai[j].value_type == value_jiangzi)
			{
				if (m_5zupai[j].value1 == i)
				{
					siguiyi = siguiyi + 2;
				}
			}
		}
		if (siguiyi == 4)
		{
			m_bFan[ID_FAN_SIGUIYI] = true;
			break;
		}
	}
}
//双同刻，二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckShuangTongKe()
{

}
//双暗刻
void NewHuPaiFanShuComputer::CheckShuangAnKe()
{
	int shuanganke = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_kezi_weipeng)
		{
			shuanganke++;
		}
	}
	if (shuanganke == 2)
	{
		m_bFan[ID_FAN_SHUANGANKE] = true;
	}
}
//暗杠
void NewHuPaiFanShuComputer::CheckAnGang()
{
	int angang = 0; 
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_angang)
		{
			angang++;
		}
	}
	if (angang == 1)
	{
		m_bFan[ID_FAN_ANGANG] = true;
	}
}
//断幺
void NewHuPaiFanShuComputer::CheckDuanYao()
{
	int duanyao = 0; 
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			if (m_5zupai[i].value1 == value_bamboo_1 || m_5zupai[i].value3 == value_bamboo_9)
			{
				duanyao++;
			}
		}
		else if (m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng ||
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 ||
			m_5zupai[i].value_type == value_minggang2 || m_5zupai[i].value_type == value_jiangzi)
		{
			if (m_5zupai[i].value1 == value_bamboo_1 || (m_5zupai[i].value1 >= value_bamboo_9 && m_5zupai[i].value1 <= value_white_dragon))
			{
				duanyao++;
			}
		}
	}
	if (duanyao == 0)
	{
		m_bFan[ID_FAN_DUANYAO] = true;
	}
}
//1番
//一般高
void NewHuPaiFanShuComputer::CheckYiBanGao()
{
	std::vector<uint32_t> vec_yibangao;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			vec_yibangao.push_back(m_5zupai[i].value1);
		}
	}
	int yibangao = 0;
	for (uint32_t i = 0; i < vec_yibangao.size(); i++)
	{
		for (uint32_t j = i+1; j < vec_yibangao.size(); j++)
		{
			if (vec_yibangao[i] == vec_yibangao[j])
			{
				yibangao++;
			}
		}
	}
	if (yibangao >= 1)//修改成最低标准
	{
		m_bFan[ID_FAN_YIBANGAO] = true;
	}
}
//喜相逢,二人麻将里不出现
void NewHuPaiFanShuComputer::CheckXiXiangFeng()
{

}
//连6
void NewHuPaiFanShuComputer::CheckLianLiu()
{
	std::vector<uint32_t> vec_lianliu;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			vec_lianliu.push_back(m_5zupai[i].value1);
		}
	}
	int lianliu = 0;
	for (uint32_t i = 0; i < vec_lianliu.size(); i++)
	{
		for (uint32_t j = i+1; j < vec_lianliu.size(); j++)
		{
			if (vec_lianliu[i] + 3 == vec_lianliu[j] || vec_lianliu[i] == vec_lianliu[j] + 3)
			{
				lianliu++;
			}
		}
	}
	if (lianliu > 0)
	{
		m_bFan[ID_FAN_LIANLIU] = true;
	}
}
//老少副
void NewHuPaiFanShuComputer::CheckLaoShaoFu()
{
	int laoshaofu123 = 0,laoshaofu789 = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_shunzi_weichi)
		{
			if (m_5zupai[i].value1 == value_bamboo_1)
			{
				laoshaofu123++;
			}
			else if (m_5zupai[i].value1 == value_bamboo_7)
			{
				laoshaofu789++;
			}
		}
	}
	if (laoshaofu123 == 1 && laoshaofu789 == 1)
	{
		m_bFan[ID_FAN_LAOSHAOFU] = true;
	}
}
//幺九刻
void NewHuPaiFanShuComputer::CheckYaoJiuKe()
{
	int yaojiuke = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_kezi_pengde || m_5zupai[i].value_type == value_kezi_weipeng || 
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 ||
			m_5zupai[i].value_type == value_minggang2)
		{
			if (m_5zupai[i].value1 == value_bamboo_1 || (m_5zupai[i].value1 >= value_bamboo_9 && m_5zupai[i].value1 <= value_white_dragon))
			{
				yaojiuke++;
			}
		}
	}
	if (yaojiuke >= 1)//改成最低标准
	{
		m_bFan[ID_FAN_YAOJIUKE] = true;
	}
}
//明杠
void NewHuPaiFanShuComputer::CheckMingGang()
{
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_minggang1 || m_5zupai[i].value_type == value_minggang2)
		{
			m_bFan[ID_FAN_MINGGANG] = true;
		}
	}
}
//缺一门，二人麻将里不会出现
void NewHuPaiFanShuComputer::CheckQueYiMen()
{

}
//无字
void NewHuPaiFanShuComputer::CheckWuZi()
{
	int wuzi = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value1 >= value_bamboo_1 && m_5zupai[i].value1 <= value_bamboo_9)
		{
			wuzi++;
		}
	}
	if (wuzi == 5)
	{
		m_bFan[ID_FAN_WUZI] = true;
	}
}
//边张
void NewHuPaiFanShuComputer::CheckBianZhang()
{

}
//坎张,
void NewHuPaiFanShuComputer::CheckKanZhang()
{
	
}
//单钓将
void NewHuPaiFanShuComputer::CheckDanDiaoJiang()
{
	int dandiaojiang = 0;
	for (int i = 0; i < 5; i++)
	{
		if (m_5zupai[i].value_type == value_shunzi_chide || m_5zupai[i].value_type == value_kezi_pengde ||
			m_5zupai[i].value_type == value_angang || m_5zupai[i].value_type == value_minggang1 || 
			m_5zupai[i].value_type == value_minggang2 || m_5zupai[i].value_type == value_jiangzi)
		{
			dandiaojiang++;
		}
	}
	if (dandiaojiang == 5)
	{
		m_bFan[ID_FAN_DANDIAOJIANG] = true;
	}
}
//花牌
void NewHuPaiFanShuComputer::CheckHuaPai()
{
	if (m_flowers > 0)
	{
		m_bFan[ID_FAN_HUAPAI] = true;
	}
}
//自摸
void NewHuPaiFanShuComputer::CheckZiMo()
{
	if (m_bIsZiMo)
	{
		m_bFan[ID_FAN_ZIMO] = true;
	}
}

void NewHuPaiFanShuComputer2::SetData(pai_group a_group,int index)
{
	if (index < 0 || index >= 7)
	{
		return;
	}
	m_7zupai[index].value1 = a_group.value1;
	m_7zupai[index].value2 = a_group.value2;
	m_7zupai[index].value3 = a_group.value3;
	m_7zupai[index].value_type = a_group.value_type;
}
void NewHuPaiFanShuComputer2::ResetAllData()
{
	m_bIsZiMo = false;
	for (int i = 0; i < 7; i++)
	{
		m_7zupai[i].Reset();
	}
	for (int i = 0; i < 81; i++)
	{
		m_bFan[i] = false;
	}
}
void NewHuPaiFanShuComputer2::CheckAllFan()
{
	CheckLianQiDui();
	CheckQiDui();
	CheckLvYiSe();
	CheckZiYiSe();
	CheckQingYiSe();
	CheckDaYuWu();
	CheckXiaoYuWu();
	CheckTuiBuDao();
	CheckHunYiSe();
	CheckQuanDaiYao();
	CheckBuQiuRen();
	CheckMenQianQing();
	CheckSiGuiYi();
	CheckDuanYao();
	CheckWuZi();
	CheckHuaPai();
	CheckZiMo();
}
void NewHuPaiFanShuComputer2::DeleteAllRepeat()
{
	//大四喜
	if (m_bFan[ID_FAN_DASIXI])
	{
		m_bFan[ID_FAN_QUANFENGKE] = false;
		m_bFan[ID_FAN_MENFENGKE] = false;
		m_bFan[ID_FAN_SANFENGKE] = false;
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
	}
	//大三元
	if (m_bFan[ID_FAN_DASANYUAN])
	{
		m_bFan[ID_FAN_JIANKE] = false;
		m_bFan[ID_FAN_SHUANGJIANKE] = false;
	}
	//九莲宝灯
	if (m_bFan[ID_FAN_JIULIANBAODENG])
	{
		m_bFan[ID_FAN_QINGYISE] = false;
		m_bFan[ID_FAN_BUQIUREN] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
	}
	//四杠
	if(m_bFan[ID_FAN_SIGANG])
	{
		m_bFan[ID_FAN_SHUANGANGANG] = false;
		m_bFan[ID_FAN_SHUANGMINGGANG] = false;
		m_bFan[ID_FAN_MINGGANG] = false;
		m_bFan[ID_FAN_ANGANG] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
	}
	//连七对
	if (m_bFan[ID_FAN_LIANQIDUI])
	{
		m_bFan[ID_FAN_QINGYISE] = false;
		m_bFan[ID_FAN_BUQIUREN] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_QIDUI] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
		m_bFan[ID_FAN_WUZI] = false;
	}
	//十三幺
	if (m_bFan[ID_FAN_SHISANYAO])
	{
		m_bFan[ID_FAN_WUMENQI] = false;
		m_bFan[ID_FAN_BUQIUREN] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_QUANDAIYAO] = false;
	}
	//清幺九
	if (m_bFan[ID_FAN_QINGYAOJIU])
	{
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_SHUANGTONGKE] = false;
		m_bFan[ID_FAN_WUZI] = false;
		m_bFan[ID_FAN_HUNYAOJIU] = false;
		m_bFan[ID_FAN_QUANDAIYAO] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
	}
	//小四喜
	if (m_bFan[ID_FAN_XIAOSIXI])
	{
		m_bFan[ID_FAN_SANFENGKE] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//小三元
	if (m_bFan[ID_FAN_XIAOSANYUAN])
	{
		m_bFan[ID_FAN_JIANKE] = false;
		m_bFan[ID_FAN_SHUANGJIANKE] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//字一色
	if (m_bFan[ID_FAN_ZIYISE])
	{
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_HUNYAOJIU] = false;
		m_bFan[ID_FAN_QUANDAIYAO] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//四暗刻
	if (m_bFan[ID_FAN_SIANKE])
	{
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_SANANKE] = false;
		m_bFan[ID_FAN_SHUANGANKE] = false;
		m_bFan[ID_FAN_BUQIUREN] = false;
	}
	//一色双龙会
	if (m_bFan[ID_FAN_YISESHUANGLONGHUI])
	{
		m_bFan[ID_FAN_PINGHU] = false;
		m_bFan[ID_FAN_QIDUI] = false;
		m_bFan[ID_FAN_QINGYISE] = false;
		m_bFan[ID_FAN_YIBANGAO] = false;
		m_bFan[ID_FAN_LAOSHAOFU] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
		m_bFan[ID_FAN_WUZI] = false;
	}
	//一色四同顺
	if (m_bFan[ID_FAN_YISESITONGSHUN])
	{
		m_bFan[ID_FAN_YISESANJIEGAO] = false;
		m_bFan[ID_FAN_YIBANGAO] = false;
		m_bFan[ID_FAN_SIGUIYI] = false;
		m_bFan[ID_FAN_YISESANTONGSHUN] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//一色四节高
	if (m_bFan[ID_FAN_YISESIJIEGAO])
	{
		m_bFan[ID_FAN_YISESANTONGSHUN] = false;
		m_bFan[ID_FAN_YISESANJIEGAO] = false;
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//一色四步高
	if (m_bFan[ID_FAN_YISESIBUGAO])
	{
		m_bFan[ID_FAN_YISESANBUGAO] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//三杠
	if (m_bFan[ID_FAN_SANGANG])
	{
		m_bFan[ID_FAN_SHUANGMINGGANG] = false;
		m_bFan[ID_FAN_SHUANGANGANG] = false;
		m_bFan[ID_FAN_MINGGANG] = false;
		m_bFan[ID_FAN_ANGANG] = false;
	}
	//混幺九
	if (m_bFan[ID_FAN_HUNYAOJIU])
	{
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_YAOJIUKE] = false;
		m_bFan[ID_FAN_QUANDAIYAO] = false;
	}
	//七对
	if (m_bFan[ID_FAN_QIDUI])
	{
		m_bFan[ID_FAN_BUQIUREN] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
	}
	//七星不靠
	if (m_bFan[ID_FAN_QIXINGBUKAO])
	{
		m_bFan[ID_FAN_WUMENQI] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_QUANBUKAO] = false;
	}
	//全双刻
	if (m_bFan[ID_FAN_QUANSHUANGKE])
	{
		m_bFan[ID_FAN_PENGPENGHU] = false;
		m_bFan[ID_FAN_DUANYAO] = false;
		m_bFan[ID_FAN_WUZI] = false;
	}
	//清一色
	if (m_bFan[ID_FAN_QINGYISE])
	{
		m_bFan[ID_FAN_WUZI] = false;
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//一色三同顺
	if (m_bFan[ID_FAN_YISESANTONGSHUN])
	{
		m_bFan[ID_FAN_YISESANJIEGAO] = false;
		m_bFan[ID_FAN_YIBANGAO] = false;
	}
	//一色三节高
	if (m_bFan[ID_FAN_YISESANJIEGAO])
	{
		m_bFan[ID_FAN_YISESANTONGSHUN] = false;
	}
	//全中
	if (m_bFan[ID_FAN_QUANZHONG])
	{
		m_bFan[ID_FAN_DUANYAO] = false;
		m_bFan[ID_FAN_WUZI] = false;
	}
	//全小
	if (m_bFan[ID_FAN_QUANXIAO])
	{
		m_bFan[ID_FAN_WUZI] = false;
		m_bFan[ID_FAN_XIAOYUWU] = false;
	}
	//清龙
	if (m_bFan[ID_FAN_QINGLONG])
	{
		m_bFan[ID_FAN_LIANLIU] = false;
		m_bFan[ID_FAN_LAOSHAOFU] = false;
	}
	//三色双龙会
	if (m_bFan[ID_FAN_SANSESHUANGLONGHUI])
	{
		m_bFan[ID_FAN_XIXIANGFENG] = false;
		m_bFan[ID_FAN_LAOSHAOFU] = false;
		m_bFan[ID_FAN_WUZI] = false;
		m_bFan[ID_FAN_PINGHU] = false;
	}
	//全带五
	if (m_bFan[ID_FAN_QUANDAIWU])
	{
		m_bFan[ID_FAN_DUANYAO] = false;
		m_bFan[ID_FAN_WUZI] = false;
	}
	//三同刻
	if (m_bFan[ID_FAN_SANTONGKE])
	{
		m_bFan[ID_FAN_SHUANGTONGKE] = false;
	}
	//三暗刻
	if (m_bFan[ID_FAN_SANANKE])
	{
		m_bFan[ID_FAN_SHUANGANKE] = false;
	}
	//全不靠
	if (m_bFan[ID_FAN_QUANBUKAO])
	{
		m_bFan[ID_FAN_WUMENQI] = false;
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
		m_bFan[ID_FAN_MENQIANQING] = false;
	}
	//大于五
	if (m_bFan[ID_FAN_DAYUWU])
	{
		m_bFan[ID_FAN_WUZI] = false;
	}
	//小于五
	if (m_bFan[ID_FAN_XIAOYUWU])
	{
		m_bFan[ID_FAN_WUZI] = false;
	}
	//三风刻
	if (m_bFan[ID_FAN_SANFENGKE])
	{
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//推不倒
	if (m_bFan[ID_FAN_TUIBUDAO])
	{
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//三色三同顺
	if (m_bFan[ID_FAN_SANSESANTONGSHUN])
	{
		m_bFan[ID_FAN_XIXIANGFENG] = false;
	}
	//妙手回春
	if (m_bFan[ID_FAN_MIAOSHOUHUICHUN])
	{
		m_bFan[ID_FAN_ZIMO] = false;
	}
	//杠上开花
	if (m_bFan[ID_FAN_GANGSHANGKAIHUA])
	{
		m_bFan[ID_FAN_ZIMO] = false;
	}
	//抢杠胡
	if (m_bFan[ID_FAN_QIANGGANGHU])
	{
		m_bFan[ID_FAN_HUJUEZHANG] = false;
	}
	//混一色
	if (m_bFan[ID_FAN_HUNYISE])
	{
		m_bFan[ID_FAN_QUEYIMEN] = false;
	}
	//全求人
	if (m_bFan[ID_FAN_QUANQIUREN])
	{
		m_bFan[ID_FAN_DANDIAOJIANG] = false;
	}
	//双暗杠
	if (m_bFan[ID_FAN_SHUANGANGANG])
	{
		m_bFan[ID_FAN_SHUANGANKE] = false;
	}
	//双箭刻
	if (m_bFan[ID_FAN_SHUANGJIANKE])
	{
		m_bFan[ID_FAN_JIANKE] = false;
	}
	//不求人
	if (m_bFan[ID_FAN_BUQIUREN])
	{
		m_bFan[ID_FAN_MENQIANQING] = false;
		m_bFan[ID_FAN_ZIMO] = false;
	}
	//双明杠
	if (m_bFan[ID_FAN_SHUANGMINGGANG])
	{
		m_bFan[ID_FAN_MINGGANG] = false;
	}
	//门风刻
	if (m_bFan[ID_FAN_MENFENGKE])
	{
		m_bFan[ID_FAN_YAOJIUKE] = false;
	}
}
int  NewHuPaiFanShuComputer2::CountFan()
{
	CStringA log_str;
	bool bWriteLog = false;
	log_str.Format("番型记录：");//if(bWriteLog)WriteLog(log_str);
	int total_fan = 0;
	if (GetSomeFan(ID_FAN_DASIXI)){total_fan += 88;log_str.Format("大四喜88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_DASANYUAN)){total_fan += 88;log_str.Format("大三元88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_LVYISE)){total_fan += 88;log_str.Format("绿一色88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_JIULIANBAODENG)){total_fan += 88;log_str.Format("九莲宝灯88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SIGANG)){total_fan += 88;log_str.Format("四杠88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_LIANQIDUI)){total_fan += 88;log_str.Format("连七对88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHISANYAO)){total_fan += 88;log_str.Format("十三幺88");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QINGYAOJIU)){total_fan += 64;log_str.Format("清幺九64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_XIAOSIXI)){total_fan += 64;log_str.Format("小四喜64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_XIAOSANYUAN)){total_fan += 64;log_str.Format("小三元64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_ZIYISE)){total_fan += 64;log_str.Format("字一色64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SIANKE)){total_fan += 64;log_str.Format("四暗刻64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESHUANGLONGHUI)){total_fan += 64;log_str.Format("一色双龙会64");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESITONGSHUN)){total_fan += 48;log_str.Format("一色四同顺48");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESIJIEGAO)){total_fan += 48;log_str.Format("一色四节高48");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESIBUGAO)){total_fan += 32;log_str.Format("一色四步高32");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANGANG)){total_fan += 32;log_str.Format("三杠32");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HUNYAOJIU)){total_fan += 32;log_str.Format("混幺九32");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QIDUI)){total_fan += 24;log_str.Format("七对24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QIXINGBUKAO)){total_fan += 24;log_str.Format("七星不靠24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANSHUANGKE)){total_fan += 24;log_str.Format("全双刻24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QINGYISE)){total_fan += 24;log_str.Format("清一色24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESANTONGSHUN)){total_fan += 24;log_str.Format("一色三同顺24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESANJIEGAO)){total_fan += 24;log_str.Format("一色三节高24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANDA)){total_fan += 24;log_str.Format("全大24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANZHONG)){total_fan += 24;log_str.Format("全中24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANXIAO)){total_fan += 24;log_str.Format("全小24");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QINGLONG)){total_fan += 16;log_str.Format("清龙16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANSESHUANGLONGHUI)){total_fan += 16;log_str.Format("三色双龙会16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YISESANBUGAO)){total_fan += 16;log_str.Format("一色三步高16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANDAIWU)){total_fan += 16;log_str.Format("全带五16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANTONGKE)){total_fan += 16;log_str.Format("三同刻16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANANKE)){total_fan += 16;log_str.Format("三暗刻16");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANBUKAO)){total_fan += 12;log_str.Format("全不靠12");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_ZUHELONG)){total_fan += 12;log_str.Format("组合龙12");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_DAYUWU)){total_fan += 12;log_str.Format("大于五12");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_XIAOYUWU)){total_fan += 12;log_str.Format("小于五12");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANFENGKE)){total_fan += 12;log_str.Format("三风刻12");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HUALONG)){total_fan += 8;log_str.Format("花龙8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_TUIBUDAO)){total_fan += 8;log_str.Format("推不倒8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANSESANTONGSHUN)){total_fan += 8;log_str.Format("三色三同顺8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANSESANJIEGAO)){total_fan += 8;log_str.Format("三色三节高8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_WUFANHU)){total_fan += 8;log_str.Format("无番胡8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_MIAOSHOUHUICHUN)){total_fan += 8;log_str.Format("妙手回春8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HAIDILAOYUE)){total_fan += 8;log_str.Format("海底捞月8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_GANGSHANGKAIHUA)){total_fan += 8;log_str.Format("杠上开花8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QIANGGANGHU)){total_fan += 8;log_str.Format("抢杠胡8");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_PENGPENGHU)){total_fan += 6;log_str.Format("碰碰胡6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HUNYISE)){total_fan += 6;log_str.Format("混一色6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SANSESANBUGAO)){total_fan += 6;log_str.Format("三色三步高6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_WUMENQI)){total_fan += 6;log_str.Format("五门齐6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANQIUREN)){total_fan += 6;log_str.Format("全求人6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHUANGANGANG)){total_fan += 6;log_str.Format("双暗杠6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHUANGJIANKE)){total_fan += 6;log_str.Format("双箭刻6");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANDAIYAO)){total_fan += 4;log_str.Format("全带幺4");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_BUQIUREN)){total_fan += 4;log_str.Format("不求人4");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHUANGMINGGANG)){total_fan += 4;log_str.Format("双明杠4");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HUJUEZHANG)){total_fan += 4;log_str.Format("胡绝张4");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_JIANKE)){total_fan += 2;log_str.Format("箭刻2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUANFENGKE)){total_fan += 2;log_str.Format("圈风刻2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_MENFENGKE)){total_fan += 2;log_str.Format("门风刻2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_MENQIANQING)){total_fan += 2;log_str.Format("门前清2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_PINGHU)){total_fan += 2;log_str.Format("平胡2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SIGUIYI)){total_fan += 2;log_str.Format("四归一2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHUANGTONGKE)){total_fan += 2;log_str.Format("双同刻2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_SHUANGANKE)){total_fan += 2;log_str.Format("双暗刻2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_ANGANG)){total_fan += 2;log_str.Format("暗杠2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_DUANYAO)){total_fan += 2;log_str.Format("断幺2");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YIBANGAO)){total_fan += 1;log_str.Format("一般高1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_XIXIANGFENG)){total_fan += 1;log_str.Format("喜相逢1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_LIANLIU)){total_fan += 1;log_str.Format("连六1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_LAOSHAOFU)){total_fan += 1;log_str.Format("老少副1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_YAOJIUKE)){total_fan += 1;log_str.Format("幺九刻1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_MINGGANG)){total_fan += 1;log_str.Format("明杠1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_QUEYIMEN)){total_fan += 1;log_str.Format("缺一门1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_WUZI)){total_fan += 1;log_str.Format("无字1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_BIANZHANG)){total_fan += 1;log_str.Format("边张1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_KANZHANG)){total_fan += 1;log_str.Format("坎张1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_DANDIAOJIANG)){total_fan += 1;log_str.Format("单钓将1");if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_HUAPAI)){total_fan += m_flowers;log_str.Format("花牌%d",m_flowers);if(bWriteLog)WriteLog(log_str);}
	if (GetSomeFan(ID_FAN_ZIMO)){total_fan += 1;log_str.Format("自摸1");if(bWriteLog)WriteLog(log_str);}
	return total_fan;
}
//连七对
void NewHuPaiFanShuComputer2::CheckLianQiDui()
{
	int l = 0;
	for (int i = 0; i < 6 ;i++)
	{
		if (m_7zupai[i].value1 +1 == m_7zupai[i+1].value1 && m_7zupai[i].value1 >= value_bamboo_1 && m_7zupai[i].value1 <= value_bamboo_9)//加上数字限制是为了避免全字七对被判为连七对
		{
			l++;
		}
	}
	if (l == 6)
	{
		m_bFan[ID_FAN_LIANQIDUI] = true;
	}
}
//七对
void NewHuPaiFanShuComputer2::CheckQiDui()
{
	m_bFan[ID_FAN_QIDUI] = true;
}
void NewHuPaiFanShuComputer2::CheckLvYiSe()
{
	int lvyise = 0;
	for (int i = 0; i < 7; i++)
	{
		if (m_7zupai[i].value1 != value_bamboo_2 && m_7zupai[i].value1 != value_bamboo_3 && 
			m_7zupai[i].value1 != value_bamboo_4 && m_7zupai[i].value1 != value_bamboo_6 &&
			m_7zupai[i].value1 != value_bamboo_8 && m_7zupai[i].value1 != value_green_dragon)
		{
			lvyise++;
		}	
	}
	if (lvyise == 7)
	{
		m_bFan[ID_FAN_LVYISE] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckZiYiSe()
{
	int kezi = 0;
	for (int i = 0; i < 7; i++)
	{
		if (m_7zupai[i].value1 >= value_east_wind && m_7zupai[i].value1 <= value_white_dragon)
		{
			kezi++;
		}
	}
	if (kezi == 7)
	{
		m_bFan[ID_FAN_ZIYISE] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckQingYiSe()
{
	int qingyise = 0;
	for (int i = 0; i < 7; i++)
	{
		if (m_7zupai[i].value1 >= value_bamboo_1 && m_7zupai[i].value1 <= value_bamboo_9)
		{
			qingyise++;
		}
	}
	if (qingyise == 7)
	{
		m_bFan[ID_FAN_QINGYISE] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckDaYuWu()
{
	int dayuwu = 0;
	for(int i = 0; i < 7; i++)
	{
		if (m_7zupai[i].value1 >= value_bamboo_6 && m_7zupai[i].value1 <= value_bamboo_9)
		{
			dayuwu++;
		}
	}
	if (dayuwu == 7)
	{
		m_bFan[ID_FAN_DAYUWU] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckXiaoYuWu()
{
	int dayuwu = 0;
	for(int i = 0; i < 7; i++)
	{
		if (m_7zupai[i].value1 >= value_bamboo_1 && m_7zupai[i].value1 <= value_bamboo_4)
		{
			dayuwu++;
		}
	}
	if (dayuwu == 7)
	{
		m_bFan[ID_FAN_XIAOYUWU] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckTuiBuDao()
{
	int tuibudao = 0;
	for (int i = 0; i < 7; i++)
	{
		if (m_7zupai[i].value1 == value_bamboo_2 || m_7zupai[i].value1 == value_bamboo_4 ||
			m_7zupai[i].value1 == value_bamboo_5 || m_7zupai[i].value1 == value_bamboo_6 ||
			m_7zupai[i].value1 == value_bamboo_8 || m_7zupai[i].value1 == value_bamboo_9)
		{
			tuibudao++;
		}
	}
	if (tuibudao == 7)
	{
		m_bFan[ID_FAN_TUIBUDAO] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckHunYiSe()
{
	bool bamboo = false,zi = false;
	for (int i = 0; i < 7; i++)
	{
		if (m_7zupai[i].value1 >= value_bamboo_1 && m_7zupai[i].value1 <= value_bamboo_9)
		{
			bamboo = true;
		}
		else if (m_7zupai[i].value1 >= value_east_wind && m_7zupai[i].value1 <= value_white_dragon)
		{
			zi = true;
		}
	}
	if (bamboo && zi)
	{
		m_bFan[ID_FAN_HUNYISE] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckQuanDaiYao()
{
	int quandaiyao = 0; 
	for (int i = 0; i < 7; i++)
	{
		if (m_7zupai[i].value1 == value_bamboo_1 || m_7zupai[i].value1 == value_bamboo_9 ||
			(m_7zupai[i].value1 >= value_east_wind && m_7zupai[i].value1 <= value_white_dragon))
		{
			quandaiyao++;
		}
	}
	if (quandaiyao == 7)
	{
		m_bFan[ID_FAN_QUANDAIYAO] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckBuQiuRen()
{
	if (m_bIsZiMo)
	{
		m_bFan[ID_FAN_BUQIUREN] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckMenQianQing()
{
	if (!m_bIsZiMo)
	{
		m_bFan[ID_FAN_MENQIANQING] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckSiGuiYi()
{
	for (uint32_t i = value_bamboo_1; i < value_white_dragon; i++)
	{
		int siguiyi = 0;
		for (int j = 0; j < 7; j++)
		{
			if (m_7zupai[j].value1 == i)
			{
				siguiyi = siguiyi + 2;
			}
		}
		if (siguiyi == 4)
		{
			m_bFan[ID_FAN_SIGUIYI] = true;
			break;
		}
	}
}
void NewHuPaiFanShuComputer2::CheckDuanYao()
{
	int duanyao = 0; 
	for (int i = 0; i < 7; i++)
	{
		if (m_7zupai[i].value1 == value_bamboo_1 || (m_7zupai[i].value1 >= value_bamboo_9 && m_7zupai[i].value1 <= value_white_dragon))
		{
			duanyao++;
		}
	}
	if (duanyao == 0)
	{
		m_bFan[ID_FAN_DUANYAO] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckWuZi()
{
	int wuzi = 0;
	for (int i = 0; i < 7; i++)
	{
		if (m_7zupai[i].value1 >= value_bamboo_1 && m_7zupai[i].value1 <= value_bamboo_9)
		{
			wuzi++;
		}
	}
	if (wuzi == 7)
	{
		m_bFan[ID_FAN_WUZI] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckHuaPai()
{
	if (m_flowers > 0)
	{
		m_bFan[ID_FAN_HUAPAI] = true;
	}
}
void NewHuPaiFanShuComputer2::CheckZiMo()
{
	if (m_bIsZiMo)
	{
		m_bFan[ID_FAN_ZIMO] = true;
	}
}