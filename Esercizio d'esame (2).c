/*
Si vuole realizzare un’applicazione per la gestione delle informazioni riguardanti acquisti di componenti per la
produzione di articoli commerciali. L’applicazione memorizza i dati relativi alla composizione degli articoli in un
dizionario AC in cui ad ogni articolo è associata la lista dei componenti necessari per la produzione dell'articolo
stesso. Le offerte effettuate dai fornitori dei componenti sono memorizzate in una matrice O avente 3 colonne, in
cui la generica riga [comp, forn, pr] rappresenta il fatto che il componente comp è offerto dal fornitore forn al prezzo
pr. Si assuma che non esistano due righe aventi uguali valori di comp e forn – in altri termini, ogni fornitore non può
effettuare più offerte per uno stesso componente. La spesa di fornitura per un articolo è la somma dei prezzi che è
necessario spendere per i componenti dell'articolo – ovviamente, se più di un fornitore fornisce uno stesso
componente, si considera l'offerta con prezzo minore. Un componente è detto speciale quando è necessario alla
produzione di un solo articolo.
Si scriva un modulo Python che metta a disposizione (almeno) le seguenti funzioni:
1. articolo_minima_spesa(AC,O), che restituisce l'articolo avente minima spesa di fornitura. Nel caso in cui più
di un articolo soddisfi la condizione, la funzione ne restituisce uno qualsiasi.
2. miglior_fornitore(AC,O), che restituisce il fornitore che soddisfa entrambe le seguenti condizioni:
a. il fornitore fornisce tutti i componenti necessari alla produzione di tutti gli articoli;
b. la somma dei prezzi richiesti dal fornitore è minima.
Nel caso in cui più di un fornitore soddisfi le condizioni, la funzione ne restituisce uno qualsiasi. Nel caso in
cui nessun fornitore soddisfi le condizioni, la funzione restituisce una stringa vuota.
3. componenti_speciali(AC), che restituisce la lista dei componenti speciali.
4. componente_comune(O), che restituisce il componente disponibile presso il maggior numero di fornitori,
cioè il componente per cui sono state effettuate il maggior numero di offerte. Nel caso in cui più di un
componente soddisfi la condizione, la funzione ne restituisce uno qualsiasi.
*/

#include <stdio.h>
#include <string.h>

#define max_nome 20
#define max_componenti 10
#define prezzo_max 1000000000000

typedef struct{
    char componente[max_nome];
    char fornitore[max_nome];
    float prezzo;
} Offerte;

typedef struct{
    char articolo[max_nome];
    char lista_componenti_necessari[max_componenti][max_nome];
    int num_componenti;
} Articoli;

// Funzione 1: articolo_minima_spesa(AC,O), che restituisce l'articolo avente minima spesa di fornitura. 
// Nel caso in cui più di un articolo soddisfi la condizione, la funzione ne restituisce uno qualsiasi.
const char* articolo_minima_spesa(Articoli articoli[], Offerte offerte[], int num_articoli, int num_offerte){
    // Inizializzo la spesa minima con un valore alto (che normalmente non si puo raggiungere)
    float minima_spesa = prezzo_max;
    // Inizializzo l'articolo minimo come una variabile char vuota per ora
    const char* articolo_minimo = "";
    // Ciclo per vedere i vari articoli
    for(int i =0 ; i < num_articoli; i++){
        // Inizializzo la spesa per l'articolo corrente pari a 0 
        float spesa = 0.0;
        // Ciclo su ogni componente dell'articolo
        for(int j = 0; j < articoli[i].num_componenti; j++){
            // Variabile per ottenere il nome del componente da "lista_componenti_necessari"
            char* comp = articoli[i].lista_componenti_necessari[j];
            // Inizializzo il prezzo minimo per il componente corrente ad un prezzo alto
            float prezzo_minimo = prezzo_max;
            // Ciclo su ogni offerta per cercare il prezzo piu basso del componente
            for(int k = 0; k < num_offerte; k++){
                // Ora confronto il nome del componente con quello dell'offerta corrente
                if(strcmp(offerte[k].componente, comp) == 0){
                    // Se il prezzo dell'offerta è piu basso di quello attuale aggiorno il prezzo minimo
                    if(offerte[k].prezzo < prezzo_minimo){
                        prezzo_minimo = offerte[k].prezzo;
                    }
                }
            }
            // Aggiungo il prezzo del componente al prezzo dell'articolo
            spesa += prezzo_minimo;
        }
        // Se la spesa dell'articolo corrente è minore della spesa minima trovata aggiorno la spesa minima
        if(spesa < minima_spesa){
            minima_spesa = spesa;
            // Salvo in una variabile il nome dell'articolo (a questo punto con spesa minima)
            articolo_minimo = articoli[i].articolo;
        }
    }
    // Restituisco l'articolo con spesa minima
    return articolo_minimo;
}

