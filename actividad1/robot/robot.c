#include <stdlib.h>
#include "robot.h"
#include "a_star.h"
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
    Coord inicio = {i1,i2};
    Coord meta = {j1,j2};
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
    Stack s= calcularCamino(inicio,meta,entorno);
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
    free(r->recorridoHecho->camino);
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
    char* top_move = stack_pop(r->recorridoPlaneado);
    int i1=r->posicion.x, i2=r->posicion.y;
    Coord next_pos = calcular_movimiento(top_move[0],r->posicion);
    int next_x=next_pos.x;
    int next_y=next_pos.y;
    if(posicion_valida(next_x, next_y,e)){
        r->posicion=next_pos;
        r->recorridoHecho.camino[r->recorridoHecho.largo++]=top_move[0];
    }else{
        r->entorno.grilla[next_x][next_y]=0;
        char* siguientePaso = stack_pop(r->recorridoPlaneado);
        Coord next_empty = calcular_movimiento(siguientePaso[0], next_pos);
        //Calculamos un nuevo camino desde la posición del robot 
        //hasta el punto al que hubieramos llegado sin obstáculo
        Stack new_path = calcular_camino(r->posicion, next_empty,r->entorno);
        Stack plan_previo = r->recorridoPlaneado;
        Stack aux = new_path;
        for(;aux->next!=NULL; aux=aux->next);
        aux->next=plan_previo;
        r->recorridoPlaneado = new_path;
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
}
