/*
Simulazione d'esame (chatgpt) - 09/07/25

Hai a disposizione una biblioteca digitale che conserva informazioni su libri. 
Scrivi un programma che gestisca una struttura Libro e un contenitore Archivio.

typedef struct {
    char titolo[50];
    char autore[30];
    int pagine;
    int anno;
    float voto; // da 1.0 a 10.0
} Libro;

typedef struct {
    Libro scaffale[15];    // massimo 15 libri
    char preferiti[5][50]; // titoli di libri preferiti (massimo 5)
} Archivio;

Funzioni da implementare
1. bool tuttiPreferitiPresenti(Archivio a)
Restituisce true se tutti i titoli in preferiti sono presenti nello scaffale, false altrimenti.

2. float mediaVotiLibriLunghi(Archivio a, int sogliaPagine)
Calcola e restituisce la media dei voti dei libri che hanno un numero di pagine maggiore o uguale a sogliaPagine. 
Se non ce ne sono, restituisci 0.0.

3. char* autorePiuApprezzato(Archivio a)
Restituisce il nome dell’autore con la media voto più alta, considerando tutti i suoi libri. 
Se ci sono più autori a pari merito, restituisci uno qualsiasi.

4. char* libroPreferitoBreve(Archivio a, int maxPagine)
Restituisce il titolo del libro con il voto più alto tra quelli che hanno al massimo maxPagine pagine. 
Se non ce ne sono, restituisce "Nessuno".
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char titolo[50];
    char autore[30];
    int pagine;
    int anno;
    float voto; // da 1.0 a 10.0
} Libro;

typedef struct {
    Libro scaffale[15];    // massimo 15 libri
    char preferiti[5][50]; // titoli di libri preferiti (massimo 5)
} Archivio;

/*
Funzione 1: bool tuttiPreferitiPresenti(Archivio a)
Restituisce true se tutti i titoli in preferiti sono presenti nello scaffale, false altrimenti.
*/
bool tuttiPreferitiPresenti(Archivio a){
    for(int i = 0; i < 5; i++){
        bool ok = false;
        for(int j = 0; j < 15; j++){
            if(strcmp(a.preferiti[i], a.scaffale[j].titolo) == 0){
                ok = true;
            }
        }
        if(!ok){
            return false;
        }
    }
    return true;
}

/*
Funzione 2: float mediaVotiLibriLunghi(Archivio a, int sogliaPagine)
Calcola e restituisce la media dei voti dei libri che hanno un numero di pagine maggiore o uguale a sogliaPagine. 
Se non ce ne sono, restituisci 0.0.
*/
float mediaVotiLibriLunghi(Archivio a, int sogliaPagine) {
    int count = 0;
    float somma = 0.0;
    for (int i = 0; i < 15; i++) {
        if (a.scaffale[i].pagine >= sogliaPagine) {
            somma += a.scaffale[i].voto;
            count++;
        }
    }
    return (count > 0) ? somma / count : 0.0;
}

/*
Funzione 3: char* autorePiuApprezzato(Archivio a)
Restituisce il nome dell’autore con la media voto più alta, considerando tutti i suoi libri. 
Se ci sono più autori a pari merito, restituisci uno qualsiasi.
*/
char* autorePiuApprezzato(Archivio a){
    static char autore[20];
    float max_media = -1.0;
    for(int i = 0; i < 15; i++){
        char* autore_ = a.scaffale[i].autore;
        float somma = 0.0;
        int count = 0;
        for(int j = 0; j < 15; j++){
            if(strcmp(autore_, a.scaffale[j].autore) == 0){
                somma += a.scaffale[j].voto;
                count++;
            }
        }
        if(count > 0){
            float media = somma / count;
            if(media > max_media){
                max_media = media;
                strcpy(autore, autore_);
            }
        }
    }
    return autore;
}

/*
Funzione 4: char* libroPreferitoBreve(Archivio a, int maxPagine)
Restituisce il titolo del libro con il voto più alto tra quelli che hanno al massimo maxPagine pagine. 
Se non ce ne sono, restituisce "Nessuno".
*/
char* libroPreferitoBreve(Archivio a, int maxPagine){
    static char libro[20];
    int* voti = (int*) malloc (15 * sizeof(int));
    for(int i = 0; i < 15; i++){
        if(a.scaffale[i].pagine <= maxPagine){
            voti[i] = a.scaffale[i].voto;
        }
        else{
            voti[i] = -1;
        }
    }
    int max_indice = -1;
    for(int i = 0; i < 15; i++){
        if(voti[i] != -1){
            max_indice = i;
            break;
        }
    }
    if(max_indice == -1){
        strcpy(libro, "Nessuno");
        return libro;
    }
    for(int i = max_indice + 1; i < 15; i++){
        if(voti[i] != -1 && voti[i] > voti[max_indice]){
            max_indice = i;
            strcpy(libro, a.scaffale[max_indice].titolo);
        }
    }
    return libro;
}
