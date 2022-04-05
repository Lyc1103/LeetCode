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
	int i, j, k, *tmp;
	int len = strlen(s);
	int *dp0 = (int *)calloc(len, sizeof(int));
	int *dp1 = (int *)calloc(len, sizeof(int));
	for (i = 0; i < len; i++)
		dp1[i] = 1;
	int *dp2 = (int *)calloc(len, sizeof(int));

	for (k = 1; k < len; k++)
	{
		// printf("round %d:\n", k);
		// printf("      ");
		// printArray_charOfMat(s, len);
		for (i = 0; i < len - k; i++)
		{
			j = i + k;
			if (s[i] == s[j])
				dp0[i] = dp2[i + 1] + 2;
			else
				dp0[i] = MAX(dp1[i], dp1[i + 1]);
		}
		// printf("dp0 = ");
		// for (j = 0; j < k; j++)
		// 	printf("  ");
		// printArray_int(dp0, len - k);
		// printf("dp1 = ");
		// for (j = 1; j < k; j++)
		// 	printf("  ");
		// printArray_int(dp1, len - k + 1);
		// printf("dp2 = ");
		// for (j = 2; j < k; j++)
		// 	printf("  ");
		// printArray_int(dp2, len - k + 2);

		tmp = dp2;
		dp2 = dp1;
		dp1 = dp0;
		dp0 = tmp;
	}

	return dp1[0];
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