/*
Simulazione d'esame (chatgpt) - Casa, Cosenza dalle 15:45 alle 16:00

Gestione Biblioteca

typedef struct {
    char titolo[40];
    char autore[30];
    int annoPubblicazione;
    int copieDisponibili;
} Libro;

typedef struct {
    Libro libri[7];
    int prestiti[15][3]; // ogni riga: [indiceLibro, giorniPrestito, codiceUtente]
} Biblioteca;

Funzioni da implementare: 
Funzione 1:
int* numeroPrestiti(Biblioteca b)
Restituisce un array dinamico di 7 interi in cui l’i-esimo elemento indica quante volte è stato prestato il libro con indice i.
Funzione 2:
int giorniTotaliPrestito(Biblioteca b, int codiceUtente)
Restituisce il numero totale di giorni di prestito accumulati da un dato utente (somma di tutti i giorniPrestito per quel codiceUtente).
Funzione 3:
char* autoreTop(Biblioteca b)
Restituisce il nome dell’autore i cui libri sono stati prestati il maggior numero di volte (considera il totale dei prestiti su tutti i suoi libri). Se più autori hanno lo stesso massimo, puoi restituire uno qualsiasi.
Funzione 4:
int libriMaiPrestati(Biblioteca b)
Restituisce il numero di libri che non sono mai stati prestati.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titolo[40];
    char autore[30];
    int annoPubblicazione;
    int copieDisponibili;
} Libro;

typedef struct {
    Libro libri[7];
    int prestiti[15][3]; // ogni riga: [indiceLibro, giorniPrestito, codiceUtente]
} Biblioteca;

/*
Funzione 1: int* numeroPrestiti(Biblioteca b)
Restituisce un array dinamico di 7 interi in cui l’i-esimo elemento indica quante volte è stato prestato il libro con indice i.
*/
int* numeroPrestiti(Biblioteca b){
    int* res = (int*) calloc (7, sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < 15; i++){
        int idx = b.prestiti[i][0];
        res[idx] += 1;
    }
    return res;
}

/*
Funzione 2: int giorniTotaliPrestito(Biblioteca b, int codiceUtente)
Restituisce il numero totale di giorni di prestito accumulati da un dato utente (somma di tutti i giorniPrestito per quel codiceUtente).
*/
int giorniTotaliPrestito(Biblioteca b, int codiceUtente){
    int somma = 0;
    for(int i = 0; i < 15; i++){
        int cod_ut = b.prestiti[i][2];
        int giorniPrestito = b.prestiti[i][1];
        if(cod_ut == codiceUtente){
            somma += giorniPrestito;
        }
    }
    return somma;
}

/*
Funzione 3: char* autoreTop(Biblioteca b)
Restituisce il nome dell’autore i cui libri sono stati prestati il maggior numero di volte 
(considera il totale dei prestiti su tutti i suoi libri). Se più autori hanno lo stesso massimo, puoi restituire uno qualsiasi.
*/
char* autoreTop(Biblioteca b){
    int* prestiti = (int*) calloc (7, sizeof(int));
    if(prestiti == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < 12; i++){
        int idx = b.prestiti[i][0];
        prestiti[idx] += 1;
    }
    int max_idx = 0;
    for(int i = 1; i < 7; i++){
        if(prestiti[i] > prestiti[max_idx]){
            max_idx = i;
        }
    }
    free(prestiti);
    return b.libri[max_idx].autore;
}

/*
Funzione 4: int libriMaiPrestati(Biblioteca b)
Restituisce il numero di libri che non sono mai stati prestati.
*/
int libriMaiPrestati(Biblioteca b){
    int count = 0;
    for(int i = 0; i < 7; i++){
        int trovato = 0;
        for(int j = 0; j < 15; j++){
            if(i == b.prestiti[j][0]){
                trovato = 1;
                break;
            }
        }
        if(!trovato){
            count++;
        }
    }
    return count;
}
