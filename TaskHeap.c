#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* nume;
    int grad_urgenta;
} Pacient;

typedef struct {
    int capacitate;
    int nr_pacienti;
    Pacient* pacienti;
} Heap;

void initializareHeap(Heap* h, int capacitate) {
   
    if (h->pacienti != NULL) 
    {
        h->capacitate = capacitate;
        h->nr_pacienti = 0;
        h->pacienti = (Pacient*)malloc(sizeof(Pacient) * capacitate);
    }
}

void interschimba(Pacient* a, Pacient* b) {
    Pacient aux = *a;
    *a = *b;
    *b = aux;
}

void urca(Heap* h, int pozitie) {
    if (pozitie == 0) return;
    int parinte = (pozitie - 1) / 2;
    if (h->pacienti[parinte].grad_urgenta < h->pacienti[pozitie].grad_urgenta) {
        interschimba(&h->pacienti[parinte], &h->pacienti[pozitie]);
        urca(h, parinte);
    }
}

void adaugaPacient(Heap* h, char nume[], int grad_urgenta) {
    if (h->nr_pacienti == h->capacitate) {
       
        if (h->pacienti != NULL) {

            h->capacitate *= 2;
            h->pacienti = (Pacient*)realloc(h->pacienti, sizeof(Pacient) * h->capacitate);
        }
    }
    h->pacienti[h->nr_pacienti].nume = (char*)malloc(strlen(nume) + 1);
    if (h->pacienti[h->nr_pacienti].nume != NULL) {
        strcpy(h->pacienti[h->nr_pacienti].nume, nume);
        h->pacienti[h->nr_pacienti].grad_urgenta = grad_urgenta;
        urca(h, h->nr_pacienti);
        h->nr_pacienti++;
    }
}

void coboara(Heap* h, int pozitie) {
    int stanga = 2 * pozitie + 1;
    int dreapta = 2 * pozitie + 2;
    int maxim = pozitie;

    if (stanga < h->nr_pacienti && h->pacienti[stanga].grad_urgenta > h->pacienti[maxim].grad_urgenta) {
        maxim = stanga;
    }
    if (dreapta < h->nr_pacienti && h->pacienti[dreapta].grad_urgenta > h->pacienti[maxim].grad_urgenta) {
        maxim = dreapta;
    }
    if (maxim != pozitie) {
        interschimba(&h->pacienti[pozitie], &h->pacienti[maxim]);
        coboara(h, maxim);
    }
}

Pacient extragePacient(Heap* h) {
    Pacient p;
    p.nume = NULL;
    p.grad_urgenta = -1;

    if (h->nr_pacienti > 0) {
        p = h->pacienti[0];
        h->pacienti[0] = h->pacienti[h->nr_pacienti - 1];
        h->nr_pacienti--;
        coboara(h, 0);
    }
    else {
        printf("Nu mai sunt pacienti.\n");
    }

    return p;
}

void afiseazaHeap(Heap* h) {
    printf("Pacientii in asteptare:\n");
    for (int i = 0; i < h->nr_pacienti; i++) {
        printf("%s - Grad urgenta: %d\n", h->pacienti[i].nume, h->pacienti[i].grad_urgenta);
    }
}

void dezalocareHeap(Heap* h) {
    for (int i = 0; i < h->nr_pacienti; i++) {
        free(h->pacienti[i].nume);
    }
    free(h->pacienti);
    h->pacienti = NULL;
    h->nr_pacienti = 0;
    h->capacitate = 0;
}

int main() {
    Heap heap;
    initializareHeap(&heap, 4);

    adaugaPacient(&heap, "Ion", 5);
    adaugaPacient(&heap, "Maria", 9);
    adaugaPacient(&heap, "Andrei", 3);
    adaugaPacient(&heap, "Elena", 7);

    afiseazaHeap(&heap);

    printf("\nPreluare pacienti:\n");
    while (heap.nr_pacienti > 0) {
        Pacient p = extragePacient(&heap);
        if (p.nume != NULL) {
            printf("A fost preluat pacientul %s cu gradul de urgenta %d.\n", p.nume, p.grad_urgenta);
            free(p.nume);
        }
        dezalocareHeap(&heap);

        return 0;
    }
}
