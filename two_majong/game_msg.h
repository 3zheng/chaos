#pragma once
////////////////////////报文定义////////////////////////
#include <vector>

#include "base_itf.h"
#include "config.h"
using namespace std;

#define	MKD_DDZ			0x1006			//斗地主游戏报文大类定义
#define MKD_MAJONG2		0x1006
#define FIRST_GAME_PROTOCOL				1000
#define PRO_GAME_BEGIN					FIRST_GAME_PROTOCOL + 1		// 一局游戏开始
#define PRO_OPPISITE_LEFT_CARD			FIRST_GAME_PROTOCOL + 2		// 发送对家手上剩余牌
#define PRO_UPDATE_TABLE_UNGOT_CARDS	FIRST_GAME_PROTOCOL + 4		// 更新桌面未抓牌
#define PRO_SEND_CHEW_AND_SO_ON			FIRST_GAME_PROTOCOL + 6		// 发送吃碰杠胡听
#define PRO_CLICK_CHEW_AND_SO_ON_BTN	FIRST_GAME_PROTOCOL + 7		// 点击吃碰刚胡听放弃按钮
#define PRO_OUT_CARD_NOTIFY				FIRST_GAME_PROTOCOL + 8		// 出牌情况通知，包括吃，碰，杠，听
#define PRO_END_GAME					FIRST_GAME_PROTOCOL + 9		// 一局游戏结束
#define PRO_TURN_CURRENT_PLAYER			FIRST_GAME_PROTOCOL + 10	// 变换当前玩家
#define PRO_SEND_TING_NOTIFY			FIRST_GAME_PROTOCOL + 12	// 发送听通知
#define PRO_GAME_DATA_REQ				FIRST_GAME_PROTOCOL + 15	// 游戏数据同步请求
#define PRO_GAME_DATA_REPLY				FIRST_GAME_PROTOCOL + 16	// 游戏数据同步应答
#define PRO_ADD_FLOWER					FIRST_GAME_PROTOCOL + 17	// 加花
#define PRO_GROUP_SEND_PAI				FIRST_GAME_PROTOCOL + 18    // 群发牌
#define PRO_SINGLE_SEND_PAI				FIRST_GAME_PROTOCOL + 19    // 单发牌
#define PRO_BTN_SEND					FIRST_GAME_PROTOCOL + 20    // 按钮发送
#define PRO_SAME_WITH_SVR				FIRST_GAME_PROTOCOL + 21	// 纠正手牌
#define	PRO_EXPRESSION					FIRST_GAME_PROTOCOL + 13	// ·￠?í±í?é//??????o?￡???o?óD?ù+13?a??DòáD??3?à′
enum btn_id{
	btn_id_normal = 0,
	btn_id_chi = 1,
	btn_id_peng = 2,
	btn_id_an_gang = 3,
	btn_id_ming_gang_1 = 4,
	btn_id_ming_gang_2 = 5,
	btn_id_hu = 6,
	btn_id_ting = 7,
	btn_id_tuo_guan = 8,
	btn_id_qu_xiao_tuo_guan = 9,
	btn_id_fangqi = 10,
	btn_id_jiabei = 11};
