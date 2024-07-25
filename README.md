# Proyecto: Modelado del Movimiento de un Robot en un Entorno Desconocido

## Descripción

Este proyecto intenta modelar el movimiento de un robot en un entorno desconocido, el cual tiene obstáculos. Este entorno es una cuadrícula de N*M, donde cada casilla es un obstáculo o camino. Se asume que siempre existe un camino válido para el robot.

El proyecto se divide en dos actividades principales:

### Actividad 1: Robot Ciego

En esta actividad, el robot no tiene sensores y avanza desde una posición `(i1, j1)` a una posición `(i2, j2)`, descubriendo dónde hay un obstáculo al "chocarse" con él. El objetivo es encontrar el camino más corto posible. Para ello, se usan los algoritmos A* y Flood Fill.

### Actividad 2: Robot con Sensor

En esta actividad, el robot cuenta con un sensor externo con rango D que le indica dónde está el obstáculo más cercano en cada dirección, si es que lo encuentra en dicho rango. Si no encuentra un obstáculo en dicho rango, el sensor devuelve D+1. El objetivo en este caso es minimizar el uso del sensor. Para ello, se usa el algoritmo D* Lite, asumiendo que el costo de ir a una casilla conocida es 1, a una desconocida es 2 y a un obstáculo es infinito.

## Tests

### Actividad 1

Existe una carpeta de tests con:

- Un programa en Python que permite verificar si los caminos que toma el robot son válidos.
- Un programa en C que permite comparar la longitud de los caminos en cada algoritmo respecto al camino óptimo (encontrado con BFS), además de mostrar el tiempo de ejecución de cada uno. Este programa en C tiene un comentario que indica cómo compilarlo.

### Actividad 2

Para correr el programa:

1. Compilar con `make`.
2. Ejecutar el archivo `./correr.sh`.

En caso de tener muchos tableros, se puede usar `./testall.sh` para correr todos, o `./testsome.sh` para correr un 2% de los tableros.

## Generador de Tableros

Existe una carpeta `generadorTableros` que contiene un algoritmo que genera tableros aleatoriamente con formato y caminos válidos para el robot. Este algoritmo genera miles de tableros en una carpeta `/tableros`. Esta carpeta generada se puede copiar y pegar en la carpeta de la actividad 2 o de tests para la actividad 1 y permite correr los archivos de test.

## Formato de los Archivos

El formato indicado para los archivos es:

```
N M D
i1 j1
i2 j2
tablero
```

- **N M D**: Tres números enteros representando N, M y el rango del sensor.
- **i1 j1**: Posición inicial del robot.
- **i2 j2**: Posición final del robot.
- **tablero**: N líneas de M caracteres `.` (camino) o `#` (obstáculo), terminadas por un salto de línea cada una.

## Formateo de Código

Existe un archivo `format.sh` que permite formatear todos los archivos `.c` y `.h` a la convención establecida para el proyecto. 

## Makefiles

Cada una de las carpetas de las actividades tiene un archivo `Makefile` que sirve para compilar los respectivos programas.

## Ejecución

### Actividad 2

Para correr el programa en la actividad 2, además de compilar con `make`, se debe ejecutar el archivo `./correr.sh`. En caso de tener muchos tableros, se puede usar `./testall.sh` para correr todos los tableros, o `./testsome.sh` para correr un 2% de los tableros.

## Contribución

Para contribuir al proyecto, asegúrate de seguir las convenciones de codificación establecidas y formatear tu código utilizando el script `format.sh`.