#include <stdio.h>
#include <stdlib.h>

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

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n)
{
	int *tmp = (int *)calloc(m, sizeof(int));
	for (int i = 0; i < m; i++)
		tmp[i] = nums1[i];
	// printArray(tmp, m);
	// printArray(nums2, n);
	int i, pos1 = 0, pos2 = 0;
	for (i = 0; i < nums1Size && pos1 < m && pos2 < n; i++)
	{
		if (tmp[pos1] < nums2[pos2])
			nums1[i] = tmp[pos1++];
		else
			nums1[i] = nums2[pos2++];
	}
	while (pos1 < m)
		nums1[i++] = tmp[pos1++];
	while (pos2 < n)
		nums1[i++] = nums2[pos2++];

	free(tmp);
	return;
}

int main()
{
	// int nums1[6] = {1, 2, 3, 0, 0, 0}, m = 3;
	// int nums2[3] = {2, 5, 6}, n = 3;
	int nums1[1] = {0}, m = 0;
	int nums2[1] = {1}, n = 1;
	merge(nums1, 1, 0, nums2, 1, 1);
	printArray(nums1, m + n);
	return 0;
}