#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode
{
	int val;
	struct ListNode *next;
};

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
	struct ListNode *tmp = headA;
	while (tmp != NULL)
	{
		tmp->val += 1000000;
		tmp = tmp->next;
	}
	tmp = headB;
	while (tmp != NULL && tmp->val < 100001)
	{
		tmp = tmp->next;
	}
	struct ListNode *res = tmp;
	tmp = headA;
	while (tmp != NULL)
	{
		tmp->val -= 1000000;
		tmp = tmp->next;
	}
	return res;
}

void printList(struct ListNode *root, struct ListNode *target)
{
	struct ListNode *tmp = root;
	while (tmp != target)
	{
		printf("node.val = %d -> ", tmp->val);
		tmp = tmp->next;
	}
	puts("NULL");
	return;
}

int main()
{
	struct ListNode rootA = (struct ListNode)malloc(sizeof(struct ListNode));
	struct ListNode nodeA2 = (struct ListNode)malloc(sizeof(struct ListNode));

	struct ListNode rootB = (struct ListNode)malloc(sizeof(struct ListNode));
	struct ListNode nodeB2 = (struct ListNode)malloc(sizeof(struct ListNode));
	struct ListNode nodeB3 = (struct ListNode)malloc(sizeof(struct ListNode));

	struct ListNode nodeJoin1 = (struct ListNode)malloc(sizeof(struct ListNode));
	struct ListNode nodeJoin2 = (struct ListNode)malloc(sizeof(struct ListNode));
	struct ListNode nodeJoin3 = (struct ListNode)malloc(sizeof(struct ListNode));
	struct ListNode nodeJoin4 = (struct ListNode)malloc(sizeof(struct ListNode));

	rootA->val = 1;
	rootA->next = nodeA2;
	nodeA2->val = 5;
	nodeA2->next = NULL; // nodeJoin1;

	rootB->val = 2;
	rootB->next = nodeB2;
	nodeB2->val = 6;
	nodeB2->next = nodeB3;
	nodeB3->val = 4;
	nodeB3->next = NULL; // nodeJoin1;

	nodeJoin1->val = 8;
	nodeJoin1->next = nodeJoin2;
	nodeJoin2->val = 4;
	nodeJoin2->next = nodeJoin3;
	nodeJoin3->val = 5;
	nodeJoin3->next = NULL;

	printList(rootA, NULL);
	printList(rootB, NULL);
	struct ListNode *res = getIntersectionNode(rootA, rootB);
	if (res == NULL)
		puts("No Intersection");
	else
		printf("Intersection Node = %d\n", res->val);
	// printList(rootA, res);
	// printf("\t\t\t\t\t");
	// printList(nodeJoin1, NULL);
	// printList(rootB, res);

	return 0;
}