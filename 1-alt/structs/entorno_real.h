#ifndef ENTORNO_REAL_H
#define ENTORNO_REAL_H
#include <stdbool.h>

typedef struct{
    bool** grilla; // false representa obstaculo, true casilla libre
    int N,M;
}EntornoReal;

EntornoReal crear_entorno_real(int n, int m);
void liberar_entorno_real(EntornoReal e);
#endif