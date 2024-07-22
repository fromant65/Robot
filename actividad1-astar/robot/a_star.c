#include "a_star.h"
#include "robot.h"
#include <stdlib.h>
#include <stdio.h>
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
        algData.closedList[top->pos.x][top->pos.y]=1;
        if(top->pos.x==fin.x && top->pos.y==fin.y){
            camino=reconstruir_camino(top);
        }else{
            Coord* vecinos = obtener_vecinos(top->pos);
            for(int i=0;i<4;i++){
                int cx = vecinos[i].x, cy=vecinos[i].y;
                if(cx>=0 && cy>=0 && cx < e.N && cy < e.M &&
                algData.closedList[cx][cy]==0 && posicion_valida(cx,cy,e)){
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
            free(vecinos);
        }
    }
    liberar_a_star_data(algData,e.N, e.M);
    return camino;
}


/**
 * @brief dada una casilla de finalización, 
 * reconstruye el camino desde esa casilla hasta que encuentra una sin padre.
 */
Stack reconstruir_camino(HeapElem *fin){
    Stack s = crear_stack();
    HeapElem* aux = fin;
    if(aux==NULL) return NULL;
    while(aux->parent!=NULL){
        //printf("current (%d %d) parent (%d %d) direccion %c\n", 
        //aux->pos.x, aux->pos.y, aux->parent->pos.x, aux->parent->pos.y,
        //calcular_direccion(aux->parent->pos, aux->pos));
        s=stack_push(s, calcular_direccion(aux->parent->pos,aux->pos));
        //print_stack(s);
        aux=aux->parent;
    }
    return s;
}

/**
 * @brief dada una casilla, devuelve un array con sus 4 vecinos ordenados como
 * v_up, v_right, v_down, v_left
 */
Coord* obtener_vecinos(Coord celda){
    Coord* vecinas = malloc(sizeof(Coord)*4);
    Coord up,right,down,left;
    up.x=celda.x-1;
    up.y=celda.y;
    down.x=celda.x+1;
    down.y=celda.y;
    right.x=celda.x;
    right.y=celda.y+1;
    left.x=celda.x;
    left.y=celda.y-1;
    vecinas[0]=up;
    vecinas[1]=right;
    vecinas[2]=down;
    vecinas[3]=left;
    return vecinas;
}
