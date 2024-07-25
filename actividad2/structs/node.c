#include <stdlib.h>
#include "node.h"
#include "../robot_dir/dstar.h"
Key new_key(int v1, int v2) {
  Key k = malloc(sizeof(int) * 2);
  k[0] = v1;
  k[1] = v2;
  return k;
}

void free_key(Key k) {
  free(k);
}

Node ***new_board(int N, int M) {
  Node ***board = malloc(sizeof(Node **) * N);
  for (int i = 0; i < N; i++) {
    board[i] = malloc(sizeof(Node *) * M);
    for (int j = 0; j < M; j++) {
      board[i][j] = malloc(sizeof(Node));
      board[i][j]->key = malloc(sizeof(int) * 2);
      board[i][j]->order = -1;
      board[i][j]->pos = (Coord) {i, j};
      board[i][j]->g = INFINITY;
      board[i][j]->rhs = INFINITY;
    }
  }
  return board;
}

void free_board(Node *** board, int N) {
  for (int i = 0; i < N; i++) {
    free(board[i]);
  }
  free(board);
}
