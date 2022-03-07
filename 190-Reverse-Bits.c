#include <stdio.h>
#include <stdint.h>

uint32_t reverseBits(uint32_t n)
{
	uint32_t res = 0, cmp = 0;
	for (int i = 0; i < 32; i++)
	{
		res = (res << 1) | (n & 1);
		// printf("n = %x, res = %x, %u\n", n & 1, res, res);
		n = n >> 1;
	}
	return res;
}

int main()
{
	uint32_t n = 4294967293;
	uint32_t res = reverseBits(n);
	printf("%u\n", res);

	return 0;
}