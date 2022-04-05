#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode
{
	int val;
	struct ListNode *next;
};

struct ListNode *insertListNode(struct ListNode *head, int value)
{
	struct ListNode *newnode = (struct ListNode *)malloc(sizeof(struct ListNode));
	newnode->val = value;
	if (head == NULL)
	{
		newnode->next = NULL;
		return newnode;
	}
	else
	{
		newnode->next = head;
		return newnode;
	}
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

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
	struct ListNode *tmp1 = reverseList(list1);
	printLinkLists(tmp1);
	struct ListNode *tmp2 = reverseList(list2);
	printLinkLists(tmp2);
	struct ListNode *ret = NULL;
	while (tmp1 != NULL && tmp2 != NULL)
	{
		if (tmp1->val >= tmp2->val)
		{
			ret = insertListNode(ret, tmp1->val);
			tmp1 = tmp1->next;
		}
		else
		{
			ret = insertListNode(ret, tmp2->val);
			tmp2 = tmp2->next;
		}
	}
	while (tmp1 != NULL)
	{
		ret = insertListNode(ret, tmp1->val);
		tmp1 = tmp1->next;
	}
	while (tmp2 != NULL)
	{
		ret = insertListNode(ret, tmp2->val);
		tmp2 = tmp2->next;
	}
	return ret;
}

int main()
{
	struct ListNode *list1 = NULL, *list2 = NULL, *list3 = NULL;
	// list1 = insertListNode(list1, 4);
	// list1 = insertListNode(list1, 2);
	// list1 = insertListNode(list1, 1);
	// list2 = insertListNode(list2, 4);
	// list2 = insertListNode(list2, 3);
	list2 = insertListNode(list2, 0);
	list3 = mergeTwoLists(list1, list2);
	// printLinkLists(list1);
	// printLinkLists(list2);
	printLinkLists(list3);
	return 0;
}