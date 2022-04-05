#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

_Bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{
	for (int front = 0, rear = matrixSize * matrixColSize[0], mid; front < rear;)
	{
		mid = (front + rear) / 2;
		if (matrix[mid / matrixColSize[0]][mid % matrixColSize[0]] == target)
			return 1;
		else if (matrix[mid / matrixColSize[0]][mid % matrixColSize[0]] <= target)
			front = mid + 1;
		else
			rear = mid;
	}
	return 0;
}

int **dealWithInputFile_forMatrix(FILE *pfile, int *matSize, int **matColSize)
{
	int size = 10;
	int **mat = (int **)malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++)
	{
		mat[i] = (int *)malloc(size * sizeof(int));
		*matColSize = (int *)calloc(size, sizeof(int));
	}
	char c;
	int ctr = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		while (!feof(pfile))
		{
			fscanf(pfile, "%c", &c);
			printf("%c", c);
			if (c == '[')
				break;
		}
		while (!feof(pfile))
		{
			fscanf(pfile, "%d", &mat[*matSize][ctr]);
			printf("%d", mat[*matSize][ctr]);
			ctr++;
			fscanf(pfile, "%c", &c);
			printf("%c", c);
			if (c == ']')
			{
				(*matColSize)[*matSize] = ctr;
				(*matSize)++;
				ctr = 0;
				break;
			}
		}
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
	}
	return mat;
}

void printMatrix_int(int **mat, int matSize, int matColSize)
{
	for (int i = 0; i < matSize; i++)
	{
		printf("  row%d = [", i);
		for (int j = 0; j < matColSize - 1; j++)
			printf("%2d,", mat[i][j]);
		printf("%2d]\n", mat[i][matColSize - 1]);
	}
	puts("  completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("74.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int matSize, *matColSize, target;
	int **mat = dealWithInputFile_forMatrix(pfile, &matSize, &matColSize);
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &target);
	printf(" %d", target);
	puts("");

	puts("matrix:");
	printMatrix_int(mat, matSize, matColSize[0]);
	printf("target = %d\n", target);

	if (searchMatrix(mat, matSize, matColSize, target))
		puts("true");
	else
		puts("false");

	return 0;
}
