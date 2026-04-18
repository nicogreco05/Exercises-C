/*
Simulazione d'esame (molto simile esame) - Casa, Cosenza dalle 16:00 alle 17:00

Si vuole realizzare un’applicazione per la gestione dei dati relativi a registi e co-produzioni cinematografiche. 
Le informazioni sono memorizzate in struct aventi la seguente definizione:

typedef struct{
    char nome[30];
    char nazionalita[20];
} Regista;

typedef struct{
    Regista registi[6];
    int coproduzioni[10][4]; // cod_reg_1, cod_reg_2, anno_inizio, anno_fine
} ArchivioCinema;

Ogni istanza di Regista rappresenta il fatto che il regista con nome nome è di nazionalità nazionalita. 
Inoltre, a ciascuno dei 6 registi è associato un codice intero compreso tra 0 e 5. 
L’i-esimo elemento dell’array registi contiene l’istanza del regista con codice i.
Le informazioni sulle co-produzioni sono memorizzate nella matrice coproduzioni, 
la cui i-esima riga [cod1, cod2, inizio, fine] indica che il regista cod1 ha co-prodotto film con il regista cod2 nel periodo che va 
da inizio a fine (inclusi). La co-produzione è reciproca, quindi anche cod2 ha co-prodotto con cod1 nello stesso intervallo.
È possibile che due registi abbiano collaborato più volte in anni diversi.

Funzioni da implementare: 
1. int* numeroCoproduzioni(ArchivioCinema a)
Restituisce un array dinamico di 6 interi. L’i-esimo elemento indica quante co-produzioni hanno coinvolto il regista con codice i.

2. int registaAffidabile(ArchivioCinema a, int codice)
Restituisce il codice del regista che ha collaborato più a lungo complessivamente (in anni) con il regista di codice codice.
Se più registi hanno la stessa durata massima, la funzione può restituire uno qualsiasi di essi.

3. int* duratePerNazionalita(ArchivioCinema a, char nazionalita[20])
Restituisce un array di 10 interi. L’i-esimo elemento contiene la durata in anni della i-esima co-produzione solo se almeno uno dei due registi coinvolti ha quella nazionalità, altrimenti contiene zero.

4. int registaInternazionale(ArchivioCinema a)
Restituisce il codice del regista che ha collaborato con tutti gli altri 5 almeno una volta.
Se nessuno soddisfa questa condizione, restituisce -1.
Se più registi la soddisfano, ne restituisce uno qualsiasi.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[30];
    char nazionalita[20];
} Regista;

typedef struct{
    Regista registi[6];
    int coproduzioni[10][4]; // cod_reg_1, cod_reg_2, anno_inizio, anno_fine
} ArchivioCinema;

/*
Funzione 1: int* numeroCoproduzioni(ArchivioCinema a)
Restituisce un array dinamico di 6 interi. L’i-esimo elemento indica quante co-produzioni hanno coinvolto il regista con codice i.
*/
int* numeroCoproduzioni(ArchivioCinema a){
    int* res = (int*) calloc (6, sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < 10; i++){
        int r1 = a.coproduzioni[i][0];
        int r2 = a.coproduzioni[i][1];
        for(int j = 0; j < 6; j++){
            if(r1 == j || r2 == j){
                res[j] += 1;
            }
        }
    }
    return res;
}

/*
Funzione 2: int registaAffidabile(ArchivioCinema a, int codice)
Restituisce il codice del regista che ha collaborato più a lungo complessivamente (in anni) con il regista di codice codice.
Se più registi hanno la stessa durata massima, la funzione può restituire uno qualsiasi di essi.
*/
int registaAffidabile(ArchivioCinema a, int codice){
    int* durate_coll = (int*) calloc (6, sizeof(int));
    if(durate_coll == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < 10; i++){
        int r1 = a.coproduzioni[i][0];
        int r2 = a.coproduzioni[i][1];
        int inizio_coll = a.coproduzioni[i][2];
        int fine_coll = a.coproduzioni[i][3];
        int durata_coll = fine_coll - inizio_coll;
        if(r1 == codice){
            durate_coll[r2] += durata_coll;
        }
        else if(r2 == codice){
            durate_coll[r1] += durata_coll;
        }
    }
    int max_idx = 0;
    for(int i = 1; i < 6; i++){
        if(durate_coll[i] > durate_coll[max_idx]){
            max_idx = i;
        }
    }
    free(durate_coll);
    return max_idx;
}

