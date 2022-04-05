#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

// Definition for singly-linked list.
struct ListNode
{
	int val;
	struct ListNode *next;
};

struct ListNode *insertListNode(struct ListNode *head, int value)
{
	struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
	newNode->val = value;
	if (head == NULL)
		newNode->next = NULL;
	else
		newNode->next = head;
	return newNode;
}

void printLinkLists(struct ListNode *head)
{
	struct ListNode *tmp = head;
	while (tmp != NULL)
	{
		printf("%d -> ", tmp->val);
		tmp = tmp->next;
	}
	printf("NULL\n");
}

struct ListNode *reverseList(struct ListNode *list)
{
	struct ListNode *tmp = list, *newlist = NULL;
	while (tmp != NULL)
	{
		newlist = insertListNode(newlist, tmp->val);
		tmp = tmp->next;
	}
	return newlist;
}

struct ListNode *deleteDuplicates(struct ListNode *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	struct ListNode *tmp = reverseList(head);
	// printLinkLists(tmp);
	struct ListNode *ret = NULL;
	int pre_val = tmp->val;
	int cnt = 1;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		// printf("pre_val = %d, cnt = %d, tmp_val = %d\n", pre_val, cnt, tmp->val);
		if (tmp->val != pre_val)
		{
			if (cnt == 1)
				ret = insertListNode(ret, pre_val);
			if (tmp->next == NULL)
				ret = insertListNode(ret, tmp->val);
			pre_val = tmp->val;
			cnt = 1;
			tmp = tmp->next;
		}
		else
		{
			cnt++;
			tmp = tmp->next;
		}
	}
	return ret;
}

struct ListNode *dealWithInputFile_ForLinkList(FILE *pfile, int *nums, int *numsSize)
{
	char c;
	int sum = 0, flag = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
		{
			if (flag)
			{
				nums[*numsSize] = sum;
				(*numsSize)++;
			}
			break;
		}
		if (c == ',')
		{
			nums[*numsSize] = sum;
			(*numsSize)++;
			sum = 0;
		}
		else
		{
			sum = sum * 10 + (c - '0');
			flag = 1;
		}
	}
	puts("");
	printf("nums: ");
	printArray_int(nums, *numsSize);

	struct ListNode *head = NULL;
	for (int i = *numsSize - 1; i >= 0; i--)
		head = insertListNode(head, nums[i]);
	puts("// Input File completed.");
	return head;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("82.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums[20] = {0}, numsSize = 0;
	struct ListNode *head = dealWithInputFile_ForLinkList(pfile, nums, &numsSize);
	printf("original link list: ");
	printLinkLists(head);
	head = deleteDuplicates(head);
	printf("duplicates-deleted link list: ");
	printLinkLists(head);
	return 0;
}