#include <stdio.h>
#include <stdlib.h>

_Bool isHappy(int n)
{
	int *buffer = (int *)calloc(10, sizeof(int));
	while (1)
	{
		int sum = 0, remainder = n % 10;
		// printf("n = %d, remainder = %d\n", n, remainder);

		if (n / 10 == 0 && remainder == 1)
			return 1;
		else if (n / 10 == 0 && remainder != 1)
		{
			if (buffer[remainder])
				return 0;
			else
			{
				buffer[remainder] = 1;
				// printf("// buffer[%d] = 1\n", remainder);
			}
		}

		// printf("sum = %d^2", remainder);
		while (n / 10 != 0 || remainder != 0)
		{
			sum += remainder * remainder;
			n /= 10;
			remainder = n % 10;
			// printf(" + %d^2", remainder);
		}
		// printf(" = %d\n", sum);
		n = sum;
	}
}

int main()
{
	int n = 19;
	if (isHappy(n))
		puts("true");
	else
		puts("false");

	return 0;
}