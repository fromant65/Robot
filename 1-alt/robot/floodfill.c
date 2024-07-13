#include "floodfill.h"
#include <stdlib.h>
#include <stdio.h>
#include "robot.h"


/**
 * @brief Realiza el primer calculo de Floodfill para el entorno dado
 * donde la distancia de la meta es 0
 */
Entorno calcular_floodfill(Coord meta, Entorno e){
    Cola *c = crear_cola();
    Nodo* metaN = e.grilla[meta.x][meta.y];
    EntornoReal aProcesar = crear_entorno_real(e.N, e.M); //true representa que aun no se visitó la casilla
    metaN->distancia=0;
    encolar(c, metaN);
    aProcesar.grilla[meta.x][meta.y]=false;
    while(c->first!=NULL){
        Nodo* frente = desencolar(c);
        Nodo** vecinos = get_vecinos(frente, e);
        for(int i=0; i<4; i++){
            int cx=vecinos[i]!=NULL?vecinos[i]->pos.x:-1;
            int cy=vecinos[i]!=NULL?vecinos[i]->pos.y:-1;
            if(cx>=0 && cy>=0 && aProcesar.grilla[cx][cy]==true){
                aProcesar.grilla[cx][cy]=false;
                e.grilla[cx][cy]->distancia=frente->distancia+1;
                encolar(c,vecinos[i]);
            }
        }
        free(vecinos);
    }
    liberar_entorno_real(aProcesar);
    free(c);
    return e;
}

/**
 * @brief Dado un entorno con los valores de Floodfill inicializados
 * y una coordenada vecina a un obstaculo (conflicto), recalculamos
 * los valores de floodfill en ese entorno a partir del nodo conflicto
 */
Entorno recalcular_floodfill(Coord conflicto, Entorno e){
    Nodo *inicio=e.grilla[conflicto.x][conflicto.y];
    Cola *c = crear_cola();
    encolar(c,inicio);
    while(c->first!=NULL){
        Nodo* top = desencolar(c);
        Coord m = get_vecino_menor(top->pos, e);
        Nodo* vecino_menor = e.grilla[m.x][m.y];
        if(top->distancia>vecino_menor->distancia+1){
            top->distancia=vecino_menor->distancia+1;
            Nodo** vecinos = get_vecinos(top, e);
            for(int i=0; i<4;i++){
                if(!vecinos[i]->obstaculo){
                    encolar(c, vecinos[i]);
                }
            }
            free(vecinos);
        }
    }
    free(c);
    return e;
}

/**
 * @brief Devuelve un array de nodos vecinos de un nodo dado.
 */
Nodo** get_vecinos(Nodo* n, Entorno e){
    Nodo** vecinos = malloc(sizeof(Nodo*)*4);
    int cx=n->pos.x, cy=n->pos.y;
    vecinos[0]=cx>0?e.grilla[cx-1][cy]:NULL;
    vecinos[1]=cy<e.M-1?e.grilla[cx][cy+1]:NULL;
    vecinos[2]=cx<e.N-1?e.grilla[cx+1][cy]:NULL;
    vecinos[3]=cy>0?e.grilla[cx][cy-1]:NULL;
    return vecinos;
}