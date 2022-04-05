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

char *longestPalindrome(char *s)
{
	int i, len = strlen(s);
	int cmp_r, cmp_l, max_len = 1, max_len_pos = 0;
	for (i = 0; i < len; i++)
	{
		cmp_l = i;
		cmp_r = i;
		while (cmp_r + 1 < len)
		{
			if (s[cmp_r + 1] == s[cmp_r])
				cmp_r++;
			else
				break;
		}

		while (cmp_l - 1 >= 0 && cmp_r + 1 < len)
		{
			if (s[cmp_l - 1] == s[cmp_r + 1])
			{
				cmp_l--;
				cmp_r++;
			}
			else
				break;
		}

		if (max_len < cmp_r - cmp_l + 1)
		{
			max_len = cmp_r - cmp_l + 1;
			max_len_pos = cmp_l;
		}
	}

	char *res = (char *)malloc((max_len + 1) * sizeof(char));
	strncpy(res, &(s[max_len_pos]), max_len);
	res[max_len] = '\0';

	return res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("5.txt", "r")) == NULL)
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

	char *res = longestPalindrome(str);

	len = strlen(res);
	printf("res = ");
	printArray(res, len);

	return 0;
}