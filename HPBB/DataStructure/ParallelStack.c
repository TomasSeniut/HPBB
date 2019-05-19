#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include "ParallelStack.h"

static stack_node *_head;

static omp_lock_t _lock;
static int _numberOfThreads;

static volatile int *_workFlags;

static void **_localStore;

static long _count = 0;

void initStackParallel() {
    _head = NULL;

    _numberOfThreads = omp_get_max_threads();

    _workFlags = malloc(sizeof(int) * _numberOfThreads);
    for (int i = 0; i < _numberOfThreads; ++i) {
        _workFlags[i] = 0;
    }

    _localStore = malloc(sizeof(void*) * _numberOfThreads);
    for (int i = 0; i < _numberOfThreads; ++i) {
        _localStore[i] = NULL;
    }

    omp_init_lock(&_lock);
}

void pushParallel(void* data) {
    if (_localStore[omp_get_thread_num()] == NULL) {
        _localStore[omp_get_thread_num()] = data;

        #pragma omp atomic
        _count++;
        return;
    }

    stack_node *tmp = (stack_node *) malloc(sizeof(stack_node));
    if (tmp == NULL) {
        exit(111);
    }

    omp_set_lock(&_lock);

    tmp->data = data;
    tmp->next = _head;
    _head = tmp;

    _count++;

    omp_unset_lock(&_lock);
}

int popParallel(void** element) {
    if (_localStore[omp_get_thread_num()] != NULL) {
        *element = _localStore[omp_get_thread_num()];
        _localStore[omp_get_thread_num()] = NULL;
        _workFlags[omp_get_thread_num()] = 1;

        return 1;
    }

    omp_set_lock(&_lock);

    if (_head == NULL) {
        _workFlags[omp_get_thread_num()] = 0;

        omp_unset_lock(&_lock);
        return 0;
    }

    stack_node *tmp = _head;
    *element = _head->data;
    _head = _head->next;

    free(tmp);

    _workFlags[omp_get_thread_num()] = 1;
    omp_unset_lock(&_lock);

    return 1;
}

int isEmptyParallel() {
    if (_localStore[omp_get_thread_num()] != NULL) {
        return 0;
    }

    int isEmpty = _head == NULL ? 1 : 0;
    if (!isEmpty) {
        return 0;
    }

    omp_set_lock(&_lock);

    for (int i = 0; i < _numberOfThreads; ++i) {
        if (_workFlags[i]) {
            omp_unset_lock(&_lock);
            return 0;
        }
    }

    omp_unset_lock(&_lock);
    return 1;
}

void destroyStack() {
    printf("Total elements processed: %ld\n", _count);

    omp_destroy_lock(&_lock);
    free((void*)_workFlags);
    free(_localStore);
}