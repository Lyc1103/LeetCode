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
int *inorderTraversal(struct TreeNode *root, int *returnSize)
{
	*returnSize = 0;
	int *ret = (int *)calloc(100001, sizeof(int));
	if (root == NULL)
		return ret;

	Stack T;
	T.top = -1;
	T.tree = (struct TreeNode **)malloc(100001 * sizeof(struct TreeNode *));
	struct TreeNode *ptr = root, *tmp;
	Push(&T, ptr);
	while (T.top != -1)
	{
		while (ptr->left != NULL && ptr->left->val != -100001)
		{
			Push(&T, ptr->left);
			ptr = ptr->left;
		}
		// printf("returnSize(before) = %d, ", *returnSize);
		ptr = Pop(&T);
		ret[*returnSize] = ptr->val;
		*returnSize += 1;
		// printf("ret[cur] = %d, returnSize(after) = %d\n", ptr->val, *returnSize);
		ptr->val = -100001;
		if (ptr->right != NULL && ptr->right->val != -100001)
		{
			Push(&T, ptr->right);
			ptr = ptr->right;
		}
	}
	// printf("top of stack T is %d\n", T.top);

	// free(T);
	return ret;
}

struct TreeNode *ArrayToBST(int *nums, int front, int rear)
{
	// printf("front = %d, rear = %d\n", front, rear);
	if (front > rear)
		return NULL;
	struct TreeNode *newnode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	int partition = front + (rear - front) / 2;
	newnode->val = nums[partition];
	newnode->left = NULL;
	newnode->right = NULL;
	// printf("partition = %d\n", front, rear, partition);

	if (front == rear)
		return newnode;

	newnode->left = ArrayToBST(nums, front, partition - 1);
	newnode->right = ArrayToBST(nums, partition + 1, rear);

	return newnode;
}

struct TreeNode *sortedArrayToBST(int *nums, int numsSize)
{
	if (numsSize == 0)
		return NULL;
	struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	int partition = (numsSize - 1) / 2;
	root->val = nums[partition];
	root->left = NULL;
	root->right = NULL;
	// printf("partition = %d, root.val = %d\n", partition, root->val);

	root->left = ArrayToBST(nums, 0, partition - 1);
	root->right = ArrayToBST(nums, partition + 1, numsSize - 1);

	return root;
}

_Bool binarySearch(struct TreeNode *root, int target)
{
	struct TreeNode *ptr = root;
	while (1)
	{
		// printf("ptr.val = %d->", ptr->val);
		if (ptr->val == target)
			return 1;
		else if (ptr->val > target && ptr->left != NULL)
		{
			ptr = ptr->left;
		}
		else if (ptr->val > target && ptr->left == NULL)
		{
			return 0;
		}
		else if (ptr->val < target && ptr->right != NULL)
		{
			ptr = ptr->right;
		}
		else if (ptr->val < target && ptr->right == NULL)
		{
			return 0;
		}
	}
	return 0;
}

_Bool findTarget(struct TreeNode *root, int k)
{
	int numsSize = 0;
	int *nums = inorderTraversal(root, &numsSize);
	// printArray(nums, numsSize);

	struct TreeNode *root2 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	root2 = sortedArrayToBST(nums, numsSize);
	// printf("root.val = %d\n", root2->val);

	for (int i = 0; i < numsSize; i++)
	{
		int target = k - nums[i];
		// printf("target = %d, ", target);
		if (2 * target == k)
			return 0;
		if (binarySearch(root2, target))
			return 1;
		// puts("return");
	}
	return 0;
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
	root->left = NULL;
	root->right = NULL;
	node2->val = 4;
	node2->left = NULL;
	node2->right = NULL;
	node3->val = 7;
	node3->left = NULL;
	node3->right = NULL;
	node4->val = 0;
	node4->left = NULL;
	node4->right = node5;
	node5->val = 2;
	node5->left = NULL;
	node5->right = node6;
	node6->val = 7;
	node6->left = NULL;
	node6->right = node7;
	node7->val = 9;
	node7->left = NULL;
	node7->right = NULL;
	node8->val = 8;
	node8->left = NULL;
	node8->right = NULL;
	node9->val = 9;
	node9->left = NULL;
	node9->right = NULL;

	int target = 2;
	if (findTarget(root, target))
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