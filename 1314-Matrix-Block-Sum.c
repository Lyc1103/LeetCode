// Reference: https://medium.com/rayonchang/leetcode-medium-1314-matrix-block-sum-9c0caf35f9b9
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
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **matrixBlockSum(int **mat, int matSize, int *matColSize, int k, int *returnSize, int **returnColumnSizes)
{
	int i, j, tmp, tmp_i, tmp_j;
	*returnSize = matSize;
	*returnColumnSizes = (int *)malloc(matSize * sizeof(int));
	int **res = (int **)malloc(matSize * sizeof(int *));
	int **pre_sum = (int **)malloc(matSize * sizeof(int *));
	for (i = 0; i < matSize; i++)
	{
		res[i] = (int *)calloc(*matColSize, sizeof(int));
		pre_sum[i] = (int *)calloc(*matColSize, sizeof(int));
		(*returnColumnSizes)[i] = *matColSize;
	}

	// Calculate pre_sum
	for (i = 0; i < matSize; i++)
	{
		if ((tmp_i = i - 1) >= 0)
			for (j = 0; j < *matColSize; j++)
			{
				if ((tmp_j = j - 1) >= 0)
					pre_sum[i][j] = mat[i][j] + pre_sum[tmp_i][j] + pre_sum[i][tmp_j] - pre_sum[tmp_i][tmp_j];
				else
					pre_sum[i][j] = mat[i][j] + pre_sum[tmp_i][j];
			}
		else
			for (j = 0; j < *matColSize; j++)
			{
				if ((tmp_j = j - 1) >= 0)
					pre_sum[i][j] = mat[i][j] + pre_sum[i][tmp_j];
				else
					pre_sum[i][j] = mat[i][j];
			}
	}
	// puts("pre_sum:");
	// for (i = 0; i < matSize; i++)
	// {
	// 	printf("row %d: ", i);
	// 	printArray(pre_sum[i], *matColSize);
	// }
	// puts("");

	// Calculate result
	int lower_left_cornor_of_block_sum;
	int tmp_r_cor_i;
	int tmp_l_cor_j;
	for (i = 0; i < matSize; i++)
	{
		for (j = 0; j < *matColSize; j++)
		{
			tmp_i = MIN(i + k, matSize - 1);
			tmp_j = MIN(j + k, *matColSize - 1);
			tmp_r_cor_i = i - k - 1;
			tmp_l_cor_j = j - k - 1;
			// printf("i = %d, j = %d\n", i, j);
			// printf("tmp_i = %d, tmp_r_cor_i = %d\n", tmp_i, tmp_r_cor_i);
			// printf("tmp_j = %d, tmp_l_cor_j = %d\n\n", tmp_j, tmp_l_cor_j);
			if (tmp_r_cor_i >= 0 && tmp_l_cor_j >= 0)
			{
				res[i][j] = pre_sum[tmp_i][tmp_j] - pre_sum[tmp_i][tmp_l_cor_j] - pre_sum[tmp_r_cor_i][tmp_j] + pre_sum[tmp_r_cor_i][tmp_l_cor_j];
			}
			else if (tmp_r_cor_i >= 0)
			{
				res[i][j] = pre_sum[tmp_i][tmp_j] - pre_sum[tmp_r_cor_i][tmp_j];
			}
			else if (tmp_l_cor_j >= 0)
			{
				res[i][j] = pre_sum[tmp_i][tmp_j] - pre_sum[tmp_i][tmp_l_cor_j];
			}
			else
			{
				res[i][j] = pre_sum[tmp_i][tmp_j];
			}
		}
	}

	return res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("1314.txt", "r")) == NULL)
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

	int k;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
		{
			fscanf(pfile, " %d", &k);
			printf(" %d", k);
			break;
		}
	}
	puts("");

	printf("mat = \n");
	for (int i = 0; i < matSize; i++)
	{
		printf("row%d: ", i);
		printArray(mat[i], matColSize);
	}

	int returnSize, *returnColSize;
	int **res = matrixBlockSum(mat, matSize, &matColSize, k, &returnSize, &returnColSize);
	printf("res = \n");
	for (int i = 0; i < matSize; i++)
	{
		printf("row%d: ", i);
		printArray(res[i], matColSize);
	}
	free(returnColSize);
	free(res);
	return 0;
}
