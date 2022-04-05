#include <stdio.h>

// typedef struct{
// 	int data;
// 	TreeNode *parent;
// 	TreeNode *lchild;
// 	TreeNode *rchild;
// } TreeNode;

typedef struct
{
	int top, min;
	int *data;
} MinStack;

MinStack *minStackCreate()
{
	MinStack *obj = (MinStack *)malloc(sizeof(MinStack));
	obj->top = 0;
	obj->min = 0;
	obj->data = (int *)calloc(300002, sizeof(int));
	return obj;
}

void minStackPush(MinStack *obj, int val)
{
	if (obj->top == 0)
	{
		obj->min = val;
	}
	else if (obj->min >= val)
	{
		obj->data[++(obj->top)] = obj->min;
		obj->min = val;
	}
	obj->data[++(obj->top)] = val;
}

void minStackPop(MinStack *obj)
{
	if (obj->top <= 0)
	{
		puts("Invaild Pop! Stack is empty.\n");
		return;
	}
	int tmp = obj->data[(obj->top)--];
	if (tmp == obj->min && obj->top > 0)
	{
		obj->min = obj->data[(obj->top)--];
	}
	return;
}

int minStackTop(MinStack *obj)
{
	return obj->data[obj->top];
}

int minStackGetMin(MinStack *obj)
{
	return obj->min;
}

void minStackFree(MinStack *obj)
{
	free(obj->data);
	return;
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/

int main()
{
	MinStack minStack = minStackCreate();
	minStack.push(-2);
	minStack.push(0);
	minStack.push(-3);
	int res1 = minStack.getMin(); // return -3
	minStack.pop();
	int res2 = minStack.top();    // return 0
	int res3 = minStack.getMin(); // return -2
	printf("res1 = %d, res2 = %d, res3 = %d\n", res1, res2, res3);

	return 0;
}