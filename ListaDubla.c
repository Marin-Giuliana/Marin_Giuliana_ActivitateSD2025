#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Moneda {
	char* taraEmitenta;
	int valoareNominala;
	float greutate;
	int anEmitere;
};

typedef struct Moneda Moneda;
typedef struct Nod Nod;

struct Nod {
	Moneda info;
	Nod* next;
	Nod* prev;
};

typedef struct ListaDubla ListaDubla;

struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};

void afisareMoneda(Moneda m) {

	printf("Tara emitenta: %s\n", m.taraEmitenta);
	printf("Valoare nominala: %d\n", m.valoareNominala);
	printf("Greutate: %.2f\n", m.greutate);
	printf("Anul emiterii: %d\n\n", m.anEmitere);
}

Moneda citireMonedaDinFisier(FILE* f) {
	Moneda m = { NULL,0,0.0,0 };
	char buffer[100];
	char sep[3] = ",\n";
	if (fgets(buffer, 100, f) == NULL) return m;

	char* token = strtok(buffer, sep);
	if (token == NULL) return m;
	m.taraEmitenta = malloc(strlen(token) + 1);
	strcpy_s(m.taraEmitenta, strlen(token) + 1, token);

	token = strtok(NULL, sep);
	if (token == NULL) return m;
	m.valoareNominala = atoi(token);

	token = strtok(NULL, sep);
	if (token == NULL) return m;
	m.greutate = atof(token);

	token = strtok(NULL, sep);
	if (token == NULL) return m;
	m.anEmitere = atoi(token);

	return m;
}

void traversareListaDeLaInceput(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareMoneda(p->info);
		p = p->next;
	}
}

void traversareListaDeLaFinal(ListaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afisareMoneda(p->info);
		p = p->prev;
	}
}

void adaugaLaInceput(ListaDubla* lista, Moneda monedaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = monedaNoua;
	nou->next = lista->first;
	nou->prev = NULL;
	if (lista->first != NULL) {
		lista->first->prev = nou;
	}
	else {
		lista->last = nou;
	}
	lista->first = nou;
	lista->nrNoduri++;
}

void adaugaLaFinal(ListaDubla* lista, Moneda monedaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = monedaNoua;
	nou->next = NULL;
	nou->prev = lista->last;
	if (lista->last != NULL) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->last = nou;
	lista->nrNoduri++;
}

ListaDubla citireListaDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	while (!feof(f)) {
		adaugaLaFinal(&lista, citireMonedaDinFisier(f));
	}
	fclose(f);
	return lista;
}


void dezalocare(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if (aux->info.taraEmitenta != NULL)
			free(aux->info.taraEmitenta);
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

float calculeazaGreutateMedie(ListaDubla lista) {
	float suma = 0;
	if (lista.nrNoduri > 0) {
		Nod* p = lista.first;
		while (p) {
			suma += p->info.greutate;
			p = p->next;
		}
		return suma / lista.nrNoduri;
	}
	else return 0;
}
void stergeDupaAn(ListaDubla* lista, int an) {
	if (lista->first == NULL) {
		return;
	}
	Nod* p = lista->first;
	while (p != NULL && p->info.anEmitere != an) {
		p = p->next;
	}
	if (p == NULL) {
		return;
	}
	if (p->prev == NULL) {
		lista->first = p->next;
		lista->first->prev = NULL;
	}
	else {
		p->prev->next = p->next;
	}
	if (p->next != NULL) {
		p->next->prev = p->prev;
	}
	else {
		lista->last = p->prev;
	}
	if (p->info.taraEmitenta != NULL)
		free(p->info.taraEmitenta);
	free(p);
	lista->nrNoduri--;
}

int main() {
	ListaDubla lista = citireListaDinFisier("monede.txt");
	traversareListaDeLaInceput(lista);
	printf("-------------------------------------\n");
	stergeDupaAn(&lista, 2022);
	traversareListaDeLaFinal(lista);



	float medie = calculeazaGreutateMedie(lista);
	printf("Media greutatii este: %.2f", medie);

	dezalocare(&lista);
	return 0;
}


