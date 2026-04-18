/* Si vuole realizzare un'applicazione per la gestione delle informazioni riguardanti i movimenti di denaro effettuati su
conti correnti presso diverse filiali di una banca.
Ogni conto corrente è identificato mediante un codice intero compreso tra 0 e n-1. L’applicazione memorizza i
movimenti utilizzando una matrice M avente 3 colonne, in cui la generica riga [cc, data, amm] rappresenta il fatto
che sul conto corrente con codice cc nel giorno data è stato effettuato un movimento per un ammontare pari ad
amm. Le date sono rappresentate per semplicità come numeri interi. Ogni ammontare è rappresentato come float
e può essere negativo. Il saldo di un conto corrente è dato dalla somma dei movimenti effettuati su quel conto
corrente. I dati sulle filiali e sui clienti sono memorizzati utilizzando un dizionario C in cui ad ogni chiave cc è
associata una lista [citta, nome_cliente] che rappresenta il fatto che il conto corrente con codice cc è aperto presso
la filiale presente nella città citta e che il conto è intestato al cliente con nome nome_cliente (assumiamo che in
ogni città sia presente una sola filiale e che un conto possa essere intestato ad un solo cliente).
Si scriva un modulo C che metta a disposizione (almeno) le seguenti funzioni:
1. meno_movimenti(M,C), che restituisce la città nella cui filiale sono stati effettuati il minor numero di
movimenti. Se più di una città soddisfa tale condizione, la funzione restituisce una qualunque di esse.
2. clienti_target(M,C), che restituisce una lista contenente i nomi dei clienti che hanno conti correnti con saldo
positivo presso almeno due filiali diverse.
3. statistiche(M,C), che restituisce un dizionario contenente, per ogni cliente, il saldo totale dei conti correnti
intestati a quel cliente.
4. situazione_alla_data(M,C,d), che restituisce un dizionario in cui ad ogni chiave cc è associata una lista
[nome_cliente, totale] che rappresenta il fatto che sul conto corrente con codice cc, intestato al cliente
nome_cliente, fino alla data d (inclusa) sono stati effettuati movimenti per un ammontare totale pari a
totale. */

#include <stdio.h>
#include <string.h>

#define max_nome 20

typedef struct{
    int codice_cc;
    int data;
    float amm;
} Movimento;

typedef struct{
    char citta[max_nome];
    char nome_cliente[max_nome];
} Info;

// Funzione per calcolare il saldo totale di un conto corrente
float saldo_totale(Movimento movimenti[],int num_movimenti,int codice_conto){
    float saldo_totale=0.0;
    for(int i=0;i<num_movimenti;i++){
        if(codice_conto==movimenti[i].codice_cc){
            saldo_totale+=movimenti[i].amm;
        }
    }
    return saldo_totale;
}

/*
1. meno_movimenti(M,C), che restituisce la città nella cui filiale sono stati effettuati il minor numero di
movimenti. Se più di una città soddisfa tale condizione, la funzione restituisce una qualunque di esse.
*/
int conta_movimenti(Movimento movimenti[],int num_movimenti,int codice_conto){
    int count=0;
    for(int i=0;i<num_movimenti;i++){
        if(codice_conto==movimenti[i].codice_cc){
            count++;
        }
    }
    return count;
}

char meno_movimenti(Movimento movimento[],Info info[],int num_conti,int num_movimenti){


    char citta_con_meno_movimenti="";
    int movimentiperfiliale[num_conti];
    for(int i=0;i<num_conti;i++){
        movimenti_per_filiale[i]=conta_movimenti(movimenti,num_movimenti,i);
    }
    int min=0;
    for(int j=0;j<num_conti;j++){
        if(movimenti_per_filiale[i]<movimenti_per_filiale[min]){
            min=i;
        }
    }
    citta_con_meno_movimenti=strcpy(citta_con_meno_movimenti,info[min].citta);
    return citta_con_meno_movimenti;
}

/*
2. clienti_target(M,C), che restituisce una lista contenente i nomi dei clienti che hanno conti correnti con saldo
positivo presso almeno due filiali diverse.
*/
void clienti_target(Movimento movimenti[],int num_movimenti,Info info[],int num_conti){
    int filiali_positive[100];
    for(int i=0;i<num_conti;i++){
        float saldo=saldo_totale(movimenti,num_movimenti,i);
        if(saldo>0){
            filiali_positive[i]=1;
        }
    }
    printf("Clienti con saldi positivi in più filiali:\n");
    for(int i=0;i<num_conti;i++){
        int count=0;
        for(int j=0;j<num_conti;j++){
            if(strcmp(info[i].nome_cliente,info[j].nome_cliente)==0){
                count=count+filiali_positive[i];
            }
        }
        if(count>1){
            printf("-%s\n",info[i].nome_cliente);
        }
    }
}

/*
3. statistiche(M,C), che restituisce un dizionario contenente, per ogni cliente, il saldo totale dei conti correnti
intestati a quel cliente.
*/
void statistiche(Movimento movimenti[],int num_movimenti,Info info[],int num_conti){
    float saldi_clienti[100]={0};
    int clienti_elaborati[100]={0};
    for(int i=0;i<num_conti;i++){
        float saldo_conto=saldo_totale(movimenti,num_movimenti,i);
        for(int j=0;j<num_conti;j++){
            if(strcmp(info[i].nome_cliente,info[j].nome_cliente)==0){
                saldi_clienti[i]+=saldo_conto;
            }
        }
    }
    printf("Statistiche per cliente:\n");
    for(int i=0;i<num_movimenti;i++){
        if(!clienti_elaborati[i]){
            printf("-%s: %.2f\n",info[i].nome_cliente,saldi_clienti[i]);
            for(int j=0;j<num_conti;j++){
                if(strcmp(info[i].nome_cliente,info[j].nome_cliente)==0){
                    clienti_elaborati[j]=1;
                }

            }
        }
    }
}

/*
situazione_alla_data(M,C,d), che restituisce un dizionario in cui ad ogni chiave cc è associata una lista
[nome_cliente, totale] che rappresenta il fatto che sul conto corrente con codice cc, intestato al cliente
nome_cliente, fino alla data d (inclusa) sono stati effettuati movimenti per un ammontare totale pari a
totale
*/
void situazione_alla_data(Movimento movimenti[],int num_movimenti,Info info[],int num_conti,int data_limite){
    float saldi[100]={0};
    for(int i=0;i<num_movimenti;i++){
        if(movimenti[i].data<=data_limite){
            saldi[movimenti[i].codice_cc]+=movimenti[i].amm;
        }
    }
    printf("Situazione conti alla data %d:\n",data_limite);
    for(int j=0;j<num_conti;j++){
        printf("-Conto %d (%s): %.2f\n",j,info[j].nome_cliente,saldi[j]);
    }
}