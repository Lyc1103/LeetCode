#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int strStr(char *haystack, char *needle)
{
	// KMP algorithm
	int nee_len = strlen(needle);
	if (nee_len == 0)
		return 0;
	int *prefix = (int *)calloc(nee_len + 1, sizeof(int));
	prefix[1] = 0;
	int k = 0;
	for (int i = 2; i <= nee_len; i++)
	{
		while (k > 0 && needle[k] != needle[i - 1])
			k = prefix[k];
		if (needle[k] == needle[i - 1])
			k += 1;
		prefix[i] = k;
	}

	int hay_len = strlen(haystack);
	int *kmp_arr = (int *)calloc(hay_len + 1, sizeof(int));
	k = 0;
	for (int i = 1; i <= hay_len; i++)
	{
		while (k > 0 && needle[k] != haystack[i - 1])
			k = prefix[k];
		if (needle[k] == haystack[i - 1])
			k += 1;
		if (k == nee_len)
			return (i - 1) - nee_len + 1;
	}
	return -1;
}

int main()
{
	char haystack[50001] = "aaaa", needle[50001] = "bba";
	int position = strStr(haystack, needle);
	printf("first position = %d\n", position);
}