//游戏开启
struct pro_game_begin_s : public CMD_base
{
	int			money_rate;			// 游戏币倍数
	int			score_rate;			// 积分倍数
	uint32_t	shaizi[4];			// 骰子
	int			svr_seat_id;		// 服务器座位id
	uint32_t	is_banker;			// 是否庄家：=1是，=0否
	bool FromReader( IMsgReader *r);
	void ToWriter( IMsgWriter *w);
};
//群发牌
struct pro_group_send_pai_s : public CMD_base
{
	int						seat_id;
	char					pais[13];
	bool FromReader( IMsgReader*  r);
	void ToWriter( IMsgWriter * w);
};
//单发牌
struct pro_single_send_pai_s : public CMD_base
{
	int						seat_id;
	char					pai;
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//花数
struct pro_add_flower_count : public CMD_base
{
	int						seat_id;
	char				total_flowers;
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//桌面更新
struct pro_update_table_ungot_cards_s : public CMD_base
{
	uint32_t				normal_count;	//正向计数器
	uint32_t				reverse_count;	//反向计数器
	uint32_t				kind;			//种类：=1群发牌，=2普通抓牌，=3逆向抓牌
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//吃碰杠胡听按钮发送
struct usual_btn_send : public CMD_base
{
	char btn_flag;//一共八位，用右边六位，从右边起，第0位：吃，第1位:碰，第二位：暗杠，第三位：明1，第四位：明2，第五位：胡，第六位：听
	char last_pai;//最后那张牌
	char special_fan_for_hu;//可胡时的特殊番型,从右往左：妙手回春，海底捞月，杠上开花，抢杠胡
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//出牌情况通知
struct pro_out_card_notify_s : public CMD_base
{
	int					seat_id;
	uint32_t			kind;//种类：见枚举
	uint32_t			pai[4];//一次性最多出4张,规定：暗杠，明杠1，明杠2，只传一个数值pai0，传一个真值
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//一局游戏结束,主要是用于番数的发送
struct pro_end_a_game_s : public CMD_base
{
	char				hu_na_zhi;//胡哪个
	int					seat_id1;//第一家（赢者的座位id，若是荒庄，则seatid1,seatid2两者皆为0）
	char				pai1[14];//第一家所有牌唯一值，暗先吃碰杠出的牌，再单牌的形式放置
	char				count1;//吃碰杠组数
	char				index1[4];//最多四个吃碰杠组，表示第几个是暗杠=1是，=2明1，=3明2，都是原始定义=0否（默认）
	uint32_t			beishu;//赢者倍数
	uint32_t			other_fan;//其他番：个位=1表示妙手回春，十位=1表示海底捞月，百位=1表示杠上开花，千位=1表示抢杠胡
	char				zimo_or_dianpao;//自摸=1点炮=2
	int					fan[3];//番型[0],[1]各记32个，从高到低，[0]的最右边那位记录大四喜，以此类推,[2]只用到右边17个位，因为一共81种番型
	int					total_fan;//总番数
	long long			win_lose_point;//胜负点数，即得分或扣分数，这里应该赋值正的，由赢输标记再判断正负
	void init_data();
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//对家剩余手中牌，用于一局结束后显示对家牌
struct pro_oppisite_left_cards : public CMD_base
{
	char				pai[14];
	pro_oppisite_left_cards(){memset(pai,0,sizeof(pai));}
	bool				FromReader( IMsgReader* r);
	void				ToWriter( IMsgWriter * w);
};
//当前玩家变化指示
struct pro_turn_current_player_s : public CMD_base
{
	int			current_player_seat_id;//当前玩家的座位id
	bool FromReader(IMsgReader *r);
	void ToWriter(IMsgWriter *w);
};
// 发送听通知,托通知
struct pro_ting_notify_s : public CMD_base
{
	int						seat_id;
	uint32_t				kind;//=0听通知，=1托通知,=2取消托
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
// 点击吃碰刚胡听放弃托管,以及普通牌
struct pro_click_btn_c : public CMD_base
{
	int						seat_id;
	char					kind;//种类：见枚举
	char					index;//若是单击普通牌，则表示出的牌的唯一值，若是吃，还需指出是编号几,从0开始，对应于服务器的吃列表，其他按钮就一种
	//若是放弃或加倍，这里给出是自摸还是点炮，=0自摸=1点炮
	bool FromReader( IMsgReader* r);
	void ToWriter(IMsgWriter *w);
};
//掉线重连
struct player_data
{
	char my_chi_peng_gang[20];//5个一组，每组前三个为吃碰杠牌，第四个只有杠才有用，第五个标记=0暗杠，=1明杠1，=2明杠2,牌还是用唯一值比较好
	char my_out_cards[20];//我的出牌
	char oppisite_chi_peng_gang[20];//对家吃碰杠
	char oppisite_out_cards[20];//对家的出牌
	char my_cards_group[14];//我的整组站牌//为0则没有
	char table_update[4];//桌面更新牌的四个数据
	char my_flowers_count;//我的花数
	char oppisite_card_count;//对家站牌数
	char oppisite_flower_count;//对家花数
	char is_tuo_guan;//是否托管=1是托管=2听
	void reset()
	{
		for (int i = 0; i < 14; i++)
		{
			my_cards_group[i] = 0;
		}
		for(int i = 0; i < 20; i++)
		{
			my_chi_peng_gang[i] = 0;
			my_out_cards[i] = 0;
			oppisite_chi_peng_gang[i] = 0;
			oppisite_out_cards[i] = 0;
		}
		my_flowers_count = 0;
		oppisite_card_count = 0;
		oppisite_flower_count = 0;
		for (int i = 0; i < 4; i++)
		{
			table_update[i] = 0;
		}
		is_tuo_guan = 0;
	}
};

struct pro_game_data_reply : public CMD_base
{
	int				state;				// 游戏状态，0－准备，1－叫分，2－出牌，3－压牌
	int				current_player;		// 轮到哪个玩家操作
	int				timeout;			// 下次操作超时时间
	int				banker;				// 庄家座位号
	int				multiple;			// 倍数
	player_data		plrdata;			// 玩家数据
	int				my_seat_id;			// 我的座位号
	bool FromReader( IMsgReader *r);
	void ToWriter( IMsgWriter *w);
};
struct pro_game_data_req : public CMD_base
{
	bool FromReader( IMsgReader *r);
	void ToWriter( IMsgWriter *w);
};
//纠正手牌
struct pro_same_with_svr : public CMD_base
{
	int						seat_id;	//座位id
	char					pais[14];	//手牌14张
	char					index;		//类型索引，=0普通打牌，=1吃碰杠
	bool FromReader( IMsgReader*  r);
	void ToWriter( IMsgWriter * w);
};

struct pro_expression : public CMD_base
{
	int			seatid;			// í??ò×ù??o?
	int			expressionid;	// ±í?éid

	bool FromReader( IMsgReader *r);
	void ToWriter( IMsgWriter *w);
};
//--------------------------------------------??D?éè??μ?--------------------------------------------------------------------------------
//2aê?·￠??charoíBYTE??òa?ú·??§?ú?±?ó?3?μêy?μê?ò??ùμ?

