#ifndef HEAP_H
#define HEAP_H
#include "coord.h"
/**
 * Será un heap utilizado para A*, por lo cual la prioridad será la suma de g y h
 */
typedef struct _HeapNode {
  Coord pos;
  int f, g, h;
  struct _HeapNode *parent;
  int obstaculo;                //1 significa obstaculo, 0 significa camino abierto
} HeapElem;

/**
 * @brief Heap usado como cola de prioridad
 */
typedef struct {
  HeapElem **buffer;            //Array a punteros a HeapElem
  int fin, capacidad;
} Heap;

/**
 * @brief Dados los datos de un nodo del heap, lo crea y devuelve un puntero al mismo
 */
HeapElem *crear_heap_elem(Coord pos, int f, int g, int h, HeapElem * parent,
                          int obstaculo);

/**
 * @brief Crea una cola de prioridad vacía del tamaño dado
 * con el tamaño indicado de tipo de dato
 */
Heap *crear_heap(int capacidad);

/**
 * @brief libera la memoria usada por el Heap pasado
 * No libera la memoria ocupada por cada uno de los elementos del buffer
 */
void liberar_heap(Heap * h);

/**
 * @return el elemento de menor prioridad del Heap dado
 */
HeapElem *heap_dequeue(Heap * h);

/**
 * @brief dado un elemento con su prioridad, 
 * lo agrega a la cola de prioridad representada por el heap
 */
void heap_enqueue(Heap * h, HeapElem * elem);

void flotar_elemento(Heap * h, int indice);
void hundir_elemento(Heap * h, int indice);

#endif
