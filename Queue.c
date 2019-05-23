//
// Created by SysAdmin on 23/05/2019.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Queue{
    int key;
    struct Queue *next;
}Queue;


void enqueue(int elemento,Queue *testa, Queue *tail){
    //inserimento in coda
    if(tail->key ==  99999999){
        //primo elemento
        testa->next = NULL;
        testa->key = elemento;
        printf("\nqui");
        tail = testa;
        printf("\n%d",tail->key);
    }else{
        printf("\n%d elemento",tail->key);
        tail->next = (Queue *)malloc(sizeof(Queue));
        tail = tail->next;
        tail->key = elemento;
        tail->next = NULL;
        printf("\necco");
        printf("\n%d",tail->key);
    }
}

Queue* dequeue(Queue *testa, Queue *tail){
    int el;
    Queue *temp;
    temp = testa;
    el = testa->key;
    testa = testa->next;
    printf("\nEliminato %d",el);
    free(temp);
    return testa;
}

void stampa(Queue *coda) {
    Queue *temp = coda;
    printf("\nSTAMPA CODA :");
    if(coda->key ==  99999999)
        return;
    while (temp != NULL){
        printf(" %d", temp->key);
        temp = temp->next;
    }
}

int main(){
    int scelta;
    Queue *coda =(Queue*) malloc(sizeof(Queue));
    Queue *tail = (Queue*)malloc(sizeof(Queue));
    tail = coda;
    tail->key = 99999999;
    do{
        printf("\nMENU : "
               "1 : inserire un elemento \n2 : cancellare un elemento \n3: stampare la coda"
               "\n4: uscire\n");
        scanf("%d",&scelta);
        switch(scelta){
            case 1:
                printf("\nChe elemento vuoi inserire?\n");
                int el;
                scanf("%d",&el);
                if(coda == NULL){
                    coda =(Queue*) malloc(sizeof(Queue));
                    tail = (Queue*)malloc(sizeof(Queue));
                    tail = coda;
                    tail->key = 99999999;
                }
                enqueue(el, coda,tail);
                while(tail->next != NULL)
                    tail = tail->next;
                if(coda == NULL || tail == NULL)
                    printf("\nERRORE");
                printf("\nInserimento avvenuto con successo");
                break;
            case 2:
                if(coda->key == 99999999 || coda == NULL){
                    printf("\nImpossibile eliminare elementi la coda è vuota");
                    break;
                }
                coda = dequeue(coda, tail);
                if(coda == NULL){
                    tail = NULL;
                    printf("\ncoda vuota");
                    coda =(Queue*) malloc(sizeof(Queue));
                    tail = (Queue*)malloc(sizeof(Queue));
                    tail = coda;
                    tail->key = 99999999;

                }else {
                    if (coda->next == NULL)
                        tail = coda;
                }
                break;
            case 3:
                stampa(coda);
                break;
        }
    }while(scelta != 4);



}
