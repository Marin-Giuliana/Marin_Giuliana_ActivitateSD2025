//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include<stdlib.h>
//#include<string.h>
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
//	Nod* st;
//	Nod* dr;
//	Comanda info;
//};
//
//Comanda initializareComanda(int cod, char* numeClient, int nrProduse, float suma) {
//	Comanda c; 
//	c.cod = cod;
//	c.numeClient = malloc(strlen(numeClient) + 1);
//	strcpy_s(c.numeClient, strlen(numeClient) + 1, numeClient);
//	c.nrProduse = nrProduse;
//	c.suma = suma;
//
//	return c;
//}
//
//void afisare(Comanda comanda) {
//	printf("\nCod: %d\n", comanda.cod);
//	printf("Numele clientului: %s\n", comanda.numeClient);
//	printf("Nr produse: %d\n", comanda.nrProduse);
//	printf("Suma: %.2f\n", comanda.suma);
//}
//
//Comanda citireComanda(FILE* f) {
//	char buffer[100];
//	char del[3]="\n,";
//	char* token;
//	Comanda c;
//	fgets(buffer, 100, f);
//	token = strtok(buffer, del);
//	c.cod = atoi(token);
//	token = strtok(NULL, del);
//	c.numeClient = malloc(strlen(token)+1);
//	strcpy_s(c.numeClient, strlen(token) + 1, token);
//	token = strtok(NULL, del);
//	c.nrProduse = atoi(token);
//	token = strtok(NULL, del);
//	c.suma = atof(token);
//
//	return c;
//}
//
//int inaltimeArbore(Nod* radacina) {
//
//	if (radacina) {
//		int st = inaltimeArbore(radacina->st);
//		int dr = inaltimeArbore(radacina->dr);
//		int maxim; 
//		if (st > dr)
//			maxim = st;
//		else
//			maxim = dr;
//
//		return 1 + maxim;
//	}
//	else
//		return 0;
//}
//
//int calculGradEchilibru(Nod* radacina) {
//	return inaltimeArbore(radacina->st) - inaltimeArbore(radacina->dr);
//}
//
//void rotireDreapta(Nod** radacina) {
//	Nod* aux = (*radacina)->st;
//	(*radacina)->st = aux->dr;
//	aux->dr = (*radacina);
//	(*radacina) = aux;
//}
//
//void rotireStanga(Nod** radacina) {
//	Nod* aux = (*radacina)->dr;
//	(*radacina)->dr = aux->st;
//	aux->st = (*radacina);
//	(*radacina) = aux;
//}
//
//void inserare(Nod** radacina, Comanda c) {
//	if ((*radacina)) {
//
//		if (c.nrProduse < (*radacina)->info.nrProduse)
//			inserare(&((*radacina)->st), c);
//		else
//			inserare(&((*radacina)->dr), c);
//
//		int gradEchilibru = calculGradEchilibru(*radacina);
//		if (gradEchilibru == 2)
//		{
//			if (calculGradEchilibru((*radacina)->st) == -1)
//				rotireStanga(&((*radacina)->st));
//
//			rotireDreapta(radacina);
//		}
//		else if (gradEchilibru == -2) {
//
//			if (calculGradEchilibru((*radacina)->dr) == 1)
//				rotireDreapta(&((*radacina)->dr));
//			rotireStanga(radacina);
//		}
//	}
//	else
//	{
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->st = NULL;
//		nou->dr = NULL;
//		nou->info = c;
//		(*radacina) = nou;
//	}
//}
//
//Nod* citireArbore(const char* fisier) {
//	Nod* arbore = NULL;
//	FILE* f = fopen(fisier, "r");
//	while (!feof(f)) {
//		Comanda c = citireComanda(f);
//		inserare(&arbore,c);
//	}
//	fclose(f);
//
//	return arbore;
//}
//
//void parcurgereInordine(Nod* radacina) {
//	if (radacina != NULL) {
//		parcurgereInordine(radacina->st);
//		afisare(radacina->info);
//		parcurgereInordine(radacina->dr);
//	}
//}
//
//
//void dezalocare(Nod** arbore)
//{
//	if ((*arbore)) {
//		dezalocare(&((*arbore)->st));
//		dezalocare(&((*arbore)->dr));
//		free((*arbore)->info.numeClient);
//		free(*arbore);
//		(*arbore) = NULL;
//	}
//}
////pret total comenzi
////cauta comanda dupa nr produse
//
//float calculPretTotal(Nod* radacina) {
//
//	if (radacina == NULL)
//		return 0;
//	else
//	{
//		return radacina->info.suma + calculPretTotal(radacina->st) + calculPretTotal(radacina->dr);
//	}
//}
//
//Comanda comandaDupaNrProduse(Nod* arbore, int nr) {
//	Comanda c;
//	c.nrProduse = -1;
//	if (arbore != NULL) {
//		if(nr < arbore->info.nrProduse)
//			return comandaDupaNrProduse(arbore->st, nr);
//		 else if(nr > arbore->info.nrProduse)
//			return comandaDupaNrProduse(arbore->dr, nr);
//		 else if (nr == arbore->info.nrProduse) {
//			c.cod = arbore->info.cod;
//			c.numeClient = malloc(strlen(arbore->info.numeClient) + 1);
//			strcpy_s(c.numeClient, strlen(arbore->info.numeClient) + 1, arbore->info.numeClient);
//			c.nrProduse = arbore->info.nrProduse;
//			c.suma = arbore->info.suma;
//			
//		 }
//
//	}
//	return c;
//}
//
//int main() {
//
//	Nod* arbore = citireArbore("comenzi.txt");
//	parcurgereInordine(arbore);
//	float total = calculPretTotal(arbore);
//	printf("\nPretul total al tuturor comenzilor: %.2f\n", total);
//	Comanda c = comandaDupaNrProduse(arbore, 3);
//	printf("\nComanda cautata:\n");
//	afisare(c);
//	dezalocare(&arbore);
//
//	Nod* arbore2 = NULL;
//	Comanda c1 = initializareComanda(11, "Marcel", 3, 100);
//	Comanda c2 = initializareComanda(12, "Gigel", 2, 110);
//	Comanda c3 = initializareComanda(13, "Cornel", 1, 120);
//	Comanda c4 = initializareComanda(14, "Marcel", 4, 130);
//	inserare(&arbore2, c1);
//	inserare(&arbore2, c2);
//	inserare(&arbore2, c3);
//	inserare(&arbore2, c4);
//	parcurgereInordine(arbore2);
//
//	return 0;
//
//}