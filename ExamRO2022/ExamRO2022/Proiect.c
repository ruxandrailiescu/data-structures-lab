#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#define HT_SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


typedef struct Proiect
{
	unsigned int cod;
	char* titlu;
	char* beneficiar;
	unsigned char nrExec;
	float buget;
} Proiect;

Proiect* creareProiect(unsigned int cod, const char* titlu, const char* beneficiar,
	unsigned char nrExec, float buget)
{
	Proiect* proiect = NULL;

	if (titlu && beneficiar)
	{
		proiect = (Proiect*)malloc(sizeof(Proiect));
		proiect->cod = cod;
		proiect->titlu = (char*)malloc(strlen(titlu) + 1);
		strcpy(proiect->titlu, titlu);
		proiect->beneficiar = (char*)malloc(strlen(beneficiar) + 1);
		strcpy(proiect->beneficiar, beneficiar);
		proiect->nrExec = nrExec;
		proiect->buget = buget;
	}

	return proiect;
}

void afisareProiect(Proiect* proiect)
{
	if (proiect)
	{
		printf("Cod: %d, Titlu: %s, Beneficiar: %s, Nr executanti: %d, Buget: %.2f\n",
			proiect->cod, proiect->titlu, proiect->beneficiar, proiect->nrExec, proiect->buget);
	}
}

// HASHTABLE IMPLEMENTATION -- CHAINING
typedef struct HashN
{
	Proiect* info;
	struct HashN* next;
} HashNode;

typedef struct HashT
{
	HashNode** items;
	int size;
} HashTable;

