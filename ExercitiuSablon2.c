//#include <stdio.h>
//#include <malloc.h>
//#include<string.h>
//
//struct Prajitura{
//	int id;
//	char* denumire;
//	float gramaj;
//	char alergen;
//};
//
//struct Prajitura initializare(int idNou, const char* denumireNoua, float gramajNou, char alergenNou)
//{
//	struct Prajitura p;
//	p.id = idNou;
//	p.denumire = malloc(sizeof(char) * (strlen(denumireNoua) + 1));
//	strcpy_s(p.denumire, strlen(denumireNoua) + 1, denumireNoua);
//	p.gramaj = gramajNou;
//	p.alergen = alergenNou;
//
//	return p;
//}
//
//void afisare(struct Prajitura p)
//{
//	printf(" Id: %d\n Denumire: %s\n Gramaj: %.2f\n Alergen: %c\n\n",p.id,p.denumire,p.gramaj,p.alergen);
//}
//
//
//void afisareVector(struct Prajitura* vector, int nrElemente) 
//{
//	for (int i = 0; i < nrElemente; i++)
//		afisare(vector[i]);
//}
//
//void dezalocare(struct Prajitura** vector, int* nrElemente)
//{
//	for (int i = 0; i < (*nrElemente); i++)
//		free((*vector)[i].denumire);
//	free(*vector);
//	(*vector) = NULL;
//	(*nrElemente) = 0;
//}
//
//void copiazaPrajituriGramajMare(struct Prajitura* vector, int nrElemente, float prag, struct Prajitura** vectorNou, int* nrElementeNou)
//{
//	(*nrElementeNou) = 0;
//	for (int i = 0; i < nrElemente; i++)
//	{
//		if (vector[i].gramaj > prag)
//			(*nrElementeNou)++;
//	}
//
//	(*vectorNou) = malloc(sizeof(struct Prajitura) * (*nrElementeNou));
//	int k = 0;
//	for (int i = 0; i < nrElemente; i++)
//	{
//		if (vector[i].gramaj > prag)
//		{
//			(*vectorNou)[k] = vector[i];
//			(*vectorNou)[k].denumire = malloc(sizeof(char) * (strlen(vector[i].denumire) + 1));
//			strcpy_s((*vectorNou)[k].denumire, strlen(vector[i].denumire) + 1, vector[i].denumire);
//			k++;
//		}
//	}
//}
//
//struct Prajitura getPrimaPrajituraDupaDenumire(struct Prajitura* vector, int nrElemente, const char* denumireConditie)
//{
//	struct Prajitura p;
//	p.id = 0;
//	p.denumire = NULL;
//	p.gramaj = 0.0;
//	p.alergen = 'l';
//
//	int ok = 0;
//	for (int i = 0; i < nrElemente; i++)
//	{
//		if (strcmp(vector[i].denumire, denumireConditie) == 0)
//		{
//			p = vector[i];
//			p.denumire = malloc(sizeof(char) * (strlen(denumireConditie) + 1));
//			strcpy_s(p.denumire, strlen(denumireConditie) + 1, denumireConditie);
//			ok = 1;
//		}
//
//		if (ok == 1)
//			break;
//	}
//	return p;
//
//}
//
//int main(){
//
//	struct Prajitura p;
//	p = initializare(1, "Amandina", 88.70, 'l');
//	afisare(p);
//	printf("\n");
//
//	struct Prajitura* vectorPrajituri;
//	int nrPrajituri = 4;
//	vectorPrajituri = malloc(sizeof(struct Prajitura) * nrPrajituri);
//	vectorPrajituri[0] = initializare(2, "Savarina", 112.20, 's');
//	vectorPrajituri[1] = initializare(3, "Dobos", 105.60, 'n');
//	vectorPrajituri[2] = initializare(4, "Tiramisu", 101.50, 'l');
//	vectorPrajituri[3] = initializare(5, "Dobos", 96.80, 's');
//	afisareVector(vectorPrajituri, nrPrajituri);
//	printf("\n");
//
//	struct Prajitura* vectorPrajituriCopiate = NULL;
//	int nrElementeCopiate = 3;
//	copiazaPrajituriGramajMare(vectorPrajituri, nrPrajituri, 100.50, &vectorPrajituriCopiate, &nrElementeCopiate);
//	printf("\nPrajituri cu gramaj mare copiate:\n");
//	afisareVector(vectorPrajituriCopiate, nrElementeCopiate);
//	
//	printf("\nPrima prajitura care are denumirea precum cea specificata este:\n");
//	struct Prajitura pConditie;
//	pConditie = getPrimaPrajituraDupaDenumire(vectorPrajituri, nrPrajituri, "Dobos");
//	afisare(pConditie);
//	
//	dezalocare(&vectorPrajituri, &nrPrajituri);
//	dezalocare(&vectorPrajituriCopiate, &nrElementeCopiate);
//	return 0;
//}