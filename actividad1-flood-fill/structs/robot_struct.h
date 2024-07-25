#ifndef ROBOT_STRUCT_H
#define ROBOT_STRUCT_H
#include "entorno.h"
#include "coord.h"
#include "string.h"
typedef struct {
  Entorno entorno;
  Coord pos, meta;
  String camino;
} Robot;

#endif
