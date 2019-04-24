#ifndef TRAVELINGSALESMAN_MPI_H
#define TRAVELINGSALESMAN_MPI_H

#include <HPBB.h>

enum { MPI_PROBLEM_TAG = 11, MPI_BOUND_TAG = 22 };

void MPI_Wrapper_Init(int *size, int *rank, HPBB_message_passing_functions functions);
void MPI_Wrapper_Finalize();
void MPI_Wrapper_Share_Bound(void *bound);
void MPI_Wrapper_Receive_Bound(void *boundToUpdate);
void MPI_Wrapper_Synchronize(void *boundToUpdate, void *globalParams);

#endif //TRAVELINGSALESMAN_MPI_H
