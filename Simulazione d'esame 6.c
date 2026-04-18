/*
Simulazione d'esame (5 febbrario 2025) - Casa, Cosenza 27/05/25 dalle 13:00 alle 14:00
Dopo averlo fatto:
Funzione 1 --> ok
Funzione 2 --> ok-
Funzione 3 --> ok-
Funzione 4 --> ok

Si vuole realizzare un’applicazione per la gestione di dati relativi ad un negozio di informatica. Le informazioni 
sono memorizzate in struct aventi la seguente definizione:

typedef struct {
    char nome[20]; 
    char cat[20]; 
    int qntDisp; 
    int prezzo; 
} Prodotto;

typedef struct {
    Prodotto prodotti[5]; 
    int vendite[8][3]; 
} VenditeProdotti;

Ogni istanza di Prodotto rappresenta il fatto che il prodotto di nome nome appartiene alla categoria cat, è 
disponibile  in  magazzino  in  un  numero  di  pezzi  pari  a  qntDisp  ed  ha  un  prezzo  pari  a  prezzo.  A  ciascun 
prodotto è assegnato un codice intero compreso tra 0 e  4. L’i-esimo elemento dell’array prodotti contiene 
l’istanza di Prodotto relativa al prodotto i. 
Le informazioni  relative alle vendite sono memorizzate in una matrice  vendite la cui i-esima riga [codProd, 
numPez, prezzo] indica che il prodotto con codice codProd è stato acquistato in quantità numPezzi al prezzo 
di vendita prezzo. Si noti che (i) ciascun prodotto può apparire in più di una riga della matrice vendite e (ii) i 
prezzi di uno stesso prodotto in righe diverse di vendite possono differire. 
L’istanza di VenditeProdotti contiene l’array prodotti e la matrice vendite. 
Si scrivano in C le seguenti funzioni (la scrittura di eventuali funzioni ausiliarie è sempre ammessa): 
• int  valoreMagazzino(VenditeProdotti  vp)  che  restituisce  il  valore  totale  dei  prodotti  contenuti  nel 
  magazzino. Per calcolare il valore si deve fare riferimento al prezzo riportato nell’istanza di Prodotto. 
• int  *prodottiTop(VediteProdotti  vp,  char  cat[20],  int  num,  int  *count)  che  restituisce  un  array 
  contenente i codici dei prodotti di categoria cat che sono stati venduti in un numero di pezzi maggiori 
  a num. La variabile count rappresenta il puntatore al numero di elementi inseriti nell’array risultato. 
• char[20] categoriaRedditizia(VenditeProdotti vp), che restituisce il nome della categoria le cui vendite 
  hanno portato il guadagno massimo. Per guadagno della categoria si intende il ricavato delle vendite 
  di prodotti appartenenti a quella categoria. 
• int prodottoInvenduto(VenditeProdotti vp), che restituisce il codice di un prodotto non coinvolto in 
  alcuna vendita. Se più di un prodotto soddisfa la condizione, la funzione restituisce uno qualsiasi di 
  essi, altrimenti restituisce -1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[20]; 
    char cat[20]; 
    int qntDisp; 
    int prezzo; 
} Prodotto;

typedef struct {
    Prodotto prodotti[5]; 
    int vendite[8][3]; // [codprod , numpezi , prezzo]
} VenditeProdotti;

/*
Funzione 1: int valoreMagazzino(VenditeProdotti  vp)  che  restituisce  il  valore  totale  dei  prodotti  contenuti  nel 
magazzino. Per calcolare il valore si deve fare riferimento al prezzo riportato nell’istanza di Prodotto. 
*/
int valoreMagazzino(VenditeProdotti vp){
    int valore_totale = 0;
    for(int i = 0; i < 5; i++){
        valore_totale += vp.prodotti[i].prezzo * vp.prodotti[i].qntDisp;
    }
    return valore_totale;
}

/*
Funzione 2: int  *prodottiTop(VediteProdotti  vp,  char  cat[20],  int  num,  int  *count)  che  restituisce  un  array 
contenente i codici dei prodotti di categoria cat che sono stati venduti in un numero di pezzi maggiori 
a num. La variabile count rappresenta il puntatore al numero di elementi inseriti nell’array risultato. 
*/
int *prodottiTop(VenditeProdotti vp, char cat[20], int num, int *count){
    int cnt = 0;
    for(int i = 0; i < 5; i++){
        if(strcmp(vp.prodotti[i].cat, cat) == 0){
            int sommaPezzi = 0;
            for(int j = 0; j < 8; j++){
                if(vp.vendite[j][0] == i){
                    sommaPezzi += vp.vendite[j][1];
                }
            }
            if(sommaPezzi > num){
                cnt++;
            }
        }
    }
    int* res = malloc(cnt * sizeof(int));
    *count = cnt;
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int k = 0;
    for(int i = 0; i < 5; i++){
        if(strcmp(vp.prodotti[i].cat, cat) == 0){
            int sommaPezzi = 0;
            for(int j = 0; j < 8; j++){
                if(vp.vendite[j][0] == i){
                    sommaPezzi += vp.vendite[j][1];
                }
            }
            if(sommaPezzi > num){
                res[k] = i;
            }
        }
    }
    return res;
}

/*
Funzione 3: char[20] categoriaRedditizia(VenditeProdotti vp), che restituisce il nome della categoria le cui vendite 
hanno portato il guadagno massimo. Per guadagno della categoria si intende il ricavato delle vendite 
di prodotti appartenenti a quella categoria. 
*/
char* categoriaRedditizia(VenditeProdotti vp){
    char* categorie[5][20];
    int totali[5] = {0};
    int nCategorie = 0;
    for(int i = 0; i < 5; i++){
        int index = -1;
        for(int k = 0; k < nCategorie; k++){
            if(strcmp(vp.prodotti[i].cat, categorie[k]) == 0){
                index = k;
                break;
            }
        }
        if(index == -1){
            strcpy(categorie[nCategorie], vp.prodotti[i].cat);
            index = nCategorie;
            nCategorie++;
        }
        for(int j = 0; j < 8; j++){
            if(vp.vendite[j][0] == i){
                totali[index] = vp.vendite[j][1] * vp.vendite[j][2];
             }
        }
    }
    int max = totali[0];
    int pos = 0;
    for(int i = 1; i < nCategorie; i++){
        if(totali[i] > max){
            max = totali[i];
            pos = i;
        }
    }
    char* res = malloc(20 * sizeof(char*));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    strcpy(res, categorie[pos]);
    return res;
}

/*
Funzione 4: int prodottoInvenduto(VenditeProdotti vp), che restituisce il codice di un prodotto non coinvolto in 
alcuna vendita. Se più di un prodotto soddisfa la condizione, la funzione restituisce uno qualsiasi di 
essi, altrimenti restituisce -1.
*/
int prodottoInvenduto(VenditeProdotti vp){
    for(int i = 0; i < 5; i++){
        int venduto = 0;
        for(int j = 0; j < 8; j++){
            if(vp.vendite[j][0] == i){
                venduto = 1;
                break;
            }
        }
        if(!venduto){
            return i;
        }
    }
    return -1;
}
