// Dichiarare una variabile di tipo int ed inizializzarla ad un valore arbitrario quindi modificarne il valore tramite una variabile puntatore
#include <stdio.h>
int main(void){
    int num = 5;
    int *ptr = &num;
    printf("Il valore del numero (originale): %d", num); 
    *ptr = 6;
    printf("Il valore del numero (dopo la modifica): %d", num);
    return 0;
}

// Creare una funzione "swap" che dati due interi ne scambi il valore tra di loro
void swap(int *val1, int *val2){
    int tmp;
    tmp = *val1;
    *val1 = *val2;
    *val2 = tmp;

}

int main(void){
    int a = 5;
    int b = 10;
    printf("Valori prima dello scambio:\n");
    printf("Valore di a: %d; Valore di b: %d\n",a, b);
    swap(&a, &b);
    printf("Valori dopo dello scambio:\n");
    printf("Valore di a: %d; Valore di b: %d",a, b);
    return 0; 
}

// CASA (COSENZA), 19/05/25 DALLE 15:00 ALLE 17:00
// Stampare una stringa lettera per lettera con char *
int main(void){
    char *parola = "ciao";
    while(*parola != '\0'){
        printf("%c\n", *parola);
        parola++; // per passare al carattere successivo 
    }
    return 0;
}

// Modifica il programma precedente per contare quante lettere ci sono nella parola
int main(void){
    char *parola = "ciao";
    char *inizio = parola;
    int count = 0;
    while(*parola != '\0'){
        count++;
        parola++;
    }
    printf("Nella parola -%s- ci sono %d lettere", inizio, count);
    return 0;
}

// Crea un array di n elementi, usa un puntatore per scorrere l'array e raddopiare ogni elemento 
// Variante 1
int main(void){
    int array[5] = {1, 2, 3, 4, 5};
    int *ptr = array;
    printf("Array originale: ");
    for(int i = 0; i < 5; i++){
        printf("%d ",array[i]);
    }
    // modifca dei valori usando il puntatore
    for(int i = 0; i < 5; i++){
        *(ptr + i) *= 2;
    }
    printf("\nArray modificato: ");
    for(int i = 0; i < 5; i++){
        printf("%d ",array[i]);
    }
    return 0;
}

// Variante 2
int main(void){
    int array[5] = {1, 2, 3, 4, 5};
    int *ptr = array;
    printf("Array originale: ");
    for(int i = 0; i < 5; i++){
        printf("%d ",array[i]);
    }
    // modifico l'aaray
    for(int i = 0; i < 5; i++){
        *ptr *= 2;
        ptr++;
    }
    printf("\nArray modificato: ");
    for(int i = 0; i < 5; i++){
        printf("%d ",array[i]);
    }
    return 0;
}

/*
CREARE UN ARRAY DINAMICO CON MALLOC
Scrivi un programma che:
-chiede all'utente quanti numeri deve inserire
-alloca dinamicamente un array di interi con malloc
-fa inserire i numeri all'utente
-raddoppia ogni valore con l'uso dei puntatori
-stampa l'array modificato
-libera la memoria con free
*/
int main(void){
    int num_ins;
    printf("Quanti numeri vuoi inserire? ");
    scanf("%d",&num_ins);
    // uso malloc per allocare la memoria
    int *arr = malloc(num_ins * sizeof(int));
    if(arr == NULL){
        printf("Errore di allocazione della memoria.\n");
        return 1;
    }
    // faccio inserire i numeri all'utente
    printf("Inserisci %d numeri:\n",num_ins);
    for(int i = 0; i < num_ins; i++){
        scanf("%d",&arr[i]);
    }
    // modifico l'array
    int *ptr = arr;
    for(int i = 0; i < num_ins; i++){
        *ptr *= 2;
        ptr++;
    }
    // stampo l'array modificato
    printf("Array modificato: ");
    for(int i = 0; i < num_ins; i++){
        printf("%d ",arr[i]);
    }
    // libero la memoria 
    free(arr);
    return 0;
}

