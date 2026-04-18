/*
I puntatori in c sono dei "tipi" a cui noi però non possiamo associare delle variabili definite, 
(int, char, double) ma associamo i puntatori ai tipi stessi, ad esempio un puntatore ad int, o un puntatore a char, ecc. ecc.
Un puntatore contiene un indrizzo di memoria.
Per ottenere l'indirizzo di memoria di una variabile usiamo l'operaotre "&"
Per accedere al valore memorizzato all'indirizzo usiamo "*" (deferenziazione)
Ad esempio:
int num = 5;
int* ptr = &num;
printf("L'indrizzo di memoria di %d: %p", num, *ptr); --> L'indirizzo di memoria di num è 084738210
dove: 
-int* ptr è un puntatore all'indirizzo di num 
-%p stampa l'indirizzo di memoria
---------------------------------------------------------------------------------------------------------------------------------------
A cosa serve un puntatore?
Con un puntatore possiamo:
-modificare il contenuto di una variabile da una funzione
-allocare memoria dinamicamente (con malloc, realloc ecc. ecc.)
-gestire array e stringhe in modo flessibile
-restituire piu dati da una funzione 
---------------------------------------------------------------------------------------------------------------------------------------
La funzione MALLOC
Questi tipi di funzioni servono per allocare memoria dinamicamente durante l'esecuzione di un programma

int *arr = malloc(5 * sizeof(int)); --> crea un array di 5 interi

-malloc alloca memoria e restituisce un puntatore all'inizio del blocco 
-sieof(int) serve a dire quanto spazio serve per ciascun intero
-arr è un puntatore ad int, quindi -> int *arr
---------------------------------------------------------------------------------------------------------------------------------------
La funzione REALLOC 
La funzione realloc come si puo intuire dalla parola stessa serve per ridimensionare la memoria allocata con malloc
Vediamo come funziona sfruttando l'esempio di prima usato con malloc 

arr = realloc(arr, 10 * sizeof(int)) --> ora l'array ha spazio per cinque elementi
---------------------------------------------------------------------------------------------------------------------------------------
La funzione CALLOC
Questa funzione è molto simile a malloc ma con una differenza principale.
Come sappiamo la funzione malloc alloca memoria per n elementi, e questi elementi vengono inizializzati in modo casuale.
La funzione calloc, invece, allora si memoria per n elementi MA questi elementi vengono inizilizzati a 0.
Quando è utile utlizzare calloc:
-quando ci serve una struttura inizializzata a 0 (contatori, array vuoti --> il che ci sonsente di fare += in modo sicuro)
-quando vogliamo evitare bug dovuti a variabili non inizializzate 

Vediamo un esempio
int *arr = calloc(3, sizeof(int))

Output atteso:
arr[1] = 0
arr[2] = 0
arr[3] = 0
---------------------------------------------------------------------------------------------------------------------------------------
Esempio pratico: funzione che restituisce un array di stringhe 

char **creaNomi(){
    char **nomi = malloc(3 * sizeof(char *));

    nomi[0] = malloc(10); --> spazio per "Marco"
    nomi[1] = malloc(10);
    nomi[2] = malloc(10);

    strcpy(nomi[0],"Marco");
    strcpy(nomi[1],"Luca");
    strcpy(nomi[2],"Lucia");

    return nomi;

}

In questo caso:
-char **nomi è un array di 3 stringhe
-ogni nomi[i] una stringa (char *), quindi serve malloc per ognuna 

*/

