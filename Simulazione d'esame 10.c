/*
Simulazione d'esame (chatgpt) - Casa, San Gregorio, 05/06/25 dalle 9:30 alle 10:30

Esercizio 1 - Gestione di una libreria

typedef struct {
    int codice;
    char titolo[30];
    char genere[20];
    float prezzo;
} Libro;

typedef struct {
    Libro catalogo[MAX_LIBRI];
    int vendite[MAX_CLIENTI][2]; // [][0] = codice libro, [][1] = copie acquistate
} Libreria;

Scrivere le seguenti funzioni: 
1.int* libriPopolari(Libreria l, char genere[], int soglia, int* count);
Restituisce un array con i codici dei libri del genere specificato che sono stati venduti in più di soglia copie.
Il valore puntato da count sarà il numero di codici nell’array.

2.char* genereTop(Libreria l);
Restituisce il genere che ha generato il maggiore incasso totale.
L’incasso di un libro è: prezzo * copie vendute.

3.int libroMaiVenduto(Libreria l);
Restituisce il codice del primo libro che non è mai stato venduto, oppure -1 se tutti sono stati venduti almeno una volta.
*/
#define MAX_LIBRI 5
#define MAX_CLIENTI 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codice;
    char titolo[30];
    char genere[20];
    float prezzo;
} Libro;

typedef struct {
    Libro catalogo[MAX_LIBRI];
    int vendite[MAX_CLIENTI][2]; // [][0] = codice libro, [][1] = copie acquistate
} Libreria;

/*
Funzione 1: int* libriPopolari(Libreria l, char genere[], int soglia, int* count);
Restituisce un array con i codici dei libri del genere specificato che sono stati venduti in più di soglia copie.
Il valore puntato da count sarà il numero di codici nell’array.
*/
int* libriPopolari(Libreria l, char genere[], int soglia, int *count){
    int cnt = 0;
    int tmp[MAX_LIBRI];
    for(int i = 0; i < MAX_LIBRI; i++){
        int copie_vendute = 0;
        for(int j = 0; j < MAX_CLIENTI; j++){
            if(l.catalogo[i].codice == l.vendite[j][0]){
                copie_vendute += l.vendite[j][i];
            }
        }
        if(copie_vendute > soglia){
            tmp[cnt++] = l.catalogo[i].codice;
        }
    }
    *count = cnt;
    int* res = (int*) malloc (cnt * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < cnt; i++){
        res[i] = tmp[i];
    }
    return res;
}

/*
Funzione 2: char* genereTop(Libreria l);
Restituisce il genere che ha generato il maggiore incasso totale.
L’incasso di un libro è: prezzo * copie vendute.
*/
int esisteGenere(char generi[][20], int n, char* target) {
    for(int i = 0; i < n; i++) {
        if(strcmp(generi[i], target) == 0) {
            return i; // Trovato, ritorna la posizione
        }
    }
    return -1; // Non trovato
}

char* genereTop(Libreria l){
    char generi[MAX_LIBRI][20];
    int totali_incassi[MAX_LIBRI] = {0};
    int numGeneri = 0;
    for(int i = 0; i < MAX_LIBRI; i++){
        char* genereCorrente = l.catalogo[i].genere;
        int index = esisteGenere(generi, numGeneri, genereCorrente);
        if(index == -1){
            strcpy(generi[numGeneri], genereCorrente);
            for(int j = 0; j < MAX_CLIENTI; j++){
                if(l.vendite[j][i] > 0){
                    totali_incassi[numGeneri] += l.catalogo[i].prezzo * l.vendite[j][i];
                }
            }
            numGeneri++;
        }
        else{
            for(int j = 0; j < MAX_CLIENTI; j++){
                if(l.vendite[j][i] > 0){
                    totali_incassi[index] += l.catalogo[i].prezzo * l.vendite[j][i];
                }
            }  
        }
    }
    int max_index = 0;
    for(int i = 0; i < numGeneri; i++){
        if(totali_incassi[i] > totali_incassi[max_index]){
            max_index = i;
        }
    }
    char* res = (char*) malloc (20 * sizeof(char));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    strcpy(res, generi[max_index]);
    return res;
}

/*
Funzione 3: int libroMaiVenduto(Libreria l);
Restituisce il codice del primo libro che non è mai stato venduto, oppure -1 se tutti sono stati venduti almeno una volta.
*/
int libroMaiVenduto(Libreria l){
    for(int i = 0; i < MAX_LIBRI; i++){
        int trovato = 0;
        for(int j = 0; j < MAX_CLIENTI; j++){
            if(l.vendite[j][i] > 0){
                trovato = 1;
                break;
            }
        }
        if(!trovato){
            return l.catalogo[i].codice;
        }
    }
    return -1;
}


/*
Esercizio 2 - Finestra su array

int* finestreSopraSoglia(int* A, int dim, int soglia, int* dimRes);

Restituisce un array con gli indici i tali che A[i] + A[i+1] + A[i+2] > soglia.
Imposta *dimRes con il numero di tali indici.
*/
int* finestreSopraSoglia(int* A, int dim, int soglia, int* dimRes){
    int count = 0;
    for(int i = 0; i < dim-2; i++){
        if((A[i] + A[i+1] + A[i+2]) > soglia){
            count++;
        }
    }
    *dimRes = count;
    int k = 0;
    int* res = (int*) malloc (count * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    } 
    for(int i = 0; i < dim-2; i++){
        if((A[i] + A[i+1] + A[i+2]) > soglia){
            res[k++] = i;
        }
    }
    return res;
}