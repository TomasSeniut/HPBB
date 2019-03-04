#ifndef TRAVELINGSALESMAN_PARALLELSTACK_H
#define TRAVELINGSALESMAN_PARALLELSTACK_H

#include "Data.h"

void initStackParallel();
void pushParallel(void* data);
int popParallel(void** data);
int isEmptyParallel();
void destroyStack();

#endif //TRAVELINGSALESMAN_PARALLELSTACK_H
