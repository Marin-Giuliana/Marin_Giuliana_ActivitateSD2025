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
typedef struct ListaDubla ListaDubla;

struct Nod {
	Masina info;
	Nod* next;
	Nod* prev;
};
struct ListaDubla {
	Nod* head;
	Nod* tail;
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

void afisareListaMasini(ListaDubla lista) {
	Nod* aux = lista.head;
	while (aux) {
		afisareMasina(aux->info);
		aux = aux->next;
	}
}

void adaugaMasinaInLista(ListaDubla* lista,Masina masinaNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	if (lista->tail == NULL) {
		nou->prev = NULL;
		lista->head = lista->tail = nou;
	}
	else
	{
		nou->prev = lista->tail;
		lista->tail->next = nou;
		lista->tail = nou;
	}
}

void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->prev = NULL;

	if (lista->head == NULL) {
		nou->next = NULL;
		lista->head = lista->tail = nou;
	}
	else {
		nou->next = lista->head;
		lista->head->prev = nou;
		lista->head = nou;
	}
}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {

	ListaDubla lista = { NULL, NULL };
	FILE* file = fopen(numeFisier, "r");
	if (!file) return lista;

	while (!feof(file)) {
		Masina m = citireMasinaDinFisier(file);
		adaugaMasinaInLista(&lista, m);
	}

	fclose(file);
	return lista;
}


void dezalocareLDMasini(ListaDubla* lista) {
	Nod* aux;
	while (lista->head)
	{
		aux = lista->head;
		lista->head = lista->head->next;
		free(aux->info.model);
		free(aux->info.numeSofer);
		free(aux);
	}
	lista->tail = NULL;
}

float calculeazaPretMediu(ListaDubla lista) {

	float suma = 0;
	int k = 0;
	Nod* temp = lista.head;
	while (temp) {
		suma += temp->info.pret;
		k++;
		temp = temp->next;
	}

	if (k)
		return 0;
	else 
		return suma / k;
}

void stergeMasinaDupaID(ListaDubla* lista, int id) {

	Nod* aux = lista->head;
	while (aux) {
		if (aux->info.id == id) {
			if (aux->prev) 
				aux->prev->next = aux->next;
			else
				lista->head = aux->next;

			if (aux->next) 
				aux->next->prev = aux->prev;
			else 
				lista->tail = aux->prev;

			free(aux->info.model);
			free(aux->info.numeSofer);
			free(aux);
			return;
		}
		aux = aux->next;
	}
}

char* getNumeSoferMasinaScumpa(ListaDubla lista) {
	if (lista.head)
	{
		Nod* aux = lista.head;
		Nod* max = lista.head;

		while (aux) {
			if (aux->info.pret > max->info.pret) {
				max = aux;
			}
			aux = aux->next;
		}
		return max->info.numeSofer;
	}
	else 
		return NULL;
}

int main() {

	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasini(lista);

	printf("\nret mediu: %.2f\n", calculeazaPretMediu(lista));

	stergeMasinaDupaID(&lista, 1);
	printf("\nMaini dupa stergere:\n");
	afisareListaMasini(lista);

	printf("\nSoferul cu cea mai scumpa masina este: %s\n", getNumeSoferMasinaScumpa(lista));
	dezalocareLDMasini(&lista);

	return 0;
}