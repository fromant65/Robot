#ifndef LEER_ARCHIVO_H
#define LEER_ARCHIVO_H

#include <stdio.h>
#include "./../structs/program_data.h"
ProgramData *leer_archivo(FILE *);
void print_data(ProgramData *);

#endif
