#include "floodfill.h"
#include <stdlib.h>
#include <stdio.h>
#include "robot.h"

/**
 * @brief Realiza el primer calculo de Floodfill para el entorno dado
 * donde la distancia de la meta es 0
 */
Entorno calcular_floodfill(Coord meta, Entorno e){
    for(int i =0; i<e.N; i++){
        for(int j=0;j<e.M;j++){
            e.grilla[i][j]->distancia=heuristica(e.grilla[i][j]->pos, meta);
        }
    }
    return e;
}

/**
 * @brief Dado un entorno con los valores de Floodfill inicializados
 * y una coordenada de un obstaculo (conflicto), recalculamos
 * los valores de floodfill en ese entorno a partir del nodo conflicto
 */
Entorno recalcular_floodfill(Coord conflicto, Entorno e){
    Nodo *obstaculo=e.grilla[conflicto.x][conflicto.y];
    Cola *c = crear_cola();
    Nodo** vecinosObs = get_vecinos(obstaculo, e);
    for(int i=0;i<4;i++){
        if(vecinosObs[i]!=NULL && vecinosObs[i]->obstaculo==false){
            encolar(c,vecinosObs[i]);
        }
    }
    free(vecinosObs);
    while(c->first!=NULL){
        Nodo* top = desencolar(c);
        Coord m = get_vecino_menor(top->pos, e);
        Nodo* vecino_menor;
        if((m.x==-1 && m.y==-1) || top->distancia==0)
            vecino_menor = NULL;
        else
            vecino_menor = e.grilla[m.x][m.y];
        if(vecino_menor && top->distancia<=vecino_menor->distancia){
            top->distancia=vecino_menor->distancia+1;
            Nodo** vecinos = get_vecinos(top, e);
            for(int i=0; i<4;i++){
                if(vecinos[i]!=NULL && 
                !vecinos[i]->obstaculo 
                && vecinos[i]->distancia!=0
                ){
                    encolar(c, vecinos[i]);
                }
            }
            free(vecinos);
        }
    }
    free(c);
    return e;
}

Nodo** shuffle(Nodo** arr, int len){
    for(int i=0; i<len*2;i++){
        int a=rand()%len, b=rand()%len;
        Nodo* aux = arr[a];
        arr[a]=arr[b];
        arr[b]=aux;
    }
    return arr;
}

/**
 * @brief Devuelve un array de nodos vecinos de un nodo dado.
 * Usamos shuffle para que no considere siempre el mismo orden de direcciones
 * Esto en ciertos casos puede hacer mas rapido el camino.
 */
Nodo** get_vecinos(Nodo* n, Entorno e){
    Nodo** vecinos = malloc(sizeof(Nodo*)*4);
    int cx=n->pos.x, cy=n->pos.y;
    vecinos[0]=cx>0?e.grilla[cx-1][cy]:NULL;
    vecinos[1]=cy<e.M-1?e.grilla[cx][cy+1]:NULL;
    vecinos[2]=cx<e.N-1?e.grilla[cx+1][cy]:NULL;
    vecinos[3]=cy>0?e.grilla[cx][cy-1]:NULL;
    //vecinos = shuffle(vecinos, 4);
    return vecinos;
}