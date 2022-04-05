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

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
	struct ListNode *dummy = (struct ListNode *)malloc(sizeof(struct ListNode));
	dummy->next = head;
	struct ListNode *ptr = dummy, *nth_ptr = dummy;
	for (int i = 0; i <= n; i++)
		ptr = ptr->next;
	while (ptr != NULL)
	{
		nth_ptr = nth_ptr->next;
		ptr = ptr->next;
	}
	nth_ptr->next = nth_ptr->next->next;
	return dummy->next;
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
	if (head == NULL)
	{
		puts("[]");
		return;
	}
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
	if ((pfile = fopen("19.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int n;
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
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &n);
	printf(" %d", n);
	puts("");

	printf("nums = ");
	printArray_int(nums, numsSize);
	printf("n = %d\n", n);

	struct ListNode *head = NULL;
	for (int i = numsSize - 1; i >= 0; i--)
		head = insertLinkListFromHead(head, nums[i]);

	printf("Link List: ");
	printLinkList(head);

	struct ListNode *res = removeNthFromEnd(head, n);
	printf("Removed Link List: ");
	printLinkList(res);
	printf("output: ");
	printLinkListInArray(res);

	return 0;
}