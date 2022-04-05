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

typedef struct
{
	int **pre_sum;
} NumMatrix;

NumMatrix *numMatrixCreate(int **matrix, int matrixSize, int *matrixColSize)
{
	int i, j, tmp_i, tmp_j, **ptr;
	NumMatrix *mat = (NumMatrix *)malloc(sizeof(NumMatrix));

	// Calculate mat->pre_sum
	mat->pre_sum = (int **)malloc(matrixSize * sizeof(int *));
	for (i = 0; i < matrixSize; i++)
	{
		mat->pre_sum[i] = (int *)calloc(*matrixColSize, sizeof(int));
		ptr = mat->pre_sum;
		if ((tmp_i = i - 1) >= 0)
		{
			for (j = 0; j < *matrixColSize; j++)
			{

				if ((tmp_j = j - 1) >= 0)
					ptr[i][j] = matrix[i][j] + ptr[tmp_i][j] + ptr[i][tmp_j] - ptr[tmp_i][tmp_j];
				else
					ptr[i][j] = matrix[i][j] + ptr[tmp_i][j];
			}
		}
		else
		{
			for (j = 0; j < *matrixColSize; j++)
			{
				if ((tmp_j = j - 1) >= 0)
					ptr[i][j] = matrix[i][j] + ptr[i][tmp_j];
				else
					ptr[i][j] = matrix[i][j];
			}
		}
	}
	puts("mat->pre_sum:");
	for (i = 0; i < matrixSize; i++)
	{
		printf("row %d: ", i);
		printArray(mat->pre_sum[i], *matrixColSize);
	}
	puts("");
	return mat;
}

int numMatrixSumRegion(NumMatrix *obj, int row1, int col1, int row2, int col2)
{
	int tmp_i = row1 - 1, tmp_j = col1 - 1;
	if (tmp_i >= 0 && tmp_j >= 0)
		return obj->pre_sum[row2][col2] - obj->pre_sum[row2][tmp_j] - obj->pre_sum[tmp_i][col2] + obj->pre_sum[tmp_i][tmp_j];
	else if (tmp_i >= 0)
		return obj->pre_sum[row2][col2] - obj->pre_sum[tmp_i][col2];
	else if (tmp_j >= 0)
		return obj->pre_sum[row2][col2] - obj->pre_sum[row2][tmp_j];
	else
		return obj->pre_sum[row2][col2];
}

void numMatrixFree(NumMatrix *obj)
{
	free(obj->pre_sum);
	free(obj);
	return;
}

/**
 * Your NumMatrix struct will be instantiated and called as such:
 * NumMatrix* obj = numMatrixCreate(matrix, matrixSize, matrixColSize);
 * int param_1 = numMatrixSumRegion(obj, row1, col1, row2, col2);

 * numMatrixFree(obj);
*/

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("304.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int flag = 0, tmp;
	int n = 10;
	int matSize = 0;
	int matColSize, cnt;
	int **mat = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		mat[i] = (int *)calloc(n, sizeof(int));

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
			matSize++;
			matColSize = cnt;
			cnt = 0;
			flag = 2;
		}
		else if (c == '[' || flag == 1)
		{
			fscanf(pfile, "%d", &(mat[matSize][cnt]));
			printf("%d", mat[matSize][cnt]);
			cnt++;
			flag = 1;
		}
	}
	puts("");

	printf("mat = \n");
	for (int i = 0; i < matSize; i++)
	{
		printf("row%d: ", i);
		printArray(mat[i], matColSize);
	}

	NumMatrix *num_mat = numMatrixCreate(mat, matSize, &matColSize);
	printf("sumOfRegion((%d, %d), (%d, %d)) = %d\n", 2, 1, 4, 3, numMatrixSumRegion(num_mat, 2, 1, 4, 3));
	printf("sumOfRegion((%d, %d), (%d, %d)) = %d\n", 1, 1, 2, 2, numMatrixSumRegion(num_mat, 1, 1, 2, 2));
	printf("sumOfRegion((%d, %d), (%d, %d)) = %d\n", 1, 2, 2, 4, numMatrixSumRegion(num_mat, 1, 2, 2, 4));
	numMatrixFree(num_mat);
	return 0;
}