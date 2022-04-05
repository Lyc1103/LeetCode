// Reference: https://leetcode.com/problems/perfect-squares/discuss/1811965/C%2B%2B-Solution-Faster-than-100
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int numSquares(int n)
{
	if (n <= 3)
		return n;

	int i, s, t;
	int st = sqrt(n);
	if (st * st == n)
		return 1;
	while (n % 4 == 0)
		n /= 4;
	if (n % 8 == 7)
		return 4;
	for (i = 1; i * i < n; i++)
	{
		s = n - i * i;
		t = sqrt(s);
		if (t * t == s)
			return 2;
	}
	return 3;
}

int main()
{
	int n;
	FILE *pfile = NULL;
	if ((pfile = fopen("279.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	printf("input: ");
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &n);
	printf(" %d ", n);
	puts("");
	printf("num square of %d = %d\n", n, numSquares(n));
	return 0;
}