#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *longestCommonPrefix(char strs[3][201], int strsSize)
{
	char *res = strs[0];
	int len = 0;
	while (len <= strlen(strs[0]))
	{
		for (int i = 0; i < strsSize; i++)
		{
			if (strs[0][len] != strs[i][len] || len > strlen(strs[i]))
			{
				res[len] = '\0';
				return res;
			}
		}
		len++;
	}
	res[len] = '\0';
	return res;
}

int main()
{
	char strs[3][201] = {"ab", "a"};
	printf("\"%s\", \"%s\", \"%s\"\n", strs[0], strs[1], strs[2]);
	char *res = longestCommonPrefix(strs, 2);
	printf("\"%s\"\n", res);
	return 0;
}