// Simulazione d'esame (esercizi 2) - Casa, Cosenza dalle 17:00 alle 18:00

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Esercizio 1: int* elementiConsecutivi(int* arr, int n);
che riceve un array arr e la sua dimensione n e restituisce un nuovo array dinamico di dimensione n-1 
dove ogni elemento è la differenza in valore assoluto tra l’elemento arr[i] e arr[i+1].
*/
int* elementiConsecutivi(int* arr, int n){
    int dim = n - 1;
    int* res = (int*) malloc (dim * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < dim; i++){
        res[i] = arr[i] - arr[i+1];
        if(res[i] < 0){
            res[i] = res[i] * -1;
        }
    }
    return res;
}

/*
Esercizio 2: int* frequenze(int* arr, int n);
che riceve un array arr di interi positivi e la sua dimensione n, e restituisce un array 
dinamico di dimensione max(arr)+1 (dove max(arr) è il valore massimo in arr).
L’array restituito ha alla posizione i il numero di occorrenze del valore i in arr.
*/
int max(int* arr, int n){
    int max = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

int contaOccorrenze(int* arr, int n, int num){
    int count = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == num){
            count++;
        }
    }
    return count;
}

int* frequenze(int* arr, int n){
    int dim = max(arr, n) + 1;
    int* res = (int*) malloc (dim * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < dim; i++){
        res[i] = contaOccorrenze(arr, n, arr[i]);
    }
    return res;
}

/*
Esercizio 3: int* conteggioValori(int* arr1, int n1, int* arr2, int n2);
che restituisce un array dinamico di lunghezza n1, tale che ogni elemento i indica quante volte il valore arr1[i] compare in arr2.
*/
int contaocc(int* arr, int n, int num){
    int count = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == num){
            count++;
        }
    }
    return count;
}

int* conteggioValori(int* arr1, int* arr2, int n1, int n2){
    int* res = (int*) malloc (n1 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < n1; i++){
        res[i] = contaocc(arr2, n2, arr1[i]);
    }
    return res;
}

/*
Funzione 4: int* valoriConFrequenzaEsatta(int* arr1, int* arr2, int n1, int n2);
che restituisce un array dinamico di lunghezza n1, dove l’elemento i è arr1[i] se compare esattamente arr1[i] volte in arr2, altrimenti -1.
*/
int contaoccorrenze(int* arr, int n, int num){
    int count = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] == num){
            count++;
        }
    }
    return count;
}

int* valoriConFrequenzaEsatta(int* arr1, int* arr2, int n1, int n2){
    int* res = (int*) malloc (n1 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < n1; i++){
        if(arr1[i] == contaoccorrenze(arr2, n2, arr1[i])){
            res[i] = arr1[i];
        }
        else{
            res[i] = -1;
        }
    }
    return res;
}

/*
Esercizio 5: int* selezionaValori(int* A, int* B, int nA, int nB);
La funzione riceve in ingresso:
•	Un array A di nA interi positivi (valori da valutare).
•	Un array B di nB interi positivi (insieme di riferimento).
Restituisce un array dinamico di dimensione nA tale che:
•	L’elemento i dell’array restituito contiene:
•	A[i] se A[i] compare in B almeno A[i] volte;
•	-1 altrimenti.
*/
int* selezionaValori(int* A, int* B, int nA, int nB){
    int* res = (int*) malloc (nA * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < nA; i++){
        if(contaoccorrenze(B, nB, A[i]) >= A[i]){
            res[i] = A[i];
        }
        else{
            res[i] = -1;
        }
    }
    return res;
}