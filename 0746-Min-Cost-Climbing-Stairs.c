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

int minCostClimbingStairs(int *cost, int costSize)
{
	if (costSize == 2)
		return cost[0] < cost[1] ? cost[0] : cost[1];

	int pre0 = cost[0], pre1 = cost[1], tmp;
	for (int16_t i = 2; i < costSize; i++)
	{
		tmp = pre1;
		pre1 = cost[i] + (pre0 < pre1 ? pre0 : pre1);
		pre0 = tmp;
	}

	return pre0 < pre1 ? pre0 : pre1;
}

int main()
{
	int cost[1000] = {0}, costSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("746.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%d", &cost[costSize]);
		printf("%d ", cost[costSize]);
		costSize++;
	}
	puts("");

	fclose(pfile);
	int res = minCostClimbingStairs(cost, costSize);
	printf("min-cost = %d\n", res);
}