/*
Simulazione d'esame (chatgpt) - Casa, Cosenza 21/06/25 dalle 15:00 alle 15:30

Gestione di studenti ed esami 

typedef struct {
    char nome[30];
    int matricola;
    float mediaVoti;
} Studente;

typedef struct {
    Studente studenti[5];
    int votiEsami[5][5];  // massimo 5 voti per ciascuno studente
} RegistroEsami;

Funzioni da implementare: 
1.	Funzione int contaStudentiPromossi(RegistroEsami r)
Restituisce quanti studenti hanno tutti i voti ≥ 18.
2.	Funzione float calcolaMediaStudente(RegistroEsami r, int indice)
Restituisce la media dei voti dello studente in posizione indice.
3.	Funzione void aggiornaMedie(RegistroEsami *r)
Calcola e aggiorna il campo mediaVoti di ogni studente, usando la media dei suoi 5 voti.
4.	Funzione void stampaStudentiPromossi(RegistroEsami r)
Stampa nome e matricola degli studenti con mediaVoti ≥ 24.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    int matricola;
    float mediaVoti;
} Studente;

typedef struct {
    Studente studenti[5];
    int votiEsami[5][5];  // massimo 5 voti per ciascuno studente
} RegistroEsami;

/*
Funzione 1: Funzione int contaStudentiPromossi(RegistroEsami r)
Restituisce quanti studenti hanno tutti i voti ≥ 18.
*/
int contaStudentiPromossi(RegistroEsami r){
    int count = 0;
    for(int i = 0; i < 5; i++){
        int tutti_promossi = 1;
        for(int j = 0; j < 5; j++){
            if(r.votiEsami[i][j] >= 18){
                tutti_promossi = 0;
                break;
            }
        }
        if(tutti_promossi){
            count++;
        }
    }
    return count;
}

/*
Funzione 2: Funzione float calcolaMediaStudente(RegistroEsami r, int indice)
Restituisce la media dei voti dello studente in posizione indice.
*/
float calcolaMediaStudente(RegistroEsami r, int indice){
    float somma = 0.0;
    for(int i = 0; i < 5; i++){
        somma += r.votiEsami[indice][i];
    }
    float media = somma / 5;
    return media;
}

/*
Funzione 3: void aggiornaMedie(RegistroEsami *r)
Calcola e aggiorna il campo mediaVoti di ogni studente, usando la media dei suoi 5 voti.
*/
void aggiornaMedie(RegistroEsami* r){
    for(int i = 0; i < 5; i++){
        float somma = 0;
        for(int j = 0; j < 5; j++){
            somma += r->votiEsami[i][j];
        }
        r->studenti[i].mediaVoti = somma / 5;
    }
}

/*
Funzione 4: void stampaStudentiPromossi(RegistroEsami r)
Stampa nome e matricola degli studenti con mediaVoti ≥ 24.
*/
void stampaStudentiPromossi(RegistroEsami r){
    printf("Studenti promossi:\n");
    for(int i = 0; i < 5; i++){
        if(r.studenti[i].mediaVoti >= 24){
            printf("Nome: %s - Matricola: %d\n",r.studenti[i].nome, r.studenti[i].matricola);
        }
    }
}
