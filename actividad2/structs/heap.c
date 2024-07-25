#include "heap.h"
#include <stdlib.h>

void swap(Heap * h, int i1, int i2) {
  Node *aux = h->buffer[i1];
  h->buffer[i1] = h->buffer[i2];
  h->buffer[i2] = aux;
}

Heap *new_heap(int size) {
  Heap *h = malloc(sizeof(Heap));
  h->buffer = malloc(sizeof(Node *) * size);
  h->buffer[0] = NULL;
  h->size = size;
  h->length = 0;
  return h;
}

void free_heap(Heap * h) {
  free(h->buffer);
  free(h);
}


Node *heap_dequeue(Heap * h) {
  if (h->length == 0)
    return NULL;
  Node *first = h->buffer[1];
  h->buffer[1] = h->buffer[h->length];
  h->buffer[h->length--] = NULL;
  heap_sink(h, 1);
  return first;
}

void heap_enqueue(Heap * h, Node * elem) {
  h->length++;
  h->buffer[h->length] = elem;
  heap_float(h, h->length);
}

void heap_remove(Heap * h, Node * elem) {
  Node *toRemove = NULL;
  int rIndex = -1;
  for (int i = 1; i <= h->length && toRemove == NULL; i++) {
    if (h->buffer[i]->pos.x == elem->pos.x
        && h->buffer[i]->pos.y == elem->pos.y) {
      toRemove = elem;
      rIndex = i;
    }
  }
  if (toRemove != NULL && rIndex != -1) {
    swap(h, rIndex, h->length--);
    heap_sink(h, rIndex);
    heap_float(h, rIndex);
  }
}

void heap_float(Heap * h, int index) {
  if (index <= 1 || index > h->length)
    return;
  if (compare_keys(h->buffer[index]->key, h->buffer[index / 2]->key) == -1) {
    swap(h, index, index / 2);
    heap_float(h, index / 2);
  }
}

void heap_sink(Heap * h, int index) {
  if (index < 1 || index * 2 > h->length)
    return;
  int smallerChild = index * 2;
  if (index * 2 + 1 <= h->length &&
      compare_keys(h->buffer[index * 2 + 1]->key,
                   h->buffer[index * 2]->key) == -1)
    smallerChild = index * 2 + 1;
  if (compare_keys(h->buffer[index]->key, h->buffer[smallerChild]->key) == 1) {
    swap(h, index, smallerChild);
    heap_sink(h, smallerChild);
  }
}

Node *heap_top_elem(Heap * h) {
  if (h->length < 1)
    return NULL;
  return h->buffer[1];
}

int compare_keys(Key a, Key b) {
  if (a[0] == b[0])
    return a[1] < b[1] ? -1 : a[1] > b[1] ? 1 : 0;
  return a[0] < b[0] ? -1 : 1;
}

// Función auxiliar para obtener el índice del hijo izquierdo
int left_child(int index) {
  return 2 * index;
}

// Función auxiliar para obtener el índice del hijo derecho
int right_child(int index) {
  return 2 * index + 1;
}

// Función auxiliar para verificar si un índice está dentro de los límites del heap
bool is_in_bounds(int index, int length) {
  return index <= length;
}

// Función principal para verificar la condición del heap
bool check_heap_condition(Heap * h) {
  for (int i = 1; i <= h->length; ++i) {
    int left = left_child(i);
    int right = right_child(i);

    // Verificar si el hijo izquierdo está dentro de los límites y cumple la condición del heap
    if (is_in_bounds(left, h->length)
        && compare_keys(h->buffer[i]->key, h->buffer[left]->key) > 0) {
      return false;
    }
    // Verificar si el hijo derecho está dentro de los límites y cumple la condición del heap
    if (is_in_bounds(right, h->length)
        && compare_keys(h->buffer[i]->key, h->buffer[right]->key) > 0) {
      return false;
    }
  }
  return true;
}
