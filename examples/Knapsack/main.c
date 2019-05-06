#include <stdio.h>
#include <omp.h>
#include <HPBB.h>
#include <stdlib.h>
#include "DataStructure.h"
#include "IO/IO.h"
#include "utils.h"

static long count = 0;

stack_data *highestValueWeightRatio(knapsack_global params);

static int getKnapsackLowerBound(stack_data problem, knapsack_global params);

void ks_branch(stack_data *node, knapsack_global *params, HPBB_node_processing next) {
    int nextIndex = node->current + 1;

    count++;

    if (nextIndex > params->count) {
        return;
    }

    // item not taken
    stack_data *subProblemNotTaken = malloc(sizeof(stack_data));
    subProblemNotTaken->weight = node->weight;
    subProblemNotTaken->price = node->price;
    subProblemNotTaken->current = nextIndex;
    InitializeAndCopyArray(params->count, node->taken, &subProblemNotTaken->taken);
    subProblemNotTaken->taken[nextIndex] = 0;

    next(subProblemNotTaken);

    // item taken
    int weight = node->weight + params->items[nextIndex].weight;
    if (weight > params->weight) {
         return;
    }

    stack_data *subProblemTaken = malloc(sizeof(stack_data));
    subProblemTaken->weight = weight;
    subProblemTaken->price = node->price + params->items[nextIndex].price;
    subProblemTaken->current = nextIndex;
    InitializeAndCopyArray(params->count, node->taken, &subProblemTaken->taken);
    subProblemTaken->taken[nextIndex] = 1;

    next(subProblemTaken);
}

int ks_isSolution(stack_data *node, knapsack_global *params) {
    for (int i = node->current; i < params->count; ++i) {
        if (node->weight + params->items[i].weight <= params->weight) {
            return 0;
        }
    }

    return 1;
}

int ks_isSolutionBetterThanUpperBound(stack_data *solutionNode, stack_data *upperBound, knapsack_global *params) {
    int isBetter = upperBound->price <= solutionNode->price;

    return isBetter;
}

int ks_isNodeLowerBoundBetterThanUpper(stack_data *node, stack_data *upperBound, knapsack_global *params) {
    int lowerBound = getKnapsackLowerBound(*node, *params);
    int isBetter = upperBound->price <= lowerBound;

    return isBetter;
}

void ks_disposeNode(stack_data *node) {
    free(node->taken);
    free(node);
}

HPBB_message_passing_bound_indication ks_selectBoundIndication(stack_data *node) {
    HPBB_message_passing_bound_indication data = {
            .bound = &node->price,
            .type = MPI_INT
    };

    return data;
}

HPBB_message_passing_solution_array ks_selectSolutionArray(stack_data *node, knapsack_global *params) {
    HPBB_message_passing_solution_array data = {
            .array = node->taken,
            .arraySize = params->count,
            .type = MPI_CHAR
    };

    return data;
}

HPBB_message_passing_bound_indication ks_receiveBoundIndication() {
    int *someBound = malloc(sizeof(int));
    HPBB_message_passing_bound_indication data = {
            .bound = someBound,
            .type = MPI_INT
    };

    return data;
}

int ks_updateBoundIndication(void *receivedBound, stack_data *node) {
    int bound = *(int*)receivedBound;

    free(receivedBound);

    if (node->price <= bound) {
        node->price = bound;

        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./Knapsack problemFileName\n");
        return 1;
    }

    char* dataFileName = argv[1];

    HPBB_queues queues = HPBB_default_DataStructures();

    HPBB_algorithm_functions functions = {
            .branch = ks_branch,
            .isSolution = ks_isSolution,
            .isSolutionBetterThanUpperBound = ks_isSolutionBetterThanUpperBound,
            .isLowerBoundOfNodeBetterThanUpperBound = ks_isNodeLowerBoundBetterThanUpper,
            .disposeNode = ks_disposeNode
    };

    HPBB_message_passing_functions messagingFunctions = {
        .receiveBoundIndication = ks_receiveBoundIndication,
        .updateBoundIndication = ks_updateBoundIndication,
        .selectBoundIndication = ks_selectBoundIndication,
        .selectSolutionArray = ks_selectSolutionArray
    };

    HPBB_init_solver(queues, functions, messagingFunctions);

    knapsack_global params = ReadGlobalData(dataFileName);
    stack_data *upperBound = highestValueWeightRatio(params);

    stack_data *initialProblem = malloc(sizeof(stack_data));
    initialProblem->price = 0;
    initialProblem->weight = 0;
    initialProblem->current = -1;
    InitializeArray(params.count, &initialProblem->taken);

    double start = omp_get_wtime();
    stack_data *solution = HPBB_solve(initialProblem, upperBound, &params);
    double duration = omp_get_wtime() - start;
    printf("It took %f seconds for algorithm.\n", duration);

    PrintResult(params, *solution);

    return 0;
}

static int getKnapsackLowerBound(stack_data problem, knapsack_global params) {
    Item running = { .price = problem.price, .weight = problem.weight };

    for (int i = 0; i < params.count; ++i) {
        if (i <= problem.current) {
            continue;
        }

        int weight = running.weight + params.items[i].weight;

        if (weight >= params.weight) {
            float factor = (float) (params.weight - running.weight) / params.items[i].weight;

            running.price += (int) (factor * params.items[i].price);
            break;
        }

        running.weight = weight;
        running.price += params.items[i].price;
    }

    return running.price;
}