#define _CRT_SECURE_NO_WARNINGS
#define LINE_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. crearea structurii Reteta si a listei duble
//    operatii: creareReteta, afisareReteta, stergereReteta
//				creareNod, inserareNodPozitie, inserareNodSortat, stergereNod
//				afisareLista

typedef struct Reteta
{
	unsigned int nrReteta;
	char* numePacient;
	char* numeMedic;
	char* statutSpecial;
	unsigned char nrMedicamente;
	float procentCompensare;
} Reteta;

Reteta* creareReteta(unsigned int _nrReteta, const char* _numePacient, const char* _numeMedic,
	const char* _statutSpecial, unsigned char _nrMedicamente, float _procentCompensare)
{
	// 1. validare (optional)
	if (_numePacient == NULL || _numeMedic == NULL || _statutSpecial == NULL)
	{
		return NULL;
	}

	// 2. alocare memorie structura
	Reteta* reteta = (Reteta*)malloc(sizeof(Reteta));

	// 3. initializare atribute
	reteta->nrReteta = _nrReteta;
	
	reteta->numePacient = (char*)malloc(strlen(_numePacient) + 1);
	strcpy(reteta->numePacient, _numePacient);

	reteta->numeMedic = (char*)malloc(strlen(_numeMedic) + 1);
	strcpy(reteta->numeMedic, _numeMedic);

	reteta->statutSpecial = (char*)malloc(strlen(_statutSpecial) + 1);
	strcpy(reteta->statutSpecial, _statutSpecial);

	reteta->nrMedicamente = _nrMedicamente;
	reteta->procentCompensare = _procentCompensare;

	// 4. return structura
	return reteta;
}

void afisareReteta(Reteta* reteta)
{
	if (reteta)
	{
		printf("\nNr reteta: %d, Nume pacient: %s, Nume medic: %s, Statut special: %s, Nr medicamente: %d, Procent compensare: %.2f\n",
			reteta->nrReteta, reteta->numePacient, reteta->numeMedic, reteta->statutSpecial, reteta->nrMedicamente, reteta->procentCompensare);
	}
}

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

typedef struct NodLD
{
	struct NodLD* prev;
	Reteta* reteta;
	struct NodLD* next;
} Nod;

Nod* creareNod(Reteta* reteta)
{
	// validare (optional)
	Nod* nod = NULL;
	if (reteta)
	{
		// 1. alocare memorie structura
		nod = (Nod*)malloc(sizeof(Nod));

		// 2. initializare atribute
		nod->reteta = reteta;
		nod->next = nod->prev = NULL;
	}
	// 3. return structura
	return nod;
}

void inserareNodPozitie(Nod** lista, Reteta* reteta, int poz)
{
	Nod* nod = creareNod(reteta);

	// daca lista este goala
	if ((*lista) == NULL)
	{
		(*lista) = nod;
	}
	else
	{
		// verificam daca pozitia este admisibila
		Nod* tmp = (*lista);
		int counter = 0;
		while (tmp)
		{
			counter++;
			tmp = tmp->next;
		}

		// poz = 0 => inseram la head
		if (poz == 0)
		{
			nod->next = (*lista);
			(*lista)->prev = nod;
			(*lista) = nod;
			return;
		}

		// resetam tmp la inceputul listei
		tmp = (*lista);

		// poz >= counter => inseram la tail
		if (poz >= counter)
		{
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			tmp->next = nod;
			nod->prev = tmp;
			return;
		}

		counter = 0;
		while (counter < poz)
		{
			counter++;
			tmp = tmp->next;
		}
		Nod* nxt = tmp;
		tmp->prev->next = nod;
		nod->prev = tmp->prev;
		nxt->prev = nod;
		nod->next = nxt;
	}
}

// (*) aditional: inserare sortata (crescator) pe baza procentului de compensare
void inserareNodSortat(Nod** lista, Reteta* reteta)
{
	Nod* nod = creareNod(reteta);

	// daca lista este goala
	if ((*lista) == NULL)
	{
		(*lista) = nod;
	}
	else
	{
		Nod* tmp = (*lista);
		Nod* prv = NULL;
		
		// gasim pozitia corecta pt inserare
		while (tmp && tmp->reteta->procentCompensare <= nod->reteta->procentCompensare)
		{
			prv = tmp;
			tmp = tmp->next;
		}

		// suntem la inceputul listei
		if (prv == NULL)
		{
			nod->next = (*lista);
			(*lista)->prev = nod;
			(*lista) = nod;
		} 
		// suntem la sfarsitul listei
		else if (tmp == NULL)
		{
			prv->next = nod;
			nod->prev = prv;
		}
		else
		{
			prv->next = nod;
			nod->prev = prv;
			nod->next = tmp;
			tmp->prev = nod;
		}
	}
}

