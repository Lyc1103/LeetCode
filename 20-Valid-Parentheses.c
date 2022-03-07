#include <stdio.h>
#include <string.h>

typedef struct stack
{
	char str[100000];
	int top;
} Stack;

void Push(Stack *sta, char c)
{
	sta->top++;
	sta->str[sta->top] = c;
}

int Pop(Stack *sta)
{
	char tmp = sta->str[sta->top];
	sta->top--;
	return tmp;
}

_Bool isValid(char *s)
{
	Stack sta;
	sta.top = 0;
	char tmp;
	int len = strlen(s);
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '(')
			Push(&sta, '(');
		else if (s[i] == '[')
			Push(&sta, '[');
		else if (s[i] == '{')
			Push(&sta, '{');
		else if (s[i] == ')')
		{
			tmp = Pop(&sta);
			if (tmp != '(')
				return 0;
		}
		else if (s[i] == ']')
		{
			tmp = Pop(&sta);
			if (tmp != '[')
				return 0;
		}
		else if (s[i] == '}')
		{
			tmp = Pop(&sta);
			if (tmp != '{')
				return 0;
		}
	}
	if (sta.top != 0)
		return 0;
	return 1;
}

int main()
{
	char *s = "({)}";
	_Bool res = isValid(s);
	if (res)
		printf("true\n");
	else
		printf("false\n");
	return 0;
}