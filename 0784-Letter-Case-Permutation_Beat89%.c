#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

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
		printf("%c\"", str[strSize - 1]);
	puts(" // completely print.");
	return;
}

int Pow(int m, int n)
{
	int i, res = 1;
	for (i = 0; i < n; i++)
	{
		res *= m;
	}
	return res;
}

typedef struct stackInformation
{
	int top;
	char *data;
} Stack;

Stack *createStack(int size)
{
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->top = -1;
	sta->data = (char *)malloc(size * sizeof(char));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	return sta->top == -1 ? 1 : 0;
}

void pushToStack(Stack *sta, char data)
{
	(sta->top)++;
	sta->data[sta->top] = data;
	return;
}

int popFromStack(Stack *sta)
{
	(sta->top)--;
	return sta->data[(sta->top) + 1];
}

void freeStack(Stack *sta)
{
	free(sta->data);
	free(sta);
	return;
}

void printElementsInStack(Stack *sta)
{
	if (isEmptyStack(sta))
	{
		puts("sta = []");
		return;
	}
	printf("sta = [");
	int i;
	for (i = 0; i < sta->top; i++)
		printf("%c,", sta->data[i]);
	printf("%c]\n", sta->data[i]);
}

void cpyElementsFromStackToArray(Stack *sta, char **ret, int *ctr)
{
	for (int i = 0; i <= sta->top; i++)
		ret[*ctr][i] = sta->data[i];
	(*ctr)++;
	return;
}

char lowercase[26] = "abcdefghijklmnopqrstuvwxyz";
char uppercase[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
void DFS(char *s, int slen, char **ret, int *ctr, int pos, int len, Stack *sta)
{

	if (len == 0)
	{
		// printElementsInStack(sta);
		cpyElementsFromStackToArray(sta, ret, ctr);
		ret[*ctr - 1][slen] = '\0';
		return;
	}
	int tmp_a = s[pos] - 'a';
	int tmp_A = s[pos] - 'A';
	if (tmp_a >= 0 && tmp_a <= 25)
	{
		pushToStack(sta, s[pos]);
		DFS(s, slen, ret, ctr, pos + 1, len - 1, sta);
		popFromStack(sta);
		pushToStack(sta, uppercase[tmp_a]);
		DFS(s, slen, ret, ctr, pos + 1, len - 1, sta);
		popFromStack(sta);
	}
	else if (tmp_A >= 0 && tmp_A <= 25)
	{
		pushToStack(sta, s[pos]);
		DFS(s, slen, ret, ctr, pos + 1, len - 1, sta);
		popFromStack(sta);
		pushToStack(sta, lowercase[tmp_A]);
		DFS(s, slen, ret, ctr, pos + 1, len - 1, sta);
		popFromStack(sta);
	}
	else
	{
		pushToStack(sta, s[pos]);
		DFS(s, slen, ret, ctr, pos + 1, len - 1, sta);
		popFromStack(sta);
	}

	return;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCasePermutation(char *s, int *returnSize)
{
	int i, slen = strlen(s);
	int permute_len = slen;
	for (i = 0; i < slen; i++)
		if (s[i] - '0' >= 0 && s[i] - '0' <= 9)
			permute_len--;
	// printf("permute_len = %d\n", permute_len);
	permute_len = Pow(2, permute_len);
	// printf("ret size = %d\n", permute_len);
	char **ret = (char **)malloc(permute_len * sizeof(char *));
	for (i = 0; i < permute_len; i++)
		ret[i] = (char *)malloc((slen + 1) * sizeof(char));
	*returnSize = 0;
	Stack *sta = createStack(slen + 1);
	DFS(s, slen, ret, returnSize, 0, slen, sta);
	return ret;
}

void dealWithInputFile_ForString(FILE *pfile, char *str, int *strSize)
{
	char c;
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
		str[*strSize] = c;
		(*strSize)++;
	}
	puts("");
	return;
}

void printMatrix_char(char **mat, int matSize)
{
	for (int i = 0; i < matSize; i++)
		printf("  row%d = \"%s\"\n", i, mat[i]);
	puts("  completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("784.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char str[50] = "";
	int strSize = 0;
	dealWithInputFile_ForString(pfile, str, &strSize);
	printf("str: ");
	printArray_char(str, strSize);

	int returnSize;
	char **ret = letterCasePermutation(str, &returnSize);
	puts("ret:");
	printMatrix_char(ret, returnSize);
	return 0;
}