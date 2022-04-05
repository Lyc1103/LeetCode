#include <stdio.h>
#include <stdlib.h>

void printArray(char *str, int strSize)
{
	printf("[");
	for (int i = 0; i < strSize - 1; i++)
	{
		printf("%c", str[i]);
		printf(",");
	}
	printf("%c]\n", str[strSize - 1]);
	return;
}
void printArray_int(int *nums, int numsSize)
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

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

int maximalSquare(char **matrix, int matrixSize, int *matrixColSize)
{
	int i, j, tmp_i, tmp_j;
	char tmp;
	int **buffer = (int **)malloc(matrixSize * sizeof(int *));
	int res = 0;
	for (i = 0; i < matrixSize; i++)
	{
		buffer[i] = (int *)calloc(*matrixColSize, sizeof(int));
		if (matrix[i][0] == '1')
		{
			buffer[i][0] = 1;
			res = 1;
		}
	}
	for (j = 1; j < *matrixColSize; j++)
		if (matrix[0][j] == '1')
		{
			buffer[0][j] = 1;
			res = 1;
		}

	for (i = 1; i < matrixSize; i++)
	{
		for (j = 1; j < *matrixColSize; j++)
		{
			if ((tmp = matrix[i][j]) == '0')
				continue;

			tmp_i = i - 1;
			tmp_j = j - 1;
			if (matrix[tmp_i][tmp_j] == '1' && matrix[tmp_i][j] == '1' && matrix[i][tmp_j] == '1')
				buffer[i][j] = MIN(MIN(buffer[tmp_i][tmp_j], buffer[tmp_i][j]), buffer[i][tmp_j]) + 1;
			else
				buffer[i][j] = 1;
			res = MAX(res, buffer[i][j]);
		}
	}
	printf("buffer = \n");
	for (int i = 0; i < matrixSize; i++)
	{
		printf("row%d: ", i);
		printArray_int(buffer[i], *matrixColSize);
	}
	puts("");

	return res * res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("221.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int flag = 0, tmp;
	int n = 10;
	int matrixSize = 0;
	int matrixColSize, cnt;
	char **matrix = (char **)malloc(n * sizeof(char *));
	for (int i = 0; i < n; i++)
		matrix[i] = (char *)malloc(n * sizeof(char));

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
			matrixSize++;
			matrixColSize = cnt;
			cnt = 0;
			flag = 2;
		}
		else if (c == '[' || flag == 1)
		{
			fscanf(pfile, "\"%c\"", &(matrix[matrixSize][cnt]));
			printf("%c", matrix[matrixSize][cnt]);
			cnt++;
			flag = 1;
		}
	}
	puts("");

	printf("matrix = \n");
	for (int i = 0; i < matrixSize; i++)
	{
		printf("row%d: ", i);
		printArray(matrix[i], matrixColSize);
	}
	puts("");

	printf("max-square = %d\n", maximalSquare(matrix, matrixSize, &matrixColSize));

	return 0;
}