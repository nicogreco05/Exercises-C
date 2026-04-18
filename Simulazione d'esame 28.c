/*
Simulazione d'esame (tutor) - Casa, San Gregorio dalle 11:30 alle 

Si vuole realizzare un’applicazione per la gestione delle richieste in un centro commerciale che vende elettrodomestici. 
Le informazioni sono memorizzate mediante le seguenti strutture:

    typedef struct {
        char marca[20];
        char tipo[20];      // es. "Frigorifero", "Lavatrice", ...
        int potenza;        // in Watt
        int prezzo;         // in euro
    } Elettrodomestico;
 
    typedef struct {
        Elettrodomestico inventario[6];     // massimo 6 prodotti disponibili
        int richieste[5][2];                // ogni riga: {min_potenza, max_prezzo}
    } DatiCentro;
 
Ogni riga della matrice richieste rappresenta la richiesta di un cliente:
si desidera un elettrodomestico che abbia una potenza maggiore o uguale a
min_potenza e un prezzo minore o uguale a max_prezzo.
 
Si scrivano le seguenti funzioni:
- bool tutteSoddisfatte(DatiCentro dc), che restituisce true se tutte le richieste
possono essere soddisfatte da almeno un elettrodomestico disponibile.
Altrimenti restituisce false.

- char* tipoPiuEconomico(DatiCentro dc), che restituisce il tipo di elettrodomestico
(es. “Lavatrice”) con il prezzo medio più basso. Se ci sono più tipi con lo
stesso prezzo medio, si può restituire uno qualsiasi di essi.
 
- char* marcaPiuPotente(DatiCentro dc), che restituisce la marca con la somma di
potenza più alta tra i suoi elettrodomestici.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM_ELETTRODOMESTICI 6

 typedef struct {
    char marca[20];
    char tipo[20];      // es. "Frigorifero", "Lavatrice", ...
    int potenza;        // in Watt
    int prezzo;         // in euro
} Elettrodomestico;
 
typedef struct {
     Elettrodomestico inventario[6];     // massimo 6 prodotti disponibili
    int richieste[5][2];                // ogni riga: {min_potenza, max_prezzo}
} DatiCentro;

/*
Funzione 1: bool tutteSoddisfatte(DatiCentro dc), che restituisce true se tutte le richieste
possono essere soddisfatte da almeno un elettrodomestico disponibile.
Altrimenti restituisce false.
*/
bool tutteSoddisfatte(DatiCentro dc){
    for(int i = 0; i < 5; i++){
        bool soddisfatte = false;
        for(int j = 0; j < 6; j++){
            if(dc.richieste[i][0] <= dc.inventario[j].potenza && dc.richieste[i][1] >= dc.inventario[j].prezzo){
                soddisfatte = true;
            }
        }
        if(!soddisfatte){
            return false;
        }
    }
    return true;
}

/*
Funzione 2: char* tipoPiuEconomico(DatiCentro dc), che restituisce il tipo di elettrodomestico
(es. “Lavatrice”) con il prezzo medio più basso. Se ci sono più tipi con lo
stesso prezzo medio, si può restituire uno qualsiasi di essi.
*/
char* tipoPiuEconomico(DatiCentro dc) {
    static char tipoMin[20];
    int somma[NUM_ELETTRODOMESTICI] = {0};
    int conteggio[NUM_ELETTRODOMESTICI] = {0};
    char tipi[NUM_ELETTRODOMESTICI][20];
    int tipiCount = 0;
 
    for (int i = 0; i < NUM_ELETTRODOMESTICI; i++) {
        int idx = -1;
        for (int k = 0; k < tipiCount; k++) {
            if (strcmp(tipi[k], dc.inventario[i].tipo) == 0) {
                idx = k;
                break;
            }
        }
        if (idx == -1) {
            strcpy(tipi[tipiCount], dc.inventario[i].tipo);
            idx = tipiCount;
            tipiCount++;
        }
 
        somma[idx] += dc.inventario[i].prezzo;
        conteggio[idx]++;
    }
 
    float minMedia = -1;
    int indMin = -1;
    for (int i = 0; i < tipiCount; i++) {
        float media = (float) somma[i] / conteggio[i];
        if (media < minMedia) {
            minMedia = media;
            indMin = i;
        }
    }
 
    strcpy(tipoMin, tipi[indMin]);
 
    return tipoMin;
}

/*
Funzione 3: char* marcaPiuPotente(DatiCentro dc), che restituisce la marca con la somma di
potenza più alta tra i suoi elettrodomestici.
*/
char* marcaPiuPotente(DatiCentro dc){
    static char marca[20];
    int somma[6] = {0};
    char marche[6][20];
    int marcheCount = 0;
    for(int i = 0; i < 6; i++){
        int idx = -1;
        for(int j = 0; j < marcheCount; j++){
            if(strcmp(marche[j], dc.inventario[i].marca) == 0){
                idx = j;
                break;
            }
        }
        if(idx == -1){
            strcpy(marche[marcheCount],dc.inventario[i].marca);
            idx = marcheCount;
            marcheCount++;
        }
        somma[idx] += dc.inventario[i].potenza;
    }
    int max_idx = 0; 
    for(int i = 1; i < marcheCount; i++){
        if(somma[i] > somma[max_idx]){
            max_idx = i;
        }
    }
    strcpy(marca, marche[max_idx]);
    return marca;
}

/*
Esercizio 2: Si scriva una funzione int* differenzaValori(int *a, int *b, int dim, int *dim_out), che
riceve in ingresso due array a e b di interi di uguale dimensione dim, e un puntatore
dim_out dove memorizzare la dimensione del nuovo array restituito. La funzione restituisce
un array allocato dinamicamente, contenente solo gli elementi di a che differiscono da
quelli di b nella stessa posizione. Se a[i] != b[i], allora a[i] verrà inserito nel
nuovo array. Dopo l’elaborazione, la variabile puntata da dim_out conterrà la dimensione
del nuovo array.
 
Es. Se a = [10, 20, 30, 40, 50] e b = [10, 25, 30, 35, 50], allora la funzione
restituirà il vettore [20, 40] e *dim_out = 2, perché solo le posizioni 1 e 3
hanno valori diversi.
*/
int* differenzaValori(int* a, int* b, int dim, int* dim_out){
    *dim_out = 0;
    for(int i = 0; i < dim; i++){
        if(a[i] != b[i]){
            (*dim_out)++;
        }
    }
    int* res = (int*) malloc ((*dim_out) * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int k = 0;
    for(int i = 0; i < dim; i++){
        if(a[i] != b[i]){
            res[k++] = a[i];
        }
    }
    return res;
}
