
#include "blowfish.h"
#include "encrypt_data.h"
#include <string>

using namespace std;

int main()
{
	string str_src = "abcdefghijklmnopq";
	string str_key = "key";
	vector<char> key;
	for (auto it = str_key.begin(); it != str_key.end(); it++)
	{
		key.push_back(*it);
	}

	vector<char> input;
	vector<char> output;

	Blowfish *tool = new Blowfish(key);	//������Կ
	for (auto it : str_src)
	{
		input.push_back(it);
	}
	output = tool->Encrypt(input);	//���ܺ��ִ�
	
	//����û��ֱ�Ӵ���string�ķ�����ֻ��vector<char>�ķ���
	
	input.clear();
	for (auto it = output.begin(); it != output.end(); it++)
	//��Ч��
	//for (auto it : output)
	{
		input.push_back(*it);
	}

	output.clear();
	output = tool->Decrypt(input);
	return 0;
}