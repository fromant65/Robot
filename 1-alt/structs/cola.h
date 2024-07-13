#ifndef QUEUE_H
#define QUEUE_H
#include "nodo.h"

typedef struct _Cola{
    Nodo *data;
    struct _Cola *next;
}ColaNodo;

typedef struct{
    ColaNodo* first;
    ColaNodo* last;
}Cola;

Cola* crear_cola();
Nodo* desencolar(Cola* c);
void encolar(Cola* c, Nodo* n);
void liberar_cola(Cola *c);

#endif