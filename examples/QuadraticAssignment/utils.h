#ifndef QUADRATICASSIGMENT_UTILS_H
#define QUADRATICASSIGMENT_UTILS_H

#include <math.h>
#include <stdlib.h>
#include "DataStructure.h"

void PopulateDistanceMatrix(int n, point *array, double *distanceMatrix[]);

void InitializeArray(int n, int ** array);
void CopyArray(int n, const int from[], int to[]);
void InitializeAndCopyArray(int n, const int *from, int **to);

#endif //QUADRATICASSIGMENT_UTILS_H
