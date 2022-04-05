#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

typedef struct stack
{
	int *index;
	int top;
} Stack;

void Push(Stack *sta, int index)
{
	sta->top++;
	sta->index[sta->top] = index;
}

int Pop(Stack *sta)
{
	sta->top--;
	return sta->index[sta->top + 1];
}

int jump(int *nums, int numsSize)
{
	if (numsSize == 1)
		return 0;
	if (nums[0] >= numsSize - 1)
		return 1;
	Stack S, T;
	S.top = -1;
	S.index = (int *)calloc(numsSize, sizeof(int));
	T.top = -1;
	T.index = (int *)calloc(numsSize, sizeof(int));
	Push(&T, 0);

	int farest = 0, farest_tmp;
	int index, cnt = 1, i;
	_Bool flag = 0;
	while (S.top != -1 || T.top != -1)
	{

		while (T.top != -1)
		{
			index = Pop(&T);
			printf("index = %d:\n", index);

			for (i = index + 1; i <= index + nums[index] && i < numsSize - 1; i++)
			{
				if (i + nums[i] >= numsSize - 1)
					return cnt + 1;
				if (i > farest)
				{
					Push(&S, i);
					farest = farest > i ? farest : i;
					printf("%d ", i);
				}
			}
			puts("\n");
		}

		cnt++;

		while (S.top != -1)
		{
			index = Pop(&S);
			Push(&T, index);
		}
	}

	return 0;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("45.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	printf("input: ");
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c%d", &c, &nums[numsSize]);
		printf("%d ", nums[numsSize]);
		numsSize++;
	}
	puts("");

	int min_step = jump(nums, numsSize);
	printf("min_step = %d\n", min_step);

	return 0;
}