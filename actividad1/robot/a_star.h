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

#endif