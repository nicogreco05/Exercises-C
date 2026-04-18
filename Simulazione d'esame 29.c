/*
    Simulazione d'esame (tutor) - 08/07/25

    Si vuole realizzare un’applicazione per la gestione delle iscrizioni a corsi universitari.
    Le informazioni sono rappresentate con le seguenti strutture:

    typedef struct {
        char nome[30];
        int cfu;
        int maxStudenti;
        int iscritti;
    } Corso;

    typedef struct {
        char nome[30];
        int matricola;
    } Studente;

    typedef struct {
        Corso corsi[6];
        Studente studenti[5];
        int richieste[5][6]; // richieste[i][j] = 1 se studente i vuole iscriversi al corso j
    } SistemaIscrizione;

    Ogni elemento di richieste[i][j] indica se lo studente i ha richiesto l’iscrizione al corso j (1 = sì, 0 = no).
    Una richiesta può essere accettata solo se il numero di iscritti al corso è inferiore al massimo consentito.


    Scrivere le seguenti funzioni:
    - bool iscrizioniPossibili(SistemaIscrizione s), che restituisce true se tutte le
      richieste possono essere soddisfatte senza superare il numero massimo di studenti per corso.

    - int sommaCfuRichiesti(SistemaIscrizione s), che restituisce la somma dei CFU totali
      dei corsi richiesti da tutti gli studenti, solo se tutte le richieste sono accettabili.
      In caso contrario, restituisce -1.

    - char* corsoPiuRichiesto(SistemaIscrizione s), che restituisce il nome del corso che
      ha ricevuto il maggior numero di richieste.

    - char* corsoConMenoIscritti(SistemaIscrizione s), che restituisce il nome del corso che
      attualmente ha il minor numero di iscritti.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char nome[30];
    int cfu;
    int maxStudenti;
    int iscritti;
} Corso;

typedef struct {
    char nome[30];
    int matricola;
 } Studente;

typedef struct {
    Corso corsi[6];
    Studente studenti[5];
    int richieste[5][6]; // richieste[i][j] = 1 se studente i vuole iscriversi al corso j
} SistemaIscrizione;

/*
Funzione 1: bool iscrizioniPossibili(SistemaIscrizione s), che restituisce true se tutte le
richieste possono essere soddisfatte senza superare il numero massimo di studenti per corso.
*/
bool iscrizioniPossibili(SistemaIscrizione s){
    int richieste_totali[6] = {0};
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){
            if(s.richieste[i][j] == 1){
                richieste_totali[j]++;
            }
        }
    }
    for(int i = 0; i < 6; i++){
        if(s.corsi[i].iscritti + richieste_totali[i] > s.corsi[i].maxStudenti){
            return false;
        }
    }
    return true;
}

/*
Funzione 2: int sommaCfuRichiesti(SistemaIscrizione s), che restituisce la somma dei CFU totali
dei corsi richiesti da tutti gli studenti, solo se tutte le richieste sono accettabili.
In caso contrario, restituisce -1.
*/
int sommaCfuRichiesti(SistemaIscrizione s) {
    if (!iscrizioniPossibili(s)) {
        return -1;
    }

    int somma = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            if (s.richieste[i][j] == 1) {
                somma += s.corsi[j].cfu;
            }
        }
    }

    return somma;
}

/*
Funzione 3: 
*/
char* corsoPiuRichiesto(SistemaIscrizione s) {
    static char corsoRichiesto[30];
    int richiestePerCorso[6] = {0};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            if (s.richieste[i][j] == 1) {
                richiestePerCorso[j]++;
            }
        }
    }

    int maxIndex = 0;
    for (int j = 1; j < 5; j++) {
        if (richiestePerCorso[j] > richiestePerCorso[maxIndex]) {
            maxIndex = j;
        }
    }

    strcpy(corsoRichiesto, s.corsi[maxIndex].nome);
    return corsoRichiesto;
}

/*
Funzione 4: 
*/
char* corsoConMenoIscritti(SistemaIscrizione s) {
    static char corsoMin[30];
    int minIndex = 0;

    for (int j = 1; j < 6; j++) {
        if (s.corsi[j].iscritti < s.corsi[minIndex].iscritti) {
            minIndex = j;
        }
    }

    strcpy(corsoMin, s.corsi[minIndex].nome);
    return corsoMin;
}

