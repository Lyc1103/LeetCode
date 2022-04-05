#include <stdio.h>
#include <stdlib.h>

//  Definition for singly-linked list.
struct ListNode
{
	int val;
	struct ListNode *next;
};

void prinfLinkList(struct ListNode *head)
{
	struct ListNode *ptr = head;
	while (ptr != NULL)
	{
		printf("%d -> ", ptr->val);
		ptr = ptr->next;
	}
	puts("NULL");
	return;
}

struct ListNode *removeElements(struct ListNode *head, int val)
{

	while (head != NULL && head->val == val)
	{
		head = head->next;
	}
	if (head == NULL)
		return NULL;

	struct ListNode *ptr = head, *pre = head;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		while (ptr != NULL && ptr->val == val)
		{
			ptr = ptr->next;
		}

		pre->next = ptr;
		pre = ptr;
	}

	return head;
}

int main()
{
	struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *node2 = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *node3 = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *node4 = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *node5 = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *node6 = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *node7 = (struct ListNode *)malloc(sizeof(struct ListNode));
	head->val = 6;
	head->next = node2;
	node2->val = 6;
	node2->next = node3;
	node3->val = 6;
	node3->next = node4;
	node4->val = 1;
	node4->next = node5;
	node5->val = 6;
	node5->next = node6;
	node6->val = 6;
	node6->next = node7;
	node7->val = 6;
	node7->next = NULL;

	prinfLinkList(head);

	int target = 6;
	struct ListNode *newhead = removeElements(head, target);
	prinfLinkList(newhead);

	free(head);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(node7);
	return 0;
}