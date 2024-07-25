#include "string.h"
#include <stdlib.h>


String crear_string(int capacidad) {
  String s = { malloc(sizeof(char) * capacidad), capacidad, 0 };
  return s;
}
void liberar_string(String s) {
  free(s.buffer);
}
String insertar_char(String s, char c) {
  if (s.capacidad <= s.fin + 1) {
    s.capacidad *= 2;
    s.buffer = realloc(s.buffer, sizeof(char) * s.capacidad);
  }
  s.buffer[s.fin++] = c;
  return s;
}
String eliminar_char(String s) {
  s.fin--;
  return s;
}
