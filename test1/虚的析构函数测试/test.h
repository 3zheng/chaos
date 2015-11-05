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
	//virtual ~Father();	//只要Grandfather最开始的基类的析构函数设成了虚函数，delete Son的时候也会调用~Father()，无论~Father()有没有被声明为虚函数
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

