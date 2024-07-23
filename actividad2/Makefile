# Nombre del ejecutable
EXEC = robotp

# Compilador y banderas de compilación
CC = gcc
CFLAGS = -Wall -Wextra -I./lectura -I./structs

# Directorios de los archivos fuente
SRCDIR = .
LECTURADIR = lectura
STRUCTSDIR = structs
ROBOTDIR = robot

# Archivos fuente
SRC = $(SRCDIR)/main.c $(wildcard $(LECTURADIR)/*.c) $(wildcard $(STRUCTSDIR)/*.c) $(wildcard $(ROBOTDIR)/*.c)

# Archivos objeto
OBJ = $(SRC:.c=.o)

# Regla por defecto
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para compilar archivos .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -f $(OBJ) $(EXEC)

# Limpiar todo, incluyendo archivos generados por el preprocesador
distclean: clean
	rm -f $(SRCDIR)/*.gch $(LECTURADIR)/*.gch $(STRUCTSDIR)/*.gch $(ROBOTDIR)/*.gch

# Phony targets
.PHONY: all clean distclean
