#include <stdio.h>
#include <stdlib.h>
#include "robot_dir/dstar.h"
#include "robot_dir/robot.h"

int main() {
  DStarData *data = malloc(sizeof(DStarData));
  int N, M, D;
  int i1, j1;
  int i2, j2;
  scanf("%d %d %d", &N, &M, &D);
  scanf("%d %d", &i1, &j1);
  scanf("%d %d", &i2, &j2);
  initialize(data, N, M, (Coord) {i1, j1}, (Coord) {i2, j2});
  String init_path = new_string(2048);
  Robot *robot = malloc(sizeof(Robot));
  robot->path = init_path;
  robot->pos = (Coord) {i1, j1};
  d_star_lite(data, robot, D);
  printf("! %s\n", robot->path.buffer);
  fflush(stdout);
  for (int i = 0; i < data->N; i++) {
    for (int j = 0; j < data->M; j++) {
      free(data->nodes[i][j]->key);
      free(data->nodes[i][j]);
    }
  }
  free_board(data->nodes, data->N);
  free_heap(data->openList);
  free_string(robot->path);
  for (int i = 0; i < data->N; i++) {
    for (int j = 0; j < data->M; j++) {
      free(data->weights[i][j]);
    }
    free(data->weights[i]);
  }
  free(data->weights);
  free(robot);
  free(data);
  return 0;
}
