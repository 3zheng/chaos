#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Grandfather
{
	char *pGf = nullptr;
public:
	Grandfather();

	virtual ~Grandfather();
};

class Father : public Grandfather
{
public:
	Father();
	//virtual ~Father();	//ֻҪGrandfather�ʼ�Ļ������������������麯����delete Son��ʱ��Ҳ�����~Father()������~Father()��û�б�����Ϊ�麯��
	~Father();

protected:
private:
	char *pF = nullptr;
};

class Son : public Father
{
public:
	Son();
	~Son();
	
	void Fun1();
private:
	char *pS = nullptr;
};

