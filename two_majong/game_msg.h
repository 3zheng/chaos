#pragma once
////////////////////////���Ķ���////////////////////////
#include <vector>

#include "base_itf.h"
#include "config.h"
using namespace std;

#define	MKD_DDZ			0x1006			//��������Ϸ���Ĵ��ඨ��
#define MKD_MAJONG2		0x1006
#define FIRST_GAME_PROTOCOL				1000
#define PRO_GAME_BEGIN					FIRST_GAME_PROTOCOL + 1		// һ����Ϸ��ʼ
#define PRO_OPPISITE_LEFT_CARD			FIRST_GAME_PROTOCOL + 2		// ���ͶԼ�����ʣ����
#define PRO_UPDATE_TABLE_UNGOT_CARDS	FIRST_GAME_PROTOCOL + 4		// ��������δץ��
#define PRO_SEND_CHEW_AND_SO_ON			FIRST_GAME_PROTOCOL + 6		// ���ͳ����ܺ���
#define PRO_CLICK_CHEW_AND_SO_ON_BTN	FIRST_GAME_PROTOCOL + 7		// ��������պ���������ť
#define PRO_OUT_CARD_NOTIFY				FIRST_GAME_PROTOCOL + 8		// �������֪ͨ�������ԣ������ܣ���
#define PRO_END_GAME					FIRST_GAME_PROTOCOL + 9		// һ����Ϸ����
#define PRO_TURN_CURRENT_PLAYER			FIRST_GAME_PROTOCOL + 10	// �任��ǰ���
#define PRO_SEND_TING_NOTIFY			FIRST_GAME_PROTOCOL + 12	// ������֪ͨ
#define PRO_GAME_DATA_REQ				FIRST_GAME_PROTOCOL + 15	// ��Ϸ����ͬ������
#define PRO_GAME_DATA_REPLY				FIRST_GAME_PROTOCOL + 16	// ��Ϸ����ͬ��Ӧ��
#define PRO_ADD_FLOWER					FIRST_GAME_PROTOCOL + 17	// �ӻ�
#define PRO_GROUP_SEND_PAI				FIRST_GAME_PROTOCOL + 18    // Ⱥ����
#define PRO_SINGLE_SEND_PAI				FIRST_GAME_PROTOCOL + 19    // ������
#define PRO_BTN_SEND					FIRST_GAME_PROTOCOL + 20    // ��ť����
#define PRO_SAME_WITH_SVR				FIRST_GAME_PROTOCOL + 21	// ��������
#define	PRO_EXPRESSION					FIRST_GAME_PROTOCOL + 13	// ����?������?��//??????o?��???o?��D?��+13?a??D����D??3?����
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
//��Ϸ����
struct pro_game_begin_s : public CMD_base
{
	int			money_rate;			// ��Ϸ�ұ���
	int			score_rate;			// ���ֱ���
	uint32_t	shaizi[4];			// ����
	int			svr_seat_id;		// ��������λid
	uint32_t	is_banker;			// �Ƿ�ׯ�ң�=1�ǣ�=0��
	bool FromReader( IMsgReader *r);
	void ToWriter( IMsgWriter *w);
};
//Ⱥ����
struct pro_group_send_pai_s : public CMD_base
{
	int						seat_id;
	char					pais[13];
	bool FromReader( IMsgReader*  r);
	void ToWriter( IMsgWriter * w);
};
//������
struct pro_single_send_pai_s : public CMD_base
{
	int						seat_id;
	char					pai;
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//����
struct pro_add_flower_count : public CMD_base
{
	int						seat_id;
	char				total_flowers;
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//�������
struct pro_update_table_ungot_cards_s : public CMD_base
{
	uint32_t				normal_count;	//���������
	uint32_t				reverse_count;	//���������
	uint32_t				kind;			//���ࣺ=1Ⱥ���ƣ�=2��ͨץ�ƣ�=3����ץ��
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//�����ܺ�����ť����
struct usual_btn_send : public CMD_base
{
	char btn_flag;//һ����λ�����ұ���λ�����ұ��𣬵�0λ���ԣ���1λ:�����ڶ�λ�����ܣ�����λ����1������λ����2������λ����������λ����
	char last_pai;//���������
	char special_fan_for_hu;//�ɺ�ʱ�����ⷬ��,�����������ֻش����������£����Ͽ��������ܺ�
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//�������֪ͨ
struct pro_out_card_notify_s : public CMD_base
{
	int					seat_id;
	uint32_t			kind;//���ࣺ��ö��
	uint32_t			pai[4];//һ��������4��,�涨�����ܣ�����1������2��ֻ��һ����ֵpai0����һ����ֵ
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//һ����Ϸ����,��Ҫ�����ڷ����ķ���
struct pro_end_a_game_s : public CMD_base
{
	char				hu_na_zhi;//���ĸ�
	int					seat_id1;//��һ�ң�Ӯ�ߵ���λid�����ǻ�ׯ����seatid1,seatid2���߽�Ϊ0��
	char				pai1[14];//��һ��������Ψһֵ�����ȳ����ܳ����ƣ��ٵ��Ƶ���ʽ����
	char				count1;//����������
	char				index1[4];//����ĸ��������飬��ʾ�ڼ����ǰ���=1�ǣ�=2��1��=3��2������ԭʼ����=0��Ĭ�ϣ�
	uint32_t			beishu;//Ӯ�߱���
	uint32_t			other_fan;//����������λ=1��ʾ���ֻش���ʮλ=1��ʾ�������£���λ=1��ʾ���Ͽ�����ǧλ=1��ʾ���ܺ�
	char				zimo_or_dianpao;//����=1����=2
	int					fan[3];//����[0],[1]����32�����Ӹߵ��ͣ�[0]�����ұ���λ��¼����ϲ���Դ�����,[2]ֻ�õ��ұ�17��λ����Ϊһ��81�ַ���
	int					total_fan;//�ܷ���
	long long			win_lose_point;//ʤ�����������÷ֻ�۷���������Ӧ�ø�ֵ���ģ���Ӯ�������ж�����
	void init_data();
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
//�Լ�ʣ�������ƣ�����һ�ֽ�������ʾ�Լ���
struct pro_oppisite_left_cards : public CMD_base
{
	char				pai[14];
	pro_oppisite_left_cards(){memset(pai,0,sizeof(pai));}
	bool				FromReader( IMsgReader* r);
	void				ToWriter( IMsgWriter * w);
};
//��ǰ��ұ仯ָʾ
struct pro_turn_current_player_s : public CMD_base
{
	int			current_player_seat_id;//��ǰ��ҵ���λid
	bool FromReader(IMsgReader *r);
	void ToWriter(IMsgWriter *w);
};
// ������֪ͨ,��֪ͨ
struct pro_ting_notify_s : public CMD_base
{
	int						seat_id;
	uint32_t				kind;//=0��֪ͨ��=1��֪ͨ,=2ȡ����
	bool FromReader( IMsgReader* r);
	void ToWriter( IMsgWriter * w);
};
// ��������պ��������й�,�Լ���ͨ��
struct pro_click_btn_c : public CMD_base
{
	int						seat_id;
	char					kind;//���ࣺ��ö��
	char					index;//���ǵ�����ͨ�ƣ����ʾ�����Ƶ�Ψһֵ�����ǳԣ�����ָ���Ǳ�ż�,��0��ʼ����Ӧ�ڷ������ĳ��б�������ť��һ��
	//���Ƿ�����ӱ�������������������ǵ��ڣ�=0����=1����
	bool FromReader( IMsgReader* r);
	void ToWriter(IMsgWriter *w);
};
//��������
struct player_data
{
	char my_chi_peng_gang[20];//5��һ�飬ÿ��ǰ����Ϊ�������ƣ����ĸ�ֻ�иܲ����ã���������=0���ܣ�=1����1��=2����2,�ƻ�����Ψһֵ�ȽϺ�
	char my_out_cards[20];//�ҵĳ���
	char oppisite_chi_peng_gang[20];//�Լҳ�����
	char oppisite_out_cards[20];//�Լҵĳ���
	char my_cards_group[14];//�ҵ�����վ��//Ϊ0��û��
	char table_update[4];//��������Ƶ��ĸ�����
	char my_flowers_count;//�ҵĻ���
	char oppisite_card_count;//�Լ�վ����
	char oppisite_flower_count;//�Լһ���
	char is_tuo_guan;//�Ƿ��й�=1���й�=2��
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
	int				state;				// ��Ϸ״̬��0��׼����1���з֣�2�����ƣ�3��ѹ��
	int				current_player;		// �ֵ��ĸ���Ҳ���
	int				timeout;			// �´β�����ʱʱ��
	int				banker;				// ׯ����λ��
	int				multiple;			// ����
	player_data		plrdata;			// �������
	int				my_seat_id;			// �ҵ���λ��
	bool FromReader( IMsgReader *r);
	void ToWriter( IMsgWriter *w);
};
struct pro_game_data_req : public CMD_base
{
	bool FromReader( IMsgReader *r);
	void ToWriter( IMsgWriter *w);
};
//��������
struct pro_same_with_svr : public CMD_base
{
	int						seat_id;	//��λid
	char					pais[14];	//����14��
	char					index;		//����������=0��ͨ���ƣ�=1������
	bool FromReader( IMsgReader*  r);
	void ToWriter( IMsgWriter * w);
};

struct pro_expression : public CMD_base
{
	int			seatid;			// ��??������??o?
	int			expressionid;	// ����?��id

	bool FromReader( IMsgReader *r);
	void ToWriter( IMsgWriter *w);
};
//--------------------------------------------??D?����??��?--------------------------------------------------------------------------------
//2a��?����??charo��BYTE??��a?����??��?��?��?��?3?�̨�y?�̨�?��??����?

