#ifndef HEAP_H
#define HEAP_H
#include "nodo.h"

typedef struct{
    Nodo** buffer;
    int length, size;
}Heap;

/**
 * @brief Creates an empty priority queue of given size 
 * implemented with a heap.
 */
Heap* new_heap(int size);

/**
 * @brief frees the memory used by the heap
 */
void free_heap(Heap* h);

/**
 * @return the lowest priority element from the given heap
 */
Nodo* heap_dequeue(Heap* h);

/**
 * @brief enqueues the given node in the given heap in its right position
 */
void heap_enqueue(Heap* h, Nodo* elem);

void heap_float(Heap* h, int index);
void heap_sink(Heap* h, int index);

#endif