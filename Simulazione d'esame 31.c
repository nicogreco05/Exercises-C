/*
Simulazione d'esame (chatgpt) - Casa, San Gregorio 09/07/25

Si vuole realizzare un’applicazione per la gestione di una libreria musicale digitale.
Le informazioni sono memorizzate utilizzando le seguenti struct:

typedef struct {
    char titolo[30];
    char artista[30];
    int durata;       // in secondi
    int anno;
    int popolarita;   // valore da 1 (bassa) a 10 (alta)
} Brano;

typedef struct {
    Brano catalogo[10];     // fino a 10 brani in catalogo
    char playlist[5][30];   // nomi dei brani richiesti per una playlist
} Libreria;

Ogni Brano contiene informazioni su un brano musicale.
La playlist contiene i titoli dei brani desiderati da un utente.

Si scrivano le seguenti funzioni:
1. bool braniDisponibili(Libreria lib)
Restituisce true se tutti i brani elencati nella playlist sono presenti nel catalogo (basandosi sul titolo), altrimenti false.

2. int durataTotalePlaylist(Libreria lib)
Restituisce la durata totale, in secondi, dei brani della playlist che sono effettivamente presenti nel catalogo.

3. char* artistaPopolare(Libreria lib)
Restituisce il nome dell’artista con la media di popolarità più alta, calcolata su tutti i brani del catalogo.
In caso di pari merito, restituisce uno qualsiasi degli artisti a pari media.

4. char* branoCortoPreferito(Libreria lib, int maxDurata)
Restituisce il titolo del brano con la massima popolarità tra quelli che hanno durata non superiore a maxDurata.
Se più brani soddisfano la condizione, ne restituisce uno qualsiasi.
Se nessun brano soddisfa, restituisce "Nessuno".
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char titolo[30];
    char artista[30];
    int durata;       // in secondi
    int anno;
    int popolarita;   // valore da 1 (bassa) a 10 (alta)
} Brano;

typedef struct {
    Brano catalogo[10];     // fino a 10 brani in catalogo
    char playlist[5][30];   // nomi dei brani richiesti per una playlist
} Libreria;

/*
Funzione 1: bool braniDisponibili(Libreria lib)
Restituisce true se tutti i brani elencati nella playlist sono presenti nel catalogo (basandosi sul titolo), altrimenti false.
*/
bool braniDisponibili(Libreria lib){
    for(int i = 0; i < 5; i++){
        bool presenti = false;
        for(int j = 0; j < 10; j++){
            if(strcmp(lib.playlist[i], lib.catalogo[j].titolo) == 0){
                presenti = true;
            }
        }
        if(!presenti){
            return false;
        }
    }
    return true;
}

/*
Funzione 2: int durataTotalePlaylist(Libreria lib)
Restituisce la durata totale, in secondi, dei brani della playlist che sono effettivamente presenti nel catalogo.
*/
int durataTotalePlaylist(Libreria lib){
    int totale = 0;
    for(int i = 0; i < 5 ; i++){
        for(int j = 0; j < 10; j++){
            if(strcmp(lib.playlist[i], lib.catalogo[j].titolo) == 0){
                totale += lib.catalogo[j].durata;
            }
        }
    }
    return totale;
}

/*
Funzione 3: char* artistaPopolare(Libreria lib)
Restituisce il nome dell’artista con la media di popolarità più alta, calcolata su tutti i brani del catalogo.
In caso di pari merito, restituisce uno qualsiasi degli artisti a pari media.
*/
char* artistaPopolare(Libreria lib){
    static char artista[20];
    int max_media = -1;
    for(int i = 0; i < 10; i++){
        char* attuale = lib.catalogo[i].artista;
        int somma = 0;
        int count = 0;
        for(int j = 0; j < 10; j++){
            if(strcmp(attuale, lib.catalogo[j].artista) == 0){
                somma += lib.catalogo[j].popolarita;
                count++;
            }
        }
        if(count > 0){
            int media = somma / count;
            if(media > max_media){
                max_media = media;
                strcpy(artista, attuale);
            }
        }
    }
    return artista;
}

/*
Funzione 4: char* branoCortoPreferito(Libreria lib, int maxDurata)
Restituisce il titolo del brano con la massima popolarità tra quelli che hanno durata non superiore a maxDurata.
Se più brani soddisfano la condizione, ne restituisce uno qualsiasi.
Se nessun brano soddisfa, restituisce "Nessuno".
*/
char* branoCortoPreferito(Libreria lib, int maxDurata){
    static char brano[20];
    int* pop = (int*) malloc (10 * sizeof(int));
    for(int i = 0; i < 10; i++){
        if(lib.catalogo[i].durata <= maxDurata){
            pop[i] = lib.catalogo[i].popolarita;
        }
        else{
            pop[i] = -1;
        }
    }
    int max_idx = -1;
    for(int i = 0; i < 10; i++){
        if(pop[i] != -1){
            max_idx = i;
            break;
        }
    }
    if(max_idx == -1){
        strcpy(brano, "Nessuno");
        return brano;
    }
    for(int i = max_idx + 1; i < 10; i++){
        if(pop[i] != -1 && pop[i] > pop[max_idx]){
            max_idx = i;
        }
    }
    free(pop);
    strcpy(brano, lib.catalogo[max_idx].titolo);
    return brano;
}