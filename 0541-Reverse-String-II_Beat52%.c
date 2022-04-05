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

char *reverseStr(char *s, int k)
{
	int i, f, r, tmp;
	int len = strlen(s);
	for (i = 0; i < len; i += 2 * k)
	{
		f = i;
		r = i + k - 1 < len ? i + k - 1 : len - 1;
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
	if ((pfile = fopen("541.txt", "r")) == NULL)
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
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &k);
	printf(" %d", k);
	puts("");

	printf("s = ");
	printArray_char(s, sSize);
	printf("k = %d\n", k);

	reverseStr(s, k);
	printf("output: ");
	printArray_char(s, sSize);

	return 0;
}