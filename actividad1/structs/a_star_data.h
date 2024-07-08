#ifndef A_STAR_DATA_H
#define A_STAR_DATA_H

#include "heap.h"
#include "coord.h"

/**
 * @brief Representa las estructuras usadas en A*
 * El heap es un heap de elementos de tipo Coord
 */
typedef struct{
    Heap* heap;
    Coord** openList;
    Coord** closedList;
    Coord** padres;
}AStartData;

#endif