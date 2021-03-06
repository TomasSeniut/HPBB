#include "IO.h"

qa_global ReadGlobalData(const char *fileName) {
    FILE *fp;
    if (!(fp = fopen(fileName, "r"))) {
        printf("Files does not exists\n");
        exit(121212);
    }

    qa_global params;

    fscanf(fp, "# Locations: %d\n", &params.locations);

    params.distanceMatrix = (int **) malloc(sizeof(int *) * params.locations);
    for (int j = 0; j < params.locations; j++)
        params.distanceMatrix[j] = (int *) malloc(params.locations * sizeof(int));

    for (int i = 0; i < params.locations; ++i) {
        for (int j = 0; j < params.locations; ++j) {
            fscanf(fp, "%d", &(params.distanceMatrix[i][j]));
        }
    }

    fscanf(fp, "\n# Flow:\n");

    params.flowMatrix = (int **) malloc(sizeof(int *) * params.locations);
    for (int j = 0; j < params.locations; j++)
        params.flowMatrix[j] = (int *) malloc(params.locations * sizeof(int));

    for (int i = 0; i < params.locations; ++i) {
        for (int j = 0; j < params.locations; ++j) {
            fscanf(fp, "%d", &(params.flowMatrix[i][j]));
        }
    }

    fclose(fp);

    return params;
}

void PrintResult(qa_global params, stack_data solution) {
    printf("Solution cost: %ld\n", solution.cost);
    printf("Assignment: ");
    for (int i = 0; i < params.locations; ++i) {
        printf("%d:%d ", i, solution.assignment[i]);
    }
    printf("\n");
}