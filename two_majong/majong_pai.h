#pragma once
#include <stdint.h>
#include <vector>
#include <map>
#include <atlstr.h>
#include <fstream>
#include <iostream>
#include <atltime.h>
using namespace std;

#define MAX_USERS 2

// ��ID��˳��Ϊ1���һ�ţ�2���һ�ţ���������1��ڶ��ţ�2��ڶ��ţ���������9������ţ������ϣ����������У������ף������ģ������÷�������񣬾�
enum CardId {			id_unknown=0,		bamboo_1A=1,		bamboo_2A=2,		bamboo_3A=3,	bamboo_4A=4,		bamboo_5A=5,		bamboo_6A=6,		bamboo_7A=7,
	bamboo_8A=8,		bamboo_9A=9,		east_wind_A=10,		south_wind_A=11,	west_wind_A=12, north_wind_A=13,	red_dragon_A=14,	green_dragon_A=15,	white_dragon_A=16,
	bamboo_1B=17,		bamboo_2B=18,		bamboo_3B=19,		bamboo_4B=20,		bamboo_5B=21,	bamboo_6B=22,		bamboo_7B=23,
	bamboo_8B=24,		bamboo_9B=25,		east_wind_B=26,		south_wind_B=27,	west_wind_B=28, north_wind_B=29,	red_dragon_B=30,	green_dragon_B=31,	white_dragon_B=32,
	bamboo_1C=33,		bamboo_2C=34,		bamboo_3C=35,		bamboo_4C=36,		bamboo_5C=37,	bamboo_6C=38,		bamboo_7C=39, 
	bamboo_8C=40,		bamboo_9C=41,		east_wind_C=42,		south_wind_C=43,	west_wind_C=44,	north_wind_C=45,	red_dragon_C=46,	green_dragon_C=47,	white_dragon_C=48,
	bamboo_1D=49,		bamboo_2D=50,		bamboo_3D=51,		bamboo_4D=52,		bamboo_5D=53,	bamboo_6D=54,		bamboo_7D=55,
	bamboo_8D=56,		bamboo_9D=57,		east_wind_D=58,		south_wind_D=59,	west_wind_D=60, north_wind_D=61,	red_dragon_D=62,	green_dragon_D=63,	white_dragon_D=64,
	flower_spring=65,	flower_summer=66,	flower_autumn=67,	flower_winter=68,	flower_plum=69, flower_orchid=70,	flower_bamboo=71,	flower_chrysanthemum=72};
//����������ֵ����4��1��Ϊ��ͬ��value_bamboo_1
enum CardValue{value_unknown=0, value_bamboo_1=1, value_bamboo_2=2, value_bamboo_3=3, value_bamboo_4=4, value_bamboo_5=5, value_bamboo_6=6,
	value_bamboo_7=7, value_bamboo_8=8, value_bamboo_9=9, value_east_wind=10, value_south_wind=11, value_west_wind=12, value_north_wind=13,
	value_red_dragon=14, value_green_dragon=15, value_white_dragon=16,value_flower=17,value_blank=18};

enum CardStatus{status_sleep = 0,		status_in_hand_normal = 1,		status_in_hand_select = 2,		status_out_normal = 3,		status_chew_self = 4,		status_chew_oppisite = 5,
	status_pong_self = 6,	status_pong_oppisite = 7,		status_kong_self = 8,			status_kong_oppisite = 9,	status_win = 10,status_in_hand_reverse = 11};


