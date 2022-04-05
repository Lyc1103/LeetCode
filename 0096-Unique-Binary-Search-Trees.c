#include <stdio.h>

int numTrees(int n)
{
    long long res = 1;
    int denominator = 1;
    int i, j, cnt = n;
    for (i = 0, j = 1; i < n; i++, j++)
    {
        res *= 2;
        cnt--;
        i++;
        if (i < n)
            res *= (2 * n - i);
    }
    for (i = 1; i <= cnt; i++)
    {
        denominator *= i;
    }
    res = (res / denominator) / (n + 1);
    return res;
}

int main()
{
    int n = 1;
    printf("%d\n", numTrees(n));
    return 0;
}