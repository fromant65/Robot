#include "dstar.h"

#include <stdlib.h>
#include <stdio.h>

int abs(int a){
    return a>=0?a:-a;
}

int min(int a, int b){
    return a<b?a:b;
}

int heuristic(Coord a, Coord b){
    return abs(a.x-b.x)+abs(a.y-b.y);
}

void calculate_key(Node* n, int k_m, Coord sStar){
    Key k = n->key==NULL? malloc(sizeof(int)*2):n->key;
    k[0]=min(n->g, n->rhs)+heuristic(sStar,n->pos)+k_m;
    k[1]=min(n->g, n->rhs);
    n->key=k;
}

void initialize(DStarData* data, int N, int M, Coord goal, Coord start){
    data->N=N;
    data->M=M;
    data->openList = new_heap(N*M);
    data->k_m=0;
    data->nodes=new_board(N,M);
    data->sGoal = data->nodes[goal.x][goal.y];
    data->sStart = data->nodes[start.x][start.y];
    initialize_weights(data, N, M);
    data->sGoal->rhs=0;
    calculate_key(data->sGoal, 0, start);
    data->sGoal->inOpenList=true;
    heap_enqueue(data->openList, data->sGoal);
}

void update_vertex(Node* u, DStarData* data){
    if(u->pos.x != data->sGoal->pos.x && u->pos.y != data->sGoal->pos.y){
        Node *minNeighbor = min_neighbor(u, data);
        u->rhs=minNeighbor->g + get_cost(u,minNeighbor, data);
    }
    if(u->inOpenList){
        u->inOpenList=false;
        heap_remove(data->openList,u);
    }
    if(u->g!=u->rhs){
        calculate_key(u,data->k_m,data->sStart->pos);
        u->inOpenList=true;
        heap_enqueue(data->openList,u);
    }
}

void compute_shortest_path(DStarData* data){
    Key topKey = data->openList->buffer[0]->key;
    Key startKey = data->sStart->key;
    Node* start = data->sStart;
    while(compare_keys(topKey,startKey)==-1 || start->g!=start->rhs){
        Key oldKey = new_key(topKey[0], topKey[1]);
        data->openList->buffer[0]->inOpenList = false;
        Node* top = heap_dequeue(data->openList);
        calculate_key(top,data->k_m,start->pos);
        if(compare_keys(oldKey, top->key)==1)
            heap_enqueue(data->openList, top);
        else if(top->g>top->rhs){
            top->g=top->rhs;
            for(int i=0; i<4;i++){
                int dx= i==0?-1:i==2?1:0;
                int dy= i==1?1:i==3?-1:0;
                Node* neighbor = data->nodes[top->pos.x+dx][top->pos.y+dy];
                update_vertex(neighbor, data);
            }
        }else{
            top->g=INFINITY;
            for(int i=0; i<4;i++){
                int dx= i==0?-1:i==2?1:0;
                int dy= i==1?1:i==3?-1:0;
                Node* neighbor = data->nodes[top->pos.x+dx][top->pos.y+dy];
                update_vertex(neighbor, data);
            }
            update_vertex(top,data);
        }
    }
}

void d_star_lite(DStarData* data, Robot* r, int sensorRange){
    data->sLast =  data->sStart;
    compute_shortest_path(data);
    while(data->sStart->pos.x != data->sGoal->pos.x || data->sStart->pos.y!=data->sGoal->pos.y){
        Node* start = data->sStart;
        Node* minNeighbor = min_neighbor(start, data);
        char direction = calc_direction(start->pos, minNeighbor->pos);
        if(get_cost(start, minNeighbor,data)>1){
            int *distances=use_sensor(r->pos);
            update_weights(data, distances, sensorRange);
            free(distances);
            compute_shortest_path(data);
        }else{    
            data->sStart = minNeighbor;
            r->pos=data->sStart->pos;
            push_char(r->path, direction);
        }
    }
}

//utility
/**
 * @brief Initialize all weights to 2 except for border cells
 * where the weights are set to INFINITY on out-of-bound connections
 */
