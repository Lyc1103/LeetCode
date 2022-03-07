#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

_Bool canJump(int *nums, int numsSize)
{
	if (numsSize == 1)
		return 1;
	if (numsSize == 2)
	{
		if (nums[0] > 0)
			return 1;
		else
			return 0;
	}
	int farest_prepos = nums[0];
	int farest_curpos;
	if (nums[0] == 0)
		return 0;
	else
		farest_curpos = farest_prepos > nums[1] + 1 ? farest_prepos : nums[1] + 1;
	if (numsSize == 3 && farest_curpos >= numsSize - 1)
		return 1;
	printf("nums[1] = %d, farest_curpos = %d, farest_prepos = %d\n", nums[1], farest_curpos, farest_prepos);

	int16_t i;
	int tmp;
	for (i = 2; i < numsSize - 1; i++)
	{
		if (i > farest_curpos)
			return 0;
		tmp = farest_curpos;
		farest_curpos = farest_curpos > nums[i] + i ? farest_curpos : nums[i] + i;
		farest_prepos = tmp;
		printf("nums[%d] = %d, farest_curpos = %d, farest_prepos = %d\n", i, nums[i], farest_curpos, farest_prepos);
		if (farest_curpos >= numsSize - 1)
			return 1;
	}
	return 0;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("55.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	printf("input: ");
	while (!feof(pfile))
	{
		fscanf(pfile, "%d", &nums[numsSize]);
		printf("%d ", nums[numsSize]);
		numsSize++;
	}
	puts("");

	if (canJump(nums, numsSize))
		puts("true");
	else
		puts("false");

	return 0;
}