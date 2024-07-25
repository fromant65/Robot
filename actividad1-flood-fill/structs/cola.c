#include <stdlib.h>
#include "cola.h"

Cola *crear_cola() {
  Cola *c = malloc(sizeof(Cola));
  if (c == NULL)
    return NULL;
  c->first = NULL;
  c->last = NULL;
  return c;
}

Nodo *desencolar(Cola * c) {
  if (c->first == NULL)
    return NULL;
  ColaNodo *top = c->first;
  c->first = c->first->next;
  if (c->first == NULL) {
    c->last = NULL;
  }
  Nodo *data = top->data;
  free(top);
  return data;
}

void encolar(Cola * c, Nodo * n) {
  ColaNodo *nuevo = malloc(sizeof(ColaNodo));
  if (nuevo == NULL)
    return;
  nuevo->data = n;
  nuevo->next = NULL;
  if (c->first == NULL) {
    c->first = nuevo;
    c->last = nuevo;
  } else {
    c->last->next = nuevo;
    c->last = nuevo;
  }
}

void liberar_cola(Cola * c) {
  while (c->first != NULL) {
    desencolar(c);
  }
  free(c);
}
