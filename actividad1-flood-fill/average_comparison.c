#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

/**
 * Comando de compilación:
 * gcc -o comp average_comparison.c -lrt
 * la flag sirve para linkear la librería lrt
 */

#define MAX 10000
#define INF 1000000

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point points[MAX];
    int front, rear;
} Queue;

void init_queue(Queue* q) {
    q->front = 0;
    q->rear = 0;
}

int is_empty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, Point p) {
    q->points[q->rear++] = p;
}

Point dequeue(Queue* q) {
    return q->points[q->front++];
}

int bfs(char** grid, int N, int M, Point start, Point end) {
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int distances[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            distances[i][j] = INF;
        }
    }
    distances[start.x][start.y] = 0;
    Queue q;
    init_queue(&q);
    enqueue(&q, start);

    while (!is_empty(&q)) {
        Point current = dequeue(&q);
        for (int i = 0; i < 4; i++) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] == '.' && distances[nx][ny] == INF) {
                distances[nx][ny] = distances[current.x][current.y] + 1;
                enqueue(&q, (Point){nx, ny});
                if (nx == end.x && ny == end.y) {
                    return distances[nx][ny];
                }
            }
        }
    }
    return -1; // Si no se encuentra un camino
}

int min_len(char* name) {
    FILE *file = fopen(name, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int N, M, D;
    fscanf(file, "%d %d %d", &N, &M, &D);

    Point start, end;
    fscanf(file, "%d %d", &start.x, &start.y);
    fscanf(file, "%d %d", &end.x, &end.y);

    char** grid = (char**)malloc(N * sizeof(char*));
    for (int i = 0; i < N; i++) {
        grid[i] = (char*)malloc((M + 1) * sizeof(char));
        fscanf(file, "%s", grid[i]);
    }

    fclose(file);
    int ret = bfs(grid, N, M, start, end);
    for (int i = 0; i < N; i++) {
        free(grid[i]);
    }
    free(grid);
    return ret;
}

void process_floodfill(const char *directory)
{
    DIR *dir;
    struct dirent *entry;
    char source_path[1024];
    char command[1024];
    char buffer[1024];
    int program_total_length = 0;
    int program_count = 0;
    if ((dir = opendir(directory)) == NULL)
    {
        perror("opendir() error");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strncmp(entry->d_name, "tablero", 7) == 0 
        //&& rand() % 50 == 0
        ){
            snprintf(source_path, sizeof(source_path), "%s/%s", directory, entry->d_name);
            snprintf(command, sizeof(command), "./programa %s",source_path);
            //printf("%s\n", command);
            FILE *program_output = popen(command, "r");
            if (program_output == NULL)
            {
                perror("Error executing ./program");
                continue;
            }

            // Leer y procesar la salida de ./programa
            if (fgets(buffer, sizeof(buffer), program_output) != NULL)
            {
                //printf("%s\n", buffer);
                int length = strlen(buffer);
                program_total_length += length;
                program_count++;
            }

            pclose(program_output);
        }
    }

    closedir(dir);

    // Calcular promedios
    double program_average = program_count > 0 ? (double)program_total_length / (double)program_count : 0.0;
    printf("PROMEDIO FLOODFILL: %f\n", program_average);
    printf("Cantidad de tableros: %d\n", program_count);
    printf("Longitud total: %d\n", program_total_length);
}

void process_astar(const char *directory){
    DIR *dir;
    struct dirent *entry;
    char source_path[1024];
    char command[1024];
    char buffer[1024];
    int program_total_length = 0;
    int program_count = 0;
    if ((dir = opendir(directory)) == NULL)
    {
        perror("opendir() error");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strncmp(entry->d_name, "tablero", 7) == 0 
        //&& rand() % 50 == 0
        ){
            snprintf(source_path, sizeof(source_path), "%s/%s", directory, entry->d_name);
            snprintf(command, sizeof(command), "./programa_astar %s",source_path);
            //printf("%s\n", command);
            FILE *program_output = popen(command, "r");
            if (program_output == NULL)
            {
                perror("Error executing ./program");
                continue;
            }

            // Leer y procesar la salida de ./programa
            if (fgets(buffer, sizeof(buffer), program_output) != NULL)
            {
                //printf("%s\n", buffer);
                int length = strlen(buffer);
                program_total_length += length;
                program_count++;
            }

            pclose(program_output);
        }
    }

    closedir(dir);

    // Calcular promedios
    double program_average = program_count > 0 ? (double)program_total_length / (double)program_count : 0.0;
    printf("PROMEDIO A*: %f\n", program_average);
    printf("Cantidad de tableros: %d\n", program_count);
    printf("Longitud total: %d\n", program_total_length);
}

void process_bfs(const char* directory){
    DIR *dir;
    struct dirent *entry;
    char source_path[1024];
    char command[1024];
    char buffer[1024];
    int bfs_total_length = 0;
    int bfs_count = 0;
    if ((dir = opendir(directory)) == NULL)
    {
        perror("opendir() error");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strncmp(entry->d_name, "tablero", 7) == 0 
        //&& rand() % 50 == 0
        ){
            snprintf(source_path, sizeof(source_path), "%s/%s", directory, entry->d_name);
            int curr_bfs = min_len(source_path);
            if(curr_bfs!=-1){
                bfs_total_length+=curr_bfs;
                bfs_count++;
            }
        }
    }
    closedir(dir);
    // Calcular promedios
    double bfs_average = bfs_count > 0 ? (double)bfs_total_length / (double)bfs_count : 0.0;
    printf("PROMEDIO BFS: %f\n", bfs_average);
    printf("Cantidad de tableros: %d\n", bfs_count);
    printf("Longitud total: %d\n", bfs_total_length);
}

double tiempo_funcion(void(*runtime)(const char*), const char* directory) {
    struct timespec start, end;

    // Marcar el inicio
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Ejecutar la función
    runtime(directory);

    // Marcar el final
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcular el tiempo utilizado en segundos
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1E9;
    return time_taken;
}

int main()
{
    srand(time(NULL));
    // Asume que los archivos están en el directorio ./tableros.
    double tBFS = tiempo_funcion(process_bfs, "./tableros");
    double tFF = tiempo_funcion(process_floodfill, "./tableros");
    double tAS = tiempo_funcion(process_astar,"./tableros");
    printf("Tiempo BFS: %f\n", tBFS);
    printf("Tiempo Floodfill: %f\n", tFF);
    printf("Tiempo A*: %f\n",tAS);
    return 0;
}
