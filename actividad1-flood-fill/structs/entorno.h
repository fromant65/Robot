#ifndef ENTORNO_H
#define ENTORNO_H
#include "nodo.h"
#include "coord.h"
typedef struct{
    Nodo*** grilla;
    int N,M;
}Entorno;
/**
 * @brief dado el tamaño del entorno y una coordenada de meta,
 * crea un entorno con las distancias de floodfill aplicadas al mismo.
 */
Entorno crear_entorno(int N, int M, Coord meta);
void liberar_entorno(Entorno e);
#endif