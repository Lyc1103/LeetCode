#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
// For Files Pre-Treatment
int main()
{
	FILE *pfile;
	if ((pfile = fopen(filename, "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	// ...

	return 0;
}

// Deal With An Input File
int *dealWithInputFile_ForNums(FILE *pfile, int *numsSize);
char *dealWithInputFile_ForString(FILE *pfile, int *strSize);
int **dealWithInputFile_forMatrix(FILE *pfile, int *matSize, int **matColSize);
struct TreeNode *dealWithInputFile_forOneTree(FILE *pfile, int *nums, int *numsSize);

// For "Prints"
void swap(int *a, int *b);
int cmpFunction(const void *a, const void *b);
void printArray_int(int *nums, int numsSize);
void printArray_char(char *str, int strSize);
void printMatrix_int(int **mat, int matSize, int matColSize);

// Combinatorics
int P(int m, int n);
int C(int m, int n);

// Binary Search
int binarySearch_Array_Recursion(int *nums, int left, int right, int target);
int binarySearch_Array_Iteration(int *nums, int front, int rear, int target);
_Bool binarySearch_Matrix(int **matrix, int matrixSize, int *matrixColSize, int target);

// General Stack Data Structure
typedef struct stackInformation
{
	int top;
	int *data;
} Stack;
Stack *createStack(int size);
_Bool isEmptyStack(Stack *sta);
void pushToStack(Stack *sta, int data);
int popFromStack(Stack *sta);
void freeStack(Stack *sta);
void printElementsInStack(Stack *sta);
void cpyElementsFromStackToArray(Stack *sta, int **ret, int *ctr);

// For Link List Data Structure
struct ListNode
{
	int val;
	struct ListNode *next;
};
struct ListNode *insertLinkListFromHead(struct ListNode *head, int data);
struct ListNode *middleNode(struct ListNode *head);
void printLinkList(struct ListNode *head);
void printLinkListInArray(struct ListNode *head);

// For Node's Data Structure
// Definition for a Node.
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
Stack *createStack(int size);
_Bool isEmptyStack(Stack *sta);
void pushToStack(Stack *sta, struct Node *node);
struct Node *popFromStack(Stack *sta);
void printElementsInStack(Stack *sta);
struct Node *connect(struct Node *root);
struct Node *buildTree(int *nums, int numsSize);
struct Node *dealWithInputFile_forOneTree(FILE *pfile);
void printTree_byTwoStack(struct Node *root);
void printConnect(struct Node *root);
int mainOfNode();

// For Tree's Data Structure
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
Stack *createStack(int size);
_Bool isEmptyStack(Stack *sta);
void pushToStack(Stack *sta, struct TreeNode *ptr);
struct TreeNode *popFromStack(Stack *sta);
void printTree_byTwoStacks(struct TreeNode *root);
typedef struct
{
	int front, rear;
	struct TreeNode **data;
} Queue;

Queue *createQueue(int size);
_Bool isEmptyQueue(Queue *que);
void enQueue(Queue *que, struct TreeNode *ptr);
struct TreeNode *deQueue(Queue *que);
void printQueueElements(Queue *que);
void printTree_byQueue(struct TreeNode *root);

struct TreeNode *buildTree(int *nums, int numsSize);
struct TreeNode *mergeTrees(struct TreeNode *root1, struct TreeNode *root2);
struct TreeNode *dealWithInputFile_forOneTree(FILE *pfile, int *nums, int *numsSize);
int mainFunctionOfTree(char *filename);

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////////////////////                             ////////////////////
////////////////////   For Files Pre-Treatment   ////////////////////
////////////////////                             ////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

int main()
{
	FILE *pfile;
	if ((pfile = fopen(filename, "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	// ...

	return 0;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////////////////////                             ////////////////////
////////////////////   Deal With An Input File   ////////////////////
////////////////////                             ////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

int *dealWithInputFile_ForNums(FILE *pfile, int *numsSize)
{
	char c;
	int sum = 0, flag = 0;
	*numsSize = 0;
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
		{
			if (flag)
			{
				nums[*numsSize] = sum;
				(*numsSize)++;
			}
			break;
		}
		if (c == ',')
		{
			nums[*numsSize] = sum;
			(*numsSize)++;
			sum = 0;
		}
		else
		{
			sum = sum * 10 + (c - '0');
			flag = 1;
		}
	}
	return nums;
}

char *dealWithInputFile_ForString(FILE *pfile, int *strSize)
{
	char c;
	char *str = (char *)malloc(50 * sizeof(char));
	*strSize = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '"')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '"')
			break;
		str[*strSize] = c;
		(*strSize)++;
	}
	str[*strSize] = '\0';
	return str;
}

int **dealWithInputFile_forMatrix(FILE *pfile, int *matSize, int **matColSize)
{
	int size = 10;
	int **mat = (int **)malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++)
	{
		mat[i] = (int *)malloc(size * sizeof(int));
		*matColSize = (int *)calloc(size, sizeof(int));
	}
	char c;
	int ctr = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		while (!feof(pfile))
		{
			fscanf(pfile, "%c", &c);
			printf("%c", c);
			if (c == '[')
				break;
		}
		while (!feof(pfile))
		{
			fscanf(pfile, "%d", &mat[*matSize][ctr]);
			printf("%d", mat[*matSize][ctr]);
			ctr++;
			fscanf(pfile, "%c", &c);
			printf("%c", c);
			if (c == ']')
			{
				(*matColSize)[*matSize] = ctr;
				(*matSize)++;
				ctr = 0;
				break;
			}
		}
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
	}
	puts("");
	return mat;
}

char **dealWithInputFile_forGrid(FILE *pfile, int *gridSize, int **gridColSize)
{
	int size = 10;
	char **grid = (char **)malloc(size * sizeof(char *));
	for (int i = 0; i < size; i++)
	{
		grid[i] = (char *)malloc(size * sizeof(char));
		*gridColSize = (int *)calloc(size, sizeof(int));
	}
	char c;
	int ctr = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		while (!feof(pfile))
		{
			fscanf(pfile, "%c", &c);
			printf("%c", c);
			if (c == '[')
				break;
		}
		while (!feof(pfile))
		{
			fscanf(pfile, "\"%c\"", &grid[*gridSize][ctr]);
			printf("\"%c\"", grid[*gridSize][ctr]);
			ctr++;
			fscanf(pfile, "%c", &c);
			printf("%c", c);
			if (c == ']')
			{
				(*gridColSize)[*gridSize] = ctr;
				(*gridSize)++;
				ctr = 0;
				break;
			}
		}
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
	}
	puts("");
	return grid;
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

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////////////////////                             ////////////////////
////////////////////        For "Prints"         ////////////////////
////////////////////                             ////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int cmpFunction(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

void printArray_int(int *nums, int numsSize)
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

void printArray_char(char *str, int strSize)
{
	printf("\"");
	for (int i = 0; i < strSize - 1; i++)
	{
		printf("%c", str[i]);
	}
	if (strSize == 0)
		puts("\"");
	else
		printf("%c\"", str[strSize - 1]);
	puts(" //  completely print.");
	return;
}

void printMatrix_int(int **mat, int matSize, int matColSize)
{
	if (matSize == 0)
		puts("mat:\n    []");
	else
	{
		printf("mat:  ");
		for (int i = 0; i < matColSize; i++)
			printf("  %d", i);
		puts("");
		for (int i = 0; i < matSize; i++)
		{
			printf("    %d [", i);
			for (int j = 0; j < matColSize - 1; j++)
				printf("%2d,", mat[i][j]);
			printf("%2d]\n", mat[i][matColSize - 1]);
		}
	}
	puts("    completely print.");
	return;
}

void printGrid(char **grid, int gridSize, int gridColSize)
{
	if (gridSize == 0)
		puts("grid:\n  []");
	else
	{
		printf("grid: ");
		for (int i = 0; i < gridColSize; i++)
			printf("   %d", i);
		puts("");
		for (int i = 0; i < gridSize; i++)
		{
			printf("     %d [", i);
			for (int j = 0; j < gridColSize - 1; j++)
				printf("\"%c\",", grid[i][j]);
			printf("\"%c\"]\n", grid[i][gridColSize - 1]);
		}
	}
	puts("     completely print.");
	return;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///////////////////                              ////////////////////
///////////////////        Combinatorics         ////////////////////
///////////////////                              ////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

int P(int m, int n)
{
	int i, res = 1;
	for (i = m; i > m - n; i--)
	{
		res *= i;
	}
	return res;
}

int C(int m, int n)
{
	int *pre_row = (int *)calloc(20, sizeof(int));
	int *cur_row = (int *)calloc(20, sizeof(int));
	int i, j, *tmp;
	if ((n == 0) || (m == n))
		return 1;
	pre_row[0] = 1;
	cur_row[0] = 1;
	n = m - n < n ? m - n : n;
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= i && j <= n; j++)
			cur_row[j] = pre_row[j] + pre_row[j - 1];
		tmp = pre_row;
		pre_row = cur_row;
		cur_row = tmp;
	}
	return pre_row[n];
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////////////////////                             ////////////////////
////////////////////        Binary Search        ////////////////////
////////////////////                             ////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/* Standard Binary Search function*/
int binarySearch_Array_Recursion(int *nums, int left, int right, int target)
{
	if (right < left)
		return -1;

	int mid = left + (right - left) / 2;
	if (target == nums[mid])
		return mid;
	if (target > nums[mid])
		return binarySearch(nums, mid + 1, right, target);
	else
		return binarySearch(nums, left, mid - 1, target);
}

int binarySearch_Array_Iteration(int *nums, int front, int rear, int target)
{
	int mid;
	while (front <= rear)
	{
		mid = (front + rear) / 2;
		if (nums[mid] == target)
			return mid;
		if (nums[mid] < target)
			front = mid + 1;
		else
			rear = mid - 1;
	}
	return -1;
}

_Bool binarySearch_Matrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{
	for (int front = 0, rear = matrixSize * matrixColSize[0], mid; front < rear;)
	{
		mid = (front + rear) / 2;
		if (matrix[mid / matrixColSize[0]][mid % matrixColSize[0]] == target)
			return 1;
		else if (matrix[mid / matrixColSize[0]][mid % matrixColSize[0]] <= target)
			front = mid + 1;
		else
			rear = mid;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///////////////////                              ////////////////////
/////////////////// General Stack Data Structure ////////////////////
///////////////////                              ////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

typedef struct stackInformation
{
	int top;
	int *data;
} Stack;

Stack *createStack(int size)
{
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->top = -1;
	sta->data = (int *)malloc(size * sizeof(int));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	return sta->top == -1 ? 1 : 0;
}

void pushToStack(Stack *sta, int data)
{
	(sta->top)++;
	sta->data[sta->top] = data;
	return;
}

int popFromStack(Stack *sta)
{
	(sta->top)--;
	return sta->data[(sta->top) + 1];
}

void freeStack(Stack *sta)
{
	free(sta->data);
	free(sta);
	return;
}

void printElementsInStack(Stack *sta)
{
	if (isEmptyStack(sta))
	{
		puts("sta = []");
		return;
	}
	printf("sta = [");
	int i;
	for (i = 0; i < sta->top; i++)
		printf("%d,", sta->data[i]);
	printf("%d]\n", sta->data[i]);
	return;
}

void cpyElementsFromStackToArray(Stack *sta, int **ret, int *ctr)
{
	for (int i = 0; i <= sta->top; i++)
		ret[*ctr][i] = sta->data[i];
	(*ctr)++;
	return;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///////////////////                              ////////////////////
/////////////////// For Link List Data Structure ////////////////////
///////////////////                              ////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

//   Definition for singly-linked list.
struct ListNode
{
	int val;
	struct ListNode *next;
};

struct ListNode *insertListNodeFromHead(struct ListNode *head, int data)
{
	struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
	newNode->val = data;
	if (head == NULL)
		newNode->next = NULL;
	else
		newNode->next = head;
	return newNode;
}

struct ListNode *middleNode(struct ListNode *head)
{
	struct ListNode *ptr = head, *res = head;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		if (ptr != NULL)
		{
			ptr = ptr->next;
			res = res->next;
		}
	}
	return res;
}

void printLinkList(struct ListNode *head)
{
	printf("head -> ");
	struct ListNode *ptr = head;
	while (ptr != NULL)
	{
		printf("%d -> ", ptr->val);
		ptr = ptr->next;
	}
	puts("NULL");
	return;
}

void printLinkListInArray(struct ListNode *head)
{
	printf("[");
	struct ListNode *ptr = head;
	while (ptr->next != NULL)
	{
		printf("%d,", ptr->val);
		ptr = ptr->next;
	}
	printf("%d]\n", ptr->val);
	return;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////////////////////                             ////////////////////
////////////////////  For Node's Data Structure  ////////////////////
////////////////////                             ////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

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

int mainOfNode()
{
	FILE *pfile;
	if ((pfile = fopen("filename.txt", "r")) == NULL)
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

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////////////////////                             ////////////////////
////////////////////  For Tree's Data Structure  ////////////////////
////////////////////                             ////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

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

void printTree_byTwoStack(struct TreeNode *root)
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

typedef struct
{
	int front, rear;
	struct TreeNode **data;
} Queue;

Queue *createQueue(int size)
{
	Queue *que;
	que->front = -1;
	que->rear = -1;
	que->data = (struct TreeNode **)malloc(size * sizeof(struct TreeNode *));
	return que;
}

_Bool isEmptyQueue(Queue *que)
{
	if (que->front == que->rear)
		return 1;
	return 0;
}

void enQueue(Queue *que, struct TreeNode *ptr)
{
	(que->rear)++;
	que->data[que->rear] = ptr;
	return;
}

struct TreeNode *deQueue(Queue *que)
{
	if (isEmptyQueue(que))
	{
		puts("The Queue is empty!");
		exit(0);
		return NULL;
	}
	(que->front)++;
	return que->data[que->front];
}

void printQueueElements(Queue *que)
{
	if (isEmptyQueue(que))
		return;
	printf("current queue = [");
	for (int i = (que->front) + 1; i < que->rear; i++)
		printf("%d,", que->data[i]->val);
	printf("%d]\n", que->data[que->rear]->val);
	return;
}

void printTree_byQueue(struct TreeNode *root)
{
	int size = 100;
	Queue q;
	q.front = q.rear = -1;
	q.data = (struct TreeNode **)malloc(size * sizeof(struct TreeNode *));
	if (root != NULL)
		enQueue(&q, root);
	printQueueElements(&q);

	struct TreeNode *ptr;
	while (!isEmptyQueue(&q))
	{
		ptr = deQueue(&q);
		if (ptr->left == NULL)
			printf("%d --left--> NULL\n", ptr->val);
		else
		{
			enQueue(&q, ptr->left);
			printf("%d --left--> %d\n", ptr->val, ptr->left->val);
		}
		if (ptr->right == NULL)
			printf("%d --right--> NULL\n", ptr->val);
		else
		{
			enQueue(&q, ptr->right);
			printf("%d --right--> %d\n", ptr->val, ptr->right->val);
		}
		printQueueElements(&q);
	}
	puts("completely print.");
	free(q.data);
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

int mainFunctionOfTree(char *filename)
{
	FILE *pfile;
	if ((pfile = fopen(filename, "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums1[100], numsSize1;
	int nums2[100], numsSize2;
	puts("input:");
	struct TreeNode *root1 = dealWithInputFile_forOneTree(pfile, nums1, &numsSize1);
	struct TreeNode *root2 = dealWithInputFile_forOneTree(pfile, nums2, &numsSize2);
	puts("");

	printf("nums1 = ");
	printArray_int(nums1, numsSize1);
	printf("nums2 = ");
	printArray_int(nums2, numsSize2);
	puts("tree1: ");
	printTree_byTwoStack(root1);
	puts("tree2: ");
	printTree_byTwoStack(root2);
	puts("");

	return 0;
}