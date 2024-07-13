#include "entorno.h"
#include "../robot/floodfill.h"
#include <stdlib.h>
Entorno crear_entorno(int N, int M, Coord meta){
    Entorno e;
    e.N=N;
    e.M=M;
    e.grilla = malloc(sizeof(Nodo**)*N);
    for(int i=0; i<N; i++){
        e.grilla[i]=malloc(sizeof(Nodo*)*M);
        for(int j=0; j<M;j++){
            e.grilla[i][j]=crear_nodo(i,j,0,false);
        }
    }
    e=calcular_floodfill(meta, e);
    return e;
}
void liberar_entorno(Entorno e){
    for(int i=0; i<e.N; i++){
        for(int j=0; j<e.M;j++){
            free(e.grilla[i][j]);
        }
        free(e.grilla[i]);
    }
    free(e.grilla);
}