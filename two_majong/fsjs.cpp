#include "fsjs.h"

void FSJS::CountData()
{
	for (uint32_t i = 0; i < vec_all_cards.size(); i++)
	{
		data_count[vec_all_cards[i] - 1]++;
	}
}

bool FSJS::IsDaSiXi()
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

bool FSJS::IsDaSanYuan()
{
	CountData();
	if (data_count[value_red_dragon-1] == 3 && data_count[value_green_dragon-1] == 3 && data_count[value_white_dragon-1] == 3)
	{
		return true;
	}
	return false;
}