//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct StructuraMasina {
//    int id;
//    int nrUsi;
//    float pret;
//    char* model;
//    char* numeSofer;
//    unsigned char serie;
//} Masina;
//
//typedef struct NodMasina {
//    Masina info;
//    struct NodMasina* next;
//} NodMasina;
//
//
//
//Masina citireMasinaDinFisier(FILE* file) {
//    char buffer[100];
//    char sep[3] = ",\n";
//    Masina m1 = { 0, 0, 0.0, NULL, NULL, 0 };
//
//    if (fgets(buffer, 100, file) == NULL) {
//        return m1;
//    }
//
//    char* aux = strtok(buffer, sep);
//    if (aux == NULL) return m1;
//    m1.id = atoi(aux);
//
//    aux = strtok(NULL, sep);
//    if (aux == NULL) return m1;
//    m1.nrUsi = atoi(aux);
//
//    aux = strtok(NULL, sep);
//    if (aux == NULL) return m1;
//    m1.pret = atof(aux);
//
//    aux = strtok(NULL, sep);
//    if (aux == NULL) return m1;
//    m1.model = malloc(strlen(aux) + 1);
//    if (m1.model != NULL) strcpy(m1.model, aux);
//
//    aux = strtok(NULL, sep);
//    if (aux == NULL) return m1;
//    m1.numeSofer = malloc(strlen(aux) + 1);
//    if (m1.numeSofer != NULL) strcpy(m1.numeSofer, aux);
//
//    aux = strtok(NULL, sep);
//    if (aux == NULL) return m1;
//    m1.serie = aux[0];
//
//    return m1;
//}
//
//void afisareMasina(Masina masina) {
//    printf("Id: %d\n", masina.id);
//    printf("Nr. usi: %d\n", masina.nrUsi);
//    printf("Pret: %.2f\n", masina.pret);
//    printf("Model: %s\n", masina.model);
//    printf("Nume sofer: %s\n", masina.numeSofer);
//    printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(NodMasina* cap) {
//    NodMasina* temp = cap;
//    while (temp != NULL) {
//        afisareMasina(temp->info);
//        temp = temp->next;
//    }
//}
//
//void adaugaMasinaInLista(NodMasina** cap, Masina masinaNoua) {
//    NodMasina* nou = (NodMasina*)malloc(sizeof(NodMasina));
//    if (!nou) {
//        printf("Eroare la alocarea nodului nou!\n");
//        return;
//    }
//
//    nou->info = masinaNoua;
//    nou->next = NULL;
//
//    if (*cap == NULL) {
//        *cap = nou;
//    }
//    else {
//        NodMasina* temp = *cap;
//        while (temp->next != NULL) {
//            temp = temp->next;
//        }
//        temp->next = nou;
//    }
//}
//
//void adaugaLaInceputInLista(NodMasina** cap, Masina masinaNoua) {
//    NodMasina* nou = (NodMasina*)malloc(sizeof(NodMasina));
//    if (!nou) {
//        printf("Eroare la alocarea nodului nou!\n");
//        return;
//    }
//
//    nou->info = masinaNoua;
//    nou->next = *cap;
//    *cap = nou;
//}
//
//NodMasina* citireListaMasiniDinFisier(const char* numeFisier) {
//    FILE* file = fopen(numeFisier, "r");
//    if (file == NULL) {
//        printf("Nu s-a putut deschide fisierul %s.\n", numeFisier);
//        return NULL;
//    }
//
//    NodMasina* cap = NULL;
//    Masina m = citireMasinaDinFisier(file);
//    while (m.model != NULL) {
//        adaugaMasinaInLista(&cap, m);
//        m = citireMasinaDinFisier(file);
//    }
//
//    fclose(file);
//    return cap;
//}
//
//void dezalocareListaMasini(NodMasina** cap) {
//    NodMasina* temp;
//    while (*cap != NULL) {
//        temp = *cap;
//        *cap = (*cap)->next;
//        free(temp->info.model);
//        free(temp->info.numeSofer);
//        free(temp);
//    }
//}
//
//float calculeazaPretMediu(NodMasina* cap) {
//    float suma = 0;
//    int k = 0;
//    NodMasina* temp = cap;
//
//    while (temp != NULL) {
//        suma += temp->info.pret;
//        k++;
//        temp = temp->next;
//    }
//
//    return (k > 0) ? suma / k : 0;
//}
//
//void stergeMasiniDinSeria(NodMasina** cap, char serieCautata) {
//    while (*cap != NULL && (*cap)->info.serie == serieCautata) {
//        NodMasina* temp = *cap;
//        *cap = (*cap)->next;
//        free(temp->info.model);
//        free(temp->info.numeSofer);
//        free(temp);
//    }
//
//    if (*cap == NULL) return;
//
//    NodMasina* nou = *cap;
//    while (nou->next != NULL) {
//        if (nou->next->info.serie == serieCautata) {
//            NodMasina* temp = nou->next;
//            nou->next = temp->next;
//            free(temp->info.model);
//            free(temp->info.numeSofer);
//            free(temp);
//        }
//        else {
//            nou = nou->next;
//        }
//    }
//}
//
//float calculeazaPretulMasinilorUnuiSofer(NodMasina* cap, const char* numeSofer) {
//    float suma = 0;
//    NodMasina* temp = cap;
//
//    while (temp != NULL) {
//        if (strcmp(temp->info.numeSofer, numeSofer) == 0) {
//            suma += temp->info.pret;
//        }
//        temp = temp->next;
//    }
//
//    return suma;
//}
//
//int main() {
//    NodMasina* listaMasini = citireListaMasiniDinFisier("masini.txt");
//
//    if (listaMasini == NULL) {
//        return 1;
//    }
//
//    printf("Lista initiala:\n");
//    afisareListaMasini(listaMasini);
//
//    float pretMediu = calculeazaPretMediu(listaMasini);
//    printf("Pretul mediu al masinilor: %.2f\n\n", pretMediu);
//
//    float sumaIonescu = calculeazaPretulMasinilorUnuiSofer(listaMasini, "Ionescu");
//    printf("Suma preturilor masinilor soferului Ionescu: %.2f\n\n", sumaIonescu);
//
//    stergeMasiniDinSeria(&listaMasini, 'A');
//    printf("Lista masinilor dupa stergerea masinilor cu seria A:\n");
//    afisareListaMasini(listaMasini);
//
//    Masina masinaNoua;
//    masinaNoua.id = 7;
//    masinaNoua.nrUsi = 4;
//    masinaNoua.pret = 7500;
//    masinaNoua.model = malloc(strlen("Dacia") + 1);
//    if (masinaNoua.model != NULL) strcpy(masinaNoua.model, "Dacia");
//    masinaNoua.numeSofer = malloc(strlen("Popescu") + 1);
//    if (masinaNoua.numeSofer != NULL) strcpy(masinaNoua.numeSofer, "Popescu");
//    masinaNoua.serie = 'D';
//
//    adaugaLaInceputInLista(&listaMasini, masinaNoua);
//
//    printf("Lista masinilor dupa adaugarea unei masini la inceput:\n");
//    afisareListaMasini(listaMasini);
//
//    dezalocareListaMasini(&listaMasini);
//
//    return 0;
//}
