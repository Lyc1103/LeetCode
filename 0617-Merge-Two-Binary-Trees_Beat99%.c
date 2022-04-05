#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definition for a binary tree node.
struct TreeNode
{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

typedef struct
{
	int top;
	struct TreeNode **data;
} Stack;

Stack *createStack(int size)
{
	Stack *sta;
	sta->top = -1;
	sta->data = (struct TreeNode **)malloc(size * sizeof(struct TreeNode *));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	if (sta->top == -1)
		return 1;
	return 0;
}

void pushToStack(Stack *sta, struct TreeNode *ptr)
{
	(sta->top)++;
	sta->data[sta->top] = ptr;
	return;
}

struct TreeNode *popFromStack(Stack *sta)
{
	if (isEmptyStack(sta))
	{
		puts("The stack is empty!");
		exit(0);
		return NULL;
	}
	(sta->top)--;
	return sta->data[(sta->top) + 1];
}

void printTree(struct TreeNode *root)
{
	int size = 100;
	Stack s, t;
	s.top = t.top = -1;
	s.data = (struct TreeNode **)malloc(size * sizeof(struct TreeNode *));
	t.data = (struct TreeNode **)malloc(size * sizeof(struct TreeNode *));
	if (root != NULL)
		pushToStack(&t, root);

	struct TreeNode *ptr;
	while (!isEmptyStack(&s) || !isEmptyStack(&t))
	{
		while (!isEmptyStack(&t))
		{
			ptr = popFromStack(&t);
			if (ptr->left == NULL)
				printf("%d --left--> NULL\n", ptr->val);
			else
			{
				pushToStack(&s, ptr->left);
				printf("%d --left--> %d\n", ptr->val, ptr->left->val);
			}
			if (ptr->right == NULL)
				printf("%d --right--> NULL\n", ptr->val);
			else
			{
				pushToStack(&s, ptr->right);
				printf("%d --right--> %d\n", ptr->val, ptr->right->val);
			}
		}

		while (!isEmptyStack(&s))
		{
			ptr = popFromStack(&s);
			pushToStack(&t, ptr);
		}
	}
	free(s.data);
	free(t.data);
	return;
}

struct TreeNode *buildTree(int *nums, int numsSize)
{
	struct TreeNode **tree = (struct TreeNode **)malloc((numsSize + 1) * sizeof(struct TreeNode *));
	for (int i = 1; i <= numsSize; i++)
	{
		if (nums[i - 1] != INT_MIN)
		{
			tree[i] = (struct TreeNode *)malloc(sizeof(struct TreeNode));
			tree[i]->val = nums[i - 1];
			tree[i]->left = NULL;
			tree[i]->right = NULL;
		}
		else
			tree[i] = NULL;
	}
	for (int i = 1; i * 2 <= numsSize; i++)
	{
		if (tree[i] == NULL)
			continue;
		tree[i]->left = tree[i * 2];
		if (i * 2 + 1 <= numsSize)
			tree[i]->right = tree[i * 2 + 1];
	}

	return tree[1];
}

struct TreeNode *mergeTrees(struct TreeNode *root1, struct TreeNode *root2)
{
	if (root1 == NULL)
		return root2;
	if (root2 == NULL)
		return root1;
	root1->val += root2->val;
	root1->left = mergeTrees(root1->left, root2->left);
	root1->right = mergeTrees(root1->right, root2->right);
	return root1;
}

void printArray_int(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		if (nums[i] == INT_MIN)
			printf("null,");
		else
			printf("%d,", nums[i]);
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

struct TreeNode *dealWithInputFile_forOneTree(FILE *pfile, int *nums, int *numsSize)
{
	char c;
	int sum = 0, tmp;
	*numsSize = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
		else if (c == 'n')
		{
			fscanf(pfile, "%c%c%c", &c, &c, &c);
			printf("ull");
			nums[(*numsSize)++] = INT_MIN;
		}
		else if (c != ',')
		{
			c -= '0';
			while (c < 10 && c >= 0)
			{
				sum = sum * 10 + c;
				fscanf(pfile, "%c", &c);
				printf("%c", c);
				if (c == ']')
					break;
				c -= '0';
			}
			nums[(*numsSize)++] = sum;
			sum = 0;
			if (c == ']')
				break;
		}
	}
	struct TreeNode *root = buildTree(nums, *numsSize);
	return root;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("617.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	// char c;
	// int sum = 0, tmp;
	int nums1[100], numsSize1;
	int nums2[100], numsSize2;
	// root1, *root2;
	puts("input:");
	struct TreeNode *root1 = dealWithInputFile_forOneTree(pfile, nums1, &numsSize1);
	struct TreeNode *root2 = dealWithInputFile_forOneTree(pfile, nums2, &numsSize2);
	puts("");

	printf("nums1 = ");
	printArray_int(nums1, numsSize1);
	printf("nums2 = ");
	printArray_int(nums2, numsSize2);
	puts("tree1: ");
	printTree(root1);
	puts("tree2: ");
	printTree(root2);
	puts("");

	struct TreeNode *merged_root = mergeTrees(root1, root2);
	puts("merged root:");
	printTree(merged_root);

	return 0;
}