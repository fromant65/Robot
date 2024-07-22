#include <stdlib.h>
#include "entorno.h"

void free_entorno(Entorno e){
    for(int i=0;i<e.N;i++){
        free(e.grilla[i]);
    }
    free(e.grilla);
}