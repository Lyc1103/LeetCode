#include <stdio.h>
#include <stdlib.h>

//  Definition for singly-linked list.
struct ListNode
{
	int val;
	struct ListNode *next;
};

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

struct ListNode *reverseList(struct ListNode *head)
{
	if (head == NULL)
		return NULL;
	struct ListNode *ptr = head;
	struct ListNode *prevptr = NULL;
	struct ListNode *nextptr = ptr->next;
	while (1)
	{
		ptr->next = prevptr;

		if (nextptr == NULL)
			break;
		prevptr = ptr;
		ptr = nextptr;
		nextptr = nextptr->next;
	}
	head = ptr;
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
	head->val = 1;
	head->next = node2;
	node2->val = 2;
	node2->next = node3;
	node3->val = 3;
	node3->next = node4;
	node4->val = 4;
	node4->next = node5;
	node5->val = 5;
	node5->next = node6;
	node6->val = 6;
	node6->next = node7;
	node7->val = 7;
	node7->next = NULL;

	printLinkLists(head);

	struct ListNode *newhead = reverseList(head);
	printLinkLists(newhead);

	free(head);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(node7);
	return 0;
}