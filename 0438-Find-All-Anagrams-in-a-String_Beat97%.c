#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
void printArray_int(int *nums, int numsSize);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findAnagrams(char *s, char *p, int *returnSize)
{
	int s_len = strlen(s), p_len = strlen(p);
	*returnSize = 0;
	int *ret = (int *)malloc(s_len * sizeof(int));
	if (p_len > s_len)
		return ret;

	// first window
	int i;
	int p_char_ctr_buffer[26] = {0};
	int all_zero_buffer[26] = {0};
	for (i = 0; i < p_len; i++)
	{
		p_char_ctr_buffer[p[i] - 'a'] += 1;
		p_char_ctr_buffer[s[i] - 'a'] -= 1;
	}
	// check memory method 1
	if (memcmp(p_char_ctr_buffer, all_zero_buffer, sizeof(p_char_ctr_buffer)) == 0)
	{
		ret[*returnSize] = 0;
		*returnSize += 1;
	}
	// check memory method 2
	// for (i = 0; i < 26; i++)
	// 	if (p_char_ctr_buffer[i] != 0)
	// 		break;
	// if (i == 26)
	// {
	// 	ret[*returnSize] = 0;
	// 	*returnSize += 1;
	// }

	// sliding window
	for (int front = 0, rear = p_len; rear < s_len; front++, rear++)
	{
		p_char_ctr_buffer[s[front] - 'a'] += 1;
		p_char_ctr_buffer[s[rear] - 'a'] -= 1;
		// check memory method 1
		if (memcmp(p_char_ctr_buffer, all_zero_buffer, sizeof(p_char_ctr_buffer)) == 0)
		{
			ret[*returnSize] = front + 1;
			*returnSize += 1;
		}
		// check memory method 2
		// for (i = 0; i < 26; i++)
		// 	if (p_char_ctr_buffer[i] != 0)
		// 		break;
		// if (i == 26)
		// {
		// 	ret[*returnSize] = front + 1;
		// 	*returnSize += 1;
		// }
	}
}

return ret;
}

char *dealWithInputFile_ForString(FILE *pfile, int *strSize)
{
	char c;
	char *str = (char *)malloc(50 * sizeof(char));
	*strSize = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '"')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '"')
			break;
		str[*strSize] = c;
		(*strSize)++;
	}
	str[*strSize] = '\0';
	return str;
}

void printArray_char(char *str, int strSize)
{
	printf("\"");
	for (int i = 0; i < strSize - 1; i++)
	{
		printf("%c", str[i]);
	}
	if (strSize == 0)
		puts("\"");
	else
		printf("%c\"", str[strSize - 1]);
	puts(" //  completely print.");
	return;
}

void printArray_int(int *nums, int numsSize)
{
	if (numsSize == 0)
	{
		puts("[]");
		return;
	}
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		if (nums[i] == INT_MIN)
			printf("null,");
		else
			printf("%d,", nums[i]);
	}
	printf("%d]", nums[numsSize - 1]);
	puts(" // completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("438.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int sSize, pSize;
	printf("input: ");
	char *s = dealWithInputFile_ForString(pfile, &sSize);
	char *p = dealWithInputFile_ForString(pfile, &pSize);
	puts("");
	printf("s = ");
	printArray_char(s, sSize);
	printf("p = ");
	printArray_char(p, pSize);

	int returnSize;
	int *ret = findAnagrams(s, p, &returnSize);
	printf("ret: ");
	printArray_int(ret, returnSize);

	return 0;
}