#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Comanda Comanda;
typedef struct Nod Nod;

struct Comanda {
	int cod;
	char* numeClient;
	int nrProduse;
	float suma;
};

struct Nod {
	Nod* st;
	Nod* dr;
	Comanda info;
};

void afisare(Comanda c) {
	printf("\nCod comanda: %d\n", c.cod);
	printf("Nume client: %s\n", c.numeClient);
	printf("Nr produse: %d\n", c.nrProduse);
	printf("Total: %.2f\n", c.suma);
}

Comanda citireComanda(FILE* f) {
	char buffer[100];
	char del[3] = ",\n";
	char* token;
	Comanda c;
	fgets(buffer, 100, f);
	token = strtok(buffer, del);
	c.cod = atoi(token);
	token = strtok(NULL, del);
	c.numeClient = malloc(strlen(token) + 1);
	strcpy_s(c.numeClient, strlen(token) + 1, token);
	token = strtok(NULL, del);
	c.nrProduse = atoi(token);
	token = strtok(NULL, del);
	c.suma = atof(token);

	return c;
}

int calculInaltime(Nod* radacina) {
	if (radacina) {
		int st = calculInaltime(radacina->st);
		int dr = calculInaltime(radacina->dr);
		int maxim;
		if (st > dr)
			maxim = st;
		else
			maxim = dr;

		return 1 + maxim;
	}
	else 
		return 0;
}

int calculGradEchilibru(Nod* radacina) {
	return calculInaltime(radacina->st) - calculInaltime(radacina->dr);
}

void rotireDreapta(Nod** radacina) {
	Nod* aux = (*radacina)->st;
	(*radacina)->st = aux->dr;
	aux->dr = (*radacina);
	(*radacina) = aux;
}

void rotireStanga(Nod** radacina) {
	Nod* aux = (*radacina)->dr;
	(*radacina)->dr = aux->st;
	aux->st = (*radacina);
	(*radacina) = aux;
}

void inserare(Nod** radacina, Comanda c) {
	if ((*radacina)) {
		if (c.nrProduse < (*radacina)->info.nrProduse)
			inserare(&((*radacina)->st), c);
		else
			inserare(&((*radacina)->dr), c);

		int gradEchilibru = calculGradEchilibru(*radacina);
		if (gradEchilibru == 2) {

			if (calculGradEchilibru((*radacina)->st) == -1)
				rotireStanga(&((*radacina)->st));

			rotireDreapta(radacina);
		}
		else if (gradEchilibru == -2) {

			if (calculGradEchilibru((*radacina)->dr) == 1)
				rotireDreapta(&((*radacina)->dr));

			rotireStanga(radacina);
		}
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->dr = NULL;
		nou->st = NULL;
		nou->info = c;
		(*radacina) = nou;
	}
}

Nod* citireArbore(const char* fisier) {
	Nod* arbore = NULL;
	FILE* f = fopen(fisier, "r");
	while (!feof(f)) {
		Comanda c = citireComanda(f);
		inserare(&arbore,c);
	}
	fclose(f);
	return arbore;
}

void afisareInordine(Nod* arbore) {
	if (arbore) {
		afisareInordine(arbore->st);
		afisare(arbore->info);
		afisareInordine(arbore->dr);
	}
}

void dezalocare(Nod** arbore) {

	if (*arbore) {
		dezalocare(&((*arbore)->st));
		dezalocare(&((*arbore)->dr));
		free((*arbore)->info.numeClient);
		free(*arbore);
		*arbore = NULL;
	}
}

float calculeazaSumaTotala(Nod* arbore) {
	if (arbore) {
		return arbore->info.suma + calculeazaSumaTotala(arbore->st) + calculeazaSumaTotala(arbore->dr);
	}
	else
		return 0;
}

Comanda cautaComandaNrProduse(Nod* radacina, int nr) {
	Comanda c;
	c.nrProduse = -100;
	if (radacina) {
		if (nr < radacina->info.nrProduse)
			return cautaComandaNrProduse(radacina->st, nr);
		else if (nr > radacina->info.nrProduse)
			return cautaComandaNrProduse(radacina->dr, nr);
		else if (nr == radacina->info.nrProduse)
		{
			c.cod = radacina->info.cod;
			c.nrProduse = radacina->info.nrProduse;
			c.suma = radacina->info.suma;
			c.numeClient = malloc(strlen(radacina->info.numeClient) + 1);
			strcpy_s(c.numeClient, strlen(radacina->info.numeClient) + 1, radacina->info.numeClient);
		}
	}
	return c;
}
int main()
{
	Nod* arbore = citireArbore("comenzi.txt");
	afisareInordine(arbore);
	float suma = calculeazaSumaTotala(arbore);
	printf("\nSuma este: %.2f", suma);
	Comanda c = cautaComandaNrProduse(arbore, 4);
	afisare(c);

	dezalocare(&arbore);

	return 0;
}