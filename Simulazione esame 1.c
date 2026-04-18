/*
Simulazione d'esame - 23/05/25 dalle 17:00 alle 18:00 
Dopo avrlo fatto:
Funzione 1 --> facilissima
Funzione 2 --> facile
Funzione 3 --> difficilissima
Funzione 4 --> ok
Finale: 7 su 10 --> posso fare molto di piu 

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
    int vendite[8][3]; 
} VenditeProdotti;

/*
Funzione 1: int  valoreMagazzino(VenditeProdotti  vp)  che  restituisce  il  valore  totale  dei  prodotti  contenuti  nel 
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
        int qnt_vend = 0;
        if(strcmp(vp.prodotti[i].cat, cat) == 0){
            for(int j = 0; j < 8; j++){
                if(vp.vendite[j][0] == i){
                    qnt_vend += vp.vendite[j][1];
                }
            }
            if(qnt_vend > num){
                cnt++;
            }
        }
    }
    *count = cnt;
    int *res = (int*) malloc(cnt * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int k = 0;
    for(int i = 0; i < 5; i++){
        int qnt_vend = 0;
        if(strcmp(vp.prodotti[i].cat, cat) == 0){
            for(int j = 0; j < 8; j++){
                if(vp.vendite[j][0] == i){
                    qnt_vend += vp.vendite[j][1];
                }
            }
            if(qnt_vend > num){
                res[k++] = i;
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

int contenuto(char** v, int dim, char* elem){
    for(int i = 0; i < dim; i++){
        if (strcmp(v[i], elem) == 0){
            return 1;
        }
    }
    return 0;
}

char* categoriaReddizia(VenditeProdotti vp){
    char** categorie = (char**) calloc (5, sizeof(char*));
    int k = 0;
    for(int i = 0; i < 5; i++){
        char *cat = vp.prodotti[i].cat;
        if(!contenuto(categorie, k, cat)){
            categorie[k] = cat;
            k++;
        }
    }
    categorie = (char**) realloc (categorie, k * sizeof(char*));
    int max_guadagno = 0;
    char* max_cat = "";
    for(int i = 0; i < k; i++){
        int guadano_corr = 0;
        char* categoria_corr = categorie[i];
        for(int j = 0; j < 8; j++){
            int cod_prod = vp.vendite[j][0];
            if(strcmp(vp.prodotti[cod_prod].cat,categoria_corr) == 0){
                guadano_corr += vp.vendite[j][1] * vp.vendite[j][2];
            }
        }
        if(guadano_corr > max_guadagno){
            max_guadagno = guadano_corr;
            max_cat = categoria_corr;
        }
    }
    return max_cat;
}

/*
Funzione 4: int prodottoInvenduto(VenditeProdotti vp), che restituisce il codice di un prodotto non coinvolto in 
alcuna vendita. Se più di un prodotto soddisfa la condizione, la funzione restituisce uno qualsiasi di 
essi, altrimenti restituisce -1.
*/
int prodottoInvenduto(VenditeProdotti vp){
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 8; i++){
            if(vp.vendite[j][0] = i){
                trovato = 1;
                break;
            }
        }
        if(!trovato){
            return i;
        }
    }
}