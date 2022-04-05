#include <stdio.h>
#include <stdlib.h>

void printArray(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%3d", nums[i]);
		printf(",");
	}
	printf("%3d]\n", nums[numsSize - 1]);
	return;
}

#define MIN(a, b) (a < b ? a : b)

int minPathSum(int **grid, int gridSize, int *gridColSize)
{
	int i, j, tmp_i;
	for (j = 1; j < *gridColSize; j++)
		grid[0][j] += grid[0][j - 1];
	for (i = 1; i < gridSize; i++)
	{
		tmp_i = i - 1;
		grid[i][0] += grid[tmp_i][0];
		for (j = 1; j < *gridColSize; j++)
			grid[i][j] += MIN(grid[tmp_i][j], grid[i][j - 1]);
	}
	return grid[i - 1][j - 1];
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("64.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int flag = 0, tmp;
	int n = 10;
	int gridSize = 0;
	int gridColSize, cnt;
	int **grid = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		grid[i] = (int *)calloc(n, sizeof(int));

	printf("input:\n");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	cnt = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']' && flag == 2)
			break;
		else if (c == ']')
		{
			gridSize++;
			gridColSize = cnt;
			cnt = 0;
			flag = 2;
		}
		else if (c == '[' || flag == 1)
		{
			fscanf(pfile, "%d", &(grid[gridSize][cnt]));
			printf("%d", grid[gridSize][cnt]);
			cnt++;
			flag = 1;
		}
	}
	puts("");

	printf("grid = \n");
	for (int i = 0; i < gridSize; i++)
	{
		printf("row%d: ", i);
		printArray(grid[i], gridColSize);
	}
	puts("");

	printf("min-path-sum = %d\n", minPathSum(grid, gridSize, &gridColSize));
	printf("grid = \n");
	for (int i = 0; i < gridSize; i++)
	{
		printf("row%d: ", i);
		printArray(grid[i], gridColSize);
	}
	return 0;
}