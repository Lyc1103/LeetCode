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

int main()
{
	struct ListNode *list1 = NULL, *list2 = NULL;
	list1 = insertListNode(list1, 3);
	// list1 = insertListNode(list1, 2);
	// list1 = insertListNode(list1, 1);
	// list1 = insertListNode(list1, 1);
	// list1 = insertListNode(list1, 1);
	// list1 = insertListNode(list1, 1);
	// list1 = insertListNode(list1, 1);
	// printLinkLists(list1);
	list2 = deleteDuplicates(list1);
	printLinkLists(list2);
	return 0;
}