/*
Funzione 3: int* duratePerNazionalita(ArchivioCinema a, char nazionalita[20])
Restituisce un array di 10 interi. L’i-esimo elemento contiene la durata in anni della i-esima co-produzione solo 
se almeno uno dei due registi coinvolti ha quella nazionalità, altrimenti contiene zero.
*/
int* duratePerNazionalita(ArchivioCinema a, char nazionalita[20]){
    int* res = (int*) calloc (10, sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int k = 0;
    for(int i = 0; i < 10; i++){
        int r1 = a.coproduzioni[i][0];
        int r2 = a.coproduzioni[i][1];
        int inizio_coll = a.coproduzioni[i][2];
        int fine_coll = a.coproduzioni[i][3];
        int durata_coll = fine_coll - inizio_coll;
        if(strcmp(nazionalita, a.registi[r1].nazionalita) == 0 || strcmp(nazionalita, a.registi[r2].nazionalita) == 0){
            res[i] += durata_coll;
        }
    }
    return res;
}

/*
Funzione 4: int registaInternazionale(ArchivioCinema a)
Restituisce il codice del regista che ha collaborato con tutti gli altri 5 almeno una volta.
Se nessuno soddisfa questa condizione, restituisce -1.
Se più registi la soddisfano, ne restituisce uno qualsiasi.
*/
int registaInternazionale(ArchivioCinema a){
    for(int i = 0; i < 6; i++){
        int registi[6] = {0};
        for(int j = 0; j < 10; j++){
            int r1 = a.coproduzioni[j][0];
            int r2 = a.coproduzioni[j][1];
            if(r1 == i){
                registi[r2] = 1;
            }
            else if(r2 == i){
                registi[r1] = 1;
            }
        }
        int coll_tutti = 1;
        for(int k = 0; k < 6; k++){
            if(k != i && registi[k] == 0){
                coll_tutti = 0;
                break;
            }
        }
        if(coll_tutti){
            return i;
        }
    }
    return -1;
}

/*
Esercizio 2: Si scriva una funzione valutaOccorrenze(int *L1, int *L2, int nL1, int nL2) che riceve in ingresso due array 
di interi positivi L1 ed L2 (le cui rispettive lunghezze sono nL1 ed nL2) e restituisce un array avente lunghezza pari ad nL1 
il cui i-esimo elemento contiene: 
L1[i] se il valore L1[i] è presente in L2 un numero di volte pari ad L1[i]; 
-1 altrimenti. 

Esempio: Se L1 = [2, 1, 3, 5] e L2 = [2, 4, 1, 2, 5, 5, 5, 6, 5, 1, 4, 5] 
allora la funzione restituisce l'array [2, -1, -1, 5] perché l’elemento L1[0]=2 compare esattamente 2 volte in L2, 
l’elemento L1[3]=5 compare esattamente 5 volte in L2, mentre gli elementi L1[1]=1 ed L1[2]=3 non hanno un numero 
di occorrenze in L2 pari al loro valore. 
*/
int contaOccorrenzne(int* L1, int nL1, int num){
    int count = 0;
    for(int i = 0; i < nL1; i++){
        if(L1[i] == num){
            count++;
        }
    }
    return count;
}

int valutaOccorrenze(int* L1, int* L2, int nL1, int nL2){
    int* res = (int*) malloc (nL1 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < nL1; i++){
        if(L1[i] == contaOccorrenze(L2, nL2, L1[i])){
            res[i] = L1[i];
        }
        else{
            res[i] = -1;
        }
    }
    return res;
}