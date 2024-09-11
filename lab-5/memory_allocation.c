#include <stdio.h>
#include <stdbool.h>

#define NUM_PARTITIONS 5
#define NUM_PROCESSES 4

void firstFit(int partitions[], int partitionSize[], int processes[], int processSize[]);
void bestFit(int partitions[], int partitionSize[], int processes[], int processSize[]);
void nextFit(int partitions[], int partitionSize[], int processes[], int processSize[]);
void worstFit(int partitions[], int partitionSize[], int processes[], int processSize[]);

int main() {
    int partitions[NUM_PARTITIONS] = {0};  // 0 indicates that the partition is free
    int partitionSize[NUM_PARTITIONS] = {100, 500, 200, 300, 600};  // Sizes of partitions
    int processes[NUM_PROCESSES] = {212, 417, 112, 426};  // Sizes of processes

    printf("First Fit Allocation:\n");
    firstFit(partitions, partitionSize, processes, processes);

    // Reset partitions for the next fit
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        partitions[i] = 0;
    }

    printf("\nBest Fit Allocation:\n");
    bestFit(partitions, partitionSize, processes, processes);

    // Reset partitions for the next fit
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        partitions[i] = 0;
    }

    printf("\nNext Fit Allocation:\n");
    nextFit(partitions, partitionSize, processes, processes);

    // Reset partitions for the next fit
    for (int i = 0; i < NUM_PARTITIONS; i++) {
        partitions[i] = 0;
    }

    printf("\nWorst Fit Allocation:\n");
    worstFit(partitions, partitionSize, processes, processes);

    return 0;
}

void firstFit(int partitions[], int partitionSize[], int processes[], int processSize[]) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        bool allocated = false;
        for (int j = 0; j < NUM_PARTITIONS; j++) {
            if (!partitions[j] && partitionSize[j] >= processes[i]) {
                partitions[j] = processes[i];
                printf("Process %d allocated to partition %d.\n", processes[i], j + 1);
                allocated = true;
                break;
            }
        }
        if (!allocated) {
            printf("Process %d could not be allocated.\n", processes[i]);
        }
    }
}

void bestFit(int partitions[], int partitionSize[], int processes[], int processSize[]) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int bestIndex = -1;
        for (int j = 0; j < NUM_PARTITIONS; j++) {
            if (!partitions[j] && partitionSize[j] >= processes[i]) {
                if (bestIndex == -1 || partitionSize[j] < partitionSize[bestIndex]) {
                    bestIndex = j;
                }
            }
        }
        if (bestIndex != -1) {
            partitions[bestIndex] = processes[i];
            printf("Process %d allocated to partition %d.\n", processes[i], bestIndex + 1);
        } else {
            printf("Process %d could not be allocated.\n", processes[i]);
        }
    }
}

void nextFit(int partitions[], int partitionSize[], int processes[], int processSize[]) {
    int lastAllocatedPartition = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        bool allocated = false;
        for (int j = lastAllocatedPartition; j < NUM_PARTITIONS; j++) {
            if (!partitions[j] && partitionSize[j] >= processes[i]) {
                partitions[j] = processes[i];
                lastAllocatedPartition = j;
                printf("Process %d allocated to partition %d.\n", processes[i], j + 1);
                allocated = true;
                break;
            }
        }
        if (!allocated) {
            for (int j = 0; j < lastAllocatedPartition; j++) {
                if (!partitions[j] && partitionSize[j] >= processes[i]) {
                    partitions[j] = processes[i];
                    lastAllocatedPartition = j;
                    printf("Process %d allocated to partition %d.\n", processes[i], j + 1);
                    allocated = true;
                    break;
                }
            }
        }
        if (!allocated) {
            printf("Process %d could not be allocated.\n", processes[i]);
        }
    }
}

void worstFit(int partitions[], int partitionSize[], int processes[], int processSize[]) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        int worstIndex = -1;
        for (int j = 0; j < NUM_PARTITIONS; j++) {
            if (!partitions[j] && partitionSize[j] >= processes[i]) {
                if (worstIndex == -1 || partitionSize[j] > partitionSize[worstIndex]) {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1) {
            partitions[worstIndex] = processes[i];
            printf("Process %d allocated to partition %d.\n", processes[i], worstIndex + 1);
        } else {
            printf("Process %d could not be allocated.\n", processes[i]);
        }
    }
}

