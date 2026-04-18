/*
Simulazione d'esame (23/05/25) - Casa, San Gregorio 09/07/25

Si vuole realizzare un'applicazione per la gestione di dati relativi ad un negozio di cornici. 
Le informazioni sono memorizzate utilizzando struct aventi la seguente definizione:

typedef struct{
    char materiale[20];
    int larghezza;
    int altezza;
    int prezzo;
} Cornice;

typedef struct{
    Cornice magazzino[5];
    int richieste[6][2]; // [larg, alt]
} DatiNegozio;

Ogni istanza di Cornice rappresenta il fatto che sono disponibili (si assuma in numero illimitato) 
cornici realizzate in materiale materiale aventi dimensioni larghezza x altezza e prezzo prezzo.
A ciascuna cornice è assegnato un codice intero compreso tra 0 e 4. 
L'i-esimo elemento dell'array magazzino contiene l'istanza di Cornice relativa alla cornice con codice i.
Le informazioni relative alle richieste sono memorizzate in una matrice richieste la cui i-esima riga [larg, alt] indica 
che è stata richiesta una cornice aventi dimensioni larg x alt.
Una richiesta può essere soddisfatta se in magazzino è presente almeno una cornice avente larghezza e 
altezza maggiori o uguali a quelle indicate nella richiesta.

Si scrivano le seguenti funzioni (la scrittura di eventuali funzioni ausiliarie è sempre ammessa):
bool magazzinoSufficiente(DatiNegozio dn) che restituisce true se e solo se tutte le richieste possono essere soddisfatte

int acquistolnBlocco(DatiNegozio dn, int quantita(5]) 
che restituisce il prezzo totale pagato da un cliente che voglia acquistare, per ogni i compreso tra 0 e 4, 
quantita[i] cornici del tipo descritto da magazzino[i].

char[20] materialeConvenienteRichiesta(DatiNegozio dn, int i) che 
restituisce il materiale in cui è realizzata la più economica delle cornici
che possono soddisfare la richiesta rappresentata nell'i-esima riga della matrice richieste. 
Se più materiali soddisfano la condizione, la funzione resituisce uno qualsiasi di essi.

char[20] materialeCostoso(DatiNegozio dn) che, per ogni materiale, 
calcola il prezzo medio delle cornici realizzate in quel materiale e infine restituisce 
il materiale avente il massimo prezzo medio. Se più materiali soddisfano la condizione, la funzione resituisce uno qualsiasi di essi.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char materiale[20];
    int larghezza;
    int altezza;
    int prezzo;
} Cornice;

typedef struct{
    Cornice magazzino[5];
    int richieste[6][2]; // [larg, alt]
} DatiNegozio;

/*
Funzione 1: bool magazzinoSufficiente(DatiNegozio dn) che restituisce true se e solo se tutte le richieste possono essere soddisfatte
*/
bool magazzinoSufficente(DatiNegozio dn){
    for(int i = 0; i < 6; i++){
        bool soddisfatte = false;
        for(int j = 0; j < 5; j++){
            if(dn.magazzino[j].altezza >= dn.richieste[i][1] && dn.magazzino[j].larghezza >= dn.richieste[i][0]){
                soddisfatte = true;
            }
        }
        if(!soddisfatte){
            return false;
        }
    }
    return true;
}

/*
Funzione 2: int acquistolnBlocco(DatiNegozio dn, int quantita(5]) 
che restituisce il prezzo totale pagato da un cliente che voglia acquistare, per ogni i compreso tra 0 e 4, 
quantita[i] cornici del tipo descritto da magazzino[i].
*/
int acquistoInBlocco(DatiNegozio dn, int quantita[5]){
    int totale = 0;
    for(int i = 0; i < 5; i++){
        totale += quantita[i] * dn.magazzino[i].prezzo;
    }
    return totale;
}

/*
Funzione 3: char[20] materialeConvenienteRichiesta(DatiNegozio dn, int i) che 
restituisce il materiale in cui è realizzata la più economica delle cornici
che possono soddisfare la richiesta rappresentata nell'i-esima riga della matrice richieste. 
Se più materiali soddisfano la condizione, la funzione resituisce uno qualsiasi di essi.
*/
char* materialeConvenienteRichiesta(DatiNegozio dn, int i){
    int altezza = dn.richieste[i][1];
    int larghezza = dn.richieste[i][0];
    static char materiale_conveniente[20];
    int* prezzi = (int*) malloc (5 * sizeof(int));
    for(int i = 0; i < 5; i++){
        if(dn.magazzino[i].altezza >= altezza && dn.magazzino[i].larghezza >= larghezza){
            prezzi[i] = dn.magazzino[i].prezzo;
        }
        else{
            prezzi[i] = -1;
        }
    }
    int min_idx = -1;
    for(int i = 0; i < 5; i++){
        if(prezzi[i] != -1){
            min_idx = i;
            break;
        }
    }
    if(min_idx == -1){
        strcpy(materiale_conveniente, "Nessuna");
        return materiale_conveniente;
    }
    for(int j = min_idx + 1; j < 5; j++){
        if(prezzi[j] != -1 && prezzi[j] < prezzi[min_idx]){
            min_idx = j;

        }

    }
    free(prezzi);
    strcpy(materiale_conveniente, dn.magazzino[min_idx].materiale);
    return materiale_conveniente;
}

/*
Funzione 4: char[20] materialeCostoso(DatiNegozio dn) che, per ogni materiale, 
calcola il prezzo medio delle cornici realizzate in quel materiale e infine restituisce 
il materiale avente il massimo prezzo medio. Se più materiali soddisfano la condizione, la funzione resituisce uno qualsiasi di essi.
*/
char* materialeCostoso(DatiNegozio dn) {
    static char costoso[20] = "";
    int maxMedia = -1;  //Inizializziamo la media massima a -1 per il primo confronto
    for (int i = 0; i < 5; i++) {
        char *mat = dn.magazzino[i].materiale;
        int somma = 0, conta = 0;
        // Calcola somma e numero di cornici con lo stesso materiale
        for (int j = 0; j < 5; j++) {
            if (strcmp(dn.magazzino[j].materiale, mat) == 0) {  //Compariamo i materiali delle cornici con strcmp
                somma += dn.magazzino[j].prezzo;
                conta++;
            }
        }
        //Facciamo la media
        if (conta > 0) {
            int media = somma / conta;
            if (media > maxMedia) {  //Verifichiamo quale materiale ha le cornici che costano mediamente di più
                maxMedia = media;
                strcpy(costoso, mat);
            }
        }
    }
    return costoso;
}