#include "stack.h"
#include <stdlib.h>

/**
 * @return Un stack vacío
 */
Stack crear_stack(){
    return NULL;
}

/**
 * @brief Agrega un elemento al tope del stack
 */
void stack_push(Stack s, char data){
    Stack node=malloc(sizeof(StackNode));
    node->data=data;
    node->next=s;
    s=node;
}

/**
 * @brief Elimina el tope del stack y lo devuelve
 */
char stack_pop(Stack s){
    char top = s->data;
    Stack topS = s;
    s=s->next;
    free(topS);
    return top;
}

/**
 * @brief Libera toda la memoria usada por el stack
 */
void stack_free(Stack s){
    while(s!=NULL){
        Stack aux=s;
        s=s->next;
        free(aux);
    }
}
