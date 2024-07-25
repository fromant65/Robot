#ifndef ENTORNO_H
#define ENTORNO_H

typedef struct {
  int N, M;
  int **grilla;
} Entorno;

void free_entorno(Entorno e);

#endif
