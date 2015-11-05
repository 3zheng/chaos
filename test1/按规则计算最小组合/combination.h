#pragma once
#include <stdio.h>
#include <vector>
#include <set>
using namespace std;

#define CT_SINGLE					1									//��������
#define CT_DOUBLE					2									//��������
#define CT_THREE					3									//��������
#define CT_SINGLE_LINE				4									//��������
#define CT_DOUBLE_LINE				5									//��������
#define CT_THREE_LINE				6									//��������

#define CT_BOMB_CARD				12									//ը������

struct CombinaCard
{
	//����
	vector<int> data;
	int type = 0;
};

class Analyse
{
public:
	Analyse();
	
	void CombinaCardSplit();	//��m_test_data��vector<CombinaCard>��
	//��src_data���m_single_card,m_double_card��m_three_card��m_four_card�ĸ���������
	void GetBase(vector<int> src_data);
	//ʵ�����Ǹ���m_single_card��m_double_card��m_three_card��m_four_card�����
	void GetSingleLine();	
	void GetDoubleLine();
	void GetThreeLine();

	void ClearCombina();	//�������vector<CombinaCard>������

	int GetCardCombNum(vector<int> src_data, vector<CombinaCard> &final_comb, int extra_reduce_num = 0);	//��3������Ķ��������

	void RemoveSubDataFromSrcData(vector<int> &src_data, vector<int> sub_data);

	int m_min_comb = 17;	//���������������ȫ�����ǵ���

	vector<int> m_all_data;

	vector<int> m_store_data;	//���ڴ��m_test_data
	vector<int> m_test_data;	//���ȡ17�ŵĲ�������
private:
	vector<CombinaCard> m_single_card;	//1��
	vector<CombinaCard> m_double_card;	//2��
	vector<CombinaCard> m_three_card;	//3��
	vector<CombinaCard> m_four_card;	//4��
	vector<CombinaCard> m_single_line_card;	//˳��
	vector<CombinaCard> m_double_line_card;	//����
	vector<CombinaCard> m_three_line_card;	//�ɻ�

};