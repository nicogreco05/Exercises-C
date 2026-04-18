/*
Simulazione d'esame (chatgpt) - Casa, Cosezna dalle 15:30 alle 16:00

Gestione Videoteca

typedef struct {
    char titolo[50];
    char regista[40];
    char genere[20];     // es: "Azione", "Dramma", "Commedia", "Horror", ...
    int durata;          // in minuti
    int copieDisponibili;
    float prezzoNoleggio; // prezzo per ogni noleggio
} Film;

typedef struct {
    Film film[5];
    int noleggi[10][3];  // ogni riga: [indiceFilm, giorniNoleggio, numeroCopie]
} RegistroNoleggi;

Funzioni da implementare:
1.	float valoreVideoteca(RegistroNoleggi r)
Restituisce il valore della videoteca in base a:
copieDisponibili * prezzoNoleggio per ogni film.
2.	int* filmPopolari(RegistroNoleggi r, char* genere, int soglia, int* dim)
Restituisce un array dinamico con gli indici dei film di un dato genere noleggiati almeno soglia volte (numero di noleggi, non giorni).
Usa *dim per restituire la dimensione dell’array.
3.	char* genereTopNoleggi(RegistroNoleggi r)
Restituisce il genere che ha generato il maggiore incasso totale:
(giorniNoleggio * prezzoNoleggio * numeroCopie) per ogni noleggio.
4.	int filmMaiNoleggiati(RegistroNoleggi r)
Restituisce quanti film tra i 5 non sono mai stati noleggiati.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titolo[50];
    char regista[40];
    char genere[20];     // es: "Azione", "Dramma", "Commedia", "Horror", ...
    int durata;          // in minuti
    int copieDisponibili;
    float prezzoNoleggio; // prezzo per ogni noleggio
} Film;

typedef struct {
    Film film[5];
    int noleggi[10][3];  // ogni riga: [indiceFilm, giorniNoleggio, numeroCopie]
} RegistroNoleggi;

/*
Funzione 1: float valoreVideoteca(RegistroNoleggi r)
Restituisce il valore della videoteca in base a:
copieDisponibili * prezzoNoleggio per ogni film.
*/
float valoreVideoteca(RegistroNoleggi r){
    float valore = 0.0;
    for(int i = 0; i < 5; i++){
        valore += r.film[i].copieDisponibili * r.film[i].prezzoNoleggio;
    }
    return valore;
}

/*
Funzione 2: int* filmPopolari(RegistroNoleggi r, char* genere, int soglia, int* dim)
Restituisce un array dinamico con gli indici dei film di un dato genere noleggiati almeno soglia volte (numero di noleggi, non giorni).
Usa *dim per restituire la dimensione dell’array.
*/
int* filmPopolari(RegistroNoleggi r, char* genere, int soglia, int* dim){
    int* res = (int*) malloc (5 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    *dim = 0;
    for(int i = 0; i < 5; i++){
        if(strcmp(genere, r.film[i].genere) == 0){
            for(int j = 0; i < 10; i++){
                if(r.noleggi[j][1] >= soglia){
                    (*dim)++;
                }
            }
        }
    }
    res = (int*) calloc ((*dim), sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int k = 0;
        for(int i = 0; i < 5; i++){
        if(strcmp(genere, r.film[i].genere) == 0){
            for(int j = 0; i < 10; i++){
                if(r.noleggi[j][1] >= soglia){
                    res[k++] = i;
                }
            }
        }
    }
    return res;
}

/*
Funzione 3: char* genereTopNoleggi(RegistroNoleggi r)
Restituisce il genere che ha generato il maggiore incasso totale:
(giorniNoleggio * prezzoNoleggio * numeroCopie) per ogni noleggio.
*/
char* genereTopNoleggi(RegistroNoleggi r){
    char* generi[5];
    int* totali = (int*) calloc (5, sizeof(int));
    if(totali == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int nGeneri = 0;
    for(int i = 0; i < 10; i++){
        int index = r.noleggi[i][0];
        int giorni_noleggio = r.noleggi[i][1];
        int num_copie = r.noleggi[i][2];
        int prezzo_noleggio = r.film[index].prezzoNoleggio;
        char* genere = r.film[index].genere;
        int trovato = 0;
        for(int j = 0; j < nGeneri; j++){
            if(strcmp(genere, generi[j]) == 0){
                totali[j] += giorni_noleggio * prezzo_noleggio * num_copie;
                trovato = 1;
                break;
            }
        }
        if(!trovato){
            generi[nGeneri] = strdup(genere);
            totali[nGeneri] = giorni_noleggio * prezzo_noleggio * num_copie;
            nGeneri++;
        }
    }
    int max_index = 0;
    for(int i = 1; i < nGeneri; i++){
        if(totali[i] > totali[max_index]){
            max_index = i;
        }
    }
    free(totali);
    return generi[max_index];
}

/*
Funzione 4: int filmMaiNoleggiati(RegistroNoleggi r)
Restituisce quanti film tra i 5 non sono mai stati noleggiati.
*/
int filmMaiNoleggiati(RegistroNoleggi r){
    int count = 0;
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 10; j++){
            if(i == r.noleggi[j][0]){
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
