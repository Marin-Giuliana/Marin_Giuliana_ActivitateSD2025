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

	if ((*radacina) != NULL) {
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
	
	Nod* arbore = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInArbore(&arbore, m);
	}
	fclose(f);
	return arbore;
}

void afisareInordine(Nod* radacina) {

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

void dezalocareArboreDeMasini(Nod** radacina) {
	
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

Masina getMasinaByID(Nod* radacina, int id) {
	Masina m;
	if (radacina != NULL)
	{
		if (id == radacina->info.id)
		{
			m.id = radacina->info.id;
			m.nrUsi = radacina->info.nrUsi;
			m.pret = radacina->info.pret;
			m.serie = radacina->info.serie;
			m.model = malloc(strlen(radacina->info.model) + 1);
			strcpy_s(m.model, strlen(radacina->info.model) + 1, radacina->info.model);
			m.numeSofer = malloc(strlen(radacina->info.numeSofer) + 1);
			strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
		}
		else
		{
			if (id < radacina->info.id)
				return getMasinaByID(radacina->st, id);
			else
				return getMasinaByID(radacina->dr, id);
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

		return 1 + inaltimeMaxima;
	}


}

float calculeazaPretTotal(Nod* radacina) {
	
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
//-------------------Sablon seminar-----------------

//stergerea nodului radacina
Nod* stergereRadacina(Nod** radacina) {
	Nod* aux = (*radacina);
	if (aux->st != NULL) {
		(*radacina) = aux->st;
		if (aux->dr != NULL) {
			Nod* temp = aux->st;
			while (temp->dr)
				temp = temp->dr;
			temp->dr = aux->dr;
		}
	}
	else {
		if (aux->dr != NULL)
			(*radacina) = aux->dr;
		else
			(*radacina) = NULL;
	}
	free(aux->info.numeSofer);
	free(aux->info.model);
	free(aux);

	return (*radacina);
}

//stergerea unui nod dupa id
Nod* stergereNod(Nod** radacina, int id) {
	if ((*radacina) == NULL)
		return NULL;
	else {
		if ((*radacina)->info.id == id) {
			(*radacina) = stergereRadacina(radacina);
			return (*radacina);
		}
		else if (id < (*radacina)->info.id) {
			(*radacina)->st = stergereNod(&((*radacina)->st), id);
			return (*radacina);
		}
		else {
			(*radacina)->dr = stergereNod(&((*radacina)->dr), id);
			return (*radacina);
		}
	}
}

//subarborele cu inaltimea mai mare
void subarboreInaltimeMaiMare(Nod* radacina) {
	if (radacina == NULL)
		return;
	int inaltimeSt = calculeazaInaltimeArbore(radacina->st);
	int inaltimeDr = calculeazaInaltimeArbore(radacina->dr);

	if (inaltimeSt > inaltimeDr && radacina->st != NULL)
		afisareMasina(radacina->st->info);
	else if (radacina->dr != NULL)
		afisareMasina(radacina->dr->info);
}

//nr de noduri in subordine
int numarNoduriSubordine(Nod* radacina) {
	if (radacina == NULL)
		return 0;
	int noduriSt = determinaNumarNoduri(radacina->st);
	int noduriDr = determinaNumarNoduri(radacina->dr);
	return noduriSt + noduriDr;
}

//subarborele cu mai multe noduri in subordine
void subarboreMaiMulteNoduri(Nod* radacina) {
	if (radacina == NULL)
		return;
	int noduriSt = determinaNumarNoduri(radacina->st);
	int noduriDr = determinaNumarNoduri(radacina->dr);

	if (noduriSt > noduriDr && radacina->st != NULL)
		afisareMasina(radacina->st->info);
	else if (radacina->dr != NULL)
		afisareMasina(radacina->dr->info);
}


int main() {

	Nod* arbore = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareInordine(arbore);


	printf("\nNumar total de noduri: %d\n", determinaNumarNoduri(arbore));
	printf("\nInaltimea arborelui: %d\n", calculeazaInaltimeArbore(arbore));

	int idCautat = 2;
	printf("\nCautare masina:\n");
	Masina masinaGasita = getMasinaByID(arbore, idCautat);
	if (masinaGasita.model != NULL) {
		afisareMasina(masinaGasita);
		free(masinaGasita.model);
		free(masinaGasita.numeSofer);
	}
	else {
		printf("Masina cu ID %d nu a fost gasita!\n", idCautat);
	}

	printf("Pretul total al masinilor: %.2f\n", calculeazaPretTotal(arbore));
	printf("Pretul masinilor soferului Gigel: %.2f\n", calculeazaPretulMasinilorUnuiSofer(arbore, "Gigel"));

	arbore = stergereNod(&arbore, 5);
	printf("\nStergerea nodului cu id 5:\n");
	afisareInordine(arbore);

	printf("\nRadacina subarborelui cu inaltime mai mare:\n");
	subarboreInaltimeMaiMare(arbore);

	printf("\nNr noduri in subordine pentru radacina: %d\n", numarNoduriSubordine(arbore));

	printf("\nRadacina subarborelui cu mai multe noduri:\n");
	subarboreMaiMulteNoduri(arbore);


	dezalocareArboreDeMasini(&arbore);
	return 0;
}