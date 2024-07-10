#ifndef A_STAR_H
#define A_START_H

#include "./../structs/a_star_data.h"
#include "./../structs/stack.h"
#include "./../structs/entorno.h"

/**
 * @brief dados un entorno y una coordenada de inicio y fin
 * devuelve un stack con los movimientos a hacer para realizar
 * el recorrido de forma óptima
 */
Stack calcular_camino(Coord init, Coord fin, Entorno e);

/**
 * @brief dada una casilla de finalización, 
 * reconstruye el camino desde esa casilla hasta que encuentra una sin padre.
 */
Stack reconstruir_camino(HeapElem *fin);

/**
 * @brief dada una casilla, devuelve un array con sus 4 vecinos ordenados como
 * v_up, v_rigth, v_down, v_left
 */
Coord* obtener_vecinos(Coord celda);

/**
 * @brief dada la información del algoritmo y una celda, devuelve el valor de g de su padre.
 */
int get_parent_g(AStartData data, Coord celda);
#endif