//�齫����������
class PaiKind
{
public:
	uint32_t u32RealCard;//��ʵ�ƺţ���card_id�е�ֵ
	uint32_t u32ValueCard;//��ʵֵ����card_value�е�ֵ
	uint32_t u32Status;//״ֵ̬��=0δץ�����������м䣻=1��������е��ƣ�δѡ��ƽ�ţ���=2��������е��ƣ�ѡ�����𣬽�Ҫ���״̬��
	//=3������ƣ��������ϣ�=4���ƣ��Լ��ģ���=5���ƣ��Լҵģ���=6���ƣ��Լ�����=7���ƣ��Լҵģ���=8����(�Լ���
	//=9���ƣ��Լҵģ�=10ȫ����������
	static CardValue GetValueFromRealCard(uint32_t u32Real)
	{
		CardValue ret = value_unknown;
		if(u32Real == bamboo_1A			|| u32Real == bamboo_1B			|| u32Real == bamboo_1C			|| u32Real == bamboo_1D)			{ret = value_bamboo_1;return ret;}
		if(u32Real == bamboo_2A			|| u32Real == bamboo_2B			|| u32Real == bamboo_2C			|| u32Real == bamboo_2D)			{ret = value_bamboo_2;return ret;}
		if(u32Real == bamboo_3A			|| u32Real == bamboo_3B			|| u32Real == bamboo_3C			|| u32Real == bamboo_3D)			{ret = value_bamboo_3;return ret;}
		if(u32Real == bamboo_4A			|| u32Real == bamboo_4B			|| u32Real == bamboo_4C			|| u32Real == bamboo_4D)			{ret = value_bamboo_4;return ret;}
		if(u32Real == bamboo_5A			|| u32Real == bamboo_5B			|| u32Real == bamboo_5C			|| u32Real == bamboo_5D)			{ret = value_bamboo_5;return ret;}
		if(u32Real == bamboo_6A			|| u32Real == bamboo_6B			|| u32Real == bamboo_6C			|| u32Real == bamboo_6D)			{ret = value_bamboo_6;return ret;}
		if(u32Real == bamboo_7A			|| u32Real == bamboo_7B			|| u32Real == bamboo_7C			|| u32Real == bamboo_7D)			{ret = value_bamboo_7;return ret;}
		if(u32Real == bamboo_8A			|| u32Real == bamboo_8B			|| u32Real == bamboo_8C			|| u32Real == bamboo_8D)			{ret = value_bamboo_8;return ret;}
		if(u32Real == bamboo_9A			|| u32Real == bamboo_9B			|| u32Real == bamboo_9C			|| u32Real == bamboo_9D)			{ret = value_bamboo_9;return ret;}
		if(u32Real == east_wind_A		|| u32Real == east_wind_B		|| u32Real == east_wind_C		|| u32Real == east_wind_D)			{ret = value_east_wind;return ret;}
		if(u32Real == south_wind_A		|| u32Real == south_wind_B		|| u32Real == south_wind_C		|| u32Real == south_wind_D)			{ret = value_south_wind;return ret;}
		if(u32Real == west_wind_A		|| u32Real == west_wind_B		|| u32Real == west_wind_C		|| u32Real == west_wind_D)			{ret = value_west_wind;return ret;}
		if(u32Real == north_wind_A		|| u32Real == north_wind_B		|| u32Real == north_wind_C		|| u32Real == north_wind_D)			{ret = value_north_wind;return ret;}
		if(u32Real == red_dragon_A		|| u32Real == red_dragon_B		|| u32Real == red_dragon_C		|| u32Real == red_dragon_D)			{ret = value_red_dragon;return ret;}
		if(u32Real == green_dragon_A	|| u32Real == green_dragon_B	|| u32Real == green_dragon_C	|| u32Real == green_dragon_D)		{ret = value_green_dragon;return ret;}
		if(u32Real == white_dragon_A	|| u32Real == white_dragon_B	|| u32Real == white_dragon_C	|| u32Real == white_dragon_D)		{ret = value_white_dragon;return ret;}
		if(u32Real == flower_spring		|| u32Real == flower_summer		|| u32Real == flower_autumn		|| u32Real == flower_winter
			|| u32Real == flower_plum		|| u32Real == flower_orchid		|| u32Real == flower_bamboo		|| u32Real == flower_chrysanthemum)	{ret = value_flower;return ret;}
		return ret;
	}
	
};


enum SupectJudgeType
{
	emJudgeNone,
	emJudgeAnJianJingLing,			//��������
	emJudgeAllAuto,					//ȫ���й�
	emJudgeOther
};

enum AutoType
{
	emAutoNone,				//δ�й�
	emActiveAuto,			//�����й�(��������й�)
	emPassiveAuto			//�����й�(����˳�ʱ�й�)
};

