#ifndef HEAP_H
#define HEAP_H
#include "node.h"

typedef struct{
    Node** buffer;
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
Node* heap_dequeue(Heap* h);

/**
 * @brief enqueues the given node in the given heap in its right position
 */
void heap_enqueue(Heap* h, Node *elem);

/**
 * @brief gets a Node and removes it from the queue
 */
void heap_remove(Heap*h, Node* elem);

void heap_float(Heap* h, int index);
void heap_sink(Heap* h, int index);

/**
 * @brief Gets 2 keys
 * @return -1 if the first key is smaller,
 * 1 if the first is bigger, 
 * 0 if they are equal
 * 
 */
int compare_keys(Key a, Key b);
#endif