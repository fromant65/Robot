#ifndef STRING_H
#define STRING_H

typedef struct{
    char* buffer;
    int capacidad, fin;
}String;

String crear_string(int capacidad);
void liberar_string(String s);
String insertar_char(String s, char c);
String eliminar_char(String s);
#endif