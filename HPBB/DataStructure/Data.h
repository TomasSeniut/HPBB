#ifndef HPBB_DATA_H
#define HPBB_DATA_H

typedef struct stack_node stack_node;
struct stack_node
{
    void* data;
    stack_node* next;
};


#endif //HPBB_DATA_H
