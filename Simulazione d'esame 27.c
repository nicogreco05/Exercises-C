/*
Simulazione d'esame (chatgpt) - Casa, San Gregorio, 07/07/25

Si vuole creare un sistema per gestire i libri disponibili in una biblioteca universitaria.

typedef struct {
    char titolo[30];
    char autore[20];
    char categoria[15];
    int pagine;
} Libro;

typedef struct {
    Libro catalogo[7];
    char categorieRichieste[5][15];
} Biblioteca;

1.	bool tutteCategoriePresenti(Biblioteca b)
Restituisce true se ogni categoria richiesta è presente almeno una volta nel catalogo.

2.	int pagineTotaliCategoria(Biblioteca b, char categoria[])
Restituisce il totale delle pagine per tutti i libri di una data categoria.

3.	char* autorePiùProduttivo(Biblioteca b)
Restituisce l’autore con il maggior numero totale di pagine scritte.

4.	char* categoriaPiùEstesa(Biblioteca b)
Restituisce la categoria con il maggiore numero medio di pagine.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char titolo[30];
    char autore[20];
    char categoria[15];
    int pagine;
} Libro;

typedef struct {
    Libro catalogo[7];
    char categorieRichieste[5][15];
} Biblioteca;

/*
Funzione 1: bool tutteCategoriePresenti(Biblioteca b)
Restituisce true se ogni categoria richiesta è presente almeno una volta nel catalogo.
*/
bool tutteCategoriePresenti(Biblioteca b){
    for(int i = 0; i < 5; i++){
        bool trovata = false;
        for(int j = 0; j < 7; j++){
            if(strcmp(b.categorieRichieste[i], b.catalogo[j].categoria) == 0){
                trovata = true;
            }
        }
        if(!trovata){
            return false;
        }
    }
    return true;
}

/*
Funzione 2: int pagineTotaliCategoria(Biblioteca b, char categoria[])
Restituisce il totale delle pagine per tutti i libri di una data categoria.
*/
int pagineTotaliCategoria(Biblioteca b, char categoria[]){
    int tot_pagine = 0;
    for(int i = 0; i < 7; i++){
        if(strcmp(b.catalogo[i].categoria, categoria) == 0){
            tot_pagine += b.catalogo[i].pagine;
        }
    }
    return tot_pagine;
}

/*
Funzione 3: char* autorePiùProduttivo(Biblioteca b)
Restituisce l’autore con il maggior numero totale di pagine scritte.
*/
char* autorePiuProduttivo(Biblioteca b){
    char* autore_top = b.catalogo[0].autore;
    int max_pagine = 0;
    for(int i = 0; i < 7; i++){
        int pagine = 0;
        for(int j = 0; j < 7; j++){
            if(strcmp(b.catalogo[i].autore, b.catalogo[j].autore) == 0){
                pagine += b.catalogo[j].pagine;
            }
        }
        if(pagine > max_pagine){
            max_pagine = pagine;
            autore_top = b.catalogo[i].autore;
        }
    }
    return autore_top;
}

/*

*/
char* categoriaPiùEstesa(Biblioteca b) {
    int maxMedia = 0;
    char* categoriaTop = b.catalogo[0].categoria;

    for (int i = 0; i < 7; i++) {
        int somma = 0;
        int conta = 0;
        for (int j = 0; j < 7; j++) {
            if (strcmp(b.catalogo[i].categoria, b.catalogo[j].categoria) == 0) {
                somma += b.catalogo[j].pagine;
                conta++;
            }
        }
        if (conta > 0) {
            int media = somma / conta;
            if (media > maxMedia) {
                maxMedia = media;
                categoriaTop = b.catalogo[i].categoria;
            }
        }
    }
    return categoriaTop;
}