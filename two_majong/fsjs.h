#ifndef _FSJS_H_
#define _FSJS_H_

#include <stdint.h>
#include <vector>
enum CardValue{value_unknown=0, value_bamboo_1=1, value_bamboo_2=2, value_bamboo_3=3, value_bamboo_4=4, value_bamboo_5=5, value_bamboo_6=6,
	value_bamboo_7=7, value_bamboo_8=8, value_bamboo_9=9, value_east_wind=10, value_south_wind=11, value_west_wind=12, value_north_wind=13,
	value_red_dragon=14, value_green_dragon=15, value_white_dragon=16,value_flower=17,value_blank=18};
/************************************************************************/
/* 番数计算器(拼音：FSJS，番数计算)                                     */
/************************************************************************/
//可只用值来计算
class FSJS
{
	std::vector<uint32_t> vec_all_cards;
	uint32_t data_count[16];
public:
	void init(){vec_all_cards.clear();for(int i = 0; i < 16;i++)data_count[i] = 0;}
	void SetAllData(std::vector<uint32_t> all_cards){vec_all_cards = all_cards;}
	void CountData();
	//88番
	//大四喜
	bool IsDaSiXi();
	//大三元
	bool IsDaSanYuan();

};

#endif