#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
char *convertToTitle(int columnNumber)
{
	char buffer[26] = "ZABCDEFGHIJKLMNOPQRSTUVWXY";
	char *rev_res = (char *)malloc(20 * sizeof(char));
	int quotient = columnNumber / 26, remainder = columnNumber % 26;
	int cnt = 0;
	while (quotient != 0 || remainder != 0)
	{
		if (remainder == 0)
		{
			rev_res[cnt] = buffer[0];
			quotient -= 1;
		}
		else
			rev_res[cnt] = buffer[remainder];
		printf("rev_res = %s\n", rev_res);

		remainder = quotient % 26;
		quotient /= 26;
		cnt++;
	}
	rev_res[cnt] = '\0';
	printf("final rev_res = %s\n", rev_res);

	char *res = (char *)malloc((cnt + 1) * sizeof(char));
	for (int i = 0; i < cnt; i++)
	{
		res[i] = rev_res[cnt - 1 - i];
	}
	res[cnt] = '\0';

	return res;
}
*/
char *convertToTitle(int columnNumber)
{
	char *rev_res = (char *)malloc(20 * sizeof(char));
	int cnt = 0;
	while (columnNumber > 0)
	{
		columnNumber--;
		rev_res[cnt] = (columnNumber % 26) + 'A';
		columnNumber /= 26;
		cnt++;
	}
	rev_res[cnt] = '\0';
	printf("final rev_res = %s\n", rev_res);

	char *res = (char *)malloc((cnt + 1) * sizeof(char));
	for (int i = 0; i < cnt; i++)
	{
		res[i] = rev_res[cnt - 1 - i];
	}
	res[cnt] = '\0';

	return res;
}

int main()
{
	int columnNumber = 701;
	char *str = convertToTitle(columnNumber);
	printf("%s\n", str);

	return 0;
}