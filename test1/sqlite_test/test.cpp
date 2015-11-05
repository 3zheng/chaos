#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
//创建handle和建表
sqlite3 *CreateSqlHandle()
{
	sqlite3 *db3 = nullptr;
	char filename[100] = "";
	sprintf(filename, "%lite");
	int ret = sqlite3_open(filename, &db3);
	if (ret != SQLITE_OK)
	{
		sqlite3_close(db3);
		return nullptr;
	}
	sqlite3_exec(db3, "PRAGMA encoding = \"UTF-8\"; ", 0, 0, 0);	//设置UTF8字符集
	sqlite3_exec(db3, "PRAGMA read_uncommitted=1 ; ", 0, 0, 0);	//设置允许读取还没有提交完成的数据（即可读加锁中的数据）

	char *create_sql = "create table if not exists round_data(start_day INTEGER, plan_id INTEGER , match_id INTEGER, ms_appid INTEGER, plan_name TEXT, game_kind INTEGER, start_point INTEGER, stage_index INTEGER, round_id TEXT, round_index INTEGER, record_data TEXT);";
	sqlite3_exec(db3, create_sql, 0, 0, 0);

	return db3;
}

//select表
void ReadData(sqlite3 *db3)
{
	char *select_sql = "select * from round_data";
	char **result = nullptr;
	char *error_msg = nullptr;
	int row = 0, column = 0;
	sqlite3_get_table(db3, select_sql, &result, &row, &column, &error_msg);
	for (int i = 0; i < row; i++)
	{
		result[i][0];	//start_day
		result[i][1];	//plan_id
		result[i][2];	//match_id
		result[i][3];	//ms_appid
		result[i][4];	//plan_name
		result[i][5];	//game_kind
		result[i][6];	//start_point
		result[i][7];	//stage_index
		result[i][8];	//round_id
		result[i][9];	//round_index
		result[i][10];	//record_data
	}

	sqlite3_free_table(result);	//释放内存
}

//insert表
void WriteData(sqlite3 *db3)
{
	char *error_msg = nullptr;
	//sqlite的sql语句长度限制是1000000即1M字节
	string insert_sql = "insert into round_data(start_day, plan_id, match_id, ms_appid, plan_name, game_kind, start_point, stage_index, round_id, round_index, record_data)"
		"values(";
	char buff[500] = "";
	int start_day =0, plan_id =0, ms_appid=0, game_kind=0, stage_index=0, round_index=0;
	long long match_id=0, start_point=0;
	string plan_name, round_id;
	sprintf(buff, "%d, %d, %lld, %d, \"%s\", %d, %lld, %d, \"%s\", %d",
		start_day, plan_id, match_id, ms_appid, plan_name.c_str(), game_kind, start_point, stage_index, round_id.c_str(), round_index);
	//record_data长度很大所以不放在buff处理，否则buff会越界
	string record_data;	//very big,超过10K
	insert_sql += buff;
	insert_sql += "\"";
	insert_sql += record_data;
	insert_sql += "\"";


	sqlite3_exec(db3, insert_sql.c_str(), 0, 0, &error_msg);
}

int main()
{
	sqlite3 *db3 = CreateSqlHandle();
	WriteData(db3);
	ReadData(db3);
}