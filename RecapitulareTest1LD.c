#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

struct Farmacie {
	char* denumire;
	float suprafata;
	unsigned int nrAngajati;
};

typedef struct Farmacie Farmacie;
typedef struct Nod Nod;

struct Nod {
	Nod* prev;
	Nod* next;
	Farmacie info;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};

void afisareFarmacie(Farmacie farmacie) {
	printf("\nDenumirea farmaciei: %s\n", farmacie.denumire);
	printf("Suprafata: %.2f\n", farmacie.suprafata);
	printf("Numarul de angajati: %d\n", farmacie.nrAngajati);
}

void afisareLista(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareFarmacie(p->info);
		p = p->next;
	}
}

Farmacie citireFarmacieDinFisier(FILE* f) {

	Farmacie farmacie;
	char buffer[100];
	char sep[3] = ",\n";
	char* token;
	fgets(buffer, 100, f);
	token = strtok(buffer, sep);
	farmacie.denumire = (char*)malloc(strlen(token) + 1);
	strcpy_s(farmacie.denumire, strlen(token) + 1, token);
	token = strtok(NULL, sep);
	farmacie.suprafata = atof(token);
	token = strtok(NULL, sep);
	farmacie.nrAngajati = atoi(token);

	return farmacie;
}

void adaugaLaFinal(ListaDubla* lista, Farmacie farmacieNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = farmacieNoua;
	nou->next = NULL;
	nou->prev = lista->last;

	if (lista->last) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->last = nou;
	lista->nrNoduri++;
}

void adaugaLaInceput(ListaDubla* lista, Farmacie farmacieNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = farmacieNoua;
	nou->next = lista->first;
	nou->prev = NULL;
	if (lista->first) {
		lista->first->prev = nou;
	}
	else
	{
		lista->last = nou;
	}
	lista->first = nou;
	lista->nrNoduri++;
}

ListaDubla citireListaDinFisier(const char* numeFisier) {
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Farmacie farma = citireFarmacieDinFisier(f);
		adaugaLaFinal(&lista, farma);
	}
	fclose(f);
	return lista;
}

void dezalocare(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* temp = p;
		p = p->next;
		free(temp->info.denumire);
		free(temp);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

void stergeDupaDenumire(ListaDubla* lista, char* denum) {
	if (lista->first == NULL) return;
	Nod* p = lista->first;
	while (p != NULL && strcmp(p->info.denumire, denum) != 0) {
		p = p->next;
	}
	if (p == NULL)return;
	if (p->prev == NULL) {
		lista->first = p->next;
		if (lista->first)
			lista->first->prev = NULL;
	}
	else {
		p->prev->next = p->next;
	}
	if (p->next) {
		p->next->prev = p->prev;
	}
	else {
		lista->last = p->prev;

	}
	free(p->info.denumire);
	free(p);
	lista->nrNoduri--;
}

Farmacie* vector(ListaDubla lista, int* dimensiune, char* denum) {
	int k = 0;
	Nod* p = lista.first;

	while (p)
	{
		if (strcmp(p->info.denumire, denum) == 0)
			k++;
		p = p->next;
	}
	p = lista.first;
	int contor = 0;
	Farmacie* vector = (Farmacie*)(malloc(sizeof(Farmacie) * k));
	while (p) {
		if (strcmp(p->info.denumire, denum) == 0)
		{
			vector[contor].denumire = (char*)malloc(sizeof(char) * strlen(p->info.denumire) + 1);
			strcpy_s(vector[contor].denumire, strlen(p->info.denumire) + 1, p->info.denumire);
			vector[contor].nrAngajati = p->info.nrAngajati;
			vector[contor].suprafata = p->info.suprafata;
			contor++;
		}
		p = p->next;
	}
	*dimensiune = k;
	return vector;
}

int main() {

	ListaDubla lista = citireListaDinFisier("farmacii.txt");
	afisareLista(lista);
	printf("-----------------STERGERE---------------------");
	stergeDupaDenumire(&lista, "Catena");
	afisareLista(lista);
	printf("-----------------VECTOR---------------------");
	int dimensiune;
	Farmacie* vectorFarmacii = vector(lista, &dimensiune, "HelpNet");
	for (int i = 0; i < dimensiune; i++) {
		afisareFarmacie(vectorFarmacii[i]);
	}

	return 0;
}