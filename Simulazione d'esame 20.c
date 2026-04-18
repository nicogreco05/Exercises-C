/*
Simulazione d'esame (chatgpt) - Casa, Cosenza 21/06/25 dalle 16:45 alle 17:30

Atleti e Gare

typedef struct {
    char nome[30];
    char disciplina[20];  // es: "nuoto", "corsa", ecc.
} Atleta;

typedef struct {
    Atleta atleti[6];
    int gare[10][4];  // [cod_atleta_1, cod_atleta_2, anno, punteggio_comune]
} ArchivioSportivo;

Funzioni da implementare:
1. int* numeroGare(ArchivioSportivo a)
Restituisce un array di 6 interi, in cui l’i-esimo elemento indica quante gare ha fatto l’atleta con codice i.
2. int* punteggiDisciplina(ArchivioSportivo a, char disciplina[20])
Restituisce un array di 10 interi: l’i-esimo elemento contiene il punteggio della gara i solo se almeno uno dei due atleti pratica quella disciplina, altrimenti contiene zero.
3. int atletaCompleto(ArchivioSportivo a)
Restituisce il codice dell’atleta che ha gareggiato con tutti gli altri 5 almeno una volta.
Se non esiste, restituisce -1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    char disciplina[20];  // es: "nuoto", "corsa", ecc.
} Atleta;

typedef struct {
    Atleta atleti[6];
    int gare[10][4];  // [cod_atleta_1, cod_atleta_2, anno, punteggio_comune]
} ArchivioSportivo;

/*
Funzione 1: int* numeroGare(ArchivioSportivo a)
Restituisce un array di 6 interi, in cui l’i-esimo elemento indica quante gare ha fatto l’atleta con codice i.
*/
int* numeroGare(ArchivioSportivo a){
    int* res = (int*) calloc (6, sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 10; j++){
            int atl1 = a.gare[j][0];
            int atl2 = a.gare[j][1];
            if(atl1 == i || atl2 == i){
                res[i] += 1;
            }
        }
    }
    return res;
}

/*
Funzione 2: int* punteggiDisciplina(ArchivioSportivo a, char disciplina[20])
Restituisce un array di 10 interi: l’i-esimo elemento contiene il punteggio della gara i solo 
se almeno uno dei due atleti pratica quella disciplina, altrimenti contiene zero.
*/
int* punteggiDisciplina(ArchivioSportivo a, char disciplina[20]){
    int* res = (int*) calloc (10, sizeof(int));
        if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < 10; i++){
        int atl1 = a.gare[i][0];
        int atl2 = a.gare[i][1];
        int punteggio = a.gare[i][3];
        if(strcmp(a.atleti[atl1].disciplina, disciplina) == 0 || strcmp(a.atleti[atl2].disciplina, disciplina) == 0){
            res[i] = punteggio;
        }
        else{
            res[i] = 0;
        }
    }
    return res;
}

/*
Funzione 3: int atletaCompleto(ArchivioSportivo a)
Restituisce il codice dell’atleta che ha gareggiato con tutti gli altri 5 almeno una volta.
Se non esiste, restituisce -1.
*/
int atletaCompleto(ArchivioSportivo a){
    for(int i = 0; i < 6; i++){
        int atleti[6] = {0};
        for(int j = 0; j < 10; j++){
            int atl1 = a.gare[j][0];
            int atl2 = a.gare[j][1];
            if(atl1 == i){
                atleti[atl2] = 1;
            }
            else if(atl2 == i){
                atleti[atl1] = 1;
            }
        }
        int colltutti = 1;
        for(int k = 0; k < 6; k++){
            if(k != i && atleti[k] == 0){
                colltutti = 0;
                break;
            }
        }
        if(colltutti){
            return i;
        }
    }
    return -1;
}

/*
Esercizio 2 (traccia)
Si scriva una funzione valutaOccorrenze(int *L1, int *L2, int nL1, int nL2) che riceve in ingresso due array di interi positivi
L1 ed L2 (le cui rispettive lunghezze sono nL1 ed nL2) e restituisce un array avente lunghezza pari ad nL1 il cui i-esimo
elemento contiene:
• L1[i] se il valore L1[i] è presente in L2 un numero di volte pari ad L1[i];
• -1 altrimenti.
Esempio: Se L1 = [2, 1, 3, 5] e L2 = [2, 4, 1, 2, 5, 5, 5, 6, 5, 1, 4, 5] allora la funzione restituisce l'array [2, -1, -1, 5] perché
l’elemento L1[0]=2 compare esattamente 2 volte in L2, l’elemento L1[3]=5 compare esattamente 5 volte in L2, mentre
gli elementi L1[1]=1 ed L1[2]=3 non hanno un numero di occorrenze in L2 pari al loro valore.
*/
int contaOccorrenze(int* a, int l_a, int n){
    int count = 0;
    for(int i = 0; i < l_a; i++){
        if(a[i] == n){
            count++;
        }
    }
    return count;
}

int valutaOccorrenze(int *L1, int* L2, int nL1, int nL2){
    int* res = (int*) malloc (nL1 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < nL1; i++){
        int cnt = contaOccorrenze(L2, nL2, L1[i]);
        if(L1[i] == cnt){
            res[i] = cnt;
        }
        else{
            res[i] = -1;
        }
    }
    return res;
}