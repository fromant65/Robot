#include "heap.h"
#include <stdlib.h>

void swap(Heap * h, int i1, int i2) {
  if (i1 != i2) {
    Node *aux = h->buffer[i1];
    h->buffer[i1] = h->buffer[i2];
    h->buffer[i2] = aux;
    h->buffer[i1]->order = i1;
    h->buffer[i2]->order = i2;
  }
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
  first->order = -1;
  if (h->length > 1) {
    h->buffer[1] = h->buffer[h->length];
    h->buffer[1]->order = 1;
    heap_sink(h, 1);
  }
  h->buffer[h->length] = NULL;
  h->length--;
  return first;
}

void heap_enqueue(Heap * h, Node * elem) {
  h->length++;
  h->buffer[h->length] = elem;
  elem->order = h->length;
  heap_float(h, h->length);
}

void heap_remove(Heap * h, Node * elem) {
  int index = elem->order;
  if (index == -1)
    return;
  Node *toRemove = h->buffer[index];
  swap(h, index, h->length);
  h->length--;
  toRemove->order = -1;
  heap_sink(h, index);
  heap_float(h, index);
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
  if (h->length == 1 || index < 1 || index * 2 > h->length)
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

int left_child(int index) {
  return 2 * index;
}

int right_child(int index) {
  return 2 * index + 1;
}

bool is_in_bounds(int index, int length) {
  return index <= length;
}

bool check_heap_condition(Heap * h) {
  for (int i = 1; i <= h->length; ++i) {
    int left = left_child(i);
    int right = right_child(i);

    if (is_in_bounds(left, h->length)
        && compare_keys(h->buffer[i]->key, h->buffer[left]->key) > 0) {
      return false;
    }

    if (is_in_bounds(right, h->length)
        && compare_keys(h->buffer[i]->key, h->buffer[right]->key) > 0) {
      return false;
    }
  }
  return true;
}
