#include <stdio.h>
#include <stdlib.h>

//  Definition for singly-linked list.
struct ListNode
{
	int val;
	struct ListNode *next;
};

_Bool hasCycle(struct ListNode *head)
{
	if (head == NULL)
		return 0;
	struct ListNode *ptr = head;
	while (ptr->next != NULL && ptr->val < 100001)
	{
		// printf("ptr.val = %d\n", ptr->val);
		ptr->val += 1000000;
		if (ptr->next->val > 100000)
			return 1;
		ptr = ptr->next;
	}
	return 0;
}

int main()
{
	struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *node2 = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *node3 = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *node4 = (struct ListNode *)malloc(sizeof(struct ListNode));
	struct ListNode *node5 = (struct ListNode *)malloc(sizeof(struct ListNode));
	head->val = 1;
	head->next = head;
	node2->val = 100000;
	node2->next = node3;
	node3->val = 99999;
	node3->next = node2;
	node4->val = 1;
	node4->next = node5;
	node5->val = 1;
	node5->next = node2;

	if (hasCycle(head))
		puts("true");
	else
		puts("false");

	free(head);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	return 0;
}