#ifndef HPBB_LIBRARY_H
#define HPBB_LIBRARY_H

#include <mpi.h>

typedef struct {
    void (*init)(void);
    void (*enQueue)(void* data);
    int (*deQueue)(void** data);
    int (*isEmpty)(void);
} HPBB_queue_interface;

typedef struct {
    HPBB_queue_interface staticLoadBalancing;
    HPBB_queue_interface main;
} HPBB_queues;

typedef struct {
    void *array;
    int arraySize;
    MPI_Datatype type;
} HPBB_message_passing_solution_array;

typedef struct {
    void *bound;
    MPI_Datatype type;
} HPBB_message_passing_bound_indication;

typedef struct {
    HPBB_message_passing_bound_indication (*receiveBoundIndication)();
    int (*updateBoundIndication)(void *receivedIndication, void *upperBound);
    HPBB_message_passing_solution_array (*selectSolutionArray)(void *node, void *globalParams);
    HPBB_message_passing_bound_indication (*selectBoundIndication)(void *node);
} HPBB_message_passing_functions;

typedef void (*HPBB_node_processing)(void*);

typedef struct {
    void (*branch)(void* node, void* globalParameters, HPBB_node_processing next);
    int (*isSolution)(void* node, void* globalParams);
    int (*isSolutionBetterThanUpperBound)(void* solution, void* upperBound, void* globalParams);
    int (*isLowerBoundOfNodeBetterThanUpperBound)(void* node, void *upperBound, void* globalParams);
    void (*disposeNode)(void* node);
} HPBB_algorithm_functions;

HPBB_queues HPBB_default_DataStructures(void);
void HPBB_init_solver(HPBB_queues queues, HPBB_algorithm_functions functions, HPBB_message_passing_functions messagingFunctions);
void *HPBB_solve(void *initialProblem, void *upperBound, void *globalParameters);

#endif