#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
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

void recoverValue(struct TreeNode *root)
{
	if (root == NULL)
		return;

	Stack S, T;
	S.top = -1;
	S.tree = (struct TreeNode **)malloc(10001 * sizeof(struct TreeNode *));
	T.top = -1;
	T.tree = (struct TreeNode **)malloc(10001 * sizeof(struct TreeNode *));
	struct TreeNode *ptr = root;
	Push(&T, ptr);
	while (S.top != -1 || T.top != -1)
	{
		while (T.top != -1)
		{
			ptr = Pop(&T);
			ptr->val -= 1000000000;

			if (ptr->left != NULL)
				Push(&S, ptr->left);
			if (ptr->right != NULL)
				Push(&S, ptr->right);
		}

		while (S.top != -1)
		{
			struct TreeNode *tmp = Pop(&S);
			Push(&T, tmp);
		}
	}
	return;
}

struct TreeNode *convertBST(struct TreeNode *root)
{
	if (root == NULL)
		return NULL;

	Stack T;
	T.top = -1;
	T.tree = (struct TreeNode **)malloc(10001 * sizeof(struct TreeNode *));
	struct TreeNode *stackbottom = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	stackbottom->val = -10001;
	Push(&T, stackbottom);
	struct TreeNode *ptr = root;
	Push(&T, ptr);

	int pre_val = 0;
	while (1)
	{
		if (T.tree[T.top]->val == stackbottom->val)
			break;

		// Find right-most node
		ptr = T.tree[T.top];
		while (ptr->right != NULL && ptr->right->val <= 10000 && ptr->right->val >= -10000)
		{
			Push(&T, ptr->right);
			ptr = ptr->right;
		}

		// calculate sum of values of all nodes that greater than ptr.value
		printf("top = %d, cur_val = %d, ", T.top, T.tree[T.top]->val);
		ptr = Pop(&T);
		if (ptr->val <= 10000 && ptr->val >= -10000)
			ptr->val += 1000000000;
		ptr->val += pre_val;
		pre_val = ptr->val - 1000000000;
		printf("changed_val = %d\n", ptr->val);

		// Traversal the next left node(leftchild)
		if (ptr->left != NULL && ptr->left->val <= 10000 && ptr->left->val >= -10000)
		{
			Push(&T, ptr->left);
			ptr = ptr->left;
		}
	}
	free(T.tree);

	recoverValue(root);

	return root;
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
	root->val = 1564;
	root->left = node2;
	root->right = node3;
	node2->val = 1434;
	node2->left = node4;
	node2->right = NULL;
	node3->val = 3048;
	node3->left = NULL;
	node3->right = node7;
	node4->val = 1;
	node4->left = NULL;
	node4->right = NULL;
	node5->val = 0;
	node5->left = NULL;
	node5->right = node8;
	node6->val = -38;
	node6->left = node8;
	node6->right = NULL;
	node7->val = 3184;
	node7->left = NULL;
	node7->right = NULL;
	node8->val = -40;
	node8->left = NULL;
	node8->right = NULL;
	node9->val = 8;
	node9->left = NULL;
	node9->right = NULL;
	int returnSize, *returnColumnSize;
	int **order = levelOrder(root, &returnSize, &returnColumnSize);
	printf("before:\t[");
	for (int i = 0; i < returnSize - 1; i++)
	{
		printArray(order[i], returnColumnSize[i], 1);
	}
	printArray(order[returnSize - 1], returnColumnSize[returnSize - 1], 0);
	printf("]\n");

	struct TreeNode *new_tree = convertBST(root);
	order = levelOrder(new_tree, &returnSize, &returnColumnSize);
	printf("after:\t[");
	for (int i = 0; i < returnSize - 1; i++)
	{
		printArray(order[i], returnColumnSize[i], 1);
	}
	printArray(order[returnSize - 1], returnColumnSize[returnSize - 1], 0);
	printf("]\n");

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