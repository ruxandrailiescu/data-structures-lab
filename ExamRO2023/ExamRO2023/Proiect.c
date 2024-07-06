#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#define PQ_SIZE 7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// 1.
typedef struct Proiect
{
	unsigned int cod;
	char* titlu;
	char* benef;
	unsigned char nrExec;
	float buget;
} Proiect;

Proiect* creareProiect(unsigned int cod, const char* titlu, const char* benef, unsigned char nrExec, float buget)
{
	Proiect* proiect = NULL;

	if (titlu && benef)
	{
		proiect = (Proiect*)malloc(sizeof(Proiect));
		proiect->cod = cod;
		proiect->titlu = (char*)malloc(strlen(titlu) + 1);
		strcpy(proiect->titlu, titlu);
		proiect->benef = (char*)malloc(strlen(benef) + 1);
		strcpy(proiect->benef, benef);
		proiect->nrExec = nrExec;
		proiect->buget = buget;
	}

	return proiect;
}

void afisareProiect(Proiect* proiect)
{
	if (proiect)
	{
		printf("Cod: %d, Titlu: %s, Benef: %s, Nr exec: %d, Buget: %.2f\n",
			proiect->cod, proiect->titlu, proiect->benef, proiect->nrExec, proiect->buget);
	}
}

typedef struct Node
{
	struct Node* prev;
	Proiect* info;
	struct Node* next;
} ListNode;

ListNode* creareNod1(Proiect* proiect)
{
	ListNode* nod = NULL;

	if (proiect)
	{
		nod = (ListNode*)malloc(sizeof(ListNode));
		nod->info = proiect;
		nod->prev = nod->next = NULL;
	}

	return nod;
}

// inserare sortata crescator (cheie: cod proiect)
void inserareNod(ListNode** lista, Proiect* proiect)
{
	ListNode* nod = creareNod1(proiect);

	if (nod)
	{
		if (*lista == NULL)
			(*lista) = nod;
		else
		{
			ListNode* tmp = *lista;
			ListNode* prev = NULL;

			while (tmp && (tmp->info->cod <= nod->info->cod))
			{
				prev = tmp;
				tmp = tmp->next;
			}

			if (prev == NULL)
			{
				nod->next = (*lista);
				(*lista)->prev = nod;
				(*lista) = nod;
			}
			else
			{
				prev->next = nod;
				nod->prev = prev;
			}

			if (tmp)
			{
				tmp->prev = nod;
				nod->next = tmp;
			}
		}
	}
}

void afisareLista(ListNode* lista)
{
	while (lista->next)
	{
		afisareProiect(lista->info);
		lista = lista->next;
	}
	afisareProiect(lista->info);

	printf("\n--------------- TRAVERSARE SENS OPUS ------------------\n");

	while (lista->prev)
	{
		afisareProiect(lista->info);
		lista = lista->prev;
	}
	afisareProiect(lista->info);
}

// 2.
void calcNrProiecte(ListNode* lista, unsigned char nrExec, int* nrProiecte)
{
	while (lista)
	{
		if (lista->info->nrExec > nrExec)
			(*nrProiecte)++;
		lista = lista->next;
	}
}

// 3.
void actualizareProiecte(ListNode* lista, const char* benef, float procent)
{
	while (lista)
	{
		if (strcmp(lista->info->benef, benef) == 0)
			lista->info->buget *= (1 + procent / 100);
		lista = lista->next;
	}
}

// 4.
void sortareListaBuget(ListNode** lista)
{
	if (*lista == NULL || (*lista)->next == NULL)
		return;

	int swapped;
	ListNode* current;
	ListNode* last = NULL;

	do
	{
		swapped = 0;
		current = *lista;

		while (current->next != last)
		{
			if (current->info->buget > current->next->info->buget)
			{
				Proiect* aux = current->info;
				current->info = current->next->info;
				current->next->info = aux;

				swapped = 1;
			}
			current = current->next;
		}
		last = current;

	} while (swapped);
}

// 5.
// MAX PQueue
typedef struct PQueue
{
	Proiect** items;
	int currentIndex;
	int size;
} PQueue;

void reheapUp(PQueue* pQueue, int currentIndex)
{
	if (currentIndex > 0)
	{
		int parentIndex = (currentIndex - 1) / 2;

		if (pQueue->items[parentIndex]->cod < pQueue->items[currentIndex]->cod)
		{
			Proiect* aux = pQueue->items[parentIndex];
			pQueue->items[parentIndex] = pQueue->items[currentIndex];
			pQueue->items[currentIndex] = aux;

			reheapUp(pQueue, parentIndex);
		}
	}
}

void inserareHeap(PQueue* pQueue, Proiect* proiect)
{
	if (pQueue->currentIndex >= pQueue->size)
	{
		pQueue->size *= 2;
		pQueue->items = (Proiect**)realloc(pQueue->items, sizeof(Proiect*) * pQueue->size);
	}

	pQueue->items[pQueue->currentIndex] = proiect;
	reheapUp(pQueue, pQueue->currentIndex);
	pQueue->currentIndex++;
}

void enqueueHeapBenef(PQueue* pQueue, ListNode* lista, const char* benef)
{
	while (lista)
	{
		if (strcmp(lista->info->benef, benef) == 0)
		{
			Proiect* copy = creareProiect(lista->info->cod, lista->info->titlu, lista->info->benef,
				lista->info->nrExec, lista->info->buget);
			inserareHeap(pQueue, copy);
		}
		lista = lista->next;
	}
}

void main()
{
	ListNode* lista = NULL;
	FILE* pFile = fopen("DataProiect.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",\n";
		char* token = NULL;
		char buffer[LINE_SIZE], titlu[LINE_SIZE], benef[LINE_SIZE];
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
			strcpy(benef, token);
			token = strtok(NULL, delimiter);
			nrExec = atoi(token);
			token = strtok(NULL, delimiter);
			buget = atof(token);

			Proiect* proiect = creareProiect(cod, titlu, benef, nrExec, buget);
			//afisareProiect(proiect);
			inserareNod(&lista, proiect);
		}
		afisareLista(lista);

		// 2.
		printf("\n2.--------------------------\n");
		int nrProiecte = 0;
		calcNrProiecte(lista, 4, &nrProiecte);
		printf("Nr proiecte: %d\n", nrProiecte);

		// 3.
		printf("\n3.--------------------------\n");
		actualizareProiecte(lista, "Ionescu Mihai", 10);
		afisareLista(lista);

		// 4.
		printf("\n4.-----------------------------\n");
		sortareListaBuget(&lista);
		afisareLista(lista);

		// 5.
		printf("\n5.-----------------------------\n");
		PQueue pQueue = { .items = NULL, .currentIndex = 0, .size = PQ_SIZE };
		pQueue.items = (Proiect**)malloc(sizeof(Proiect*) * pQueue.size);
		enqueueHeapBenef(&pQueue, lista, "Ionescu Mihai");
		for (int i = 0; i < pQueue.currentIndex; i++)
			afisareProiect(pQueue.items[i]);
	}
}