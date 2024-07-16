#include "nodo.h"
#include <stdlib.h>

Nodo* crear_nodo(int x, int y, int distancia, bool obstaculo){
    Coord pos = {x,y};
    Nodo* n = malloc(sizeof(Nodo));
    n->distancia=distancia;
    n->obstaculo=obstaculo;
    n->pos=pos;
    n->visitado=false;
    return n;
}