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

int uniquePathsWithObstacles(int **obstacleGrid, int obstacleGridSize, int *obstacleGridColSize)
{
	if (obstacleGrid[0][0] == 1)
		return 0;
	int i, j, tmp, tmp_i, tmp_j;
	int **res = (int **)malloc(obstacleGridSize * sizeof(int *));
	res[0] = (int *)calloc(*obstacleGridColSize, sizeof(int));
	res[0][0] = 1;
	for (j = 1; j < *obstacleGridColSize; j++)
		res[0][j] = obstacleGrid[0][j] != 1 ? res[0][j - 1] : 0;
	for (i = 1; i < obstacleGridSize; i++)
	{
		res[i] = (int *)calloc(*obstacleGridColSize, sizeof(int));
		res[i][0] = obstacleGrid[i][0] != 1 ? res[i - 1][0] : 0;
		for (j = 1; j < *obstacleGridColSize; j++)
		{
			if (obstacleGrid[i][j] != 1)
				res[i][j] = res[i - 1][j] + res[i][j - 1];
		}
	}
	// printf("res = \n");
	// for (i = 0; i < obstacleGridSize; i++)
	// {
	// 	printf("row%d: ", i);
	// 	printArray(res[i], *obstacleGridColSize);
	// }
	// puts("");
	return res[obstacleGridSize - 1][*obstacleGridColSize - 1];
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("63.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int flag = 0, tmp;
	int n = 10;
	int obstacleGridSize = 0;
	int obstacleGridColSize, cnt;
	int **obstacleGrid = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		obstacleGrid[i] = (int *)calloc(n, sizeof(int));

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
			obstacleGridSize++;
			obstacleGridColSize = cnt;
			cnt = 0;
			flag = 2;
		}
		else if (c == '[' || flag == 1)
		{
			fscanf(pfile, "%d", &(obstacleGrid[obstacleGridSize][cnt]));
			printf("%d", obstacleGrid[obstacleGridSize][cnt]);
			cnt++;
			flag = 1;
		}
	}
	puts("");

	printf("obstacleGrid = \n");
	for (int i = 0; i < obstacleGridSize; i++)
	{
		printf("row%d: ", i);
		printArray(obstacleGrid[i], obstacleGridColSize);
	}

	int res = uniquePathsWithObstacles(obstacleGrid, obstacleGridSize, &obstacleGridColSize);
	printf("res = %d\n", res);
	return 0;
}