/* Funzione 2: miglior_fornitore(AC,O), che restituisce il fornitore che soddisfa entrambe le seguenti condizioni:
a. il fornitore fornisce tutti i componenti necessari alla produzione di tutti gli articoli;
b. la somma dei prezzi richiesti dal fornitore è minima.
Nel caso in cui più di un fornitore soddisfi le condizioni, la funzione ne restituisce uno qualsiasi. Nel caso in
cui nessun fornitore soddisfi le condizioni, la funzione restituisce una stringa vuota. */
const char* miglior_fornitore(Articoli articoli[], Offerte offerte[], int num_articoli, int num_offerte) {
    // Lista di tutti i componenti necessari senza ripetizioni
    char componenti_necessari[100][max_nome];
    int num_componenti_necessari = 0;
    // Raccogli tutti i componenti da tutti gli articoli
    for (int i = 0; i < num_articoli; i++) {
        for (int j = 0; j < articoli[i].num_componenti; j++) {
            char* comp = articoli[i].lista_componenti_necessari[j];
            int già_presente = 0;
            // Verifica se il componente è già stato aggiunto
            for (int k = 0; k < num_componenti_necessari; k++) {
                if (strcmp(componenti_necessari[k], comp) == 0) {
                    già_presente = 1;
                    break;
                }
            }
            // Aggiungi il componente se non c'è già
            if (!già_presente) {
                strcpy(componenti_necessari[num_componenti_necessari], comp);
                num_componenti_necessari++;
            }
        }
    }
    // Raccogli tutti i fornitori unici dalle offerte
    char fornitori[100][max_nome];
    int num_fornitori = 0;
    for (int i = 0; i < num_offerte; i++) {
        char* nome_forn = offerte[i].fornitore;
        int già_presente = 0;
        for (int j = 0; j < num_fornitori; j++) {
            if (strcmp(fornitori[j], nome_forn) == 0) {
                già_presente = 1;
                break;
            }
        }
        if (!già_presente) {
            strcpy(fornitori[num_fornitori], nome_forn);
            num_fornitori++;
        }
    }
    // Cerca il fornitore che fornisce tutti i componenti e al minor costo
    float costo_minimo = prezzo_max;
    const char* miglior_forn = "";
    for (int i = 0; i < num_fornitori; i++) {
        char* nome_forn = fornitori[i];
        int fornisce_tutti = 1;
        float costo_totale = 0.0;

        // Controlla se il fornitore fornisce tutti i componenti
        for (int j = 0; j < num_componenti_necessari; j++) {
            char* comp = componenti_necessari[j];
            int trovato = 0;

            for (int k = 0; k < num_offerte; k++) {
                if (strcmp(offerte[k].fornitore, nome_forn) == 0 && strcmp(offerte[k].componente, comp) == 0) {
                    costo_totale += offerte[k].prezzo;
                    trovato = 1;
                    break;
                }
            }
            // Se manca almeno un componente, non è un buon fornitore
            if (!trovato) {
                fornisce_tutti = 0;
                break;
            }
        }
        // Se è valido e ha costo inferiore, aggiornalo come migliore
        if (fornisce_tutti && costo_totale < costo_minimo) {
            costo_minimo = costo_totale;
            miglior_forn = fornitori[i];
        }
    }
    // Se nessuno soddisfa la condizione, ritorna stringa vuota
    return miglior_forn;
}

