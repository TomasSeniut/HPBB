#include <stdio.h>
#include "DataStructure/LinkedQueue.h"
#include "DataStructure/ParallelStack.h"
#include "include/HPBB.h"

HPBB_queues HPBB_default_DataStructures(void) {
    HPBB_queues queues;

    queues.staticLoadBalancing.init = initQueue;
    queues.staticLoadBalancing.enQueue = enQueue;
    queues.staticLoadBalancing.deQueue = deQueue;
    queues.staticLoadBalancing.isEmpty = isQueueEmpty;

    queues.main.init = initStackParallel;
    queues.main.enQueue = pushParallel;
    queues.main.deQueue = popParallel;
    queues.main.isEmpty = isEmptyParallel;

    return queues;
}