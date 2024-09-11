#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 10
#define MAX_RESOURCES 10
void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allot[MAX_PROCESSES][MAX_RESOURCES], int P, int R) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}
bool isSafe(int processes[], int avail[], int max[][MAX_RESOURCES], int allot[][MAX_RESOURCES], int P, int R) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, allot, P, R);
    bool finish[MAX_PROCESSES] = {0};
    int safeSeq[MAX_PROCESSES];
    int work[MAX_RESOURCES];
    
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j])
                        break;
                }
                if (j == R) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }
        if (found == false) {
            printf("System is not in a safe state\n");
            return false;
        }}
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    return true;}
int main() {
    int processes[] = {0, 1, 2, 3, 4};
    int P = sizeof(processes) / sizeof(processes[0]);
    int avail[] = {3, 3, 2};
    int max[][MAX_RESOURCES] = {{7, 5, 3},
                                {3, 2, 2},
                                {9, 0, 2},
                                {2, 2, 2},
                                {4, 3, 3}};
    int allot[][MAX_RESOURCES] = {{0, 1, 0},
                                  {2, 0, 0},
                                  {3, 0, 2},
                                  {2, 1, 1},
                                  {0, 0, 2}};
    int R = sizeof(avail) / sizeof(avail[0]);
    isSafe(processes, avail, max, allot, P, R);
    return 0;
}
