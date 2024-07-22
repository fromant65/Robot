#ifndef NODE_H
#define NODE_H
#define INFINITY __INT16_MAX__
#include "coord.h"
#include <stdbool.h>
typedef int* Key; //Array of 2 ints
typedef struct _Node{
    Coord pos;
    int rhs, g;
    Key key;
    bool inOpenList;
}Node;

Key new_key(int v1, int v2);

void free_key(Key k);

/**
 * @return A bidimensional array of node pointers for each node of the board.
 */
Node*** new_board(int N, int M);

/**
 * @brief frees al memory used by the board without freeing the nodes
 */
void free_board(Node*** board, int N);

#endif