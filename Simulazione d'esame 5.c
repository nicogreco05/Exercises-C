/*
Simulazione d'esame (chatgpt) - Casa, Cosenza 27/05/25 dalle 12:00 alle 14:00

Un’applicazione gestisce gli ordini di un sito di e-commerce. I dati sono rappresentati con le seguenti strutture:
Dopo averlo fatto:
Funzione 1 --> ok
Funzione 2 --> ok-
Funzione 3 --> imposibile
Funzione 4 --> ok

typedef struct {
    char nomeProdotto[30];
    char categoria[20];
    int pezziDisponibili;
    int prezzoUnitario;
} Prodotto;

typedef struct {
    Prodotto prodotti[5];
    int ordini[8][3]; --> Ogni riga è: [codProdotto, pezziOrdinati, idCliente]
} GestioneOrdini;

Ogni riga della matrice ordini indica che il cliente con idCliente ha ordinato pezziOrdinati del prodotto con codice codProdotto. 
I prodotti sono identificati da codici da 0 a 4.

Funzioni da implementare:
1.int valoreMagazzino(GestioneOrdini g):
Restituisce il valore complessivo (in euro) del magazzino considerando solo i prodotti disponibili.

2.int* prodottiPopolari(GestioneOrdini g, int soglia, int* count):
Restituisce un array contenente i codici dei prodotti ordinati in quantità totali superiori a soglia.
La variabile count conterrà il numero di prodotti trovati.

3.char* categoriaTop(GestioneOrdini g):
Restituisce la categoria che ha generato il ricavo più alto (pezzi ordinati × prezzo unitario).

4.int prodottoMaiOrdinato(GestioneOrdini g):
Restituisce il codice di un prodotto che non è mai stato ordinato. Se tutti sono stati ordinati, restituisce -1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nomeProdotto[30];
    char categoria[20];
    int pezziDisponibili;
    int prezzoUnitario;
} Prodotto;

typedef struct {
    Prodotto prodotti[5];
    int ordini[8][3]; // Ogni riga è: [codProdotto, pezziOrdinati, idCliente]
} GestioneOrdini;

/*
Funzione 1: int valoreMagazzino(GestioneOrdini g):
Restituisce il valore complessivo (in euro) del magazzino considerando solo i prodotti disponibili.
*/
int valoreMagazzino(GestioneOrdini g){
    int valore_totale = 0;
    for(int i = 0; i < 5; i++){
        valore_totale += g.prodotti[i].pezziDisponibili * g.prodotti[i].prezzoUnitario;
    }
    return valore_totale;
}

/*
Funzione 2: int* prodottiPopolari(GestioneOrdini g, int soglia, int* count):
Restituisce un array contenente i codici dei prodotti ordinati in quantità totali superiori a soglia.
La variabile count conterrà il numero di prodotti trovati.
*/
int* prodottiPopolari(GestioneOrdini g, int soglia, int* count){
    int cnt = 0;
    for(int i = 0; i < 5; i++){
        int supera = 0;
        for(int j = 0; j < 8; j++){
            if(g.ordini[j][0] == i){
                if(g.ordini[j][1] > soglia){
                    supera = 1;
                    break;
                }
            }
        }
        if(supera){
            cnt++;
        }
    }
    int* res = malloc(cnt * sizeof(int));
    *count = cnt;
    if(res == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    int k = 0;
    for(int i = 0; i < 5; i++){
        int supera = 0;
        for(int j = 0; j < 8; j++){
            if(g.ordini[j][0] == i){
                if(g.ordini[j][1] > soglia){
                    supera = 1;
                    break;
                }
            }
        }
        if(supera){
            res[k++] = i;
        }
    }
    return res;
}

/*
Funzione 3: char* categoriaTop(GestioneOrdini g):
Restituisce la categoria che ha generato il ricavo più alto (pezzi ordinati × prezzo unitario).
*/
char* categoriaTop(GestioneOrdini g) {
    char* categorie[5];
    int totali[5] = {0};
    int nCategorie = 0;
    for(int i = 0; i < 5; i++) {
        // Trova se la categoria è già stata vista
        int index = -1;
        for(int k = 0; k < nCategorie; k++) {
            if(strcmp(g.prodotti[i].categoria, categorie[k]) == 0) {
                index = k;
                break;
            }
        }
        // Se è nuova, aggiungila
        if(index == -1) {
            categorie[nCategorie] = g.prodotti[i].categoria;
            index = nCategorie;
            nCategorie++;
        }
        // Somma il fatturato di questo prodotto a quella categoria
        for(int j = 0; j < 8; j++) {
            if(g.ordini[j][0] == i) {
                totali[index] += g.ordini[j][1] * g.prodotti[i].prezzoUnitario;
            }
        }
    }
    // Trova l'indice della categoria col massimo totale
    int max = totali[0];
    int pos = 0;
    for(int i = 1; i < nCategorie; i++) {
        if(totali[i] > max) {
            max = totali[i];
            pos = i;
        }
    }
    return categorie[pos]; // ritorna direttamente il puntatore alla stringa già presente
}

/*
Funzione 4: int prodottoMaiOrdinato(GestioneOrdini g):
Restituisce il codice di un prodotto che non è mai stato ordinato. Se tutti sono stati ordinati, restituisce -1.
*/
int prodottoMaiOrdinato(GestioneOrdini g){
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 8; j++){
            if(g.ordini[j][0] == i){
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