void initialize_weights(DStarData* data, int N, int M){
    data->weights = malloc(sizeof(int**)*N);
    for(int i=0; i<N;i++){
        data->weights[i]=malloc(sizeof(int*)*M);
        for(int j=0;j<M;j++){
            data->weights[i][j]=malloc(sizeof(int)*4);
            for(int k=0;k<4;k++){
                data->weights[i][j][k]=2;
            }
            if(i==0) data->weights[i][j][0]=INFINITY;
            if(j==M-1) data->weights[i][j][1]=INFINITY;
            if(i==N-1) data->weights[i][j][2]=INFINITY;
            if(j==0) data->weights[i][j][3]=INFINITY;
        }
    }
}

Node* min_neighbor(Node* s, DStarData* data){
    int min_c = RAND_MAX;
    Node* n = NULL;
    for(int i=0; i<4;i++){
        int dx= i==0?-1:i==2?1:0;
        int dy= i==1?1:i==3?-1:0;
        Coord nPos = {s->pos.x+dx, s->pos.y+dy};
        int curr_cost=RAND_MAX;
        if(nPos.x>=0 || nPos.y>=0 || nPos.x<data->N || nPos.y<data->M){
            n = data->nodes[nPos.x][nPos.y];
            curr_cost =get_cost(n,s, data)+n->g;
        }
        if(curr_cost<min_c)
            min_c = curr_cost;
    }
    return n;
}

char calc_direction(Coord p1, Coord p2){
    if(abs(p1.x-p2.x)>1 || abs(p1.y-p2.y)>1) return '\0';
    if(abs(p1.x-p2.x)==1 && abs(p1.y-p2.y==1)) return '\0';
    if(p1.x==p2.x && p1.y== p2.y) return'\0';
    if(p1.x>p2.x) return 'U';
    if(p1.x<p2.x) return 'D';
    if(p1.y>p2.y) return 'L';
    return 'R';
}

int get_direction_index(char direction){
    if(direction=='U') return 0;
    if(direction=='R') return 1;
    if(direction=='D') return 2;
    if(direction=='L') return 3;
    return -1;
}

int* use_sensor(Coord pos){
    int* distances = malloc(sizeof(int)*4);
    printf("? %d %d\n",pos.x, pos.y);
    fflush(stdout);
    //The sensor returns position in UDLR order
    scanf("%d%d%d%d", distances, distances+2,distances+3,distances+1);
    //We return them in URDL order
    return distances;
}

void update_weights(DStarData* data, int* distances, int sensorRange) {
    int x = data->sStart->pos.x;
    int y = data->sStart->pos.y;
    for (int i = 0; i < 4; i++) {
        int dist = distances[i];
        int dx= i==0?-1:i==2?1:0;
        int dy= i==1?1:i==3?-1:0;
        for (int d = 1; d <= sensorRange && d <= dist; d++) {
            int nx = x + d * dx;
            int ny = y + d * dy;
            Node* curr = data->nodes[nx][ny];
            Node** neighbors = get_neighbors(curr, data);
            for(int j=0; j<4;j++){
                Coord nCoord = neighbors[i]->pos;
                char neighborDirection = calc_direction(nCoord, curr->pos);
                int neighborIndex = get_direction_index(neighborDirection);
                data->weights[nCoord.x][nCoord.y][neighborIndex]=d==dist?INFINITY:1;
            }
            free(neighbors);
        }
    }
    for (int i = 0; i < 4; i++) {
        int dist = distances[i];
        int dx= i==0?-1:i==2?1:0;
        int dy= i==1?1:i==3?-1:0;
        for (int d = 1; d <= dist; d++) {
            int nx = x + d * dx;
            int ny = y + d * dy;
            Node* curr = data->nodes[nx][ny];
            update_vertex(curr,data);
        }
    }
}

int get_cost(Node* a, Node* b, DStarData* data){
    Coord pa = a->pos;
    Coord pb = b->pos;
    char dir = calc_direction(pa,pb);
    int index = get_direction_index(dir);
    return data->weights[pa.x][pa.y][index];
}

Node** get_neighbors(Node* a, DStarData* data){
    Node** n = malloc(sizeof(Node*)*4);
    Coord pa = a->pos;
    for(int i=0; i<4;i++){
        int dx= i==0?-1:i==2?1:0;
        int dy= i==1?1:i==3?-1:0;
        n[i]=data->nodes[pa.x+dx][pa.y+dy];
    }
    return n;
}