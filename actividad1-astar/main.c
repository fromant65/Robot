#include <stdio.h>
#include <stdlib.h>
#include "./structs/program_data.h"
#include "./lectura/leer_archivo.h"
#include "./robot/robot.h"
#include "./robot/a_star.h"
int main(int argc, char **argv) {
  ProgramData *data = NULL;
  if (argc > 0) {
    FILE *input = fopen(argv[1], "r");
    if (input != NULL) {
      data = leer_archivo(input);
      fclose(input);
    } else
      printf("No se encontró el archivo %s\n", argv[1]);
  }
  if (data != NULL) {
    Robot *r =
        crear_robot(data->N, data->M, data->i1, data->i2, data->j1, data->j2);
    Entorno tablero = { data->N, data->M, (int **) data->entorno };
    while (r->posicion.x != r->meta.x || r->posicion.y != r->meta.y) {
      hacer_movimiento(r, tablero);
    }
    r->recorridoHecho.camino[r->recorridoHecho.largo] = '\0';
    printf("%s", r->recorridoHecho.camino);
  }

  return 0;
}