enum GameState
{
	FAPAI = 1,	//���ƽ׶�
	//BUHUA = 2,	//�����׶�
	CHUPAI = 3,	//���ƽ׶�
	GAMEEND = 4,	//��Ϸ��������ʾ��������
	ROUNDEND = 5,	//һ�ֽ���
};

//�̶�������
enum FixedType
{
	//ֵ��twomajong.proto��ACTION����һ��
	UNKNOWN = 0,
	CHI = 1,
	PENG = 2,
	GANG = 3,
};

//�������Ժ�̶�����
struct FixedCard
{
	FixedType type = FixedType::UNKNOWN;	//��������
	CardValue card_group[4];	//����ֵ

	FixedCard()
	{
		for (int i = 0; i < 4; i++)
		{
			card_group[i] = CardValue::value_unknown;
		}
	}
};
//���Ʊ�����ݵ�Ԫ�ṹ
//�淶���ԣ�pai1,pai2��¼׼���Ե��ƣ�pai3��¼�����ı�����
//		����pai1,pai2��¼׼�������ƣ�pai3��¼�����ı�����
//		���ܣ�pai1,pai2,pai3��¼׼�����ܵ��ƣ�pai4��¼�����ı�����
//		����1�����ż�¼����1����
//		����2��ֻ��¼pai1ΪҪ�ܵ���
struct chew_struct_data
{
	uint32_t pai1;
	uint32_t pai2;
	uint32_t pai3;
	uint32_t pai4;
	void init(){pai1 = id_unknown;pai2 = id_unknown;pai3 = id_unknown;pai4 = id_unknown;}
};

enum AutoType
{
	emAutoNone,				//δ�й�
	emActiveAuto,			//�����й�(��������й�)
	emPassiveAuto			//�����й�(����˳�ʱ�й�)
};

//������ݽṹ
struct PlayerData
{
	enum PlayerStep
	{
		//ÿ���ֵ�һ����Ҳ���ʱ��Ϊ�����׶Σ�ץ�ƽ׶���ȥ�ƺӲ������ƻ��߳����ܵĲ��������ƽ׶��ǳ����ܺ��һ����
		GETSETP = 1,	//ץ�ƽ׶�
		OUTSETP = 2,	//���ƽ׶�
	};
	uint32_t seat_id = 0;
	uint64_t user_id = 0;

	AutoType auto_type;
	PlayerStep step;
	//���ƣ���card_valueΪ�±������ [0]��ȱ���ߺ��� ���������ƣ���Ϊ�����޷���������ж�
	//��������Ϊ1��������2�������������װ壬��ôhand_pai[value_bamboo_1] = 1,hand_pai[value_bamboo_5] = 2,hand_pai[value_white_dragon] = 3
	//���ڿ����ж��Ƿ����
	uint32_t hand_pai[17];
	//�������ƣ���card_idΪ�±�����ƣ�[0]unknown���� ���������и�����A�ţ���ôhand_card_id[white_dragon_A] = true; һ����ϣ�����ݽṹ���ڿ���У�����ƣ���������ܺ�Ҳ�ᱻ��Ϊfalse
	bool hand_card_id[73];
	//�ѹ̶������飬�����Ѿ��������˵��ƣ������ٺ������������������
	vector<FixedCard> fixed_card;
	//û�����Ƶ���������������ָ�����ܺ����
	uint32_t remain_hidden_count;

