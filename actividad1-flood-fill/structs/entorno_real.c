#include "entorno_real.h"
#include <stdlib.h>
EntornoReal crear_entorno_real(int n, int m) {
  bool **grilla = malloc(sizeof(bool *) * n);
  for (int i = 0; i < n; i++) {
    grilla[i] = malloc(sizeof(bool) * m);
    for (int j = 0; j < m; j++) {
      grilla[i][j] = true;
    }
  }
  EntornoReal e = { grilla, n, m };
  return e;
}

void liberar_entorno_real(EntornoReal e) {
  for (int i = 0; i < e.N; i++) {
    free(e.grilla[i]);
  }
  free(e.grilla);
}
