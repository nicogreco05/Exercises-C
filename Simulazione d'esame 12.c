/*
Simulazione d'esame (chat gpt) - Casa, San Gregorio dalle 17:30 alle 18:30

Un cinema vuole gestire i dati dei film disponibili in programmazione e i biglietti venduti.

typedef struct {
    char titolo[30];
    int durata;      // in minuti
    int categoria;   // 0=Animazione, 1=Azione, 2=Commedia, 3=Horror, 4=Altro
    float prezzo;
} Film;

typedef struct {
    Film elenco[5];        // massimo 5 film in programmazione
    int vendite[10][2];    // ogni riga: {indiceFilm, bigliettiVenduti}
} Cinema;

Implementare le seguenti funzioni:
1. float incassoTotale(Cinema c)
Restituisce l’incasso totale generato da tutti i film (prezzo × biglietti venduti per film).

2. int filmPiuVisto(Cinema c)
Restituisce l’indice del film che ha venduto più biglietti in totale.

3. char* categoriaTop(Cinema c)
Restituisce una stringa con il nome della categoria (tra quelle indicate) che ha totalizzato più biglietti venduti in totale.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titolo[30];
    int durata;      // in minuti
    int categoria;   // 0=Animazione, 1=Azione, 2=Commedia, 3=Horror, 4=Altro
    float prezzo;
} Film;

typedef struct {
    Film elenco[5];        // massimo 5 film in programmazione
    int vendite[10][2];    // ogni riga: {indiceFilm, bigliettiVenduti}
} Cinema;

/*
Funzione 1: float incassoTotale(Cinema c)
Restituisce l’incasso totale generato da tutti i film (prezzo × biglietti venduti per film).
*/
float incassoTotale(Cinema c){
    float somma = 0.0;
    for(int i = 0; i < 10; i++){
        somma += c.vendite[i][0] * c.elenco[i].prezzo;
    }
    return somma;
}

/*
Funzione 2: int filmPiuVisto(Cinema c)
Restituisce l’indice del film che ha venduto più biglietti in totale.
*/
int filmPiuVisto(Cinema c){
    int totali[5] = {0};
    for(int i = 0; i < 10; i++){
        int indice_film = c.vendite[i][0];
        int n_venduti = c.vendite[i][1];
        totali[indice_film] += n_venduti;
    }
    int max = 0;
    for(int i = 1; i < 5; i++){
        if(totali[i] > totali[max]){
            max = i;
        }
    }
    return max;
}

/*
Funzione 3: char* categoriaTop(Cinema c)
Restituisce una stringa con il nome della categoria (tra quelle indicate) che ha totalizzato più biglietti venduti in totale.
*/
char* categoriaTop(Cinema c){
    char* categorie[5] = {"ANimazione", "Azione", "Commedia", "Horror", "Altro"};
    int totali[5] = {0};
    for(int i = 0; i < 10; i++){
        int indice_libro = c.vendite[i][0];
        int biglietti_venduti = c.vendite[i][1];
        int genere = c.elenco[indice_libro].categoria;
        totali[genere] += biglietti_venduti;
    }
    int max_categoria = 0;
    for(int i = i; i < 5; i++){
        if(totali[i] > totali[max_categoria]){
            max_categoria = i;
        }
    }
    char* res = (char*) malloc (20 * sizeof(char));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    strcpy(res, categorie[max_categoria]);
    return res;
}

/*
Esercizio 2: int* finestreDecrescenti(int* A, int dim, int* dimRes)

Data una sequenza di interi A di lunghezza dim, 
restituisce un array dinamico contenente gli indici da cui partono sottosequenze di 3 elementi consecutivi decrescenti.

Esempio:
Se A = {10, 8, 5, 6, 4, 2}
La funzione restituirà {0, 3}
Perché:
•	A[0]=10, A[1]=8, A[2]=5  
•	A[3]=6, A[4]=4, A[5]=2  
*/
int* finestreDecrescenti(int* A, int dim, int soglia, int* dimRes){
    int count = 0;
    for(int i = 0; i <= dim - 3 ; i++){
        int somma = A[i] + A[i+1] + A[i+2];
        if(somma > soglia){
            count++;
        }
    }
    int* res = (int*) malloc (count * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int k = 0;
    for(int i = 0; i <= dim - 3 ; i++){
        int somma = A[i] + A[i+1] + A[i+2];
        if(somma > soglia){
            res[k++] = i;
        }
    }
    *dimRes = count;
    return res;
}