	PlayerData()
	{
		for (int i = 0; i < 17; i++)
		{
			hand_pai[i] = 0;
		}

		for (int i = 0; i < 73; i++)
		{
			hand_card_id[i] = false;
		}
	}
};
//���Ʒ���������
class MjHuPaiFanShuComputer
{
public:
	void SetAllData(std::vector<uint32_t> all_cards){vec_all_cards = all_cards;}
	void SetHandData(std::vector<uint32_t> hand_cards){vec_hand_cards = hand_cards;}
	char m_an_gang_count;//ԭ��������ֻ��Ҫ���жϷ��͵ĵط��ĳ���1����
	char m_ming_gang_count1;//��1,ԭ����1��ֻ��Ҫ���жϷ��͵ĵط��ĳɰ��ܼ���
	char m_ming_gang_count2;//��2
	char m_total_gang_count;
	bool m_is_quan_dai_yao;//ȫ���ۣ��ɴ����ж�
	bool m_is_zi_mo;		//�Ƿ����������ʾ����
	bool m_is_miao_shou_hui_chun;//�Ƿ����ֻش�
	bool m_is_hai_di_lao_yue;//�Ƿ񺣵�����
	bool m_is_gang_shang_kai_hua;//�Ƿ���Ͽ���
	bool m_is_qiang_gang_hu;//�Ƿ����ܺ�
	uint32_t m_flowers;//��������
	//uint32_t ComputerTotalFan();
	void CountData();//���������Ƶ�����
	void CountData2();//ֻ�����������Ƶ�����
	uint32_t data_count[16];//�����Ƶ�������������
	uint32_t data_count2[16];//�����Ƶ�������������
	uint32_t pai_in_hand_count;//�Լ����ϵ������������ж�ȫ���ˣ�������
	std::map<std::wstring,uint32_t> map_fans;
	std::vector<uint32_t> vec_all_cards;//��������ֵ
	std::vector<uint32_t> vec_hand_cards;//��������ֵ
	//88��
	//����ϲ
	bool IsDaSiXi();
	//����Ԫ
	bool IsDaSanYuan();
	//��һɫ
	bool IsLvYiSe();
	//��������
	bool IsJiuLianBaoDeng();
	//�ĸ�,����ʱ��¼һ����������
	bool IsSiGang();
	//���߶�
	bool IsLianQiDui();
	//ʮ����,�����齫�ﲻ�����
	bool IsShiSanYao();
	//64��
	//���۾�,�����齫�ﲻ�����
	bool IsQingYaoJiu();
	//С��ϲ
	bool IsXiaoSiXi();
	//С��Ԫ
	bool IsXiaoSanYuan();
	//��һɫ
	bool IsZiYiSe();
	//�İ��̣�����ʱ��¼һ���������ɣ������ĸ�
	bool IsSiAnKe();
	//һɫ˫����
	bool IsYiSeShuangLongHui();
	//48��
	//һɫ��ͬ˳
	bool IsYiSeSiTongShun();
	//һɫ�Ľڸ�
	bool IsYiSeSiJieGao();
	//32��
	//һɫ�Ĳ���
	bool IsYiSeSiBuGao();
	//����,����ʱ��¼һ���������ɣ������ĸ�
	bool IsSanGang();
	//���۾�
	bool IsHunYaoJiu();
	//24��
	//�߶�,��������Ƴ�ͻ��Ҳ���ܲ���ͻ������ж�ʱ���������
	bool IsQiDui();
	//���ǲ���,�����齫�ﲻ�����
	bool IsQiXinBuKao();
	//ȫ˫��,ò�ƶ����齫����ֲ����������
	bool IsQuanShuangKe();
	//��һɫ
	bool IsQingYiSe();
	//һɫ��ͬ˳
	bool IsYiSeSanTongShun();
	//һɫ���ڸ�,ò�Ƶ�ͬ�ڡ�һɫ��ͬ˳��
	bool IsYiSeSanJieGao();
	//ȫ��,ò�ƶ����齫����ֲ����������
	bool IsQuanDa();
	//ȫ��,ò�ƶ����齫����ֲ����������
	bool IsQuanZhong();
	//ȫС,ò�ƶ����齫����ֲ����������
	bool IsQuanXiao();
	//16��
	//����
	bool IsQingLong();
	//��ɫ˫����,�����齫�ﲻ�����
	bool IsSanSeShuangLongHui();
	//һɫ������
	bool IsYiSeSanBuGao();
	//ȫ����,�����齫�ﲻ�����
	bool IsQuanDaiWu();
	//��ͬ��,�����齫�ﲻ�����
	bool IsSanTongKe();
	//�����̣�����ʱ��¼һ���������ɣ������ĸ�
	bool IsSanAnKe();
	//12��
	//ȫ����,�����齫�ﲻ�����
	bool IsQuanBuKao();
	//�����,�����齫�ﲻ�����
	bool IsZuHeLong();
	//������
	bool IsDaYuWu();
	//С����
	bool IsXiaoYuWu();
	//�����
	bool IsSanFengKe();
	//8��
	//����,�����齫�ﲻ�����
	bool IsHuaLong();
	//�Ʋ���
	bool IsTuiBuDao();
	//��ɫ��ͬ˳,�����齫�ﲻ�����
	bool IsSanSeSanTongShun();
	//��ɫ���ڸ�,�����齫�ﲻ�����
	bool IsSanSeSanJieGao();
	//�޷���,���ż���
	bool IsWuFanHu();
	//���ֻش�
	bool IsMiaoShouHuiChun();
	//��������
	bool IsHaiDiLaoYue();
	//���Ͽ���
	bool IsGangShangKaiHua();
	//���ܺ�
	bool IsQiangGangHu();
	//6��
	//������
	bool IsPengPengHu();
	//��һɫ,�����齫��Զ�ǻ�һɫ
	bool IsHunYiSe();
	//��ɫ�����ߣ������齫�ﲻ�����
	bool IsSanSeSanBuGao();
	//�����룬�����齫�ﲻ�����
	bool IsWuMenQi();
	//ȫ����
	bool IsQuanQiuRen();
	//˫����
	bool IsShuangAnGang();
	//˫����
	bool IsShuangJianKe();
	//4��
	//ȫ����,�ɴ����ж�
	bool IsQuanDaiYao();
	//������
	bool IsBuQiuRen();
	//˫����
	bool IsShuangMingGang();
	//�����ţ������齫�ﲻ�����
	bool IsHuJueZhang();
	//2��
	//����
	bool IsJianKe();
	//Ȧ��̣������齫ò��û��
	bool IsQuanFengKe();
	//�ŷ�̣������齫ò��û��
	bool IsMenFengKe();
	//��ǰ��
	bool IsMenQianQing();
	//ƽ��,δ�ж�
	bool IsPingHu();
	//�Ĺ�һ
	bool IsSiGuiYi();
	//˫ͬ�̣������齫�ﲻ�����
	bool IsShuangTongKe();
	//˫����
	bool IsShuangAnKe();
	//����
	bool IsAnGang();
	//����
	bool IsDuanYao();
	//1��
	//һ���
	bool IsYiBanGao();
	//ϲ���
	bool IsXiXiangFeng();
	//��6
	bool IsLianLiu();
	//���ٸ�
	bool IsLaoShaoFu();
	//�۾ſ�
	bool IsYaoJiuKe();
	//����
	bool IsMingGang();
	//ȱһ�ţ������齫�ﲻ�����
	bool IsQueYiMen();
	//����
	bool IsWuZi();
	//����
	bool IsBianZhang(){return false;}
	//����
	bool IsKanZhang(){return false;}
	//������
	bool IsDanDiaoJiang();
	//����
	bool IsZiMo()
	{
		if (IsMiaoShouHuiChun() || IsGangShangKaiHua())
		{
			return false;
		}
		return m_is_zi_mo;
	}
};

