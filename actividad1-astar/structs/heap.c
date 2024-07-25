#include "heap.h"
#include "stdlib.h"

/**
 * @brief Dados los datos de un nodo del heap, lo crea y devuelve un puntero al mismo
 */
HeapElem *crear_heap_elem(Coord pos, int f, int g, int h, HeapElem * parent,
                          int obstaculo) {
  HeapElem *elem = malloc(sizeof(HeapElem));
  elem->pos = pos;
  elem->f = f;
  elem->g = g;
  elem->h = h;
  elem->parent = parent;
  elem->obstaculo = obstaculo;
  return elem;
}

/**
 * @brief Crea una cola de prioridad vacía del tamaño dado
 * con el tamaño indicado de tipo de dato
 */
Heap *crear_heap(int capacidad) {
  Heap *h = malloc(sizeof(Heap));
  h->buffer = malloc(sizeof(HeapElem *) * capacidad);
  h->buffer[0] = NULL;
  h->capacidad = capacidad;
  h->fin = 0;
  return h;
}

/**
 * @brief libera la memoria usada por el Heap pasado
 * No libera la memoria ocupada por cada uno de los elementos del buffer
 */
void liberar_heap(Heap * h) {
  free(h->buffer);
  free(h);
}

/**
 * @return el elemento de menor prioridad del Heap dado
 */
HeapElem *heap_dequeue(Heap * h) {
  if (h->fin == 0)
    return NULL;
  HeapElem *primero = h->buffer[1];
  h->buffer[1] = h->buffer[h->fin];
  h->buffer[h->fin--] = NULL;
  hundir_elemento(h, 1);
  return primero;
}

/**
 * @brief dado un elemento con su prioridad, 
 * lo agrega a la cola de prioridad representada por el heap
 */
void heap_enqueue(Heap * h, HeapElem * elem) {
  h->fin++;
  h->buffer[h->fin] = elem;
  flotar_elemento(h, h->fin);
}

/**
 * @brief Funcion interna para cambiar dos elementos de lugar en el heap
 */
void swap(Heap * h, int i1, int i2) {
  HeapElem *aux = h->buffer[i1];
  h->buffer[i1] = h->buffer[i2];
  h->buffer[i2] = aux;
}

void flotar_elemento(Heap * h, int indice) {
  if (indice <= 1 || indice > h->fin)
    return;
  if (h->buffer[indice]->f < h->buffer[indice / 2]->f) {
    swap(h, indice, indice / 2);
    flotar_elemento(h, indice / 2);
  }
}

void hundir_elemento(Heap * h, int indice) {
  if (indice < 1 || indice * 2 > h->fin)
    return;
  int menorHijo = indice * 2;
  if (indice * 2 + 1 <= h->fin
      && h->buffer[indice * 2 + 1]->f < h->buffer[indice * 2]->f) {
    menorHijo = indice * 2 + 1;
  }
  if (h->buffer[indice]->f > h->buffer[menorHijo]->f) {
    swap(h, indice, menorHijo);
    hundir_elemento(h, menorHijo);
  }
}
