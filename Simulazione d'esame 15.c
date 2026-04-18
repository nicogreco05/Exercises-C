/*
Simulazione d'esame (tutor) - Casa, Cosenza dalle 17:30 alle 18:30

Si vuole realizzare un’applicazione per la gestione dei dati relativi ai veicoli
di un autonoleggio. Le informazioni sono memorizzate in struct secondo le seguenti
definizioni:
 
typedef struct {
    char modello[30];
    char categoria[20]; // es. "Utilitaria", "SUV", "Furgone"
    int disponibili;
    int costoGiornaliero;
} Veicolo;
 
typedef struct {
    Veicolo veicoli[5];
    int noleggi[5][3]; // ogni riga, colonne: [indiceVeicolo, giorni, prezzoTotale]
} RegistroNoleggi;
 
Si scrivano in C le seguenti funzioni:
- int valoreParcoAuto(RegistroNoleggi rn)
  Restituisce il valore totale (in €) dei veicoli disponibili nel parco auto,
  calcolato come costoGiornaliero * disponibili per ciascun veicolo.
 
- int* veicoliPopolari(RegistroNoleggi rn, char *categoria, int soglia, int *dim)
  Restituisce un array dinamico contenente i codici dei veicoli della categoria
  specificata che sono stati noleggiati almeno soglia volte.
  Usa *dim per restituire il numero di elementi.
 
- char* categoriaTopCliente(RegistroNoleggi rn)
  Restituisce la categoria in cui i clienti hanno speso di più complessivamente
  (somma dei prezzi totali dei noleggi per categoria).
 
- int veicoliMaiNoleggiati(RegistroNoleggi rn)
  Restituisce il numero di veicoli (su 5) che non sono mai stati noleggiati.
 
Es. veicoli = { {"Panda", "Utilitaria", 3, 30},
                {"Ducato", "Furgone", 2, 50},
                {"Golf", "Utilitaria", 2, 40},
                {"Q5", "SUV", 1, 80},
                {"Transit", "Furgone", 3, 45} }
 
    noleggi = { {0, 3, 90},
                {2, 2, 80},
                {1, 4, 200},
                {4, 1, 45},
                {3, 2, 160} }
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char modello[30];
    char categoria[20]; // es. "Utilitaria", "SUV", "Furgone"
    int disponibili;
    int costoGiornaliero;
} Veicolo;
 
typedef struct {
    Veicolo veicoli[5];
    int noleggi[5][3]; // ogni riga, colonne: [indiceVeicolo, giorni, prezzoTotale]
} RegistroNoleggi;

/*
Funzione 1: int valoreParcoAuto(RegistroNoleggi rn)
Restituisce il valore totale (in €) dei veicoli disponibili nel parco auto,
calcolato come costoGiornaliero * disponibili per ciascun veicolo.
*/
int valoreParcoAuto(RegistroNoleggi rn){
    int val_tot = 0;
    for(int i = 0; i < 5; i++){
        val_tot += rn.veicoli[i].disponibili * rn.veicoli[i].costoGiornaliero;
    }
    return val_tot;
}

/*
Funzione 2: int* veicoliPopolari(RegistroNoleggi rn, char *categoria, int soglia, int *dim)
Restituisce un array dinamico contenente i codici dei veicoli della categoria
specificata che sono stati noleggiati almeno soglia volte.
Usa *dim per restituire il numero di elementi.
*/
int* veicoliPopolari(RegistroNoleggi rn, char* categoria, int soglia, int* dim){
    int* conteggi = (int*) calloc (5, sizeof(int));
    if(conteggi == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int* res = (int*) malloc (5 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    *dim = 0;
    for(int i = 0; i < 5; i++){
        int index = rn.noleggi[i][0];
        if(strcmp(categoria, rn.veicoli[index].categoria) == 0){
            conteggi[index]++;
        }
    }
    for(int i = 0; i < 5; i++){
        if(conteggi[i] >= soglia){
            res[*dim] = i;
            (*dim)++;
        }
    }
    free(conteggi);
    res = realloc(res, (*dim) * sizeof(int));
    return res;
}

/*
char* categoriaTopCliente(RegistroNoleggi rn)
Restituisce la categoria in cui i clienti hanno speso di più complessivamente
(somma dei prezzi totali dei noleggi per categoria).
*/
char* categoriaTopCliente(RegistroNoleggi rn){
    char* categorie[5];
    int guadagni[5] = {0};
    int nCategorie = 0;
    for(int i = 0; i < 5; i++){
        int index = rn.noleggi[i][0];
        int prezzo = rn.noleggi[i][2];
        char* cat = rn.veicoli[index].categoria;
        int trovato = 0;
        for(int j = 0; j < 5; j++){
            if(strcmp(cat, categorie[j]) == 0){
                guadagni[j] += prezzo;
                trovato = 1;
                break;
            }
        }
        if(!trovato){
            categorie[nCategorie] = cat;
            guadagni[nCategorie] = prezzo; // non metto += perche è una nuva categoria --> non ha prezzo inizializzato quindi
            nCategorie++;
        }
    }
    int max_index = 0;
    for(int i = 1; i < nCategorie; i++){
        if(guadagni[i] > guadagni[max_index]){
            max_index = i;
        }
    }
    return categorie[max_index];
}

/*
Funzione 4: int veicoliMaiNoleggiati(RegistroNoleggi rn)
Restituisce il numero di veicoli (su 5) che non sono mai stati noleggiati.
*/
int veicoliMaiNoleggiati(RegistroNoleggi rn){
    int count = 0;
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 5; j++){
            if(rn.noleggi[j][0] == i){
                trovato = 1;
                break;
            }
        }
        if(!trovato){
            count++;
        }
    }
    return count;
}