#ifndef ROBOT_H
#define ROBOT_H
#include "../structs/coord.h"
#include "../structs/string.h"
typedef struct{
    Coord pos;
    String path;
}Robot;

#endif