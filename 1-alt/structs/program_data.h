#ifndef PROGRAM_DATA_H
#define PROGRAM_DATA_H

#include <stdbool.h>
/**
 * El entorno será true en espacio vacío '.',
 * false en obstáculo '#'
 */
typedef struct
{
    int N,M,D,i1,i2,j1,j2;
    bool **entorno;
}ProgramData;

#endif