#pragma once
#include "DataUtil.h"

typedef struct NodeS
{
	Student* info;
	struct NodeS* next;
}StackNode, *PStackNode;

StackNode* createStackNode(Student* info)
{
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->info = info;
	node->next = NULL;
	return node;
}

StackNode* pushNode(StackNode* stack, Student* info)
{
	StackNode* node = createStackNode(info);
	node->next = stack;
	return node;
}

Student* peekNode(StackNode* stack)
{
	Student* info = NULL;
	if (stack != NULL)
	{
		info = stack->info;
	}
	return info;
}

Student* popNode(StackNode** stack)
{
	Student* info = NULL;
	if ((*stack) != NULL)
	{
		info = (*stack)->info;
		StackNode* tmp = (*stack);
		(*stack) = tmp->next;
		free(tmp);
	}
	return info;
}

void deleteStack(StackNode** stack)
{
	while ((*stack))
	{
		Student* info = popNode(stack);
		printStudent(info);
		deleteStudent(info);
	}
}

void displayStack(StackNode** stack)
{
	StackNode* tmp = NULL;
	while (*stack)
	{
		Student* info = popNode(stack);
		printStudent(info);
		tmp = pushNode(tmp, info);
	}
	while (tmp)
	{
		Student* info = popNode(&tmp);
		*stack = pushNode(*stack, info);
	}
}