//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//typedef struct Comanda Comanda;
//typedef struct Nod Nod;
//
//struct Comanda {
//	int cod;
//	char* numeClient;
//	int nrProduse;
//	float suma;
//};
//
//struct Nod {
//	Nod* next;
//	Comanda info;
//};
//
//void afisare(Comanda comanda) {
//	printf("\nCod comanda: %d\n", comanda.cod);
//	printf("Nume client: %s\n", comanda.numeClient);
//	printf("Numarul de produse: %d\n", comanda.nrProduse);
//	printf("Suma de plata: %.2f\n", comanda.suma);
//}
//
//Comanda citireComanda(FILE* f) {
//	Comanda c;
//	char buffer[100];
//	char del[3] = "\n,";
//	char* token;
//	fgets(buffer, 100, f);
//	token = strtok(buffer, del);
//	c.cod = atoi(token);
//	token = strtok(NULL, del);
//	c.numeClient = malloc(strlen(token) + 1);
//	strcpy_s(c.numeClient, strlen(token) + 1, token);
//	token = strtok(NULL, del);
//	c.nrProduse = atoi(token);
//	token = strtok(NULL, del);
//	c.suma = atof(token);
//
//	return c;
//}
//
//void pushCoada(Nod** coada, Comanda comanda) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = comanda;
//	nou->next = NULL;
//
//	if (*coada == NULL) {
//		*coada = nou;
//	}
//	else {
//		Nod* temp = *coada;
//		while (temp->next != NULL) {
//			temp = temp->next;
//		}
//		temp->next = nou;
//	}
//}
//
//
//Nod* citireCoada(const char* fisier) {
//	FILE* f = fopen(fisier, "r");
//	Nod* coada = NULL;
//	while (!feof(f)) {
//		Comanda c = citireComanda(f);
//		pushCoada(&coada, c);
//	}
//	fclose(f);
//	return coada;
//}
//
//void traversare(Nod* coada) {
//	while (coada) {
//		afisare(coada->info);
//		coada = coada->next;
//	}
//}
//
//
//void dezalocare(Nod** coada) {
//	while (*coada) {
//		Nod* temp = *coada;
//		
//		*coada = (*coada)->next;
//		free(temp->info.numeClient); 
//		free(temp);
//	}
//}
//
//
//Comanda popCoada(Nod** coada) {
//	Comanda c;
//	c.cod = -1;
//	if ((*coada) != NULL)
//	{
//		Nod* temp = *coada;
//		c = (*coada)->info;
//		(*coada) = (*coada)->next;
//		free(temp);
//	}
//	return c;
//}
//
//
//int main() {
//	Nod* coada = citireCoada("comenzi.txt");
//	traversare(coada);
//	Comanda comanda = popCoada(&coada);
//	afisare(comanda);
//
//	dezalocare(&coada);
//	return 0;
//}