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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **levelOrder(struct Node *root, int *returnSize, int **returnColumnSizes)
{
	*returnSize = 0;
	*returnColumnSizes = (int *)calloc(1001, sizeof(int));
	int **ret = (int **)calloc(1001, sizeof(int *));

	if (root == NULL)
	{
		*returnColumnSizes = NULL;
		return ret;
	}

	Stack S, T;
	S.top = -1;
	S.tree = (struct Node **)malloc(10001 * sizeof(struct Node *));
	T.top = -1;
	T.tree = (struct Node **)malloc(10001 * sizeof(struct Node *));
	struct Node *ptr = root;
	Push(&T, ptr);
	while (S.top != -1 || T.top != -1)
	{
		ret[*returnSize] = (int *)calloc(T.top + 1, sizeof(int));
		(*returnColumnSizes)[*returnSize] = T.top + 1;
		// printf("returnColumnSize = %d\n", (*returnColumnSizes)[*returnSize]);
		int pos = 0;
		while (T.top != -1)
		{
			// printf("//level = %d, top = %d, T[top].val = %d, ", *returnSize, T.top, T.tree[T.top]->val);
			ptr = Pop(&T);
			ret[*returnSize][pos++] = ptr->val;
			// printf("ret[%d][%d] = %d\n", *returnSize, pos - 1, ret[*returnSize][pos - 1]);

			int i = 0;
			while (i < ptr->numChildren)
			{
				if (ptr->children[i] != NULL)
				{
					Push(&S, ptr->children[i]);
				}
				i++;
			}
		}
		*returnSize += 1;

		while (S.top != -1)
		{
			struct Node *tmp = Pop(&S);
			Push(&T, tmp);
		}
	}

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
	int returnSize = 0, *returnColumnSize;
	int **order = levelOrder(root, &returnSize, &returnColumnSize);
	// int order[2][3] = {1, 2, 3,
	// 		   4, 5, 6};
	free(root->children);
	free(node3->children);
	free(node4->children);
	free(node5->children);
	free(node7->children);
	free(node8->children);
	free(node9->children);
	free(node11->children);
	for (int i = 0; i < returnSize; i++)
	{
		printArray(order[i], returnColumnSize[i]);
	}

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