//�º��Ʒ��ͼ�����

//�������Ͷ�Ӧpai_group��value_type
enum{   value_shunzi_chide = 1,	value_shunzi_weichi = 2,	value_kezi_pengde = 3,	value_kezi_weipeng = 4,
		value_angang = 5,		value_minggang1=6,			value_minggang2=7,		value_jiangzi = 8};//�������1�Ͱ��Ѿ���������


enum{	ID_FAN_DASIXI=0,		ID_FAN_DASANYUAN,		ID_FAN_LVYISE,				ID_FAN_JIULIANBAODENG,		ID_FAN_SIGANG,
		ID_FAN_LIANQIDUI,		ID_FAN_SHISANYAO,		ID_FAN_QINGYAOJIU,			ID_FAN_XIAOSIXI,			ID_FAN_XIAOSANYUAN,
		ID_FAN_ZIYISE,			ID_FAN_SIANKE,			ID_FAN_YISESHUANGLONGHUI,	ID_FAN_YISESITONGSHUN,		ID_FAN_YISESIJIEGAO,
		ID_FAN_YISESIBUGAO,		ID_FAN_SANGANG,			ID_FAN_HUNYAOJIU,			ID_FAN_QIDUI,				ID_FAN_QIXINGBUKAO,
		ID_FAN_QUANSHUANGKE,	ID_FAN_QINGYISE,		ID_FAN_YISESANTONGSHUN,		ID_FAN_YISESANJIEGAO,		ID_FAN_QUANDA,
		ID_FAN_QUANZHONG,		ID_FAN_QUANXIAO,		ID_FAN_QINGLONG,			ID_FAN_SANSESHUANGLONGHUI,	ID_FAN_YISESANBUGAO,
		ID_FAN_QUANDAIWU,		ID_FAN_SANTONGKE,		ID_FAN_SANANKE,				ID_FAN_QUANBUKAO,			ID_FAN_ZUHELONG,
		ID_FAN_DAYUWU,			ID_FAN_XIAOYUWU,		ID_FAN_SANFENGKE,			ID_FAN_HUALONG,				ID_FAN_TUIBUDAO,
		ID_FAN_SANSESANTONGSHUN,ID_FAN_SANSESANJIEGAO,	ID_FAN_WUFANHU,				ID_FAN_MIAOSHOUHUICHUN,		ID_FAN_HAIDILAOYUE,
		ID_FAN_GANGSHANGKAIHUA,	ID_FAN_QIANGGANGHU,		ID_FAN_PENGPENGHU,			ID_FAN_HUNYISE,				ID_FAN_SANSESANBUGAO,
		ID_FAN_WUMENQI,			ID_FAN_QUANQIUREN,		ID_FAN_SHUANGANGANG,		ID_FAN_SHUANGJIANKE,		ID_FAN_QUANDAIYAO,
		ID_FAN_BUQIUREN,		ID_FAN_SHUANGMINGGANG,	ID_FAN_HUJUEZHANG,			ID_FAN_JIANKE,				ID_FAN_QUANFENGKE,
		ID_FAN_MENFENGKE,		ID_FAN_MENQIANQING,		ID_FAN_PINGHU,				ID_FAN_SIGUIYI,				ID_FAN_SHUANGTONGKE,
		ID_FAN_SHUANGANKE,		ID_FAN_ANGANG,			ID_FAN_DUANYAO,				ID_FAN_YIBANGAO,			ID_FAN_XIXIANGFENG,
		ID_FAN_LIANLIU,			ID_FAN_LAOSHAOFU,		ID_FAN_YAOJIUKE,			ID_FAN_MINGGANG,			ID_FAN_QUEYIMEN,
		ID_FAN_WUZI,			ID_FAN_BIANZHANG,		ID_FAN_KANZHANG,			ID_FAN_DANDIAOJIANG,		ID_FAN_HUAPAI,
		ID_FAN_ZIMO};
