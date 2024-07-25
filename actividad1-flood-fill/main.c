#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./structs/program_data.h"
#include "./lectura/leer_archivo.h"
#include "./robot/robot.h"
int main(int argc, char **argv) {
  srand(time(NULL));
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
    EntornoReal e = { data->entorno, data->N, data->M };
    Robot *r =
        crear_robot(data->N, data->M, data->i1, data->i2, data->j1, data->j2);
    while (r->meta.x != r->pos.x || r->meta.y != r->pos.y) {
      hacer_movimiento(r, e);
    }
    r->camino = insertar_char(r->camino, '\0');
    printf("%s", r->camino.buffer);
    liberar_robot(r);
    liberar_entorno_real(e);
    free(data);
  }
  return 0;
}
