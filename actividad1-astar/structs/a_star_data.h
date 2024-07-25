#ifndef A_STAR_DATA_H
#define A_STAR_DATA_H

#include "heap.h"
#include "coord.h"


/**
 * @brief Representa las estructuras usadas en A*
 * El heap es un heap de elementos de tipo Coord
 */
typedef struct {
  Heap *openList;
  HeapElem ***hash;             //array bidimensional de punteros a HeapElem con los datos del Heap
  int **closedList;             //closedList[i][j]==1 si la celda está en la lista, sino 0
  HeapElem **nodos;             //Garbage collector para liberar la memoria de los nodos 
} AStartData;

/**
 * @brief Dadas las dimensiones del entorno, 
 * pedimos la memoria para cada una de las estructuras del algoritmo
 * y la devolvemos como estructura
 */
AStartData crear_a_star_data(int N, int M);

/**
 * @brief Libera toda la memoria usada por la estructura recibida de tipo AStarData
 */
void liberar_a_star_data(AStartData data, int N, int M);

#endif