struct pai_group//����ֵ����,˳�Ӵ����ţ����ӣ����ӣ����Ӵ�1��
{
	uint32_t value1;
	uint32_t value2;
	uint32_t value3;
	uint32_t value_type;//ֵ���ͣ�������ö��
	pai_group(){value1 = 0;value2 = 0;value3 = 0;value_type = 0;}
	void Reset(){value1 = 0;value2 = 0;value3 = 0;value_type = 0;}
};
class NewHuPaiFanShuComputer
{
public:
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

	void SetZiMo(bool bIsZiMo){m_bIsZiMo = bIsZiMo;}
	bool GetZiMo(){return m_bIsZiMo;}
	void SetData(pai_group a_group,int index);//���ڼ�����������
	void ResetAllData();//������������
	void CheckAllFan();//������з���
	void DeleteAllRepeat();//ɾȥ�ظ��ķ���
	int  CountFan();//���㷬
	void SetFlowers(int flowers){m_flowers = flowers;}
	int  GetFlowers(){return m_flowers;}
	bool GetSomeFan(int index){return m_bFan[index];}
	void SetMiaoShouHuiChun(bool bMiaoShouHuiChun){m_bFan[ID_FAN_MIAOSHOUHUICHUN] = bMiaoShouHuiChun;}
	void SetHaiDiLaoYue(bool bHaiDiLaoYue){m_bFan[ID_FAN_HAIDILAOYUE] = bHaiDiLaoYue;}
	void SetGangShangKaiHua(bool bGangShangKaiHua){m_bFan[ID_FAN_GANGSHANGKAIHUA] = bGangShangKaiHua;}
	void SetQiangGangHu(bool bQiangGangHu){m_bFan[ID_FAN_QIANGGANGHU] = bQiangGangHu;}
	pai_group m_5zupai[5];//5����
private:
	bool m_bIsZiMo;//�Ƿ�����
	
