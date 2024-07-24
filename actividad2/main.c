#include <stdio.h>
#include <stdlib.h>
#include "robot_dir/dstar.h"
#include "robot_dir/robot.h"

int main(){
    DStarData* data = malloc(sizeof(DStarData));
    int N,M,D;
    int i1,j1;
    int i2,j2;
    scanf("%d %d %d", &N,&M,&D);
    scanf("%d %d",&i1,&j1);
    scanf("%d %d",&i2,&j2);
    initialize(data,N,M,(Coord){i1,j1}, (Coord){i2,j2});
    String init_path = new_string(2048);
    Robot* robot = malloc(sizeof(Robot));
    robot->path=init_path;
    robot->pos=(Coord){i1,j1}; 
    d_star_lite(data,robot,D);
    // fprintf(stderr,"\n");
    // for(int i=0;i<data->N;i++){
    //     for(int j=0;j<data->M;j++){
    //         if(data->nodes[i][j]->key!=NULL){
    //             int v=data->nodes[i][j]->g;
    //             fprintf(stderr,"%s%d ", v>9?"":" ",v>100?-1:v);
    //         }
    //     }
    //     fprintf(stderr, "\n");
    // }
    printf("! %s\n", robot->path.buffer);
    fflush(stdout);
    return 0;
}