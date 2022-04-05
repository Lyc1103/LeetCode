#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *addBinary(char *a, char *b)
{
	int lena = strlen(a), lenb = strlen(b);
	int len = lena > lenb ? lena : lenb;
	// printf("len = %d\n", len);
	char *c = (char *)malloc((len + 1) * sizeof(char));
	c[len] = '\0';
	int carry = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (lena)
			carry += a[--lena] - '0';
		if (lenb)
			carry += b[--lenb] - '0';
		c[i] = (carry & 1) + '0';
		carry = carry >> 1;
	}
	if (carry == 1)
	{
		c = (char *)realloc(c, len + 2);
		c[len + 1] = '\0';
		for (int i = len; i > 0; i--)
			c[i] = c[i - 1];
		c[0] = '1';
	}
	return c;
}

int main()
{
	char a[10001] = "11";
	char b[10001] = "1";
	char *c = addBinary(a, b);
	int len = strlen(c);
	printf("\"");
	for (int i = 0; i < len; i++)
	{
		printf("%c", c[i]);
	}
	printf("\"\n");
	return 0;
}