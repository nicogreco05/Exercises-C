/*
Simulazione d'esame (chatgpt) - Casa, Cosenza dalle 15:00 alle 15:45

Si vuole realizzare un’applicazione in linguaggio C per la gestione dei dati relativi ai film disponibili in una videoteca e ai noleggi effettuati.

typedef struct {
    char titolo[50];
    char genere[30];       // es. "Azione", "Commedia", "Dramma", ecc.
    int copieDisponibili;
    int valoreNoleggio;    // prezzo in euro per ogni noleggio
} Film;

typedef struct {
    Film film[6];
    int noleggi[12][3]; // ogni riga: [indiceFilm, giorni, prezzoTotale]
} RegistroNoleggi;

Funzioni da implementare:
1.	int valoreTotaleCatalogo(RegistroNoleggi r)
Calcola e restituisce il valore totale dei film disponibili
2.	int* filmPopolari(RegistroNoleggi r, char* genere, int soglia, int* dim)
Restituisce un array dinamico contenente gli indici dei film del genere specificato noleggiati almeno soglia volte.
Usa *dim per restituire il numero di elementi.
3.	char* genereTop(RegistroNoleggi r)
Restituisce il genere in cui i clienti hanno speso di più in totale. Se ci sono più generi con lo stesso massimo, si può restituire uno qualsiasi.
4.	int filmMaiNoleggiati(RegistroNoleggi r)
Restituisce il numero di film che non sono mai stati noleggiati.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titolo[50];
    char genere[30];       // es. "Azione", "Commedia", "Dramma", ecc.
    int copieDisponibili;
    int valoreNoleggio;    // prezzo in euro per ogni noleggio
} Film;

typedef struct {
    Film film[6];
    int noleggi[12][3]; // ogni riga: [indiceFilm, giorni, prezzoTotale]
} RegistroNoleggi;

/*
Funzione 1: int valoreTotaleCatalogo(RegistroNoleggi r)
Calcola e restituisce il valore totale dei film disponibili
*/
int valoreTotaleCatalogo(RegistroNoleggi r){
    int valore_totale = 0;
    for(int i = 0; i < 6; i++){
        valore_totale += r.film[i].copieDisponibili * r.film[i].valoreNoleggio;
    }
    return valore_totale;
}

/*
Funzione 2: int* filmPopolari(RegistroNoleggi r, char* genere, int soglia, int* dim)
Restituisce un array dinamico contenente gli indici dei film del genere specificato noleggiati almeno soglia volte.
Usa *dim per restituire il numero di elementi.
*/
int* filmPopolari(RegistroNoleggi r, char* genere, int soglia, int* dim){
    int* conteggi_soglie = (int*) calloc (6, sizeof(int));
    if(conteggi_soglie == NULL){
        printf("Errore nell'allocazione della memorria!");
        exit(1);
    } 
    *dim = 0;
    for(int i = 0; i < 12; i++){
        int index = r.noleggi[i][0];
        if(strcmp(r.film[index].genere, genere) == 0){
            conteggi_soglie[index]++;
        }
    }
    for(int i = 0; i < 6; i++){
        if(conteggi_soglie[i] >= soglia){
            (*dim)++;
        }
    }
    int* res = (int*) malloc ((*dim) * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int k = 0;
    for(int i = 0; i < 6; i++){
        if(conteggi_soglie[i] >= soglia){
            res[k++] = i;
        }
    }
    free(conteggi_soglie);
    return res;
}

/*
Funzione 3: char* genereTop(RegistroNoleggi r)
Restituisce il genere in cui i clienti hanno speso di più in totale. 
Se ci sono più generi con lo stesso massimo, si può restituire uno qualsiasi.
*/
char* genereTop(RegistroNoleggi r){
    char* generi[6];
    int totali[6] = {0};
    int nGeneri = 0;
    for(int i = 0; i < 12; i++){
        int index = r.noleggi[i][0];
        char* genere = r.film[index].genere;
        int tot = r.noleggi[i][2];
        int trovato = -1;
        for(int j = 0; j < nGeneri; j++){
            if(strcmp(generi[i], genere) == 0){
                trovato = j;
                break; 
            }
        }
        if(trovato == -1){
            generi[nGeneri] = genere;
            totali[nGeneri] = tot;
            nGeneri++;
        }
        else{
            totali[trovato] += tot; 
        }
    }
    int max_idx = 0;
    for(int i = 1; i < nGeneri; i++){
        if(totali[i] > totali[max_idx]){
            max_idx = i;
        }
    }
    return generi[max_idx];
}

/*
Funzione 4: int filmMaiNoleggiati(RegistroNoleggi r)
Restituisce il numero di film che non sono mai stati noleggiati.
*/
int maiNoleggiati(RegistroNoleggi r){
    int count = 0;
    for(int i = 0; i < 6; i++){
        int trovato = 0;
        for(int j = 0; j < 12; j++){
            if(i == r.noleggi[j][0]){
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