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

// 牌ID，顺序为1梭第一张，2梭第一张，。。。，1梭第二张，2梭第二张，。。。，9梭第四张，东，南，西，北，中，发，白，春，夏，秋，冬，梅，兰，竹，菊
enum CardId {			id_unknown=0,		bamboo_1A=1,		bamboo_2A=2,		bamboo_3A=3,	bamboo_4A=4,		bamboo_5A=5,		bamboo_6A=6,		bamboo_7A=7,
	bamboo_8A=8,		bamboo_9A=9,		east_wind_A=10,		south_wind_A=11,	west_wind_A=12, north_wind_A=13,	red_dragon_A=14,	green_dragon_A=15,	white_dragon_A=16,
	bamboo_1B=17,		bamboo_2B=18,		bamboo_3B=19,		bamboo_4B=20,		bamboo_5B=21,	bamboo_6B=22,		bamboo_7B=23,
	bamboo_8B=24,		bamboo_9B=25,		east_wind_B=26,		south_wind_B=27,	west_wind_B=28, north_wind_B=29,	red_dragon_B=30,	green_dragon_B=31,	white_dragon_B=32,
	bamboo_1C=33,		bamboo_2C=34,		bamboo_3C=35,		bamboo_4C=36,		bamboo_5C=37,	bamboo_6C=38,		bamboo_7C=39, 
	bamboo_8C=40,		bamboo_9C=41,		east_wind_C=42,		south_wind_C=43,	west_wind_C=44,	north_wind_C=45,	red_dragon_C=46,	green_dragon_C=47,	white_dragon_C=48,
	bamboo_1D=49,		bamboo_2D=50,		bamboo_3D=51,		bamboo_4D=52,		bamboo_5D=53,	bamboo_6D=54,		bamboo_7D=55,
	bamboo_8D=56,		bamboo_9D=57,		east_wind_D=58,		south_wind_D=59,	west_wind_D=60, north_wind_D=61,	red_dragon_D=62,	green_dragon_D=63,	white_dragon_D=64,
	flower_spring=65,	flower_summer=66,	flower_autumn=67,	flower_winter=68,	flower_plum=69, flower_orchid=70,	flower_bamboo=71,	flower_chrysanthemum=72};
//忽略种类后的值，如4个1梭为相同的value_bamboo_1
enum CardValue{value_unknown=0, value_bamboo_1=1, value_bamboo_2=2, value_bamboo_3=3, value_bamboo_4=4, value_bamboo_5=5, value_bamboo_6=6,
	value_bamboo_7=7, value_bamboo_8=8, value_bamboo_9=9, value_east_wind=10, value_south_wind=11, value_west_wind=12, value_north_wind=13,
	value_red_dragon=14, value_green_dragon=15, value_white_dragon=16,value_flower=17,value_blank=18};

enum CardStatus{status_sleep = 0,		status_in_hand_normal = 1,		status_in_hand_select = 2,		status_out_normal = 3,		status_chew_self = 4,		status_chew_oppisite = 5,
	status_pong_self = 6,	status_pong_oppisite = 7,		status_kong_self = 8,			status_kong_oppisite = 9,	status_win = 10,status_in_hand_reverse = 11};


//麻将单张牌属性
class PaiKind
{
public:
	uint32_t u32RealCard;//真实牌号，即card_id中的值
	uint32_t u32ValueCard;//真实值，即card_value中的值
	uint32_t u32Status;//状态值，=0未抓，即在桌子中间；=1在玩家手中的牌（未选中平放），=2在玩家手中的牌（选中树起，将要打出状态）
	//=3打出的牌，在桌子上；=4吃牌（自己的）；=5吃牌（对家的）；=6碰牌（自己）；=7碰牌（对家的）；=8杠牌(自己）
	//=9杠牌（对家的）=10全倒，胡牌了
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
	emJudgeAnJianJingLing,			//按键精灵
	emJudgeAllAuto,					//全程托管
	emJudgeOther
};

enum AutoType
{
	emAutoNone,				//未托管
	emActiveAuto,			//主动托管(玩家自主托管)
	emPassiveAuto			//被动托管(服务端超时托管)
};

enum GameState
{
	FAPAI = 1,	//发牌阶段
	//BUHUA = 2,	//补花阶段
	CHUPAI = 3,	//出牌阶段
	GAMEEND = 4,	//游戏结束，显示分数结算
	ROUNDEND = 5,	//一轮结束
};

//固定的牌组
enum FixedType
{
	//值与twomajong.proto的ACTION保持一致
	UNKNOWN = 0,
	CHI = 1,
	PENG = 2,
	GANG = 3,
};

