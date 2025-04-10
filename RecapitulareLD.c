#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct Moneda {
	char* taraEmitenta;
	int valoareNominala;
	float greutate;
	int anEmitere;
};
typedef struct Moneda Moneda;
typedef struct Nod Nod;

struct Nod {
	Nod* next;
	Nod* prev;
	Moneda info;
};
typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};

void afisareMoneda(Moneda m) {
	printf("\nTara emitenta: %s\n", m.taraEmitenta);
	printf("Valoare nominala: %d\n", m.valoareNominala);
	printf("Greutate: %.2f\n", m.greutate);
	printf("Anul emiterii: %d\n", m.anEmitere);
}

void afisareLista(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareMoneda(p->info);
		p = p->next;
	}
}

Moneda citireMonedaDinFisier(FILE* f) {

	Moneda m;
	char buffer[100];
	char sep[3] = "\n,";
	char* token;
	fgets(buffer, 100, f);
	token = strtok(buffer, sep);
	m.taraEmitenta = (char*)malloc(strlen(token) + 1);
	strcpy_s(m.taraEmitenta, strlen(token) + 1, token);
	token = strtok(NULL, sep);
	m.valoareNominala = atoi(token);
	token = strtok(NULL, sep);
	m.greutate = atof(token);
	token = strtok(NULL, sep);
	m.anEmitere = atoi(token);

	return m;
}

Moneda initilizareMoneda(char* tara, int valoare, float greutate, int an) {
	Moneda m;
	m.taraEmitenta = (char*)malloc(sizeof(char) * strlen(tara) + 1);
	strcpy_s(m.taraEmitenta, strlen(tara) + 1, tara);
	m.valoareNominala = valoare;
	m.greutate = greutate;
	m.anEmitere = an;
	return m;
}

void adaugaLaFinal(ListaDubla* lista, Moneda monedaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = monedaNoua;
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

ListaDubla citireListaDinFisier(const char* numeFisier) {
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Moneda m = citireMonedaDinFisier(f);
		adaugaLaFinal(&lista, m);
	}
	fclose(f);
	return lista;
}

void adaugaLaInceput(ListaDubla* lista, Moneda monedaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = monedaNoua;
	nou->next = lista->first;
	nou->prev = NULL;
	if (lista->first) {
		lista->first->prev = nou;
	}
	else {
		lista->last = nou;
	}
	lista->first = nou;
	lista->nrNoduri++;
}

void dezalocare(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* temp = p;
		p = p->next;
		free(temp->info.taraEmitenta);
		free(temp);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

void stergereDupaGreutate(ListaDubla* lista, float greutate) {
	if (lista->first == NULL) return;
	Nod* p = lista->first;
	while (p != NULL) {
		Nod* temp = p->next;
		if (p->info.greutate == greutate) {
			if (p->prev) {
				p->prev->next = p->next;
			}
			else {
				lista->first = p->next;
				if (lista->first)
					lista->first->prev = NULL;
			}
			if (p->next) {
				p->next->prev = p->prev;
			}
			else {
				lista->last = p->prev;
			}
			free(p->info.taraEmitenta);
			free(p);
			lista->nrNoduri--;
		}
		p = temp;
	}
}

Moneda* transformareInVector(ListaDubla lista, int* dimensiune, char* tara) {
	int k = 0;
	Nod* p = lista.first;
	while (p) {
		if (strcmp(p->info.taraEmitenta, tara) == 0)
			k++;
		p = p->next;
	}
	Nod* temp = lista.first;
	int contor = 0;
	Moneda* vector = (Moneda*)malloc(sizeof(Moneda) * k);
	while (temp) {
		if (strcmp(temp->info.taraEmitenta, tara) == 0) {
			vector[contor].anEmitere = temp->info.anEmitere;
			vector[contor].greutate = temp->info.greutate;
			vector[contor].valoareNominala = temp->info.valoareNominala;
			vector[contor].taraEmitenta = (char*)malloc(strlen(temp->info.taraEmitenta) + 1);
			strcpy_s(vector[contor].taraEmitenta, strlen(temp->info.taraEmitenta) + 1, tara);
			contor++;
		}
		temp = temp->next;
	}
	*dimensiune = k;
	return vector;

}

int main() {
	ListaDubla lista = citireListaDinFisier("monede.txt");
	afisareLista(lista);
	/*lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	Moneda m1 = initilizareMoneda("Romania", 10, 25.5, 2020);
	Moneda m2 = initilizareMoneda("Italia", 15, 30.5, 2021);
	Moneda m3 = initilizareMoneda("Romania", 15, 25.5, 2022);
	Moneda m4 = initilizareMoneda("Spania", 10, 20.75, 2023);
	Moneda m5 = initilizareMoneda("Bulgaria", 10, 25.5, 2024);
	adaugaLaFinal(&lista, m1);
	adaugaLaFinal(&lista, m2);
	adaugaLaFinal(&lista, m3);
	adaugaLaFinal(&lista, m4);
	adaugaLaFinal(&lista, m5);
	afisareLista(lista);

	printf("----------VECTOR----------\n");
	int dim;
	Moneda* vector = transformareInVector(lista, &dim, "Romania");
	for (int i = 0; i < dim; i++) {
		afisareMoneda(vector[i]);
	}

	for (int i = 0; i < dim; i++) {
		free(vector[i].taraEmitenta);
	}
   free(vector);

	printf("----------STERGERE----------\n");
	stergereDupaGreutate(&lista, 25.5);
	afisareLista(lista);
	dezalocare(&lista);*/
	return 0;
}