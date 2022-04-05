#include <stdio.h>
#include <string.h>

void printArray(char *str, int strSize)
{
	printf("\"");
	for (int i = 0; i < strSize - 1; i++)
		printf("%c", str[i]);
	printf("%c\"\n", str[strSize - 1]);
	return;
}

_Bool isSubsequence(char *s, char *t)
{
	int i;
	int len_t = strlen(t);
	int len_s = strlen(s);
	int cnt_s = 0;
	for (i = 0; i < len_t; i++)
		if (s[cnt_s] == t[i])
			cnt_s++;

	if (cnt_s == len_s)
		return 1;
	return 0;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("392.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char s[100], t[100];
	int cnt_s = 0, cnt_t = 0;
	printf("input: ");
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '"')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '"')
			break;
		s[cnt_s++] = c;
	}
	s[cnt_s] = '\0';
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '"')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '"')
			break;
		t[cnt_t++] = c;
	}
	t[cnt_t] = '\0';
	puts("");

	printf("s = ");
	printArray(s, cnt_s);
	printf("t = ");
	printArray(t, cnt_t);

	if (isSubsequence(s, t))
		puts("true");
	else
		puts("false");

	return 0;
}