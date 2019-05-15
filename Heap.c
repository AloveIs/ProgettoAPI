//
// Created by SysAdmin on 14/05/2019.
//
#include <stdio.h>
#include <stdlib.h>
#define LEFT(x)2*x+1
#define RIGHT(x)2*x+2
#define PARENT(x)(x-1)/2

typedef struct elemento{
    int valore;
}elemento;

typedef struct Heap{
    int size; //tiene conto della grandezza dell'array
    elemento *elem;
}Heap;



void switch_node(elemento *e1, elemento *e2){
    //creo un elemento temporaneo
    elemento temp = *e1;
    *e1 = *e2;
    *e2 = temp;
}

void heapify(Heap *heap, int n){
    int max = n;
    if(LEFT(n) < heap->size && heap->elem[LEFT(n)].valore > heap->elem[n].valore){
        max = LEFT(n);
    }
    if(RIGHT(n) < heap->size && heap->elem[RIGHT(n)].valore > heap->elem[max].valore){
        max = RIGHT(n);
    }
    if(max != n){
        switch_node(&(heap->elem[n]),&(heap->elem[max]));
        heapify(heap,max);
    }
}

void create(Heap *heap, int *valori, int num){
    int i;
    for( i = 0; i<num; i++){
        if(heap->size){
            heap->elem = realloc(heap->elem,(heap->size+1)*sizeof(elemento));
        }else{
            //sto inserendo il primo elemento
            heap->elem = malloc(sizeof(elemento));
        }
        elemento e;
        e.valore = valori[i];
        heap->elem[(heap->size)++] = e;

    }

    //aggiunti tutti sistemo l'heap

    for(i = (heap->size -1)/2; i>= 0; i--){
        heapify(heap,i);
    }

}

void add_elem (Heap *heap, int el){
    elemento nd ;
    nd.valore = el ;

    int i = (heap->size)++ ;
    while(i && nd.valore > heap->elem[PARENT(i)].valore) {
        heap->elem[i] = heap->elem[PARENT(i)] ;
        i = PARENT(i) ;
    }
    heap->elem[i] = nd ;
}

void print(Heap *heap){
    for(int i = 0; i<heap->size; i++){
        printf("\nNODO %d FIGLIO DI %d, SINISTRO %d, DESTRO %d",heap->elem[i].valore,PARENT(i),
                LEFT(i),RIGHT(i));
    }
}


int main(){
    //dichiaro quanti elementi voglio inserire
    int n_elem;
    printf("\nQuanti elementi vuoi inserire?");
    scanf("%d",&n_elem);
    int array[n_elem];
    for(int i= 0; i<n_elem; i++){
        printf("\nINSERISCI UN NUMERO ");
        scanf("%d",&array[i]);
    }
    printf("\nCREO IL MAXHEAP...");
    //init dell'heap
    Heap *heap;
    heap = (Heap *)malloc(sizeof(heap));
    heap->size = 0;
    heap->elem = malloc(sizeof(elemento)*n_elem);
    //add array
    create(heap, array,n_elem);
    printf("\nradice : %d",heap->elem[0].valore);
    print(heap);
    //add 1 elem
    add_elem(heap, 20);
    printf("\nradice : %d",heap->elem[0].valore);
    print(heap);

}

