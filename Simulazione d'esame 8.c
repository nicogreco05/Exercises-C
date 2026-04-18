/*
Simulazione d'esame (chatgpt) - Casa, San Gregorio 02/06/25 dalle 9:00 alle 11:00

Si vuole realizzare un’applicazione per la gestione di un servizio di noleggio auto. I dati sono organizzati come segue:

typedef struct {
    int codice;              // Codice auto (univoco da 0 a 4)
    char modello[20];        // Modello dell'auto
    char categoria[20];      // Categoria (es. "SUV", "Utilitaria", "Sportiva")
    int prezzoGiornaliero;   // Prezzo per giorno di noleggio
} Auto;

typedef struct {
    Auto autoDisponibili[5];     // Elenco delle auto
    int noleggi[8][3];           // Ogni riga: [codiceAuto, giorniNoleggio, prezzoPagatoTotale]
} NoleggioAuto;

Si implementino le seguenti funzioni:

1.	int valoreAutoDisponibili(NoleggioAuto na)
Restituisce il valore totale delle auto disponibili a noleggio, calcolato come somma dei prezzi giornalieri.
2.	int* autoPopolari(NoleggioAuto na, char categoria[20], int soglia, int* count)
Restituisce un array con i codici delle auto della categoria indicata che sono state noleggiate per un numero totale di giorni superiore a soglia.
 La variabile count è un puntatore dove salvare il numero di auto trovate.
3.	char* categoriaTop(NoleggioAuto na)
Restituisce la categoria di auto che ha generato il maggiore guadagno complessivo dai noleggi.
4.	int autoMaiNoleggiata(NoleggioAuto na)
Restituisce il codice di un’auto mai noleggiata. Se tutte sono state noleggiate almeno una volta, restituisce -1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codice;              // Codice auto (univoco da 0 a 4)
    char modello[20];        // Modello dell'auto
    char categoria[20];      // Categoria (es. "SUV", "Utilitaria", "Sportiva")
    int prezzoGiornaliero;   // Prezzo per giorno di noleggio
} Auto;

typedef struct {
    Auto autoDisponibili[5];     // Elenco delle auto
    int noleggi[8][3];           // Ogni riga: [codiceAuto, giorniNoleggio, prezzoPagatoTotale]
} NoleggioAuto;

/*
Funzione 1: int valoreAutoDisponibili(NoleggioAuto na)
Restituisce il valore totale delle auto disponibili a noleggio, calcolato come somma dei prezzi giornalieri.
*/
int valoreAutoDisponibili(NoleggioAuto na){
    int totale = 0;
    for(int i = 0; i < 5; i++){
        totale += na.autoDisponibili[i].prezzoGiornaliero;
    }
    return totale;
}

