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
	printf("%c\"\n", str[strSize - 1]);
	return;
}

void reverseString(char *s, int sSize)
{
	int f = 0, r = sSize - 1;
	char tmp;
	while (f < r)
	{
		tmp = s[f];
		s[f] = s[r];
		s[r] = tmp;
		f++;
		r--;
	}
	return;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("344.txt", "r")) == NULL)
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
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "\"%c\"", &(s[sSize]));
		printf("\"%c\"", s[sSize]);
		sSize++;
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
	}
	s[sSize] = '\0';
	puts("");

	printf("s = ");
	printArray_char(s, sSize);

	reverseString(s, sSize);
	printf("reversed s = ");
	printArray_char(s, sSize);
	printf("i.e. output: [");
	for (int i = 0; i < sSize - 1; i++)
	{
		printf("\"%c\",", s[i]);
	}
	printf("\"%c\"]\n", s[sSize - 1]);

	return 0;
}