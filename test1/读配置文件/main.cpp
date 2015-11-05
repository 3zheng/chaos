#include "read_profile.h"
#include <vector>

using namespace std;

class QConfig :public  ccf::RProgramConfigLoad
{
public:
	ccf::RConfigItemLong    my_pageid_;

	/*
	关于gate地址的配置
	[gate]
	address_00=g1.chensheng.net:10100
	address_01=60.191.221.180:10100
	*/
	ccf::RConfigItemStringArr gate_address_;
	ccf::RConfigItemLong      seconds_start_point_get_;
	ccf::RConfigItemLong      show_ui_;
	ccf::RConfigItemString     table_exe_name_;
	ccf::RConfigItemLong		time_disconn_;			//连接断开时间，默认15秒
	ccf::RConfigItemLong    cipher_enable_;
	ccf::RConfigItemLong    send_pulse_;
public:
	QConfig()
		:ccf::RProgramConfigLoad("gateclient.ini")
		, my_pageid_(m_items_head, "main", "pageid", 1)
		, gate_address_(m_items_head, "gate", "address", 32)
		, seconds_start_point_get_(m_items_head, "main", "开赛点获取间隔秒数", 30)
		, table_exe_name_(m_items_head, "main", "exename", "landmatch")
		, show_ui_(m_items_head, "ui", "show", 0)
		, time_disconn_(m_items_head, "main", "timedisconn", 25)
		, cipher_enable_(m_items_head, "main", "报文方式", 1)
		, send_pulse_(m_items_head, "main", "发送心跳", 1)
	{

	}

};

void main()
{
	vector<char*> ip;
	char port[16];

	char key_name[100] = "";
	for (int i = 1; i < 100; i++)	//01到99
	{
		char *alloc_ip = new char[50];
		memset(alloc_ip, '\0', 50);
		sprintf(key_name, "ip_%02d", i);
		GetProfileString("./cls.conf", "main", key_name, alloc_ip);
		if (strcmp("", alloc_ip) == 0)
		{
			delete alloc_ip;
		}
		else
		{
			ip.push_back(alloc_ip);
		}
	}
	
	GetProfileString("./cls.conf", "main", "port", port);
	printf("%s:%s\n", ip, port);

	QConfig cfg;
	printf("pageid=%d", cfg.my_pageid_);
	return;
}