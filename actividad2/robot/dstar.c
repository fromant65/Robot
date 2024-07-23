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

void calculate_key(Node* n, int k_m, Coord sStar) {
    if (n->key == NULL) {
        n->key = malloc(sizeof(int) * 2);
    }
    n->key[0] = min(n->g, n->rhs) + heuristic(sStar, n->pos) + k_m;
    n->key[1] = min(n->g, n->rhs);
}

void initialize(DStarData* data, int N, int M, Coord start,Coord goal){
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
    if(u->pos.x != data->sGoal->pos.x || u->pos.y != data->sGoal->pos.y){
        Node *minNeighbor = min_neighbor(u, data);
        u->rhs=minNeighbor->g + get_cost(u, minNeighbor, data);
    }
    if(u->inOpenList){
        heap_remove(data->openList,u);
        u->inOpenList=false;
    }
    if(u->g!=u->rhs){
        calculate_key(u,data->k_m,data->sStart->pos);
        heap_enqueue(data->openList,u);
        u->inOpenList=true;
    }
}

void compute_shortest_path(DStarData* data){
    Node* topElem = heap_top_elem(data->openList);
    Node* start = data->sStart;
    calculate_key(start,data->k_m,start->pos);
    Key topKey = topElem!=NULL?topElem->key:NULL;
    Key startKey = data->sStart->key;
    while(compare_keys(heap_top_elem(data->openList)->key,startKey)<0 || start->g!=start->rhs){
        Node* top = heap_dequeue(data->openList);
        top->inOpenList=false;
        Key oldKey = top->key;
        calculate_key(top,data->k_m,start->pos);
        topKey=top->key;
        if(compare_keys(oldKey, topKey)==-1){
            heap_enqueue(data->openList, top);
        }else if(top->g>top->rhs){
            top->g=top->rhs;
            for(int i=0; i<4;i++){
                int dx= i==0?-1:i==2?1:0;
                int dy= i==1?1:i==3?-1:0;
                int nx= dx+top->pos.x;
                int ny= dy+top->pos.y;
                if(nx>=0 && nx<data->N && ny>=0 && ny<data->M){
                    Node* neighbor = data->nodes[nx][ny];
                    update_vertex(neighbor, data);
                }
            }
        }else{
            top->g=INFINITY;
            for(int i=0; i<4;i++){
                int dx= i==0?-1:i==2?1:0;
                int dy= i==1?1:i==3?-1:0;
                int nx= dx+top->pos.x;
                int ny= dy+top->pos.y;
                if(nx>=0 && nx<data->N && ny>=0 && ny<data->M){
                    Node* neighbor = data->nodes[nx][ny];
                    update_vertex(neighbor, data);
                }
            }
            update_vertex(top,data);
        }
        calculate_key(start, data->k_m, data->sStart->pos);
        startKey=start->key;
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
            r->path=push_char(r->path, direction);
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
        Node* curr_n = NULL;
        if(nPos.x>=0 && nPos.y>=0 && nPos.x<data->N && nPos.y<data->M){
            curr_n = data->nodes[nPos.x][nPos.y];
            curr_cost =get_cost(s,curr_n, data)+curr_n->g;
        }
        if(curr_cost<min_c){
            n=curr_n;
            min_c = curr_cost;
        }
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
            Node* curr= NULL;
            if(nx>=0&&nx<data->N&&ny>=0&&ny<data->M){
                curr = data->nodes[nx][ny];
                if(d==dist){
                    curr->g=INFINITY;
                    curr->rhs=INFINITY;
                }
                Node** neighbors = get_neighbors(curr, data);
                for(int j=0; j<4;j++){
                    if(neighbors[j]!=NULL){
                        Coord nCoord = neighbors[j]->pos;
                        char neighborDirection = calc_direction(nCoord, curr->pos);
                        int neighborIndex = get_direction_index(neighborDirection);
                        data->weights[nCoord.x][nCoord.y][neighborIndex]=d==dist?INFINITY:1;
                    }
                }
                free(neighbors);
            }
                
        }
    }
    for (int i = 0; i < 4; i++) {
        int dist = distances[i];
        int dx= i==0?-1:i==2?1:0;
        int dy= i==1?1:i==3?-1:0;
        for (int d = 1; d <= dist; d++) {
            int nx = x + d * dx;
            int ny = y + d * dy;
            if(nx>=0&&nx<data->N&&ny>=0&&ny<data->M){
                Node* curr = data->nodes[nx][ny];
                update_vertex(curr,data);
            }
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
        int nx=pa.x+dx;
        int ny=pa.y+dy;
        if(nx>=0&&ny>=0&&nx<data->N&&ny<data->M)
            n[i]=data->nodes[nx][ny];
        else
            n[i]=NULL;
    }
    return n;
}