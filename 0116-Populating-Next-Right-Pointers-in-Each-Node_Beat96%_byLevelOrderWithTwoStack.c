#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// Definition for a Node.
struct Node
{
	int val;
	struct Node *left;
	struct Node *right;
	struct Node *next;
};

typedef struct
{
	int top;
	struct Node **data;
} Stack;

Stack *createStack(int size)
{
	Stack *sta;
	sta->top = -1;
	sta->data = (struct Node **)malloc(size * sizeof(struct Node *));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	if (sta->top == -1)
		return 1;
	return 0;
}

void pushToStack(Stack *sta, struct Node *ptr)
{
	(sta->top)++;
	sta->data[sta->top] = ptr;
	return;
}

struct Node *popFromStack(Stack *sta)
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

void printStackElements(Stack *sta)
{
	if (isEmptyStack(sta))
		return;
	int top = sta->top;
	printf("current stack = [");
	for (int i = 0; i < top; i++)
		printf("%d,", sta->data[i]->val);
	printf("%d]\n", sta->data[top]->val);
	return;
}

void printTree(struct Node *root)
{
	int size = 100;
	Stack s, t;
	s.top = t.top = -1;
	s.data = (struct Node **)malloc(size * sizeof(struct Node *));
	t.data = (struct Node **)malloc(size * sizeof(struct Node *));
	if (root != NULL)
		pushToStack(&t, root);
	printStackElements(&t);

	struct Node *ptr;
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
			if (ptr->next == NULL)
				printf("%d --next--> NULL\n", ptr->val);
			else
				printf("%d --next--> %d\n", ptr->val, ptr->next->val);
		}
		printStackElements(&s);

		while (!isEmptyStack(&s))
		{
			ptr = popFromStack(&s);
			pushToStack(&t, ptr);
		}
	}
	puts("completely print.");
	free(s.data);
	free(t.data);
	return;
}

struct Node *buildTree(int *nums, int numsSize)
{
	struct Node **tree = (struct Node **)malloc((numsSize + 1) * sizeof(struct Node *));
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

struct Node *dealWithInputFile_forOneTree(FILE *pfile, int *nums, int *numsSize)
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
	struct Node *root = buildTree(nums, *numsSize);
	return root;
}

struct Node *connect(struct Node *root)
{
	int size = 2048;
	Stack s, t;
	s.top = t.top = -1;
	s.data = (struct Node **)malloc(size * sizeof(struct Node *));
	t.data = (struct Node **)malloc(size * sizeof(struct Node *));
	if (root != NULL)
		pushToStack(&t, root);

	struct Node *ptr1, *ptr2;
	while (!isEmptyStack(&s) || !isEmptyStack(&t))
	{
		if (!isEmptyStack(&t))
		{
			ptr1 = popFromStack(&t);
			if (ptr1->left != NULL)
				pushToStack(&s, ptr1->left);
			if (ptr1->right != NULL)
				pushToStack(&s, ptr1->right);
		}
		while (!isEmptyStack(&t))
		{
			ptr2 = popFromStack(&t);
			ptr1->next = ptr2;
			if (ptr2->left != NULL)
				pushToStack(&s, ptr2->left);
			if (ptr2->right != NULL)
				pushToStack(&s, ptr2->right);
			ptr1 = ptr2;
		}

		while (!isEmptyStack(&s))
		{
			ptr1 = popFromStack(&s);
			pushToStack(&t, ptr1);
		}
	}
	free(s.data);
	free(t.data);
	return root;
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

int main()
{
	FILE *pfile;
	if ((pfile = fopen("116.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums[100], numsSize;
	puts("input:");
	struct Node *root = dealWithInputFile_forOneTree(pfile, nums, &numsSize);
	puts("");

	printf("nums = ");
	printArray_int(nums, numsSize);
	puts("tree: ");
	printTree(root);
	puts("");

	struct Node *res = connect(root);
	puts("res tree: ");
	printTree(res);

	return 0;
}