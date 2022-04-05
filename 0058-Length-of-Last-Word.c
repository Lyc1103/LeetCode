#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int lengthOfLastWord(char *s)
{
	char *tok;
	const char cut[2] = " ";
	tok = strtok(s, cut);
	int len;
	while (tok != NULL)
	{
		len = strlen(tok);
		// printf("strlen(%s) = %d\n", tok, strlen(tok));
		tok = strtok(NULL, cut);
	}
	return len;
}

int main()
{
	char s[10001] = "luffy is still joyboy";
	int len = lengthOfLastWord(s);
	printf("str len of last word = %d\n", len);
	return 0;
}