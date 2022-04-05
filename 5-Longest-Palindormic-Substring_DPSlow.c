#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(char *str, int strSize)
{
	printf("\"");
	for (int i = 0; i < strSize - 1; i++)
		printf("%c", str[i]);
	printf("%c\"\n", str[strSize - 1]);
	return;
}
void printArray_charOfMat(char *str, int strSize)
{
	for (int i = 0; i < strSize - 1; i++)
		printf("%c ", str[i]);
	printf("%c\n", str[strSize - 1]);
	return;
}
void printArray_bool(_Bool *nums, int numsSize)
{
	for (int i = 0; i < numsSize - 1; i++)
		printf("%d ", nums[i]);
	printf("%d\n", nums[numsSize - 1]);
	return;
}

char *longestPalindrome(char *s)
{
	int i, j, cal_len;
	int len = strlen(s);
	if (len == 1)
		return s;

	_Bool **dp = (_Bool **)malloc(len * sizeof(_Bool *));
	for (i = 0; i < len; i++)
	{
		dp[i] = (_Bool *)calloc(len, sizeof(_Bool));
		dp[i][i] = 1;
		if (i - 1 >= 0)
			dp[i][i - 1] = 1;
	}

	int max_len = 1, max_len_pos = 0;
	int tmp_limit;
	_Bool tmp;
	for (cal_len = 2; cal_len <= len; cal_len++)
	{
		tmp_limit = len - cal_len + 1;
		for (i = 0; i < tmp_limit; i++)
		{
			j = i + cal_len - 1;
			if (s[i] == s[j])
			{
				tmp = (dp[i][j] = dp[i + 1][j - 1]);
				if (tmp && max_len < cal_len)
				{
					max_len = cal_len;
					max_len_pos = i;
				}
			}
			printf("dp[%d][%d] = %d, max_len = %d\n", i, j, dp[i][j], max_len);
		}
	}
	printf("max_len = %d, max_len_pos = %d\n", max_len, max_len_pos);

	printf("dp_mat = \n");
	printf("   ");
	printArray_charOfMat(s, len);
	for (i = 0; i < len; i++)
	{
		printf(" %c ", s[len - 1 - i]);
		printArray_bool(dp[i], len);
	}

	char *res = (char *)calloc(max_len + 1, sizeof(char));
	strncpy(res, &(s[max_len_pos]), max_len);
	res[max_len] = '\0';

	return res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("5.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int n = 10;
	int strSize = 0;
	int cnt = 0;
	char *str = (char *)malloc(n * sizeof(char));

	printf("input: ");
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
		str[cnt++] = c;
	}
	int len = cnt;
	str[len] = '\0';
	puts("");

	printf("str = ");
	printArray(str, len);

	char *res = longestPalindrome(str);

	len = strlen(res);
	printf("res = ");
	printArray(res, len);

	return 0;
}