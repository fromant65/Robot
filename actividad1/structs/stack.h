#ifndef STACK_H
#define STACK_H

typedef struct _Stack{
    void* data;
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
void stack_push(Stack s, void* data);

/**
 * @brief Elimina el tope del stack y lo devuelve
 */
void* stack_pop(Stack s);

/**
 * @brief Libera toda la memoria usada por el stack
 */
void stack_free(Stack s);

#endif