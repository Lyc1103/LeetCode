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
	int i, j, k, tmp;
	int buffer[26] = {0}, tmp_buffer[26] = {0};
	for (i = 0; i < strlen(s1); i++)
		tmp_buffer[s1[i] - 'a'] = (buffer[s1[i] - 'a'] += 1);
	printArray_int(tmp_buffer, 26);
	for (i = 0, j = strlen(s1) - 1; j < strlen(s2); i++, j++)
	{
		printf("i = %d, j = %d, array = ", i, j);
		printArray_char(&(s2[i]), strlen(s1));
		for (k = i; k <= j; k++)
			if ((tmp_buffer[s2[k] - 'a'] -= 1) < 0)
				break;
		printArray_int(tmp_buffer, 26);
		if (k == j + 1)
			return 1;
		for (k = 0; k < 26; k++)
			tmp_buffer[k] = buffer[k];
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