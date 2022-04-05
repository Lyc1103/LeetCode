#include <stdio.h>
#include <stdlib.h>

//   Definition for singly-linked list.
struct ListNode
{
	int val;
	struct ListNode *next;
};

struct ListNode *insertLinkListFromHead(struct ListNode *head, int data)
{
	struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
	newNode->val = data;
	if (head == NULL)
		newNode->next = NULL;
	else
		newNode->next = head;
	return newNode;
}

struct ListNode *middleNode(struct ListNode *head)
{
	struct ListNode *ptr = head, *res = head;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		if (ptr != NULL)
		{
			ptr = ptr->next;
			res = res->next;
		}
	}
	return res;
}

void printLinkList(struct ListNode *head)
{
	printf("head -> ");
	struct ListNode *ptr = head;
	while (ptr != NULL)
	{
		printf("%d -> ", ptr->val);
		ptr = ptr->next;
	}
	puts("NULL");
	return;
}

void printLinkListInArray(struct ListNode *head)
{
	printf("[");
	struct ListNode *ptr = head;
	while (ptr->next != NULL)
	{
		printf("%d,", ptr->val);
		ptr = ptr->next;
	}
	printf("%d]\n", ptr->val);
	return;
}

void printArray_int(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d,", nums[i]);
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("876.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int target;
	int nums[100] = {0}, numsSize = 0;
	printf("input: ");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%d", &(nums[numsSize]));
		printf("%d", nums[numsSize]);
		numsSize++;
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
	}
	puts("");

	printf("nums = ");
	printArray_int(nums, numsSize);

	struct ListNode *head = NULL;
	for (int i = numsSize - 1; i >= 0; i--)
	{
		head = insertLinkListFromHead(head, nums[i]);
	}

	printf("Link List: ");
	printLinkList(head);

	struct ListNode *res = middleNode(head);
	printf("middle node val = %d\n", res->val);
	printf("i.e. output: ");
	printLinkListInArray(res);

	return 0;
}