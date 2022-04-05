#include <stdio.h>
#include <math.h>

int mySqrt(int x)
{
	if (x == 0)
		return 0;
	double a = 0, b = x, half;
	while ((int)a < (int)b)
	{
		half = (a + b) / 2;
		if (half * half > x)
			b = half;
		else if (half * half < x)
		{
			a = half;
		}
		else
			return half;
	}
	return (int)half;
}

int main()
{
	int x = 8;
	int sqrtx = mySqrt(x);
	printf("sqrt(x) = %d\n", sqrtx);
	return 0;
}