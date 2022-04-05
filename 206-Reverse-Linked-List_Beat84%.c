#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode
{
	int val;
	struct ListNode *next;
};

struct ListNode *insertLinkListFromHead(struct ListNode *head, int data)
{
	struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
	newNode->val = data;
	newNode->next = head;
	return newNode;
}

struct ListNode *buildLinkList(int *nums, int numsSize)
{
	struct ListNode *head = NULL;
	int i;
	for (i = numsSize - 1; i >= 0; i--)
		head = insertLinkListFromHead(head, nums[i]);
	return head;
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

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
	if (list1 == NULL)
		return list2;
	if (list2 == NULL)
		return list1;
	struct ListNode *ret, *cur_ptr;
	if (list1->val <= list2->val)
	{
		ret = list1;
		list1 = list1->next;
	}
	else
	{
		ret = list2;
		list2 = list2->next;
	}

	cur_ptr = ret;
	while (list1 != NULL && list2 != NULL)
	{
		if (list1->val <= list2->val)
		{
			cur_ptr->next = list1;
			cur_ptr = list1;
			list1 = list1->next;
		}
		else // list1->val > list2->val
		{
			cur_ptr->next = list2;
			cur_ptr = list2;
			list2 = list2->next;
		}
	}
	if (list1 != NULL)
		cur_ptr->next = list1;
	else if (list2 != NULL)
		cur_ptr->next = list2;

	return ret;
}

struct ListNode *reverseList(struct ListNode *head)
{
	struct ListNode *ret = NULL;
	for (; head != NULL; head = head->next)
		ret = insertLinkListFromHead(ret, head->val);
	return ret;
}

struct ListNode *dealWithInputFile_forOneLinkList(FILE *pfile, int *nums, int *numsSize)
{
	char c;
	int sum = 0, flag = 0;
	*numsSize = 0;
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
			if (flag == 1)
				(*numsSize)++;
			break;
		}
		if (c == ',')
		{
			(*numsSize)++;
			continue;
		}
		nums[*numsSize] = nums[*numsSize] * 10 + (c - '0');
		flag = 1;
	}
	struct ListNode *head = buildLinkList(nums, *numsSize);
	return head;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("206.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums[100] = {0}, numsSize;
	struct ListNode *head = dealWithInputFile_forOneLinkList(pfile, nums, &numsSize);
	puts("");
	printf("list: ");
	printLinkList(head);
	printf("list: ");
	printLinkListInArray(head);

	head = reverseList(head);
	printf("res: ");
	printLinkListInArray(head);

	return 0;
}
