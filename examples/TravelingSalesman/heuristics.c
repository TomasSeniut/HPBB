#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "DataStructure.h"
#include "utils.h"

typedef struct {
    int city;
    double distance;
} neighbour;

static int IsAllCitiesVisited(int n, const int cityArray[]);

static neighbour FindNearestNeighbour(int currentCity, tsp_global params, const int *visitedCities);

stack_data *NearestNeighbourMethod(tsp_global params) {
    stack_data *solution = malloc(sizeof(stack_data));
    InitializeArray(params.cities, &solution->visited);

    solution->city = 0;
    solution->step = 0;
    solution->pathLength = 0;
    solution->visited[0] = solution->step + 1;

    for (int i = 0; i < params.cities; ++i) {
        neighbour nearest = FindNearestNeighbour(solution->city, params, solution->visited);

        if (nearest.city == -2) {
            printf("Something wrong");
            exit(3);
        }

        solution->step++;
        solution->visited[nearest.city] = solution->step + 1;
        solution->city = nearest.city;
        solution->pathLength += nearest.distance;
    }

    return solution;
}

static neighbour FindNearestNeighbour(int currentCity, tsp_global params, const int *visitedCities) {
    neighbour nearest = {-2, DBL_MAX};

    for (int i = 0; i < params.cities; ++i) {
        if (visitedCities[i]) {
            continue;
        }

        double distanceBetweenCities = params.distanceMatrix[currentCity][i];
        if (nearest.distance > distanceBetweenCities) {
            nearest.distance = distanceBetweenCities;
            nearest.city = i;
        }
    }

    if (IsAllCitiesVisited(params.cities, visitedCities)) {
        nearest.city = 0;
        nearest.distance = params.distanceMatrix[currentCity][0];
    }

    return nearest;
}

static int IsAllCitiesVisited(int n, const int cityArray[]) {
    for (int i = 0; i < n; ++i) {
        if (!cityArray[i]) {
            return 0;
        }
    }

    return 1;
}