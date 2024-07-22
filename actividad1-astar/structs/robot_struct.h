#ifndef ROBOT_STRUCT_H
#define ROBOT_STRUCT_H

#include "stack.h"
#include "entorno.h"
#include "coord.h"
typedef struct{
    char* camino;
    int largo, capacidad;
}RobotRecorrido;

/**
 * @brief 
 * 
 * Robot.entorno es el entorno que conoce el robot.
 * Originalmente no tiene obstáculos.
 * 
 * recorridoHecho es un string con los pasos dados por el robot.
 * Originalmente está vacío.
 * 
 * recorridoPlaneado es un stack con los pasos que el robot debería
 * hacer en un camino óptimo a la meta si el entorno real es igual 
 * (al menos alrededor del recorrido) al que conoce el robot.
 * Se calcula al crear el robot.
 */
typedef struct{
    Coord posicion, meta;
    RobotRecorrido recorridoHecho;
    Stack recorridoPlaneado;
    Entorno entorno;
}Robot;

#endif