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

struct TreeNode *ArrayToBST(int *nums, int front, int rear)
{
	printf("front = %d, rear = %d\n", front, rear);
	if (front > rear)
		return NULL;
	struct TreeNode *newnode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	int partition = front + (rear - front) / 2;
	newnode->val = nums[partition];
	newnode->left = NULL;
	newnode->right = NULL;
	printf("partition = %d\n", front, rear, partition);

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
	printf("partition = %d, root.val = %d\n", partition, root->val);

	root->left = ArrayToBST(nums, 0, partition - 1);
	root->right = ArrayToBST(nums, partition + 1, numsSize - 1);

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
	int nums[2] = {1, 3};
	int numsSize = 2;

	struct TreeNode *root = sortedArrayToBST(nums, numsSize);

	int returnSize, *returnColumnSize;
	int **order = levelOrder(root, &returnSize, &returnColumnSize);
	printf("[");
	for (int i = 0; i < returnSize - 1; i++)
	{
		printArray(order[i], returnColumnSize[i], 1);
	}
	printArray(order[returnSize - 1], returnColumnSize[returnSize - 1], 0);
	printf("]\n");

	return 0;
}