// Reference:　https://github.com/kenjin/DSAlgo/blob/master/LeetCode/0139_Word-Break/0139_word-break-dp-sol.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(char *str, int strSize)
{
	printf("[");
	for (int i = 0; i < strSize; i++)
	{
		if (str[i] == '\0')
			break;
		printf("%c", str[i]);
	}
	puts("]");
	return;
}

_Bool findBreak(_Bool **dp, int base_index, int size)
{
	if (base_index >= size)
		return 1;

	int i;
	for (i = 0; i < size; i++)
	{
		if (dp[base_index][i] && findBreak(dp, i + 1, size))
			return 1;
		else
			dp[base_index][i] = 0;
	}
	return 0;
}

_Bool wordBreak(char *s, char **wordDict, int wordDictSize)
{
	int s_len = strlen(s);
	_Bool **dp = (_Bool **)malloc(s_len * sizeof(_Bool *));
	int i;
	for (i = 0; i < s_len; i++)
		dp[i] = (_Bool *)calloc(s_len, sizeof(_Bool));

	for (i = 0; i < wordDictSize; i++)
	{
		char *pos = strstr(s, wordDict[i]);
		int w_len = strlen(wordDict[i]);
		while (pos != NULL)
		{
			int start = pos - s;
			int end = start + w_len - 1;
			dp[start][end] = 1;
			pos = strstr(&(s[start + 1]), wordDict[i]);
		}
	}

	_Bool res = findBreak(dp, 0, s_len);
	for (i = 0; i < s_len; i++)
	{
		free(dp[i]);
	}
	free(dp);
	return res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("139.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int flag = 0;
	char s[301] = "";
	int s_len = 0;
	printf("input:\n");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c != '"' && flag == 1)
			s[s_len++] = c;
		if (c == '"')
			flag++;
		if (flag == 2)
			break;
	}

	flag = 0;
	int wordDictSize = 0;
	char **wordDict = (char **)malloc(100 * sizeof(char *));
	for (int i = 0; i < 100; i++)
	{
		wordDict[i] = (char *)calloc(21, sizeof(char));
	}
	int w_len = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c != '"' && flag == 1)
			wordDict[wordDictSize][w_len++] = c;
		else if (c == '"' && flag == 1)
		{
			wordDictSize++;
			flag = 0;
			w_len = 0;
		}
		else if (c == '"' && flag == 0)
			flag = 1;
	}
	puts("");

	printf("s = ");
	printArray(s, s_len);
	puts("wordDict = ");
	for (int i = 0; i < wordDictSize; i++)
	{
		printf("word %d: ", i);
		printArray(wordDict[i], 10);
	}

	if (wordBreak(s, wordDict, wordDictSize))
		puts("true");
	else
		puts("false");

	return 0;
}