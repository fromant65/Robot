#ifndef STRING_H
#define STRING_H

typedef struct {
  char *buffer;
  int length, size;
} String;

String new_string(int size);

void free_string(String s);

/**
 * @brief Adds a char at the end of the string
 */
String push_char(String s, char c);

/**
 * @brief Removes the last char from the string
 */
String pop_char(String s);

/**
 * @return the last char from the string
 */
char last_char(String s);

void print_string(String s);
#endif