HashNode* creareHashNode(Proiect* proiect)
{
	HashNode* node = NULL;
	if (proiect)
	{
		node = (HashNode*)malloc(sizeof(HashNode));
		node->info = proiect;
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

int fHash(const char* key, int size)
{
	return key[0] % size;
}

void inserareHashTable(HashTable* hashTable, Proiect* proiect)
{
	HashNode* node = creareHashNode(proiect);

	if (hashTable->size == 0)
		initHashTable(hashTable, HT_SIZE);

	if (node)
	{
		int index = fHash(node->info->beneficiar, hashTable->size);
		node->next = hashTable->items[index];
		hashTable->items[index] = node;
	}
}

// 2.
void afisareHashTable(HashTable hashTable)
{
	for (int i = 0; i < hashTable.size; i++)
	{
		printf("\n-------------- Bucket %d --------------\n", i);
		HashNode* current = hashTable.items[i];
		while (current)
		{
			printf("%d: %s\n", current->info->cod, current->info->beneficiar);
			current = current->next;
		}
	}
}

// 3.
float calcBuget(HashTable hashTable, const char* beneficiar)
{
	float buget = 0;

	if (beneficiar)
	{
		if (hashTable.items && hashTable.size > 0)
		{
			int index = fHash(beneficiar, hashTable.size);
			HashNode* current = hashTable.items[index];
			while (current)
			{
				if (strcmp(beneficiar, current->info->beneficiar) == 0)
				{
					buget += current->info->buget;
				}
				current = current->next;
			}
		}
	}
	return buget;
}

// 4.
void modifBeneficiar(HashTable hashTable, const char* benefVechi, const char* benefNou)
{
	if (benefVechi && benefNou)
	{
		if (hashTable.items && hashTable.size > 0)
		{
			int index = fHash(benefVechi, hashTable.size);
			HashNode* current = hashTable.items[index];
			while (current)
			{
				if (strcmp(current->info->beneficiar, benefVechi) == 0)
				{
					free(current->info->beneficiar);
					current->info->beneficiar = (char*)malloc(strlen(benefNou) + 1);
					strcpy(current->info->beneficiar, benefNou);
				}
				current = current->next;
			}
		}
	}
}

// 5.
typedef struct NodLS
{
	Proiect* info;
	struct NodLS* next;
} Nod;

Nod* creareNod(Proiect* proiect)
{
	Nod* nod = NULL;
	if (proiect)
	{
		nod = (Nod*)malloc(sizeof(Nod));
		nod->info = proiect;
		nod->next = NULL;
	}
	return nod;
}

void salvareListaSimpla(HashTable hashTable, Nod** lista, float buget)
{
	if (hashTable.items && hashTable.size > 0)
	{
		for (int i = 0; i < hashTable.size; i++)
		{
			HashNode* current = hashTable.items[i];
			while (current)
			{
				if (current->info->buget > buget)
				{
					Proiect* proiect = creareProiect(current->info->cod, current->info->titlu, current->info->beneficiar,
						current->info->nrExec, current->info->buget);
					Nod* nod = creareNod(proiect);

					if (*lista != NULL)
					{
						nod->next = (*lista);
					}
					(*lista) = nod;
				}
				current = current->next;
			}
		}
	}
}

void afisareListaSimpla(Nod* lista)
{
	while (lista)
	{
		afisareProiect(lista->info);
		lista = lista->next;
	}
}

// HASHTABLE IMPLEMENTATION -- LINEAR PROBING
typedef struct HashTLP
{
	Proiect** items;
	int size;
} HashTableLP;

int linearProbing(HashTableLP hashTable, const char* key, int index);

void initHashTableLP(HashTableLP* hashTable, int size)
{
	hashTable->size = size;
	hashTable->items = (Proiect**)malloc(sizeof(Proiect*) * size);
	memset(hashTable->items, 0, sizeof(Proiect*) * size);
}

void inserareHashTableLP(HashTableLP* hashTable, Proiect* proiect)
{
	if (hashTable->size == 0)
		initHashTableLP(hashTable, HT_SIZE);

	int index = fHash(proiect->beneficiar, hashTable->size);

	if (hashTable->items[index] != NULL)
	{
		index = linearProbing(*hashTable, proiect->beneficiar, index);
	}

	hashTable->items[index] = proiect;
}

// resize hash table and copy existing items
void resizeHashTable(HashTableLP* hashTable)
{
	Proiect** aux = hashTable->items;
	initHashTableLP(hashTable, hashTable->size * 3);

	for (int i = 0; i < hashTable->size / 3; i++)
	{
		Proiect* proiect = aux[i];
		if (proiect)
		{
			inserareHashTableLP(hashTable, proiect);
		}
	}
}

// returns the index where a free slot is available
int linearProbing(HashTableLP hashTable, const char* key, int index)
{
	while (hashTable.items[index] != NULL)
	{
		index++;
		if (hashTable.size == index)
		{
			resizeHashTable(&hashTable);
			index = fHash(key, hashTable.size);
		}
	}
	return index;
}

// 2.
void afisareHashTableLP(HashTableLP hashTable)
{
	if (hashTable.items && hashTable.size > 0)
	{
		for (int i = 0; i < hashTable.size; i++)
		{
			printf("\n---------------- Bucket %d --------------\n", i);
			afisareProiect(hashTable.items[i]);
		}
	}
} 

void main()
{
	HashTable hashTable = { .items = NULL, .size = 0 };
	HashTableLP hashTable1 = { .items = NULL, .size = 0 };

	FILE* pFile = fopen("DataProiect.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",";
		char* token = NULL;
		char buffer[LINE_SIZE], titlu[LINE_SIZE], beneficiar[LINE_SIZE];
		unsigned int cod;
		unsigned char nrExec;
		float buget;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			cod = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(titlu, token);
			token = strtok(NULL, delimiter);
			strcpy(beneficiar, token);
			token = strtok(NULL, delimiter);
			nrExec = atoi(token);
			token = strtok(NULL, delimiter);
			buget = atof(token);

			Proiect* proiect = creareProiect(cod, titlu, beneficiar, nrExec, buget);
			//afisareProiect(proiect);
			inserareHashTable(&hashTable, proiect);
			inserareHashTableLP(&hashTable1, proiect);
		}
		fclose(pFile);

		// 2.
		afisareHashTable(hashTable);

		// 3.
		float bugetTotal = calcBuget(hashTable, "Ionescu Mihai");
		printf("\nBuget: %.2f\n", bugetTotal);

		// 4.
		modifBeneficiar(hashTable, "Ionescu Mihai", "Ionescu Mihai-Constantin");
		afisareHashTable(hashTable);

		// 5.
		Nod* lista = NULL;
		salvareListaSimpla(hashTable, &lista, 150);
		printf("\n----------- Afisare Lista Simpla -------------\n");
		afisareListaSimpla(lista);

		printf("\n\n------------------------ LINEAR PROBING ------------------------\n");
		// 2.
		afisareHashTableLP(hashTable1);
	}
}