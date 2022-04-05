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

#define MIN(a, b) (a < b ? a : b)

int minimumTotal(int **triangle, int triangleSize, int *triangleColSize)
{
	int i, j, tmp_i;
	for (i = triangleSize - 2; i >= 0; i--)
	{
		tmp_i = i + 1;
		for (j = 0; j < triangleColSize[i]; j++)
			triangle[i][j] += MIN(triangle[tmp_i][j], triangle[tmp_i][j + 1]);
	}
	return triangle[0][0];
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("120.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int flag = 0, tmp;
	int n = 10;
	int triangleSize = 0;
	int *triangleColSize = (int *)calloc(n, sizeof(int));
	int **triangle = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		triangle[i] = (int *)calloc(n, sizeof(int));

	printf("input:\n");
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
		if (c == ']')
		{
			triangleSize++;
			flag = 2;
		}
		else if (c == '[' || flag == 1)
		{
			tmp = triangleColSize[triangleSize];
			fscanf(pfile, "%d", &(triangle[triangleSize][tmp]));
			printf("%d", triangle[triangleSize][tmp]);
			triangleColSize[triangleSize]++;
			flag = 1;
		}
	}
	triangleSize -= 2;
	puts("");

	printf("triangle = \n");
	for (int i = 0; i < triangleSize; i++)
	{
		printf("row%d: ", i);
		printArray(triangle[i], triangleColSize[i]);
	}
	printf("triangleColumnSize = ");
	printArray(triangleColSize, triangleSize);

	int res = minimumTotal(triangle, triangleSize, triangleColSize);
	printf("res_triangle = \n");
	for (int i = 0; i < triangleSize; i++)
	{
		printf("row%d: ", i);
		printArray(triangle[i], triangleColSize[i]);
	}
	printf("res = %d\n", res);

	return 0;
}
