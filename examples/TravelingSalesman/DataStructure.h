#ifndef TRAVELINGSALESMAN_DATASTRUCTURE_H
#define TRAVELINGSALESMAN_DATASTRUCTURE_H

typedef struct {
    int cities;
    double **distanceMatrix;
} tsp_global;

typedef struct {
    int x;
    int y;
} City;

typedef struct {
    int city;
    int step;
    double pathLength;
    int *visited;
} stack_data;


#endif //TRAVELINGSALESMAN_DATASTRUCTURE_H
