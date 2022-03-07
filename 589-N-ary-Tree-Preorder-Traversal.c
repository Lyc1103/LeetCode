#include <stdio.h>
#include <stdlib.h>

// Definition for a Node.
struct Node
{
	int val;
	int numChildren;
	struct Node **children;
};

void printArray(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d", nums[i]);
		printf(",");
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

typedef struct stack
{
	struct Node **tree;
	int top;
} Stack;

void Push(Stack *sta, struct Node *node)
{
	sta->top++;
	sta->tree[sta->top] = node;
}

struct Node *Pop(Stack *sta)
{
	struct Node *tmp = sta->tree[sta->top];
	sta->top--;
	return tmp;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *preorder(struct Node *root, int *returnSize)
{
	*returnSize = 0;
	int *ret = (int *)calloc(10001, sizeof(int));
	if (root == NULL)
		return ret;

	Stack T;
	T.top = -1;
	T.tree = (struct Node **)malloc(10001 * sizeof(struct Node *));
	struct Node *ptr = root;
	Push(&T, ptr);
	while (T.top != -1)
	{
		printf("//cur_val = %d, top = %d, T[top].val = %d\n", ptr->val, T.top, T.tree[T.top]->val);
		ptr = T.tree[T.top];
		if (ptr->val < 10001)
		{
			ret[*returnSize] = ptr->val;
			*returnSize += 1;
			// printf("ret[cur] = %d, top = %d, T[top].val = %d\n", ptr->val, T.top, T.tree[T.top]->val);
			ptr->val += 1000000;
		}

		int i = 0;
		while (i < ptr->numChildren)
		{
			if (ptr->children[i] != NULL && ptr->children[i]->val < 10001)
			{
				Push(&T, ptr->children[i]);
				break;
			}
			i++;
		}
		if (i == ptr->numChildren)
			Pop(&T);
	}
	// printf("returnSize = %d\n", *returnSize);
	return ret;
}

int main()
{
	struct Node *root = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node2 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node3 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node4 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node5 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node6 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node7 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node8 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node9 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node10 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node11 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node12 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node13 = (struct Node *)malloc(sizeof(struct Node));
	struct Node *node14 = (struct Node *)malloc(sizeof(struct Node));
	root->val = 1;
	root->numChildren = 4;
	root->children = (struct Node **)malloc(4 * sizeof(struct Node));
	root->children[0] = node2;
	root->children[1] = node3;
	root->children[2] = node4;
	root->children[3] = node5;
	node2->val = 2;
	node2->numChildren = 0;
	node3->val = 3;
	node3->numChildren = 2;
	node3->children = (struct Node **)malloc(2 * sizeof(struct Node));
	node3->children[0] = node6;
	node3->children[1] = node7;
	node4->val = 4;
	node4->numChildren = 1;
	node4->children = (struct Node **)malloc(1 * sizeof(struct Node));
	node4->children[0] = node8;
	node5->val = 5;
	node5->numChildren = 2;
	node5->children = (struct Node **)malloc(2 * sizeof(struct Node));
	node5->children[0] = node9;
	node5->children[1] = node10;
	node6->val = 6;
	node6->numChildren = 0;
	node7->val = 7;
	node7->numChildren = 1;
	node7->children = (struct Node **)malloc(1 * sizeof(struct Node));
	node7->children[0] = node11;
	node8->val = 8;
	node8->numChildren = 1;
	node8->children = (struct Node **)malloc(1 * sizeof(struct Node));
	node8->children[0] = node12;
	node9->val = 9;
	node9->numChildren = 1;
	node9->children = (struct Node **)malloc(1 * sizeof(struct Node));
	node9->children[0] = node13;
	node10->val = 10;
	node10->numChildren = 0;
	node11->val = 11;
	node11->numChildren = 1;
	node11->children = (struct Node **)malloc(1 * sizeof(struct Node));
	node11->children[0] = node14;
	node12->val = 12;
	node12->numChildren = 0;
	node13->val = 13;
	node13->numChildren = 0;
	node14->val = 14;
	node14->numChildren = 0;
	int returnSize = 0;
	int *order = preorder(root, &returnSize);
	free(root->children);
	free(node3->children);
	free(node4->children);
	free(node5->children);
	free(node7->children);
	free(node8->children);
	free(node9->children);
	free(node11->children);
	printArray(order, returnSize);

	free(root);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(node7);
	free(node8);
	free(node9);
	free(node10);
	free(node11);
	free(node12);
	free(node13);
	free(node14);
	return 0;
}