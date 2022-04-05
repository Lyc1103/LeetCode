#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (a < b ? a : b)

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

void popFromStack(Stack *sta)
{
	if (isEmptyStack(sta))
		return;
	(sta->top)--;
	return;
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
		puts("sta = \"\"");
		return;
	}
	printf("sta = [");
	int i;
	for (i = 0; i < sta->top; i++)
		printf("\"%c\", ", sta->data[i]);
	printf("%c]\n", sta->data[i]);
	return;
}

_Bool backspaceCompare(char *s, char *t)
{
	int i;
	int len_s = strlen(s);
	int len_t = strlen(t);
	Stack *sta_s = createStack(201);
	Stack *sta_t = createStack(201);
	for (i = 0; i < MIN(len_s, len_t); i++)
	{
		if (s[i] == '#')
			popFromStack(sta_s);
		else
			pushToStack(sta_s, s[i]);
		if (t[i] == '#')
			popFromStack(sta_t);
		else
			pushToStack(sta_t, t[i]);
	}
	for (; i < len_s; i++)
	{
		if (s[i] == '#')
			popFromStack(sta_s);
		else
			pushToStack(sta_s, s[i]);
	}
	for (; i < len_t; i++)
	{
		if (t[i] == '#')
			popFromStack(sta_t);
		else
			pushToStack(sta_t, t[i]);
	}
	pushToStack(sta_s, '\0');
	pushToStack(sta_t, '\0');

	return strcmp(sta_s->data, sta_t->data) == 0 ? 1 : 0;
}

char *dealWithInputFile_ForString(FILE *pfile, int *strSize)
{
	char c;
	char *str = (char *)malloc(50 * sizeof(char));
	*strSize = 0;
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
	str[*strSize] = '\0';
	return str;
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
		printf("%c\"", str[strSize - 1]);
	puts(" //  completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("844.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int strSize1, strSize2;
	char *s = dealWithInputFile_ForString(pfile, &strSize1);
	char *t = dealWithInputFile_ForString(pfile, &strSize2);
	puts("");

	printf("s: ");
	printArray_char(s, strSize1);
	printf("t: ");
	printArray_char(t, strSize2);

	if (backspaceCompare(s, t))
		puts("true");
	else
		puts("false");

	return 0;
}
