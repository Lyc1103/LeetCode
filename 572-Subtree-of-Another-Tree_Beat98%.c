#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#define COUNT 5

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
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->top = -1;
	sta->data = (struct TreeNode **)malloc(size * sizeof(struct TreeNode *));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	return sta->top == -1 ? 1 : 0;
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

_Bool cmpTrees(struct TreeNode *root, struct TreeNode *subRoot)
{
	if (root == NULL && subRoot == NULL)
		return 1;
	else if (root == NULL || subRoot == NULL)
		return 0;
	return (root->val == subRoot->val) && cmpTrees(root->left, subRoot->left) && cmpTrees(root->right, subRoot->right);
}

_Bool isSubtree(struct TreeNode *root, struct TreeNode *subRoot)
{
	Stack *s = createStack(2000);
	pushToStack(s, root);
	struct TreeNode *ptr;
	while (!isEmptyStack(s))
	{
		ptr = popFromStack(s);
		// printf("cur_root = %d\n", ptr->val);
		if (cmpTrees(ptr, subRoot))
			return 1;
		if (ptr->left != NULL)
			pushToStack(s, ptr->left);
		if (ptr->right != NULL)
			pushToStack(s, ptr->right);
	}
	return 0;
}

void printArray_TreeNode(int *nums, int numsSize)
{
	if (numsSize == 0)
	{
		puts("[]");
		return;
	}
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		if (nums[i] == INT_MIN)
			printf("null,");
		else
			printf("%2d,", nums[i]);
	}
	printf("%2d]", nums[numsSize - 1]);
	puts(" // completely print.");
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

struct Truck
{
	struct Truck *prev;
	char *str;
};

struct Truck *createTruck(struct Truck *prev_tru, char *string)
{
	struct Truck *tru = (struct Truck *)malloc(sizeof(struct Truck));
	tru->prev = prev_tru;
	tru->str = (char *)malloc(50 * sizeof(char));
	strcpy(tru->str, string);
	return tru;
}

void showTrucks(struct Truck *ptr)
{
	if (ptr == NULL)
		return;
	showTrucks(ptr->prev);
	printf("%s", ptr->str);
	return;
}

void printTree(struct TreeNode *root, struct Truck *prev, _Bool is_right)
{
	if (root == NULL)
		return;

	char *prev_str = (char *)malloc(50 * sizeof(char));
	strcpy(prev_str, "    ");
	struct Truck *tru = createTruck(prev, prev_str);

	printTree(root->right, tru, 1);

	if (!prev)
		strcpy(tru->str, " --");
	else if (is_right)
	{
		strcpy(tru->str, ".---");
		strcpy(prev_str, "   |");
	}
	else
	{
		strcpy(tru->str, "`---");
		strcpy(prev->str, prev_str);
	}

	showTrucks(tru);
	printf(" %d\n", root->val);

	if (prev)
		prev->str = prev_str;
	strcpy(tru->str, "   |");
	printTree(root->left, tru, 0);
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("572.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums1[100], numsSize1;
	int nums2[100], numsSize2;
	printf("Input:");
	struct TreeNode *root = dealWithInputFile_forOneTree(pfile, nums1, &numsSize1);
	struct TreeNode *subRoot = dealWithInputFile_forOneTree(pfile, nums2, &numsSize2);
	puts("");

	printf("nums1 = ");
	printArray_TreeNode(nums1, numsSize1);
	printf("nums2 = ");
	printArray_TreeNode(nums2, numsSize2);

	struct Truck *ptr = NULL;
	puts("tree1: ");
	printTree(root, ptr, 0);
	ptr = NULL;
	puts("tree2: ");
	printTree(subRoot, ptr, 0);
	puts("");

	if (isSubtree(root, subRoot))
		puts("true");
	else
		puts("false");

	return 0;
}