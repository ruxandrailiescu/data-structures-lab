#pragma once
#include "DataUtil.h"

#define PQUEUE_SIZE 7

// MAX PQ IMPLEMENTATION

// currentIndex: no of elements in the PQ
// size: maximum no of elements that can be added in the PQ
typedef struct PQueue
{
	Student** items;
	int size;
	int currentIndex;
}PriorityQueue;

void ReheapUp(Student** items, int currentIndex)
{
	if (currentIndex > 0)
	{
		int parentIndex = (currentIndex - 1) / 2;
		if (items[parentIndex]->income <
			items[currentIndex]->income)
		{
			Student* aux = items[parentIndex];
			items[parentIndex] = items[currentIndex];
			items[currentIndex] = aux;
			ReheapUp(items, parentIndex);
		}
	}
}

void enqueue(struct PQueue* pQueue, Student* info)
{
	if ((*pQueue).items == NULL)
	{
		(*pQueue).items = (Student**)malloc(sizeof(Student*) * PQUEUE_SIZE);
		memset((*pQueue).items, 0, sizeof(Student*) * PQUEUE_SIZE);
		(*pQueue).size = PQUEUE_SIZE;
	}
	if ((*pQueue).size > (*pQueue).currentIndex)
	{
		(*pQueue).items[(*pQueue).currentIndex] = info;
		ReheapUp((*pQueue).items, (*pQueue).currentIndex);
		(*pQueue).currentIndex++;
	}
}

void ReheapDown(PriorityQueue* pQueue, int parentIndex)
{
	int lChildIndex = 2 * parentIndex + 1;
	int rChildIndex = 2 * parentIndex + 2;
	int maxIndex = parentIndex;
	if (lChildIndex < pQueue->currentIndex)
	{
		if (pQueue->items[lChildIndex]->income > pQueue->items[maxIndex]->income)
			maxIndex = lChildIndex;
		if (rChildIndex < pQueue->currentIndex &&
			pQueue->items[rChildIndex]->income > pQueue->items[maxIndex]->income)
			maxIndex = rChildIndex;
		if (maxIndex != parentIndex)
		{
			Student* aux = pQueue->items[maxIndex];
			pQueue->items[maxIndex] = pQueue->items[parentIndex];
			pQueue->items[parentIndex] = aux;
			ReheapDown(pQueue, maxIndex);
		}
	}
}

Student* deque(PriorityQueue* pQueue)
{
	Student* result = NULL;
	if (pQueue->currentIndex > 0)
	{
		result = pQueue->items[0];
		pQueue->items[0] = pQueue->items[pQueue->currentIndex - 1];
		pQueue->currentIndex--;
		ReheapDown(pQueue, 0);
	}
	return result;
}

/*
	HOMEWORK DUE 15/5

	Change priority of PQueue: You will receive the index
	of the student whose income has to be modified with 
	a given value; the priority of the queue has to be
	modified to maintain the appropriate structure.
*/

void changePrio(PriorityQueue* pQueue, int index, float key)
{
	if (index > 0 && index < pQueue->currentIndex) {
		if (pQueue->items[index]->income != key) {
			pQueue->items[index]->income = key;
		}

		int parentIndex = index / 2;
		int lChildIndex = 2 * index + 1;
		int rChildIndex = 2 * index + 2;

		if (pQueue->items[index]->income > pQueue->items[parentIndex]->income) {
			Student* aux = pQueue->items[parentIndex];
			pQueue->items[parentIndex] = pQueue->items[index];
			pQueue->items[index] = aux;
			changePrio(pQueue, parentIndex, pQueue->items[parentIndex]->income);
		}
		else {
			int maxIndex = index;
			if (lChildIndex < pQueue->currentIndex) {
				if (pQueue->items[lChildIndex]->income > pQueue->items[maxIndex]->income)
					maxIndex = lChildIndex;
				if (rChildIndex < pQueue->currentIndex &&
					pQueue->items[rChildIndex]->income > pQueue->items[maxIndex]->income)
					maxIndex = rChildIndex;
				if (maxIndex != index) {
					Student* aux = pQueue->items[maxIndex];
					pQueue->items[maxIndex] = pQueue->items[index];
					pQueue->items[index] = aux;
					changePrio(pQueue, maxIndex, pQueue->items[maxIndex]->income);
				}
			}
		}
	}
}