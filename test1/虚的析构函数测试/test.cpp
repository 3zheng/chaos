#include "test.h"

Grandfather::Grandfather()
{
	pGf = new char[20];
	strcpy(pGf, "i am grandfather");
}

Grandfather::~Grandfather()
{
	if (pGf != nullptr)
	{
		printf("%s,don't destruct me!\n", pGf);
		delete pGf;
		pGf = nullptr;
	}
}


Father::Father()
{
	pF = new char[30];
	strcpy(pF, "i am father");
}

Father::~Father()
{
	if (pF != nullptr)
	{
		printf("%s,don't destruct me!\n", pF);
		delete pF;
		pF = nullptr;
	}
}

Son::Son()
{
	pS = new char[30];
	strcpy(pS, "i am father");
}

Son::~Son()
{
	if (pS != nullptr)
	{
		printf("%s,don't destruct me!\n", pS);
		delete pS;
		pS = nullptr;
	}
}

void Son::Fun1()
{
	printf("my name is hanmeimei. what's your name?\n");
}

int main()
{
	Son *test_son = new Son;
	test_son->Fun1();
	delete test_son;
	return 0;
}
