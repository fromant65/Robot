#include "leer_archivo.h"
#include <stdlib.h>

ProgramData *leer_archivo(FILE * f) {
  ProgramData *data = malloc(sizeof(ProgramData));
  if (data == NULL)
    return data;
  int n, m, d, res;
  res = fscanf(f, "%d%d%d", &n, &m, &d);
  if (res != 3) {
    free(data);
    return NULL;
  }
  data->N = n;
  data->M = m;
  data->D = d;
  res = fscanf(f, "%d%d", &n, &m);
  if (res != 2) {
    free(data);
    return NULL;
  }
  data->i1 = n;
  data->i2 = m;
  res = fscanf(f, "%d%d", &n, &m);
  if (res != 2) {
    free(data);
    return NULL;
  }
  data->j1 = n;
  data->j2 = m;
  //inicializamos memoria para el entorno
  data->entorno = malloc(sizeof(unsigned int *) * data->N);
  if (data->entorno == NULL) {
    free(data);
    return NULL;
  }
  for (int i = 0; i < data->N; i++) {
    data->entorno[i] = malloc(sizeof(unsigned int) * data->M);
    if (data->entorno[i] == NULL)
      i--;
  }
  //leemos el entorno
  char c = fgetc(f);
  int i = 0, j = 0, valid_format = 1;
  while ((c = fgetc(f)) != EOF && valid_format) {
    if ((c == '\n' && j != data->M) || i > data->N
        || (c != '.' && c != '#' && c != '\n')) {
      valid_format = 0;
    } else if (c == '\n') {
      i++;
      j = 0;
    } else
      data->entorno[i][j++] = c == '.' ? 1 : 0;
  }

  return valid_format ? data : NULL;
}

void print_data(ProgramData * data) {
  if (data == NULL)
    printf("NO DATA");
  else {
    printf("N:%d, M:%d, D:%d\n", data->N, data->M, data->D);
    printf("i1:%d, i2:%d\n", data->i1, data->i2);
    printf("j1:%d, j2:%d\n", data->j1, data->j2);
    printf("   ");
    for (int i = 0; i < data->M; i++) {
      printf("%d%s", i, i > 9 ? " " : "  ");
    }
    printf("\n");
    for (int i = 0; i < data->N; i++) {
      printf("%d%s", i, i > 9 ? " " : "  ");
      for (int j = 0; j < data->M; j++) {
        printf("%c  ", data->entorno[i][j] ? '.' : '#');
      }
      printf("\n");
    }
  }
}