//吃碰杠以后固定的牌
struct FixedCard
{
	FixedType type = FixedType::UNKNOWN;	//牌组类型
	CardValue card_group[4];	//牌组值

	FixedCard()
	{
		for (int i = 0; i < 4; i++)
		{
			card_group[i] = CardValue::value_unknown;
		}
	}
};
//吃牌表的数据单元结构
//规范：吃：pai1,pai2记录准备吃的牌，pai3记录最后出的被吃牌
//		碰：pai1,pai2记录准备碰的牌，pai3记录最后出的被碰牌
//		暗杠：pai1,pai2,pai3记录准备暗杠的牌，pai4记录最后出的被杠牌
//		明杠1：四张记录明杠1的牌
//		明杠2：只记录pai1为要杠的牌
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
	emAutoNone,				//未托管
	emActiveAuto,			//主动托管(玩家自主托管)
	emPassiveAuto			//被动托管(服务端超时托管)
};

//玩家数据结构
struct PlayerData
{
	enum PlayerStep
	{
		//每次轮到一个玩家操作时分为两个阶段，抓牌阶段是去牌河补充手牌或者吃碰杠的操作，出牌阶段是吃碰杠后出一张牌
		GETSETP = 1,	//抓牌阶段
		OUTSETP = 2,	//出牌阶段
	};
	uint32_t seat_id = 0;
	uint64_t user_id = 0;

