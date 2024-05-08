#include "main.h"
#include <assert.h>

// Leetcode #155

/*
	Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

	Implement the MinStack class:

	MinStack() initializes the stack object.
	void push(int val) pushes the element val onto the stack.
	void pop() removes the element on the top of the stack.
	int top() gets the top element of the stack.
	int getMin() retrieves the minimum element in the stack.

	You must implement a solution with O(1) time complexity for each function.
*/

// A structure to represent an element of the stack
typedef struct Node {
	int val;
	struct Node* next;
} Node;

Node* nodeCreate(int val) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->val = val;
	node->next = NULL;
	return node;
}

void nodePush(Node** obj, int val) {
	assert(obj);
	Node* node = (Node*)malloc(sizeof(Node));
	node->val = val;
	node->next = *obj;
	*obj = node;
}

void nodePop(Node** obj) {
	assert(obj);
	if (*obj) {
		Node* tmp = *obj;
		*obj = tmp->next;
		free(tmp);
	}
}

// A structure to represent a stack
typedef struct Stack {
	int size;
	Node* top;
} Stack;

Stack* stackCreate() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->size = 0;
	stack->top = NULL;
	return stack;
}

void stackPush(Stack* stack, int val) {
	if (!stack->top) {
		stack->top = nodeCreate(val);
	}
	else {
		nodePush(&stack->top, val);
	}
	stack->size++;
}

void stackPop(Stack* stack) {
	nodePop(&stack->top);
	stack->size--;
}

int stackTop(Stack* stack) {
	assert(stack);
	assert(stack->top);
	return stack->top->val;
}

typedef struct MinStack {
	Stack* stack;
	Stack* minStack;
} MinStack;

MinStack* minStackCreate() {
	MinStack* min = (MinStack*)malloc(sizeof(MinStack));
	min->stack = NULL;
	min->minStack = NULL;
	return min;
}

// Keep the min value on top of the minStack
void minStackPush(MinStack* obj, int val) {
	assert(obj);
	if (!obj->stack) {
		obj->stack = stackCreate();
		obj->minStack = stackCreate();
	}
	stackPush(obj->stack, val);
	if (obj->minStack->top) {
		int minTop = stackTop(obj->minStack);
		if (val < minTop) {
			stackPush(obj->minStack, val);
		}
		else {
			stackPush(obj->minStack, minTop);
		}
	}
	else {
		stackPush(obj->minStack, val);
	}
}

void minStackPop(MinStack* obj) {
	assert(obj);
	stackPop(obj->stack);
	stackPop(obj->minStack);
}

int minStackTop(MinStack* obj) {
	assert(obj);
	return stackTop(obj->stack);
}

int minStackGetMin(MinStack* obj) {
	assert(obj);
	return stackTop(obj->minStack);
}

void minStackFree(MinStack* obj) {
	assert(obj);
	if (obj->stack) {
		while (obj->stack->top) {
			stackPop(obj->stack);
		}
		while (obj->minStack->top) {
			stackPop(obj->minStack);
		}
		free(obj->stack);
		free(obj->minStack);
	}
	free(obj);
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

void mainMS() {

	MinStack* obj = minStackCreate();
	minStackPush(obj, 2);
	minStackPush(obj, 5);
	minStackPush(obj, -2);
	minStackPush(obj, 7);
	minStackPush(obj, -10);
	minStackPush(obj, 3);
//	minStackPop(obj);
	int param1 = minStackTop(obj);
	int param2 = minStackGetMin(obj);
	printf("\n%d", param1);
	printf("\n%d", param2);
	minStackFree(obj);
}