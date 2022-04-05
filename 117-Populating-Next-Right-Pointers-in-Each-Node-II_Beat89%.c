#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

//  Definition for a Node.
struct Node
{
	int val;
	struct Node *left;
	struct Node *right;
	struct Node *next;
};

typedef struct stackInformation
{
	int top;
	struct Node **nodes;
} Stack;

Stack *createStack(int size)
{
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->top = -1;
	sta->nodes = (struct Node **)malloc(size * sizeof(struct Node *));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	return sta->top == -1 ? 1 : 0;
}

void pushToStack(Stack *sta, struct Node *node)
{
	(sta->top)++;
	sta->nodes[sta->top] = node;
	return;
}

struct Node *popFromStack(Stack *sta)
{
	if (isEmptyStack(sta))
	{
		puts("The stack is empty!");
		exit(0);
	}
	(sta->top)--;
	return sta->nodes[(sta->top) + 1];
}

void printElementsInStack(Stack *sta)
{
	if (isEmptyStack(sta))
	{
		puts("sta: []");
		return;
	}
	printf("sta: [");
	for (int i = 0; i < sta->top; i++)
		printf("%2d, ", sta->nodes[i]->val);
	printf("%2d]\n", sta->nodes[sta->top]->val);
	return;
}

struct Node *connect(struct Node *root)
{
	if (root == NULL)
		return root;
	Stack *s = createStack(3001);
	Stack *t = createStack(3001);
	pushToStack(t, root);

	struct Node *cur_node, *pre_node;
	while (!isEmptyStack(s) || !isEmptyStack(t))
	{
		if (!isEmptyStack(t))
		{
			pre_node = popFromStack(t);
			if (pre_node->left != NULL)
				pushToStack(s, pre_node->left);
			if (pre_node->right != NULL)
				pushToStack(s, pre_node->right);
		}
		while (!isEmptyStack(t))
		{
			cur_node = popFromStack(t);
			if (cur_node->left != NULL)
				pushToStack(s, cur_node->left);
			if (cur_node->right != NULL)
				pushToStack(s, cur_node->right);
			pre_node->next = cur_node;
			pre_node = cur_node;
		}

		while (!isEmptyStack(s))
		{
			cur_node = popFromStack(s);
			pushToStack(t, cur_node);
		}
	}
	return root;
}

struct Node *buildTree(int *nums, int numsSize)
{
	struct Node **tree = (struct Node **)malloc((numsSize + 1) * sizeof(struct Node *));
	tree[1] = NULL;
	for (int i = 1; i <= numsSize; i++)
	{
		if (nums[i - 1] != INT_MIN)
		{
			tree[i] = (struct Node *)malloc(sizeof(struct Node));
			tree[i]->val = nums[i - 1];
			tree[i]->left = NULL;
			tree[i]->right = NULL;
			tree[i]->next = NULL;
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

struct Node *dealWithInputFile_forOneTree(FILE *pfile)
{
	char c;
	int sum = 0, tmp, numsSize = 0;
	int *nums = (int *)malloc(50 * sizeof(int));
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
			nums[numsSize++] = INT_MIN;
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
			nums[numsSize++] = sum;
			sum = 0;
			if (c == ']')
				break;
		}
	}
	puts("");
	struct Node *root = buildTree(nums, numsSize);
	return root;
}

void printTree_byTwoStack(struct Node *root)
{
	if (root == NULL)
	{
		puts("empty tree!");
		return;
	}
	int size = 100;
	Stack *s = createStack(size);
	Stack *t = createStack(size);
	if (root != NULL)
		pushToStack(t, root);

	struct Node *ptr;
	while (!isEmptyStack(s) || !isEmptyStack(t))
	{
		while (!isEmptyStack(t))
		{
			ptr = popFromStack(t);
			if (ptr->left == NULL)
				printf("%d --left--> NULL\n", ptr->val);
			else
			{
				pushToStack(s, ptr->left);
				printf("%d --left--> %d\n", ptr->val, ptr->left->val);
			}
			if (ptr->right == NULL)
				printf("  --right--> NULL\n", ptr->val);
			else
			{
				pushToStack(s, ptr->right);
				printf("  --right--> %d\n", ptr->right->val);
			}
			if (ptr->next == NULL)
				printf("  --next--> NULL\n", ptr->val);
			else
				printf("  --next--> %d\n", ptr->next->val);
		}

		while (!isEmptyStack(s))
		{
			ptr = popFromStack(s);
			pushToStack(t, ptr);
		}
	}
	puts("// completely print.\n");
	freeStack(s);
	freeStack(t);
	return;
}

void printConnect(struct Node *root)
{
	if (root == NULL)
	{
		puts("Output: []");
		return;
	}
	struct Node *head = root, *ptr;
	printf("Output: [");

	while (1)
	{
		printf("%d,", head->val);
		ptr = head->next;
		while (ptr != NULL)
		{
			printf("%d,", ptr->val);
			ptr = ptr->next;
		}

		while (head != NULL && head->left == NULL && head->right == NULL)
			head = head->next;
		if (head != NULL && head->left != NULL)
			head = head->left;
		else if (head != NULL && head->right != NULL)
			head = head->right;

		if (head != NULL)
			printf("#,");
		else
			break;
	}

	puts("#] // completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("117.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	struct Node *root = dealWithInputFile_forOneTree(pfile);
	puts("original tree:");
	printTree_byTwoStack(root);

	root = connect(root);
	puts("connected tree:");
	printConnect(root);

	return 0;
}