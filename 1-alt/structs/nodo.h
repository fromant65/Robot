#ifndef NODO_H
#define NODO_H
#include <stdbool.h>
#include "coord.h"

typedef struct{
    Coord pos;
    int distancia;
    bool obstaculo; //true: obstaculo; false: libre
}Nodo;

Nodo* crear_nodo(int x, int y, int distancia, bool obstaculo);

#endif