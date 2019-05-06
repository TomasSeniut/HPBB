#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <HPBB.h>
#include "DataStructure.h"
#include "IO/IO.h"
#include "utils.h"

stack_data *randomWithCorrectingIterations(qa_global params);

static long GetLowerBound(stack_data node, qa_global params);

static long CostOfAssignment(qa_global params, stack_data node, int currentLocation, int factory);

void qa_branch(stack_data *node, qa_global *params, HPBB_node_processing next) {
    int current = node->location + 1;

    for (int i = 0; i < params->locations; ++i) {
        if (node->factoryTaken[i]) {
            continue;
        }

        stack_data *subProblem = malloc(sizeof(stack_data));

        subProblem->location = current;
        InitializeAndCopyArray(params->locations, node->assignment, &subProblem->assignment);
        subProblem->assignment[current] = i;
        InitializeAndCopyArray(params->locations, node->factoryTaken, &subProblem->factoryTaken);
        subProblem->factoryTaken[i] = 1;
        subProblem->cost = node->cost + CostOfAssignment(*params, *subProblem, current, i);

        next(subProblem);
    }
}

int qa_isSolution(stack_data *node, qa_global *params) {
    return (node->location + 1) >= params->locations;
}

int qa_isSolutionBetterThanUpperBound(stack_data *solutionNode, stack_data *upperBound, qa_global *params) {
    return upperBound->cost >= solutionNode->cost;
}

int qa_isLowerBoundOfNodeBetterThanUpperBound(stack_data *node, stack_data *upperBound, qa_global *params) {
    double costEstimate = node->cost + GetLowerBound(*node, *params);
    return upperBound->cost >= costEstimate;
}

void qa_disposeNode(stack_data *node) {
    free(node->assignment);
    free(node->factoryTaken);
    free(node);
}

HPBB_message_passing_bound_indication qa_selectBoundIndication(stack_data *node) {
    HPBB_message_passing_bound_indication data = {
            .bound = &node->cost,
            .type = MPI_LONG
    };

    return data;
}

HPBB_message_passing_solution_array qa_selectSolutionArray(stack_data *node, qa_global *params) {
    HPBB_message_passing_solution_array data = {
            .array = node->assignment,
            .arraySize = params->locations,
            .type = MPI_INT
    };

    return data;
}

HPBB_message_passing_bound_indication qa_receiveBoundIndication() {
    long *someBound = malloc(sizeof(long));
    HPBB_message_passing_bound_indication data = {
            .bound = someBound,
            .type = MPI_LONG
    };

    return data;
}

int qa_updateBoundIndication(void *receivedBound, stack_data *node) {
    long bound = *(long*)receivedBound;

    free(receivedBound);

    if (node->cost >= bound) {
        node->cost = bound;

        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./QuadraticAssignment problemFileName\n");
        return 1;
    }

    HPBB_queues queues = HPBB_default_DataStructures();

    HPBB_algorithm_functions functions = {
            .branch = qa_branch,
            .isSolution = qa_isSolution,
            .isSolutionBetterThanUpperBound = qa_isSolutionBetterThanUpperBound,
            .isLowerBoundOfNodeBetterThanUpperBound = qa_isLowerBoundOfNodeBetterThanUpperBound,
            .disposeNode = qa_disposeNode
    };

    HPBB_message_passing_functions messagingFunctions = {
            .receiveBoundIndication = qa_receiveBoundIndication,
            .updateBoundIndication = qa_updateBoundIndication,
            .selectBoundIndication = qa_selectBoundIndication,
            .selectSolutionArray = qa_selectSolutionArray
    };

    HPBB_init_solver(queues, functions, messagingFunctions);

    char *dataFileName = argv[1];

    qa_global params = ReadGlobalData(dataFileName);
    stack_data *upperBound = randomWithCorrectingIterations(params);

    stack_data *initialProblem = malloc(sizeof(stack_data));
    InitializeArray(params.locations, &initialProblem->assignment);
    InitializeArray(params.locations, &initialProblem->factoryTaken);
    initialProblem->cost = 0;
    initialProblem->location = -1;

    double start = omp_get_wtime();
    stack_data *solution = HPBB_solve(initialProblem, upperBound, &params);
    double duration = omp_get_wtime() - start;

    printf("It took %f seconds for algorithm.\n", duration);

    PrintResult(params, *solution);

    return 0;
}


static long CostOfAssignment(qa_global params, stack_data node, int currentLocation, int factory) {
    long cost = 0;
    for (int i = 0; i < currentLocation; ++i) {
        cost += params.distanceMatrix[i][currentLocation] * params.flowMatrix[node.assignment[i]][factory];
    }

    return cost;
}

static long GetLowerBound(stack_data node, qa_global params) {
    return 0;
}