#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Nodo{
    struct Nodo* p;
    struct Nodo* left;
    struct Nodo* right;
    int key;
}Nodo;

typedef Nodo *albero;

void inizializza(albero *a){
    *a = NULL;
}

bool alberoVuoto(albero a){
    if(a == NULL)
        return true;
    else return false;
}

void insert(albero *a, int n){
    Nodo *temp;
    temp = malloc(sizeof(Nodo));
    temp->key = n;
    if(alberoVuoto(*a)){
        temp->left = NULL;
        temp->right = NULL;
        temp->p = NULL;
        *a = temp;

    }else{
        printf("\nDigita 0 se vuoi inserire il dato a sinistra, 1 per inserirlo a destra\n ");
        int scelta;
        scanf("%d",&scelta);
        if(scelta == 0){
            //creo un sottoalbero sinistro
            albero punt;
            punt = *a;
            while(punt->left != NULL)
                punt = punt->left;
            temp->p = punt;
            temp->left = NULL;
            temp->right = NULL;
            punt->left = temp;
        }else{
            //creo un sottoalbero destro
            albero punt;
            punt = *a;
            while(punt->right != NULL)
                punt = punt->right;
            temp->p = punt;
            temp->left = NULL;
            temp->right = NULL;
            punt->right = temp;
        }
    }
}

void stampa(albero *a){
    if(!alberoVuoto(*a)){
        Nodo *nodo;
        nodo = *a;
        printf("\nvalore %d",nodo->key);
        if(nodo->p != NULL){
            printf(" padre %d",nodo->p->key);
        }
        if(nodo->left != NULL){
            printf(" figlio sinistro %d",nodo->left->key);
        }
        if(nodo->right != NULL){
            printf(" figlio destro %d",nodo->right->key);
        }
        stampa(&(nodo->left));
        stampa(&(nodo->right));
    };
}

void search(albero *a, int n){
    if(!alberoVuoto(*a)){
        Nodo *nodo;
        nodo = *a;
        if(nodo->key != n){
            search(&(nodo->left),n);
            search(&(nodo->right),n);
        }else{
            printf("\nElemento trovato");
        }
    }
}


int main(){
    albero root;
    inizializza(&root);
    int ch;
    int elemento;
    do{
        printf("\nMenu\n0: uscire\n1: inserire un elemento\n2: cercare un elemento\n3: stampare l'albero\n");
        scanf("%d",&ch);
        switch(ch){
            case 1: printf("\nChe dato vuoi inserire?\n");
                    scanf("%d",&elemento);
                    insert(&root,elemento);
                    break;
            case 2 :printf("\nQuale elemento vuoi cercare?\n");
                    scanf("%d",&elemento);
                    search(&root,elemento);
                    break;
            case 3 : stampa(&root);
                     break;
            case 0: break;
            default : printf("\nErrore");
                      getchar();
                      getchar();
                      break;

        }
    }while(ch != 0);

    free(root);
}
