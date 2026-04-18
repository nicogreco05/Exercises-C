/*
Simulazione d'esame (chatgpt) - 24/05/35 dalle 11:00 alle 13:00

Dopo averlo fatto: 
Funzione 1 --> facilissima
Funzione 2 --> ci sono ma devo allenarmi di piu 
Funzione 3 --> non ci sono minimamente
Funzione 4 --> facilissima

typedef struct {
    char titolo[30];
    char genere[20];
    int copieDisponibili;
    int prezzoNoleggio;
} Film;

typedef struct {
    Film film[5];
    int noleggi[8][3]; // [codFilm, giorniNoleggio, prezzoEffettivo]
} NoleggiFilm;

Scrivere le seguenti funzioni:
-int valoreMagazzino(NoleggiFilm nf):r estituisce il valore totale (in euro) dei film presenti in magazzino, 
calcolato moltiplicando copieDisponibili per il prezzoNoleggio di ciascun film.

-int* filmPiuNoleggiati(NoleggiFilm nf, char genere[20], int soglia, int* count): restituisce un array dinamico contenente 
i codici dei film appartenenti al genere genere che sono stati noleggiati 
per un numero di giorni maggiore di soglia (sommando i giorni in tutte le righe corrispondenti).
Il numero di elementi nell’array risultato viene salvato in *count.

-char[20] generePiuRedditizio(NoleggiFilm nf): restituisce il genere per cui i noleggi hanno prodotto il guadagno totale più alto. 
Il guadagno di un film è la somma di tutti i prezzoEffettivo nelle righe che lo riguardano.
Il guadagno di un genere è la somma dei guadagni dei suoi film.

-int filmMaiNoleggiato(NoleggiFilm nf): restituisce il codice di un film che non compare in alcuna riga della matrice noleggi.
Se più film soddisfano la condizione, si può restituire uno qualsiasi di essi.
Se tutti i film sono stati noleggiati almeno una volta, la funzione restituisce -1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titolo[30];
    char genere[20];
    int copieDisponibili;
    int prezzoNoleggio;
} Film;

typedef struct {
    Film film[5];
    int noleggi[8][3]; // [codFilm, giorniNoleggio, prezzoEffettivo]
} NoleggiFilm;

/*
Funzione 1: int valoreMagazzino(NoleggiFilm nf): estituisce il valore totale (in euro) dei film presenti in magazzino, 
calcolato moltiplicando copieDisponibili per il prezzoNoleggio di ciascun film.
*/
int valoreMagazzino(NoleggiFilm nf){
    int valore_totale = 0;
    for(int i = 0; i < 5; i++){
        valore_totale += nf.film[i].copieDisponibili * nf.film[i].prezzoNoleggio;
    }
    return valore_totale;
}

/*
Funzione 2: int* filmPiuNoleggiati(NoleggiFilm nf, char genere[20], int soglia, int* count): restituisce un array dinamico contenente 
i codici dei film appartenenti al genere genere che sono stati noleggiati 
per un numero di giorni maggiore di soglia (sommando i giorni in tutte le righe corrispondenti).
Il numero di elementi nell’array risultato viene salvato in *count.
*/
int* filmPiuNoleggiati(NoleggiFilm nf, char genere[20], int soglia, int* count){
    int cnt = 0;
    for(int i = 0; i < 5; i++){
        if(strcmp(nf.film[i].genere, genere) == 0){
            int num_noleggi = 0;
            for(int j = 0; j < 8; j++){
                if(nf.noleggi[j][0] == i){
                    num_noleggi++;
                }
            }
            if(num_noleggi > soglia){
                cnt++;
            }
        }
    }
    int* res = malloc(cnt * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    *count = cnt;
    int k = 0;
    for(int i = 0; i < 5; i++){
        if(strcmp(nf.film[i].genere, genere) == 0){
            int num_noleggi = 0;
            for(int j = 0; j < 8; j++){
                if(nf.noleggi[j][0] == i){
                    num_noleggi++;
                }
            }
            if(num_noleggi > soglia){
                res[k] = i;
                k++;
            }
        }
    }
    return res;
}

/*
Funzione 3: char[20] generePiuRedditizio(NoleggiFilm nf): restituisce il genere per cui i noleggi hanno prodotto il guadagno totale più alto. 
Il guadagno di un film è la somma di tutti i prezzoEffettivo nelle righe che lo riguardano.
Il guadagno di un genere è la somma dei guadagni dei suoi film.
*/
void generePiuRedditizio(NoleggiFilm nf, char risultato[20]){
    int guadagni[5] = {0}; // uno per ogni film 
    char generi[5][20]; // per salvare i generi dei film
    int n_generi;
    // Calcolo i guadagni per ciascun film
    for(int i = 0; i < 8; i++){
        int codice = nf.noleggi[i][0];
        int prezzoEff = nf.noleggi[i][2];
        guadagni[codice] += prezzoEff;
    }
    // Sommo i guadagni per ogni genere
    int guadagnoPerGenere[5] = {0};
    for(int i = 0; i < 5; i++){
        // Controllo se il genere è gia stato registrato
        int index = -1;
        for(int j = 0; j < n_generi; j++){
            if(strcmp(nf.film[i].genere, generi[j]) == 0){
                index = j;
                break;
            }
        }
        if(index == -1){
            // nuovo genere
            strcpy(generi[n_generi], nf.film[i].genere);
            guadagnoPerGenere[n_generi] = guadagni[i];
            n_generi++;
        } else {
            // sommo guadagno a genere gia visto
            guadagnoPerGenere[index] += guadagni[i];
        }
    }
    // Trovo il genere col massimo guadagno 
    int max = guadagnoPerGenere[0];
    int pos = 0;
    for(int i = 1; i < n_generi; i++){
        if(guadagnoPerGenere[i] > max){
            max = guadagnoPerGenere[i];
            pos = i;
        }
    }
    strcpy(risultato, generi[pos]);
}

/*
Funzione 4: int filmMaiNoleggiato(NoleggiFilm nf): restituisce il codice di un film che non compare in alcuna riga della matrice noleggi.
Se più film soddisfano la condizione, si può restituire uno qualsiasi di essi.
Se tutti i film sono stati noleggiati almeno una volta, la funzione restituisce -1.
*/
int filmMaiNoleggiato(NoleggiFilm nf){
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 8; j++){
            if(nf.noleggi[j][0] == i){
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