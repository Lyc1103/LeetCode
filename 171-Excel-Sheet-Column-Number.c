#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int titleToNumber(char *columnTitle)
{
	int len = strlen(columnTitle);
	int res = 0;
	for (int i = 0; i < len; i++)
	{
		res = res * 26 + (columnTitle[i] - 'A') + 1;
	}

	return res;
}

int main()
{
	char columnTitle[7] = "FXSHRXW";
	int res = titleToNumber(columnTitle);
	printf("%d\n", res);

	return 0;
}