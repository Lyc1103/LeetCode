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
	if (head == NULL)
		newNode->next = NULL;
	else
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
	if ((pfile = fopen("21.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums1[100] = {0}, numsSize1, nums2[100] = {0}, numsSize2;
	struct ListNode *list1 = dealWithInputFile_forOneLinkList(pfile, nums1, &numsSize1);
	struct ListNode *list2 = dealWithInputFile_forOneLinkList(pfile, nums2, &numsSize2);
	puts("");
	printf("list1: ");
	printLinkList(list1);
	printf("list1: ");
	printLinkListInArray(list1);
	printf("list2: ");
	printLinkList(list2);
	printf("list2: ");
	printLinkListInArray(list2);

	list1 = mergeTwoLists(list1, list2);
	printf("res: ");
	printLinkListInArray(list1);

	return 0;
}