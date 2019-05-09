#include <HPBB.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <MPI/mpiWrapper.h>

static int _initialized = 0;
static void *_upperBound;
static void *_globalParameters;

static int _loadBalancingSize = 0;

static HPBB_queues _queues;
static HPBB_algorithm_functions _functions;
static HPBB_message_passing_functions _messagingFunctions;

static void loadBalancingBranchAndBoundLoop();

static void branchAndBoundLoop();

static void mainNodeProcessing(void *node);

static void loadBalancingNodeProcessing(void *node);

void HPBB_init_solver(HPBB_queues queues, HPBB_algorithm_functions functions, HPBB_message_passing_functions messagingFunctions) {
    _queues = queues;
    _functions = functions;
    _messagingFunctions = messagingFunctions;
    _initialized = 1;
}

void *HPBB_solve(void *initialProblem, void *upperBound, void *globalParameters) {
    if (!_initialized) {
        printf("Solver was not initialized with needed params. Please call `HPBB_init_solver` first.");
        exit(999);
    }

    _upperBound = upperBound;
    _globalParameters = globalParameters;

    _queues.staticLoadBalancing.init();
    _queues.staticLoadBalancing.enQueue(initialProblem);

    loadBalancingBranchAndBoundLoop();

    if (_queues.staticLoadBalancing.isEmpty()) {
        return _upperBound;
    }

    int rank;
    int size;
    MPI_Wrapper_Init(&size, &rank, _messagingFunctions);

    int count = 0;
    _queues.main.init();

    while (!_queues.staticLoadBalancing.isEmpty()) {
        void *queueElement = NULL;
        _queues.staticLoadBalancing.deQueue(&queueElement);

        if (queueElement == NULL) {
            printf("`queueElement` should not be NULL here.");
        }

        int destination = ++count % size;
        if (destination == rank) {
            _queues.main.enQueue(queueElement);
        }
    }

    printf("I am process %d with %d threads and have stack of size %d\n", rank, omp_get_max_threads(), count);

    branchAndBoundLoop();

    MPI_Wrapper_Synchronize(_upperBound, _globalParameters);
    printf("Finished work on process %d\n", rank);

    MPI_Wrapper_Finalize();

    return _upperBound;
}

static void loadBalancingBranchAndBoundLoop() {
    _loadBalancingSize = 0;
    int maxBalancingSize = 10 * 8 * 10;

    while (_loadBalancingSize < maxBalancingSize && !_queues.staticLoadBalancing.isEmpty()) {
        void *problem;
        int success = _queues.staticLoadBalancing.deQueue(&problem);
        if (!success) {
            continue;
        }

        _functions.branch(problem, _globalParameters, loadBalancingNodeProcessing);
        _functions.disposeNode(problem);
    }
}

static void branchAndBoundLoop() {
    #pragma omp parallel
    {
        while (!_queues.main.isEmpty()) {
            void *problem;
            int success = _queues.main.deQueue(&problem);
            if (!success) {
                continue;
            }

            _functions.branch(problem, _globalParameters, mainNodeProcessing);
            _functions.disposeNode(problem);
        }

        printf("Thread: %d finished working\n", omp_get_thread_num());
    }
}

static void mainNodeProcessing(void *node) {
    if (_functions.isSolution(node, _globalParameters)) {

        if (_functions.isSolutionBetterThanUpperBound(node, _upperBound, _globalParameters)) {
            void *temp = NULL;

            #pragma omp critical(mainUpperBoundUpdate)
            {
                MPI_Wrapper_Receive_Bound(node);

                if (_functions.isSolutionBetterThanUpperBound(node, _upperBound, _globalParameters)) {
                    temp = _upperBound;
                    _upperBound = node;

                    MPI_Wrapper_Share_Bound(node);
                }
            }

            if (temp != NULL) {
                _functions.disposeNode(temp);
                return;
            }
        }
    }

    if (!_functions.isLowerBoundOfNodeBetterThanUpperBound(node, _upperBound, _globalParameters)) {
        _functions.disposeNode(node);
        return;
    }

    _queues.main.enQueue(node);
}

static void loadBalancingNodeProcessing(void *node) {
    if (_functions.isSolution(node, _globalParameters)) {

        if (_functions.isSolutionBetterThanUpperBound(node, _upperBound, _globalParameters)) {
            void *temp = _upperBound;
            _upperBound = node;
            _functions.disposeNode(temp);
            return;
        }
    }

    if (!_functions.isLowerBoundOfNodeBetterThanUpperBound(node, _upperBound, _globalParameters)) {

        _functions.disposeNode(node);
        return;
    }

    #pragma omp atomic
    _loadBalancingSize++;

    _queues.staticLoadBalancing.enQueue(node);
}
