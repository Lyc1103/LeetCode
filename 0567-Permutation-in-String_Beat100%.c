// Reference: https://github.com/vli02/leetcode/blob/master/567.%20Permutation%20in%20String.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void printArray_char(char *str, int strSize)
{
	printf("\"");
	for (int i = 0; i < strSize - 1; i++)
	{
		printf("%c", str[i]);
	}
	if (strSize == 0)
		puts("\"");
	else
		printf("%c\"\n", str[strSize - 1]);
	return;
}

_Bool checkInclusion(char *s1, char *s2)
{
	int i, j;
	int buffer[26] = {0}, cnt = 0;
	char c, k;

	while (c = *(s1++))
	{
		buffer[c - 'a']++;
		cnt++;
	}

	i = j = 0;
	while (c = s2[j++])
	{
		c -= 'a';
		if (buffer[c] > 0)
			cnt--;
		if (cnt == 0)
			return 1; // where i is the start index, j - i is the length
		buffer[c]--;
		while (buffer[c] < 0)
		{
			k = s2[i++];
			k -= 'a';
			buffer[k]++;
			if (buffer[k] > 0)
				cnt++;
		}
	}

	return 0;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("567.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int target;
	char s1[100], s2[100];
	int s1Size = 0, s2Size = 0;
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
		s1[s1Size] = c;
		s1Size++;
	}
	s1[s1Size] = '\0';
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
		s2[s2Size] = c;
		s2Size++;
	}
	s2[s2Size] = '\0';
	puts("");

	printf("s1 = ");
	printArray_char(s1, s1Size);
	printf("s2 = ");
	printArray_char(s2, s2Size);

	if (checkInclusion(s1, s2))
		puts("true");
	else
		puts("false");

	return 0;
}