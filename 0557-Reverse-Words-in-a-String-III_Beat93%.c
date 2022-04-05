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

char *reverseWords(char *s)
{
	int i, f = 0, r, tmp;
	int len = strlen(s);
	for (i = 0; i < len; i++)
	{
		if (s[i] == ' ')
		{
			r = i - 1;
			while (f < r)
			{
				tmp = s[f];
				s[f] = s[r];
				s[r] = tmp;
				f++;
				r--;
			}
			f = i + 1;
		}
	}
	if (s[len - 1] != ' ')
	{
		r = len - 1;
		while (f < r)
		{
			tmp = s[f];
			s[f] = s[r];
			s[r] = tmp;
			f++;
			r--;
		}
	}

	return s;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("557.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int k;
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

	reverseWords(s);
	printf("output: ");
	printArray_char(s, sSize);

	return 0;
}