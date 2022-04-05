#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *VERSIONS;

void printArray(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d,", nums[i]);
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

// The API isBadVersion is defined for you.
_Bool isBadVersion(int version)
{
	return VERSIONS[version];
}

int firstBadVersion(int n)
{
	int front = 1, rear = n, mid;
	while (front <= rear)
	{
		mid = front + (rear - front) / 2;
		if (!isBadVersion(mid))
			front = mid + 1;
		else // if(isBadVersion(mid))
			rear = mid - 1;
	}
	return front;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("278.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int n, bad;
	printf("input: ");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &n);
	printf(" %d", n);
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &bad);
	printf(" %d", bad);
	puts("");

	printf("n = %d\n", n);
	printf("bad = %d\n", bad);

	VERSIONS = (int *)calloc(n + 1, sizeof(int));
	for (int i = bad; i <= n; i++)
		VERSIONS[i] = 1;
	printf("VERSION = ");
	printArray(VERSIONS, n + 1);

	printf("position = %d\n", firstBadVersion(n));

	return 0;
}