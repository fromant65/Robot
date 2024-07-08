#ifndef PROGRAM_DATA_H
#define PROGRAM_DATA_H
/**
 * El entorno será 1 en espacio vacío '.',
 * 0 en obstáculo '#'
 */
typedef struct
{
    int N,M,D,i1,i2,j1,j2;
    unsigned int **entorno;
}ProgramData;

#endif