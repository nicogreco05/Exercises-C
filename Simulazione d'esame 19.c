/*
Simulazione d'esame (traccia) - Casa, Cosenza dalle 16:00 alle 16:45

Si vuole realizzare un’applicazione per la gestione dei dati relativi a musicisti e collaborazioni tra di essi. Le informazioni
sono memorizzate in struct aventi la seguente definizione:

typedef struct{
    char nome[20];
    char strumento[20]:
} Musicista;

typedef struct{
    Musicista musicisti[6];
    int collaborazioni[8][4]; // cod_mus_1, cod_mus_2, inizio_anno_coll, fine_anno_coll
} MusicistiCollaborazioni;


Ogni istanza di Musicista rappresenta il fatto che il musicista con nome nome suona lo strumento strumento. Inoltre,
ad ognuno di 6 musicisti è associato un codice intero compreso tra 0 e 5. L'i-esimo elemento dell'array musicisti
contiene l'istanza di Musicista corrispondente al musicista con codice i.
Le informazioni relative alle collaborazioni tra musicisti sono memorizzate in una matrice collaborazioni, la cui i-esima
riga [cod1, cod2, inizio, fine] rappresenta il fatto che il musicista con codice cod1 ha collaborato con il musicista con
codice cod2 dall'anno inizio all'anno fine (inclusi). Si noti che (i) la stessa riga rappresenta anche il fatto che, nello stesso
periodo, il musicista con codice cod2 ha collaborato con il musicista con codice cod1 e (ii) una stessa coppia di musicisti
può aver collaborato in più periodi diversi.
Si scrivano in C le seguenti funzioni (la scrittura di eventuali funzioni ausiliarie è ovviamente ammessa):
• int *numeroCollaborazioni(MusicistiCollaborazioni c) che restituisce un array di lunghezza pari a 6, il cui i-esimo
elemento contiene il numero di collaborazioni che coinvolgono il musicista con codice i.
• int musicistaSimile(MusicistiCollaborazioni c, int cod) che restituisce il codice del musicista che ha collaborato
più a lungo con il musicista con codice cod. Se più di un musicista soddisfa la condizione, la funzione restituisce
il codice di uno qualsiasi di essi.
• int *durateStrumento(MusicistiCollaborazioni c, char strum[20]) che restituisce un array di lunghezza pari a 8,
il cui i-esimo elemento contiene la durata (in anni) della i-esima collaborazione se almeno uno dei due musicisti
suona lo strumento strum, zero altrimenti.
• int musicistaRichiesto(MusicistiCollaborazioni c) che restituisce il codice di un musicista che ha collaborato con
tutti gli altri musicisti. Se più di un musicista soddisfa la condizione, la funzione restituisce il codice di uno
qualsiasi di essi. Se nessun musicista soddisfa la condizione, la funzione restituisce -1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[20];
    char strumento[20];
} Musicista;

typedef struct{
    Musicista musicisti[6];
    int collaborazioni[8][4]; // cod_mus_1, cod_mus_2, inizio_anno_coll, fine_anno_coll
} MusicistiCollaborazioni;

/*
Funzione 1: int *numeroCollaborazioni(MusicistiCollaborazioni c) che restituisce un array di lunghezza pari a 6, il cui i-esimo
elemento contiene il numero di collaborazioni che coinvolgono il musicista con codice i.
*/
int *numeroCollaborazioni(MusicistiCollaborazioni c){
    int* res = (int*) malloc (6 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    for(int i = 0; i < 6; i++){
        int coll = 0;
        for(int j = 0; j < 8; j++){
            int cod1 = c.collaborazioni[j][0];
            int cod2 = c.collaborazioni[j][1];
            if(cod1 == i || cod2 == i){
                coll++;
            }
        }
        res[i] = coll;
    }
    return res;
}

/*
Funzione 2: int musicistaSimile(MusicistiCollaborazioni c, int cod) che restituisce il codice del musicista che ha collaborato
più a lungo con il musicista con codice cod. Se più di un musicista soddisfa la condizione, la funzione restituisce
il codice di uno qualsiasi di essi.
*/
int musicistaSimile(MusicistiCollaborazioni c, int cod){
    int* annicoll = (int*) malloc (6 * sizeof(int));
    if(annicoll == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < 8; i++){
        int cod1 = c.collaborazioni[i][0];
        int cod2 = c.collaborazioni[i][1];
        int inizio = c.collaborazioni[i][2];
        int fine = c.collaborazioni[i][3];
        int durata = fine - inizio;
        if(cod1 == cod){
            annicoll[cod2] += durata;
        }
        else if(cod2 == cod){
            annicoll[cod1] += durata;
        }
    }
    int max_anni_durata = -1;
    int max_index = -1;
    for(int i = 0; i < 6; i++){
        if(annicoll[i] > max_anni_durata){
            max_anni_durata = annicoll[i];
            max_index = i;
        }
    }
    free(annicoll);
    return max_index;
}

/*
Funzione 3: int *durateStrumento(MusicistiCollaborazioni c, char strum[20]) che restituisce un array di lunghezza pari a 8,
il cui i-esimo elemento contiene la durata (in anni) della i-esima collaborazione se almeno uno dei due musicisti
suona lo strumento strum, zero altrimenti.
*/
int* durateStrumento(MusicistiCollaborazioni c, char strum[20]){
    int* res = (int*) malloc (8 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < 8; i++){
        int cod1 = c.collaborazioni[i][0];
        int cod2 = c.collaborazioni[i][1];
        int inizio = c.collaborazioni[i][2];
        int fine = c.collaborazioni[i][3];
        int durata = fine - inizio;
        if(strcmp(c.musicisti[cod1].strumento, strum) == 0 || strcmp(c.musicisti[cod2].strumento, strum) == 0){
            res[i] = durata;
        }
        else{
            res[i] = 0;
        }
    }
    return res;
}

/*
Funzione 4: int musicistaRichiesto(MusicistiCollaborazioni c) che restituisce il codice di un musicista che ha collaborato con
tutti gli altri musicisti. Se più di un musicista soddisfa la condizione, la funzione restituisce il codice di uno
qualsiasi di essi. Se nessun musicista soddisfa la condizione, la funzione restituisce -1.
*/
int musicistaRichiesto(MusicistiCollaborazioni c) {
    for (int i = 0; i < 6; i++) {
        int collaboratori[6] = {0};  // Per segnare con chi ha collaborato
        for (int j = 0; j < 8; j++) {
            int cod1 = c.collaborazioni[j][0];
            int cod2 = c.collaborazioni[j][1];
            if (cod1 == i) {
                collaboratori[cod2] = 1;
            } else if (cod2 == i) {
                collaboratori[cod1] = 1;
            }
        }

        int haCollaboratoConTutti = 1;
        for (int k = 0; k < 6; k++) {
            if (k != i && collaboratori[k] == 0) {
                haCollaboratoConTutti = 0;
                break;
            }
        }

        if (haCollaboratoConTutti) {
            return i;
        }
    }
    return -1;
}