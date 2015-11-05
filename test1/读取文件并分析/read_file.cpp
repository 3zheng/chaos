#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;

int main()
{
	FILE *fp1 = nullptr; 
	FILE *fp2 = nullptr;
	vector<string> vec_1, vec_2;
	fp1 = fopen("1.txt", "r");
	char buff[100] = "";
	while (!feof(fp1))
	{
		fgets(buff, 100, fp1);
		vec_1.push_back(buff);
	}
	fp2 = fopen("2.txt", "r");
	while (!feof(fp2))
	{
		fgets(buff, 100, fp2);
		vec_2.push_back(buff);
	}
	fclose(fp1);
	fclose(fp2);

	vector<string> vec_same;
	for (auto it_1 = vec_1.begin(); it_1 != vec_1.end(); it_1++)
	{
		for (auto it_2 = vec_2.begin(); it_2 != vec_2.end(); it_2++)
		{
			if (*it_1 == *it_2)
			{
				vec_same.push_back(*it_1);
				break;
			}
		}
	}

	fp1 = fopen("same.txt", "w");
	for (auto it_same = vec_same.begin(); it_same != vec_same.end(); it_same++)
	{
		for (auto it_1 = vec_1.begin(); it_1 != vec_1.end(); it_1++)
		{
			if (*it_1 == *it_same)
			{
				vec_1.erase(it_1);
				break;
			}
		}

		for (auto it_2 = vec_2.begin(); it_2 != vec_2.end(); it_2++)
		{
			if (*it_2 == *it_same)
			{
				vec_2.erase(it_2);
				break;
			}
		}

		
		fprintf(fp1, "%s", it_same->c_str());
	}
	fclose(fp1);
	
	fp1 = fopen("1_different.txt", "w");
	for (auto it_1 = vec_1.begin(); it_1 != vec_1.end(); it_1++)
	{
		fprintf(fp1, "%s", it_1->c_str());
	}
	fclose(fp1);



	return 0;
}
