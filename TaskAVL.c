#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
} Masina;

typedef struct Nod {
    Masina info;
    struct Nod* st;
    struct Nod* dr;
} Nod;

typedef struct {
    Masina* vector;
    int dim;
    int capacitate;
} VectorMasini;

typedef struct NodListSimpla {
    Masina info;
    struct NodListSimpla* next;
} NodListSimpla;

typedef struct NodListaDubla {
    Masina info;
    struct NodListaDubla* next;
    struct NodListaDubla* prev;
} NodListaDubla;

Masina creareMasina(int id, int nrUsi, float pret, const char* model, const char* sofer, unsigned char serie) {
    Masina m;
    m.id = id;
    m.nrUsi = nrUsi;
    m.pret = pret;
    m.model = malloc(strlen(model) + 1);
    strcpy(m.model, model);
    m.numeSofer = malloc(strlen(sofer) + 1);
    strcpy(m.numeSofer, sofer);
    m.serie = serie;
    return m;
}

void afisareMasina(Masina m) {
    printf("Id: %d\nNr usi: %d\nPret: %.2f\nModel: %s\nSofer: %s\nSerie: %c\n\n",
        m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
}

void dezalocareMasina(Masina* m) {
    free(m->model);
    free(m->numeSofer);
}

int inaltime(Nod* r) {
    if (!r) return 0;
    int h_st = inaltime(r->st);
    int h_dr = inaltime(r->dr);
    return 1 + (h_st > h_dr ? h_st : h_dr);
}

int gradEchilibru(Nod* r) {
    return inaltime(r->st) - inaltime(r->dr);
}

void rotireStanga(Nod** r) {
    Nod* nod = (*r)->dr;
    (*r)->dr = nod->st;
    nod->st = *r;
    *r = nod;
}

void rotireDreapta(Nod** r) {
    Nod* nod = (*r)->st;
    (*r)->st = nod->dr;
    nod->dr = *r;
    *r = nod;
}

void inserareAVL(Nod** r, Masina m) {
    if (!(*r)) {
        *r = malloc(sizeof(Nod));
        (*r)->info = creareMasina(m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
        (*r)->st = (*r)->dr = NULL;
    }
    else if (m.id < (*r)->info.id) {
        inserareAVL(&(*r)->st, m);
    }
    else {
        inserareAVL(&(*r)->dr, m);
    }

    int grad = gradEchilibru(*r);
    if (grad == 2) {
        if (gradEchilibru((*r)->st) < 0)
            rotireStanga(&(*r)->st);
        rotireDreapta(r);
    }
    else if (grad == -2) {
        if (gradEchilibru((*r)->dr) > 0)
            rotireDreapta(&(*r)->dr);
        rotireStanga(r);
    }
}

Masina cautaMasinaDupaID(Nod* rad, int id) {
    if (!rad) {
        Masina m;
        m.id = -1;
        return m;
    }
    if (id < rad->info.id)
        return cautaMasinaDupaID(rad->st, id);
    else if (id > rad->info.id)
        return cautaMasinaDupaID(rad->dr, id);
    else
        return rad->info;
}

void dezalocareArbore(Nod** r) {
    if (*r) {
        dezalocareArbore(&(*r)->st);
        dezalocareArbore(&(*r)->dr);
        dezalocareMasina(&(*r)->info);
        free(*r);
        *r = NULL;
    }
}

void initializareVector(VectorMasini* v, int capacitate) {
    v->vector = malloc(sizeof(Masina) * capacitate);
    v->dim = 0;
    v->capacitate = capacitate;
}

void adaugaInVector(VectorMasini* v, Masina m) {
    if (v->dim < v->capacitate) {
        v->vector[v->dim++] = creareMasina(m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
    }
}

void afisareVector(VectorMasini v) {
    for (int i = 0; i < v.dim; i++)
        afisareMasina(v.vector[i]);
}

void dezalocareVector(VectorMasini* v) {
    for (int i = 0; i < v->dim; i++)
        dezalocareMasina(&v->vector[i]);
    free(v->vector);
    v->vector = NULL;
}

void adaugaListaSimpla(NodListSimpla** cap, Masina m) {
    NodListSimpla* nou = malloc(sizeof(NodListSimpla));
    nou->info = creareMasina(m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
    nou->next = NULL;
    if (!*cap) 
        *cap = nou;
    else 
    {
        NodListSimpla* t = *cap;
        while (t->next)
            t = t->next;
        t->next = nou;
    }
}

void afisareListaSimpla(NodListSimpla* cap) {
    while (cap) {
        afisareMasina(cap->info);
        cap = cap->next;
    }
}

void dezalocareListaSimpla(NodListSimpla** cap) {
    while (*cap) {
        NodListSimpla* temp = *cap;
        *cap = temp->next;
        dezalocareMasina(&temp->info);
        free(temp);
    }
}

void adaugaListaDubla(NodListaDubla** cap, Masina m) {
    NodListaDubla* nou = malloc(sizeof(NodListaDubla));
    nou->info = creareMasina(m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
    nou->next = NULL;
    nou->prev = NULL;
    if (!*cap) 
        *cap = nou;
    else 
    {
        NodListaDubla* t = *cap;
        while (t->next) t = t->next;
        t->next = nou;
        nou->prev = t;
    }
}

void afisareListaDubla(NodListaDubla* cap) {
    while (cap) {
        afisareMasina(cap->info);
        cap = cap->next;
    }
}

void dezalocareListaDubla(NodListaDubla** cap) {
    while (*cap) {
        NodListaDubla* temp = *cap;
        *cap = temp->next;
        dezalocareMasina(&temp->info);
        free(temp);
    }
}

void salvareVectorPreordine(Nod* r, VectorMasini* v) {
    if (r) {
        adaugaInVector(v, r->info);
        salvareVectorPreordine(r->st, v);
        salvareVectorPreordine(r->dr, v);
    }
}

void salvareVectorInordine(Nod* r, VectorMasini* v) {
    if (r) {
        salvareVectorInordine(r->st, v);
        adaugaInVector(v, r->info);
        salvareVectorInordine(r->dr, v);
    }
}

void salvareVectorPostordine(Nod* r, VectorMasini* v) {
    if (r) {
        salvareVectorPostordine(r->st, v);
        salvareVectorPostordine(r->dr, v);
        adaugaInVector(v, r->info);
    }
}

void salvareListaSimplaPreordine(Nod* r, NodListSimpla** cap) {
    if (r) {
        adaugaListaSimpla(cap, r->info);
        salvareListaSimplaPreordine(r->st, cap);
        salvareListaSimplaPreordine(r->dr, cap);
    }
}

void salvareListaSimplaInordine(Nod* r, NodListSimpla** cap) {
    if (r) {
        salvareListaSimplaInordine(r->st, cap);
        adaugaListaSimpla(cap, r->info);
        salvareListaSimplaInordine(r->dr, cap);
    }
}

void salvareListaSimplaPostordine(Nod* r, NodListSimpla** cap) {
    if (r) {
        salvareListaSimplaPostordine(r->st, cap);
        salvareListaSimplaPostordine(r->dr, cap);
        adaugaListaSimpla(cap, r->info);
    }
}

void salvareListaDublaPreordine(Nod* r, NodListaDubla** cap) {
    if (r) {
        adaugaListaDubla(cap, r->info);
        salvareListaDublaPreordine(r->st, cap);
        salvareListaDublaPreordine(r->dr, cap);
    }
}

void salvareListaDublaInordine(Nod* r, NodListaDubla** cap) {
    if (r) {
        salvareListaDublaInordine(r->st, cap);
        adaugaListaDubla(cap, r->info);
        salvareListaDublaInordine(r->dr, cap);
    }
}

void salvareListaDublaPostordine(Nod* r, NodListaDubla** cap) {
    if (r) {
        salvareListaDublaPostordine(r->st, cap);
        salvareListaDublaPostordine(r->dr, cap);
        adaugaListaDubla(cap, r->info);
    }
}

int main() {
    Nod* radacina = NULL;
    Masina masini[] = {
        creareMasina(1,3,5000,"Astra","Ionescu",'A'),
        creareMasina(2,5,8000,"Mokka","Vasilescu",'S'),
        creareMasina(3,4,9000,"Passat","Gigel",'I'),
        creareMasina(4,5,4000,"Arkana","Gheorghe",'B'),
        creareMasina(5,3,11000,"Logan","Ionescu",'C'),
        creareMasina(6,5,4000,"Sportage","Badescu",'J'),
        creareMasina(7,3,4000,"Astra","Gigel",'A'),
        creareMasina(8,6,12000,"Mokka","Gheorghe",'U'),
        creareMasina(9,3,2700,"Passat","Ionescu",'I'),
        creareMasina(10,5,4000,"Mokka","Gigel",'B')
    };

    for (int i = 0; i < 10; i++) {
        inserareAVL(&radacina, masini[i]);
    }

    VectorMasini v;
    initializareVector(&v, 20);
    printf("\n---VECTOR (PREORDINE)---\n");
    salvareVectorPreordine(radacina, &v);
    afisareVector(v);
    dezalocareVector(&v);

    initializareVector(&v, 20);
    printf("\n---VECTOR (INORDINE)---\n");
    salvareVectorInordine(radacina, &v);
    afisareVector(v);
    dezalocareVector(&v);

    initializareVector(&v, 20);
    printf("\n---VECTOR (POSTORDINE)---\n");
    salvareVectorPostordine(radacina, &v);
    afisareVector(v);
    dezalocareVector(&v);

    NodListSimpla* listaSimpla = NULL;
    printf("\n---LISTA SIMPLA (PREORDINE)---\n");
    salvareListaSimplaPreordine(radacina, &listaSimpla);
    afisareListaSimpla(listaSimpla);
    dezalocareListaSimpla(&listaSimpla);

    printf("\n---LISTA SIMPLA (INORDINE)---\n");
    salvareListaSimplaInordine(radacina, &listaSimpla);
    afisareListaSimpla(listaSimpla);
    dezalocareListaSimpla(&listaSimpla);

    printf("\n---LISTA SIMPLA (POSTORDINE)---\n");
    salvareListaSimplaPostordine(radacina, &listaSimpla);
    afisareListaSimpla(listaSimpla);
    dezalocareListaSimpla(&listaSimpla);

    NodListaDubla* listaDubla = NULL;
    printf("\n---LISTA DUBLA (PREORDINE)---\n");
    salvareListaDublaPreordine(radacina, &listaDubla);
    afisareListaDubla(listaDubla);
    dezalocareListaDubla(&listaDubla);

    printf("\n---LISTA DUBLA (INORDINE)---\n");
    salvareListaDublaInordine(radacina, &listaDubla);
    afisareListaDubla(listaDubla);
    dezalocareListaDubla(&listaDubla);

    printf("\n---LISTA DUBLA (POSTORDINE)---\n");
    salvareListaDublaPostordine(radacina, &listaDubla);
    afisareListaDubla(listaDubla);
    dezalocareListaDubla(&listaDubla);

    printf("\n---CAUTARE MASINA CU ID = 5---\n");
    Masina gasita = cautaMasinaDupaID(radacina, 5);
    if (gasita.id != -1)
        afisareMasina(gasita);
    else
        printf("Masina nu a fost gasita.\n");


    for (int i = 0; i < 10; i++) {
        dezalocareMasina(&masini[i]);
    }

    dezalocareArbore(&radacina);
    return 0;
}
