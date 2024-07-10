#include "a_star_data.h"
#include <stdlib.h>

/**
 * @brief Dadas las dimensiones del entorno, 
 * pedimos la memoria para cada una de las estructuras del algoritmo
 * y la devolvemos como estructura
 */
AStartData crear_a_star_data(int N, int M){
    AStartData data;
    data.openList=crear_heap(N*M);
    data.closedList=malloc(sizeof(int*)*N);
    data.hash=malloc(sizeof(HeapElem**)*N);
    data.nodos=malloc(sizeof(HeapElem*)*N*M);
    for(int i=0; i<N;i++){
        data.closedList[i]=malloc(sizeof(int)*M);
        data.hash[i]=malloc(sizeof(HeapElem*)*M);
        for(int j=0; j<M;j++){
            data.nodos[i*M+j]=NULL;
            data.hash[i][j]=NULL;
        }
    }
    return data;
}

/**
 * @brief Libera toda la memoria usada por la estructura recibida de tipo AStarData
 */
void liberar_a_star_data(AStartData data, int N, int M){
    // Liberar la lista cerrada
    for (int i = 0; i < N; i++) {
        free(data.closedList[i]);
    }
    free(data.closedList);
    
    // Liberar la tabla hash
    for (int i = 0; i < N; i++) {
        free(data.hash[i]);
    }
    free(data.hash);
    
    // Liberar los nodos
    for(int i=0; i<N*M; i++){
        free(data.nodos[i]);
    }
    free(data.nodos);
    
    // Liberar la lista abierta
    liberar_heap(data.openList);
}