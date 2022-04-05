#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

_Bool isSymmetric(struct TreeNode *root)
{
	if (root == NULL || (root->left == NULL && root->right == NULL))
		return 1;
	else if (root->left == NULL || root->right == NULL)
		return 0;

	struct TreeNode *p = root->left, *q = root->right;
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

		if (q_tmp->right != NULL)
		{
			q_tmp->right->val += (100000 + q_tmp->val);
			q_queue[++rear2] = q_tmp->right;
		}
		if (q_tmp->left != NULL)
		{

			q_tmp->left->val += (200000 + q_tmp->val);
			q_queue[++rear2] = q_tmp->left;
		}

		if (rear1 != rear2)
			return 0;
	}
	return 1;
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
	root->left = node2;
	root->right = node3;
	node2->val = 2;
	node2->left = node4;
	node2->right = node5;
	node3->val = 2;
	node3->left = node6;
	node3->right = node7;
	node4->val = 3;
	node4->left = NULL;
	node4->right = NULL;
	node5->val = 4;
	node5->left = node8;
	node5->right = NULL;
	node6->val = 4;
	node6->left = NULL;
	node6->right = node9;
	node7->val = 3;
	node7->left = NULL;
	node7->right = NULL;
	node8->val = 5;
	node8->left = NULL;
	node8->right = NULL;
	node9->val = 5;
	node9->left = NULL;
	node9->right = NULL;
	_Bool res = isSymmetric(root);
	if (res)
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