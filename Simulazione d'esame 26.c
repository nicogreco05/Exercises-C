/*
Simulazione d'esame (chatgpt) - Casa, San Gregorio, 07/07/25

Si vuole gestire un archivio di film disponibili in streaming

typedef struct {
    char titolo[30];
    char genere[15];
    int durata;    // in minuti
    float rating;  // da 0 a 10
} Film;

typedef struct {
    Film catalogo[8];
    char generiRichiesti[5][15];
} Archivio;

Funzioni richieste:
1.	bool tuttiGeneriDisponibili(Archivio a)
Restituisce true se per ogni genere richiesto esiste almeno un film nel catalogo.

2.	float tempoTotaleVisione(Archivio a)
Restituisce la durata totale (in minuti) di tutti i film in catalogo.

3.	char* filmTopGenere(Archivio a, char genere[])
Restituisce il titolo del film col rating più alto nel genere specificato.

4.	char* generePreferito(Archivio a)
Restituisce il genere con il rating medio più alto.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char titolo[30];
    char genere[15];
    int durata;    // in minuti
    float rating;  // da 0 a 10
} Film;

typedef struct {
    Film catalogo[8];
    char generiRichiesti[5][15];
} Archivio;

/*
Funzione 1: bool tuttiGeneriDisponibili(Archivio a)
Restituisce true se per ogni genere richiesto esiste almeno un film nel catalogo.
*/
bool tuttiGeneriDisponibili(Archivio a){
    for(int i = 0; i < 5; i++){
        bool tutti_disp = false;
        for(int j = 0; j < 8; j++){
            if(strcmp(a.generiRichiesti[i], a.catalogo[j].genere) == 0){
                tutti_disp = true;
                break;
            }
        }
        if(!tutti_disp){
            return false;
        }
    }
    return true;
}

/*
Funzione 2: float tempoTotaleVisione(Archivio a)
Restituisce la durata totale (in minuti) di tutti i film in catalogo.
*/
float tempoTotaleVisione(Archivio a){
    float totale = 0.0;
    for(int i = 0; i < 8; i++){
        float minuti = a.catalogo[i].durata;
        totale += minuti;
    }
    return totale;
}

/*
Funzione 3: char* filmTopGenere(Archivio a, char genere[])
Restituisce il titolo del film col rating più alto nel genere specificato.
*/
char* filmTopGenere(Archivio a, char genere[]){
    int* ratings = (int*) malloc (8 * sizeof(int));
    if(ratings == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < 8; i++){
        if(strcmp(genere, a.catalogo[i].genere) == 0){
            ratings[i] = a.catalogo[i].rating;
        }
        else{
            ratings[i] = -1;
        }
    }
    int max_idx = 0;
    for(int i = 1; i < 8; i++){
        if(ratings[i] > ratings[max_idx]){
            max_idx = i;
        }
    }
    free(ratings);
    return a.catalogo[max_idx].titolo;
}

/*
Funzione 4: char* generePreferito(Archivio a)
Restituisce il genere con il rating medio più alto.
*/
char* genereCostoso(Archivio a) {
    static char genereTop[20]; // static per poterlo restituire
    char generiUnici[8][20];
    int sommaRating[8] = {0};
    int conteggio[8] = {0};
    int n_generi = 0;

    for (int i = 0; i < 8; i++) {
        int trovato = -1;
        for (int j = 0; j < n_generi; j++) {
            if (strcmp(a.catalogo[i].genere, generiUnici[j]) == 0) {
                trovato = j;
                break;
            }
        }

        if (trovato == -1) {
            strcpy(generiUnici[n_generi], a.catalogo[i].genere);
            sommaRating[n_generi] = a.catalogo[i].rating;
            conteggio[n_generi] = 1;
            n_generi++;
        } else {
            sommaRating[trovato] += a.catalogo[i].rating;
            conteggio[trovato]++;
        }
    }

    float maxMedia = -1;
    int indiceMax = -1;
    for (int i = 0; i < n_generi; i++) {
        float media = (float)sommaRating[i] / conteggio[i];
        if (media > maxMedia) {
            maxMedia = media;
            indiceMax = i;
        }
    }

    strcpy(genereTop, generiUnici[indiceMax]);
    return genereTop;
}