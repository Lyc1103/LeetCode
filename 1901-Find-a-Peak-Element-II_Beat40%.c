#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void recursiveBinarySearch(int **mat, int matSize, int matColSize, int front, int rear, int *ret, int *flag)
{
	if (*flag || front > rear)
		return;
	int mid = (front + rear) >> 2;
	int x = mid / matColSize;
	int y = mid % matColSize;
	printf("x = %d, y = %d, mat[%d][%d] = %d\n", x, y, x, y, mat[x][y]);
	int ctr = 0;
	if ((x - 1 < 0 || mat[x][y] > mat[x - 1][y]) && (x + 1 >= matSize || mat[x][y] > mat[x + 1][y]) && (y - 1 < 0 || mat[x][y] > mat[x][y - 1]) && (y + 1 >= matColSize || mat[x][y] > mat[x][y + 1]))
	{
		*flag = 1;
		ret[0] = x;
		ret[1] = y;
		return;
	}
	recursiveBinarySearch(mat, matSize, matColSize, front, mid - 1, ret, flag);
	recursiveBinarySearch(mat, matSize, matColSize, mid + 1, rear, ret, flag);
}

/*
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findPeakGrid(int **mat, int matSize, int *matColSize, int *returnSize)
{
	int i, j, x, y;
	int front, rear, mid, ctr, flag = 0;
	_Bool dir = 0;
	int *ret = (int *)malloc(2 * sizeof(int));
	*returnSize = 2;
	recursiveBinarySearch(mat, matSize, matColSize[0], 0, matSize * matColSize[0] - 1, ret, &flag);
	return ret;
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
	puts("");
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

void printArray_int(int *nums, int numsSize)
{
	if (numsSize == 0)
	{
		puts("[]");
		return;
	}
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		if (nums[i] == INT_MIN)
			printf("null,");
		else
			printf("%d,", nums[i]);
	}
	printf("%d]", nums[numsSize - 1]);
	puts(" // completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("1901.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int matSize = 0, *matCloSize;
	int **mat = dealWithInputFile_forMatrix(pfile, &matSize, &matCloSize);
	puts("matrix = ");
	printMatrix_int(mat, matSize, matCloSize[0]);

	int returnSize;
	int *ret = findPeakGrid(mat, matSize, matCloSize, &returnSize);
	printf("peak position = ");
	printArray_int(ret, returnSize);

	return 0;
}
