#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *postorderTraversal(struct TreeNode *root, int *returnSize)
{
	*returnSize = 0;
	int *ret = (int *)calloc(101, sizeof(int));
	if (root == NULL)
		return ret;

	Stack T;
	T.top = -1;
	T.tree = (struct TreeNode **)malloc(101 * sizeof(struct TreeNode *));
	struct TreeNode *ptr = root;
	Push(&T, ptr);
	while (1)
	{
		printf("//cur_val = %d, top = %d, T[top].val = %d\n", ptr->val, T.top, T.tree[T.top]->val);
		if (ptr->left != NULL && ptr->left->val < 101)
		{
			Push(&T, ptr->left);
			ptr = ptr->left;
		}
		else if (ptr->right != NULL && ptr->right->val < 101)
		{
			Push(&T, ptr->right);
			ptr = ptr->right;
		}
		else
		{
			ptr = T.tree[T.top];
			if (ptr->val < 101 && (ptr->right == NULL || ptr->right->val > 100))
			{
				Pop(&T);
				ret[*returnSize] = ptr->val;
				*returnSize += 1;
				// printf("ret[cur] = %d, top = %d, T[top].val = %d\n", ptr->val, T.top, T.tree[T.top]->val);
				ptr->val += 1000;
				if (T.top != -1)
					ptr = T.tree[T.top];
				else
					break;
			}
		}
	}
	printf("top = %d\n", T.top);
	free(T.tree);
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
	root->val = 1;
	// root->left = NULL;   // node2;
	// root->right = node2; // node3;
	// node2->val = 2;
	// node2->left = node3; // node4;
	// node2->right = NULL; // node5;
	// node3->val = 3;
	// node3->left = NULL;  // node6;
	// node3->right = NULL; // node7;
	root->left = node2;
	root->right = node3;
	node2->val = 2;
	node2->left = node4;
	node2->right = node5;
	node3->val = 3;
	node3->left = node6;
	node3->right = node7;
	node4->val = 4;
	node4->left = NULL;
	node4->right = NULL;
	node5->val = 5;
	node5->left = node8;
	node5->right = NULL;
	node6->val = 6;
	node6->left = NULL;
	node6->right = node9;
	node7->val = 7;
	node7->left = NULL;
	node7->right = NULL;
	node8->val = 8;
	node8->left = NULL;
	node8->right = NULL;
	node9->val = 9;
	node9->left = NULL;
	node9->right = NULL;
	int returnSize = 0;
	int *order = postorderTraversal(root, &returnSize);
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
	return 0;
}