	bool m_bFan[81];//81�ַ��ͣ�������ö��
	int	 m_flowers;//����
	//88��
	//����ϲ
	void CheckDaSiXi();
	//����Ԫ
	void CheckDaSanYuan();
	//��һɫ
	void CheckLvYiSe();
	//��������
	void CheckJiuLianBaoDeng();
	//�ĸ�,����ʱ��¼һ����������
	void CheckSiGang();
	//���߶�
	void CheckLianQiDui();
	//ʮ����,�����齫�ﲻ�����
	void CheckShiSanYao();
	//64��
	//���۾�,�����齫�ﲻ�����
	void CheckQingYaoJiu();
	//С��ϲ
	void CheckXiaoSiXi();
	//С��Ԫ
	void CheckXiaoSanYuan();
	//��һɫ
	void CheckZiYiSe();
	//�İ��̣�����ʱ��¼һ���������ɣ������ĸ�
	void CheckSiAnKe();
	//һɫ˫����
	void CheckYiSeShuangLongHui();
	//48��
	//һɫ��ͬ˳
	void CheckYiSeSiTongShun();
	//һɫ�Ľڸ�
	void CheckYiSeSiJieGao();
	//32��
	//һɫ�Ĳ���
	void CheckYiSeSiBuGao();
	//����,����ʱ��¼һ���������ɣ������ĸ�
	void CheckSanGang();
	//���۾�
	void CheckHunYaoJiu();
	//24��
	//�߶�,��������Ƴ�ͻ��Ҳ���ܲ���ͻ������ж�ʱ���������
	void CheckQiDui();
	//���ǲ���,�����齫�ﲻ�����
	void CheckQiXinBuKao();
	//ȫ˫��,ò�ƶ����齫����ֲ����������
	void CheckQuanShuangKe();
	//��һɫ
	void CheckQingYiSe();
	//һɫ��ͬ˳
	void CheckYiSeSanTongShun();
	//һɫ���ڸ�,ò�Ƶ�ͬ�ڡ�һɫ��ͬ˳��
	void CheckYiSeSanJieGao();
	//ȫ��,ò�ƶ����齫����ֲ����������
	void CheckQuanDa();
	//ȫ��,ò�ƶ����齫����ֲ����������
	void CheckQuanZhong();
	//ȫС,ò�ƶ����齫����ֲ����������
	void CheckQuanXiao();
	//16��
	//����
	void CheckQingLong();
	//��ɫ˫����,�����齫�ﲻ�����
	void CheckSanSeShuangLongHui();
	//һɫ������
	void CheckYiSeSanBuGao();
	//ȫ����,�����齫�ﲻ�����
	void CheckQuanDaiWu();
	//��ͬ��,�����齫�ﲻ�����
	void CheckSanTongKe();
	//�����̣�����ʱ��¼һ���������ɣ������ĸ�
	void CheckSanAnKe();
	//12��
	//ȫ����,�����齫�ﲻ�����
	void CheckQuanBuKao();
	//�����,�����齫�ﲻ�����
	void CheckZuHeLong();
	//������
	void CheckDaYuWu();
	//С����
	void CheckXiaoYuWu();
	//�����
	void CheckSanFengKe();
	//8��
	//����,�����齫�ﲻ�����
	void CheckHuaLong();
	//�Ʋ���
	void CheckTuiBuDao();
	//��ɫ��ͬ˳,�����齫�ﲻ�����
	void CheckSanSeSanTongShun();
	//��ɫ���ڸ�,�����齫�ﲻ�����
	void CheckSanSeSanJieGao();
	//�޷���,���ż���
	void CheckWuFanHu();
	//���ֻش�
	void CheckMiaoShouHuiChun();
	//��������
	void CheckHaiDiLaoYue();
	//���Ͽ���
	void CheckGangShangKaiHua();
	//���ܺ�
	void CheckQiangGangHu();
	//6��
	//������
	void CheckPengPengHu();
	//��һɫ,�����齫��Զ�ǻ�һɫ
	void CheckHunYiSe();
	//��ɫ�����ߣ������齫�ﲻ�����
	void CheckSanSeSanBuGao();
	//�����룬�����齫�ﲻ�����
	void CheckWuMenQi();
	//ȫ����
	void CheckQuanQiuRen();
	//˫����
	void CheckShuangAnGang();
	//˫����
	void CheckShuangJianKe();
	//4��
	//ȫ����,�ɴ����ж�
	void CheckQuanDaiYao();
	//������
	void CheckBuQiuRen();
	//˫����
	void CheckShuangMingGang();
	//�����ţ������齫�ﲻ�����
	void CheckHuJueZhang();
	//2��
	//����
	void CheckJianKe();
	//Ȧ��̣������齫ò��û��
	void CheckQuanFengKe();
	//�ŷ�̣������齫ò��û��
	void CheckMenFengKe();
	//��ǰ��
	void CheckMenQianQing();
	//ƽ��,δ�ж�
	void CheckPingHu();
	//�Ĺ�һ
	void CheckSiGuiYi();
	//˫ͬ�̣������齫�ﲻ�����
	void CheckShuangTongKe();
	//˫����
	void CheckShuangAnKe();
	//����
	void CheckAnGang();
	//����
	void CheckDuanYao();
	//1��
	//һ���
	void CheckYiBanGao();
	//ϲ���
	void CheckXiXiangFeng();
	//��6
	void CheckLianLiu();
	//���ٸ�
	void CheckLaoShaoFu();
	//�۾ſ�
	void CheckYaoJiuKe();
	//����
	void CheckMingGang();
	//ȱһ�ţ������齫�ﲻ�����
	void CheckQueYiMen();
	//����
	void CheckWuZi();
	//����
	void CheckBianZhang();
	//����
	void CheckKanZhang();
	//������
	void CheckDanDiaoJiang();
	//����
	void CheckHuaPai();
	//����
	void CheckZiMo();
};
//�߶�ר��
class NewHuPaiFanShuComputer2
{
public:
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
	void SetZiMo(bool bIsZiMo){m_bIsZiMo = bIsZiMo;}
	bool GetZiMo(){return m_bIsZiMo;}
	void SetData(pai_group a_group,int index);//���ڼ�����������
	void ResetAllData();//������������
	void CheckAllFan();//������з���
	void DeleteAllRepeat();//ɾȥ�ظ��ķ���
	int  CountFan();//���㷬
	void SetFlowers(int flowers){m_flowers = flowers;}
	int  GetFlowers(){return m_flowers;}
	bool GetSomeFan(int index){return m_bFan[index];}
	void SetMiaoShouHuiChun(bool bMiaoShouHuiChun){m_bFan[ID_FAN_MIAOSHOUHUICHUN] = bMiaoShouHuiChun;}
	void SetHaiDiLaoYue(bool bHaiDiLaoYue){m_bFan[ID_FAN_HAIDILAOYUE] = bHaiDiLaoYue;}
	void SetGangShangKaiHua(bool bGangShangKaiHua){m_bFan[ID_FAN_GANGSHANGKAIHUA] = bGangShangKaiHua;}
	void SetQiangGangHu(bool bQiangGangHu){m_bFan[ID_FAN_QIANGGANGHU] = bQiangGangHu;}
	pai_group m_7zupai[7];//7����
private:
	bool m_bIsZiMo;//�Ƿ�����
	
	bool m_bFan[81];//81�ַ��ͣ�������ö��
	int	 m_flowers;//����

	//���߶�
	void CheckLianQiDui();
	//�߶�
	void CheckQiDui();
	void CheckLvYiSe();
	void CheckZiYiSe();
	void CheckQingYiSe();
	void CheckDaYuWu();
	void CheckXiaoYuWu();
	void CheckTuiBuDao();
	void CheckHunYiSe();
	void CheckQuanDaiYao();
	void CheckBuQiuRen();
	void CheckMenQianQing();
	void CheckSiGuiYi();
	void CheckDuanYao();
	void CheckWuZi();
	void CheckHuaPai();
	void CheckZiMo();
};


