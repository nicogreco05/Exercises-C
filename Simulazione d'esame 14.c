/*
Simulazione d'esame (20/01/25) - Casa, Cosenza 18/06/25 dalle 10:00 alle 12:00
Dopo averlo fatto:
Esercizio 1 --> fattibile ma devo migliorare
Esercizio 2 --> molto fattibile
Esercizio 3 --> facilissimo
Esercizio 4 --> praticamente bisogna saperla a memoria
Esercizio 5 --> praticamente bisogna saperla a memoria
Si vuole realizzare un’applicazione per la gestione dei dati relativi a musicisti e collaborazioni tra di essi. Le informazioni sono memorizzate in struct aventi la seguente definizione: 

typedef struct  
{   char nome[20]; 
    char strumento[20];     
} Musicista; 

typedef struct  
{   Musicista musicisti[6]; 
    int collaborazioni[8][4]; 
} MusicistiCollaborazioni; 
 
 
Si scrivano in C le seguenti funzioni (la scrittura di eventuali funzioni ausiliarie è ovviamente ammessa): 
int *numeroCollaborazioni(MusicistiCollaborazioni c) 
che restituisce un array di lunghezza pari a 6, 
il cui i-esimo elemento contiene il numero di collaborazioni che coinvolgono il musicista con codice i. 

int musicistaSimile(MusicistiCollaborazioni c, int cod) 
che restituisce il codice del musicista che ha collaborato più a lungo con il musicista con codice cod. 
Se più di un musicista soddisfa la condizione, la funzione restituisce il codice di uno qualsiasi di essi. 

int *durateStrumento(MusicistiCollaborazioni c, char strum[20]) che restituisce un array di lunghezza pari a 8, 
il cui i-esimo elemento contiene la durata (in anni) della i-esima collaborazione se almeno uno dei due musicisti suona 
lo strumento strum,  zero altrimenti. 

int musicistaRichiesto(MusicistiCollaborazioni c) che restituisce il codice di un musicista che ha collaborato con tutti gli altri 
musicisti. Se più di un musicista soddisfa la condizione, la funzione restituisce il codice di uno qualsiasi di essi. 
Se nessun musicista soddisfa la condizione, la funzione restituisce -1. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  
{ char nome[20]; 
  char strumento[20]; 
} Musicista; 

typedef struct  
{   Musicista musicisti[6]; 
    int collaborazioni[8][4]; // musicista1, musicista2, annoiniziocoll, annofinecoll
} MusicistiCollaborazioni; 

