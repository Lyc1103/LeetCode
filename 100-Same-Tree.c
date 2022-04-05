#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

_Bool isSameTree(struct TreeNode *p, struct TreeNode *q)
{
	if (p == NULL && q == NULL)
		return 1;
	else if (p == NULL || q == NULL)
		return 0;
	int front1 = -1, rear1 = -1, front2 = -1, rear2 = -1;
	struct TreeNode **p_queue = (struct TreeNode **)malloc(202 * sizeof(struct TreeNode *));
	struct TreeNode **q_queue = (struct TreeNode **)malloc(202 * sizeof(struct TreeNode *));
	p_queue[++rear1] = p;
	q_queue[++rear2] = q;
	while (front1 < rear1 && front2 < rear2)
	{
		struct TreeNode *p_tmp = p_queue[++front1], *q_tmp = q_queue[++front2];
		// printf("p_tmp = %d, q_tmp = %d\n", p_tmp->val, q_tmp->val);
		if (p_tmp->val != q_tmp->val)
			return 0;

		if (p_tmp->left != NULL)
		{
			p_tmp->left->val += (100000 + p_tmp->val);
			p_queue[++rear1] = p_tmp->left;
		}
		if (p_tmp->right != NULL)
		{
			p_tmp->right->val += (200000 + p_tmp->val);
			p_queue[++rear1] = p_tmp->right;
		}
		if (q_tmp->left != NULL)
		{

			q_tmp->left->val += (100000 + q_tmp->val);
			q_queue[++rear2] = q_tmp->left;
		}
		if (q_tmp->right != NULL)
		{
			q_tmp->right->val += (200000 + q_tmp->val);
			q_queue[++rear2] = q_tmp->right;
		}

		if (rear1 != rear2)
			return 0;
	}
	return 1;
}

int main()
{
	struct TreeNode *root1 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node12 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node13 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *root2 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node22 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	struct TreeNode *node23 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	root1->val = 1;
	root1->left = NULL;
	root1->right = NULL;
	node12->val = 2;
	node12->left = NULL;
	node12->right = NULL;
	node13->val = 3;
	node13->left = NULL;
	node13->right = NULL;
	root2->val = 1;
	root2->left = NULL;
	root2->right = node22;
	node22->val = 2;
	node22->left = NULL;
	node22->right = NULL;
	node23->val = 3;
	node23->left = NULL;
	node23->right = NULL;
	_Bool res = isSameTree(root1, root2);
	if (res)
		puts("true");
	else
		puts("false");

	return 0;
}