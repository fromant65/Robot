#include <stdlib.h>
#include <stdio.h>
#include "robot.h"
#include "floodfill.h"

/**
 * @brief Funcion interna que calcula el valor absoluto de un numero
 */
int abs(int a) {
  return a >= 0 ? a : -a;
}

int posicion_valida(int x, int y, EntornoReal e) {
  if (x >= e.N || x < 0 || y >= e.M || y < 0 || e.grilla[x][y] == false)
    return 0;
  return 1;
}

Robot *crear_robot(int N, int M, int i1, int i2, int j1, int j2) {
  Robot *robot = malloc(sizeof(Robot));
  Coord inicio = {.x = i1,.y = i2 };
  Coord meta = {.x = j1,.y = j2 };
  Entorno entorno = crear_entorno(N, M, meta);
  String camino = crear_string(M * N);
  robot->pos = inicio;
  robot->meta = meta;
  robot->entorno = entorno;
  robot->camino = camino;
  return robot;
}

void liberar_robot(Robot * r) {
  liberar_string(r->camino);
  liberar_entorno(r->entorno);
  free(r);
}

void hacer_movimiento(Robot * r, EntornoReal e) {
  Coord posActual = r->pos;
  Coord next_pos = get_vecino_menor(r->pos, r->entorno);
  int nx = next_pos.x, ny = next_pos.y;
  if (!posicion_valida(nx, ny, e)) {
    r->entorno.grilla[nx][ny]->obstaculo = true;
    r->entorno = recalcular_floodfill(next_pos, r->entorno);
    hacer_movimiento(r, e);
  } else {
    if (r->entorno.grilla[r->pos.x][r->pos.y]->visitado == true)
      r->entorno = recalcular_floodfill(posActual, r->entorno);
    r->entorno.grilla[r->pos.x][r->pos.y]->visitado = true;
    r->pos = next_pos;
    r->camino =
        insertar_char(r->camino, calcular_direccion(posActual, next_pos));
  }
}

Coord calcular_movimiento(char direccion, Coord posicion) {
  int next_x =
      direccion == 'U' ? posicion.x - 1 : direccion ==
      'D' ? posicion.x + 1 : posicion.x;
  int next_y =
      direccion == 'L' ? posicion.y - 1 : direccion ==
      'R' ? posicion.y + 1 : posicion.y;
  Coord ret = { next_x, next_y };
  return ret;
}

char calcular_direccion(Coord p1, Coord p2) {
  if (abs(p1.x - p2.x) > 1 || abs(p1.y - p2.y) > 1)
    return '\0';
  if (abs(p1.x - p2.x) == 1 && abs(p1.y - p2.y == 1))
    return '\0';
  if (p1.x > p2.x)
    return 'U';
  if (p1.x < p2.x)
    return 'D';
  if (p1.y > p2.y)
    return 'L';
  return 'R';
}

int heuristica(Coord init, Coord fin) {
  return abs(init.x - fin.x) + abs(init.y - fin.y);
}

Coord get_vecino_menor(Coord c, Entorno e) {
  int i_menor = -1, d_menor = __INT16_MAX__;
  Nodo **vecinos = get_vecinos(e.grilla[c.x][c.y], e);
  for (int i = 0; i < 4; i++) {
    if (vecinos[i] != NULL &&
        vecinos[i]->distancia < d_menor && !vecinos[i]->obstaculo) {
      i_menor = i;
      d_menor = vecinos[i]->distancia;
    }
  }
  if (i_menor == -1) {
    free(vecinos);
    return (Coord) {
    -1, -1};
  } else {
    Coord menor = vecinos[i_menor]->pos;
    free(vecinos);
    return menor;
  }
}
