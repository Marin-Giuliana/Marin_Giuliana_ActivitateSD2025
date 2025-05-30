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
//typedef struct StructuraMasina Masina;
//typedef struct Heap Heap;
//
//struct Heap {
//	int lungime;
//	Masina* vector;
//	int nrElemente;
//};
//
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
//Heap initializareHeap(int lungime) {
//	Heap h;
//	h.lungime = lungime;
//	h.nrElemente = 0;
//	h.vector = (Masina*)malloc(sizeof(Masina) * lungime);
//	return h;
//}
//
//void filtreazaHeap(Heap heap, int pozitieNod) {
//	
//	int st = 2 * pozitieNod + 1;
//	int dr = 2 * pozitieNod + 2;
//	int maxim = pozitieNod;
//	if (st < heap.nrElemente && heap.vector[st].id > heap.vector[maxim].id)
//		maxim = st;
//	if (dr < heap.nrElemente && heap.vector[dr].id > heap.vector[maxim].id)
//		maxim = dr;
//	if (maxim != pozitieNod) {
//		Masina aux = heap.vector[maxim];
//		heap.vector[maxim] = heap.vector[pozitieNod];
//		heap.vector[pozitieNod] = aux;
//	}
//	if (maxim <= (heap.nrElemente - 2) / 2) { //ultimul parinte, daca pozitia fiului din stanga este in nr de elemente
//		filtreazaHeap(heap, maxim);
//	}
//}
//
//Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Heap h = initializareHeap(10);
//	while (!feof(f)) {
//		h.vector[h.nrElemente++] = citireMasinaDinFisier(f);
//	}
//	fclose(f);
//
//	for (int i = (h.nrElemente-2)/2; i >= 0; i--) { //de la  poz ultimului parinte 
//		filtreazaHeap(h,i);
//	}
//	return h;
//}
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrElemente; i++) {
//		afisareMasina(heap.vector[i]);
//	}
//}
//
//void afiseazaHeapAscuns(Heap heap) {
//	
//	for (int i = heap.nrElemente; i <= heap.lungime; i++)
//		afisareMasina(heap.vector[i]);
//
//}
//
//Masina extrageMasina(Heap* heap) {
//	//extrage si returneaza masina de pe prima pozitie
//	//elementul extras nu il stergem...doar il ascundem
//
//	if (heap->nrElemente > 0) {
//		Masina aux = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrElemente - 1];
//		heap->vector[heap->nrElemente - 1] = aux;
//		heap->nrElemente--;
//
//		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--)
//		{
//			filtreazaHeap(*heap, i);
//		}
//		return aux;
//	}
//
//}
//
//
//void dezalocareHeap(Heap* heap) {
//	//sterge toate elementele din Heap
//
//	for (int i = 0; i < heap->lungime; i++) {
//		free(heap->vector[i].model);
//		free(heap->vector[i].numeSofer);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrElemente = 0;
//}
//
//int main() {
//
//	Heap heap = citireHeapDeMasiniDinFisier("masini.txt");
//	afisareHeap(heap);
//
//	printf("Masini extrase:\n");
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//
//	printf("Heap-ul ascuns:\n");
//	afiseazaHeapAscuns(heap);
//
//	dezalocareHeap(&heap);
//
//	return 0;
//}
