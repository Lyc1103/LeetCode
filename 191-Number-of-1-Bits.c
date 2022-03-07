#include <stdio.h>
#include <stdint.h>

int hammingWeight(uint32_t n)
{
	int res = 0;
	while ((n | 0) != 0)
	{
		res += (n & 1);
		// printf("n = %x, res = %x, %u\n", n & 1, res, res);
		n = n >> 1;
	}
	return res;
}

int main()
{
	uint32_t n = 4294967293;
	int res = hammingWeight(n);
	printf("num of bits = %d\n", res);

	return 0;
}