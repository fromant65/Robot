#include "string.h"
#include <stdlib.h>
#include <stdio.h>

String new_string(int size) {
  String s;
  s.buffer = malloc(sizeof(char) * size);
  s.length = 0;
  s.size = size;
  return s;
}

void free_string(String s) {
  free(s.buffer);
}

String push_char(String s, char c) {
  if (s.size - 2 < s.length) {
    s.size *= 2;
    s.buffer = realloc(s.buffer, sizeof(char) * s.size);
  }
  s.buffer[s.length] = c;
  if (c != '\0') {
    s.length++;
    s.buffer[s.length] = '\0';
  }
  return s;
}

String pop_char(String s) {
  s.length--;
  return s;
}

char last_char(String s) {
  if (s.length == 0)
    return '\0';
  return s.buffer[s.length - 1];
}

void print_string(String s) {
  for (int i = 0; i < s.length; i++) {
    printf("%c", s.buffer[i]);
  }
}
