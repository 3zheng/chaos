#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <string>
#include <vector>

using namespace std;

int GetProfileString(char *profile, const char *AppName, const char *KeyName, char *KeyVal);

/*文件格式为
[main]
ip=192.168.10.17
ip_2=192.168.5.88
port=10010
*/
namespace ccf{

	class RProgramConfigLoad
	{
	public:
		char m_items_head[100];	//对应的是文件名
	public:
		RProgramConfigLoad(char *file_name)
		{
			strcpy(m_items_head, file_name);
		}
	};

	class RConfigItemLong
	{
	public:
		long m_value;
		long m_default;

	public:
		void set(long v)
		{
			m_value = v;
		}
		long value() const
		{
			return m_value;
		}
		operator long() const
		{
			return m_value;
		}
		RConfigItemLong(char *file_name, const char * strSectionName, const char * keyName, long default_val = 0)
			: m_default(default_val)
			, m_value(default_val)
		{
			char ini_value[100] = "";
			GetProfileString(file_name, strSectionName, keyName, ini_value);
			if (strcmp(ini_value, "") != 0)
			{
				m_value = atoi(ini_value);	//ini_value不为空
			}
			
		}
	};

	class RConfigItemStringArr
	{
	public:
		int m_item_num;
		
		vector<string> m_arrs;
		
		RConfigItemStringArr(char *file_name, const char * strSectionName, const char * keyName, long	item_num)
			: m_item_num(item_num)
		{
			if (item_num > 0)
			{
				char final_key_name[100] = "";
				
				for (int i = 0; i<item_num; i++)
				{
					char ini_value[100] = "";
					sprintf(final_key_name, "%s_%02d", keyName, i);
					GetProfileString(file_name, strSectionName, final_key_name, ini_value);
					if (strcmp(ini_value, "") != 0)
					{
						m_arrs.push_back(ini_value);	//ini_value不为空
					}
					else
					{
						m_arrs.push_back("");
					}
				}
			}
		}

	public:
		size_t count() { return m_arrs.size(); }
		const char * operator[](size_t i)
		{
			if (m_arrs.size()>i)
			{
				return m_arrs[i].c_str();
			}
			return "";
		}
	};


	class RConfigItemString 
	{
	public:
		string m_value;
		string m_default;
	public:
		void set(const basic_string<char> & v)
		{
			m_value = v;
		}
		const char * c_str()
		{
			return m_value.c_str();
		}
		operator const char*() const
		{
			return m_value.c_str();
		}
		RConfigItemString(char *file_name, const char * strSectionName, const char * keyName, string default_val = "")
			: m_default(default_val)
			, m_value(default_val)
		{
			char ini_value[100] = "";
			GetProfileString(file_name, strSectionName, keyName, ini_value);
			if (strcmp(ini_value, "") != 0)
			{
				m_value = ini_value;	//ini_value不为空
			}
		}
		

	};
}