/*
Usare char** per gestire un elenco di stringhe
Scrivi un programma che:
-chiede all’utente quanti nomi vuole inserire.
-alloca dinamicamente un array di stringhe (char **).
-per ogni stringa, alloca dinamicamente la memoria necessaria con malloc.
-chiede all’utente di inserire ciascun nome.
-stampa tutti i nomi.
-libera tutta la memoria con free.
*/
int main(void){
    int parole_inserite;
    printf("Quante parole vuoi inserire? ");
    scanf("%d",&parole_inserite);
    // uso malloc per allocare la memoria
    char **arr = malloc(parole_inserite * sizeof(char*));
    if(arr == NULL){
        printf("Errore nell'allocazione della memoria");
        return 1;
    }
    // allocazione e inserimento parole
    printf("Inserisci %d parole:\n",parole_inserite);
    for(int i = 0; i < parole_inserite; i++){
        arr[i] = malloc(50 * sizeof(char)); // alloca spazio per ogni parola
        if(arr[i] == NULL){
            printf("Errore nell'allocazione della memoria della parola");
            return 1;
        }
        printf("Inserisci la parola %d: ",i+1);
        scanf("%s",arr[i]);
    }
    // stampa delle parole
    printf("Ecco le parole che hai inserito:\n");
    for(int i = 0; i < parole_inserite; i++){
        printf("%s\n",arr[i]);
    }
    // libero la memoria
    for(int i = 0; i < parole_inserite; i++){
        free(arr[i]);
    }
    free(arr);
    return 0;
}

// BIBLIOTECA, 20/05/25 DALLE 13:00 ALLE 14:00
/*
Funzione che legge parole
Scrivi un programma che:
-chiede all'tente quante parole vuole inserire
-alloca un char** dinamicamente
-passa questo array ad una funzione leggi_parole(char **arr int n) che:
  -allora la memoria per ogni parola
  -chiede all'utente di inserirla
-nel main, dopo la funzione, stampa tutte le parole inserite
-libera tutta la memoria come sempre 
*/
#define max_caratteri 50

void leggi_parole(char **arr, int n){
    printf("Inserisci %d parole:\n",n);
    for(int i = 0; i < n; i++){
        // uso malloc per allocare la memoria di ogni parola
        arr[i] = malloc(max_caratteri * sizeof(char));
        if(arr[i] == NULL){
            printf("Errore nell'allocazione della memoria della parola!");
            exit(1); // se fallisce malloc esco dal programma
        }

        printf("Inserisci la parola %d: ", i+1);
        scanf("%s",arr[i]);
    }
}
int main(void){
    // chiedo all'utente quante parole vuole inserire
    int numero_parole;
    printf("Quante parole vuoi inserire? ");
    scanf("%d", &numero_parole);
    // uso malloc per allocare la memoria
    char **arr = malloc(numero_parole * sizeof(char*));
    if(arr == NULL){
        printf("Errore nell'allocazione della memoria!");
        return 1;
    }
    // richiamo la funzione per far inserire le parole all'utente
    leggi_parole(arr,numero_parole);
    // stampa delle parole
    printf("Ecco le parole che hai inserito:\n");
    for(int i = 0; i < numero_parole; i++){
        printf("%s ",arr[i]);
    }
    // libero la memoria
    for(int i = 0; i < numero_parole; i++){
        free(arr[i]);
    }
    free(arr);
    return 0;
}
/*
Scrivi un programma che:
-chiede all'utente quante parole deve inserire
-chiama una funzione char** leggi_parole(int n) che:
  -alloca dinamicamente un array di stringhe
  -alloca memoria per ogni parola
  -fa inserire le parole al'utente
  -ritorna il char** nel main
-nel main, stampa le parole ricevuta
-libera tutta le memoria
*/

#define max_caratteri 50

char** leggi_parole2(int n){
    // alloco la memoria con malloc
    char** res = malloc(n * sizeof(char*));
    if(res == NULL){
        printf("Errore nell'allocazione della memoria!");
        exit(1);
    }
    // ora alloco la memoria per ogni parola
    for(int i = 0; i < n; i++){
        res[i] = malloc(max_caratteri * sizeof(char));
        if(res[i] == NULL){
            printf("Erroe nell'allocazione della memoria della parola!");
            exit(1);
        }
        // faccio inserire le parole
        printf("Inserisci la parola %d: ",i+1);
        scanf("%s",res[i]);
    }
    // ritorno l'array di parole
    return res;
}

int main(void){
    // chiedo all'utente quante parole vuole inserire
    int numero_parole;
    printf("Quante parole vuoi inserire? ");
    scanf("%d",&numero_parole);
    // richiamo la funzione
    char **arr = leggi_parole2(numero_parole);
    // stampo le parole
    printf("Ecco le parole che hai inserito:\n");
    for(int i = 0; i < numero_parole; i++){
        printf("%s ",arr[i]);
    }
    // libero la memoria
    for(int i = 0; i < numero_parole; i++){
        free(arr[i]);
    }
    free(arr);
    return 0;
}