#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (a > b ? a : b)

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

int maxArea(int *height, int heightSize)
{
	int positions[2];
	positions[0] = 0;
	positions[1] = heightSize - 1;
	int flag = height[0] < height[heightSize - 1] ? 0 : 1; // store the situation of smaller height of left and right position.
	int max_area = height[positions[flag]] * (positions[1] - positions[0]);

	for (int front = 1, rear = heightSize - 2; front <= rear;)
	{
		if (flag == 0) // left height is smaller
		{
			while (front <= rear && height[positions[0]] > height[front])
				front++;
			positions[0] = front;
			front++;
		}
		else // right height is smallar
		{
			while (front <= rear && height[positions[1]] > height[rear])
				rear--;
			positions[1] = rear;
			rear--;
		}
		flag = height[positions[0]] < height[positions[1]] ? 0 : 1;
		max_area = MAX(max_area, height[positions[flag]] * (positions[1] - positions[0]));
	}

	return max_area;
}

int *dealWithInputFile_ForNums(FILE *pfile, int *numsSize)
{
	char c;
	int sum = 0, flag = 0;
	*numsSize = 0;
	int *nums = (int *)malloc(50 * sizeof(int));
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
			if (flag)
			{
				nums[*numsSize] = sum;
				(*numsSize)++;
			}
			break;
		}
		if (c == ',')
		{
			nums[*numsSize] = sum;
			(*numsSize)++;
			sum = 0;
		}
		else
		{
			sum = sum * 10 + (c - '0');
			flag = 1;
		}
	}
	return nums;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("11.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int heightSize;
	int *height = dealWithInputFile_ForNums(pfile, &heightSize);
	puts("");

	printf("height = ");
	printArray(height, heightSize);

	printf("maximum area = %d\n", maxArea(height, heightSize));

	return 0;
}