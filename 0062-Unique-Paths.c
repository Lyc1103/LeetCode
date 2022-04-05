#include <stdio.h>
#include <stdlib.h>

int uniquePaths(int m, int n)
{
	int i, j;
	int **res = (int **)malloc(m * sizeof(int *));
	res[0] = (int *)calloc(n, sizeof(int));
	for (j = 0; j < n; j++)
		res[0][j] = 1;
	for (i = 1; i < m; i++)
	{
		res[i] = (int *)calloc(n, sizeof(int));
		res[i][0] = 1;
		for (j = 1; j < n; j++)
			res[i][j] = res[i - 1][j] + res[i][j - 1];
	}
	return res[m - 1][n - 1];
}

int main()
{
	int m = 51;
	int n = 9;
	printf("%d\n", uniquePaths(m, n));
	return 0;
}