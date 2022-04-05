// Reference: https://hackmd.io/@kenjin/0264_ugly-number-ii
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printArray(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d", nums[i]);
		printf(",");
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

#define MIN(a, b) (a < b ? a : b)

int minFallingPathSum(int **matrix, int matrixSize, int *matrixColSize)
{
	if (matrixSize == 1)
		return matrix[0][0];

	int min_res = INT_MAX;
	int i = 0, j, tmp, tmp_i;
	for (i = 1; i < matrixSize - 1; i++)
	{
		tmp_i = i - 1;
		matrix[i][0] += MIN(matrix[tmp_i][0], matrix[tmp_i][1]);
		for (j = 1; j < matrixSize - 1; j++)
			matrix[i][j] += MIN(MIN(matrix[tmp_i][j - 1], matrix[tmp_i][j]), matrix[tmp_i][j + 1]);
		matrix[i][matrixSize - 1] += MIN(matrix[tmp_i][j - 1], matrix[tmp_i][j]);
	}

	tmp_i = i - 1;
	tmp = (matrix[i][0] += MIN(matrix[tmp_i][0], matrix[tmp_i][1]));
	min_res = MIN(min_res, tmp);
	// printf("min_res = %d, matrix[%d][0] = %d\n", min_res, i, matrix[i][0]);
	for (j = 1; j < matrixSize - 1; j++)
	{
		tmp = (matrix[i][j] += MIN(MIN(matrix[tmp_i][j - 1], matrix[tmp_i][j]), matrix[tmp_i][j + 1]));
		min_res = MIN(min_res, tmp);
		// printf("min_res = %d, matrix[%d][%d] = %d\n", min_res, i, j, matrix[i][j]);
	}
	tmp = (matrix[i][matrixSize - 1] += MIN(matrix[tmp_i][j - 1], matrix[tmp_i][j]));
	min_res = MIN(min_res, tmp);
	// printf("min_res = %d, matrix[%d][%d] = %d\n", min_res, i, j, matrix[i][j]);
	return min_res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("931.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int flag = 0;
	int n = 10;
	int **matrix = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
	{
		matrix[i] = (int *)calloc(n, sizeof(int));
	}
	int matrixSize = 0, cnt = 0;
	printf("input:\n");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
		{
			matrixSize++;
			cnt = 0;
			flag = 2;
		}
		else if (c == '[' || flag == 1)
		{
			fscanf(pfile, "%d", &(matrix[matrixSize][cnt]));
			printf("%d", matrix[matrixSize][cnt]);
			cnt++;
			flag = 1;
		}
	}
	matrixSize -= 2;
	puts("");

	printf("matrix = \n");
	for (int i = 0; i < matrixSize; i++)
	{
		printf("row%d: ", i);
		printArray(matrix[i], matrixSize);
	}

	int res = minFallingPathSum(matrix, matrixSize, &matrixSize);
	printf("matrix = \n");
	for (int i = 0; i < matrixSize; i++)
	{
		printf("row%d: ", i);
		printArray(matrix[i], matrixSize);
	}
	printf("res = %d\n", res);

	return 0;
}
