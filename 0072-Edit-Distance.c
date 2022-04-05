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
		printf(" %c ", str[i]);
	printf(" %c\n", str[strSize - 1]);
	return;
}
void printArray_int(int *nums, int numsSize)
{
	for (int i = 0; i < numsSize - 1; i++)
		printf("%2d ", nums[i]);
	printf("%2d\n", nums[numsSize - 1]);
	return;
}

#define MIN(a, b) (a < b ? a : b)

int minDistance(char *word1, char *word2)
{
	int len1 = strlen(word1), len2 = strlen(word2);
	if (len1 == 0)
		return len2;
	else if (len2 == 0)
		return len1;
	int *dp0 = (int *)calloc(len2 + 1, sizeof(int));
	int *dp1 = (int *)calloc(len2 + 1, sizeof(int));
	int i, j, *tmp, tmp_j;
	for (j = 0; j < len2 + 1; j++)
		dp1[j] = j;
	puts("dp = ");
	printf("      ");
	printArray_charOfMat(word2, len2);
	printf("   ");
	printArray_int(dp1, len2 + 1);
	for (i = 0; i < len1; i++)
	{
		dp0[0] = i + 1;
		for (j = 0; j < len2; j++)
		{
			if (word1[i] == word2[j])
				dp0[j + 1] = dp1[j];
			else
				dp0[j + 1] = MIN(MIN(dp0[j], dp1[j + 1]), dp1[j]) + 1;
		}
		printf(" %c ", word1[i]);
		printArray_int(dp0, len2 + 1);
		tmp = dp1;
		dp1 = dp0;
		dp0 = tmp;
	}

	return dp1[len2];
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("72.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char word1[100], word2[100];
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
		word1[cnt_1++] = c;
	}
	word1[cnt_1] = '\0';
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
		word2[cnt_2++] = c;
	}
	word2[cnt_2] = '\0';
	puts("");

	printf("s = ");
	printArray(word1, cnt_1);
	printf("t = ");
	printArray(word2, cnt_2);

	printf("res = %d\n", minDistance(word1, word2));

	return 0;
}