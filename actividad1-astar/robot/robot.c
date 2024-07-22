#include <stdlib.h>
#include <stdio.h>
#include "robot.h"
#include "a_star.h"

/**
 * @brief Funcion interna que calcula el valor absoluto de un numero
 */
int abs(int a){
    return a>=0?a:-a;
}

/**
 * @brief Toma dos enteros x,y y una matriz bidimensional con sus dimensiones
 * @return 1 si la casilla en la posición (x,y) está vacía, 
 * 0 si es un obstaculo
 */
int posicion_valida(int x, int y, Entorno e){
    if(x>=e.N || x<0 || y>=e.M || y<0 || e.grilla[x][y]==0)
        return 0;
    return 1;
}

/**
 * @brief recibe las dimensiones y posición inicial del robot
 * e inicializa un Robot con esos datos
 * @return un puntero al Robot inicializado
 */
Robot* crear_robot(int N, int M, int i1, int i2, int j1, int j2){
    Robot* robot = malloc(sizeof(Robot));
    Coord inicio = {.x=i1,.y=i2};
    Coord meta = {.x=j1,.y=j2};
    Entorno entorno;
    entorno.M=M;
    entorno.N=N;
    entorno.grilla = malloc(sizeof(int*)*N);
    for(int i=0; i<N; i++){
        entorno.grilla[i]=malloc(sizeof(int)*M);
        for(int j=0; j<M;j++){
            entorno.grilla[i][j]=1;
        }
    }
    Stack s= calcular_camino(inicio,meta,entorno);
    RobotRecorrido rec;
    rec.camino=malloc(sizeof(char)*N*M);
    rec.capacidad=N*M;
    rec.largo=0;
    robot->posicion = inicio;
    robot->meta = meta;
    robot->entorno = entorno;
    robot->recorridoHecho=rec;
    robot->recorridoPlaneado=s;
    return robot;
}

/**
 * @brief libera la memoria usada por el robot dado
 */
void liberar_robot(Robot* r){
    free(r->recorridoHecho.camino);
    stack_free(r->recorridoPlaneado);
    free_entorno(r->entorno);
    free(r);
}

/**
 * @brief Realiza el primer movimiento en la lista de
 * caminoARecorrer. 
 * Si el movimiento no es válido, recalcula el camino a recorrer.
 * Si el movimiento es válido, lo saca de caminoARecorrer
 * y lo pone al final de caminoRecorrido, y cambia las coordenadas
 * del robot a la posición a la que se movió. 
 */
void hacer_movimiento(Robot* r, Entorno e){
    char top_move = stack_pop(&(r->recorridoPlaneado));
    Coord next_pos = calcular_movimiento(top_move,r->posicion);
    int next_x=next_pos.x;
    int next_y=next_pos.y;
    if(posicion_valida(next_x, next_y,e)){
        r->posicion=next_pos;
        if(r->recorridoHecho.capacidad<=r->recorridoHecho.largo){
            r->recorridoHecho.capacidad *= 2;
            r->recorridoHecho.camino=realloc(r->recorridoHecho.camino,sizeof(char)*r->recorridoHecho.capacidad);
        }
        r->recorridoHecho.camino[r->recorridoHecho.largo++]=top_move;
    }else{
        r->entorno.grilla[next_x][next_y]=0;
        stack_free(r->recorridoPlaneado);
        r->recorridoPlaneado=calcular_camino(r->posicion,r->meta,r->entorno);
        hacer_movimiento(r,e);
    }
}

/**
 * @brief Recibe una dirección ('U', 'L', 'R', 'D') y una posición
 * y calcula a qué casilla se llegaría al hacer el movimiento
 */
Coord calcular_movimiento(char direccion, Coord posicion){
    int next_x=direccion=='U'?posicion.x-1:direccion=='D'?posicion.x+1:posicion.x; 
    int next_y=direccion=='L'?posicion.y-1:direccion=='R'?posicion.y+1:posicion.y;
    Coord ret = {next_x, next_y};    
    return ret;
}

/**
 * @brief Recibe dos casillas vecinas p1 y p2 y calcula en qué dirección
 * está p2 respecto a p1. Si las casillas no son vecinas, devuelve '\0'
 */
char calcular_direccion(Coord p1, Coord p2){
    if(abs(p1.x-p2.x)>1 || abs(p1.y-p2.y)>1) return '\0';
    if(abs(p1.x-p2.x)==1 && abs(p1.y-p2.y==1)) return '\0';
    if(p1.x>p2.x) return 'U';
    if(p1.x<p2.x) return 'D';
    if(p1.y>p2.y) return 'L';
    return 'R';
}


/**
 * @brief Dadas dos coordenadas, calcula su distancia de Manhattan
 */
int heuristica(Coord init, Coord fin){
    return abs(init.x-fin.x)+abs(init.y-fin.y);
}