/*
Funzione 1: int *numeroCollaborazioni(MusicistiCollaborazioni c) 
che restituisce un array di lunghezza pari a 6, 
il cui i-esimo elemento contiene il numero di collaborazioni che coinvolgono il musicista con codice i. 
*/
int* numeroCollaborazioni(MusicistiCollaborazioni c){
    int* res = (int*) malloc (6 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    // Inizializzo tutti a 0
    for(int i = 0; i < 6; i++){
        res[i] = 0;
    }
    for(int i = 0; i < 8; i++){
        int m1 = c.collaborazioni[i][0];
        int m2 = c.collaborazioni[i][1];
        if(m1 >= 0 && m2 < 6){
            res[m1]++;
        }
        if(m1 >= 0 && m2 < 6){
            res[m2]++;
        }
    }
    return res;
}

/*
Funzione 2: int musicistaSimile(MusicistiCollaborazioni c, int cod) 
che restituisce il codice del musicista che ha collaborato più a lungo con il musicista con codice cod. 
Se più di un musicista soddisfa la condizione, la funzione restituisce il codice di uno qualsiasi di essi. 
*/
int musicistaSimile(MusicistiCollaborazioni c, int cod){
    int musicista = -1;
    int durataCollPrec = -1;
    for(int i = 0; i < 8; i++){
        int m1 = c.collaborazioni[i][0];
        int m2 = c.collaborazioni[i][1];
        int inizioColl = c.collaborazioni[i][2];
        int fineColl = c.collaborazioni[i][3];
        int durata = fineColl - inizioColl;
        if(m1 == cod){
            if(durata > durataCollPrec){
                durataCollPrec = durata;
                musicista = m2;
            }
        }
        else if(m2 == cod){
            if(durata > durataCollPrec){
            durataCollPrec = durata;
            musicista = m1;
            }
        }
    }
    return musicista;
}

/*
Funzione 3: int *durateStrumento(MusicistiCollaborazioni c, char strum[20]) che restituisce un array di lunghezza pari a 8, 
il cui i-esimo elemento contiene la durata (in anni) della i-esima collaborazione se almeno uno dei due musicisti suona 
lo strumento strum,  zero altrimenti. 
*/
int* durateStrumento(MusicistiCollaborazioni c, char strum[20]){
    int* res = (int*) malloc (8 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
    for(int i = 0; i < 8; i++){
        int m1 = c.collaborazioni[i][0];
        int m2 = c.collaborazioni[i][1];
        int inizioColl = c.collaborazioni[i][2];
        int fineColl = c.collaborazioni[i][3];
        int durataColl = fineColl - inizioColl;
        if(strcmp(c.musicisti[m1].strumento, strum) == 0 || strcmp(c.musicisti[m2].strumento, strum) == 0){
            res[i] = durataColl;
        }
        else{
            res[i] = 0;
        }
    }
    return res;
}

/*
Funzione 4: int musicistaRichiesto(MusicistiCollaborazioni c) che restituisce il codice di un musicista che ha collaborato con tutti gli altri 
musicisti. Se più di un musicista soddisfa la condizione, la funzione restituisce il codice di uno qualsiasi di essi. 
Se nessun musicista soddisfa la condizione, la funzione restituisce -1.
*/
int musicistaRichiesto(MusicistiCollaborazioni c){
    for(int i = 0; i < 6; i++){
        int collConAltri[6] = {0};
        for(int j = 0; j < 8; j++){
            int m1 = c.collaborazioni[i][0];
            int m2 = c.collaborazioni[i][1];
            if(m1 == i && m2 != i){
                collConAltri[m2] = 1;
            }
            else if(m2 == i && m1 != i){
                collConAltri[m1] = 1;
            }
        }
        int count = 0;
        for(int k = 0; k < 6; k++){
            if(k != i && collConAltri[k] == 1){
                count++;
            }
        }
        if(count == 5){
            return i;
        }
    }
    return -1;
}


/*
Esercizio 2
Si scriva una funzione valutaOccorrenze(int *L1, int *L2, int nL1, int nL2) che riceve in ingresso due array di interi positivi 
L1 ed L2 (le cui rispettive lunghezze sono nL1 ed nL2) e restituisce un array avente lunghezza pari ad nL1 
il cui i-esimo elemento contiene: 
L1[i] se il valore L1[i] è presente in L2 un numero di volte pari ad L1[i]; 
-1 altrimenti. 
 
Esempio: Se L1 = [2, 1, 3, 5] e L2 = [2, 4, 1, 2, 5, 5, 5, 6, 5, 1, 4, 5] 
allora la funzione restituisce l'array [2, -1, -1, 5] perché l’elemento L1[0]=2 compare esattamente 2 volte in L2, 
l’elemento L1[3]=5 compare esattamente 5 volte in L2, mentre gli elementi L1[1]=1 ed L1[2]=3 
non hanno un numero di occorrenze in L2 pari al loro valore. 
*/
int* valutaOccorrenze(int* L1, int* L2, int nL1, int nL2){
    int* res = (int*) malloc (nL1 * sizeof(int));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    for(int i = 0; i < nL1; i++){
        int count = 0;
        for(int j = 0; j < nL2; j++){
            if(L1[i] == L2[j]){
                count++;
            }
        }
        if(count == L1[i]){
            res[i] = L1[i];
        }
        else{
            res[i] = -1;
        }
    }
    return res;
}

/*
Esercizio 3
Si consideri il seguente programma C:  
 
int f1(int x, int y); 
int f2(int x, int y); 
 
int f1(int x, int y) 
{   if (x == y)  
    {   return y; 
    }    
    int M = x > y ? x : y; 
    int N = x < y ? x : y; 
    return f2(M - N,N); 
} 
     
int f2(int x, int y) 
{   if(y == 0) 
    {    return x; 
    } 
    int M = 0; 
    int N = 0; 
    if(x % y >= y) 
    {   M = x % y; 
        N = y; 
    }         
    else 
    {   M = y; 
        N = x % y; 
    } 
    return f1(M,N);     
} 
 
int main(void) 
{printf("%d",f1(12,8)); 
} 
 
Si descriva sinteticamente la funzione svolta dal programma e si mostrino l'output prodotto e la traccia d'esecuzione. 

	1.	f1(12, 8)
→ x ≠ y → M = 12, N = 8
→ chiama f2(4, 8)
	2.	f2(4, 8)
→ y ≠ 0
→ x % y = 4 % 8 = 4 < 8
→ va nel ramo else → M = 8, N = 4
→ chiama f1(8, 4)
	3.	f1(8, 4)
→ x ≠ y → M = 8, N = 4
→ chiama f2(4, 4)
	4.	f2(4, 4)
→ x % y = 4 % 4 = 0
→ va nel ramo else → M = 4, N = 0
→ chiama f1(4, 0)
	5.	f1(4, 0)
→ x ≠ y → M = 4, N = 0
→ chiama f2(4, 0)
	6.	f2(4, 0)
→ y == 0 → ritorna x = 4
*/

/*
Esercizio 4
Scrivere una funzione in C:
int sommaDiagonalePrincipale(int mat[100][100], int n);
che prende in input una matrice quadrata di interi n x n e 
restituisce la somma degli elementi presenti sulla diagonale principale (quella che va da mat[0][0] a mat[n-1][n-1]).
*/
int sommaDiagonalePrincipale(int mat[100][100], int n){
    int somma = 0; 
    for(int i = 0; i < n; i++){
        somma += mat[i][i];
    }
    return somma;
}

/*
Esercizio 5
Scrivere una funzione in C:
int sommaDiagonaleSecondaria(int mat[100][100], int n);
che restituisce la somma degli elementi della diagonale secondaria (quella che va da mat[0][n-1] a mat[n-1][0]).
*/
int sommaDiagonaleSecondaria(int mat[100][100], int n){
    int somma = 0;
    for(int i = 0; i < n; i++){
        somma += mat[i][n-1-i];
    }
    return somma;
}