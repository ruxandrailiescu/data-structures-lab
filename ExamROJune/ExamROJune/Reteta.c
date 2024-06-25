#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1.
typedef struct Reteta
{
	unsigned int nrReteta;
	char* numePacient;
	char* numeMedic;
	char* statutSpecial;
	unsigned char nrMedicamente;
	float procentCompensare;
	//int* aaa;
	//int nrAaa;
} Reteta;

typedef struct NodDLL
{
	struct NodDLL* prev;
	Reteta* info;
	struct NodDLL* next;
} Nod;

Reteta* creareReteta(unsigned int _nrReteta, const char* _numePacient, const char* _numeMedic, const char* _statutSpecial, unsigned char _nrMedicamente, float _procentCompensare/*, int* _aaa, int _nrAaa*/)
{
	// 1. alocam memorie pt o reteta
	Reteta* reteta = (Reteta*)malloc(sizeof(Reteta));
	
	// 2. initializam atributele
	reteta->nrReteta = _nrReteta;
	reteta->numePacient = (char*)malloc(strlen(_numePacient) + 1);
	strcpy(reteta->numePacient, _numePacient);
	reteta->numeMedic = (char*)malloc(strlen(_numeMedic) + 1);
	strcpy(reteta->numeMedic, _numeMedic);
	reteta->statutSpecial = (char*)malloc(strlen(_statutSpecial) + 1);
	strcpy(reteta->statutSpecial, _statutSpecial);
	reteta->nrMedicamente = _nrMedicamente;
	reteta->procentCompensare = _procentCompensare;

	//reteta->aaa = (int*)malloc(sizeof(int)*_nrAaa);
	//for (int i = 0; i < _nrAaa; i++) {
	//	reteta->aaa[i] = _aaa[i];
	//}

	// 3. returnam reteta
	return reteta;
}

void displayReteta(Reteta* reteta)
{
	if (reteta)
	{
		printf("Nr reteta: %d, Nume pacient: %s, Nume medic: %s, Statut special: %s, Nr medicamente: %d, Procent compensare: %.2f\n",
			reteta->nrReteta, reteta->numePacient, reteta->numeMedic, reteta->statutSpecial, reteta->nrMedicamente, reteta->procentCompensare);
	}
}

Nod* creareNod(Reteta* reteta)
{
	// 1. alocam memorie pt nod
	Nod* nod = (Nod*)malloc(sizeof(Nod));

	// 2. initializam atributele
	nod->info = reteta;
	nod->prev = nod->next = NULL;

	// 3. returnam nodul
	return nod;
}

void inserareListaCheie(Nod** lista, Reteta* reteta, unsigned int cheie)
{
	// cheie = nr reteta

	Nod* nod = creareNod(reteta);

	Nod* tmp = (*lista);

	if (tmp == NULL)
	{
		(*lista) = nod;
		return;
	}

	while (tmp)
	{
		if (tmp->info->nrReteta == cheie)
		{
			if (tmp->next != NULL)
			{
				Nod* nodNext = tmp->next;
				tmp->next = nod;
				nod->prev = tmp;
				nod->next = nodNext;
				nodNext->prev = nod;
			}
			else 
			{
				tmp->next = nod;
				nod->prev = tmp;
			}
			return;
		}
		tmp = tmp->next;
	}
}

// traversarea listei in ambele sensuri
void displayLista(Nod* lista)
{
	while (lista->next)
	{
		displayReteta(lista->info);
		lista = lista->next;
	}
	displayReteta(lista->info);

	printf("---------- REVERSED ORDER -----------\n");
	while (lista->prev)
	{
		displayReteta(lista->info);
		lista = lista->prev;
	}
	displayReteta(lista->info);
}

// 2.
unsigned char calcNrRetete(Nod* lista, unsigned char nrMed)
{
	unsigned char nrRetete = 0;
	while (lista)
	{
		if (lista->info->nrMedicamente > nrMed)
		{
			nrRetete++;
		}
		lista = lista->next;
	}
	return nrRetete;
}

// 3.
void actualizareProcentCompensare(Nod** lista, const char* numePacient, float procentCompensareNou)
{
	Nod* tmp = *lista;
	while (tmp)
	{
		if (strcmp(tmp->info->numePacient, numePacient) == 0)
		{
			tmp->info->procentCompensare = procentCompensareNou;
			break;
		}
		tmp = tmp->next;
	}
	displayLista(*lista);
}

// 4.
void stergereReteta(Reteta* reteta)
{
	if (reteta)
	{
		free(reteta->numePacient);
		free(reteta->numeMedic);
		free(reteta->statutSpecial);
		free(reteta);
	}
}

void stergereNodCheie(Nod** lista, unsigned char nrMed)
{
	Nod* tmp = (*lista);
	while (tmp)
	{
		if (tmp->info->nrMedicamente < nrMed)
		{
			if (tmp->prev != NULL)
			{
				// actualizam pointerul next al nodului precedent
				// daca nodul care trebuie sters nu este la inceputul listei
				tmp->prev->next = tmp->next;
			}
			else
			{
				(*lista) = tmp->next;
			}

			if (tmp->next != NULL)
			{
				// actualizam pointerul prev al nodului urmator
				// daca nodul care trebuie sters nu este la sfarsitul listei
				tmp->next->prev = tmp->prev;
			}
			stergereReteta(tmp->info);
			free(tmp);
		}
		tmp = tmp->next;
	}
}

void main()
{
	Nod* lista = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	if (pFile)
	{
		char delimiter[] = ",\n";
		char* token = NULL;
		char buffer[LINE_SIZE], numePacient[LINE_SIZE], numeMedic[LINE_SIZE], statutSpecial[LINE_SIZE];
		unsigned int nrReteta;
		unsigned char nrMedicamente;
		float procentCompensare;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiter);
			nrReteta = atoi(token);
			token = strtok(NULL, delimiter);
			strcpy(numePacient, token);
			token = strtok(NULL, delimiter);
			strcpy(numeMedic, token);
			token = strtok(NULL, delimiter);
			strcpy(statutSpecial, token);
			token = strtok(NULL, delimiter);
			nrMedicamente = (char)atoi(token);
			token = strtok(NULL, delimiter);
			procentCompensare = atof(token);

			Reteta* reteta = creareReteta(nrReteta, numePacient, numeMedic, statutSpecial, nrMedicamente, procentCompensare);
			//displayReteta(reteta);
			inserareListaCheie(&lista, reteta, 1);
		}
	}
	//displayLista(lista);

	// 2.
	int nrRetete = calcNrRetete(lista, 3);
	printf("\nNr de retete care au mai mult de 3 medicamente: %d\n", nrRetete);

	// 3.
	actualizareProcentCompensare(&lista, "Ana Boncu", 222.2);
	printf("\n----------- DISPLAY LISTA MAIN ---------\n");
	displayLista(lista);

	// 4.
	stergereNodCheie(&lista, 5);
	printf("\n----------- DISPLAY LISTA DUPA STERGERE ---------\n");
	displayLista(lista);
}