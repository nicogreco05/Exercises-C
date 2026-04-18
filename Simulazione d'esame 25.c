/*
Simulazione d'esame (23/05/25) - Casa, San Gregorio

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
bool magazzinoSufficiente(DatiNegozio dn){
    for (int i = 0; i < 6; i++) {
        bool trovata = false;
        for (int j = 0; j < 5; j++) {
            if (dn.magazzino[j].larghezza >= dn.richieste[i][0] &&
                dn.magazzino[j].altezza >= dn.richieste[i][1]) {
                trovata = true;
                break;
            }
        }
        if (!trovata)
            return false; // almeno una richiesta non può essere soddisfatta
    }
    return true;
}

/*
Funzione 2: int acquistolnBlocco(DatiNegozio dn, int quantita(5]) 
che restituisce il prezzo totale pagato da un cliente che voglia acquistare, per ogni i compreso tra 0 e 4, 
quantita(i] cornici del tipo descritto da magazzino(i].
*/
int acquistoInBlocco(DatiNegozio dn, int quantita[5]){
    int prezzo_totale = 0;
    for(int i = 0; i < 5; i++){
        int prezzo = dn.magazzino[i].prezzo;
        prezzo_totale += quantita[i] * prezzo;
    }
    return prezzo_totale;
}

/*
Funzione 3: char[20] materialeConvenienteRichiesta(DatiNegozio dn, int i) che 
restituisce il materiale in cui è realizzata la più economica delle cornici
che possono soddisfare la richiesta rappresentata nell'i-esima riga della matrice richieste. 
Se più materiali soddisfano la condizione, la funzione resituisce uno qualsiasi di essi.
*/
char materialeConvenienteRichiesta(DatiNegozio dn, int i){
    int altezza = dn.richieste[i][1];
    int largezza = dn.richieste[i][0];
    int* prezzi = (int*) calloc (5, sizeof(int));
    if(prezzi == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int j = 0; j < 5; j++){
        if(dn.magazzino[j].altezza >= altezza && dn.magazzino[j].larghezza >= largezza){
            prezzi[j] = dn.magazzino[j].prezzo;
        }
        else{
            prezzi[j] = -1;
        }
    }
    int min_indice = -1;
    for(int j = 0; j < 5; j++){
        if(prezzi[j] != -1){
            if(prezzi[j] < prezzi[min_indice]){
                min_indice = j;
            }
        }
    }
    free(prezzi);
    return dn.magazzino[min_indice].materiale;
}

/*
Funzione 4: char[20] materialeCostoso(DatiNegozio dn) che, per ogni materiale, 
calcola il prezzo medio delle cornici realizzate in quel materiale e infine restituisce 
il materiale avente il massimo prezzo medio. Se più materiali soddisfano la condizione, la funzione resituisce uno qualsiasi di essi.
*/
char materialeCostoso(DatiNegozio dn){
    char materiale_costoso[20] = "";
    int maxMedia = -1;
    for(int i = 0; i < 5; i++){
        char* mat = dn.magazzino[i].materiale;
        int conta = 0;
        int somma = 0;
        for(int j = 0; j < 5; j++){
            if(strcmp(mat, dn.magazzino[j].materiale) == 0){
                somma += dn.magazzino[j].prezzo;
                conta++;
            }
        }
        if(conta > 0){
            int media = somma / conta;
            if(media > maxMedia){
                maxMedia = media;
                strcpy(materiale_costoso, mat);
            }
        }
    }
    return materiale_costoso;
}