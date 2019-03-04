#include <stdio.h>
#include <malloc.h>
#include <HPBB.h>
#include "IO/IO.h"

typedef struct {
    int current;
    int *array;
} node;

int main(int argc, char *argv[]) {

    HPBB_queues queues = HPBB_default_DataStructures();

    HPBB_algorithm_functions functions;
    functions.branch = NULL;
    functions.isSolution = NULL;
    functions.firstBetterThanSecond = NULL;
    functions.lowerBound = NULL;
    functions.disposeNode = NULL;

    HPBB_init_solver(queues, functions);

    HPBB_solve();

    return 0;
}