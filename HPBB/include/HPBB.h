#ifndef HPBB_LIBRARY_H
#define HPBB_LIBRARY_H

typedef void (*HPBB_node_processing_pipeline)(void*);

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
    void (*branch)(void* globalParameters, void* node, HPBB_node_processing_pipeline next);
    int (*isSolution)(void* node);
    int (*firstBetterThanSecond)(void*, void*);
    void* (*lowerBound)(void* node);
    void (*disposeNode)(void* node);
} HPBB_algorithm_functions;

HPBB_queues HPBB_default_DataStructures(void);
void HPBB_init_solver(HPBB_queues queues, HPBB_algorithm_functions functions);
void *HPBB_solve(void *initialProblem, void *upperBound, void *globalParameters);

#endif