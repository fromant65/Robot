#ifndef ROBOT_H
#define ROBOT_H

#include "./../structs/robot_struct.h"

/**
 * @brief Toma dos enteros x,y y una matriz bidimensional con sus dimensiones
 * @return 1 si la casilla en la posición (x,y) está vacía, 
 * 0 si es un obstaculo
 */
int posicion_valida(int x, int y, Entorno e);

/**
 * @brief recibe las dimensiones, posición inicial y meta del robot
 * e inicializa un Robot con esos datos
 * @return un puntero al Robot inicializado
 */
Robot* crear_robot(int N, int M, int i1, int i2, int j1, int j2);

/**
 * @brief libera la memoria usada por el robot dado
 */
void liberar_robot(Robot* r);

/**
 * @brief Realiza el primer movimiento en la lista de
 * caminoARecorrer. 
 * Si el movimiento no es válido, recalcula el camino a recorrer.
 * Si el movimiento es válido, lo saca de caminoARecorrer
 * y lo pone al final de caminoRecorrido, y cambia las coordenadas
 * del robot a la posición a la que se movió. 
 */
void hacer_movimiento(Robot* r, Entorno e);

/**
 * @brief Recibe una dirección ('U', 'L', 'R', 'D') y una posición
 * y calcula a qué casilla se llegaría al hacer el movimiento
 */
Coord calcular_movimiento(char direccion, Coord posicion);

/**
 * @brief Recibe dos casillas vecinas p1 y p2 y calcula en qué dirección
 * está p2 respecto a p1. Si las casillas no son vecinas, devuelve '\0'
 */
char calcular_direccion(Coord p1, Coord p2);

/**
 * @brief Dadas dos coordenadas, calcula su distancia de Manhattan
 */
int heuristica(Coord init, Coord fin);

#endif