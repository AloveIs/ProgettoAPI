//
// Created by SysAdmin on 23/05/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//STACK CON ARRAY
typedef struct Stack{
    int *array;
    signed int top; //indice dell'elemento inserito per ultimo
}Stack;

void push(Stack *st, int elemento){
    st->top = st->top +1;
    st->array[st->top] = elemento;
}

bool stack_empty(Stack *st){
    if(st->top == -1)
        return true;
    else
        return false;
}

int pop(Stack *st){
    if(stack_empty(st)){
        printf("\nERRORE DI UNDERFLOW");
        return 9999;
    }else{
        st->top = st->top-1;
        return st->array[st->top+1];
    }
}

void stampa(Stack *st){
    if(stack_empty(st)) {
        printf("\nERRORE DI UNDERFLOW: NON CONTIENE ELEMENTI");
    }else{
        printf("\nSTACK : ");
        for(int i = 0; i <= st->top; i++){
            printf("%d ",st->array[i]);
        }
    }
}

int main(){
    int n;
    printf("\nQuanti elementi puoi avere al massimo?");
    scanf("%d",&n);
    Stack *stack;
    stack = (Stack *)malloc(sizeof(Stack));
    stack->array = (int *)malloc(sizeof(int)*n);
    stack->top = -1; //assegno un valore di base
    int scelta;
    int elementoadd;


    do {
        printf("\nDigita 1 per aggiungere un elemento, 2 per rimuovere un elemento, 3 per stampare lo stack, 4 per uscire");
        scanf("%d",&scelta);
        switch (scelta) {
            case 1:
                if (stack->top == n - 1) {
                    printf("\nLo stack è pieno! Operazione impossibile");
                    break;
                } else {
                    printf("\nQuale elemento vuoi inserire?");
                    scanf("\n%d", &elementoadd);
                    push(stack, elementoadd);
                    printf("\nElemento aggiunto con successo");
                    break;
                }
            case 2:
                printf("\nAbbiamo eliminato l'elemento %d", pop(stack));
                break;
            case 3:
                stampa(stack);
                break;
        }
    }while(scelta != 4);

    free(stack->array);
    free(stack);

}