	AutoType auto_type;
	PlayerStep step;
	//手牌，以card_value为下标的手牌 [0]空缺不具含义 不包括花牌，因为花牌无法参与胡听判断
	//比如手牌为1个三条，2个五条，三个白板，那么hand_pai[value_bamboo_1] = 1,hand_pai[value_bamboo_5] = 2,hand_pai[value_white_dragon] = 3
	//用于快速判断是否胡听
	uint32_t hand_pai[17];
	//可用手牌，以card_id为下标的手牌，[0]unknown不用 假如手里有个发财A号，那么hand_card_id[white_dragon_A] = true; 一个哈希表数据结构用于快速校验手牌，如果吃碰杠后也会被置为false
	bool hand_card_id[73];
	//已固定的牌组，就是已经吃碰杠了的牌，不能再和其他手牌自由组合了
	vector<FixedCard> fixed_card;
	//没有明牌的手牌数量，明牌指吃碰杠后的牌
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
//胡牌番数计算器
class MjHuPaiFanShuComputer
{
public:
	void SetAllData(std::vector<uint32_t> all_cards){vec_all_cards = all_cards;}
	void SetHandData(std::vector<uint32_t> hand_cards){vec_hand_cards = hand_cards;}
	char m_an_gang_count;//原暗杠数，只需要在判断番型的地方改成明1即可
	char m_ming_gang_count1;//明1,原明杠1，只需要在判断番型的地方改成暗杠即可
	char m_ming_gang_count2;//明2
	char m_total_gang_count;
	bool m_is_quan_dai_yao;//全带幺，由打牌判断
	bool m_is_zi_mo;		//是否自摸，否表示点炮
	bool m_is_miao_shou_hui_chun;//是否妙手回春
	bool m_is_hai_di_lao_yue;//是否海底捞月
	bool m_is_gang_shang_kai_hua;//是否杠上开花
	bool m_is_qiang_gang_hu;//是否抢杠胡
	uint32_t m_flowers;//花牌数量
	//uint32_t ComputerTotalFan();
	void CountData();//计算所有牌的数量
	void CountData2();//只计算在手上牌的数量
	uint32_t data_count[16];//所有牌的数量保存在这
	uint32_t data_count2[16];//手上牌的数量保存在这
	uint32_t pai_in_hand_count;//自己手上的牌数，用于判断全求人，不求人
	std::map<std::wstring,uint32_t> map_fans;
	std::vector<uint32_t> vec_all_cards;//所有牌真值
	std::vector<uint32_t> vec_hand_cards;//手上牌真值
	//88番
	//大四喜
	bool IsDaSiXi();
	//大三元
	bool IsDaSanYuan();
	//绿一色
	bool IsLvYiSe();
	//九莲宝灯
	bool IsJiuLianBaoDeng();
	//四杠,杠牌时记录一下数量即可
	bool IsSiGang();
	//连七对
	bool IsLianQiDui();
	//十三幺,二人麻将里不会出现
	bool IsShiSanYao();
	//64番
	//清幺九,二人麻将里不会出现
	bool IsQingYaoJiu();
	//小四喜
	bool IsXiaoSiXi();
	//小三元
	bool IsXiaoSanYuan();
	//字一色
	bool IsZiYiSe();
	//四暗刻，杠牌时记录一下数量即可，类似四杠
	bool IsSiAnKe();
	//一色双龙会
	bool IsYiSeShuangLongHui();
	//48番
	//一色四同顺
	bool IsYiSeSiTongShun();
	//一色四节高
	bool IsYiSeSiJieGao();
	//32番
	//一色四步高
	bool IsYiSeSiBuGao();
	//三杠,杠牌时记录一下数量即可，类似四杠
	bool IsSanGang();
	//混幺九
	bool IsHunYaoJiu();
	//24番
	//七对,可能与胡牌冲突，也可能不冲突，因此判断时需调用两次
	bool IsQiDui();
	//七星不靠,二人麻将里不会出现
	bool IsQiXinBuKao();
	//全双刻,貌似二人麻将里出现不了这种情况
	bool IsQuanShuangKe();
	//清一色
	bool IsQingYiSe();
	//一色三同顺
	bool IsYiSeSanTongShun();
	//一色三节高,貌似等同于“一色三同顺”
	bool IsYiSeSanJieGao();
	//全大,貌似二人麻将里出现不了这种情况
	bool IsQuanDa();
	//全中,貌似二人麻将里出现不了这种情况
	bool IsQuanZhong();
	//全小,貌似二人麻将里出现不了这种情况
	bool IsQuanXiao();
	//16番
	//清龙
	bool IsQingLong();
	//三色双龙会,二人麻将里不会出现
	bool IsSanSeShuangLongHui();
	//一色三步高
	bool IsYiSeSanBuGao();
	//全带五,二人麻将里不会出现
	bool IsQuanDaiWu();
	//三同刻,二人麻将里不会出现
	bool IsSanTongKe();
	//三暗刻，杠牌时记录一下数量即可，类似四杠
	bool IsSanAnKe();
	//12番
	//全不靠,二人麻将里不会出现
	bool IsQuanBuKao();
	//组合龙,二人麻将里不会出现
	bool IsZuHeLong();
	//大于五
	bool IsDaYuWu();
	//小于五
	bool IsXiaoYuWu();
	//三风刻
	bool IsSanFengKe();
	//8番
	//花龙,二人麻将里不会出现
	bool IsHuaLong();
	//推不倒
	bool IsTuiBuDao();
	//三色三同顺,二人麻将里不会出现
	bool IsSanSeSanTongShun();
	//三色三节高,二人麻将里不会出现
	bool IsSanSeSanJieGao();
	//无番胡,最后才计算
	bool IsWuFanHu();
	//妙手回春
	bool IsMiaoShouHuiChun();
	//海底捞月
	bool IsHaiDiLaoYue();
	//杠上开花
	bool IsGangShangKaiHua();
	//抢杠胡
	bool IsQiangGangHu();
	//6番
	//碰碰胡
	bool IsPengPengHu();
	//混一色,二人麻将永远是混一色
	bool IsHunYiSe();
	//三色三步高，二人麻将里不会出现
	bool IsSanSeSanBuGao();
	//五门齐，二人麻将里不会出现
	bool IsWuMenQi();
	//全求人
	bool IsQuanQiuRen();
	//双暗杠
	bool IsShuangAnGang();
	//双箭刻
	bool IsShuangJianKe();
	//4番
	//全带幺,由打牌判断
	bool IsQuanDaiYao();
	//不求人
	bool IsBuQiuRen();
	//双明杠
	bool IsShuangMingGang();
	//胡绝张，二人麻将里不会出现
	bool IsHuJueZhang();
	//2番
	//箭刻
	bool IsJianKe();
	//圈风刻，二人麻将貌似没有
	bool IsQuanFengKe();
	//门风刻，二人麻将貌似没有
	bool IsMenFengKe();
	//门前清
	bool IsMenQianQing();
	//平胡,未判断
	bool IsPingHu();
	//四归一
	bool IsSiGuiYi();
	//双同刻，二人麻将里不会出现
	bool IsShuangTongKe();
	//双暗刻
	bool IsShuangAnKe();
	//暗杠
	bool IsAnGang();
	//断幺
	bool IsDuanYao();
	//1番
	//一般高
	bool IsYiBanGao();
	//喜相逢
	bool IsXiXiangFeng();
	//连6
	bool IsLianLiu();
	//老少副
	bool IsLaoShaoFu();
	//幺九刻
	bool IsYaoJiuKe();
	//明杠
	bool IsMingGang();
	//缺一门，二人麻将里不会出现
	bool IsQueYiMen();
	//无字
	bool IsWuZi();
	//边张
	bool IsBianZhang(){return false;}
	//坎张
	bool IsKanZhang(){return false;}
	//单钓将
	bool IsDanDiaoJiang();
	//自摸
	bool IsZiMo()
	{
		if (IsMiaoShouHuiChun() || IsGangShangKaiHua())
		{
			return false;
		}
		return m_is_zi_mo;
	}
};

//新胡牌番型计算器

//牌组类型对应pai_group的value_type
enum{   value_shunzi_chide = 1,	value_shunzi_weichi = 2,	value_kezi_pengde = 3,	value_kezi_weipeng = 4,
		value_angang = 5,		value_minggang1=6,			value_minggang2=7,		value_jiangzi = 8};//这里的明1和暗已经纠正过来


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
struct pai_group//存真值好了,顺子存三张，刻子，杠子，将子存1张
{
	uint32_t value1;
	uint32_t value2;
	uint32_t value3;
	uint32_t value_type;//值类型，见上面枚举
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
	void SetData(pai_group a_group,int index);//给第几组数据设置
	void ResetAllData();//重置所有数据
	void CheckAllFan();//检测所有番型
	void DeleteAllRepeat();//删去重复的番型
	int  CountFan();//计算番
	void SetFlowers(int flowers){m_flowers = flowers;}
	int  GetFlowers(){return m_flowers;}
	bool GetSomeFan(int index){return m_bFan[index];}
	void SetMiaoShouHuiChun(bool bMiaoShouHuiChun){m_bFan[ID_FAN_MIAOSHOUHUICHUN] = bMiaoShouHuiChun;}
	void SetHaiDiLaoYue(bool bHaiDiLaoYue){m_bFan[ID_FAN_HAIDILAOYUE] = bHaiDiLaoYue;}
	void SetGangShangKaiHua(bool bGangShangKaiHua){m_bFan[ID_FAN_GANGSHANGKAIHUA] = bGangShangKaiHua;}
	void SetQiangGangHu(bool bQiangGangHu){m_bFan[ID_FAN_QIANGGANGHU] = bQiangGangHu;}
	pai_group m_5zupai[5];//5组牌
private:
	bool m_bIsZiMo;//是否自摸
	
