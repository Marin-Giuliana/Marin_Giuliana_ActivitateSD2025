//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//
//typedef struct StructuraMasina Masina;
//
//void afisareMasina(Masina masina)
//{
//	printf("Masina cu id %d are %d usi, pretul %.2f, modelul %s, este condusa de %s, are seria %c.\n",
//		masina.id,masina.nrUsi,masina.pret, masina.model,masina.numeSofer,masina.serie);
//}
//
//void afisareVectorMasini(Masina* masini, int nrMasini)
//{
//	for (int i = 0; i < nrMasini; i++)
//	{
//		afisareMasina(masini[i]);
//	}
//}
//
//void dezalocareVectorMasini(Masina** vector, int* nrMasini)
//{
//	for (int i = 0; i < (*nrMasini); i++)
//	{
//		free((*vector)[i].model);
//		free((*vector)[i].numeSofer);
//	}
//	free(*vector);
//	(*vector) = NULL;
//	(*nrMasini) = 0;
//}
//
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua)
//{
//
//        Masina* vectorNou = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
//   
//        for (int i = 0; i < (*nrMasini); i++) 
//		{
//            vectorNou[i] = (*masini)[i];
//        }
//
//        int i = (*nrMasini);
//        vectorNou[i] = masinaNoua;
//
//        vectorNou[i].model = malloc(sizeof(char) * (strlen(masinaNoua.model) + 1));
//        strcpy_s(vectorNou[i].model, strlen(masinaNoua.model) + 1, masinaNoua.model);
//
//        vectorNou[i].numeSofer = malloc(sizeof(char) * (strlen(masinaNoua.numeSofer) + 1));
//        strcpy_s(vectorNou[i].numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
//
//        free(*masini);
//		(*nrMasini)++;
//        (*masini) = vectorNou;
//}
//
//Masina citireMasinaFisier(FILE* file) {
//
//	Masina masina;
//	char buffer[100];
//	char delimitatori = ",\n";
//
//	while (fgets(buffer, sizeof(buffer), file) != NULL)
//	{
//		char* token = strtok(buffer, delimitatori);
//		masina.id = atoi(token);
//
//		token = strtok(NULL, delimitatori);
//		masina.nrUsi = atoi(token); 
//
//		token = strtok(NULL, delimitatori);
//		masina.pret = atof(token);
//
//		token = strtok(NULL, delimitatori);
//		masina.model = malloc(strlen(token) + 1);
//		strcpy_s(masina.model, strlen(token) + 1, token);
//
//		token = strtok(NULL, delimitatori);
//		masina.numeSofer = malloc(strlen(token) + 1);
//		strcpy_s(masina.numeSofer, strlen(token) + 1, token);
//
//		token = strtok(NULL, delimitatori);
//		masina.serie = token[0];
//	}
//
//	return masina;
//}
//
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//	
//	Masina* vectorMasini = NULL;
//	(*nrMasiniCitite) = 0;
//
//	FILE* file = fopen(numeFisier, "r");
//	if (file != NULL)
//	{
//		while (!feof(file))
//		{
//			Masina masina = citireMasinaFisier(file);
//			adaugaMasinaInVector(&vectorMasini, &nrMasiniCitite, masina);
//		}
//
//		fclose(file);
//	}
//	else
//	{
//		printf("Nu am putut deschide fisierul %s!\n", numeFisier);
//	}
//
//	return vectorMasini;
//}
//int main()
//{
//
//		Masina* vectorMasini = NULL;
//		int nrMasini = 0;
//
//		vectorMasini = citireVectorMasiniFisier("DateExercitiuSablon3.txt", &nrMasini);
//
//		printf("Masinile citite din fisier:\n");
//		afisareVectorMasini(vectorMasini, nrMasini);
//
//		Masina masinaNoua;
//		masinaNoua.id = 6;
//		masinaNoua.nrUsi = 3;
//		masinaNoua.pret = 7000.5;
//		masinaNoua.model = malloc(strlen("Tesla_Model3") + 1);
//		strcpy_s(masinaNoua.model, strlen("Tesla_Model3") + 1, "Tesla_Model3");
//		masinaNoua.numeSofer = malloc(strlen("Elon_Musk") + 1);
//		strcpy_s(masinaNoua.numeSofer, strlen("Elon_Musk") + 1, "Elon_Musk");
//		masinaNoua.serie = 'F';
//
//		adaugaMasinaInVector(&vectorMasini, &nrMasini, masinaNoua);
//
//		printf("\nDupa adaugarea unei masini noi:\n");
//		afisareVectorMasini(vectorMasini, nrMasini);
//
//		dezalocareVectorMasini(&vectorMasini, &nrMasini);
//
//		if (vectorMasini == NULL && nrMasini == 0) {
//			printf("\nVectorul de masini a fost dezalocat cu succes!\n");
//		}
//
//		return 0;
//
//}
//
//
