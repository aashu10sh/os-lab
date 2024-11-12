#include <stdio.h>
int LeastRecent(int time[], int frames) {
    int min = time[0], pos = 0;
    for (int i = 1; i < frames; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}
int main() {
    int incomingStream[] = {5, 1, 1, 2, 0, 3, 0, 3, 3, 3, 0, 3, 2, 1, 2, 0};
    int pageFaults = 0;
    int frames = 3;
    int pages = sizeof(incomingStream) / sizeof(incomingStream[0]);
    printf("Ref String\tFrame 1\t\tFrame 2\t\tFrame 3\n");
    int temp[frames], time[frames];
    for (int i = 0; i < frames; i++) {
        temp[i] = -1;
        time[i] = -1;
    }
    for (int i = 0; i < pages; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (temp[j] == incomingStream[i]) {
                found = 1;
                time[j] = i; // Update the time of the page being used
                break;
            }
        }
        if (!found) {
            int pos;
            if (i < frames) {
                pos = i;
            } else {
                pos = LeastRecent(time, frames);
            }
            temp[pos] = incomingStream[i];
            time[pos] = i;
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