#ifndef FLOODFILL_H
#define FLOODFILL_H
#include "./../structs/cola.h"
#include "./../structs/entorno.h"
#include "./../structs/coord.h"
typedef struct{
    Cola procesar;
}FloodfillData;

/**
 * @brief Realiza el primer calculo de Floodfill para el entorno dado
 * donde la distancia de la meta es 0
 */
Entorno calcular_floodfill(Coord meta, Entorno e);

/**
 * @brief Dado un entorno con los valores de Floodfill inicializados
 * y una coordenada vecina a un obstaculo (conflicto), recalculamos
 * los valores de floodfill en ese entorno a partir del nodo conflicto
 */
Entorno recalcular_floodfill(Coord conflicto, Entorno e);

/**
 * @brief Devuelve un array de nodos vecinos de un nodo dado.
 */
Nodo** get_vecinos(Nodo* n, Entorno e);
#endif