#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define WIDTH 6
#define HEIGHT 6
#define INF 1000000

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point pos;
    int g;
    int h;
    int f;
    struct Node *parent;
    bool walkable;
} Node;

Node* create_node(int x, int y, bool walkable) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->pos.x = x;
    node->pos.y = y;
    node->g = INF;
    node->h = 0;
    node->f = 0;
    node->parent = NULL;
    node->walkable = walkable;
    return node;
}

typedef struct {
    Node* nodes[WIDTH * HEIGHT];
    int count;
} NodeList;

void add_to_list(NodeList* list, Node* node) {
    list->nodes[list->count++] = node;
}

bool node_in_list(NodeList* list, Node* node) {
    for (int i = 0; i < list->count; i++) {
        if (list->nodes[i] == node) {
            return true;
        }
    }
    return false;
}

void remove_from_list(NodeList* list, Node* node) {
    for (int i = 0; i < list->count; i++) {
        if (list->nodes[i] == node) {
            for (int j = i; j < list->count - 1; j++) {
                list->nodes[j] = list->nodes[j + 1];
            }
            list->count--;
            return;
        }
    }
}

int heuristic(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void reconstruct_path(Node* node) {
    while (node != NULL) {
        printf("(%d, %d) <- ", node->pos.x, node->pos.y);
        node = node->parent;
    }
    printf("Start\n");
}

Node* get_lowest_f_score(NodeList* list) {
    Node* lowest = list->nodes[0];
    for (int i = 1; i < list->count; i++) {
        if (list->nodes[i]->f < lowest->f) {
            lowest = list->nodes[i];
        }
    }
    return lowest;
}

void find_neighbors(Node* grid[WIDTH][HEIGHT], Node* node, NodeList* neighbors) {
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; i++) {
        int nx = node->pos.x + dx[i];
        int ny = node->pos.y + dy[i];
        if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && grid[nx][ny]->walkable) {
            add_to_list(neighbors, grid[nx][ny]);
        }
    }
}

void a_star(Node* grid[WIDTH][HEIGHT], Point start, Point goal) {
    NodeList open_list = { .count = 0 };
    NodeList closed_list = { .count = 0 };
    
    Node* start_node = grid[start.x][start.y];
    Node* goal_node = grid[goal.x][goal.y];
    
    start_node->g = 0;
    start_node->h = heuristic(start, goal);
    start_node->f = start_node->g + start_node->h;
    add_to_list(&open_list, start_node);
    
    while (open_list.count > 0) {
        Node* current = get_lowest_f_score(&open_list);
        
        if (current == goal_node) {
            reconstruct_path(current);
            return;
        }
        
        remove_from_list(&open_list, current);
        add_to_list(&closed_list, current);
        
        NodeList neighbors = { .count = 0 };
        find_neighbors(grid, current, &neighbors);
        
        for (int i = 0; i < neighbors.count; i++) {
            Node* neighbor = neighbors.nodes[i];
            
            if (node_in_list(&closed_list, neighbor)) {
                continue;
            }
            
            int tentative_g_score = current->g + 1;
            
            if (!node_in_list(&open_list, neighbor)) {
                add_to_list(&open_list, neighbor);
            } else if (tentative_g_score >= neighbor->g) {
                continue;
            }
            
            neighbor->parent = current;
            neighbor->g = tentative_g_score;
            neighbor->h = heuristic(neighbor->pos, goal);
            neighbor->f = neighbor->g + neighbor->h;
        }
    }
    
    printf("No path found\n");
}