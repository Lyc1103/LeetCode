// Reference: https://hackmd.io/@kenjin/0264_ugly-number-ii
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

#define MIN(a, b) (a < b ? a : b)

int nthUglyNumber(int n)
{
	int *dp = (int *)calloc(n, sizeof(int));
	dp[0] = 1;
	int cntOf2 = 0, cntOf3 = 0, cntOf5 = 0;
	int i, tmp2, tmp3, tmp5, tmp_dp;
	for (i = 1; i < n; i++)
	{
		// printf("cntOf2 = %d, cntOf3 = %d, cntOf5 = %d, ", cntOf2, cntOf3, cntOf5);
		tmp_dp = MIN(MIN((tmp2 = dp[cntOf2] * 2), (tmp3 = dp[cntOf3] * 3)), (tmp5 = dp[cntOf5] * 5));

		// ATTENTION
		if (tmp2 == tmp_dp)
			cntOf2++;
		if (tmp3 == tmp_dp)
			cntOf3++;
		if (tmp5 == tmp_dp)
			cntOf5++;

		dp[i] = tmp_dp;
		// printf("dp[%d] = %d\n", i, dp[i]);
	}
	// printArray(dp, n);

	return dp[n - 1];
}

int main()
{
	int n = 10;
	printf("n-th ugly number = %d\n", nthUglyNumber(n));

	return 0;
}