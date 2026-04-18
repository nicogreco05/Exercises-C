/*
Casa, San Gregorio - 30/05/25 dalle 18:00 alle 19:00

Si desidera realizzare un’applicazione in C per gestire le prenotazioni di un hotel. 
Ogni camera dell’hotel è identificata da un numero univoco e appartiene a una specifica categoria. 
Le informazioni relative alle camere e alle prenotazioni sono memorizzate utilizzando le seguenti strutture:

typedef struct {
    int numero;           // Numero identificativo della camera
    char categoria[20];   // Categoria della camera (es. "Singola", "Doppia", "Suite")
    int prezzo;           // Prezzo per notte in euro
    int disponibilita;    // Numero di notti disponibili per la prenotazione
} Camera;

typedef struct {
    Camera camere[5];     // Array di 5 camere disponibili
    int prenotazioni[8][2]; // Ogni riga rappresenta una prenotazione: [numeroCamera, nottiPrenotate]
} PrenotazioniHotel;

Funzioni da implementare:
1.	int valoreTotaleDisponibile(PrenotazioniHotel ph):
•	Calcola e restituisce il valore totale delle notti disponibili per tutte le camere, considerando il prezzo per notte di ciascuna.
2.	int camerePopolari(PrenotazioniHotel ph, char categoria[20], int soglia, int count):**
•	Restituisce un array contenente i numeri delle camere della categoria specificata che sono state prenotate 
    per un numero di notti superiore alla soglia indicata. 
    La variabile count rappresenta il numero di elementi nell’array risultato.
3.	char categoriaPreferita(PrenotazioniHotel ph):*
•	Determina e restituisce la categoria di camera che ha generato il maggior numero di notti prenotate complessivamente.
4.	int cameraMaiPrenotata(PrenotazioniHotel ph):
•	Restituisce il numero di una camera che non è mai stata prenotata. Se tutte le camere hanno almeno una prenotazione, restituisce -1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numero;           // Numero identificativo della camera
    char categoria[20];   // Categoria della camera (es. "Singola", "Doppia", "Suite")
    int prezzo;           // Prezzo per notte in euro
    int disponibilita;    // Numero di notti disponibili per la prenotazione
} Camera;

typedef struct {
    Camera camere[5];     // Array di 5 camere disponibili
    int prenotazioni[8][2]; // Ogni riga rappresenta una prenotazione: [numeroCamera, nottiPrenotate]
} PrenotazioniHotel;

/*
Funzione 1: int valoreTotaleDisponibile(PrenotazioniHotel ph):
Calcola e restituisce il valore totale delle notti disponibili per tutte le camere, considerando il prezzo per notte di ciascuna. 
*/
int valoreTotaleDisponibile(PrenotazioniHotel ph){
    int totale = 0;
    for(int i = 0; i < 5; i++){
        totale += ph.camere[i].disponibilita * ph.camere[i].prezzo;
    }
    return totale;
}

/*
Funzione 2: int camerePopolari(PrenotazioniHotel ph, char categoria[20], int soglia, int count):**
Restituisce un array contenente i numeri delle camere della categoria specificata che sono state prenotate 
per un numero di notti superiore alla soglia indicata. 
*/
int *camerePopolari(PrenotazioniHotel ph, char categoria[20], int soglia, int *count){
    int cnt = 0;
    for(int i = 0; i < 5; i++){
        int tot_camere = 0;
        if(strcmp(ph.camere[i].categoria, categoria) == 0){
            for(int j = 0; j < 8; j++){
                if(ph.prenotazioni[j][0] == ph.camere[i].numero){
                    tot_camere += ph.prenotazioni[j][1];
                }
            }
        }
        if(tot_camere > soglia){
            cnt++;
        }
    }
    int* res = (int*) malloc (cnt * sizeof(int));
    if(res == NULL){
        printf("Erroe nell'allocazione della memoria!");
        exit(1);
    }
    *count = cnt;
    int k = 0;
    for(int i = 0; i < 5; i++){
        int tot_camere = 0;
        if(strcmp(ph.camere[i].categoria, categoria) == 0){
            for(int j = 0; j < 8; j++){
                if(ph.prenotazioni[j][0] == ph.camere[i].numero){
                    tot_camere += ph.prenotazioni[j][1];  
                }
            }
        }
        if(tot_camere > soglia){
            res[k++] = i;
        }
    }
    return res;
}

/*
Funzione 3: char* categoriaPreferita(PrenotazioniHotel ph):
Determina e restituisce la categoria di camera che ha generato il maggior numero di notti prenotate complessivamente.
*/
char* categoriaPreferita(PrenotazioniHotel ph){
    // Array per salvare le categorie (5 categorie al massimo, come il numero di camere, con al massimo 20 caratteri l'una)
    char categorie[5][20];
    // Array per salvare i ricavi totali per ogni categoria
    int totali[5];
    // Contatore per il numero di categorie uniche trovate
    int numCategorie;
    // Ciclo per ogni camera
    for(int i = 0; i < 5; i++){
        int index = -1;
        // Cerco se la categoria della camera è gia presente nell'array categorie
        for(int j = 0; j < numCategorie; j++){
            if(strcmp(ph.camere[i].categoria, categorie[j]) == 0){
                index = j; // Se la trovo salvo la posizione
            }
        }
        // Se non è presente la aggiungo all'array categorie
        if(index == -1){
            strcpy(categorie[numCategorie], ph.camere[i].categoria);
            index = numCategorie;
            numCategorie++;
        }
        // Per ogni prenotazione, se è relativa alla camera i-esima, aggiungo il guadagno
        for(int k = 0; k < 8; k++){
            // Controllo se la prenotazione riguarda questa camera (usando il numero camera)
            if(ph.prenotazioni[k][0] == ph.camere[i].numero){
                // Aggiungo al totale il numero di notti * il prezzo di ogni notte
                totali[index] += ph.prenotazioni[k][1] * ph.camere[k].prezzo;
            }
        }
    }
    // Trovo la categoria con il guadagno massimo
    int max = totali[0]; // massimo iniziale
    int pos = 0; // posizione della categoria massima
    for(int i = 1; i < numCategorie; i++){
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
Funzione 4: int cameraMaiPrenotata(PrenotazioniHotel ph):
Restituisce il numero di una camera che non è mai stata prenotata. Se tutte le camere hanno almeno una prenotazione, restituisce -1.
*/
int cameraMaiPrenotata(PrenotazioniHotel ph){
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 8; j++){
            if(ph.prenotazioni[j][0] == i){
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