/*
Simulazione d'esame (chatgpt) - 03/05/25 dalle 09:00 alle 

L’università gestisce le informazioni sugli studenti e gli esami superati. I dati sono così organizzati:

typedef struct {
    int matricola;
    char nome[30];
    char corso[30];
} Studente;

typedef struct {
    int matricolaStudente;
    char codiceEsame[10];
    int voto;
} Esame;

Sono disponibili:
• un array studenti[5] con al massimo 5 studenti
• una matrice esami[8] con massimo 8 esami registrati

Funzioni da implementare:
- int* studentiMeritevoli(Studente studenti[], Esame esami[], int soglia, int* count);
Restituisce un array con le matricole degli studenti che hanno una media voti superiore alla soglia.

-char* corsoTop(Studente studenti[], Esame esami[]);
Restituisce il corso di laurea con la media voti più alta (considerando tutti gli studenti del corso).

-int studenteSenzaEsami(Studente studenti[], Esame esami[]);
Restituisce la matricola del primo studente che non ha superato alcun esame, o -1 se non esiste.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricola;
    char nome[30];
    char corso[30];
} Studente;

typedef struct {
    int matricolaStudente;
    char codiceEsame[10];
    int voto;
} Esame;

/*
Funzione 1: int* studentiMeritevoli(Studente studenti[], Esame esami[], int soglia, int* count);
Restituisce un array con le matricole degli studenti che hanno una media voti superiore alla soglia.
*/
int* studentiMeritevoli(Studente studenti[], Esame esami[], int soglia, int* count){
    int temp[5];
    int cnt = 0;
    for(int i = 0; i < 5; i++){
        int somma_voti = 0;
        int n_esami = 0;
        for(int j = 0; j < 8; j++){
            if(esami[j].matricolaStudente == studenti[i].matricola){
                somma_voti += esami[j].voto;
                n_esami++;
            }
        }
        if(n_esami > 0 && (somma_voti / n_esami) > soglia){
            temp[cnt++] = studenti[i].matricola;
        }
    }
    *count = cnt;
    int* res = (int*) malloc (cnt * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    for(int i = 0; i < cnt; i++){
        res[i] = temp[i];

    }
    return res;
}

/*
Funzione 2: char* corsoTop(Studente studenti[], Esame esami[]);
Restituisce il corso di laurea con la media voti più alta (considerando tutti gli studenti del corso).
*/
char* corsoTop(Studente studenti[], Esame esami[]){
    char corsi[10][20];
    int totali[10] = {0};
    int conteggi[10] = {0};
    int nCorsi = 0;
    for(int i = 0; i < 8; i++){
        char* corsoCorrente = NULL;
        for(int j = 0; j < 5; j++){
            if(studenti[j].matricola == esami[i].matricolaStudente){
                corsoCorrente = studenti[j].corso;
                break;
            }
        }
        if(corsoCorrente == NULL){
            continue;
        }
        int index = -1;
        for(int c = 0; c < nCorsi; c++){
            if(strcmp(corsi[c], corsoCorrente) == 0){
                index = c;
                break;
            }
        }
        if(index == -1){
            strcpy(corsi[nCorsi], corsoCorrente);
            totali[nCorsi] = esami[i].voto;
            conteggi[nCorsi] = 1;
            nCorsi++;
        }
        else{
            totali[index] += esami[i].voto;
            conteggi[index]++;
        }
    }
    float max_media = -1.0;
    int posMax = -1;
    for(int i = 0; i < nCorsi; i++){
        float media = (float)totali[i] / conteggi[i];
        if(media > max_media){
            max_media = media;
            posMax = i;
        }
    }
    char* res = (char*) malloc (20 * sizeof(char));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    strcpy(res, corsi[posMax]);
    return res;
}

/*
Funzione 3: int studenteSenzaEsami(Studente studenti[], Esame esami[]);
Restituisce la matricola del primo studente che non ha superato alcun esame, o -1 se non esiste.
*/
int studenteSenzaEsami(Studente studenti[], Esame esami[]){
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 8; j++){
            if(studenti[i].matricola == esami[j].matricolaStudente){
                trovato = 1;
            }
        }
        if(!trovato){
            return studenti[i].matricola;
        }
    }
    return -1;
}

/*
Esercizio 2

Scrivi una funzione:

int* sommaFinestra(int* A, int dimA, int k, int* dimRes);
La funzione restituisce un array contenente la somma di ogni finestra consecutiva di k elementi in A.

Esempio:
• A = [1, 2, 3, 4, 5], k = 3
• Finestre: [1+2+3], [2+3+4], [3+4+5]
• Output: [6, 9, 12]
*/
int* sommaFinestra(int* A, int dimA, int k, int* dimRes) {
    if (k > dimA || k <= 0) {
        *dimRes = 0;
        return NULL;  // Se la finestra è più grande dell'array o k non valido
    }
    *dimRes = dimA - k + 1;
    int* result = (int*)malloc((*dimRes) * sizeof(int));
    if (result == NULL) {
        *dimRes = 0;
        return NULL; // Fallimento allocazione memoria
    }
    // Calcolo la somma della prima finestra
    int sum = 0;
    for (int i = 0; i < k; i++) {
        sum += A[i];
    }
    result[0] = sum;
    // Calcolo le somme delle finestre successive usando la somma precedente
    for (int i = 1; i < *dimRes; i++) {
        sum = sum - A[i - 1] + A[i + k - 1];
        result[i] = sum;
    }
    return result;
}