#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *plusOne(int *digits, int digitsSize, int *returnSize)
{
	int i = digitsSize - 1, flag = 0;

	while (i >= 0)
	{
		if (digits[i] != 9)
		{
			flag = 1;
			break;
		}
		i--;
	}
	if (flag == 1)
	{
		*returnSize = digitsSize;
		int *res = (int *)calloc(digitsSize, sizeof(int));
		res[i] = digits[i] + 1;
		for (int j = i - 1; j >= 0; j--)
		{
			res[j] = digits[j];
		}
		return res;
	}
	else
	{
		*returnSize = digitsSize + 1;
		int *res = (int *)calloc(digitsSize + 1, sizeof(int));
		res[0] = 1;
		return res;
	}
}

int main()
{
	int digits[1] = {9};
	int digitsSize = 1;
	int returnSize;
	int *res = plusOne(digits, digitsSize, &returnSize);
	printf("returnSize = %d\n", returnSize);
	printf("[");
	for (int i = 0; i < returnSize; i++)
	{
		printf("%d,", res[i]);
	}
	printf("]\n");
	return 0;
}