#ifndef TRAVELINGSALESMAN_LINKEDQUEUE_H
#define TRAVELINGSALESMAN_LINKEDQUEUE_H

#include "Data.h"

void initQueue();
void enQueue(void* data);
int deQueue(void** data);
int isQueueEmpty();

#endif //TRAVELINGSALESMAN_LINKEDQUEUE_H
