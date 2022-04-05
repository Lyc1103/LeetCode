#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(char *str, int strSize)
{
	printf("\"");
	for (int i = 0; i < strSize; i++)
	{
		if (str[i] == '\0')
			break;
		printf("%c", str[i]);
	}
	puts("\"");
	return;
}

void printArray_int(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d,", nums[i]);
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

int numDecodings(char *s)
{
	int len = strlen(s);
	if (s[0] == '0')
		return 0;
	if (len == 1)
		return 1;

	int i, tmp;
	int bufferSize = (tmp = len + 1) <= 46 ? tmp : 46;
	int *buffer = (int *)calloc(bufferSize, sizeof(int));
	buffer[0] = 1;
	buffer[1] = 1;
	for (i = 2; i < bufferSize; i++)
	{
		buffer[i] = buffer[i - 1] + buffer[i - 2];
	}
	// printArray_int(buffer, bufferSize);

	int cnt = 1, res = 1;
	// printf("cnt = %d, res = %d\n", cnt, res);
	for (i = 1; i < len; i++)
	{
		if ((tmp = (s[i - 1] - '0') * 10 + (s[i] - '0')) >= 11 && tmp <= 26 && tmp != 20)
		{
			cnt++;
		}
		else if (tmp == 10 || tmp == 20)
		{
			res *= buffer[cnt - 1];
			cnt = 1;
		}
		else if (tmp % 10 == 0)
			return 0;
		else
		{
			res *= buffer[cnt];
			cnt = 1;
		}
		// printf("tmp = %d, cnt = %d, res = %d\n", tmp, cnt, res);
	}
	if (cnt != 1)
		res *= buffer[cnt];

	return res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("91.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int flag = 0;
	char s[301] = "";
	int s_len = 0;
	printf("input:\n");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c != '"' && flag == 1)
			s[s_len++] = c;
		if (c == '"')
			flag++;
		if (flag == 2)
			break;
	}
	puts("");

	printf("s = ");
	printArray(s, s_len);

	int res = numDecodings(s);
	printf("res = %d\n", res);

	return 0;
}