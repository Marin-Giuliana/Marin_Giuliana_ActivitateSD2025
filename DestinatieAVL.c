//#define _CRT_SECURE_NO_WARNINGS
//#include <stdlib.h>
//#include<string.h>
//#include<stdio.h>
//
//typedef struct Destinatie Destinatie;
//typedef struct Nod Nod;
//
//struct Destinatie {
//	char* denumire;
//	char* tara;
//	int nrVizitatori;
//	float scor;
//};
//
//struct Nod{
//	Destinatie info;
//	Nod* st;
//	Nod* dr;
//};
//
//void afisareDestinatie(Destinatie d) {
//	printf("\nDestinatie: %s\n", d.denumire);
//	printf("Tara: %s\n", d.tara);
//	printf("Numarul vizitatorilor: %d\n", d.nrVizitatori);
//	printf("Scorul recenziilor: %.2f\n", d.scor);
//}
//
//Destinatie citireDestinatie(FILE* f) {
//	char buffer[100];
//	char del[3] = "\n,";
//	char* token;
//	Destinatie destinatie;
//	fgets(buffer, 100, f);
//	token = strtok(buffer,del);
//	destinatie.denumire = malloc(strlen(token) + 1);
//	strcpy_s(destinatie.denumire, strlen(token) + 1, token);
//	token = strtok(NULL, del);
//	destinatie.tara = malloc(strlen(token) + 1);
//	strcpy_s(destinatie.tara, strlen(token) + 1, token);
//	token = strtok(NULL, del);
//	destinatie.nrVizitatori = atoi(token);
//	token = strtok(NULL, del);
//	destinatie.scor = atof(token);
//	
//	return destinatie;
//}
//
//int calculeazaInaltime(Nod* radacina) {
//	if (radacina) {
//		
//		int st = calculeazaInaltime(radacina->st);
//		int dr = calculeazaInaltime(radacina->dr);
//		int maxim;
//		if (st > dr)
//			maxim = st;
//		else
//			maxim = dr;
//
//		return 1 + maxim;
//	}
//	else return 0;
//}
//
//int calculGradEchilibru(Nod* radacina) {
//	if (radacina) {
//
//		return calculeazaInaltime(radacina->st) - calculeazaInaltime(radacina->dr);
//	}
//	else return 0;
//}
//
//void rotireDreapta(Nod** radacina) {
//		Nod* aux = (*radacina)->st;
//		(*radacina)->st = aux->dr;
//		aux->dr = (*radacina);
//
//		(*radacina) = aux;
//}
//
//void rotireStanga(Nod** radacina) {
//	Nod* aux = (*radacina)->dr;
//	(*radacina)->dr = aux->st;
//	aux->st = (*radacina);
//
//	(*radacina) = aux;
//}
//
//void inserare(Nod** radacina, Destinatie d) {
//	if (*radacina) {
//		if (d.scor < (*radacina)->info.scor) {
//			inserare(&((*radacina)->st), d);
//		}
//		else if (d.scor >= (*radacina)->info.scor) {
//			inserare(&((*radacina)->dr), d);
//		}
//
//		int gradEchilibru = calculGradEchilibru((*radacina));
//		if (gradEchilibru == 2) {
//
//			if (calculGradEchilibru((*radacina)->st) == -1) {
//				rotireStanga(&((*radacina)->st));
//			}
//			rotireDreapta(radacina);
//		}
//		else if (gradEchilibru == -2) {
//
//			if (calculGradEchilibru((*radacina)->dr) == 1) {
//				rotireDreapta(&((*radacina)->dr));
//			}
//			rotireStanga(radacina);
//		}
//	}
//	else {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->st = NULL;
//		nou->dr = NULL;
//		nou->info = d;
//		(*radacina) = nou;
//	}
//}
//
//Nod* citireArbore(const char* fisier) {
//	FILE* f = fopen("destinatii.txt", "r");
//	Nod* arbore = NULL;
//	while (!feof(f)) {
//		Destinatie destinatie = citireDestinatie(f);
//		inserare(&arbore,destinatie);
//	}
//	fclose(f);
//	return arbore;
//}
//
//void afisareInordine(Nod* radacina) {
//	if (radacina) {
//		afisareInordine(radacina->st);
//		afisareDestinatie(radacina->info);
//		afisareInordine(radacina->dr);
//	}
//}
//
//void dezalocare(Nod** radacina) {
//	if (*radacina) {
//		dezalocare(&((*radacina)->st));
//		dezalocare(&((*radacina)->dr));
//		free((*radacina)->info.denumire);
//		free((*radacina)->info.tara);
//		free(*radacina);
//		(*radacina) = NULL;
//	}
//}
//
//int main() {
//
//	Nod* arbore = citireArbore("destinatii.txt");
//	afisareInordine(arbore);
//
//	dezalocare(&arbore);
//	return 0;
//}