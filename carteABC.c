//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//typedef struct Carte Carte;
//typedef struct Nod Nod;
//
//struct Carte {
//	char* titlu;
//	char* autor;
//	int anulPublicarii;
//	float nivelComplexitate;
//};
//
//struct Nod {
//	Nod* st;
//	Nod* dr;
//	Carte info;
//};
//
//
//void afisareCarte(Carte carte) {
//	printf("\nTitlu: %s\n", carte.titlu);
//	printf("Autor: %s\n", carte.autor);
//	printf("Anul publicarii: %d\n", carte.anulPublicarii);
//	printf("Nivel complexitate: %.2f\n", carte.nivelComplexitate);
//}
//Carte citireCarteFisier(FILE* f) {
//	char buffer[100];
//	char del[3] = "\n,";
//	char* token;
//	Carte c;
//	fgets(buffer, 100, f);
//	token = strtok(buffer, del);
//	c.titlu = malloc(strlen(token) + 1);
//	strcpy_s(c.titlu, strlen(token) + 1, token);
//	token = strtok(NULL, del);
//	c.autor = malloc(strlen(token) + 1);
//	strcpy_s(c.autor, strlen(token) + 1, token);
//	token = strtok(NULL, del);
//	c.anulPublicarii = atoi(token);
//	token = strtok(NULL, del);
//	c.nivelComplexitate = atof(token);
//
//	return c;
//
//}
//
//void inserare(Nod** radacina, Carte c) {
//	if ((*radacina) != NULL) {
//		if (c.anulPublicarii < (*radacina)->info.anulPublicarii) {
//			inserare(&((*radacina)->st), c);
//		}
//		else if (c.anulPublicarii >= (*radacina)->info.anulPublicarii) {
//			inserare(&((*radacina)->dr), c);
//		}
//	}
//	else {
//			Nod* nou = (Nod*)malloc(sizeof(Nod));
//			nou->st = NULL;
//			nou->dr = NULL;
//			nou->info = c;
//			(*radacina) = nou;
//	}
//}
//
//Nod* citireArboreFisier(const char* fisier) {
//	FILE* f = fopen(fisier, "r");
//	Nod* arbore=NULL;
//	while (!feof(f)) {
//		Carte c = citireCarteFisier(f);
//		inserare(&arbore,c);
//	}
//	fclose(f);
//	return arbore;
//}
//
//void parcurgereInordine(Nod* radacina) {
//	if (radacina != NULL) {
//		parcurgereInordine(radacina->st);
//		afisareCarte(radacina->info);
//		parcurgereInordine(radacina->dr);
//	}
//}
//
//void dezalocare(Nod** arbore) {
//	if ((*arbore) != NULL) {
//		dezalocare(&((*arbore)->st));
//		dezalocare(&((*arbore)->dr));
//		free((*arbore)->info.titlu);
//		free((*arbore)->info.autor);
//		free(*arbore);
//		(*arbore) = NULL;
//	}
//}
//
//Carte carteCautata(Nod* arbore,int an) {
//	Carte c;
//	c.titlu = NULL;
//	c.autor = NULL;
//	c.anulPublicarii = 0;
//	c.nivelComplexitate = 0;
//	if (arbore != NULL) {
//		if (an < arbore->info.anulPublicarii)
//			return carteCautata(arbore->st,an);
//		else if (an > arbore->info.anulPublicarii)
//			return carteCautata(arbore->dr, an);
//		else if (an == arbore->info.anulPublicarii)
//			return arbore->info;
//	}
//	return c;
//}
//
//Carte nivelMinimComplexitate(Nod* arbore) {
//	if (arbore == NULL) {
//		Carte carte;
//		carte.titlu = NULL;
//		carte.autor = NULL;
//		carte.anulPublicarii = 0;
//		carte.nivelComplexitate = 0;
//
//		return carte;
//	}
//	else {
//
//		Carte st = nivelMinimComplexitate(arbore->st);
//		Carte dr = nivelMinimComplexitate(arbore->dr);
//
//		Carte minim;
//		minim.anulPublicarii = arbore->info.anulPublicarii;
//		minim.nivelComplexitate = arbore->info.nivelComplexitate;
//		minim.titlu = malloc(strlen(arbore->info.titlu) + 1);
//		strcpy_s(minim.titlu, strlen(arbore->info.titlu) + 1, arbore->info.titlu);
//		minim.autor = malloc(strlen(arbore->info.autor) + 1);
//		strcpy_s(minim.autor, strlen(arbore->info.autor) + 1, arbore->info.autor);
//
//		
//		if (st.nivelComplexitate < minim.nivelComplexitate) {
//			minim.anulPublicarii = st.anulPublicarii;
//			minim.nivelComplexitate = st.nivelComplexitate;
//			minim.titlu = malloc(strlen(st.titlu) + 1);
//			strcpy_s(minim.titlu, strlen(st.titlu) + 1, st.titlu);
//			minim.autor = malloc(strlen(st.autor) + 1);
//			strcpy_s(minim.autor, strlen(st.autor) + 1, st.autor);
//		}
//		else if ( dr.nivelComplexitate < minim.nivelComplexitate) {
//			minim.anulPublicarii= dr.anulPublicarii;
//			minim.nivelComplexitate = dr.nivelComplexitate;
//			minim.titlu = malloc(strlen(dr.titlu) + 1);
//			strcpy_s(minim.titlu, strlen(dr.titlu) + 1, dr.titlu);
//			minim.autor = malloc(strlen(dr.autor) + 1);
//			strcpy_s(minim.autor, strlen(dr.autor) + 1, dr.autor);
//		}
//
//		return minim;
//	}
//}
//
//int main() {
//	
//
//	Nod* arbore = citireArboreFisier("carti.txt");
//	parcurgereInordine(arbore);
//	Carte c = carteCautata(arbore,1818);
//	afisareCarte(c);
//	Carte carte = nivelMinimComplexitate(arbore);
//	afisareCarte(carte);
//	dezalocare(&arbore);
//	return 0;
//}
