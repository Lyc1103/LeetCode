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

int maxScoreSightseeingPair(int *values, int valuesSize)
{
	int pre_max_score = values[0];
	int max_score = pre_max_score + values[1] - 1;
	int i, tmp;
	for (i = 1; i < valuesSize - 1; i++)
	{
		// Find the maximum values from index_0 to index_i for index_i+1;
		pre_max_score = pre_max_score > (tmp = values[i] + i) ? pre_max_score : tmp;
		// Update the value of max_score by max(max_score, pre_max_score+values[i+1]-(i+1))
		max_score = max_score > (tmp = pre_max_score + values[i + 1] - (i + 1)) ? max_score : tmp;
		// printf("values[%d] = %d, pre_max_score = %d, max_score = %d\n", i, values[i], pre_max_score, max_score);
	}
	return max_score;
}

int main()
{
	int values[100] = {0}, valuesSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("1014.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	printf("input: ");
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c%d", &c, &values[valuesSize]);
		printf("%d ", values[valuesSize]);
		valuesSize++;
	}
	puts("");

	int max_score = maxScoreSightseeingPair(values, valuesSize);
	printf("max_score = %d\n", max_score);

	return 0;
}