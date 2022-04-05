#include <stdio.h>
#include <stdlib.h>

//  Definition for a binary tree node.
struct TreeNode
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

void printArray(int *nums, int numsSize, _Bool oneline)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d", nums[i]);
		printf(",");
	}
	printf("%d", nums[numsSize - 1]);

	if (oneline)
		printf("],");
	else
		printf("]");
	return;
}

typedef struct stack
{
	struct TreeNode **tree;
	int top;
} Stack;

void Push(Stack *sta, struct TreeNode *node)
{
	sta->top++;
	sta->tree[sta->top] = node;
}

struct TreeNode *Pop(Stack *sta)
{
	struct TreeNode *tmp = sta->tree[sta->top];
	sta->top--;
	return tmp;
}

int minDepth(struct TreeNode *root)
{
	if (root == NULL)
		return 0;
	Stack S, T;
	S.top = -1;
	S.tree = (struct TreeNode **)malloc(100001 * sizeof(struct TreeNode *));
	T.top = -1;
	T.tree = (struct TreeNode **)malloc(100001 * sizeof(struct TreeNode *));
	struct TreeNode *ptr = root;
	Push(&T, ptr);
	int depth = 1;
	while (S.top != -1 || T.top != -1)
	{

		// printf("returnColumnSize = %d\n", rev_returnColumnSizes[*returnSize]);
		while (T.top != -1)
		{
			// printf("//level = %d, top = %d, T[top].val = %d, ", *returnSize, T.top, T.tree[T.top]->val);
			ptr = Pop(&T);
			if (ptr->left == NULL && ptr->right == NULL)
				return depth;
			// printf("rev_ret[%d][%d] = %d\n", *returnSize, pos - 1, rev_ret[*returnSize][pos - 1]);

			if (ptr->left != NULL)
				Push(&S, ptr->left);
			if (ptr->right != NULL)
				Push(&S, ptr->right);
		}
		depth += 1;

		while (S.top != -1)
		{
			struct TreeNode *tmp = Pop(&S);
			Push(&T, tmp);
		}
	}
	return depth;
}

int **levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
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
	S.tree = (struct TreeNode **)malloc(10001 * sizeof(struct TreeNode *));
	T.top = -1;
	T.tree = (struct TreeNode **)malloc(10001 * sizeof(struct TreeNode *));
	struct TreeNode *ptr = root;
	Push(&T, ptr);
	while (S.top != -1 || T.top != -1)
	{
		ret[*returnSize] = (int *)calloc(T.top + 1, sizeof(int));
		(*returnColumnSizes)[*returnSize] = T.top + 1;
		// printf("returnColumnSize = %d\n", rev_returnColumnSizes[*returnSize]);
		int pos = 0;
		while (T.top != -1)
		{
			// printf("//level = %d, top = %d, T[top].val = %d, ", *returnSize, T.top, T.tree[T.top]->val);
			ptr = Pop(&T);
			ret[*returnSize][pos++] = ptr->val;
			// printf("rev_ret[%d][%d] = %d\n", *returnSize, pos - 1, rev_ret[*returnSize][pos - 1]);

			if (ptr->left != NULL)
				Push(&S, ptr->left);
			if (ptr->right != NULL)
				Push(&S, ptr->right);
		}
		*returnSize += 1;

		while (S.top != -1)
		{
			struct TreeNode *tmp = Pop(&S);
			Push(&T, tmp);
		}
	}
	return ret;
}

int main()
{
	struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node2 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node3 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node4 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node5 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node6 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node7 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node8 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node9 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	root->val = 3;
	root->left = node2;
	root->right = node3;
	node2->val = 9;
	node2->left = NULL;
	node2->right = NULL;
	node3->val = 20;
	node3->left = node6;
	node3->right = node7;
	node4->val = 4;
	node4->left = node6;
	node4->right = node7;
	node5->val = 5;
	node5->left = NULL;
	node5->right = NULL;
	node6->val = 15;
	node6->left = NULL;
	node6->right = NULL;
	node7->val = 7;
	node7->left = NULL;
	node7->right = NULL;
	node8->val = 8;
	node8->left = NULL;
	node8->right = NULL;
	node9->val = 9;
	node9->left = NULL;
	node9->right = NULL;

	int returnSize, *returnColumnSize;
	int **order = levelOrder(root, &returnSize, &returnColumnSize);
	printf("[");
	for (int i = 0; i < returnSize - 1; i++)
	{
		printArray(order[i], returnColumnSize[i], 1);
	}
	printArray(order[returnSize - 1], returnColumnSize[returnSize - 1], 0);
	printf("]\n");

	printf("minDepth = %d\n", minDepth(root));

	free(root);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(node7);
	free(node8);
	free(node9);
	return 0;
}