/*
Funzione 2: int* autoPopolari(NoleggioAuto na, char categoria[20], int soglia, int* count)
Restituisce un array con i codici delle auto della categoria indicata che sono state noleggiate per un numero totale di giorni superiore a soglia.
La variabile count è un puntatore dove salvare il numero di auto trovate.
*/
int* autoPopolari(NoleggioAuto na, char categoria[20], int soglia, int* count){
    int cnt = 0;
    for(int i = 0; i < 5; i++){
        int tot_giorni = 0;
        if(strcmp(na.autoDisponibili[i].categoria, categoria) == 0){
            for(int j = 0; j < 8; j++){
                if(na.noleggi[j][0] == i){
                    tot_giorni += na.noleggi[j][1];
                }
            }
        }
        if(tot_giorni > soglia){
            cnt++;
        }
    }
    int k = 0;
    *count = cnt;
    int* res = (int*) malloc (cnt * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    for(int i = 0; i < 5; i++){
        int tot_giorni = 0;
        if(strcmp(na.autoDisponibili[i].categoria, categoria) == 0){
            for(int j = 0; j < 8; j++){
                if(na.noleggi[j][0] == i){
                    tot_giorni += na.noleggi[j][1];
                }
            }
        }
        if(tot_giorni > soglia){
            res[k++] = i;
        }
    }
    return res;
}

/*
Funzione 3: char* categoriaTop(NoleggioAuto na)
Restituisce la categoria di auto che ha generato il maggiore guadagno complessivo dai noleggi.
*/
char* categoriaTop(NoleggioAuto na){
    char* categorie[5][20];
    int totali[5] = {0};
    int nCategorie = 0;
    for(int i = 0; i < 5; i++){
        int index = -1;
        for(int k = 0; k < 8; k++){
            if(strcmp(na.autoDisponibili[i].categoria, categorie[k]) == 0){
                index = k;
                break;
            }
        }
        if(index == -1){
            strcpy(categorie[nCategorie], na.autoDisponibili[i].categoria);
            index = nCategorie;
            nCategorie++;
        }
        for(int j = 0; j < 8; j++){
            if(na.noleggi[j][0] == na.autoDisponibili[i].codice){
                totali[index] += na.noleggi[j][1] * na.autoDisponibili[i].prezzoGiornaliero;
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
    char* res = (char*) malloc (20 * sizeof(char));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    strcpy(res, categorie[pos]);
    return res;
}

/*
Funzione 4: int autoMaiNoleggiata(NoleggioAuto na)
Restituisce il codice di un’auto mai noleggiata. Se tutte sono state noleggiate almeno una volta, restituisce -1.
*/
int autoMaiNoleggiata(NoleggioAuto na){
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 8; j++){
            if(na.noleggi[j][0] == i){
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

/*
Esercizio 2

La moda di un array V è l’elemento che compare più volte in V e la sua frequenza fM(V) è il numero di volte 
che la moda compare in V. Si scriva una funzione filtroModa che riceve in ingresso due array di interi L1 ed 
L2,  le  loro  dimensioni  dimL1 e  dimL2,  un  intero k,  ed  un  puntatore  a  intero  dimRes,  e  restituisce  un array 
contenente tutti e soli gli elementi di L1 che compaiano in L2 un numero di volte maggiore o uguale a (fM(L2) – k). 
Il puntatore all’intero dimRes rappresenta il puntatore al numero di elementi inseriti nell’array risultato. 
 
Esempio: Se L1 = [2, 1, 3, 5] e L2 = [2, 2, 1, 2, 5, 5, 5, 6, 5, 1, 4] allora la funzione invocata sugli array L1 ed L2 
con valore di k uguale a 1, restituisce l’array [2, 5] perché la moda di L2 è il valore 5, la sua frequenza è pari a 
4, l’elemento 2 di L1 compare 3  volte in L2 e l’elemento 5 di L1 compare 4 volte in L2, mentre gli elementi 1 
e 3 di L1 non compaiono un numero di volte maggiore o uguale a 3 in L2. A seguito della chiamata, il valore 
all’interno dell’indirizzo del puntatore dimRes sarà 2.
*/
int contaOccorrenze(int* v, int dim, int num){
    int cnt = 0;
    for(int i = 0; i < dim; i++){
        if(v[i] == num){
            cnt++;
        }
    }
    return cnt;
}

int fm(int* V, int dimV){
    int max = -1;
    for(int i = 0; i < dimV; i++){
        int corrente = contaOccorrenze(V, dimV, V[i]);
        if(corrente > max){
            max = corrente;
        }
    }
    return max;
}

int* filtroModa(int* L1, int* L2, int dim1, int dim2, int k, int* dimRes){
    int count = 0;
    for(int i = 0; i < dim1; i++){
        if(contaOccorrenze(L2, dim2, L1[i]) >= fm(L2, dim2) - k){
            count++;
        }
    }
    *dimRes = count;
    int j = 0;
    int* res = (int*) malloc (count * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    for(int i = 0; i < dim1; i++){
        if(contaOccorrenze(L2, dim2, L1[i]) >= fm(L2, dim2) - k){
            res[j++] = L1[i];
        }
    }
    return res;
}

/*
Esercizio 2 - Variante

int* filtroMedia(int* A, int* B, int dimA, int dimB, float soglia, int* dimRes);

La funzione restituisce un array contenente tutti e soli gli elementi di A che compaiono in B con una frequenza 
superiore alla media delle frequenze di tutti gli elementi di B moltiplicata per soglia.

Esempio:
•	A = [1, 2, 3, 4]
•	B = [1, 1, 2, 2, 2, 3]
•	soglia = 1.0 → media freq B = (2+3+1)/3 = 2 → inclusi 1 e 2
•	soglia = 1.5 → soglia effettiva = 3 → incluso solo 2
•	Output con soglia 1.5: [2]
*/
int frequenza(int* A, int dimA, int num){
    int cnt = 0;
    for(int i = 0; i < dimA; i++){
        if(A[i] == num){
            cnt++;
        }
    }
    return cnt;
}

float mediaFrequenze(int* A, int dimA){
    int somma = 0;
    for(int i = 0; i < dimA; i++){
        somma += frequenza(A, dimA, A[i]);
    }
    float media = (float) somma / dimA;
    return media;
}
int* filtroMedia(int* A, int* B, int dimA, int dimB, float soglia, int* dimRes){
    int count = 0;
    float mediaB = mediaFrequenze(B, dimB);
    for(int i = 0; i < dimA; i++){
        int occorrenzeB = frequenza(B, dimB, A[i]);
        if(occorrenzeB > soglia * mediaB){
            count++;
        }
    }
    *dimRes = count;
    int* res = (int*) malloc (count * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione di memoria!");
        exit(1);
    }
    int k = 0;
        for(int i = 0; i < dimA; i++){
        int occorrenzeB = frequenza(B, dimB, A[i]);
        if(occorrenzeB > soglia * mediaB){
            res[k++] = A[i];
        }
    }
    return res;
}