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

int minFallingPathSum(int **matrix, int matrixSize, int *matrixColSize)
{
	if (matrixSize == 1)
		return matrix[0][0];

	int i, j, tmp, tmp_i;
	int first_min_val = INT_MAX, first_min_pos;
	int second_min_val = INT_MAX;
	int pre_first_min_val = INT_MAX, pre_first_min_pos;
	int pre_second_min_val = INT_MAX;
	for (j = 0; j < matrixSize; j++)
	{
		if ((tmp = matrix[0][j]) < pre_first_min_val)
		{
			pre_second_min_val = pre_first_min_val;
			pre_first_min_val = tmp;
			pre_first_min_pos = j;
		}
		else if (tmp < pre_second_min_val)
		{
			pre_second_min_val = tmp;
		}
	}
	for (i = 1; i < matrixSize; i++)
	{
		first_min_val = INT_MAX;
		second_min_val = INT_MAX;
		for (j = 0; j < matrixSize; j++)
		{
			if (j != pre_first_min_pos)
				tmp = (matrix[i][j] += pre_first_min_val);
			else
				tmp = (matrix[i][j] += pre_second_min_val);

			if (tmp < first_min_val)
			{
				second_min_val = first_min_val;
				first_min_val = tmp;
				first_min_pos = j;
			}
			else if (tmp < second_min_val)
			{
				second_min_val = tmp;
			}
		}
		pre_first_min_pos = first_min_pos;
		pre_first_min_val = first_min_val;
		pre_second_min_val = second_min_val;
	}
	return first_min_val;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("1289.txt", "r")) == NULL)
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
