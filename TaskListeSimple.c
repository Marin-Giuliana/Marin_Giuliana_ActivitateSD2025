#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* next;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* lista) {
	while (lista) {
		afisareMasina(lista->info);
		lista = lista->next;
	}
}

void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	if ((*lista) == NULL) {
		(*lista) = nou;
	}
	else {
		Nod* temp = *lista;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void adaugaLaInceputInLista(Nod** lista, Masina masinaNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = *lista;
	*lista = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(file)) {
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(file));
	}
	fclose(file);
	return lista;
}

void dezalocareListaMasini(Nod** lista) {
	while (*lista)
	{
		Nod* p = (*lista);
		(*lista) = (*lista)->next;

		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
	}
}

float calculeazaPretMediu(Nod* lista) {
	float s = 0;
	int k = 0;

	while (lista)
	{
		s += lista->info.pret;
		k++;
		lista = lista->next;
	}

	return (k > 0) ? s / k : 0;
}

void stergeMasiniDinSeria(Nod** lista, char serieCautata) {

	while ((*lista) != NULL && (*lista)->info.serie == serieCautata) {
		Nod* temp = (*lista);
		(*lista) = temp->next;
		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);

	}
	Nod* p = (*lista);
	while (p != NULL) {
		while (p->next && p->next->info.serie != serieCautata) {
			p = p->next;

		}
		if (p->next != NULL) {
			Nod* temp = p->next;
			p->next = temp->next;
			free(temp->info.model);
			free(temp->info.numeSofer);
			free(temp);
		}
		else {
			p = p->next;
		}
	}
}

float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	float suma = 0;

	while (lista)
	{
		if (strcmp(lista->info.numeSofer, numeSofer) == 0)
		{
			suma += lista->info.pret;
		}
		lista = lista->next;
	}
	return suma;
}


void stergePozitie(Nod** cap, int pozitie) {

		Nod* p = (*cap);
		if (pozitie == 0)
		{
			(*cap) = p->next;
			free(p->info.model);
			free(p->info.numeSofer);
			free(p);
		}
		else
		{
			for (int k = 0; p != NULL && k < pozitie - 1; k++)
				p = p->next;

			Nod* sters = p->next;
			p->next = sters->next;
			free(sters->info.model);
			free(sters->info.numeSofer);
			free(sters);
		}
}

void inserareDupaPret(Nod** cap, Masina m)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->next = NULL;

	if ((*cap) == NULL || m.pret < (*cap)->info.pret) {
		nou->next = (*cap);
		(*cap) = nou;
	}

	Nod* aux = (*cap);
	while (aux->next && aux->next->info.pret < m.pret) {
		aux = aux->next;
	}
	nou->next = aux->next;
	aux->next = nou;
}

Masina* vectorMasini(Nod* cap, int* dimensiune, int pragNrUsi)
{
	*dimensiune = 0;
	Nod* aux = cap;

	while (aux) {
		if (aux->info.nrUsi > pragNrUsi)
		{
			(*dimensiune)++;
		}
		aux = aux->next;
	}

	Masina* vector = (Masina*)malloc((*dimensiune) * sizeof(Masina));
	int k = 0;
	while (cap) {
		if (cap->info.nrUsi > pragNrUsi) {
			Masina m;
			m.id = cap->info.id;
			m.nrUsi = cap->info.nrUsi;
			m.pret = cap->info.pret;
			m.serie = cap->info.serie;
			m.model = malloc(strlen(cap->info.model)+1);
			strcpy_s(m.model, strlen(cap->info.model)+1, cap->info.model);
			m.numeSofer = malloc(strlen(cap->info.numeSofer)+1);
			strcpy_s(m.numeSofer, strlen(cap->info.numeSofer)+1, cap->info.numeSofer);

			vector[k++]=m;
		}
		cap = cap->next;
	}
	return vector;
}

void inversarePozitii(Nod* cap, int p1, int p2)
{
	Nod* nod1=NULL;
	Nod* nod2=NULL;
	int k = 0;
	while (cap)
	{
		if (k == p1) nod1 = cap;
		if (k == p2) nod2 = cap;
		k++;
		cap = cap->next;
	}
	if (nod1 && nod2) {
		Masina aux = nod1->info;
		nod1->info = nod2->info;
		nod2->info = aux;
	}
}

int main() {

	Nod* masini = citireListaMasiniDinFisier("masini.txt");

	printf("----------LISTA INITIALA----------\n");
	afisareListaMasini(masini);

	printf("----------LISTA DUPA STERGEREA POZITIEI 3 EX1----------\n");
	stergePozitie(&masini,3);
	afisareListaMasini(masini);

	printf("----------INSERARE SORTATA DUPA PRET EX2 ----------\n");
	Masina mNoua;
	mNoua.id = 99;
	mNoua.nrUsi = 4;
	mNoua.pret = 15000;
	mNoua.model = (char*)malloc(strlen("Puma") + 1);
	strcpy_s(mNoua.model, strlen("Puma") + 1, "Puma");

	mNoua.numeSofer = (char*)malloc(strlen("Popescu") + 1);
	strcpy_s(mNoua.numeSofer, strlen("Popescu") + 1, "Popescu");

	mNoua.serie = 'Z';
	inserareDupaPret(&masini, mNoua);
	afisareListaMasini(masini);



	printf("----------VECTOR MASINI CU NR_USI > 4  EX3----------\n");
	int dim = 0;
	Masina* vector = vectorMasini(masini, &dim, 4);
	for (int i = 0; i < dim; i++) {
		afisareMasina(vector[i]);
		free(vector[i].model);
		free(vector[i].numeSofer);
	}
	free(vector);

	printf("----------DUPA INTERSCHIMBARE POZITII 1 SI 3 EX4----------\n");
	inversarePozitii(masini, 1, 3);
	afisareListaMasini(masini);

	printf("----------PRET MEDIU---------\n");
	printf("%.2f", calculeazaPretMediu(masini));
	printf("\n----------SUMA MASINI SOFER--------- \n");
	printf("Suma masinilor lui Ionescu: %.2f", calculeazaPretulMasinilorUnuiSofer(masini, "Ionescu"));
	printf("\nSterge seria A:\n");
	char serieCautata = 'A';
	stergeMasiniDinSeria(&masini, serieCautata);
	stergeMasiniDinSeria(&masini, 'B');
	afisareListaMasini(masini);
	dezalocareListaMasini(&masini);


	free(mNoua.model);
	free(mNoua.numeSofer);

	return 0;
}