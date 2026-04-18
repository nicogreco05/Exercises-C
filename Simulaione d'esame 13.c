/*
Simulazione d'esame (tutor) - Casa, Cosenza dalle 16::00 alle 17:00

Esercizio 3, Struct
Si vuole realizzare un'applicazione per la gestione dei dati relativi a una piattaforma musicale digitale.
Le informazioni sono memorizzate in struct aventi la seguente definizione:
typedef struct {
     char titolo[50];
     char artista[40];
     int genere;         // intero da 0 a 4: 0=Pop, 1=Rock, 2=Jazz, 3=Classica, 4=Elettronica
     int durataSecondi;  // Durata della canzone in secondi
     float valutazioneMedia; // Valutazione media degli utenti (da 0.0 a 5.0)
} Canzone;
 
typedef struct {
     Canzone catalogo[10]; // Numero massimo di canzoni nel catalogo
     // Ciascuna riga: {indiceCanzone, numeroRiproduzioniEffettuate} in una sessione/evento
     int riproduzioniRegistrate[20][2]; // Registra le riproduzioni singole (transazioni)
} PiattaformaMusicale;
 
Ogni istanza di Canzone rappresenta un brano musicale disponibile sulla piattaforma, associato a un genere (valore intero da 0 a 4), alla sua durata in secondi e a una valutazione media assegnata dagli utenti.
Le informazioni relative alle riproduzioni sono contenute nella matrice riproduzioniRegistrate. Ogni riga di questa matrice rappresenta un evento di riproduzione (o una sessione di ascolto) e registra:
indiceCanzone: la posizione nell'array catalogo del brano riprodotto.
numeroRiproduzioniEffettuate: quante volte il brano è stato riprodotto durante quella specifica sessione o evento.
Un brano può comparire più volte nella matrice riproduzioniRegistrate, anche con un numero diverso di riproduzioni per evento.
Scrivere le seguenti funzioni (sono ammessi eventuali metodi ausiliari):
Certamente! Ecco una nuova traccia d'esame in C, con elementi e logiche differenti, incentrata sulla gestione di una Piattaforma Musicale anziché una biblioteca.
 
 
Funzioni da Implementare
float durataTotaleCatalogo(PiattaformaMusicale p) 
Restituisce la durata complessiva (in secondi) di tutte le canzoni presenti nel catalogo della piattaforma.
 
 
int canzoniPiuAscoltate(PiattaformaMusicale p, int sogliaRiproduzioni, int indici[], int* count) 
Restituisce, nell'array indici, gli indici delle canzoni che sono state riprodotte per un numero totale di riproduzioni maggiore o uguale a sogliaRiproduzioni. La variabile count indica il numero di elementi scritti in indici.
 
 
char* generePiuAscoltato(PiattaformaMusicale p) 
Restituisce il nome del genere che ha totalizzato il maggiore numero complessivo di riproduzioni. Per determinare il genere più ascoltato, si sommano le numeroRiproduzioniEffettuate per ciascun brano e si aggregano per genere. (Suggerimento: sarà utile una funzione ausiliaria per mappare gli interi del genere (0-4) ai rispettivi nomi in stringa).
 
 
int canzoneMaiAscoltata(PiattaformaMusicale p) 
Restituisce l'indice di una canzone che non è mai stata riprodotta (cioè non compare mai nella matrice riproduzioniRegistrate). Se più canzoni soddisfano la condizione, si restituisce il primo indice trovato. Se tutte le canzoni sono state riprodotte almeno una volta, si restituisce -1.
 
EXTRA, Implementare una funzione buoneValutazioni(PiattaformaMusicale p) 
che restituisca solo il nome delle canzoni con valutazione superiore a 3.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
     char titolo[50];
     char artista[40];
     int genere;         // intero da 0 a 4: 0=Pop, 1=Rock, 2=Jazz, 3=Classica, 4=Elettronica
     int durataSecondi;
     float valutazioneMedia;
} Canzone;
 
typedef struct {
     Canzone catalogo[10];
     int riproduzioniRegistrate[20][2]; // {indiceCanzone, numeroRiproduzioni}
} PiattaformaMusicale;

// 1. Durata totale catalogo
float durataTotaleCatalogo(PiattaformaMusicale p){
    float somma = 0.0;
    for(int i = 0; i < 10; i++){
        somma += p.catalogo[i].durataSecondi;
    }
    return somma;
}

// 2. Canzoni più ascoltate
int canzoniPiuAscoltate(PiattaformaMusicale p, int sogliaRiproduzioni, int indici[], int* count){
    int riproduzioniTot[10] = {0};

    for(int i = 0; i < 20; i++){
        int idx = p.riproduzioniRegistrate[i][0];
        int num = p.riproduzioniRegistrate[i][1];
        if (idx >= 0 && idx < 10)
            riproduzioniTot[idx] += num;
    }

    *count = 0;
    for(int i = 0; i < 10; i++){
        if(riproduzioniTot[i] >= sogliaRiproduzioni){
            indici[*count] = i;
            (*count)++;
        }
    }
    return *count;
}

// 3. Genere più ascoltato
char* nomeGenere(int codice){
    switch(codice){
        case 0: return "Pop";
        case 1: return "Rock";
        case 2: return "Jazz";
        case 3: return "Classica";
        case 4: return "Elettronica";
        default: return "Sconosciuto";
    }
}

char* generePiuAscoltato(PiattaformaMusicale p){
    int ascoltiPerGenere[5] = {0};

    for(int i = 0; i < 20; i++){
        int idx = p.riproduzioniRegistrate[i][0];
        int num = p.riproduzioniRegistrate[i][1];
        if(idx >= 0 && idx < 10){
            int g = p.catalogo[idx].genere;
            ascoltiPerGenere[g] += num;
        }
    }

    int max = ascoltiPerGenere[0];
    int maxIndex = 0;
    for(int i = 1; i < 5; i++){
        if(ascoltiPerGenere[i] > max){
            max = ascoltiPerGenere[i];
            maxIndex = i;
        }
    }

    char* res = (char*) malloc(20 * sizeof(char));
    if(res == NULL){
        printf("Errore allocazione memoria.\n");
        exit(1);
    }
    strcpy(res, nomeGenere(maxIndex));
    return res;
}

// 4. Canzone mai ascoltata
int canzoneMaiAscoltata(PiattaformaMusicale p){
    int ascoltata[10] = {0};

    for(int i = 0; i < 20; i++){
        int idx = p.riproduzioniRegistrate[i][0];
        if(idx >= 0 && idx < 10){
            ascoltata[idx] = 1;
        }
    }

    for(int i = 0; i < 10; i++){
        if(ascoltata[i] == 0){
            return i;
        }
    }
    return -1;
}

// 5. EXTRA — Buone valutazioni
void buoneValutazioni(PiattaformaMusicale p){
    printf("Canzoni con valutazione > 3.0:\n");
    for(int i = 0; i < 10; i++){
        if(p.catalogo[i].valutazioneMedia > 3.0){
            printf("- %s\n", p.catalogo[i].titolo);
        }
    }
}
