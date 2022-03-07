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

_Bool hasPathSum(struct TreeNode *root, int targetSum)
{
	if (root == NULL)
		return 0;
	Stack S;
	S.top = -1;
	S.tree = (struct TreeNode **)malloc(5001 * sizeof(struct TreeNode *));
	// Push(&S, NULL);
	Push(&S, root);

	int sum = 0;
	while (S.top != -1)
	{
		struct TreeNode *ptr = S.tree[S.top];
		printf("top.val = %d, ptr.val = %d, sum(before) = %d, ", S.top, ptr->val, sum);
		if (ptr->val < 1001 && ptr->val > -1001)
		{
			sum += ptr->val;
			ptr->val += 100000;
		}
		printf("sum(after) = %d\n", sum);

		if (sum == targetSum && ptr->left == NULL && ptr->right == NULL)
		{
			return 1;
		}

		if (ptr->left != NULL && ptr->left->val < 1001 && ptr->left->val > -1001)
		{
			Push(&S, ptr->left);
			// sum += ptr->left->val;
			// printf("sum(after) = %d\n", sum);
		}
		else if (ptr->right != NULL && ptr->right->val < 1001 && ptr->right->val > -1001)
		{
			Push(&S, ptr->right);
			// sum += ptr->right->val;
			// printf("sum(after) = %d\n", sum);
		}
		else
		{
			struct TreeNode *tmp;
			tmp = Pop(&S);
			sum = sum - tmp->val + 100000;
			printf("sum(minus) = %d\n", sum);
		}
	}
	return 0;
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
	// root->val = 1;
	// root->left = node2;
	// root->right = node3;
	// node2->val = 2;
	// node2->left = NULL;
	// node2->right = NULL;
	// node3->val = 3;
	// node3->left = NULL;
	// node3->right = NULL;
	root->val = -1000;
	root->left = node2;
	root->right = node3;
	node2->val = -200;
	node2->left = node4;
	node2->right = NULL;
	node3->val = 200;
	node3->left = node5;
	node3->right = node6;
	node4->val = -500;
	node4->left = node7;
	node4->right = node8;
	node5->val = 500;
	node5->left = NULL;
	node5->right = NULL;
	node6->val = 600;
	node6->left = NULL;
	node6->right = node9;
	node7->val = 300;
	node7->left = NULL;
	node7->right = NULL;
	node8->val = 1000;
	node8->left = NULL;
	node8->right = NULL;
	node9->val = -900;
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

	int targetsum = -1100;
	if (hasPathSum(root, targetsum))
		puts("true");
	else
		puts("false");

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