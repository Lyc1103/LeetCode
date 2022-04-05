#include <stdio.h>
#include <stdlib.h>

void printArray(int *nums, int numsSize, _Bool oneline)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d", nums[i]);
		printf(",");
	}
	printf("%d", nums[numsSize - 1]);

	if (oneline)
		printf("],");
	else
		printf("]]\n");
	return;
}

typedef struct queue
{
	int front, rear;
	int *buffer;
} Queue;

void EnQue(Queue *q, int data)
{
	q->buffer[(q->rear)++] = data;
}

int DeQue(Queue *q)
{
	if (q->front >= q->rear)
	{
		puts("Que is empty");
		exit(0);
	}
	else
		return q->buffer[++(q->front)];
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **generate(int numRows, int *returnSize, int **returnColumnSizes)
{
	*returnSize = numRows;
	*returnColumnSizes = (int *)calloc(numRows, sizeof(int));
	int **res = (int **)calloc(numRows + 1, sizeof(int *));
	for (int i = 0; i < numRows; i++)
	{
		(*returnColumnSizes)[i] = i + 1;
		res[i] = (int *)calloc(i + 1, sizeof(int));
	}
	res[numRows] = (int *)calloc(1, sizeof(int));

	Queue q;
	q.front = -1;
	q.rear = 0;
	q.buffer = (int *)calloc((numRows + 3) * numRows / 2 + 2, sizeof(int));
	EnQue(&q, 0);
	EnQue(&q, 1);
	res[0][0] = 1;
	int next_level = 0, cnt = 0;
	while (next_level < numRows)
	{
		int tmp1 = DeQue(&q), tmp2 = q.buffer[q.front + 1];
		if (tmp1 == 0)
		{
			EnQue(&q, 0);
			next_level++;
			cnt = 0;
		}
		res[next_level][cnt] = tmp1 + tmp2;
		EnQue(&q, res[next_level][cnt]);
		cnt++;
	}

	return res;
}

int main()
{
	int numRows = 10, returnSize, *returnColumnSize;
	int **res = generate(numRows, &returnSize, &returnColumnSize);

	printf("[");
	for (int i = 0; i < returnSize - 1; i++)
	{
		printArray(res[i], returnColumnSize[i], 1);
	}
	printArray(res[returnSize - 1], returnColumnSize[returnSize - 1], 0);
}