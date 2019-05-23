//
// Created by SysAdmin on 14/05/2019.
//
#include <stdio.h>
#include <stdlib.h>
#define LEFT(x)2*x+1
#define RIGHT(x)2*x+2
#define PARENT(x)(x-1)/2

int max_min;

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
    if(max_min == 0) {
        int max = n;
        if (LEFT(n) < heap->size && heap->elem[LEFT(n)].valore > heap->elem[n].valore) {
            max = LEFT(n);
        }
        if (RIGHT(n) < heap->size && heap->elem[RIGHT(n)].valore > heap->elem[max].valore) {
            max = RIGHT(n);
        }
        if (max != n) {
            switch_node(&(heap->elem[n]), &(heap->elem[max]));
            heapify(heap, max);
        }
    }else{
        int min = n;
        if (LEFT(n) < heap->size && heap->elem[LEFT(n)].valore < heap->elem[n].valore) {
            min = LEFT(n);
        }
        if (RIGHT(n) < heap->size && heap->elem[RIGHT(n)].valore < heap->elem[min].valore) {
            min = RIGHT(n);
        }
        if (min != n) {
            switch_node(&(heap->elem[n]), &(heap->elem[min]));
            heapify(heap, min);
        }
    }
}

int min(Heap *heap, int i){
    if(max_min == 0){ //il minimo si trova fra le foglie
        if(LEFT(i) >= heap->size) // trovato il minimo vedo se non ha foglie
            return heap->elem[i].valore;
        int left = min(heap, LEFT(i));
        int right = min(heap, RIGHT(i));
        if(left <= right)
            return left;
        else
            return right;
    }else{
        return heap->elem[0].valore; //il minimo di un minheap è la radice
    }
}

int max(Heap *heap, int i){
    if(max_min == 0){
        //il massimo è la radice
        return heap->elem[0].valore;
    }else{
        if(LEFT(i) >= heap->size)
            return heap->elem[i].valore;
        int left = max(heap, LEFT(i));
        int right = max(heap, RIGHT(i));
        if(left >= right)
            return left;
        else return  right;
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
    if(max_min == 0) {
        while (i && nd.valore > heap->elem[PARENT(i)].valore) {
            heap->elem[i] = heap->elem[PARENT(i)];
            i = PARENT(i);
        }
    }else{
        while (i && nd.valore < heap->elem[PARENT(i)].valore) {
            heap->elem[i] = heap->elem[PARENT(i)];
            i = PARENT(i);
        }
    }
    heap->elem[i] = nd ;
}

int extract_max(Heap *heap){
    int h = max(heap, 0); //tiene conto di quale è il massimo
    int i= 0;
    while(i<heap->size && heap->elem[i].valore != h)
        i++;
    int res = heap->elem[i].valore;
    for(int j = i; j<heap->size-1; j++){
        heap->elem[j].valore = heap->elem[j+1].valore;
    }
    heap->size = heap->size-1;
    heap->elem = realloc(heap->elem,heap->size* sizeof(elemento));
    for(i = (heap->size -1)/2; i>= 0; i--){
        heapify(heap,i);
    }
    return res;

}

int extract_min(Heap *heap){
    int h = min(heap, 0);
    int i = 0;
    while(i<heap->size && heap->elem[i].valore != h)
        i++;
    int res  = heap->elem[i].valore;
    for(int j = i; j<heap->size-1; j++)
        heap->elem[j].valore = heap->elem[j+1].valore;
    heap->size = heap->size-1;
    heap->elem = realloc(heap->elem, heap->size* sizeof(elemento));
    for(i = (heap->size -1)/2; i>= 0; i--){
        heapify(heap,i);
    }
    return res;
}



void delete_elm(Heap *heap){
    if(heap->size){
        heap->elem[0] = heap->elem[(heap->size)-1];
        heap->size = heap->size-1;
        heap->elem = realloc(heap->elem,heap->size*sizeof(elemento));
        heapify(heap,0);
    }else{
        printf("\nè vuoto");
        free(heap->elem);
    }
}


void print(Heap *heap){
    for(int i = 0; i<heap->size; i++){
        printf("\nNODO %d FIGLIO DI %d, SINISTRO %d, DESTRO %d",heap->elem[i].valore,PARENT(i),
                LEFT(i),RIGHT(i));
    }
}

void delete_heap(Heap *heap){
    free(heap->elem);
    free(heap);
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
    printf("\ncosa vuoi creare maxheap(0) o minheap(1)?");
    scanf("%d",&max_min);
    printf("\nCREO L'HEAP...");
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
    printf("\nChe elemento vuoi inserire?");
    int add;
    scanf("%d",&add);
    add_elem(heap, add);
    printf("\nradice : %d",heap->elem[0].valore);
    print(heap);
    printf("\nil minimo %d", min(heap, 0));
    printf("\nil massimo %d", max(heap,0));
    printf("\nelimino un elemento");
    delete_elm(heap);
    print(heap);
    printf("\nmax %d",extract_max(heap));
    print(heap);
    printf("\nmin %d",extract_min(heap));
    print(heap);
    delete_heap(heap);

}