void stergereNod(Nod* nod)
{
	if (nod)
	{
		stergereReteta(nod->reteta);
		free(nod);
	}
}

void afisareLista(Nod* lista)
{
	while (lista->next)
	{
		afisareReteta(lista->reteta);
		lista = lista->next;
	}
	afisareReteta(lista->reteta);

	printf("------------------ TRAVERSARE SENS OPUS ------------------");
	
	while (lista->prev)
	{
		afisareReteta(lista->reteta);
		lista = lista->prev;
	}
	afisareReteta(lista->reteta);
}

// 2.
// modificam nr retete in interiorul functiei
// alta optiune
//int calcNrRetete(Nod* lista, unsigned char nrMed)
void calcNrRetete(Nod* lista, int* nrRetete, unsigned char nrMed)
{
	while (lista)
	{
		if (lista->reteta->nrMedicamente > nrMed)
		{
			(*nrRetete)++;
		}
		lista = lista->next;
	}
}

// 3.
void actualizareProcentComp(Nod** lista, const char* numePacient, float procentNou)
{
	Nod* tmp = (*lista);
	while (tmp)
	{
		if (strcmp(tmp->reteta->numePacient, numePacient) == 0)
		{
			tmp->reteta->procentCompensare = procentNou;
		}
		tmp = tmp->next;
	}
}

// 4.
void stergereNodCriteriu(Nod** lista, unsigned char nrMed)
{
	Nod* tmp = *lista;
	
	while (tmp)
	{
		Nod* deSters = tmp;
		tmp = tmp->next;		// actualizam tmp inainte de a sterge nodul pt a asigura ca accesam memorie valida

		if (deSters->reteta->nrMedicamente < nrMed)
		{
			if (deSters->prev)
			{
				deSters->prev->next = deSters->next;
			}
			else
			{
				// stergem nodul de la inceputul listei
				(*lista) = deSters->next;
			}

			if (deSters->next)
			{
				deSters->next->prev = deSters->prev;
			}
			stergereNod(deSters);
		}
	}
}

// 5.


void main()
{
	Nod* lista = NULL;
	FILE* pFile = fopen("DataReteta.txt", "r");

	if (pFile)
	{
		char delimiters[] = ",\n";
		char* token = NULL;
		char buffer[LINE_SIZE], numePacient[LINE_SIZE], numeMedic[LINE_SIZE], statutSpecial[LINE_SIZE];
		unsigned int nrReteta;
		unsigned char nrMedicamente;
		float procentCompensare;

		while (fgets(buffer, sizeof(buffer), pFile))
		{
			token = strtok(buffer, delimiters);
			nrReteta = atoi(token);
			token = strtok(NULL, delimiters);
			strcpy(numePacient, token);
			token = strtok(NULL, delimiters);
			strcpy(numeMedic, token);
			token = strtok(NULL, delimiters);
			strcpy(statutSpecial, token);
			token = strtok(NULL, delimiters);
			nrMedicamente = atoi(token);
			token = strtok(NULL, delimiters);
			procentCompensare = atof(token);

			// 1.
			Reteta* reteta = creareReteta(nrReteta, numePacient, numeMedic, statutSpecial, nrMedicamente, procentCompensare);
			//afisareReteta(reteta);
			inserareNodPozitie(&lista, reteta, nrReteta - 1);
			//inserareNodSortat(&lista, reteta);
		}
	}
	afisareLista(lista);

	// 2.
	int nrRetete = 0;
	calcNrRetete(lista, &nrRetete, 1);
	printf("\nNr retete: %d\n", nrRetete);

	// 3.
	actualizareProcentComp(&lista, "Ana Boncu", 45.5);
	//afisareLista(lista);

	// 4.
	//stergereNodCriteriu(&lista, 5);
	//afisareLista(lista);

	// 5.
}