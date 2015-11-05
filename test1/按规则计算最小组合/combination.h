#pragma once
#include <stdio.h>
#include <vector>
#include <set>
using namespace std;

#define CT_SINGLE					1									//单牌类型
#define CT_DOUBLE					2									//对牌类型
#define CT_THREE					3									//三条类型
#define CT_SINGLE_LINE				4									//单连类型
#define CT_DOUBLE_LINE				5									//对连类型
#define CT_THREE_LINE				6									//三连类型

#define CT_BOMB_CARD				12									//炸弹类型

struct CombinaCard
{
	//牌组
	vector<int> data;
	int type = 0;
};

class Analyse
{
public:
	Analyse();
	
	void CombinaCardSplit();	//把m_test_data拆到vector<CombinaCard>中
	//把src_data拆成m_single_card,m_double_card，m_three_card，m_four_card四个基本牌型
	void GetBase(vector<int> src_data);
	//实际上是根据m_single_card，m_double_card，m_three_card，m_four_card来拆分
	void GetSingleLine();	
	void GetDoubleLine();
	void GetThreeLine();

	void ClearCombina();	//清除所有vector<CombinaCard>的数据

	int GetCardCombNum(vector<int> src_data, vector<CombinaCard> &final_comb, int extra_reduce_num = 0);	//是3连允许的额外带牌数

	void RemoveSubDataFromSrcData(vector<int> &src_data, vector<int> sub_data);

	int m_min_comb = 17;	//先设置最大手数，全部都是单张

	vector<int> m_all_data;

	vector<int> m_store_data;	//用于存放m_test_data
	vector<int> m_test_data;	//随机取17张的测试牌型
private:
	vector<CombinaCard> m_single_card;	//1张
	vector<CombinaCard> m_double_card;	//2张
	vector<CombinaCard> m_three_card;	//3张
	vector<CombinaCard> m_four_card;	//4张
	vector<CombinaCard> m_single_line_card;	//顺子
	vector<CombinaCard> m_double_line_card;	//连对
	vector<CombinaCard> m_three_line_card;	//飞机

};