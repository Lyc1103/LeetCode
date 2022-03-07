#include <stdio.h>
#include <stdlib.h>

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

void insertRes(int *res, int data)
{
	if (res[0] == data || res[1] == data || res[1] == data)
		return;
	if (res[0] < data)
	{
		res[2] = res[1];
		res[1] = res[0];
		res[0] = data;
	}
	else if (res[1] < data)
	{
		res[2] = res[1];
		res[1] = data;
	}
	else if (res[2] < data)
	{
		res[2] = data;
	}
	return;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getBiggestThree(int **grid, int gridSize, int *gridColSize, int *returnSize)
{
	int *res = (int *)calloc(3, sizeof(int)), sum;
	int cnt = 0, min = gridSize > *gridColSize ? (*gridColSize) / 2 : gridSize / 2;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < *gridColSize; j++)
		{
			insertRes(res, grid[i][j]);
			for (int k = 1; k <= min; k++)
			{
				if (i + 2 * k < gridSize && j - k >= 0 && j + k < *gridColSize)
				{
					sum = 0;
					// printf("i = %d, j = %d, k = %d\n", i, j, k);
					// printf("i+k = %d, j-k = %d, j+k = %d\n", i + k, j - k, j + k);
					int l, x = i, y = j;
					for (l = 1; l <= k; l++)
					{
						sum += grid[x++][y++];
					}
					for (l = 0; l < k; l++)
					{
						sum += grid[x++][y--];
					}
					for (l = 0; l < k; l++)
					{
						sum += grid[x--][y--];
					}
					for (l = 0; l < k; l++)
					{
						sum += grid[x--][y++];
					}
					// printf("sum = %d\n\n", sum);
					insertRes(res, sum);
				}
			}
		}
	}

	*returnSize = 0;
	for (int i = 0; i < 3; i++)
	{
		if (res[i] != 0)
			(*returnSize)++;
	}

	return res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("1878-1.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	int rows, cols;
	fscanf(pfile, "%d%d", &rows, &cols);
	printf("rows = %d, cols = %d\n", rows, cols);
	int **grid = (int **)malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++)
	{
		grid[i] = (int *)calloc(cols, sizeof(int));
		for (int j = 0; j < cols; j++)
		{
			fscanf(pfile, "%d", &grid[i][j]);
			printf("%d ", grid[i][j]);
		}
		puts("");
	}
	fclose(pfile);
	int returnSize;
	int *res = getBiggestThree(grid, rows, &cols, &returnSize);
	printArray(res, returnSize);
	return 0;
}