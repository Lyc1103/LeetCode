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

int longestCommonSubsequence(char *text1, char *text2)
{
	int len1 = strlen(text1), len2 = strlen(text2);
	int *dp0 = (int *)calloc(len2, sizeof(int));
	int *dp1 = (int *)calloc(len2, sizeof(int));
	int i, j, *tmp;
	if (text1[0] == text2[0])
		dp1[0] = 1;
	for (j = 1; j < len2; j++)
	{
		if (text1[0] == text2[j])
			dp1[j] = 1;
		else
			dp1[j] = dp1[j - 1];
	}
	puts("dp = ");
	printf("   ");
	printArray_charOfMat(text2, len2);
	printf(" %c ", text1[0]);
	printArray_int(dp1, len2);
	for (i = 1; i < len1; i++)
	{
		if (text1[i] == text2[0])
			dp0[0] = 1;
		else
			dp0[0] = dp1[0];
		for (j = 1; j < len2; j++)
		{
			if (text1[i] == text2[j])
				dp0[j] = dp1[j - 1] + 1;
			else
				dp0[j] = MAX(dp0[j - 1], dp1[j]);
		}
		printf(" %c ", text1[i]);
		printArray_int(dp0, len2);
		tmp = dp1;
		dp1 = dp0;
		dp0 = tmp;
	}
	return dp1[len2 - 1];
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("1143.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char text1[100], text2[100];
	int cnt_1 = 0, cnt_2 = 0;
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
		text1[cnt_1++] = c;
	}
	text1[cnt_1] = '\0';
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
		text2[cnt_2++] = c;
	}
	text2[cnt_2] = '\0';
	puts("");

	printf("s = ");
	printArray(text1, cnt_1);
	printf("t = ");
	printArray(text2, cnt_2);

	printf("res = %d\n", longestCommonSubsequence(text1, text2));

	return 0;
}