	bool m_bFan[81];//81种番型，索引见枚举
	int	 m_flowers;//花数
	//88番
	//大四喜
	void CheckDaSiXi();
	//大三元
	void CheckDaSanYuan();
	//绿一色
	void CheckLvYiSe();
	//九莲宝灯
	void CheckJiuLianBaoDeng();
	//四杠,杠牌时记录一下数量即可
	void CheckSiGang();
	//连七对
	void CheckLianQiDui();
	//十三幺,二人麻将里不会出现
	void CheckShiSanYao();
	//64番
	//清幺九,二人麻将里不会出现
	void CheckQingYaoJiu();
	//小四喜
	void CheckXiaoSiXi();
	//小三元
	void CheckXiaoSanYuan();
	//字一色
	void CheckZiYiSe();
	//四暗刻，杠牌时记录一下数量即可，类似四杠
	void CheckSiAnKe();
	//一色双龙会
	void CheckYiSeShuangLongHui();
	//48番
	//一色四同顺
	void CheckYiSeSiTongShun();
	//一色四节高
	void CheckYiSeSiJieGao();
	//32番
	//一色四步高
	void CheckYiSeSiBuGao();
	//三杠,杠牌时记录一下数量即可，类似四杠
	void CheckSanGang();
	//混幺九
	void CheckHunYaoJiu();
	//24番
	//七对,可能与胡牌冲突，也可能不冲突，因此判断时需调用两次
	void CheckQiDui();
	//七星不靠,二人麻将里不会出现
	void CheckQiXinBuKao();
	//全双刻,貌似二人麻将里出现不了这种情况
	void CheckQuanShuangKe();
	//清一色
	void CheckQingYiSe();
	//一色三同顺
	void CheckYiSeSanTongShun();
	//一色三节高,貌似等同于“一色三同顺”
	void CheckYiSeSanJieGao();
	//全大,貌似二人麻将里出现不了这种情况
	void CheckQuanDa();
	//全中,貌似二人麻将里出现不了这种情况
	void CheckQuanZhong();
	//全小,貌似二人麻将里出现不了这种情况
	void CheckQuanXiao();
	//16番
	//清龙
	void CheckQingLong();
	//三色双龙会,二人麻将里不会出现
	void CheckSanSeShuangLongHui();
	//一色三步高
	void CheckYiSeSanBuGao();
	//全带五,二人麻将里不会出现
	void CheckQuanDaiWu();
	//三同刻,二人麻将里不会出现
	void CheckSanTongKe();
	//三暗刻，杠牌时记录一下数量即可，类似四杠
	void CheckSanAnKe();
	//12番
	//全不靠,二人麻将里不会出现
	void CheckQuanBuKao();
	//组合龙,二人麻将里不会出现
	void CheckZuHeLong();
	//大于五
	void CheckDaYuWu();
	//小于五
	void CheckXiaoYuWu();
	//三风刻
	void CheckSanFengKe();
	//8番
	//花龙,二人麻将里不会出现
	void CheckHuaLong();
	//推不倒
	void CheckTuiBuDao();
	//三色三同顺,二人麻将里不会出现
	void CheckSanSeSanTongShun();
	//三色三节高,二人麻将里不会出现
	void CheckSanSeSanJieGao();
	//无番胡,最后才计算
	void CheckWuFanHu();
	//妙手回春
	void CheckMiaoShouHuiChun();
	//海底捞月
	void CheckHaiDiLaoYue();
	//杠上开花
	void CheckGangShangKaiHua();
	//抢杠胡
	void CheckQiangGangHu();
	//6番
	//碰碰胡
	void CheckPengPengHu();
	//混一色,二人麻将永远是混一色
	void CheckHunYiSe();
	//三色三步高，二人麻将里不会出现
	void CheckSanSeSanBuGao();
	//五门齐，二人麻将里不会出现
	void CheckWuMenQi();
	//全求人
	void CheckQuanQiuRen();
	//双暗杠
	void CheckShuangAnGang();
	//双箭刻
	void CheckShuangJianKe();
	//4番
	//全带幺,由打牌判断
	void CheckQuanDaiYao();
	//不求人
	void CheckBuQiuRen();
	//双明杠
	void CheckShuangMingGang();
	//胡绝张，二人麻将里不会出现
	void CheckHuJueZhang();
	//2番
	//箭刻
	void CheckJianKe();
	//圈风刻，二人麻将貌似没有
	void CheckQuanFengKe();
	//门风刻，二人麻将貌似没有
	void CheckMenFengKe();
	//门前清
	void CheckMenQianQing();
	//平胡,未判断
	void CheckPingHu();
	//四归一
	void CheckSiGuiYi();
	//双同刻，二人麻将里不会出现
	void CheckShuangTongKe();
	//双暗刻
	void CheckShuangAnKe();
	//暗杠
	void CheckAnGang();
	//断幺
	void CheckDuanYao();
	//1番
	//一般高
	void CheckYiBanGao();
	//喜相逢
	void CheckXiXiangFeng();
	//连6
	void CheckLianLiu();
	//老少副
	void CheckLaoShaoFu();
	//幺九刻
	void CheckYaoJiuKe();
	//明杠
	void CheckMingGang();
	//缺一门，二人麻将里不会出现
	void CheckQueYiMen();
	//无字
	void CheckWuZi();
	//边张
	void CheckBianZhang();
	//坎张
	void CheckKanZhang();
	//单钓将
	void CheckDanDiaoJiang();
	//花牌
	void CheckHuaPai();
	//自摸
	void CheckZiMo();
};
//七对专用
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
	void SetData(pai_group a_group,int index);//给第几组数据设置
	void ResetAllData();//重置所有数据
	void CheckAllFan();//检测所有番型
	void DeleteAllRepeat();//删去重复的番型
	int  CountFan();//计算番
	void SetFlowers(int flowers){m_flowers = flowers;}
	int  GetFlowers(){return m_flowers;}
	bool GetSomeFan(int index){return m_bFan[index];}
	void SetMiaoShouHuiChun(bool bMiaoShouHuiChun){m_bFan[ID_FAN_MIAOSHOUHUICHUN] = bMiaoShouHuiChun;}
	void SetHaiDiLaoYue(bool bHaiDiLaoYue){m_bFan[ID_FAN_HAIDILAOYUE] = bHaiDiLaoYue;}
	void SetGangShangKaiHua(bool bGangShangKaiHua){m_bFan[ID_FAN_GANGSHANGKAIHUA] = bGangShangKaiHua;}
	void SetQiangGangHu(bool bQiangGangHu){m_bFan[ID_FAN_QIANGGANGHU] = bQiangGangHu;}
	pai_group m_7zupai[7];//7组牌
private:
	bool m_bIsZiMo;//是否自摸
	
	bool m_bFan[81];//81种番型，索引见枚举
	int	 m_flowers;//花数

	//连七对
	void CheckLianQiDui();
	//七对
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


