#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct stackInformation
{
	int top;
	int *nums;
} Stack;

Stack *createStack(int size)
{
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->top = -1;
	sta->nums = (int *)malloc(size * sizeof(int));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	return sta->top == -1 ? 1 : 0;
}

void pushToStack(Stack *sta, int data)
{
	sta->top++;
	sta->nums[sta->top] = data;
	return;
}

void popFromStack(Stack *sta, int *ret_num)
{
	*ret_num = sta->nums[sta->top];
	(sta->top)--;
	return;
}

void printElementsInStack(Stack *sta)
{
	if (isEmptyStack(sta))
	{
		puts("sta: []");
		return;
	}
	printf("sta: [");
	for (int i = 0; i < sta->top; i++)
		printf("%d, ", sta->nums[i]);
	printf("%d]\n", sta->nums[sta->top]);
	return;
}

void freeStack(Stack *sta)
{
	free(sta->nums);
	free(sta);
	return;
}

void DFSFilledGroupWith0(int **isConnected, int isConnectedSize, int input_num, Stack *sta)
{
	isConnected[input_num][input_num] = 0; // represents visited
	pushToStack(sta, input_num);
	int cur_num;
	while (!isEmptyStack(sta))
	{
		popFromStack(sta, &cur_num);
		for (int i = input_num + 1; i < isConnectedSize; i++)
			if (isConnected[cur_num][i] && isConnected[i][i])
			{
				isConnected[i][i] = 0; // represents visited
				pushToStack(sta, i);
			}
	}
	return;
}

int findCircleNum(int **isConnected, int isConnectedSize, int *isConnectedColSize)
{
	int circle_nums = 0;
	Stack *sta = createStack(isConnectedSize);
	for (int i = 0; i < isConnectedSize; i++)
		if (isConnected[i][i])
		{
			DFSFilledGroupWith0(isConnected, isConnectedSize, i, sta);
			circle_nums++;
		}
	return circle_nums;
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
	if (matSize == 0)
		puts("mat:\n    []");
	else
	{
		printf("mat:  ");
		for (int i = 0; i < matColSize; i++)
			printf("  %d", i);
		puts("");
		for (int i = 0; i < matSize; i++)
		{
			printf("    %d [", i);
			for (int j = 0; j < matColSize - 1; j++)
				printf("%2d,", mat[i][j]);
			printf("%2d]\n", mat[i][matColSize - 1]);
		}
	}
	puts("    completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("547.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int isConnectedSize, *isConnectedColSize;
	int **isConnected = dealWithInputFile_forMatrix(pfile, &isConnectedSize, &isConnectedColSize);

	printMatrix_int(isConnected, isConnectedSize, isConnectedColSize[0]);

	printf("\nnumbers of provinces = %d\n", findCircleNum(isConnected, isConnectedSize, isConnectedColSize));
	printMatrix_int(isConnected, isConnectedSize, isConnectedColSize[0]);

	return 0;
}
