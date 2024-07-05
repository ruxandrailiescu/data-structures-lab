#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#define HT_SIZE 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Request
{
	unsigned int id;
	unsigned int size;
	unsigned short priority;
	char* src;
	char* dst;
} Request;

Request* createRequest(unsigned int id, unsigned int size, unsigned short priority, const char* src, const char* dst)
{
	Request* request = NULL;

	if (src && dst)
	{
		request = (Request*)malloc(sizeof(Request));
		request->id = id;
		request->size = size;
		request->priority = priority;
		request->src = (char*)malloc(strlen(src) + 1);
		strcpy(request->src, src);
		request->dst = (char*)malloc(strlen(dst) + 1);
		strcpy(request->dst, dst);
	}

	return request;
}

void displayRequest(Request* request)
{
	if (request)
	{
		printf("\nId: %d, Size: %d, Priority: %d, Source IP: %s, Destination IP: %s\n",
			request->id, request->size, request->priority, request->src, request->dst);
	}
}

typedef struct Node
{
	struct Node* prev;
	Request* info;
	struct Node* next;
} Node;

Node* createNode(Request* request)
{
	Node* node = NULL;

	if (request)
	{
		node = (Node*)malloc(sizeof(Node));
		node->info = request;
		node->prev = node->next = NULL;
	}

	return node;
}

void insertNodeAscending(Node** list, Request* request)
{
	Node* node = createNode(request);

	if (node)
	{
		if (!(*list))
			*list = node;
		else
		{
			Node* tmp = *list;
			Node* prev = NULL;

			while (tmp && (tmp->info->size <= node->info->size))
			{
				prev = tmp;
				tmp = tmp->next;
			}

			if (!prev)
			{
				node->next = *list;
				(*list)->prev = node;
				*list = node;
			}
			else
			{
				prev->next = node;
				node->prev = prev;

				if (tmp)
				{
					tmp->prev = node;
					node->next = tmp;
				}
			}
		}
	}
}

void displayList(Node* list)
{
	while (list)
	{
		displayRequest(list->info);
		list = list->next;
	}
}

// 2.
void displayListDesc(Node* list)
{
	while (list->next)
		list = list->next;

	while (list)
	{
		displayRequest(list->info);
		list = list->prev;
	}
}

// 3.
void countRequests(Node* list, const char* src, int* count)
{
	while (list)
	{
		if (strcmp(list->info->src, src) == 0)
			(*count)++;
		list = list->next;
	}
}

// 4.
void updateRequests(Node* list, unsigned int id, unsigned short newPrio)
{
	Node* tmp = list;
	while (tmp)
	{
		if (tmp->info->id == id)
			tmp->info->priority = newPrio;
		tmp = tmp->next;
	}
}

// 5.
void deleteRequests(Node** list, const char* dst)
{
	Node* tmp = *list;
	while (tmp)
	{
		if (strcmp(tmp->info->dst, dst) == 0)
		{
			Node* toDelete = tmp;

			if (toDelete->prev)
			{
				toDelete->prev->next = toDelete->next;
			}
			else
			{
				*list = toDelete->next;
			}

			if (toDelete->next)
			{
				toDelete->next->prev = toDelete->prev;
			}

			tmp = toDelete->next;

			free(toDelete->info->src);
			free(toDelete->info->dst);
			free(toDelete->info);
			free(toDelete);
		}
		else
		{
			tmp = tmp->next;
		}
	}
}

// 6.
typedef struct HashT
{
	Request** items;
	int size;
} HashTable;

void initHashTable(HashTable* hashTable, int size)
{
	hashTable->size = size;
	hashTable->items = (Request**)malloc(sizeof(Request*) * size);
	memset(hashTable->items, 0, sizeof(Request*) * size);
}

int fHash(unsigned int key, int size)
{
	return key % size;
}

void putHashTable(HashTable* hashTable, Request* request);

void resizeHashTable(HashTable* hashTable)
{
	Request** aux = hashTable->items;
	initHashTable(hashTable, hashTable->size * 3);

	for (int i = 0; i < hashTable->size / 3; i++)
	{
		Request* request = aux[i];

		if (request)
		{
			putHashTable(hashTable, request);
		}
	}
}

int linearProbing(HashTable* hashTable, unsigned int key, int index)
{
	while (hashTable->items[index] != NULL)
	{
		index++;
		if (hashTable->size == index)
		{
			resizeHashTable(hashTable);
			index = fHash(key, hashTable->size);
		}
	}
}

void putHashTable(HashTable* hashTable, Request* request)
{
	if (hashTable->size == 0)
		initHashTable(hashTable, HT_SIZE);

	int index = fHash(request->size, hashTable->size);

	if (hashTable->items[index] != NULL)
	{
		index = linearProbing(hashTable, request->size, index);
	}

	hashTable->items[index] = request;
}

void insertHTFromDLL(Node* list, HashTable* hashTable)
{
	while (list)
	{
		putHashTable(hashTable, list->info);
		list = list->next;
	}
}

void displayHashTable(HashTable hashTable)
{
	if (hashTable.items && hashTable.size > 0)
	{
		for (int i = 0; i < hashTable.size; i++)
		{
			printf("\n----------------- Bucket %d --------------\n", i);
			displayRequest(hashTable.items[i]);
		}
	}
}

void main()
{
	Node* list = NULL;

	FILE* pFile = fopen("DataRequest.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",\n";
		char* token = NULL;
		char buffer[LINE_SIZE], src[LINE_SIZE], dst[LINE_SIZE];
		unsigned int id, size;
		unsigned short priority;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			id = atoi(token);
			token = strtok(NULL, delimiter);
			size = atoi(token);
			token = strtok(NULL, delimiter);
			priority = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(src, token);
			token = strtok(NULL, delimiter);
			strcpy(dst, token);

			Request* request = createRequest(id, size, priority, src, dst);
			//displayRequest(request);

			insertNodeAscending(&list, request);
		}
		fclose(pFile);

		//displayList(list);

		// 2.
		printf("\n------------------------------------------\n");
		displayListDesc(list);

		// 3.
		int count = 0;
		countRequests(list, "132.15", &count);
		printf("\nCount: %d\n", count);

		// 4.
		//updateRequests(list, 123, 0);
		//displayList(list);

		// 5.
		//deleteRequests(&list, "120.12");
		//displayList(list);

		// 6.
		HashTable hashTable = { .items = NULL,.size = 0 };
		insertHTFromDLL(list, &hashTable);
		displayHashTable(hashTable);
	}
}