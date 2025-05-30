//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
////STACK
////Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
////putem reprezenta o stiva prin LSI, LDI sau vector
//
//typedef struct Nod Nod;
//
//struct Nod{
//	Nod* next;
//	Nod* prev;
//	Masina info;
//};
//
//typedef struct ListaDubla ListaDubla;
//
//struct ListaDubla {
//	Nod* first;
//	Nod* last;
//};
//
////void pushStack(Nod** stiva, Masina masina) {
////	Nod* nou = (Nod*)malloc(sizeof(Nod));
////	nou->next = (*stiva);
////	nou->info = masina;
////	(*stiva) = nou;
////}
////
////Masina popStack(Nod** stiva) {
////	if ((*stiva)!=NULL) {
////		Masina masinaNoua = (*stiva)->info;
////		Nod* temp = (*stiva);
////		(*stiva) = (*stiva)->next;
////		free(temp);
////
////		return masinaNoua;
////	}
////	else {
////		Masina m;
////		m.id = -1;
////		return m;
////	}
////
////}
////
//// unsigned char emptyStack(Nod* stiva) {
////	 return stiva == NULL;
////}
////
////Nod* citireStackMasiniDinFisier(const char* numeFisier) {
////	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
////	//prin apelul repetat al functiei citireMasinaDinFisier()
////	//ATENTIE - la final inchidem fisierul/stream-ul
////	Nod* stiva=NULL;
////	FILE* f = fopen(numeFisier, "r");
////	while (!feof(f)) {
////		Masina masina = citireMasinaDinFisier(f);
////		pushStack(&stiva, masina);
////	}
////	fclose(f);
////	return stiva;
////}
////
////void dezalocareStivaDeMasini(Nod** stiva) {
////	/*while ((*stiva)!=NULL) {
////		Nod* temp = (*stiva);
////		(*stiva) = (*stiva)->next;
////		free(temp->info.model);
////		free(temp->info.numeSofer);
////		free(temp);
////	}*/
////	while ((*stiva) != NULL) {
////		Masina m = popStack(stiva);
////		free(m.model);
////		free(m.numeSofer);
////	}
////}
////
////int size(Nod* stiva) {
////	int nrElemente = 0;
////	while (stiva != NULL) {
////		nrElemente++;
////		stiva = stiva->next;
////	}
////	return nrElemente;
////}
//
////QUEUE
////Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
////putem reprezenta o coada prin LSI, LDI sau vector
//void enqueue(ListaDubla* coada, Masina masina) {
//
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->next = NULL;
//	nou->prev = coada->last;
//	nou->info = masina;
//	if (coada->last != NULL)
//		coada->last->prev = nou;
//	else
//		coada->first = nou;
//	coada->last = nou;
//}
//
//Masina dequeue(ListaDubla* coada) {
//	
//	Masina m;
//	m.id = -1;
//	if (coada->first != NULL) {
//		m = coada->first->info;
//		Nod* aux = coada->first;
//		if (coada->first->next != NULL) {
//			coada->first = coada->first->next;
//			coada->first->prev = NULL;
//		}
//		else {
//			coada->first = NULL;
//			coada->last = NULL;
//		}
//		free(aux);
//	}
//		return m;
//}
//
//ListaDubla citireCoadaDeMasiniDinFisier(const char* numeFisier) {
//
//	FILE* f = fopen(numeFisier, "r");
//	ListaDubla coada;
//	coada.first = NULL;
//	coada.last = NULL;
//	while (!feof(f)) {
//		Masina m = citireMasinaDinFisier(f);
//		enqueue(&coada, m);
//	}
//	fclose(f);
//	return coada;
//}
//
//void dezalocareCoadaDeMasini(ListaDubla* coada) {
//
//	Nod* aux = coada->last;
//	while (aux) {
//		Nod* temp = aux;
//		aux = aux->prev;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//	}
//	coada->first = NULL;
//	coada->last = NULL;
//}
//
//
////metode de procesare
//Masina getMasinaByID(/*stiva sau coada de masini*/int id);
//
//float calculeazaPretTotal(/*stiva sau coada de masini*/);
//
//int main() {
//
//	/*Nod* stiva = citireStackMasiniDinFisier("masini.txt");
//	int nrNoduri = size(stiva);
//	printf("Nr noduri: %d\n\n", nrNoduri);
//	Masina m = popStack(&stiva);
//	afisareMasina(m);
//	dezalocareStivaDeMasini(&stiva);*/
//	return 0;
//}