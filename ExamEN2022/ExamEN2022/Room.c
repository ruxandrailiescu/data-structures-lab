#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#define HT_SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Room
{
	unsigned short floor;
	unsigned short roomNo;
	char* type;
	double price;
} Room;

Room* createRoom(unsigned short floor, unsigned short roomNo, const char* type, double price)
{
	Room* room = (Room*)malloc(sizeof(Room));
	room->floor = floor;
	room->roomNo = roomNo;
	room->type = (char*)malloc(strlen(type) + 1);
	strcpy(room->type, type);
	room->price = price;
	return room;
}

void displayRoom(Room* room)
{
	if (room)
	{
		printf("Floor: %d, Room no: %d, Type: %s, Price: %.2f\n",
			room->floor, room->roomNo, room->type, room->price);
	}
}

void deleteRoom(Room* room)
{
	if (room)
	{
		free(room->type);
		free(room);
		room = NULL;
	}
}

typedef struct HashN
{
	Room* info;
	struct HashN* next;
} HashNode;

typedef struct HashT
{
	HashNode** items;
	int size;
} HashTable;

HashNode* createHashNode(Room* room)
{
	HashNode* node = NULL;

	if (room)
	{
		node = (HashNode*)malloc(sizeof(HashNode));
		node->info = room;
		node->next = NULL;
	}

	return node;
}

void initHashTable(HashTable* hashTable, int size)
{
	hashTable->size = size;
	hashTable->items = (HashNode**)malloc(sizeof(HashNode*) * size);
	memset(hashTable->items, 0, sizeof(HashNode*) * size);
}

int fHash(unsigned short key, int size)
{
	return key % size;
}

void putHashTable(HashTable* hashTable, Room* room)
{
	if (hashTable->size == 0)
		initHashTable(hashTable, HT_SIZE);

	HashNode* node = createHashNode(room);
	int index = fHash(room->floor, hashTable->size);
	
	if (hashTable->items[index])
		node->next = hashTable->items[index];
	hashTable->items[index] = node;
}

// 2.
void displayHashTable(HashTable hashTable)
{
	if (hashTable.items && hashTable.size > 0)
	{
		for (int i = 0; i < hashTable.size; i++)
		{
			HashNode* current = hashTable.items[i];
			printf("\n---------- Bucket %d -----------\n", i);
			while (current)
			{
				displayRoom(current->info);
				current = current->next;
			}
		}
	}
}

// 3.
void countRooms(HashTable hashTable, unsigned short floor, int* count)
{
	if (hashTable.items && hashTable.size > 0)
	{
		int index = fHash(floor, hashTable.size);
		HashNode* current = hashTable.items[index];
		while (current)
		{
			(*count)++;
			current = current->next;
		}
	}
}

// 4.
typedef struct Node
{
	struct Node* prev;
	Room* info;
	struct Node* next;
} Node;

Node* createNode(Room* room)
{
	Node* node = NULL;

	if (room)
	{
		node = (Node*)malloc(sizeof(Node));
		node->info = room;
		node->prev = node->next = NULL;
	}

	return node;
}

void insertList(Node** list, Room* room)
{
	Node* node = createNode(room);

	if (node)
	{
		if (*list)
		{
			node->next = *list;
			(*list)->prev = node;
		}
		(*list) = node;
	}
}

Node* createList(HashTable hashTable, double price)
{
	Node* list = NULL;

	if (hashTable.items && hashTable.size > 0)
	{
		for (int i = 0; i < hashTable.size; i++)
		{
			HashNode* current = hashTable.items[i];
			while (current)
			{
				if (current->info->price > price)
				{
					Room* room = createRoom(current->info->floor, current->info->roomNo, current->info->type, current->info->price);
					insertList(&list, room);
				}
				current = current->next;
			}
		}
	}

	return list;
}

void displayList(Node* list)
{
	while (list)
	{
		displayRoom(list->info);
		list = list->next;
	}
}

// 5.
void deleteFromList(Node** list, const char* type)
{
	if (*list)
	{
		Node* tmp = *list;
		while (tmp)
		{
			if (strcmp(tmp->info->type, type) == 0)
			{
				Node* toDelete = tmp;

				if (toDelete->prev)
					toDelete->prev->next = toDelete->next;
				else
				{
					(*list) = toDelete->next;
				}

				if (toDelete->next)
					toDelete->next->prev = toDelete->prev;

				tmp = toDelete->next;

				deleteRoom(toDelete->info);
				free(toDelete);
			}
			else
			{
				tmp = tmp->next;
			}
		}
	}
}

void main()
{
	HashTable hashTable = { .items = NULL,.size = 0 };

	FILE* pFile = fopen("DataRoom.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",\n";
		char* token = NULL;
		char buffer[LINE_SIZE], type[LINE_SIZE];
		unsigned short floor, roomNo;
		double price;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			floor = atoi(token);
			token = strtok(NULL, delimiter);
			roomNo = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(type, token);
			token = strtok(NULL, delimiter);
			price = atof(token);

			Room* room = createRoom(floor, roomNo, type, price);
			//displayRoom(room);
			putHashTable(&hashTable, room);
		}
		// 2.
		displayHashTable(hashTable);

		// 3.
		int count = 0;
		countRooms(hashTable, 2, &count);
		printf("\nCount: %d\n\n", count);

		// 4.
		Node* list = createList(hashTable, 10);
		displayList(list);

		// 5.
		deleteFromList(&list, "penthouse");
		printf("\n\n-----------------------------\n");
		displayList(list);
	}
}