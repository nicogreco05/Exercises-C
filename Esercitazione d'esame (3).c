/*
Si vuole realizzare un’applicazione per la gestione di dati relativi ad un negozio di informatica.
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
#include <string.h>
#include <stdlib.h>

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

// Funzione 1: int  valoreMagazzino(VenditeProdotti  vp)  che  restituisce  il  valore  totale  dei  prodotti  contenuti  nel 
// magazzino. Per calcolare il valore si deve fare riferimento al prezzo riportato nell’istanza di Prodotto. 
int valoreMagazzino(VenditeProdotti vp){
    int valore_totale = 0;
    for(int i = 0; i < 5; i++){
        valore_totale += vp.prodotti[i].qntDisp * vp.prodotti[i].prezzo;
    }
    return valore_totale;
}

/*
Funzione 2: int *prodottiTop(VediteProdotti  vp,  char  cat[20],  int  num,  int  *count)  che  restituisce  un  array 
contenente i codici dei prodotti di categoria cat che sono stati venduti in un numero di pezzi maggiori a num. 
La variabile count rappresenta il puntatore al numero di elementi inseriti nell’array risultato.
*/
int *prodottiTop(VenditeProdotti vp, char cat[20], int num, int *count){
    int cnt = 0;
    for (int i = 0; i < 5; i++){
        int qntvnd = 0;
        if (strcmp(vp.prodotti[i].cat, cat) == 0){
            for (int j = 0; j < 8; j++) {
                if (vp.vendite[j][0] == i){
                    qntvnd += vp.vendite[j][1];
                }
            }
        }
        if(qntvnd > num){
            cnt++;
        }
    }
    *count = cnt;
    int* res = (int*) malloc(*count * sizeof(int));
    int k = 0;
    for(int i = 0; i < 5; i++){
        int qntvnd = 0;
        if(strcmp(vp.prodotti[i].cat, cat) == 0){
            for(int j = 0; j < 8; j++){
                if(vp.vendite[j][0] == i){
                    qntvnd += vp.vendite[j][1];
                }
            }
        }
        if(qntvnd > num){
            res[k] = i;
            k++;
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
    char** categorie = (char**) calloc (5, sizeof(char*));
    int k = 0;
    for (int i = 0; i < 5; i++) {
        char* cat = vp.prodotti[i].cat;
        if (!contenuto(categorie, k, cat)) {
            categorie[k] = cat;
            k++;
        }
    }
    categorie = (char**) realloc (categorie, k * sizeof(char*));
    int maxGuad = 0;
    char* maxCat = "";
    for(int i = 0; i < k; i++) {
        int curGuad = 0;
        char* curCat = categorie[i];
        for (int j = 0; j < 8; j++) {
            int codProd = vp.vendite[j][0];
            if (strcmp(vp.prodotti[codProd].cat, curCat) == 0) {
                curGuad += vp.vendite[j][1] * vp.vendite[j][2];
            }
        }
        if (curGuad > maxGuad) {
            maxGuad = curGuad;
            maxCat = curCat;
        }
    }
    return maxCat;
}

/*
Funzione 4: int prodottoInvenduto(VenditeProdotti vp), che restituisce il codice di un prodotto non coinvolto in 
alcuna vendita. Se più di un prodotto soddisfa la condizione, la funzione restituisce uno qualsiasi di 
essi, altrimenti restituisce -1.
*/
int prodottoInvenduto(VenditeProdotti vp){
    for(int i = 0; i < 5; i++){
        int flag = 0;
        for(int j = 0; j < 8; j++){
            if(vp.vendite[j][0] == i){
                flag = 1;
                break;
            }
        }
        if(!flag){
            return i;
        }
    }
}

void stampaVettore(int* a, int n){
    puts("Stampa del vettore.");
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

// Main
int main(void) {
    VenditeProdotti vp = {
        .prodotti = {
            {"Mouse", "PC", 20, 35},
            {"Spazzolino elettrico", "Elettrodomestici", 35, 70}, 
            {"Notebook", "PC", 5, 500},
            {"TV", "Elettrodomestici", 10, 350},
            {"Monitor", "PC", 20, 200}
        },

        .vendite = {
            {1, 2, 30},
            {2, 1, 550},
            {0, 10, 25},
            {4, 1, 200},
            {0, 3, 35},
            {2, 3, 450},
            {2, 2, 500},
            {1, 1, 35}
        }
    };

    printf("Il valore del magazzino: %d\n", valoreMagazzino(vp));

    int dim;

    int* prodTop = prodottiTop(vp, "PC", 5, &dim);

    stampaVettore(prodTop, dim);

    printf("La categoria piu' redditizia: %s\n", categoriaRedditizia(vp));

    printf("Il prodotto invenduto: %d\n", prodottoInvenduto(vp));

    free(prodTop);

    return 0;
}
