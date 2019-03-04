#include <HPBB.h>
#include <stdio.h>
#include <stdlib.h>

static int _initialized = 0;
static void* _upperBound;
static HPBB_queues _queues;
static HPBB_algorithm_functions _functions;
static void* _globalParameters;

static void *branchAndBoundLoop();

void HPBB_init_solver(HPBB_queues queues, HPBB_algorithm_functions functions) {
    _queues = queues;
    _functions = functions;
    _initialized = 1;
}

void *HPBB_solve(void *initialProblem, void *upperBound, void *globalParameters) {
    if (!_initialized) {
        printf("Solver was not initialized with needed params. Please call `HPBB_init_solver` first.");
        exit(999);
    }

    _upperBound = upperBound;
    _globalParameters = globalParameters;

    return branchAndBoundLoop(initialProblem);
}

static void next(void* node) {
    if (_functions.isSolution(node)) {

        if (_functions.firstBetterThanSecond(node, _upperBound)) {
            #pragma omp critical
            {
                if (_functions.firstBetterThanSecond(node, _upperBound)) {
                    void* temp = _upperBound;
                    _upperBound = node;
                    node = temp;
                }
            }
        }

        _functions.disposeNode(node);
        return;
    }

    if (_functions.firstBetterThanSecond(_upperBound, _functions.lowerBound(node))) {
        _functions.disposeNode(node);
        return;
    }

    _queues.main.enQueue(node);
}

static void *branchAndBoundLoop(void *initialProblem) {
    _queues.main.init();
    _queues.main.enQueue(initialProblem);

    #pragma omp parallel
    {
        while (!_queues.main.isEmpty()) {
            void* problem;
            int success = _queues.main.deQueue(&problem);
            if (!success) {
                continue;
            }

            _functions.branch(_globalParameters, problem, next);
            _functions.disposeNode(problem);
        }
    }

    return _upperBound;
}


