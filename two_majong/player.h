#pragma once

#include "poke.h"
using namespace std;




struct player
{

	player() : userid(0), is_auto(false), is_drop(false),m_hu_status(0) {}

	void WriteLog(CStringA str)
	{
		ofstream f;
		SYSTEMTIME systime;
		GetLocalTime(&systime);
		TCHAR szCurrentPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szCurrentPath);
		CStringA strPath,strpathall;
		strPath = "\\log\\ddzlog.txt";
		strPath.Format("\\log\\ddzlog_%d-%d-%d.txt", systime.wYear, systime.wMonth, systime.wDay);
		strpathall = szCurrentPath + strPath;
		f.open(strpathall, ios::app|ios::out);
		CStringA strInfo;
		strInfo.Format("%d-%02d-%02d %02d:%02d:%02d.%03d  ", systime.wYear, systime.wMonth, systime.wDay, 
			systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds);
		f << strInfo;
		f << str << endl;
		f.close();
	}

	long long									userid;
	bool										is_auto;					// �Ƿ��й�
	bool										is_drop;					// �Ƿ����
	bool										is_ting;					// �Ƿ�����
	int											m_double;					// �ӱ�
	char										m_ming_gang_count1;			// ������1
	char										m_ming_gang_count2;			// ������2
	char										m_an_gang_count;			// ������
	
	uint32_t									m_current_status;			// ��ǰץ��״̬��=1������=2����
	bool										m_is_get_a_card;			// ʵ�ʷ���һ���ƣ���Ϊ����Ϊ�������޷���ʱץ�ƣ�����ֱ�����Ӧ�ú��ļ�⵽����

	uint32_t									m_hu_clock_when_is_ting;	// ��ʱ���Ƽ�ʱ10��

	bool										m_miao_shou_hui_chun;		// �������ⷬ�ͣ����ֻش�
	bool										m_hai_di_lao_yue;			// �������ⷬ�ͣ���������
	bool										m_gang_shang_kai_hua;		// �������ⷬ�ͣ����Ͽ���
	bool										m_qiang_gang_hu;			// �������ⷬ�ͣ����ܺ�

	std::vector<pai_kind>						m_pais_in_hand;				// ���ϵ���
	std::vector<pai_kind>						m_pais_on_table;			// ����������ϵ��ƣ�������
	std::vector<pai_kind>						m_pais_flowers;				// ����Ļ�
	std::vector<std::vector<pai_kind>>			m_pais_chew_pong_kong;		// �����ܳ�����
	char										m_flag_for_ming_an[4];		// �����ܱ�ǣ�Ϊ����������=1����=2��1��=3��2
	std::vector<uint32_t>						m_ting_cards;				// ��������Щ��,��ֵ��ʾ����Ψһֵ
	uint32_t									m_last_pai;					// ���������ƣ�Ψһֵ
	uint32_t									JIANG;						// ����
	player										*m_oppisite_player;			// ָ����һ�ҵ�ָ��
	std::vector<pai_kind>						m_all_pais;					// ������()

	bool										m_is_jia_bei_check_ting;	// �������ͺ�ͬʱ����ʱ��������ʾ������Ҫ�������ӱ����ٴμ��
	uint32_t									m_sort_jiang;				// �µķ��͸�������
	//��������ͬ�жϳԣ������ܣ��������ĺ���ͳһ�Ƶ��������,���ͷ������߼����Ӷ�
	std::map<uint32_t,std::vector<chew_struct_data>> m_map_table_for_chew;	// �洢�ɳ��Ƶı�����,key:����һ����value������һ��chew_struct_data�����˶���������
	std::vector<chew_struct_data>				m_vec_check_chew;			// �������ĿɳԱ������Ψһֵ
	std::vector<chew_struct_data>				m_vec_check_peng;			// �������Ŀ����������Ψһֵ
	std::vector<chew_struct_data>				m_vec_check_an_gang;		// �������Ŀɰ��ܱ������Ψһֵ
	std::vector<chew_struct_data>				m_vec_check_ming_gang1;		// �������Ŀ�����1��,�����Ʋ����Ⱥ󣬴����Ψһֵ
	std::vector<chew_struct_data>				m_vec_check_ming_gang2;		// �������Ŀ�����2��ֻ�е�һ����Ч�������Ψһֵ
	uint32_t									m_check_ting[2][16][16];	// �������Ŀ�����һά��=0��ʾ���м��ţ�=1��ʾ��������ά��ȥ�����ƣ���ά�����ӵ��ƣ���Ϊ��ֵ
	int											m_check_hu[2];				// ���������ɺ���,=0������,Ψһֵ��=1����
	uint32_t									m_judge_flag[7];			// ���ñ�ǣ�ʵ��������ʾ�ж��ٸ�������ж��ٸ������ڲ�ѯ����һ�����ԣ��ڶ���������
																			// �����������ܣ����ĸ�������1�������������2�����������������߸�����
	MjHuPaiFanShuComputer						m_fan_helper;				// ��������

	NewHuPaiFanShuComputer						m_normal_fan_helper;		// ������Ƶķ�����������ͨ��
	NewHuPaiFanShuComputer2						m_qidui_fan_helper;			// ������Ƶķ����������߶԰�

	int											m_hu_status;				// �����������ͨ��=1��2=�߶Ժ������ܻ�������
	//�������ϵ��ƣ�������ֵ��С����
	void HandPaiSort();
	//��һ����Ϸ��ʼʱ���ó�ʼ��ÿ�����
	void on_new_game();
	//������ͱ�
	void LoadChewTable();
	//������е��жϱ�,����CheckAllJudgeǰ�ȵ��ô˺����������ǰһ�ε�
	void ClearAllJudge();
	//�������
	void CheckAllJudge();
	//����
	void CheckChi();
	//�����
	void CheckPeng();
	//��ⰵ��
	void CheckAnGang();
	//�������1
	void CheckMingGang1();
	//�������2
	void CheckMingGang2();
	//����
	void CheckHu();
	//�����
	void CheckTing();
	//�����жϺ���
	uint32_t Hu(uint32_t PAI[16]);
	//�����βΰ�һ����������Ȼ���������з��ױ��
	uint32_t Remain(uint32_t PAI[16]);
	//���������
	uint32_t GetHuFan();
	//����������
	uint32_t GetTingFan(uint32_t u32Add,uint32_t u32Minus);
	//���㷬��
	uint32_t GetFan(int64_t &fan_flag,bool bComputeIt=false);
	//����Ƿ������л�,�У����ػ���Ψһֵ���񣬷���0
	uint32_t CheckFlower();
	//�����������油�������ƣ�Ψһֵ
	void DeleteACard(uint32_t flower);
	//��һ����,����Ψһֵ
	void AddACard(uint32_t u32RealCard);
	//���öԼ���������״̬
	void SetOppisiteZiMoStatus();
	//�����Լ���������״̬
	void SetMyZiMoStatus();
	//�����������
	bool ProcessOutACard(uint32_t u32RealCard);
	//�������
	bool ProcessChi(uint32_t index,uint32_t &ret0,uint32_t &ret1,uint32_t &ret2);
	//��������
	bool ProcessPeng(uint32_t index,uint32_t &ret0,uint32_t &ret1,uint32_t &ret2);
	//������
	bool ProcessAnGang(uint32_t u32Value);
	//��������1
	bool ProcessMingGang1(uint32_t u32Value);
	//��������2
	bool ProcessMingGang2(uint32_t u32RealCard);
	//�������
	void ProcessFangQi();
	//������
	void ProcessTing(uint32_t &index);
	//����ӱ�
	void ProcessJiaBei();
	//�������һ����
	void SetLastPai(uint32_t pai);
	//����һ��������
	void SetAllPai(std::vector<pai_kind> pai_group);
	//���ͼ���
	void PreProcess();
	//���ͼ��㸨������
	uint32_t SortFanCards(uint32_t PAI[16],std::vector<uint32_t> &vec_value,std::vector<uint32_t> &vec_jiang_value);
	//���ͼ��㣨�߶�ר�ã�
	void PreProcess2(uint32_t qiduipai[16]);
	//�����󽫷���Ҳ�����ͻ���ʱ�õ�
	void SetResultFan(int &fan0,int &fan1,int &fan2,bool bIsNormal = true);
	//�����жϺ�
	//uint32_t Remain(uint32_t PAI[16]);
};

