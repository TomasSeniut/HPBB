#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "LinkedQueue.h"

typedef struct {
    stack_node *front;
    stack_node *rear;
} Queue;

static Queue *_queue;

void initQueue()
{
    _queue = (Queue*)malloc(sizeof(Queue));
    _queue->front = _queue->rear = NULL;
}

void enQueue(void* data)
{
    stack_node *tmp = (stack_node *) malloc(sizeof(stack_node));
    if (tmp == NULL) {
        exit(222);
    }

    tmp->data = data;
    tmp->next = NULL;

    if (_queue->rear == NULL)
    {
        _queue->front = _queue->rear = tmp;
        return;
    }

    _queue->rear->next = tmp;
    _queue->rear = tmp;
}

int deQueue(void** data)
{
    *data = _queue->front->data;

    _queue->front = _queue->front->next;

    if (_queue->front == NULL) {
        _queue->rear = NULL;
    }

    return 1;
}

int isQueueEmpty()
{
    return _queue->front == NULL ? 1 : 0;
}