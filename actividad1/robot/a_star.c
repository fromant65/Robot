#include "a_star.h"
#include "robot.h"
#include <stdlib.h>
/**
 * @brief dados un entorno y una coordenada de inicio y fin
 * devuelve un stack con los movimientos a hacer para realizar
 * el recorrido de forma óptima
 */
Stack calcular_camino(Coord init, Coord fin, Entorno e){
    AStartData algData = crear_a_star_data(e.N, e.M);
    int h_init = heuristica(init,fin);
    HeapElem *inicio = crear_heap_elem(init,h_init, 0, h_init, NULL, 0);
    heap_enqueue(algData.openList, inicio);
    algData.hash[init.x][init.y]=inicio;
    Stack camino = NULL;
    while(algData.openList->fin>0 && camino==NULL){
        HeapElem *top = heap_dequeue(algData.openList);
        algData.hash[top->pos.x][top->pos.y]=NULL;
        if(top->pos.x==fin.x && top->pos.y==fin.y){
            camino=reconstruir_camino(top);
        }else{
            Coord* vecinos = obtener_vecinos(top->pos);
            for(int i=0;i<4;i++){
                int cx = vecinos[i].x, cy=vecinos[i].y;
                if(algData.closedList[cx][cy]==0 && algData.hash[cx][cy]->obstaculo==0){
                    int g_tentativo = top->g+1;
                    if(algData.hash[cx][cy]==NULL){
                        int h=heuristica(vecinos[i], fin);
                        int f=g_tentativo+h;
                        HeapElem *m = crear_heap_elem(vecinos[i], g_tentativo,h,f,top,0);
                        heap_enqueue(algData.openList,m);
                        algData.hash[cx][cy]=m;
                    }else if(g_tentativo<algData.hash[cx][cy]->g){
                        algData.hash[cx][cy]->g=g_tentativo;
                        algData.hash[cx][cy]->f=g_tentativo+algData.hash[cx][cy]->h;
                        algData.hash[cx][cy]->parent=top;
                    }
                }
            }
        }
    }
    return camino;
}
