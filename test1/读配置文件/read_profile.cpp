
#include "read_profile.h"

#define KEYVALLEN 100

/*文件格式为
[main]
ip=192.168.10.17
ip_2=192.168.5.88
port=10010
*/
bool IsSpace(char input)
{
	return input == ' ';
}

/*   删除左边的空格   */
char * l_trim(char * szOutput, const char *szInput)
{
	assert(szInput != NULL);
	assert(szOutput != NULL);
	assert(szOutput != szInput);
	for (NULL; *szInput != '\0' && IsSpace(*szInput); ++szInput){
		;
	}
	return strcpy(szOutput, szInput);
}

/*   删除右边的空格   */
char *r_trim(char *szOutput, const char *szInput)
{
	char *p = NULL;
	assert(szInput != NULL);
	assert(szOutput != NULL);
	assert(szOutput != szInput);
	strcpy(szOutput, szInput);
	for (p = szOutput + strlen(szOutput) - 1; p >= szOutput && IsSpace(*p); --p){
		;
	}
	*(++p) = '\0';
	return szOutput;
}

/*   删除两边的空格   */
char * a_trim(char * szOutput, const char * szInput)
{
	char *p = NULL;
	assert(szInput != NULL);
	assert(szOutput != NULL);
	l_trim(szOutput, szInput);
	for (p = szOutput + strlen(szOutput) - 1; p >= szOutput && IsSpace(*p); --p){
		;
	}
	*(++p) = '\0';
	return szOutput;
}

//#在配置文件里表示注释
int GetProfileString(char *profile, const char *AppName, const char *KeyName, char *KeyVal)
{
	char appname[32], keyname[32];
	char *buf, *c;
	char buf_i[KEYVALLEN], buf_o[KEYVALLEN];
	FILE *fp;
	int found = 0; /* 1 AppName 2 KeyName */
	if ((fp = fopen(profile, "r")) == NULL){
		printf("openfile [%s] error [%s]\n", profile, strerror(errno));
		return(-1);
	}
	fseek(fp, 0, SEEK_SET);
	memset(appname, 0, sizeof(appname));
	sprintf(appname, "[%s]", AppName);

	while (!feof(fp) && fgets(buf_i, KEYVALLEN, fp) != NULL){
		l_trim(buf_o, buf_i);
		if (strlen(buf_o) <= 0)
			continue;
		buf = NULL;
		buf = buf_o;

		if (found == 0){
			if (buf[0] != '[') {
				continue;
			}
			else if (strncmp(buf, appname, strlen(appname)) == 0){
				found = 1;
				continue;
			}

		}
		else if (found == 1){
			if (buf[0] == '#'){
				continue;
			}
			else if (buf[0] == '[') {
				break;
			}
			else {
				if ((c = (char*)strchr(buf, '=')) == NULL)
					continue;
				memset(keyname, 0, sizeof(keyname));

				sscanf(buf, "%[^=|^ |^\t]", keyname);
				if (strcmp(keyname, KeyName) == 0){
					sscanf(++c, "%[^\n]", KeyVal);
					int length = strlen(KeyVal) + 1;
					char *KeyVal_o = (char *)malloc(length);
					if (KeyVal_o != NULL){
						memset(KeyVal_o, 0, length);
						a_trim(KeyVal_o, KeyVal);
						if (KeyVal_o && strlen(KeyVal_o) > 0)
							strcpy(KeyVal, KeyVal_o);
						free(KeyVal_o);
						KeyVal_o = NULL;
					}
					found = 2;
					break;
				}
				else {
					continue;
				}
			}
		}
	}
	fclose(fp);
	if (found == 2)
		return(0);
	else
		return(-1);
}
