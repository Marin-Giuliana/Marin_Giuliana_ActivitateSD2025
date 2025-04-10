#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Farmacie {
	char* denumire;
	float suprafata;
	unsigned int nrAngajati;
};
typedef struct Farmacie Farmacie;
typedef struct Nod Nod;

struct Nod {
	Nod* next;
	Farmacie info;
};

void afisareFarmacie(Farmacie farma){
	printf("\nDenumirea farmaciei: %s\n",farma.denumire);
	printf("Suprafata farmaciei: %.2f\n",farma.suprafata);
	printf("Numarul de angajati: %u\n",farma.nrAngajati);
}

Farmacie citireFarmacieDinFisier(FILE* f) {
	char buffer[100];
	char sep[3] = "\n,";
	char* token;
	fgets(buffer, 100, f);
	Farmacie farmacie;
	token = strtok(buffer, sep);
	farmacie.denumire = (char*)malloc(sizeof(char) * strlen(token) + 1);
	strcpy_s(farmacie.denumire, strlen(token) + 1, token);
	token = strtok(NULL, sep);
	farmacie.suprafata = atof(token);
	token = strtok(NULL, sep);
	farmacie.nrAngajati = atoi(token);

	return farmacie;
}

void inserareFarmacieLaFinal(Nod** cap, Farmacie farmacieNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = farmacieNoua;
	nou->next = NULL;
	if (*cap) {
		Nod* p = *cap;
		while (p->next)
			p = p->next;

		p->next = nou;	
	}
	else
	{
		*cap = nou;
	}
}

Nod* citireListaDinFisier(const char* numeFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		Farmacie farmacie = citireFarmacieDinFisier(f);
		inserareFarmacieLaFinal(&cap, farmacie);
	}
	fclose(f);
	return cap;
}

void afisareLista(Nod* cap,int n) {
	while (cap!=NULL && n>0) {
		afisareFarmacie(cap->info);
		cap = cap->next;
		n--;
	}
}

void dezalocare(Nod** cap) {

	while(*cap) {
		Nod* p = *cap;
		(*cap) = (*cap)->next;
		free(p->info.denumire);
		free(p);
	}
}

void stergeDupaNrAngajatilor(Nod** cap, unsigned int angajati) {
	while ((*cap) && (*cap)->info.nrAngajati == angajati)
	{
		Nod* temp = *cap;
		(*cap) = (*cap)->next;
		free(temp->info.denumire);
		free(temp);
	}

	Nod* curent = *cap;
	while (curent != NULL && curent->next != NULL) {
		if (curent->next->info.nrAngajati == angajati)
		{
			Nod* temp = curent->next;
			curent->next = curent->next->next;
			free(temp->info.denumire);
			free(temp);
		}
		else {
			curent = curent->next;
		}
	}
}

//returnez prima farmacie HelpNet
Farmacie cautaPrimaFarmacieDupaDenumire(Nod* cap, char* denum) {
	int ok = 0;
	Farmacie farmacieCautata = { NULL,0.0,0 };
	while (cap) {
		if ((strcmp(cap->info.denumire, denum) == 0) && ok==0)
		{
			ok = 1;
			farmacieCautata.denumire = (char*)malloc(sizeof(char) * strlen(cap->info.denumire) + 1);
			strcpy_s(farmacieCautata.denumire, strlen(cap->info.denumire) + 1, cap->info.denumire);
			farmacieCautata.nrAngajati = cap->info.nrAngajati;
			farmacieCautata.suprafata = cap->info.suprafata;
		}
		cap = cap->next;
	}
	return farmacieCautata;
}

float calculeazaNumarMediuAngajati(Nod* cap) {
	float suma=0;
	int k = 0;
	Nod* p = cap;
	while (p)
	{
		k++;
		suma += p->info.nrAngajati;
		p = p->next;
	}
	if (k)
		return suma / k;
	else
		return 0;

}

void afiseazaDouaMaxime(Nod* cap) {
	Nod* max1 = NULL;
	Nod* max2 = NULL;

	while (cap) {
		if (max1 == NULL || cap->info.suprafata > max1->info.suprafata) {
			max2 = max1;
			max1 = cap;
		}
		else if (max2 == NULL || cap->info.suprafata > max2->info.suprafata) {
			max2 = cap;
		}
		cap = cap->next;
	}

	if (max1) {
		printf("\nFarmacia cu cea mai mare suprafata:\n");
		afisareFarmacie(max1->info);
	}
	if (max2) {
		printf("\nFarmacia cu a doua cea mai mare suprafata:\n");
		afisareFarmacie(max2->info);
	}
	if (max1 == NULL && max2 == NULL) {
		printf("Nu exista doua farmacii in lista.\n");
	}
}


Farmacie* transformareInVectorDupaDenumire(Nod* cap, char* denum, int* dimensiune) {
	Nod* p = cap;
	int k = 0;
	while (p) {
		if(strcmp(p->info.denumire,denum)==0)
			k++;
		p = p->next;
	}
	Farmacie* vector = malloc(sizeof(Farmacie) * k);
	p = cap;
	int contor=0;
	while (p) {
		if (strcmp(p->info.denumire, denum) == 0)
		{
			vector[contor] = p->info;
			/*vector[contor].denumire = malloc(strlen(p->info.denumire) + 1);
			strcpy(vector[contor].denumire, p->info.denumire);
			vector[contor].suprafata = p->info.suprafata;
			vector[contor].nrAngajati = p->info.nrAngajati;*/
			contor++;
		}
		p = p->next;
	}
	
	*dimensiune = k;

	return vector;

}


int main() {
	Nod* lista = citireListaDinFisier("farmacii.txt");
	afisareLista(lista,3);
	printf("-----------------------------------------------------------");
	/*stergeDupaNrAngajatilor(&lista, 12);
	afisareLista(lista);
	printf("-----------------------------------------------------------");
	stergeDupaNrAngajatilor(&lista, 20);
	afisareLista(lista);
	printf("-----------------------------------------------------------");
	stergeDupaNrAngajatilor(&lista, 10);
	afisareLista(lista);*/

	afiseazaDouaMaxime(lista);
	float nrMediuAngajati = calculeazaNumarMediuAngajati(lista);
	printf("\nNumarul mediu de angajati: %.2f", nrMediuAngajati);
	Farmacie farmacieCautata = cautaPrimaFarmacieDupaDenumire(lista, "HelpNet");
	printf("\nFarmacia cautata este: ");
	afisareFarmacie(farmacieCautata);

	printf("----------------------------PARCURGEM VECTORUL-------------------------------");
	int dim;
	Farmacie* v = transformareInVectorDupaDenumire(lista, "HelpNet", &dim);
	/*for (int i = 0; i < dim; i++) {
		afisareFarmacie(v[i]);
	}*/
	free(v);
	dezalocare(&lista);
	return 0;
}
