#ifndef STRING_H
#define STRING_H

typedef struct {
  char *buffer;
  int length, size;
} String;

String new_string(int size);
void free_string(String s);
String push_char(String s, char c);
String pop_char(String s);
char last_char(String s);
void print_string(String s);
#endif
