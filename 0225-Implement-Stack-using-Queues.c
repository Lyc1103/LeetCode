#include <stdio.h>
#include <stdlib.h>

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

typedef struct
{
	int *data;
	int front;
	int rear;
} MyQueue;

void swap(MyQueue *q1, MyQueue *q2)
{
	MyQueue tmp = *q1;
	*q1 = *q2;
	*q2 = tmp;
	return;
}

MyQueue *myQueueCreate()
{
	MyQueue *Q = (MyQueue *)malloc(sizeof(MyQueue));
	Q->data = (int *)calloc(101, sizeof(int));
	Q->front = -1;
	Q->rear = -1;
	return Q;
}

_Bool isEmptyQueue(MyQueue *q)
{
	if (q->front >= q->rear)
		return 1;
	else
		return 0;
}

void pushToBackOfQueue(MyQueue *q, int x)
{
	q->data[++(q->rear)] = x;
	return;
}

int popFromFrontOfQueue(MyQueue *q)
{
	if (isEmptyQueue(q))
		return -1;
	(q->front)++;
	return q->data[q->front];
}

int peekFromFrontOfQueue(MyQueue *q)
{
	if (!isEmptyQueue(q))
		return q->data[(q->front) + 1];
	return -1;
}

int sizeOfQueue(MyQueue *q)
{
	return q->rear - q->front;
}

void freeMyQueue(MyQueue *q)
{
	free(q->data);
	free(q);
	return;
}

typedef struct
{
	MyQueue *q1;
	MyQueue *q2;
} MyStack;

MyStack *myStackCreate()
{
	MyStack *S = (MyStack *)malloc(sizeof(MyStack));
	S->q1 = myQueueCreate();
	S->q2 = myQueueCreate();
	return S;
}

void myStackPush(MyStack *obj, int x)
{
	pushToBackOfQueue(obj->q1, x);
	return;
}

int myStackPop(MyStack *obj)
{
	int ret;
	if (isEmptyQueue(obj->q2))
	{
		if (!isEmptyQueue(obj->q1))
			ret = popFromFrontOfQueue(obj->q1);
		while (!isEmptyQueue(obj->q1))
		{
			pushToBackOfQueue(obj->q2, ret);
			ret = popFromFrontOfQueue(obj->q1);
		}
	}
	swap(obj->q1, obj->q2);
	return ret;
}

int myStackTop(MyStack *obj)
{
	int ret;
	if (isEmptyQueue(obj->q2))
		while (!isEmptyQueue(obj->q1))
		{
			ret = popFromFrontOfQueue(obj->q1);
			pushToBackOfQueue(obj->q2, ret);
		}
	swap(obj->q1, obj->q2);
	return ret;
}

_Bool myStackEmpty(MyStack *obj)
{
	return (isEmptyQueue(obj->q1) && isEmptyQueue(obj->q2));
}

void myStackFree(MyStack *obj)
{
	freeMyQueue(obj->q1);
	freeMyQueue(obj->q2);
	free(obj);
	return;
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);

 * int param_2 = myStackPop(obj);

 * int param_3 = myStackTop(obj);

 * bool param_4 = myStackEmpty(obj);

 * myStackFree(obj);
*/
int main()
{
	MyStack *myStack = myStackCreate();
	myStackPush(myStack, 1);
	myStackPush(myStack, 2);
	printf("q1.front = %d, q1.rear = %d, q1: ", myStack->q1->front, myStack->q1->rear);
	printArray(myStack->q1->data, 10);
	printf("q2.front = %d, q2.rear = %d, q2: ", myStack->q2->front, myStack->q2->rear);
	printArray(myStack->q2->data, 10);

	int res1 = myStackPop(myStack); // return 2
	printf("res1 = %d\n", res1);
	printf("q1.front = %d, q1.rear = %d, q1: ", myStack->q1->front, myStack->q1->rear);
	printArray(myStack->q1->data, 10);
	printf("q2.front = %d, q2.rear = %d, q2: ", myStack->q2->front, myStack->q2->rear);
	printArray(myStack->q2->data, 10);

	int res2 = myStackTop(myStack); // return 2
	printf("res2 = %d\n", res2);
	printf("q1.front = %d, q1.rear = %d, q1: ", myStack->q1->front, myStack->q1->rear);
	printArray(myStack->q1->data, 10);
	printf("q2.front = %d, q2.rear = %d, q2: ", myStack->q2->front, myStack->q2->rear);
	printArray(myStack->q2->data, 10);

	int res3 = myStackEmpty(myStack); // return False
	printf("res3 = %d\n", res3);
	printf("q1.front = %d, q1.rear = %d, q1: ", myStack->q1->front, myStack->q1->rear);
	printArray(myStack->q1->data, 10);
	printf("q2.front = %d, q2.rear = %d, q2: ", myStack->q2->front, myStack->q2->rear);
	printArray(myStack->q2->data, 10);

	return 0;
}