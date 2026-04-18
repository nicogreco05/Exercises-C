/*
Simulazione d'esame (chatgpt) - Casa, San Gregorio, 26/05/25 dalle 12:00 alle 13:00
Dopo averlo fatto:
Funzione 1 --> ok
Funzione 2 --> ok 
Funzione 3 --> difficile ma non impossibile
Funzione 4 --> ok


Si vuole realizzare un’applicazione per la gestione delle prenotazioni di una biblioteca.


typedef struct {
    char titolo[30];
    char autore[30];
    int copieDisponibili;
} Libro;

typedef struct {
    Libro libri[5];
    int prenotazioni[8][2]; --> [codLibro, idUtente] e indica che l'utente idUtente ha prenotato il libro con codice codLibro
} PrenotazioniLibri;

Funzioni da implementare:
1.int copieTotaliDisponibili(PrenotazioniLibri p)
Restituisce il numero totale di copie disponibili in biblioteca.

2.int* libriMoltoPrenotati(PrenotazioniLibri p, int soglia, int* count)
Restituisce un array contenente i codici dei libri prenotati da più utenti della soglia. 
count rappresenta il numero di elementi nell’array.

3.char* autorePiuRichiesto(PrenotazioniLibri p)
Restituisce il nome dell’autore i cui libri hanno ricevuto più prenotazioni complessivamente.
Se ci sono più autori a pari merito, ne restituisce uno qualsiasi.

4. int libroMaiPrenotato(PrenotazioniLibri p)
Restituisce il codice di un libro mai prenotato da nessun utente. 
Se tutti i libri sono stati prenotati almeno una volta, restituisce -1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titolo[30];
    char autore[30];
    int copieDisponibili;
} Libro;

typedef struct {
    Libro libri[5];
    int prenotazioni[8][2];
} PrenotazioniLibri;

/*
Funzione 1: int copieTotaliDisponibili(PrenotazioniLibri p)
Restituisce il numero totale di copie disponibili in biblioteca.
*/
int copieTotaliDisponibili(PrenotazioniLibri p){
    int totale_copie_disp = 0;
    for(int i = 0; i < 5; i++){
        totale_copie_disp += p.libri[i].copieDisponibili;
    }
    return totale_copie_disp;
}

/*
Funzione 2: int* libriMoltoPrenotati(PrenotazioniLibri p, int soglia, int* count)
Restituisce un array contenente i codici dei libri prenotati da più utenti della soglia. 
count rappresenta il numero di elementi nell’array.
*/
int* libriMoltoPrenotati(PrenotazioniLibri p, int soglia, int* count){
    int cnt = 0;
    for(int i = 0; i < 5; i++){
        int num_prenotazioni = 0;
        for(int j = 0; j < 8; j++){
            if(p.prenotazioni[j][0] == i){
                num_prenotazioni++;
            }
        }
        if(num_prenotazioni > soglia){
            cnt++;
        }
    }
    int k = 0;
    int* res = malloc(cnt * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    *count = cnt;
    for(int i = 0; i < 5; i++){
        int num_prenotazioni = 0;
        for(int j = 0; j < 8; j++){
            if(p.prenotazioni[j][0] == i){
                num_prenotazioni++;
            }
        }
        if(num_prenotazioni > soglia){
            res[k] = i;
            k++;
        }
    }
    return res;
}

/*
Funzione 3: char* autorePiuRichiesto(PrenotazioniLibri p)
Restituisce il nome dell’autore i cui libri hanno ricevuto più prenotazioni complessivamente.
Se ci sono più autori a pari merito, ne restituisce uno qualsiasi.
*/
char* autorePiuRichiesto(PrenotazioniLibri p){
    int conteggi[5] = {0};
    for(int i = 0; i < 8; i++){
        int codiceLibro = p.prenotazioni[i][0];
        if(codiceLibro >= 0 && codiceLibro <= 5){
            conteggi[codiceLibro]++;
        }
    }
    // ora sommo le prenotazioni per autore
    int max = -1;
    int indiceMax = -1;
    for(int i = 0; i < 5; i++){
        int totaleAutore = 0;
        for(int j = 0; j < 5; j++){
            if(strcmp(p.libri[i].autore, p.libri[j].autore) == 0){
                totaleAutore += conteggi[j];
            }
        }
        if(totaleAutore > max){
            max = totaleAutore;
            indiceMax = i;
        }
    }
    return p.libri[indiceMax].autore;
}

/*
Funzione 4: int libroMaiPrenotato(PrenotazioniLibri p)
Restituisce il codice di un libro mai prenotato da nessun utente. 
Se tutti i libri sono stati prenotati almeno una volta, restituisce -1.
*/
int libroMaiPrenotato(PrenotazioniLibri p){
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 8; j++){
            if(p.prenotazioni[j][0] == i){
                trovato = 1; 
                break;
            }
        }
        if(!trovato){
            return i;
        }
    }
    return -1;
}