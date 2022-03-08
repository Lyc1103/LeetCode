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

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int maxProduct(int *nums, int numsSize)
{
	int res = nums[0];
	int max_pos_product = nums[0];
	int min_neg_product = nums[0];
	int i;
	for (i = 1; i < numsSize; i++)
	{
		if (nums[i] < 0)
			swap(&max_pos_product, &min_neg_product);
		max_pos_product = nums[i] > max_pos_product * nums[i] ? nums[i] : max_pos_product * nums[i];
		min_neg_product = nums[i] < min_neg_product * nums[i] ? nums[i] : min_neg_product * nums[i];
		res = res > max_pos_product ? res : max_pos_product;
		printf("max_pos_prod = %d, min_neg_prod = %d, res = %d\n", max_pos_product, min_neg_product, res);
	}
	return res;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("152.txt", "r")) == NULL)
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

	int max_prod = maxProduct(nums, numsSize);
	printf("max_prod = %d\n", max_prod);

	return 0;
}