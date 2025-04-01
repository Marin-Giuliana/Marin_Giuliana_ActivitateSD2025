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
};

void afisareMoneda(Moneda m) {

	printf("Tara emitenta: %s\n",m.taraEmitenta);
	printf("Valoare nominala: %d\n",m.valoareNominala);
	printf("Greutate: %.2f\n",m.greutate);
	printf("Anul emiterii: %d\n\n",m.anEmitere);
}

void traversareLista(Nod* cap) {
	while (cap) {
		afisareMoneda(cap->info);
		cap = cap->next;
	}
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

void adaugareInceput(Nod* *cap, Moneda moneda) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = moneda;
	nou->next = (*cap);
	(*cap) = nou;
}
void adaugaLaFinal(Nod* *cap, Moneda moneda) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = moneda;
	nou->next = NULL;
	if (*cap) {
		Nod* temp = *cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;
	}
	else
		(*cap) = nou;
}
Nod* citireListaDinFisier(const char* numeFisier){
	
	FILE* f = fopen(numeFisier, "r");
	Nod* cap = NULL;
	
	while (!feof(f)) {
		Moneda moneda = citireMonedaDinFisier(f);
		adaugaLaFinal(&cap, moneda);
	}
	fclose(f);
	return cap;
}



void dezalocare(Nod** cap) {
	
	while (*cap) {
		Nod* temp = (*cap);
		(*cap) = (*cap)->next;
		free(temp->info.taraEmitenta);
		free(temp);
	}
}

Moneda greutateMaxima(Nod* cap) {
	Nod* maxim = (Nod*)malloc(sizeof(Nod));
	maxim->info.greutate = 0.0;
	while (cap) {
		if (cap->info.greutate > maxim->info.greutate)
			maxim = cap;
		cap = cap->next;
	}
	Moneda m;
	m.taraEmitenta = malloc(sizeof(maxim->info.taraEmitenta) + 1);
	strcpy_s(m.taraEmitenta, sizeof(maxim->info.taraEmitenta) + 1, maxim->info.taraEmitenta);
	m.valoareNominala = maxim->info.valoareNominala;
	m.greutate = maxim->info.greutate;
	m.anEmitere = maxim->info.anEmitere;

	return m;
}

Moneda* transformareVector(Nod* cap, int* dimensiune, int pragAn) {
	*dimensiune = 0;
	Nod* temp = cap;
	while (temp) {
		if (temp->info.anEmitere > pragAn)
			(*dimensiune)++;
		temp = temp->next;
	}
	Moneda* vector = (Moneda*)malloc(sizeof(Moneda) * (*dimensiune));
	int k = 0;
	while (cap) {
		if (cap->info.anEmitere > pragAn) {
			Moneda m;
			m.taraEmitenta = malloc(strlen(cap->info.taraEmitenta) + 1);
			strcpy_s(m.taraEmitenta, strlen(cap->info.taraEmitenta) + 1, cap->info.taraEmitenta);
			m.valoareNominala = cap->info.valoareNominala;
			m.anEmitere = cap->info.anEmitere;
			m.greutate = cap->info.greutate;
			vector[k++] = m;
		}
		cap = cap->next;
	}

	return vector;
}

void stergere(Nod* *cap, float greutateConditie) {
	while (*cap && (*cap)->info.greutate == greutateConditie) {
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.taraEmitenta);
		free(temp);
	}
	Nod* curent = *cap;
	while (curent && curent->next) {
		if (curent->next->info.greutate == greutateConditie) {
			Nod* temp = curent->next;
			curent->next = curent->next->next;
			free(temp->info.taraEmitenta);
			free(temp);
		}
		else
			curent = curent->next;
	}
}



int main() {

	Nod* lista=NULL;
	Nod* lista2 = NULL;
	lista = citireListaDinFisier("monede.txt");
	lista2 = citireListaDinFisier("monede.txt");
	
	printf("Lista citita din fisier:\n");
	traversareLista(lista);
	
	printf("Moneda cu greutate maxima este:\n");
	Moneda m;
	m = greutateMaxima(lista);
	afisareMoneda(m);

	printf("Vector:\n");
	int dimensiune=0;
	Moneda* monedaVector = transformareVector(lista, &dimensiune, 2022);
	for (int i = 0; i < dimensiune; i++)
		afisareMoneda(monedaVector[i]);

	for (int i = 0; i < dimensiune; i++) {
		free(monedaVector[i].taraEmitenta);
	}
	free(monedaVector);

	printf("Lista citita din fisier 2:\n");
	stergere(&lista2, 4.27);
	traversareLista(lista2);

	dezalocare(&lista2);
	return 0;
}