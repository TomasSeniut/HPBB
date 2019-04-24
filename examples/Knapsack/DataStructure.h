#ifndef KNAPSACK_DATASTRUCTURE_H
#define KNAPSACK_DATASTRUCTURE_H

typedef struct {
    int weight;
    int price;
} Item;

typedef struct {
    int weight;
    int price;
    int index;
} ItemWithIndex;

typedef struct {
    int count;
    int weight;
    Item *items;
    int *originalIndexes;
} knapsack_global;

typedef struct {
    int weight;
    int price;
    int current;
    char *taken;
} stack_data;

#endif //KNAPSACK_DATASTRUCTURE_H
