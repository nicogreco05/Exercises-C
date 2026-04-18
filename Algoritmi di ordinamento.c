/*
GLI ALGORITMI DI ORDINAMENTO 

1 - BUBBLE SORT
Bubble Sort confronta ogni coppia di elementi adiacenti e li scambia se sono nel verso sbagliato.
Alla fine di ogni “passata”, l’elemento più grande “sale” alla fine, come una bolla.
Ripete il processo più volte, finché tutto è ordinato.

Esempio su [5, 3, 8, 2]:
• 1ª passata: [3, 5, 2, 8]
• 2ª passata: [3, 2, 5, 8]
• 3ª passata: [2, 3, 5, 8] → ordinato

Complessità d'ordine:
• caso peggiore -> O(n^2)
• caso migliorne -> O(n)

Codice: 
void bubbleSort(int arr[], int n) {
    int scambiato;
    for (int i = 0; i < n - 1; i++) {
        scambiato = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Scambia
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                scambiato = 1;
            }
        }
        // Se non ci sono stati scambi → array già ordinato
        if (!scambiato) break;
    }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2 - INSERTION SORT
Costruisce l’array ordinato elemento per elemento: prende un elemento e lo inserisce nella posizione 
giusta tra quelli già ordinati a sinistra.

Esempio su [5, 3, 8, 2]:
• Prende il 3 e lo mette prima del 5 → [3, 5, 8, 2]
• Prende l’8 → già a posto → [3, 5, 8, 2]
• Prende il 2 e lo inserisce davanti → [2, 3, 5, 8]

Complessità d'ordine:
• caso peggiore -> O(n^2) array invertito
• caso migliore -> O(n) array già ordinto

Codice:
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // Sposta a destra gli elementi maggiori di key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        // Inserisce key nella posizione giusta
        arr[j + 1] = key;
    }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3 - SELECTION SORT
Cerca sempre il minimo elemento nella parte non ordinata dell’array e lo sposta all’inizio. Poi ripete sul resto.
Divide l’array in due parti: ordinata e non ordinata.
A ogni passo:
Cerca il minimo nella parte non ordinata.
Lo scambia con il primo elemento non ordinato.
Ripete fino a ordinare tutto.

Esempio su [5, 3, 8, 2]:
• Trova il minimo (2), lo scambia con 5 → [2, 3, 8, 5]
• Trova il minimo (3) tra [3, 8, 5] → già in posizione
• Trova il minimo (5) tra [8, 5] → scambia → [2, 3, 5, 8]

Complessità d'ordine:
• caso peggiore = caso migliore -> O(n^2) fa sempre nxn confornti

Codice: 
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        // Trova il minimo nell’array da i in poi
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        // Scambia arr[i] con arr[min_idx]
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

4 - QUICK SORT
Quick Sort è un algoritmo ricorsivo che usa il metodo del “divide et impera”:
sceglie un elemento chiamato pivot, e riordina l’array spostando a sinistra gli elementi più piccoli e a destra quelli più grandi.

Esempio su [5, 3, 8, 2] (pivot = 2):
•Sposta gli elementi:
[2, 3, 8, 5] (2 nella sua posizione finale)
•Ora chiama ricorsivamente su [3, 8, 5]
Pivot = 3 → [2, 3, 8, 5] → chiama su [8, 5]
Pivot = 5 → → [2, 3, 5, 8]

Complessità d'ordine:
• caso migliore -> O(nlogn)
• caso peggiore -> O(n^2)

Codice: 
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Pivot = ultimo elemento
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);  // Metti pivot al centro
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // posizione pivot
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

5 - MERGE SORT
Merge Sort è un algoritmo ricorsivo che divide l’array in due metà, le ordina separatamente, e poi le unisce ordinatamente (merge).

Esempio su [5, 3, 8, 2]:
• Divide in [5, 3] e [8, 2]
• Ordina ciascuno → [3, 5] e [2, 8]
• Merge finale: [2, 3, 5, 8]

Complessità d'ordine:
• caso peggiore = caso migliore -> O(nlogn)

Codice: 
void merge(int arr[], int sinistra, int centro, int destra) {
    int n1 = centro - sinistra + 1;
    int n2 = destra - centro;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[sinistra + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[centro + 1 + j];

    int i = 0, j = 0, k = sinistra;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int sinistra, int destra) {
    if (sinistra < destra) {
        int centro = sinistra + (destra - sinistra) / 2;
        mergeSort(arr, sinistra, centro);
        mergeSort(arr, centro + 1, destra);
        merge(arr, sinistra, centro, destra);
    }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

6 - HEAP SORT
Esempio su [5, 3, 8, 2]:
• Costruisci max heap: [8, 5, 3, 2]
• Scambia 8 e 2 → [2, 5, 3, 8], heap size = 3
• Ripristina max heap su [2, 5, 3] → [5, 2, 3, 8]
• Scambia 5 e 3 → [3, 2, 5, 8], heap size = 2
• Ripristina max heap su [3, 2] → [3, 2, 5, 8]
• Scambia 3 e 2 → [2, 3, 5, 8], heap size = 1 → ordinato!

Complessità d'ordine
• caso migliore = caso peggiore -> O(nlogn)

Codice:
void heapify(int arr[], int n, int i) {
    int largest = i;        // Inizializza il più grande come radice
    int left = 2 * i + 1;   // figlio sinistro
    int right = 2 * i + 2;  // figlio destro

    // Se il figlio sinistro è più grande della radice
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Se il figlio destro è più grande del più grande finora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Se il più grande non è la radice
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Heapify ricorsivamente il sottoalbero interessato
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Costruisci max heap (riordina l’array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Estrai un elemento alla volta dal heap
    for (int i = n - 1; i > 0; i--) {
        // Sposta la radice corrente alla fine
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Chiama heapify sul heap ridotto
        heapify(arr, i, 0);
    }
}

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

MACCHINA DI VON NEUMANN
È il modello di base di tutti i moderni computer.
Componenti principali:
1. Unità di memoria
→ Dove sono salvati dati e istruzioni (nello stesso posto!)
2. Unità di controllo
→ Coordina tutte le operazioni (decide “cosa fare dopo”).
3. Unità aritmetico-logica (ALU)
→ Esegue operazioni matematiche e logiche (somma, confronto, ecc.).
4. Registri
→ Memoria piccolissima e velocissima dentro il processore (es: PC, IR, ACC).
5. Bus
→ Canali per trasmettere dati tra le parti (es: bus dati, indirizzi, controllo).

Ciclo della macchina (o ciclo di esecuzione)
Ogni istruzione segue 3 fasi:
1. Fetch (prelievo)
La CPU legge dalla memoria l’istruzione da eseguire.
• L’indirizzo è nel Program Counter (PC)
• L’istruzione viene copiata nel Instruction Register (IR)
• Il PC viene incrementato (passa all’istruzione successiva)

2. Decode (decodifica)
La CPU interpreta l’istruzione.
Capisce cosa deve fare: somma? confronto? salto?

3. Execute (esecuzione)
La CPU esegue davvero l’operazione:
• Esegue l’operazione aritmetica (con ALU)
• Legge/scrive nella memoria
• Aggiorna registri o salta ad altre istruzioni
*/