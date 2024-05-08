#include "main.h"
#include <stdbool.h>

// Leetcode #20

/*
	Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', 
	determine if the input string is valid.

	An input string is valid if:

	Open brackets must be closed by the same type of brackets.
	Open brackets must be closed in the correct order.
	Every close bracket has a corresponding open bracket of the same type.
*/

struct Node {
	char val;
	struct Node* next;
};

struct Stack {
	struct Node* head;
	size_t len;
};

struct Node* Node(char val, struct Node* next) {
	struct Node* root = (struct Node*)malloc(sizeof(struct Node));
	root->next = next;
	root->val = val;
	return root;
}

struct Stack* Stack() {
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->len = 0;
	stack->head = NULL;
	return stack;
}

void append(struct Stack* stack, char val) {
	struct Node* node = Node(val, stack->head);
	stack->head = node;
	stack->len += 1;
}

char pop(struct Stack* stack) {
	if (stack->head == NULL) {
		return NULL;
	}
	char val = stack->head->val;
	struct Node* tmp = stack->head;
	stack->head = stack->head->next;
	stack->len -= 1;
	free(tmp);
	return val;
}

void freeStack(struct Stack* stack) {
	while (pop(stack) != NULL) {
		pop(stack);
	}
	free(stack);
}

char oppositeParenthesis(char closing)
{
	char opening = NULL;
	if (closing == ')')
	{
		opening = '(';
	}
	else if (closing == ']')
	{
		opening = '[';
	}
	else if (closing == '}')
	{
		opening = '{';
	}
	return opening;
}

bool isValid(char* s)
{
	// when encountering an opening bracket => push
	// when encountering a closing bracket => check if
	// top of stack was the opening one for it
	// if yes, pop from stack; else return false
	struct Stack* stack = Stack();
	char* chr;

	for (chr = s; *chr != '\0'; chr++) {
		if (oppositeParenthesis(*chr) == NULL) {
			// we have an opening bracket
			append(stack, *chr);
		}
		else if (stack->len != 0 && oppositeParenthesis(*chr) == pop(stack)) {
			// opening and closing parentheses match
			continue;
		}
		else {
			return false;
		}
	}
	bool result = stack->len == 0;
	freeStack(stack);
	return result;
}

void mainVP()
{
	char s[] = "()[]{}";
	bool is = isValid(s);
	printf("\n%d", is);
}