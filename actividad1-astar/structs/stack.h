#ifndef STACK_H
#define STACK_H

typedef struct _Stack{
    char data;
    struct _Stack* next;
}StackNode;

typedef StackNode* Stack;

/**
 * @return Un stack vacío
 */
Stack crear_stack();

/**
 * @brief Agrega un elemento al tope del stack
 */
Stack stack_push(Stack s, char data);

/**
 * @brief Elimina el tope del stack y lo devuelve
 */
char stack_pop(Stack* s);

/**
 * @brief Libera toda la memoria usada por el stack
 */
void stack_free(Stack s);

void print_stack(Stack s);

#endif