// Funzione 3: componenti_speciali(AC), che restituisce la lista dei componenti speciali.
// Componenti speicali --> componenti che servono ad un solo articolo
void componenti_speciali(Articoli articoli[], int num_articoli){
    char tutti_componenti[100][max_nome];
    int conteggio[100] = {0};
    int num_componenti_trovati = 0;
    for(int i = 0; i < num_articoli; i++){
        for(int j = 0; j < articoli[i].num_componenti; j++){
            char* comp_corrente = articoli[i].lista_componenti_necessari[j];
            int trovato = 0;
            for(int k = 0; k < num_componenti_trovati; k++){
                if(strcmp(tutti_componenti[k], comp_corrente) == 0){
                    conteggio[k]++;
                    trovato = 1;
                    break;
                }
            }
            if(!trovato){
                strcpy(tutti_componenti[num_componenti_trovati], comp_corrente);
                conteggio[num_componenti_trovati] = 1;
                num_componenti_trovati++;
            }
        }
    }
    printf("Componenti speciali:\n");
    for(int i = 0; i < num_componenti_trovati; i++){
        if(conteggio[i] == 1){
            printf("- %s\n", tutti_componenti[i]);
        }
    }
}

/* Funzione 4: componente_comune(O), che restituisce il componente disponibile presso il maggior numero di fornitori,
cioè il componente per cui sono state effettuate il maggior numero di offerte. Nel caso in cui più di un
componente soddisfi la condizione, la funzione ne restituisce uno qualsiasi. */
const char* componente_comune(Offerte offerte[], int num_offerte) {
    char componenti[100][max_nome]; // Array per tenere i nomi unici dei componenti
    int conteggio[100] = {0}; // Array per contare quante volte appare ogni componente
    int num_componenti = 0;
    // Scorriamo tutte le offerte
    for (int i = 0; i < num_offerte; i++) {
        char* comp = offerte[i].componente;
        int trovato = 0;
        // Controlla se il componente è già stato visto
        for (int j = 0; j < num_componenti; j++) {
            if (strcmp(componenti[j], comp) == 0) {
                conteggio[j]++; // Già presente --> aumentiamo il numero di offerte
                trovato = 1;
                break;
            }
        }
        // Se non trovato, aggiungilo tra i componenti
        if (!trovato) {
            strcpy(componenti[num_componenti], comp);
            conteggio[num_componenti] = 1;
            num_componenti++;
        }
    }
    // Ora troviamo il componente con il conteggio massimo
    int max_index = 0;
    for (int i = 1; i < num_componenti; i++) {
        if (conteggio[i] > conteggio[max_index]) {
            max_index = i;
        }
    }
    // Restituiamo il nome del componente più offerto
    static char risultato[max_nome];
    strcpy(risultato, componenti[max_index]);
    return risultato;
}

// Main
int main(){

    Articoli articoli[2] = {
        {"Sedia", {{"Gamba"}, {"Schienale"}, {"Seduta"}}, 3},
        {"Tavolo", {{"Gamba"}, {"Piano"}}, 2}
    };

    Offerte offerte[6] = {
        {"Gamba", "F1", 10.0},
        {"Gamba", "F2", 8.0},
        {"Schienale", "F1", 5.0},
        {"Seduta", "F2", 7.0},
        {"Piano", "F1", 15.0},
        {"Piano", "F3", 13.0}
    };
    
    // Funzione 1
    printf("Articolo a minima spesa: %s\n", articolo_minima_spesa(articoli, offerte, 2, 6));

    // Funzione 2
    componenti_speciali(articoli, 2);

    // Funzione 3
    printf("Componente con più fornitori: %s\n", componente_comune(offerte, 6));
    
    // Funzione 4
    const char* miglior_f = miglior_fornitore(articoli, offerte, 2, 6);
    if (strcmp(miglior_f, "") == 0) {
        printf("Nessun fornitore fornisce tutti i componenti necessari.\n");
    } 
    else {
        printf("Miglior fornitore: %s\n", miglior_f);
    }

    return 0;

}