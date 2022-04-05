#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d,", nums[i]);
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

typedef struct
{
	int *data;
	int top;
} Stack;

Stack *createStack(int size)
{
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->data = (int *)calloc(size + 1, sizeof(int));
	sta->top = -1;
	return sta;
}

void pushToStack(Stack *sta, int data)
{
	sta->top++;
	sta->data[sta->top] = data;
	return;
}

int popFromStack(Stack *sta)
{
	return sta->data[(sta->top)--];
}

int topOfStack(Stack *sta)
{
	return sta->data[sta->top];
}

int isEmptyStack(Stack *sta)
{
	if (sta->top >= 0)
		return 0;
	return 1;
}

void freeStack(Stack *sta)
{
	free(sta->data);
	free(sta);
}

int trap(int *height, int heightSize)
{
	if (heightSize <= 2)
		return 0;

	// monotonic stack
	Stack *s = createStack(heightSize);
	int i, top, res = 0;
	int pre_peak, peak_pos;
	int valley;
	for (i = 0; i < heightSize; i++)
	{
		// printf("height[%d] = %d\n", i, height[i]);
		if (isEmptyStack(s) && height[i] == 0)
			continue;

		if (!isEmptyStack(s))
		{
			top = height[topOfStack(s)];
			if (height[i] > top)
			{
				valley = height[popFromStack(s)];
				while (!isEmptyStack(s))
				{
					pre_peak = height[(peak_pos = popFromStack(s))];
					// printf("// pre_peak = %d, valley = %d\n", pre_peak, valley);
					if (pre_peak > height[i])
					{
						pushToStack(s, peak_pos);
						res += (i - peak_pos - 1) * (height[i] - valley);
						// printf("// res = %d\n", res);
						break;
					}
					else
					{
						res += (i - peak_pos - 1) * (pre_peak - valley);
						valley = pre_peak;
						// printf("// res = %d\n", res);
					}
				}
			}
		}
		pushToStack(s, i);
		// if (!isEmptyStack(s))
		// {
		// 	printf("stack s: ");
		// 	printArray(s->data, (s->top) + 1);
		// }
		// puts("");
	}

	freeStack(s);
	return res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("42.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int flag = 0;
	int height[100] = {0}, heightSize = 0;
	printf("input:\n");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
		{
			flag = 2;
			break;
		}
		else if (c == '[' || flag == 1)
		{
			fscanf(pfile, "%d", &(height[heightSize]));
			printf("%d", height[heightSize]);
			heightSize++;
			flag = 1;
		}
	}
	puts("");

	printf("height = ");
	printArray(height, heightSize);

	int res = trap(height, heightSize);
	printf("trap = %d\n", res);

	return 0;
}