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
	Moneda info;
};

void afisareMoneda(Moneda m) {
	printf("\nTara emitenta: %s\n", m.taraEmitenta);
	printf("Valoare nominala: %d\n", m.valoareNominala);
	printf("Greutate: %.2f\n", m.greutate);
	printf("Anul emiterii: %d\n", m.anEmitere);
}

Moneda initializareMoneda(char* taraEmitentaN, int valoareNominalaN, float greutateN, int anEmitereN) {
	Moneda m;
	m.taraEmitenta = (char*)malloc(strlen(taraEmitentaN) + 1);
	strcpy_s(m.taraEmitenta, strlen(taraEmitentaN) + 1, taraEmitentaN);
	m.valoareNominala = valoareNominalaN;
	m.greutate = greutateN;
	m.anEmitere = anEmitereN;
	return m;
}

void traversareLista(Nod* cap) {
	while (cap) {
		afisareMoneda(cap->info);
		cap = cap->next;
	}
}

void adaugarelaFinal(Nod** cap, Moneda monedaNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = monedaNoua;
	nou->next = NULL;
	if (*cap) {
		Nod* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else
	{
		*cap = nou;
	}
}

void adaugareLaInceput(Nod** cap, Moneda monedaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = monedaNoua;
	nou->next = *cap;
	*cap = nou;
}

void dezalocare(Nod** cap) {
	while (*cap) {
		Nod* p = *cap;
		(*cap) = (*cap)->next;
		free(p->info.taraEmitenta);
		free(p);
	}
	*cap = NULL;
}

void stergeMoneda(Nod** cap, int an) {
	while ((*cap) != NULL && (*cap)->info.anEmitere == an) {
		Nod* p = *cap;
		(*cap) = (*cap)->next;
		free(p->info.taraEmitenta);
		free(p);
	}
	Nod* curent = *cap;
	while (curent != NULL && curent->next != NULL) {
		if (curent->next->info.anEmitere == an)
		{
			Nod* p = curent->next;
			curent->next = curent->next->next;
			free(p->info.taraEmitenta);
			free(p);
		}
		else
			curent = curent->next;
	}
}

Moneda greutateMaxima(Nod* cap) {
	Moneda max;
	float maxim = 0.0;
	while (cap) {
		if (cap->info.greutate > maxim)
		{
			maxim = cap->info.greutate;
			max.anEmitere = cap->info.anEmitere;
			max.greutate = cap->info.greutate;
			max.valoareNominala = cap->info.valoareNominala;
			max.taraEmitenta = (char*)malloc(strlen(cap->info.taraEmitenta) + 1);
			strcpy_s(max.taraEmitenta, strlen(cap->info.taraEmitenta) + 1, cap->info.taraEmitenta);
		}
		cap = cap->next;
	}
	return max;
}

Moneda* transformareVector(Nod* cap, char* tara, int* dimensiune) {
	int k = 0;
	Nod* p = cap;
	while (cap) {
		if (strcmp(cap->info.taraEmitenta, tara) == 0) {
			k++;
		}
		cap = cap->next;
	}
	int contor = 0;
	Moneda* vector = (Moneda*)malloc(sizeof(Moneda) * k);
	while (p) {
		if (strcmp(p->info.taraEmitenta, tara) == 0) {
			vector[contor].anEmitere = p->info.anEmitere;
			vector[contor].valoareNominala = p->info.valoareNominala;
			vector[contor].greutate = p->info.greutate;
			vector[contor].taraEmitenta = (char*)malloc(strlen(p->info.taraEmitenta) + 1);
			strcpy_s(vector[contor].taraEmitenta, strlen(p->info.taraEmitenta) + 1, p->info.taraEmitenta);
			contor++;
		}
		p = p->next;
	}
	*dimensiune = k;
	return vector;
}


int main() {

	Nod* lista = NULL;
	Moneda m1 = initializareMoneda("Romania", 50, 15.5, 2020);
	Moneda m2 = initializareMoneda("Ungaria", 20, 10.5, 2021);
	Moneda m3 = initializareMoneda("Romania",10, 7.25, 2022);
	Moneda m4 = initializareMoneda("Franta", 5, 4.25, 2023);
	Moneda m5 = initializareMoneda("Spania", 25, 12.75, 2024);

	adaugarelaFinal(&lista, m1);
	adaugarelaFinal(&lista, m2);
	adaugarelaFinal(&lista, m3);
	adaugarelaFinal(&lista, m4);
	adaugarelaFinal(&lista, m5);
	traversareLista(lista);
	
	printf("--------------------------MONEDA MAX--------------------\n");
	Moneda maxima = greutateMaxima(lista);
	afisareMoneda(maxima);
	free(maxima.taraEmitenta);

	printf("--------------------------VECTOR--------------------\n");
	int dim;
	Moneda* vector = transformareVector(lista, "Romania", &dim);
	for (int i = 0; i < dim; i++) {
		afisareMoneda(vector[i]);
	}

	for (int i = 0; i < dim; i++) {
		free(vector[i].taraEmitenta);
	}
	free(vector);
	printf("-----------------------------STERGERE--------------------\n");
	stergeMoneda(&lista, 2020);
	stergeMoneda(&lista, 2024);
	stergeMoneda(&lista, 2022);
	traversareLista(lista);
	
	dezalocare(&lista);
	return 0;
}