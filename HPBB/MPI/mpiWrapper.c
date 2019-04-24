#include "mpiWrapper.h"
#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

static int _rank;
static int _size;
static int _boundSource;

static HPBB_message_passing_functions _functions;

static int FindBoundSource();

void MPI_Wrapper_Init(int *size, int *rank, HPBB_message_passing_functions functions) {
    _functions = functions;

    int provided;
    MPI_Init_thread(NULL, NULL, MPI_THREAD_SERIALIZED, &provided);

    MPI_Comm_size(MPI_COMM_WORLD, size);
    MPI_Comm_rank(MPI_COMM_WORLD, rank);

    if (*rank == 0) {
        printf("Provided thread support level: %d\n", provided);
        if (provided != MPI_THREAD_SERIALIZED) {
            exit(1234);
        }
    }

    _size = *size;
    _rank = *rank;

    _boundSource = _rank;
}

void MPI_Wrapper_Finalize() {
    MPI_Finalize();
}

void MPI_Wrapper_Receive_Bound(void *boundToUpdate) {
    int flag;
    MPI_Status probeStatus;
    MPI_Iprobe(MPI_ANY_SOURCE, MPI_BOUND_TAG, MPI_COMM_WORLD, &flag, &probeStatus);

    if (flag) {
        MPI_Status status;

        HPBB_message_passing_bound_indication receivedIndication = _functions.receiveBoundIndication();
        MPI_Recv(receivedIndication.bound, 1, receivedIndication.type, probeStatus.MPI_SOURCE, MPI_BOUND_TAG, MPI_COMM_WORLD, &status);

        if (_functions.updateBoundIndication(receivedIndication.bound, boundToUpdate)) {
            _boundSource = status.MPI_SOURCE;
        }

        MPI_Wrapper_Receive_Bound(boundToUpdate);
    }
}

void MPI_Wrapper_Share_Bound(void *bound) {
    for (int destination = 0; destination < _size; ++destination) {
        if (destination == _rank) continue;

        HPBB_message_passing_bound_indication boundIndication = _functions.selectBoundIndication(bound);
        MPI_Send(boundIndication.bound, 1, boundIndication.type, destination, MPI_BOUND_TAG, MPI_COMM_WORLD);
    }

    _boundSource = _rank;
}

void MPI_Wrapper_Synchronize(void *boundToUpdate, void *globalParams) {
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Wrapper_Receive_Bound(boundToUpdate);

    MPI_Barrier(MPI_COMM_WORLD);
    int boundSource = FindBoundSource();
    MPI_Barrier(MPI_COMM_WORLD);

    HPBB_message_passing_solution_array solutionArray = _functions.selectSolutionArray(boundToUpdate, globalParams);
    MPI_Bcast(solutionArray.array, solutionArray.arraySize, solutionArray.type, boundSource, MPI_COMM_WORLD);
}

static int FindBoundSource() {
    int *boundSources = NULL;
    if (_rank == 0) {
        boundSources = malloc(sizeof(int) * _size);
    }

    MPI_Gather(&_boundSource, 1, MPI_INT, boundSources, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (_rank == 0) {
        int failed = 0;
        for (int i = 0; i < _size - 1; ++i) {
            if (boundSources[i] != boundSources[i + 1]) {
                failed = 1;
            }
        }

        if (failed) {
            printf("Best bound sources does not match. ");
            for (int i = 0; i < _size; ++i) {
                printf("%d ", boundSources[i]);
            }
            printf("\n");

            exit(2345);
        }
    }

    return _boundSource;
}
