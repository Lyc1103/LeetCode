#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **mat, int matSize, int matColSize)
{
	for (int i = 0; i < matSize; i++)
	{
		printf("  row%d = [", i);
		for (int j = 0; j < matColSize - 1; j++)
			printf("%d,", mat[i][j]);
		printf("%d]\n", mat[i][matColSize - 1]);
	}
	return;
}

int DFSFillWater(int **grid, int gridSize, int *gridColSize, int x, int y, int ctr)
{
	if (x < 0 || x >= gridSize || y < 0 || y >= *gridColSize)
		return ctr;
	if (grid[x][y] == 1)
	{
		ctr++;
		grid[x][y] = 0;
		ctr = DFSFillWater(grid, gridSize, gridColSize, x - 1, y, ctr);
		ctr = DFSFillWater(grid, gridSize, gridColSize, x + 1, y, ctr);
		ctr = DFSFillWater(grid, gridSize, gridColSize, x, y - 1, ctr);
		ctr = DFSFillWater(grid, gridSize, gridColSize, x, y + 1, ctr);
	}
	return ctr;
}

int maxAreaOfIsland(int **grid, int gridSize, int *gridColSize)
{
	int i, j, res = 0, ctr;
	for (i = 0; i < gridSize; i++)
		for (j = 0; j < *gridColSize; j++)
			if (grid[i][j] == 1)
			{
				ctr = DFSFillWater(grid, gridSize, gridColSize, i, j, 0);
				res = res > ctr ? res : ctr;
			}
	return res;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("695.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int **grid = (int **)calloc(100, sizeof(int *));
	for (int i = 0; i < 10; i++)
		grid[i] = (int *)calloc(100, sizeof(int));
	int gridSize = 0, gridColSize, cnt = 0;
	printf("input: ");
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
		if (c == '[')
		{
			while (!feof(pfile))
			{
				fscanf(pfile, "%d", &grid[gridSize][cnt]);
				printf("%d", grid[gridSize][cnt]);
				cnt++;
				fscanf(pfile, "%c", &c);
				printf("%c", c);
				if (c == ']')
				{
					gridSize++;
					gridColSize = cnt;
					cnt = 0;
					break;
				}
			}
		}
		else if (c == ']')
			break;
	}
	puts("");

	puts("grid =");
	printMatrix(grid, gridSize, gridColSize);

	printf("max area = %d\n", maxAreaOfIsland(grid, gridSize, &gridColSize));
	puts("filled grid =");
	printMatrix(grid, gridSize, gridColSize);

	for (int i = 0; i < 100; i++)
		free(grid[i]);
	free(grid);
	return 0;
}