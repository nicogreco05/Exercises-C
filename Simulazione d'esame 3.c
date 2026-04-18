/*
Simulazione esame (chatgpt) - Casa, San Gregorio, 26/05/25 dalle 11:00 alle 12:00
Dopo averlo fatto:
Funzione 1 --> ok ma bisogna lavorarci
Funzione 2 --> impossibile
Funzione 3 --> difficile
Funzione 4 --> ok

Si vuole sviluppare un’applicazione per gestire le informazioni relative agli esami universitari.
Ogni esame è rappresentato dalla seguente struttura:

typedef struct {
    char nomeEsame[30];
    char docente[30];
    int cfu;
} Esame;

int risultati[8][3]
Ogni riga rappresenta un esame sostenuto da uno studente e ha la forma [codiceEsame, voto, matricola]:
•codiceEsame: valore tra 0 e 4 (indice nell’array degli esami)
•voto: voto ottenuto (18–30, o 0 se bocciato)
•matricola: numero identificativo dello studente

Funzioni da implementare:
1.int totaleCFU(GestioneEsami g, int matricola):
Restituisce il totale dei CFU ottenuti da uno studente (escludendo i voti 0 = bocciature).
2.int* esamiSuperatiDaTutti(GestioneEsami g, int* count):
Restituisce un array con i codici degli esami superati da tutti gli studenti che li hanno sostenuti (nessuna bocciatura).
count è il puntatore al numero di elementi restituiti.
3.char* docenteConMediaPiuAlta(GestioneEsami g):
Restituisce il nome del docente la cui media dei voti (escludendo le bocciature) è più alta.
4.int esameMaiSostenuto(GestioneEsami g):
Restituisce il codice di un esame mai sostenuto da nessuno. Se tutti sono stati sostenuti, restituisce -1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nomeEsame[30];
    char docente[30];
    int cfu;
} Esame;

typedef struct {
    Esame esami[5];
    int risultati[8][3]; // [codiceEsame, voto, matricola]
} GestioneEsami;

/*
Funzione 1: int totaleCFU(GestioneEsami g, int matricola):
Restituisce il totale dei CFU ottenuti da uno studente (escludendo i voti 0 = bocciature).
*/
int totaleCFU(GestioneEsami g, int matricola){
    int cfu_totali = 0;
    for(int i = 0; i < 8; i++){
        if(g.risultati[i][2] == matricola && g.risultati[i][1] > 0){
            int codiceEsame = g.risultati[i][0];
            if(codiceEsame >= 0 && codiceEsame <= 4){
                cfu_totali += g.esami[codiceEsame].cfu;
            }
        }
    }
    return cfu_totali;
}

/*
Funzione 2: int* esamiSuperatiDaTutti(GestioneEsami g, int* count):
Restituisce un array con i codici degli esami superati da tutti gli studenti che li hanno sostenuti (nessuna bocciatura).
count è il puntatore al numero di elementi restituiti.
*/
int* esamiSuperatiDaTutti(GestioneEsami g, int* count){
    int studenti[100] = {0}; // supponiamo ci siano max 100 studentu diversi
    int numStudenti = 0;
    // Trovo tutte le matricole distinte
    for(int i = 0; i < 8; i++){
        int m = g.risultati[i][2];
        int trovato = 0;
        for(int j = 0; j < numStudenti; j++){
            if(studenti[j] == m){
                trovato = 1;
                break;
            }
        }
        if(!trovato){
            studenti[numStudenti] = m;
            numStudenti++;
        }
    }
    int esamiComuni[5] = 0;
    for(int i = 0; i < 5; i++){
        int superatoDaTutti = 1;
        for(int s = 0; s < numStudenti; s++){
            int trovato = 0;
            for(int j = 0; j < 8; j++){
                if(g.risultati[j][0] == i && g.risultati[j][2] == studenti[s] && g.risultati[j][1] > 0){
                    trovato = 1;
                    break;
                }

            }
            if(!trovato){
                superatoDaTutti = 0;
                break;
            }
        }
        esamiComuni[i] = superatoDaTutti;
    }
    // conto quanti esami sono stati superati da tutti
    *count = 0;
    for(int i = 0; i < 5; i++){
        if(esamiComuni[i]){
            *count++;
        }
    }
    int *res = malloc(*count * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int k = 0;
    for(int j = 0; j < 5; j++){
        if(esamiComuni[j]){
            res[k] = j;
            k++;
        }
    }
    return res;
}

/*
Funzione 3: char* docenteConMediaPiuAlta(GestioneEsami g):
Restituisce il nome del docente la cui media dei voti (escludendo le bocciature) è più alta.
*/
char* docenteConMediaPiuAlta(GestioneEsami g){
    int conteggi[5] = {0};
    for(int i = 0; i < 8; i++){
        int codiceEsame = g.risultati[i][0];
        int voto = g.risultati[i][1];
        if(voto > 0 && codiceEsame >= 0 && codiceEsame >= 4){
            conteggi[codiceEsame]++;
        }
    }
    int max_i = 0;
    for(int i = 1; i < 5; i++){
        if(conteggi[i] > max_i){
            max_i = i;
        }
    }
    return g.esami[max_i].docente;
}

/*
Funzione 4: int esameMaiSostenuto(GestioneEsami g):
Restituisce il codice di un esame mai sostenuto da nessuno. Se tutti sono stati sostenuti, restituisce -1.
*/
int esameMaiSostenuto(GestioneEsami g){
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 8; j++){
            if(g.risultati[j][0] == i){
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