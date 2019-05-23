#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//LISTA DOPPIAMENTE CONCATENATA

struct nodo{
    int info;
    struct nodo *next;
    struct nodo *prec;
};
typedef struct nodo elemento_t;
typedef elemento_t *lista_t;

void inizializza(lista_t *lista){
    *lista = NULL;
}

bool listaVuota(lista_t lista){
    if(lista == NULL)
        return true;
    else return false;
}

void inserisci_coda(lista_t *lista){
    elemento_t *temp;
    lista_t cur;
    cur = *lista;
    temp = malloc(sizeof(elemento_t));
    printf("\nChe elemento vuoi inserire?");
    scanf("%d",&(temp->info));
    temp->next = NULL;
    if(cur ==  NULL){
        temp->prec = NULL;
        *lista = temp;
    }else{
        while((cur->next) != NULL){
            cur = cur->next;
        }
        temp->prec = cur;
        cur->next = temp;
    }
    cur = *lista;
}



void inserisci_testa(lista_t *lista){
    elemento_t *temp;
    lista_t cur;
    cur = *lista;
    temp = malloc(sizeof(elemento_t));
    printf("\nChe dato vuoi inserire?");
    scanf("%d",&(temp->info));
    temp->prec = NULL;
    if(cur == NULL) {
        *lista = temp;
        temp->next = NULL;
    }
    else{
        temp->next = cur;
        cur->prec = temp;
        *lista = temp;
    }

}

void inserisci_ordine(lista_t *lista){
    elemento_t *temp;
    elemento_t *corrente;
    elemento_t *preced = NULL;
    lista_t cur;
    cur = *lista;
    temp = malloc(sizeof(elemento_t));
    printf("\nChe dato vuoi inserire?");
    scanf("%d",&(temp->info));
    if(cur == NULL){
        *lista = temp;
        temp->next = NULL;
        temp->prec = NULL;
    }else{
        corrente = cur;
        while(corrente != NULL  && (temp->info) >(corrente->info)){
            preced = corrente;
            corrente = corrente->next;
        }
        if(corrente != NULL) {
            temp->next = corrente;
            corrente->prec = temp;
        }else{
            temp->next = NULL;
        }
        if(preced != NULL){
            preced->next = temp;
            temp->prec = preced;
        }else{
            temp->prec = NULL;
            *lista = temp;
        }
    }
}

void rimuovitesta(lista_t *lista){
    elemento_t *temp;
    if(listaVuota(*lista)){
        printf("\nla lista è vuota");
        getchar();
    }else{
        temp = *lista;
        *lista = (*lista)->next;
        if(!listaVuota(*lista))
            (*lista)->prec = NULL;
        free(temp);
    }
}

bool cerca(lista_t *lista, int el){

    lista_t  cur;
    cur = *lista;
    if(listaVuota(*lista)){
        printf("\nLa lista è vuota impossibile fare ricerche");
    }else{

        while(cur != NULL){
            printf("\n%d",cur->info);
            if(el == (cur->info)) {
                return true;
            }
            cur =  cur->next;
        }
    }
    return false;
}

void rimuovicoda(lista_t *lista){
    elemento_t *temp;
    if(listaVuota(*lista)){
        printf("\nLa lista è vuota");
        getchar();
    }else{
        temp = *lista;
        if(temp->next != NULL) {
            while ((temp->next)->next != NULL)
                temp = temp->next;
            temp->next = NULL;
        }else{
            *lista = (*lista)->next;
            free(temp);
        }
    }
}

void rimuoviElemento(lista_t *lista){
    if(listaVuota(*lista)){
        printf("\nLa lista è vuota");
        getchar();
    }else{
        elemento_t *temp;
        temp = *lista;
        int elem;
        printf("\nChe elemento vuoi eliminare?");
        scanf("%d",&elem);
        if(cerca(lista,elem)){
            while(temp->next->info != elem){
                temp = temp->next;
            }
            elemento_t *mom;
            mom = temp->next;
            mom->next->prec = temp;
            temp->next = temp->next->next;
            free(mom);

        }else{
            printf("\nL'elemento non è presente nella lista");
            getchar();
        }

    }
}

void stampa(lista_t *lista){
    elemento_t *temp;
    temp = *lista;
    if(listaVuota(*lista)){
        printf("\nla lista è vuota");
        getchar();
    }else{
        while(temp != NULL){
            printf("\nElemento %d",temp->info);
            temp = temp->next;
        }
    }


}

int main(){
    lista_t dati;
    inizializza(&dati);
    int scelta;
    int el;
    do{
        printf("\nMENU \n 0 : uscire \n 1 : inserire un dato in coda\n 2: rimuovere in testa\n 3: cercare un dato\n 4: stampare la lista\n"
               " 5 : rimuovere in coda\n 6: inserire in testa\n 7: inserire in ordine\n 8 : rimuovere elemento\n ");
        scanf("%d",&scelta);
        switch (scelta){
            case 0: break;
            case 1: inserisci_coda(&dati);
                break;
            case 2: rimuovitesta(&dati);
                break;
            case 3: printf("\nche dato cerchi?");
                scanf("%d",&el);
                if(cerca(&dati,el))
                    printf("\nElemento trovato");
                else
                    printf("\nElemento non trovato");
                break;
            case 4: stampa(&dati);
                break;
            case 5 : rimuovicoda(&dati);
                break;
            case 6 : inserisci_testa(&dati);
                break;
            case 7 : inserisci_ordine(&dati);
                break;
            case 8 : rimuoviElemento(&dati);
                break;
            default : printf("\ntasto errato premi invio e riprova\n");
                getchar();
                getchar();
                break;
        }
    }while(scelta != 0);


    while(dati != NULL){
        rimuovitesta(&dati);
    }
    free(dati);
}

