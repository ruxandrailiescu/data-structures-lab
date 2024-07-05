#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// 1.
typedef struct Prog
{
	char* data;
	char* numeClient;
	float durata;
	char* servicii;
	int cost;
	struct Prog* next;
} Programare;

typedef struct ListaProg
{
	char* dataProg;
	Programare* nod;
	struct ListaProgramari* next;
} ListaProgramari;

Programare* creareProg(const char* data, const char* numeClient, float durata, const char* servicii, int cost)
{
	Programare* programare = NULL;

	if (data && numeClient && servicii)
	{
		programare = (Programare*)malloc(sizeof(Programare));
		programare->data = (char*)malloc(strlen(data) + 1);
		strcpy(programare->data, data);
		programare->numeClient = (char*)malloc(strlen(numeClient) + 1);
		strcpy(programare->numeClient, numeClient);
		programare->durata = durata;
		programare->servicii = (char*)malloc(strlen(servicii) + 1);
		strcpy(programare->servicii, servicii);
		programare->cost = cost;

		programare->next = NULL;
	}

	return programare;
}

void afisareProg(Programare* programare)
{
	if (programare)
	{
		printf("Data: %s, Nume client: %s, Durata: %.2f, Servicii: [%s], Cost: %d\n",
			programare->data, programare->numeClient, programare->durata, programare->servicii, programare->cost);
	}
}

ListaProgramari* creareListaProg(const char* dataProg)
{
	ListaProgramari* lista = NULL;

	if (dataProg)
	{
		lista = (ListaProgramari*)malloc(sizeof(ListaProgramari));
		lista->dataProg = (char*)malloc(strlen(dataProg) + 1);
		strcpy(lista->dataProg, dataProg);

		lista->nod = NULL;
		lista->next = NULL;
	}

	return lista;
}

void inserareProg(ListaProgramari* listaProg, Programare* programare)
{
	if (listaProg)
	{
		if (strcmp(listaProg->dataProg, programare->data) == 0)
		{
			if (listaProg->nod != NULL)
			{
				programare->next = listaProg->nod;
			}
			listaProg->nod = programare;
		}
	}
}

void creareLista(ListaProgramari** lista, Programare* programare)
{
	if (*lista == NULL)
	{
		*lista = creareListaProg(programare->data);
		inserareProg(*lista, programare);
	}
	else
	{
		ListaProgramari* tmp = *lista;
		ListaProgramari* prev = NULL;

		while (tmp && strcmp(tmp->dataProg, programare->data) != 0)
		{
			prev = tmp;
			tmp = tmp->next;
		}

		if (tmp)
		{
			inserareProg(tmp, programare);
		}
		else
		{
			prev->next = creareListaProg(programare->data);
			inserareProg(prev->next, programare);
		}
	}
}

void afisareLista1(ListaProgramari* lista)
{
	while (lista)
	{
		printf("\nData: %s\n", lista->dataProg);
		Programare* tmpProg = lista->nod;
		while (tmpProg)
		{
			printf("\t");
			afisareProg(tmpProg);
			tmpProg = tmpProg->next;
		}
		lista = lista->next;
	}
}

// 2.
void calcValoareTot(ListaProgramari* lista, const char* dataProg, int* valoareTot)
{
	while (lista)
	{
		if (strcmp(lista->dataProg, dataProg) == 0)
		{
			Programare* tmpProg = lista->nod;
			while (tmpProg)
			{
				(*valoareTot) += tmpProg->cost;
				tmpProg = tmpProg->next;
			}
		}
		lista = lista->next;
	}
}

// 3.
void modifCostProg(ListaProgramari* lista, const char* numeClient, int costNou)
{
	while (lista)
	{
		Programare* tmpProg = lista->nod;
		while (tmpProg)
		{
			if (strcmp(tmpProg->numeClient, numeClient) == 0)
			{
				tmpProg->cost = costNou;
			}
			tmpProg = tmpProg->next;
		}
		lista = lista->next;
	}
}

