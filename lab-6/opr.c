#include <stdio.h>
int Optimal(int incomingStream[], int temp[], int pages, int currentIndex, int frames) {
    int farthest = currentIndex, pos = -1;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = currentIndex; j < pages; j++) {
            if (temp[i] == incomingStream[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == pages) {
            return i;
        }
    }
    return (pos == -1) ? 0 : pos;
}
int main() {
    int incomingStream[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2,0,1,7,0,1};
    int pageFaults = 0;
    int frames = 4;
    int pages = sizeof(incomingStream) / sizeof(incomingStream[0]);
    printf("Ref String\tFrame 1\t\tFrame 2\t\tFrame 3\n");
    int temp[frames];
    for (int i = 0; i < frames; i++) {
        temp[i] = -1;
    }
    for (int i = 0; i < pages; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (temp[j] == incomingStream[i]) {
                found = 1;
                break;
            }   }
        if (!found) {
            if (i < frames) {
                temp[i] = incomingStream[i];
            } else {
                int pos = Optimal(incomingStream, temp, pages, i + 1, frames);
                temp[pos] = incomingStream[i];
            }
            pageFaults++;
        }
        printf("%d\t\t", incomingStream[i]);
        for (int j = 0; j < frames; j++) {
            if (temp[j] != -1) {
                printf("%d\t\t", temp[j]);
            } else {
                printf("-\t\t");
            }       
    }
        printf("\n");
    }
    printf("Total Page Faults:\t%d\n", pageFaults);
    float pageFaultRatio = ((float)pageFaults / pages) * 100;
    printf("Page Fault Ratio:\t%.2f%%\n", pageFaultRatio);
    return 0;
}