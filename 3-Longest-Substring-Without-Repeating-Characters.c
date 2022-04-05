#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray_bool(_Bool *nums, int numsSize)
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

#define MAX(a, b) (a > b ? a : b)

int lengthOfLongestSubstring(char *s)
{
	// Using a hashtable to store the last index of every char.
	// And keep tracking the starting point of a valid substring.
	int position_hashtable[95] = {0};
	int i, tmp, start = 0, res = 0;
	for (i = 0; i < strlen(s); i++)
	{
		tmp = s[i] - ' ';
		if (position_hashtable[tmp] != 0)
			start = start > position_hashtable[tmp] ? start : position_hashtable[tmp];
		position_hashtable[tmp] = i + 1;
		if (res < i - start + 1)
			res = i - start + 1;
	}
	return res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("3.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int target;
	char s[100], sSize = 0;
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
		s[sSize] = c;
		sSize++;
	}
	s[sSize] = '\0';
	puts("");

	printf("s = ");
	printArray_char(s, sSize);

	printf("max-length of substring = %d\n", lengthOfLongestSubstring(s));

	return 0;
}