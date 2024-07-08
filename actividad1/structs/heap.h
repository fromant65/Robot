#ifndef HEAP_H
#define HEAP_H
#include "function_prototypes.h"

typedef struct{
    void* data;
    int prioridad;
}HeapElem;

/**
 * @brief Heap usado como cola de prioridad
 */
typedef struct{
    HeapElem* buffer;
    int fin, capacidad;
}Heap;

/**
 * @brief Crea una cola de prioridad vacía del tamaño dado
 * con el tamaño indicado de tipo de dato
 */
Heap* crear_heap(int capacidad, int typeSize);

/**
 * @brief libera la memoria usada por el Heap pasado
 * Usa la FuncionDestructora para liberar la memoria de
 * los datos de cada HeapElem del buffer
 */
void liberar_heap(Heap* h, FuncionDestructora f);

/**
 * @return el elemento de menor prioridad del Heap dado
 */
HeapElem heap_dequeue(Heap* h);

void flotar_elemento(Heap* h, int indice);
void hundir_elemento(Heap* h, int indice);

#endif