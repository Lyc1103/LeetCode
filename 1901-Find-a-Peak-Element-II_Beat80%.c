// Reference: https://leetcode.com/problems/find-a-peak-element-ii/discuss/1833785/100-faster-java-solution
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int findPositionOfMaxElementInARow(int *nums, int numsSize)
{
	int max = 0, i;
	for (i = 1; i < numsSize; i++)
		if (nums[i] > nums[max])
			max = i;
	return max;
}

/*
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findPeakGrid(int **mat, int matSize, int *matColSize, int *returnSize)
{
	int *ret = (int *)malloc(2 * sizeof(int));
	*returnSize = 2;

	int front_row = 0, rear_row = matSize - 1, mid_row;
	while (front_row <= rear_row)
	{
		mid_row = (front_row + rear_row) / 2;
		int row_max_pos = findPositionOfMaxElementInARow(mat[mid_row], matColSize[mid_row]);
		// mid_row is the first row
		if (mid_row == 0)
			if (mat[mid_row][row_max_pos] > mat[mid_row + 1][row_max_pos])
			{
				ret[0] = mid_row;
				ret[1] = row_max_pos;
				return ret;
			}
		// mid_row is the last row
		if (mid_row == matSize - 1)
			if (mat[mid_row][row_max_pos] > mat[mid_row - 1][row_max_pos])
			{
				ret[0] = mid_row;
				ret[1] = row_max_pos;
				return ret;
			}
		// the other conditions
		if (mat[mid_row][row_max_pos] > mat[mid_row + 1][row_max_pos] && mat[mid_row][row_max_pos] > mat[mid_row - 1][row_max_pos])
		{
			ret[0] = mid_row;
			ret[1] = row_max_pos;
			return ret;
		}
		else if (mat[mid_row][row_max_pos] < mat[mid_row + 1][row_max_pos])
			front_row = mid_row + 1;
		else
			rear_row = mid_row - 1;
	}
	ret[0] = ret[1] = -1;
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
