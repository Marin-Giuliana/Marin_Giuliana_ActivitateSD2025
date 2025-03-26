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
typedef struct ListaDubla ListaDubla;
typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* next;
	Nod* prev;
};

struct ListaDubla {
	Nod* head;
	Nod* tail;
	int nrNoduri;
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

void afisareListaMasiniDeLaFinal(ListaDubla lista) {
	Nod* nou = lista.tail;
	while (nou)
	{
		afisareMasina(nou->info);
		nou = nou->prev;
	}
}

void afisareListaMasiniDeLaInceput(ListaDubla lista)
{
	Nod* nou = lista.head;
	while (nou)
	{
		afisareMasina(nou->info);
		nou = nou->next;
	}
}

void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = masinaNoua;
	nou->next = NULL;
	nou->prev = lista->tail;

	if (!lista->head)
	{
		lista->head = nou;
		lista->nrNoduri++;
	}
	else
	{
		lista->tail->next = nou;
		lista->nrNoduri++;
	}
	lista->tail = nou;
}

void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = masinaNoua;
	nou->prev = NULL;
	nou->next = lista->head;

	if (!lista->tail)
	{
		lista->tail = nou;
		lista->nrNoduri++;
	}
	else
	{
		lista->head->prev = nou;
		lista->nrNoduri++;
	}
	lista->head = nou;
}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	ListaDubla lista;
	lista.head = lista.tail = NULL;
	lista.nrNoduri = 0;

	FILE* f = fopen(numeFisier, "r");

	while (!feof(f))
	{
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareLDMasini(ListaDubla* lista) {
	Nod* nou = lista->head;

	while (nou->next)
	{
		free(nou->info.numeSofer);
		free(nou->info.model);
		nou = nou->next;
		free(nou->prev);
	}
	free(nou->info.numeSofer);
	free(nou->info.model);
	free(nou);

	lista->head = lista->tail = NULL;
	lista->nrNoduri = 0;
}

float calculeazaPretMediu(ListaDubla lista) {
	Nod* aux = lista.head;
	float suma = 0;

	while (aux)
	{
		suma += aux->info.pret;
		aux = aux->next;
	}
	return (suma > 0) ? suma / lista.nrNoduri : 0;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(ListaDubla lista) {
	Nod* nou = lista.head;
	Nod* nodMaxim = lista.head;

	while (nou)
	{
		if (nou->info.pret > nodMaxim->info.pret)
		{
			nodMaxim->info.pret = nou->info.pret;
		}
		nou = nou->next;
	}
	return nodMaxim->info.numeSofer;
}

int main() {
	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
	//afisareListaMasiniDeLaFinal(lista);
	//printf("\n--------------------\n");
	afisareListaMasiniDeLaInceput(lista);
	printf("--------------------\n");
	printf("Pret mediu: %.2f\n", calculeazaPretMediu(lista));
	printf("--------------------\n");
	printf("Nume sofer masina scumpa: %s", getNumeSoferMasinaScumpa(lista));
	dezalocareLDMasini(&lista);
	//afisareListaMasiniDeLaFinal(lista);

	return 0;
}