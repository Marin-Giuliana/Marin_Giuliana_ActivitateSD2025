#include<stdio.h>
#include<malloc.h>

struct Masina {
	int id;
	char* model;
	float tonaj;
	char serie;
};
struct Masina initializare(int idNou, const char* modelNou, float tonajNou, char serieNou) {
	struct Masina m;
	m.id = idNou;
	m.model = malloc(sizeof(char) * (strlen(modelNou) + 1));
	strcpy_s(m.model, strlen(modelNou) + 1, modelNou);
	m.tonaj = tonajNou;
	m.serie = serieNou;

	return m;
}

void afisare(struct Masina m) {
	printf(" Id: %d\n Model: %s\n Tonaj: %.2f\n Serie: %c\n\n", m.id, m.model, m.tonaj, m.serie);
}

void afisareVector(struct Masina* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare
	for (int i = 0; i < nrElemente; i++)
		afisare(vector[i]);

}

struct Masina* copiazaPrimeleNMasini(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna, primele nrElementeCopiate
	struct Masina* vectorNou = malloc(sizeof(struct Masina) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = vector[i];
		vectorNou[i].model = malloc(sizeof(char) * (strlen(vector[i].model) + 1));
		strcpy_s(vectorNou[i].model, strlen(vector[i].model) + 1, vector[i].model);
	}

	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul

	for (int i = 0; i < (*nrElemente); i++)
		free((*vector)[i].model);

	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaMasiniUsoare(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie

	(*dimensiune) = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].tonaj < prag)
			(*dimensiune)++;

	}

	(*vectorNou) = malloc(sizeof(struct Masina) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].tonaj < prag)
		{
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].model = malloc(sizeof(char) * (strlen(vector[i].model) + 1));
			strcpy_s((*vectorNou)[k].model, strlen(vector[i].model) + 1, vector[i].model);
			k++;
		}

	}
}

struct Masina getPrimulElementConditionat(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Masina s;
	s.id = 1;

	return s;
}



int main() {

	struct Masina m;
	m = initializare(1, "BMW", 2.3, 'M');
	afisare(m);

	struct Masina* vectorMasini;
	int nrMasini = 3;
	vectorMasini = malloc(sizeof(struct Masina) * nrMasini);
	vectorMasini[0] = initializare(2, "Mercedes", 2.2, 'S');
	vectorMasini[1] = initializare(3, "Audi", 2.6, 'Q');
	vectorMasini[2] = initializare(3, "Dacia", 1.8, 'A');
	printf("\n\n");
	afisareVector(vectorMasini, nrMasini);
	printf("\n\n");
	struct Masina* vectorMasiniCopiate = NULL;
	int nrElementeCopiate = 2;

	vectorMasiniCopiate = copiazaPrimeleNMasini(vectorMasini, nrMasini, nrElementeCopiate);
	printf("Masini copiate:\n");
	afisareVector(vectorMasiniCopiate, nrElementeCopiate);

	dezalocare(&vectorMasiniCopiate, &nrElementeCopiate);

	printf("Masini usoare copiate: \n");
	copiazaMasiniUsoare(vectorMasini, nrMasini, 2.5, &vectorMasiniCopiate, &nrElementeCopiate);
	afisareVector(vectorMasiniCopiate, nrElementeCopiate);
	dezalocare(&vectorMasiniCopiate, &nrElementeCopiate);
	return 0;
}