/*
// BIBLIOTECA, 20/05/25 DALLE 14:00 ALLE 15:30

Esercizio tipo esame - Gestione Prodotti e Vendite

Avendo le seguenti strutture dati:

typedef struct {
    int id;
    char nome[50];
    float prezzo;
} Prodotto;

typedef struct {
    int id_prodotto;
    int quantita_venduta;
} VenditaProdotto;

Scrivere le seguneti funzioni:

-Prodotto *prodotti_piu_venduti(Prodotto *prodotti, int n_prodotti, VenditaProdotto *vendite, int n_vendite, int *n_risultati) che:
  -calcolare la quantità totale venduta per ogni prodotto (sommando tutte le vendite con lo stesso id_prodotto)
  -trovare il numero massimo di vendite
  -restituire un array dinamico di Prodotto che contiene tutti i prodotti che hanno raggiunto quel massimo 
  -impostare *n_risultati con il numero di prodotti piu venduti trovati
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char nome[50];
    float prezzo;
} Prodotto;

typedef struct {
    int id_prodotto;
    int quantita_venduta;
} VenditaProdotto;

Prodotto *prodotti_piu_venduti(Prodotto *prodotti, int n_prodotti, VenditaProdotto *vendite, int n_vendite, int *n_risultati) {
    // Alloca spazio per tenere traccia delle quantità vendute per ogni prodotto
    int *quantita_totale = calloc(n_prodotti, sizeof(int)); // inizializzo a 0
    if (quantita_totale == NULL) {
        printf("Errore di memoria!\n");
        exit(1);
    }
    // Calcola le quantità totali per ogni prodotto
    for (int i = 0; i < n_vendite; i++) {
        for (int j = 0; j < n_prodotti; j++) {
            if (vendite[i].id_prodotto == prodotti[j].id) {
                quantita_totale[j] += vendite[i].quantita_venduta;
            }
        }
    }
    // Trova la quantità massima
    int max = 0;
    for (int i = 0; i < n_prodotti; i++) {
        if (quantita_totale[i] > max) {
            max = quantita_totale[i];
        }
    }
    // Conta quanti prodotti hanno la quantità massima
    int count = 0;
    for (int i = 0; i < n_prodotti; i++) {
        if (quantita_totale[i] == max) {
            count++;
        }
    }
    // Alloca spazio per i prodotti più venduti
    Prodotto *risultato = malloc(count * sizeof(Prodotto));
    if (risultato == NULL) {
        printf("Errore di memoria!\n");
        exit(1);
    }
    // Copia i prodotti con quantità massima nell’array risultato
    int index = 0;
    for (int i = 0; i < n_prodotti; i++) {
        if (quantita_totale[i] == max) {
            risultato[index++] = prodotti[i];
        }
    }
    *n_risultati = count;
    // Libera la memoria temporanea
    free(quantita_totale);
    return risultato;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------- //

/*
CASA (COSENZA), 21/05/25 DALLE 18:30 ALLE 20:00

Esercizio tipo esame - Gestione Prodotti e Vendite
Avendo le seguenti strutture dati:

typedef struct {
    int id;
    char nome[50];
} Prodotto;

typedef struct {
    int id_prodotto;
    int quantita;
} Vendita;

Scrivere le seguenti funzioni:

-Prodotto* prodotto_piu_venduto(Prodotto *prodotti, int n_prodotti, Vendita *vendite, int n_vendite):
 la funzione deve restituire un puntatore al prodotto che ha totalizzato più vendite (cioe la somma delle quantità vendute con quell'id_prodotto)

-Prodotto** prodotti_sopra_media(Prodotto *prodotti, int n_prodotti, Vendita *vendite, int n_vendite, int *n_risultati):
 -Calcolare la quantità totale venduta di ogni prodotto.
 -Calcolare la media di tutte le quantità vendute.
 -Restituire un array dinamico di puntatori a Prodotto, contenente solo quelli che hanno venduto più della media.
 -Scrivere in *n_risultati quanti prodotti ci sono nell’array restituito.

-Prodotto** prodotti_mai_venduti(Prodotto *prodotti, int n_prodotti, Vendita *vendite, int n_vendite, int *n_risultati):
restituisce un array di puntatori a Prodotto che non sono mai stati venduti (cioe il cui id non compare in nessuna vendita)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char nome[50];
} Prodotto;

typedef struct {
    int id_prodotto;
    int quantita;
} Vendita;

// Funzione 1
Prodotto* prodotto_piu_venduto(Prodotto *prodotti, int n_prodotti, Vendita *vendite, int n_vendite){
    // creo un array per inseire le quantità totali per ogni prdotto
    int* quantita_totale = calloc(n_prodotti, sizeof(int));
    if(quantita_totale == NULL){
        printf("Errore di allocazione della memoria!\n");
        return NULL;
    }
    // Calcola la quantità totale venduta per ogni prodotto
    for(int i = 0; i < n_vendite; i++){
        for(int j = 0; j < n_prodotti; j++){
            if(vendite[i].id_prodotto == prodotti[j].id){
                quantita_totale[j] += vendite[i].quantita;
                break;
            }
        }
    }
    // Trova il prodotto con la quantità massima venduta
    int indice_max = 0;
    for(int i = 1; i < n_prodotti; i++){
        if(quantita_totale[i] > quantita_totale[indice_max]){
            indice_max = i;
        }
    }
    free(quantita_totale);
    return &prodotti[indice_max];
}

// Funzione 2
/*
-Prodotto** prodotti_sopra_media(Prodotto *prodotti, int n_prodotti, Vendita *vendite, int n_vendite, int *n_risultati):
 -Calcolare la quantità totale venduta di ogni prodotto.
 -Calcolare la media di tutte le quantità vendute.
 -Restituire un array dinamico di puntatori a Prodotto, contenente solo quelli che hanno venduto più della media.
 -Scrivere in *n_risultati quanti prodotti ci sono nell’array restituito.
*/
Prodotto** prodotti_sopra_media(Prodotto *prodotti, int n_prodotti, Vendita *vendite, int n_vendite, int *n_risultati){
    // creo un array per contare le quantita per ogni prdotto
    int *quantita_totale_per_ogni_prodotto = calloc(n_prodotti, sizeof(int));
    if(quantita_totale_per_ogni_prodotto == NULL){
        printf("Erroe nell'allocazione della memoria");
    }
    for(int i = 0; i < n_prodotti; i++){
        for(int j = 0; j < n_vendite; j++){
            if(prodotti[i].id == vendite[j].id_prodotto){
                quantita_totale_per_ogni_prodotto[i] += vendite[j].quantita; 
            }
        }
    }
    // mi creo una variabile somma inizializza a 0, a cui sommo le quantita per ogni prodotto
    int somma = 0;
    for(int i = 0; i < n_prodotti; i++){
        somma += quantita_totale_per_ogni_prodotto[i];
    }
    // calcolo la media
    int media = somma / n_prodotti;
    // inizializzo a 0 il count e..
    int count = 0;
    // ...per ogni quantita per prodotto maggiore della media aumento il count di 1
    for(int i = 0; i < n_prodotti; i++){
        if(quantita_totale_per_ogni_prodotto[i] > media){
            count++;
        }
    }
    // mi creo un array di prodotti 
    Prodotto** risultati = malloc(count * sizeof(Prodotto*));
    if(risultati == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    // popolo l'array con i prdotti che hanno quanti maggiore della media 
    int  k = 0;
    for(int i = 0; i < n_prodotti; i++){
        if(quantita_totale_per_ogni_prodotto[i] > media){
            risultati[k] = &prodotti[i];
            k++;
        }
    }
    // metto in int* n_risultati il numero di prodotti che hanno quantita maggiore della media
    *n_risultati = count;
    // libero la memoria delle quantita per prodotto (non mi serve piu)
    free(quantita_totale_per_ogni_prodotto);
    // restituisco i prodotti con quantita maggiore della media
    return risultati;
}

// Funzione 3
/*
-Prodotto** prodotti_mai_venduti(Prodotto *prodotti, int n_prodotti, Vendita *vendite, int n_vendite, int *n_risultati):
restituisce un array di puntatori a Prodotto che non sono mai stati venduti (cioe il cui id non compare in nessuna vendita)
*/
Prodotto** prodotti_mai_venduti(Prodotto *prodotti, int n_prodotti, Vendita *vendite, int n_vendite, int *n_risultati){
    // inizilizzo un count e un trovato per numerare i prodotti non venduti ed itero i Prodotti
    int count = 0;
    for(int i = 0; i < n_prodotti; i++){
        int trovato = 0;
        for(int j = 0; j < n_vendite; j++){
            if(prodotti[i].id == vendite[j].id_prodotto){
                trovato = 1;
            }
        }
        if(!trovato){
            count++;
        }
    }
    // mi creo l'array dei prodotti mai venduti 
    Prodotto** prod_mai_venduti = malloc(count * sizeof(Prodotto*));
    if(prod_mai_venduti == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    // popolo l'array
    int k = 0;
    for(int i = 0; i < n_prodotti; i++){
        int trovato = 0;
        for(int j = 0; j < n_vendite; j++){
            if(prodotti[i].id == vendite[j].id_prodotto){
                trovato = 1;
            }
        }
        if(!trovato){
            prod_mai_venduti[k] = &prodotti[i];
            k++;
        }
    }
    // metto in int* n_risultati il numero di prodotti che non sono mai stati venduti
    *n_risultati = count;
    // resituisco l'array con i prodotti mai venduti
    return prod_mai_venduti;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------- //

/*
CASA (SAN GREGORIO), 23/05/25 DALLE 12:00 ALLE 14:00

Esercizio tipo esame - Gestione Prodotti e Vendite

Avendo le seguenti strutture dati:

typedef struct {
    int id;
    char nome[50];
} Studente;

typedef struct {
    int id_studente;
    char materia[30];
    int voto; // da 18 a 30
} Esame;

Scrivere le seguenti funzioni:
-Restituire lo studente con la media più alta.
-Elencare gli studenti che hanno sostenuto almeno un esame.
-Elencare gli studenti che non hanno mai fatto esami.
-Trovare tutti gli esami con voto perfetto (30).
-Restituire la lista degli studenti con media sopra la media generale.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char nome[50];
} Studente;

typedef struct {
    int id_studente;
    char materia[30];
    int voto; // da 18 a 30
} Esame;

// Funzione 1: restituire lo studente con la media più alta.
char* studente_migliore(Studente *studenti, int n_studenti, Esame *esami, int n_esami){
    // mi creo 2 array, uno dove sommo i voti e uno dove conti gli esami
    float* somma_voti = calloc(n_studenti, sizeof(float));
    int* numero_esami = calloc(n_studenti, sizeof(int));
    // faccio il classico ciclo
    for(int i = 0; i < n_studenti; i++){
        for(int j = 0; j < n_esami; j++){
            if(studenti[i].id == esami[j].id_studente){
                // aggiungo e sommo all'array i voti
                somma_voti[i] += esami[j].voto;
                // aumento il count degli esami
                numero_esami[i]++;
            }
        }
    }
    // Calcolo della media
    // inizializzo una max_media e un indice_migliore
    float max_media = -1;
    int indice_migliore = -1;
    // ciclo per ogni studente
    for(int i = 0; i < n_studenti; i++){
        // se questo studente ha almeno un esame vado avanti...
        if(numero_esami[i] > 0){
            // ...calcolo la media
            float media = somma_voti[i] / numero_esami[i];
            // se la media è maggiore di max_media allora aggirono il tutto
            if(media > max_media){
                max_media = media;
                indice_migliore = i;
            }
        }
    }
    // pulisco la memoria
    free(somma_voti);
    free(numero_esami);
    // ritorno lo studente con la media maggiore 
    return studenti[indice_migliore].nome;
}

// Funzione 2: elencare gli studenti che hanno sostenuto almeno un esame.
Studente** studenti_con_almeno_un_esame(Studente *studenti, int n_studenti, Esame *esame, int n_esami){
    // inizializzo un count per contare quanti studenti hanno fatto almeno un esame
    int count = 0;
    for(int i = 0; i < n_studenti; i++){
        // inizializzo un trovato
        int trovato = 0;
        for(int j = 0; j < n_esami; j++){
            // se quello student si trova nella struct esami allora ha sostenuto almeno un esame...
            if(studenti[i].id == esame[j].id_studente){
                // ...e aggirno trovato ad 1 
                trovato = 1;
            }
        }
        // se trovato ce allora aumento il count
        if(trovato){
            count++;
        }
    }
    // inizializzo l'array che avra un numero di elementi pari a count
    Studente** studenti_min_un_esame = malloc(count * sizeof(Studente*));
    if(studenti_min_un_esame == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    // popolo l'array (vedendo come prima se lo studente ha sostenuto un esame)
    int k = 0;
    for(int i = 0; i < n_studenti; i++){
        int trovato = 0;
        for(int j = 0; j < n_esami; j++){
            if(studenti[i].id == esame[j].id_studente){
                trovato = 1;
            }
        }
        // se lo ha sostenuto allora...
        if(trovato){
            // ...aggiungo l'indirizzo dello studente all'array creato prima
            studenti_min_un_esame[k] = &studenti[i];
            // aumento k di 1 alla volta per passare all'elemento successivo
            k++;
        }
    }
    // ritorno l'array con gli studenti che hanno sostenuto almeno un esame
    return studenti_min_un_esame;
}

// Funzione 3: elencare gli studenti che non hanno mai fatto esami.
Studente** studenti_mai_esami(Studente *studenti, int n_studenti, Esame *esame, int n_esami){
    // inizializzo un count
    int count = 0;
    for(int i = 0; i < n_studenti; i++){
        // inizializzo un trovato
        int trovato = 0;
        for(int j = 0; j < n_esami; j++){
            // se quello student eha sostenuto un esame allora aggirono trovato
            if(studenti[i].id == esame[j].id_studente){
                trovato = 1;
            }
        }
        // se è diveso da trovato aumento il count
        if(!trovato){
            count++;
        }
    }
    // creo l'array da restituire
    Studente** studenti_mai_sost_esami = malloc(count * sizeof(Studente*));
    if(studenti_mai_sost_esami == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    // faccio la stessa cosa di prima
    int k = 0;
    for(int i = 0; i < n_studenti; i++){
        int trovato = 0;
        for(int j = 0; j < n_esami; j++){
            if(studenti[i].id == esame[j].id_studente){
                trovato = 1;
            }
        }
        // se è diverso da trovato...
        if(!trovato){
            // ...aggiungo quello studente all'array
            studenti_mai_sost_esami[k] = &studenti[i];
            k++;
        }
    }
    // ritorno l'array popolato
    return studenti_mai_sost_esami;
}

// Funzione 4: trovare tutti gli esami con voto perfetto (30).
Esame** esami_30(Esame *esame, int n_esami){
    // inizalizzo un count
    int count = 0;
    // ciclo sugli esami
    for(int i = 0; i < n_esami; i++){
        // se quell'esame ha un voto di 30...
        if(esame[i].voto == 30){
            // ...aumento il count
            count++;
        }
    }
    // creo l'array dove metterò gli esami con 30
    Esame** esami_con_30 = malloc(count * sizeof(Esame*));
    if(esami_con_30 == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int k = 0;
    // ciclo sugli esami
    for(int i = 0; i < n_esami; i++){
        // se quell'esame ha 30...
        if(esame[i].voto == 30){
            // ...lo aggiungo all'array
            esami_con_30[k] = &esame[i];
            k++;
        }
    }
    // ritorno gli esami con 30
    return esami_con_30;
}

// Funzione 5: restituire la lista degli studenti con media sopra la media generale.
Studente** studenti_sopra_la_media_generale(Studente *studenti, int n_studenti, Esame *esame, int n_esami, int* num){
    // inizializzo 2 variabili, una per somma i voti e una per contare gli esami (per poi fare la media)
    int somma_voti = 0;
    int count_esami = 0;
    // ciclo per ogni esame
    for(int i = 0; i < n_esami; i++){
        // sommo i voti e aggiorno il counter
        somma_voti += esame[i].voto;
        count_esami++;
    }
    // calcolo la media generale
    float media_generale = (float)somma_voti / count_esami;

    // mi creo 2 array, uno per la somma dei voti e uno per il numero di esami --> array perche lo faccio per ogni studente
    float* somma_voti_2 = calloc(n_studenti, sizeof(float));
    int* numero_esami_2 = calloc(n_studenti, sizeof(int));
    for(int i = 0; i < n_studenti; i++){
        for(int j = 0; j < n_esami; j++){
            if(studenti[i].id == esame[j].id_studente){
                // sommo i voti e aggiorno il counter (per ogni studente)
                somma_voti_2[i] += esame[j].voto;
                numero_esami_2[i]++;
            }
        }
    }
    // mi conto quanti studenti hanno la media maggiore della generale
    int count = 0;
    for(int i = 0; i < n_studenti; i++){
        // se ha almeno un esame...
        if(numero_esami_2[i] > 0){
            // ...mi calcolo la media
            float media = somma_voti_2[i] / numero_esami_2[i];
            // se ha la media maggiore della generale...
            if(media > media_generale){
                // ...aggiorno il counter
                count++;
            }
        }
    }
    // mi creo l'array da restituire con gli studenti --> array composto da counter elementi
    Studente** studenti_perfetti = malloc(count * sizeof(Studente*));
    if(studenti_perfetti == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    // popolo l'array (facendo la stessa cosa di prima per calcolare la media per studente)
    int k = 0;
    for(int i = 0; i < n_studenti; i++){
        if(numero_esami_2[i] > 0){
            float media = somma_voti_2[i] / numero_esami_2[i];
            // se la media è maggiore della generale
            if(media > media_generale){
                // ...aggiungo lo studente all'array
                studenti_perfetti[k] = &studenti[i];
                k++;
            }
        }
    }
    // libero la memoria di somma_voti_2 e numero_esami_2 perche non sono piu utili alla fine del programma
    free(somma_voti_2);
    free(numero_esami_2);
    // aggiorno il numero degli studenti che hanno media maggiore della generlae
    *num = count;
    // restituisco gli studenti_perfetti (ovvero quelli con media sopra la generale)
    return studenti_perfetti;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------- //

/*
CASA (SAN GREGORIO), 23/05/25 DALLE 16:00 ALLE 17:00

Simulazione d'esame - traccia di febbraio 2025

Si vuole realizzare un’applicazione per la gestione dei dati relativi a musicisti e collaborazioni tra di essi. 
Le informazioni sono memorizzate in struct aventi la seguente definizione: 

typedef struct  
{  char nome[20]; 
   char strumento[20];     
} Musicista; 

typedef struct  
{   Musicista musicisti[6]; 
    int collaborazioni[8][4]; 
} MusicistiCollaborazioni; 

Si scrivano in C le seguenti funzioni (la scrittura di eventuali funzioni ausiliarie è ovviamente ammessa): 

-int *numeroCollaborazioni(MusicistiCollaborazioni c) che restituisce un array di lunghezza pari a 6, 
il cui i-esimo elemento contiene il numero di collaborazioni che coinvolgono il musicista con codice i. 

-int musicistaSimile(MusicistiCollaborazioni c, int cod) 
che restituisce il codice del musicista che ha collaborato più a lungo con il musicista con codice cod. 
Se più di un musicista soddisfa la condizione, la funzione restituisce il codice di uno qualsiasi di essi. 

-int *durateStrumento(MusicistiCollaborazioni c, char strum[20]) 
che restituisce un array di lunghezza pari a 8, 
il cui i-esimo elemento contiene la durata (in anni) della i-esima collaborazione 
se almeno uno dei due musicisti suona lo strumento strum,  zero altrimenti. 

-int musicistaRichiesto(MusicistiCollaborazioni c) 
che restituisce il codice di un musicista che ha collaborato con tutti gli altri musicisti. 
Se più di un musicista soddisfa la condizione, la funzione restituisce il codice di uno qualsiasi di essi. 
Se nessun musicista soddisfa la condizione, la funzione restituisce -1. 
*/

typedef struct{
    char nome[20]; 
    char strumento[20];
} Musicista; 

typedef struct{
    Musicista musicisti[6]; 
    int collaborazioni[8][4]; 
} MusicistiCollaborazioni;

/*
Funzione 1: int *numeroCollaborazioni(MusicistiCollaborazioni c) che restituisce un array di lunghezza pari a 6, 
il cui i-esimo elemento contiene il numero di collaborazioni che coinvolgono il musicista con codice i. 
*/
int *numeroCollaborazioni(MusicistiCollaborazioni c){
    int *array_res = malloc(6 * sizeof(int));
    if(array_res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < 8; i++){
        int m1 = c.collaborazioni[i][0];
        int m2 = c.collaborazioni[i][1];
        array_res[m1]++;
        array_res[m2]++;
    }
    return array_res;
}

/*
Funzione 2: int musicistaSimile(MusicistiCollaborazioni c, int cod) 
che restituisce il codice del musicista che ha collaborato più a lungo con il musicista con codice cod. 
Se più di un musicista soddisfa la condizione, la funzione restituisce il codice di uno qualsiasi di essi.
*/
int musicistaSimile(MusicistiCollaborazioni c, int cod){
    int durata[6] = {0};
    for (int i = 0; i < 8; i++){
        int m1 = c.collaborazioni[i][0];
        int m2 = c.collaborazioni[i][1];
        int inizio = c.collaborazioni[i][2];
        int fine = c.collaborazioni[i][3];
        int anni = fine - inizio;
        if (m1 == cod){
            durata[m2] += anni;
        }else if (m2 == cod) {
            durata[m1] += anni;
        }
    }
    int max = -1;
    int simile = -1;
    for (int i = 0; i < 6; i++){
        if (i != cod && durata[i] > max){
            max = durata[i];
            simile = i;
        }
    }
    return simile;
}

/*
Funzione 3: int *durateStrumento(MusicistiCollaborazioni c, char strum[20]) 
che restituisce un array di lunghezza pari a 8, 
il cui i-esimo elemento contiene la durata (in anni) della i-esima collaborazione 
se almeno uno dei due musicisti suona lo strumento strum,  zero altrimenti. 
*/
int *durateStrumento(MusicistiCollaborazioni c, char strum[20]){
    int *res = malloc(8 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    for(int i = 0; i < 8; i++){
        int m1 = c.collaborazioni[i][0];
        int m2 = c.collaborazioni[i][1];
        int inizio = c.collaborazioni[i][2];
        int fine = c.collaborazioni[i][3];
        if(strcmp(c.collaborazioni[m1],strum) == 0 || strcmp(c.collaborazioni[m2],strum) == 0){
            res[i] = fine - inizio;
        }
    }
    return res;
}

/*
Funzione 4: int musicistaRichiesto(MusicistiCollaborazioni c) 
che restituisce il codice di un musicista che ha collaborato con tutti gli altri musicisti. 
Se più di un musicista soddisfa la condizione, la funzione restituisce il codice di uno qualsiasi di essi. 
Se nessun musicista soddisfa la condizione, la funzione restituisce -1. 
*/
int musicistaRichiesto(MusicistiCollaborazioni c){
    int collab[6][6] = {0};
    for(int i = 0; i < 8; i++){
        int m1 = c.collaborazioni[i][0];
        int m2 = c.collaborazioni[i][1];
        collab[m1][m2] = 1;
        collab[m2][m1] = 1;
    }
        for(int i = 0; i < 6; i++){
            int count = 0;
            for(int j = 0; j < 6; j++){
                if(i != j && collab[i][j]){
                    count++;
                }
            }
            if(count == 5){
                return i;
            }
        }
    return -1;
}