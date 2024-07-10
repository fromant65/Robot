#include <stdio.h>
#include <stdlib.h>
#include "./structs/program_data.h"
#include "./lectura/leer_archivo.h"
#include "./robot/robot.h"
#include "./robot/a_star.h"
int main(int argc, char** argv){
    ProgramData* data;
    if(argc>0){
        FILE* input = fopen(argv[1], "r");
        data = leer_archivo(input);
    }
    print_data(data);
    Robot *r = crear_robot(data->N, data->M, data->i1, data->i2, data->j1, data->j2);
    while(r->posicion.x!= r->meta.x || r->posicion.y!=r->meta.y){
        hacer_movimiento(r,r->entorno);
    }
    printf("%s", r->recorridoHecho.camino);
    return 0;
}
