// Reference: https://hackmd.io/@kenjin/S1Xye_onS
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
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if (len1 > len2)
		return 0;

	int i, j, tmp;
	int buffer[26] = {0};
	for (i = 0; i < len1; i++)
		buffer[s1[i] - 'a'] += 1;

	// check first window
	int index, cnt = 0;
	for (i = 0; i < len1; i++)
	{
		index = s2[i] - 'a';
		if (--buffer[index] >= 0)
			cnt++;
	}
	if (cnt == len1)
		return 1;

	// sliding window
	int front = 0, front_index;
	int rear = len1, rear_index;
	while (rear < len2)
	{
		front_index = s2[front] - 'a';
		rear_index = s2[rear] - 'a';
		if (++buffer[front_index] > 0)
			cnt--;
		if (--buffer[rear_index] >= 0)
			cnt++;
		if (cnt == len1)
			return 1;
		front++;
		rear++;
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