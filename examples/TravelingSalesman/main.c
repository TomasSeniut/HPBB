#include <stdio.h>
#include <malloc.h>
#include <HPBB.h>
#include <float.h>
#include <omp.h>
#include "IO/IO.h"
#include "utils.h"

stack_data *NearestNeighbourMethod(tsp_global params);

static double GetLowerBound(tsp_global params, const int citiesVisited[]);

void tsp_branch(stack_data *node, tsp_global *params, HPBB_node_processing next) {
    for (int i = 0; i < params->cities; ++i) {
        if (node->visited[i]) {
            continue;
        }

        stack_data *subProblem = malloc(sizeof(stack_data));

        subProblem->city = i;
        subProblem->step = node->step + 1;
        subProblem->pathLength = node->pathLength + params->distanceMatrix[node->city][subProblem->city];
        InitializeAndCopyArray(params->cities, node->visited, &subProblem->visited);
        subProblem->visited[subProblem->city] = node->step + 1;

        next(subProblem);
    }
}

int tsp_isNodeLowerBoundBetterThanUpper(stack_data *node, stack_data *upperBound, tsp_global *params) {
    double pathLength = node->pathLength + GetLowerBound(*params, node->visited);

    return upperBound->pathLength >= pathLength;
}

int tsp_isSolutionBetterThanUpperBound(stack_data *node, stack_data *upperBound, tsp_global *params) {
    int isBetter = upperBound->pathLength >= node->pathLength;

    return isBetter;
}

int tsp_isSolution(stack_data *node, tsp_global *params) {

    int isSolution = (node->step + 1) == params->cities;
    if (isSolution) {
        node->pathLength = node->pathLength + params->distanceMatrix[node->city][0];
    }

    return isSolution;
}

void tsp_disposeNode(stack_data *node) {
    free(node->visited);
    free(node);
}

HPBB_message_passing_bound_indication tsp_selectBoundIndication(stack_data *node) {
    HPBB_message_passing_bound_indication data = {
            .bound = &node->pathLength,
            .type = MPI_DOUBLE
    };

    return data;
}

HPBB_message_passing_solution_array tsp_selectSolutionArray(stack_data *node, tsp_global *params) {
    HPBB_message_passing_solution_array data = {
            .array = node->visited,
            .arraySize = params->cities,
            .type = MPI_INT
    };

    return data;
}

HPBB_message_passing_bound_indication tsp_receiveBoundIndication() {
    double *someBound = malloc(sizeof(double));
    HPBB_message_passing_bound_indication data = {
        .bound = someBound,
        .type = MPI_DOUBLE
    };

    return data;
}

int tsp_updateBoundIndication(void *receivedBound, stack_data *node) {
    double bound = *(double*)receivedBound;

    free(receivedBound);

    if (node->pathLength >= bound) {
        node->pathLength = bound;

        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./TravelingSalesman problemFileName\n");
        return 1;
    }

    char *dataFileName = argv[1];
    tsp_global params = ReadGlobalData(dataFileName);

    HPBB_queues queues = HPBB_default_DataStructures();

    HPBB_algorithm_functions functions = {
            .branch = tsp_branch,
            .isSolution = tsp_isSolution,
            .isSolutionBetterThanUpperBound = tsp_isSolutionBetterThanUpperBound,
            .isLowerBoundOfNodeBetterThanUpperBound = tsp_isNodeLowerBoundBetterThanUpper,
            .disposeNode = tsp_disposeNode
    };

    HPBB_message_passing_functions messageFunctions = {
            .receiveBoundIndication = tsp_receiveBoundIndication,
            .updateBoundIndication = tsp_updateBoundIndication,
            .selectSolutionArray = tsp_selectSolutionArray,
            .selectBoundIndication = tsp_selectBoundIndication
    };

    HPBB_init_solver(queues, functions, messageFunctions);

    stack_data *initialProblem = malloc(sizeof(stack_data));

    initialProblem->city = 0;
    initialProblem->pathLength = 0;
    initialProblem->step = 0;
    InitializeArray(params.cities, &initialProblem->visited);
    initialProblem->visited[initialProblem->city] = initialProblem->step + 1;

    stack_data *upperBound = NearestNeighbourMethod(params);

    double start = omp_get_wtime();
    stack_data *solution = HPBB_solve(initialProblem, upperBound, &params);
    double duration = omp_get_wtime() - start;
    printf("It took %f seconds for algorithm.\n", duration);

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