#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-un arbore binar de cautare
typedef struct Nod Nod;
struct Nod {
	Masina info;
	Nod* st;
	Nod* dr;
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


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiipile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID
	if ((*radacina)!= NULL) {
		if ((*radacina)->info.id > masinaNoua.id) 
		{
			adaugaMasinaInArbore(&((*radacina)->st), masinaNoua);
		}
		else 
		{
			adaugaMasinaInArbore(&((*radacina)->dr), masinaNoua);
		}
	}
	else
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->st = NULL;
		nou->dr = NULL;
		nou->info = masinaNoua;
		*radacina = nou;
	}

}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	Nod* arbore = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInArbore(&arbore,m);
	}
	fclose(f);
	return arbore;
}

void afisareInordine(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	
	if (radacina != NULL) {
		afisareInordine(radacina->st);
		afisareMasina(radacina->info);
		afisareInordine(radacina->dr);
	}
}
void afisarePreordine(Nod* radacina) {

	if (radacina != NULL) {
		afisareMasina(radacina->info);
		afisarePreordine(radacina->st);
		afisarePreordine(radacina->dr);
	}
}
void afisarePostordine(Nod* radacina) {

	if (radacina != NULL) {
		afisarePostordine(radacina->st);
		afisarePostordine(radacina->dr);
		afisareMasina(radacina->info);
	}
}

void dezalocareArboreDeMasini(Nod* *radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	if ((*radacina) != NULL) {
		Nod* st = (*radacina)->st;
		Nod* dr = (*radacina)->dr;
		free((*radacina)->info.numeSofer);
		free((*radacina)->info.model);
		free(*radacina);
		dezalocareArboreDeMasini(&st);
		dezalocareArboreDeMasini(&dr);
	}
}

Masina getMasinaByID(Nod* radacina,int id) {
	Masina m;
	if (radacina != NULL) 
	{
		if (id == radacina->info.id) 
		{
			m = radacina->info;//shallow copy
		}
		else
		{
			if (id < radacina->info.id)
				getMasinaByID(radacina->st, id);
			else
				getMasinaByID(radacina->dr, id);
		}
	}
	return m;
}

int determinaNumarNoduri(Nod* radacina) {
	
	if (radacina == NULL) 
		return 0;
	else
		return 1 + determinaNumarNoduri(radacina->st) + determinaNumarNoduri(radacina->dr);
}

int calculeazaInaltimeArbore(Nod* radacina) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza

	if (radacina == NULL)
		return 0;
	else
	{
		int inaltimeSt = calculeazaInaltimeArbore(radacina->st);
		int inaltimeDr = calculeazaInaltimeArbore(radacina->dr);

		int inaltimeMaxima;
		if (inaltimeSt > inaltimeDr)
			inaltimeMaxima = inaltimeSt;
		else
			inaltimeMaxima = inaltimeDr;

		return 1 + inaltimeMaxima;// +1 ptr nodul curent - radacina fiecarui subarbore
	}

	
}

float calculeazaPretTotal(Nod* radacina) {
	//calculeaza pretul tuturor masinilor din arbore.
	if (radacina == NULL)
		return 0;
	else
	{
		return radacina->info.pret 
			+ calculeazaPretTotal(radacina->st) 
			+ calculeazaPretTotal(radacina->dr);
	}
}

float calculeazaPretulMasinilorUnuiSofer(Nod* radacina, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.

	if (radacina == NULL)
		return 0;
	else {
		float suma = 0;

		if (strcmp(radacina->info.numeSofer, numeSofer) == 0) {
			suma += radacina->info.pret;
		}
		suma += calculeazaPretulMasinilorUnuiSofer(radacina->st, numeSofer);
		suma += calculeazaPretulMasinilorUnuiSofer(radacina->dr, numeSofer);

		return suma;
	}

	return 0;
}

int main() {

		Nod* arbore = citireArboreDeMasiniDinFisier("masini_arbore.txt");
		afisareInordine(arbore);


		printf("Numar total de noduri: %d\n", determinaNumarNoduri(arbore));
		printf("Inaltimea arborelui: %d\n", calculeazaInaltimeArbore(arbore));


		printf("Pretul total al masinilor: %.2f\n", calculeazaPretTotal(arbore));
		printf("Pretul masinilor soferului Gigel: %.2f\n", calculeazaPretulMasinilorUnuiSofer(arbore, "Gigel"));

		dezalocareArboreDeMasini(&arbore);


	return 0;
}