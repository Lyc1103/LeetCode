// Reference: http://juzertech.com/index.php/2021/05/03/leetcode-5-longest-palindromic-substring-c-medium/
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
void printArray_int(int *nums, int numsSize)
{
	for (int i = 0; i < numsSize - 1; i++)
		printf("%d ", nums[i]);
	printf("%d\n", nums[numsSize - 1]);
	return;
}

#define MAX(a, b) (a > b ? a : b)

int longestPalindromeSubseq(char *s)
{
	int i, j, k, tmp;
	int len = strlen(s), max_pal_len = 1;
	int **dp = (int **)malloc(len * sizeof(int *));
	for (i = 0; i < len; i++)
	{
		dp[i] = (int *)calloc(len, sizeof(int));
		dp[i][i] = 1;
	}
	for (k = 1; k < len; k++)
	{
		for (i = 0; i < len - k; i++)
		{
			j = i + k;
			if (s[i] == s[j])
				dp[i][j] = dp[i + 1][j - 1] + 2;
			else
				dp[i][j] = MAX(dp[i + 1][j], dp[i][j - 1]);
			max_pal_len = MAX(max_pal_len, dp[i][j]);
		}
	}
	printf("dp_mat = \n");
	printf("   ");
	printArray_charOfMat(s, len);
	for (i = 0; i < len; i++)
	{
		printf(" %c ", s[i]);
		printArray_int(dp[i], len);
	}

	return max_pal_len;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("516.txt", "r")) == NULL)
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

	printf("res = %d\n", longestPalindromeSubseq(str));

	return 0;
}