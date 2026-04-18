/*
Simulazione d'esame (fatta dal tutor il giorno prima) - Casa, San Gregorio, 06/06/25 dalle 10:00 alle 11:00

    Si vuole realizzare un'applicazione per la gestione dei dati relativi a una biblioteca digitale.
    Le informazioni sono memorizzate in struct aventi la seguente definizione:
    typedef struct {
        char titolo[30];
        char autore[30];
        int genere;     // intero da 0 a 4: 0=Romanzo, 1=Storia, 2=Scienza, 3=Tecnologia, 4=Altro
        int copie;
        float prezzo;
    } Libro;

    typedef struct {
        Libro catalogo[6];
        int prestiti[10][2]; // ciascuna riga: {indiceLibro, numeroCopiePrestate}
    } Biblioteca;

    Ogni istanza di Libro rappresenta un libro disponibile nella biblioteca,
    associato a un genere (valore intero da 0 a 4),
    a un numero di copie disponibili e al prezzo di vendita per copia.

    Le informazioni relative ai prestiti sono contenute nella matrice prestiti,
    in cui ogni riga rappresenta un prestito effettuato. Ogni prestito registra:
    - indiceLibro: posizione nell'array catalogo del libro prestato,
    - numeroCopiePrestate: quante copie del libro sono state prestate in quell'occasione.

    Un libro può comparire più volte nella matrice prestiti,
    anche con un numero diverso di copie.

    Scrivere le seguenti funzioni (sono ammessi eventuali metodi ausiliari):

    1. float valoreTotaleCatalogo(Biblioteca b)
    Restituisce il valore complessivo dei libri in magazzino,
    cioè la somma del numero di copie per il prezzo unitario di ogni libro.

    2. int libriPiuRichiesti(Biblioteca b, int soglia, int indices[], int* count)
    Restituisce, nell'array indices, gli indici dei libri che sono stati prestati
    in un numero totale di copie maggiore o uguale a soglia.
    La variabile count indica il numero di elementi scritti in indices.

    3. char* generePiuPrestato(Biblioteca b)
    Restituisce il nome del genere che ha totalizzato il numero maggiore di copie prestate.
    Per determinare il genere si somma il numero di copie prestate per ciascun libro
    e si aggregano per genere.

    4. int libroMaiPrestato(Biblioteca b)
    Restituisce l’indice di un libro che non è mai stato prestato. Se più libri
    soddisfano la condizione, si restituisce il primo. Se tutti i libri sono stati
    prestati, si restituisce -1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titolo[30];
    char autore[30];
    int genere;     // intero da 0 a 4: 0=Romanzo, 1=Storia, 2=Scienza, 3=Tecnologia, 4=Altro
    int copie;
    float prezzo;
} Libro;

typedef struct {
    Libro catalogo[6];
    int prestiti[10][2]; // ciascuna riga: {indiceLibro, numeroCopiePrestate}
} Biblioteca;

/*
Funzione 1: float valoreTotaleCatalogo(Biblioteca b)
Restituisce il valore complessivo dei libri in magazzino, cioè la somma del numero di copie per il prezzo unitario di ogni libro.
*/
float valoreTotaleCatalogo(Biblioteca b){
    float val_tot = 0.0;
    for(int i = 0; i < 6; i++){
        val_tot += b.catalogo[i].copie * b.catalogo[i].prezzo;
    }
    return val_tot;
}

/*
Funzione 2: int libriPiuRichiesti(Biblioteca b, int soglia, int indices[], int* count)
Restituisce, nell'array indices, gli indici dei libri che sono stati prestati
in un numero totale di copie maggiore o uguale a soglia.
La variabile count indica il numero di elementi scritti in indices.
*/
int libriPiuRichiesti(Biblioteca b, int soglia, int indices[], int* count){
    int totali[6] = {0};
    *count = 0;
    for(int i = 0; i < 10; i++){
    int index_libri = b.prestiti[i][0];
    int n_copie = b.prestiti[i][1];
    totali[index_libri] += n_copie;
    }
    for(int j = 0; j < 6; j++){
        if(totali[j] > soglia){
            indices[*count] = j;
            (*count)++;
        }
    }
    return indices[*count];
}

/*
Funzioe 3: char* generePiuPrestato(Biblioteca b)
Restituisce il nome del genere che ha totalizzato il numero maggiore di copie prestate.
Per determinare il genere si somma il numero di copie prestate per ciascun libro
e si aggregano per genere.
*/
char* generePiuPrestato(Biblioteca b){
    int totali[5] = {0};
    char nomi_generi[5] = {"Romanzo", "Storia", "Scienza", "Tecnologia", "Altro"};
    for(int i = 0; i < 10; i++){
        int index = b.prestiti[i][0];
        int copie = b.prestiti[i][1];
        int genere = b.catalogo[index].genere;
        totali[genere] += copie;
    }
    int max_genere = 0;
    for(int i = 1; i < 5; i++){
        if(totali[i] > totali[max_genere]){
            max_genere = i;
        }
    }
    char* res = (char*) malloc (20 * sizeof(char));
    strcpy(res, nomi_generi[max_genere]);
    return res;
}

/*
Funzione 4: int libroMaiPrestato(Biblioteca b)
Restituisce l’indice di un libro che non è mai stato prestato. Se più libri
soddisfano la condizione, si restituisce il primo. Se tutti i libri sono stati
prestati, si restituisce -1.
*/
int libroMaiPresato(Biblioteca b){
    for(int i = 0; i < 6; i++){
        int trovato = 0;
        for(int j = 0; j < 10; j++){
            if(i == b.prestiti[j][0]){
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