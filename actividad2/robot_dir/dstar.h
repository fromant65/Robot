#ifndef DSTAR_H 
#define DSTAR_H
#include "../structs/heap.h"
#include "../structs/node.h"
#include "robot.h"
typedef struct{
    Heap* openList;
    Node *sStart, *sGoal, *sLast;
    Node ***nodes;
    int ***weights;
    int k_m;
    int N;
    int M;
}DStarData;

int heuristic(Coord a, Coord b);
void calculate_key(Node* n, int k_m, Coord sStar);
void initialize(DStarData* data, int N, int M, Coord goal, Coord start);
void update_vertex(Node* u, DStarData* data);
void compute_shortest_path(DStarData* data);
void d_star_lite(DStarData* data, Robot* r, int sensorRange);

//utility functions

/**
 * @brief Initialize all weights to 2 except for border cells
 * where the weights are set to INFINITY on out-of-bound connections
 */
void initialize_weights(DStarData* data, int N, int M);

/**
 * @brief Receives a node s and returns a neighbor n such that
 * c(n,s)+g.n is minimum
 */
Node* min_neighbor(Node* s, DStarData* data);

/**
 * @brief Gets two neighbor coords and returns the position of the second coord
 * relative to the first one.
 * If the given coords are not neighbors, returns '\0'
 */
char calc_direction(Coord p1, Coord p2);

/**
 * @return 0 if direction == 'U'
 * 1 if direction == 'R'
 * 2 if direction == 'D'
 * 3 if direction == 'L'
 * -1 otherwise
 */
int get_direction_index(char direction);

/**
 * @brief Given the robot position, returns the closest obstacle in each direction
 * if there is an obstacle within the sensor range. Otherwise returns range+1.
 * The order of the directions is U-R-D-L
 */
int* use_sensor(Coord pos);

/**
 * @brief given an array of distances to the closest obstacles and the sensor range,
 * updates the weight of all affected cells
 */
void update_weights(DStarData* data, int* distances, int range);

/**
 * @brief takes two neighbor nodes a and b 
 * and returns the cost to go from a to b
 */
int get_cost(Node* a, Node* b, DStarData* data);

/**
 * @brief gets a node and returns an array with its neighbors
 */
Node** get_neighbors(Node* a, DStarData* data);

void sort_by_key(Node** arr, int len);

#endif 
