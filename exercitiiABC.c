#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct PiesaTeatru PiesaTeatru;
typedef struct Nod Nod;

struct PiesaTeatru {
	char* titlu;
	int durata;
	int anPremiera;
	float scor;
};

struct Nod {
	PiesaTeatru info;
	Nod* st;
	Nod* dr;
};

void afisarePiesa(PiesaTeatru pt) {
	printf("\nTitlu: %s\n", pt.titlu);
	printf("Durata: %d\n", pt.durata);
	printf("Anul premierii: %d\n", pt.anPremiera);
	printf("Scorul: %.2f\n", pt.scor);
}

PiesaTeatru citirePiesa(FILE* f) {
	PiesaTeatru piesa;
	char buffer[100];
	char del[3] = "\n,";
	char* token;
	fgets(buffer, 100, f);
	token = strtok(buffer, del);
	piesa.titlu = (char*)malloc(sizeof(char) * strlen(token) + 1);
	strcpy_s(piesa.titlu, strlen(token) + 1, token);
	token = strtok(NULL, del);
	piesa.durata = atoi(token);
	token = strtok(NULL, del);
	piesa.anPremiera = atoi(token);
	token = strtok(NULL, del);
	piesa.scor = atof(token);

	return piesa;
}

void inserareInArbore(Nod** radacina, PiesaTeatru piesaNoua) {
	if ((*radacina) != NULL) {
		if (strcmp(piesaNoua.titlu,(*radacina)->info.titlu)>=0) {
			inserareInArbore(&((*radacina)->dr), piesaNoua);
		}
		else if (strcmp(piesaNoua.titlu, (*radacina)->info.titlu) < 0) {
			inserareInArbore(&((*radacina)->st), piesaNoua);
		}
	}
	else {
		(*radacina) = (Nod*)malloc(sizeof(Nod));
		(*radacina)->info = piesaNoua;
		(*radacina)->st = NULL;
		(*radacina)->dr = NULL;
	}
}

Nod* citireArboreDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* arbore=NULL;
	while (!feof(f)) {
		PiesaTeatru pt = citirePiesa(f);
		inserareInArbore(&arbore, pt);
	}
	fclose(f);

	return arbore;
}

void parcurgereInordine(Nod* radacina) {
	if (radacina != NULL) {
		parcurgereInordine(radacina->st);
		afisarePiesa(radacina->info);
		parcurgereInordine(radacina->dr);
	}
}

void dezalocare(Nod** arbore) {
	if ((*arbore) != NULL)
	{
		dezalocare(&(*arbore)->st);
		dezalocare(&(*arbore)->dr);
		free((*arbore)->info.titlu);
		free(*arbore);
		(*arbore) = NULL;
	}
}

PiesaTeatru piesaPopulara(Nod* arbore) {
	
	if (arbore == NULL) {
		PiesaTeatru pt;
		pt.titlu = NULL;
		pt.anPremiera = 0;
		pt.durata = 0;
		pt.scor = 0;

		return pt;
	}
	else
	{
		PiesaTeatru st = piesaPopulara(arbore->st);
		PiesaTeatru dr = piesaPopulara(arbore->dr);
		PiesaTeatru maxim;
		maxim.anPremiera = arbore->info.anPremiera;
		maxim.durata = arbore->info.durata;
		maxim.scor = arbore->info.scor;
		maxim.titlu = malloc(strlen(arbore->info.titlu) + 1);
		strcpy_s(maxim.titlu, strlen(arbore->info.titlu) + 1, arbore->info.titlu);
		if (st.scor > maxim.scor)
			maxim = st;
		if (dr.scor > maxim.scor)
			maxim = dr;

		return maxim;
	}
}

PiesaTeatru cautaPiesaDupaTitlu(Nod* arbore, const char* t){
	PiesaTeatru p;
	p.titlu = NULL;
	if (arbore) {
		if (strcmp(t, arbore->info.titlu) > 0)
			return cautaPiesaDupaTitlu(arbore->dr, t);
		else if (strcmp(t, arbore->info.titlu) < 0)
			return cautaPiesaDupaTitlu(arbore->st, t);
		else
			return arbore->info;
	}
	return p;
}


int main() {
	Nod* arbore = citireArboreDinFisier("piese.txt");
	parcurgereInordine(arbore);
	PiesaTeatru piesa = piesaPopulara(arbore);
	afisarePiesa(piesa);
	PiesaTeatru pt = cautaPiesaDupaTitlu(arbore, "Romeo si Julieta");
	afisarePiesa(pt);
	dezalocare(&arbore);
	return 0;
}