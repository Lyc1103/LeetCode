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
		printf("]\n");
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *getRow(int rowIndex, int *returnSize)
{
	*returnSize = 0;
	int *res = (int *)calloc(rowIndex + 1, sizeof(int));
	if (rowIndex == 0)
	{
		res[(*returnSize)++] = 1;
		return res;
	}

	Queue q;
	q.front = -1;
	q.rear = 0;
	q.buffer = (int *)calloc((rowIndex + 4) * (rowIndex + 1) / 2 + 2, sizeof(int));
	// printf("buffer_size = %d\n", (rowIndex + 4) * (rowIndex + 1) / 2 + 2);
	EnQue(&q, 0);
	EnQue(&q, 1);
	int next_level = 0;
	while (next_level <= rowIndex)
	{
		int tmp1 = DeQue(&q), tmp2 = q.buffer[q.front + 1];
		// printf("tmp1 = %d, tmp2 = %d, ", tmp1, tmp2);
		if (tmp1 == 0)
		{
			EnQue(&q, 0);
			next_level++;
		}
		// printf("next_level = %d, q.front = %d, q.rear = %d\n", next_level, q.front, q.rear);
		if (next_level == rowIndex)
			res[(*returnSize)++] = tmp1 + tmp2;
		EnQue(&q, tmp1 + tmp2);
	}

	return res;
}

int main()
{
	int numRows = 0, returnSize;
	int *res = getRow(numRows, &returnSize);

	printArray(res, returnSize, 0);
}