#include <stdio.h>
#include <stdlib.h>
#include "robot/dstar.h"
#include "robot/robot.h"

int main(){
    DStarData* data = malloc(sizeof(DStarData));
    int N,M,D;
    int i1,j1;
    int i2,j2;
    scanf("%d %d %d", &N,&M,&D);
    scanf("%d %d",&i1,&j1);
    scanf("%d %d",&i2,&j2);
    initialize(data,N,M,(Coord){i1,j1}, (Coord){i2,j2});
    fprintf(stderr, "Inicializado d*\n");
    String init_path = new_string(2048);
    Robot* robot = malloc(sizeof(Robot));
    robot->path=init_path;
    robot->pos=(Coord){i1,j1}; 
    fprintf(stderr, "pre d*\n");
    d_star_lite(data,robot,D);
    for(int i=0;i<data->N;i++){
        for(int j=0;j<data->M;j++){
            if(data->nodes[i][j]->key!=NULL)
                fprintf(stderr,"%d ", data->nodes[i][j]->key[0]);
        }
        fprintf(stderr, "\n");
    }
    printf("! %s\n", robot->path.buffer);
    fflush(stdout);
    return 0;
}