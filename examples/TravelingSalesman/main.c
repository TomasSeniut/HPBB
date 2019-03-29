#include <stdio.h>
#include <malloc.h>
#include <HPBB.h>
#include <float.h>
#include "IO/IO.h"
#include "utils.h"

stack_data NearestNeighbourMethod(tsp_global params);

static double GetLowerBound(tsp_global params, const int citiesVisited[]);

void tsp_branch(stack_data *node, tsp_global *params, HPBB_node_processing next) {
    printf("branching node, step : %d\n", node->step);

    for (int i = 0; i < params->cities; ++i) {
        if (node->visited[i]) {
            continue;
        }

        stack_data *subProblem =  malloc(sizeof(stack_data*));

        subProblem->city = i;
        subProblem->step = node->step + 1;
        subProblem->pathLength = node->pathLength + params->distanceMatrix[node->city][subProblem->city];
        InitializeAndCopyArray(params->cities, node->visited, &subProblem->visited);
        subProblem->visited[subProblem->city] = node->step + 1;

        next(subProblem);
    }
}

int tsp_isNodeLowerBoundBetterThanUpper(stack_data *node, stack_data *upperBound, tsp_global *params) {
    //printf("Checking lower bound\n");

    double pathLength = node->pathLength + GetLowerBound(*params, node->visited);

    return upperBound->pathLength >= pathLength;
}

int tsp_isSolutionBetterThanUpperBound(stack_data *node, stack_data *upperBound, tsp_global *params) {
    //printf("Checking for upper bound\n");

    double pathLength = node->pathLength + params->distanceMatrix[node->city][0];

    return upperBound->pathLength >= pathLength;
}

int tsp_isSolution(stack_data *node, tsp_global *params) {
    //printf("Is this solution?\n");

    return (node->step + 1) == params->cities;
}

void tsp_disposeNode(stack_data *node) {
    //printf("Disposing stuff\n");

    free(node->visited);
    free(node);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./TravelingSalesman problemFileName\n");
        return 1;
    }

    char *dataFileName = argv[1];
    tsp_global params = ReadGlobalData(dataFileName);

    HPBB_queues queues = HPBB_default_DataStructures();

    printf("got stuff\n");

    HPBB_algorithm_functions functions = {
            .branch = tsp_branch,
            .isSolution = tsp_isSolution,
            .isSolutionBetterThanUpperBound = tsp_isSolutionBetterThanUpperBound,
            .isNodesLowerBoundBetterThanUpper = tsp_isNodeLowerBoundBetterThanUpper,
            .disposeNode = tsp_disposeNode
    };

    printf("Assigned function\n");

    HPBB_init_solver(queues, functions);
    printf("solver initialized\n");

    stack_data *initialProblem =  malloc(sizeof(stack_data*));

    initialProblem->city = 0;
    initialProblem->pathLength= 0;
    initialProblem->step = 0;
    InitializeArray(params.cities, &initialProblem->visited);
    initialProblem->visited[initialProblem->city] = initialProblem->step + 1;

    stack_data upperBound = NearestNeighbourMethod(params);
    printf("got init problem and bound\n");

    stack_data* solution =  HPBB_solve(initialProblem, &upperBound, &params);

    printf("got solution\n");
    PrintResult(params, *solution);

    return 0;
}

static double GetLowerBound(tsp_global params, const int citiesVisited[]) {
    double lowerBound = 0;

    for (int i = 0; i < params.cities; ++i) {
        if (citiesVisited[i]) {
            continue;
        }

        double firstNearestCity = DBL_MAX;
        double secondNearestCity = DBL_MAX;

        for (int j = 0; j < params.cities; ++j) {
            if (citiesVisited[j] || i == j) {
                continue;
            }

            double distance = params.distanceMatrix[i][j];

            if (distance < secondNearestCity) {
                if (distance < firstNearestCity) {
                    if (firstNearestCity < secondNearestCity) {
                        secondNearestCity = firstNearestCity;
                    }

                    firstNearestCity = distance;
                } else {
                    secondNearestCity = distance;
                }
            }
        }

        if (secondNearestCity == DBL_MAX) {
            return 0;
        }

        lowerBound += firstNearestCity + secondNearestCity;
    }

    return lowerBound / 2;
}