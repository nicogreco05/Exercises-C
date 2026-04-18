/*
Simulazione d'esame (chat gpt) - Casa, Cosezna dalle 18:30 alle 19:00

Si vuole realizzare un programma per la gestione dei libri di una biblioteca. I dati sono memorizzati nelle seguenti strutture:

typedef struct {
    char titolo[50];
    char genere[30];  // es. "Romanzo", "Saggio", "Fantascienza", ...
    int copieDisponibili;
    int valoreStimato; // valore in euro per ogni copia
} Libro;

typedef struct {
    Libro libri[5];
    int prestiti[10][3]; // ogni riga: [indiceLibro, giorniPrestito, valoreStimatoTotale]
} RegistroPrestiti;

Funzioni richieste:
1. int valoreBiblioteca(RegistroPrestiti rp)
Restituisce il valore totale della biblioteca in euro, calcolato come
copieDisponibili * valoreStimato per ciascun libro.

2. int* libriFrequenti(RegistroPrestiti rp, char* genere, int soglia, int* dim)
Restituisce un array dinamico contenente i codici (indici) dei libri del genere specificato che sono stati 
prestati almeno soglia volte. Usa *dim per restituire il numero degli elementi.

3. char* genereTopLettori(RegistroPrestiti rp)
Restituisce il genere in cui gli utenti hanno speso di più in valore stimato 
(cioè la somma dei valoreStimatoTotale dei prestiti per quel genere).

4. int libriMaiPrestati(RegistroPrestiti rp)
Restituisce il numero di libri (tra i 5 disponibili) che non sono mai stati prestati.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titolo[50];
    char genere[30];  // es. "Romanzo", "Saggio", "Fantascienza", ...
    int copieDisponibili;
    int valoreStimato; // valore in euro per ogni copia
} Libro;

typedef struct {
    Libro libri[5];
    int prestiti[10][3]; // ogni riga: [indiceLibro, giorniPrestito, valoreStimatoTotale]
} RegistroPrestiti;

/*
Funzione 1: int valoreBiblioteca(RegistroPrestiti rp)
Restituisce il valore totale della biblioteca in euro, calcolato come
copieDisponibili * valoreStimato per ciascun libro.
*/
int valoreBiblioteca(RegistroPrestiti rp){
    int valore_totale = 0;
    for(int i = 0; i < 5; i++){
        valore_totale += rp.libri[i].copieDisponibili * rp.libri[i].valoreStimato;
    }
    return valore_totale;
}

/*
Funzione 2: int* libriFrequenti(RegistroPrestiti rp, char* genere, int soglia, int* dim)
Restituisce un array dinamico contenente i codici (indici) dei libri del genere specificato che sono stati 
prestati almeno soglia volte. Usa *dim per restituire il numero degli elementi.
*/
int* libriFrequenti(RegistroPrestiti rp, char* genere, int soglia, int* dim){
    int* conteggi = (int*) calloc(5, sizeof(int));
    if(conteggi == NULL){
        printf("Errore nell'allocazione di memoria!");
        exit(1);
    }
    *dim = 0;
    for(int i = 0; i < 10; i++){
        int index = rp.prestiti[i][0];
        if(strcmp(genere, rp.libri[index].genere) == 0){
            conteggi[index]++;
        }
    }
    for(int i = 0; i < 5; i++){
        if(conteggi[i] >= soglia){
            (*dim)++;
        }
    }
    int* res = (int*) malloc (*dim * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    int k = 0;
    for(int i = 0; i < 10; i++){
        int index = rp.prestiti[i][0];
        if(strcmp(genere, rp.libri[index].genere) == 0){
            conteggi[index] += rp.prestiti[i][1];
        }
    }
    for(int i = 0; i < 5; i++){
        if(conteggi[i] >= soglia){
            res[k++] = i;
        }
    }
    free(conteggi);
    return res;
}

/*
Funzione 3: char* genereTopLettori(RegistroPrestiti rp)
Restituisce il genere in cui gli utenti hanno speso di più in valore stimato 
(cioè la somma dei valoreStimatoTotale dei prestiti per quel genere).
*/
char* genereTopLettori(RegistroPrestiti rp){
    char* generi[5];
    int valori_stimati[5] = {0};
    int nGeneri = 0;
    for(int i = 0; i < 10; i++){
        int index = rp.prestiti[i][0];
        int valore = rp.prestiti[i][2];
        char* cat = rp.libri[index].genere;
        int trovato = 0;
        for(int j = 0; j < nGeneri; j++){
            if(strcmp(cat, generi[j]) == 0){
                valori_stimati[j] += valore;
                trovato = 1;
                break;
            }
        }
        if(!trovato){
            generi[nGeneri] = cat;
            valori_stimati[nGeneri] = valore;
            nGeneri++;
        }
    }
    int max_index = 0;
    for(int i = 1; i < nGeneri; i++){
        if(valori_stimati[i] > valori_stimati[max_index]){
            max_index = i;
        }
    }
    return generi[max_index];
}

/*
Funzione 4: int libriMaiPrestati(RegistroPrestiti rp)
Restituisce il numero di libri (tra i 5 disponibili) che non sono mai stati prestati.
*/
int libriMaiPrestati(RegistroPrestiti rp){
    int count = 0;
    for(int i = 0; i < 5; i++){
        int trovato = 0;
        for(int j = 0; j < 10; j++){
            if(rp.prestiti[j][0] == i){
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