// 4.
void stergereProg(ListaProgramari* lista, float durata)
{
	while (lista)
	{
		Programare* tmpProg = lista->nod;

		while (tmpProg && tmpProg->durata < durata)
		{
			Programare* deSters = tmpProg;
			tmpProg = tmpProg->next;
			free(deSters->data);
			free(deSters->numeClient);
			free(deSters->servicii);
			free(deSters);
		}
		lista->nod = tmpProg;

		lista = lista->next;
	}
}

// 5.
typedef struct StackN
{
	Programare* programare;
	struct StackN* next;
} StackNode;

StackNode* creareStackNode(Programare* programare)
{
	StackNode* node = NULL;

	if (programare)
	{
		node = (StackNode*)malloc(sizeof(StackNode));
		node->programare = programare;
		node->next = NULL;
	}

	return node;
}

void pushStackNode(StackNode** stack, Programare* programare)
{
	StackNode* node = creareStackNode(programare);
	if (*stack)
	{
		node->next = *stack;
	}
	*stack = node;
}

void afisareStack(StackNode* stack)
{
	while (stack)
	{
		afisareProg(stack->programare);
		stack = stack->next;
	}
}

void salvareStiva(StackNode** stack, ListaProgramari* lista, const char* servicii)
{
	while (lista)
	{
		Programare* tmpProg = lista->nod;
		while (tmpProg)
		{
			if (strcmp(tmpProg->servicii, servicii) == 0)
			{
				Programare* copy = creareProg(tmpProg->data, tmpProg->numeClient, tmpProg->durata,
					tmpProg->servicii, tmpProg->cost);
				pushStackNode(stack, copy);
			}
			tmpProg = tmpProg->next;
		}
		lista = lista->next;
	}
}

void main()
{
	ListaProgramari* lista = NULL;

	FILE* pFile = fopen("DataProgramare.txt", "r");
	if (pFile)
	{
		char delimiter[] = ";";
		char* token = NULL;
		char buffer[LINE_SIZE], data[LINE_SIZE], nume[LINE_SIZE], servicii[LINE_SIZE];
		float durata;
		int cost;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			strcpy(data, token);
			token = strtok(NULL, delimiter);
			strcpy(nume, token);
			token = strtok(NULL, delimiter);
			durata = atof(token);
			token = strtok(NULL, delimiter);
			strcpy(servicii, token);
			token = strtok(NULL, delimiter);
			cost = atoi(token);

			Programare* programare = creareProg(data, nume, durata, servicii, cost);
			//afisareProg(programare);
			creareLista(&lista, programare);
		}
		fclose(pFile);

		afisareLista1(lista);

		// 2.
		int valoareTot = 0;
		calcValoareTot(lista, "2024/03/23", &valoareTot);
		printf("\n\nValoare totala: %d\n", valoareTot);

		// 3.
		modifCostProg(lista, "Ruxandra Iliescu", 999);
		afisareLista1(lista);

		// 4.
		//stergereProg(lista, 2);
		printf("\n\n-----------------------------------------------\n");
		//afisareLista1(lista);

		// 5.
		StackNode* stack = NULL;
		salvareStiva(&stack, lista, "Detartraj,Plomba");
		afisareStack(stack);

		// Free allocated memory
		while (lista) {
			ListaProgramari* tmpLista = lista;
			lista = lista->next;
			while (tmpLista->nod) {
				Programare* tmpProg = tmpLista->nod;
				tmpLista->nod = tmpLista->nod->next;
				free(tmpProg->data);
				free(tmpProg->numeClient);
				free(tmpProg->servicii);
				free(tmpProg);
			}
			free(tmpLista->dataProg);
			free(tmpLista);
		}

		// Free stack memory
		while (stack) {
			StackNode* tmpStack = stack;
			stack = stack->next;
			free(tmpStack);
		}
	}
}