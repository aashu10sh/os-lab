#include <stdio.h>
int LeastFreq(int frequency[], int frameCount, int arrivalOrder[]) {
    int minFreq = frequency[0];  
    int index = 0;
    for (int i = 1; i < frameCount; i++) { 
        if (frequency[i] < minFreq) {
            minFreq = frequency[i];
            index = i;
        } else if (frequency[i] == minFreq) {
            if (arrivalOrder[i] < arrivalOrder[index]) {
                index = i;
            }   }  }
    return index;
}
int main() {
    int incomingStream[] = {7, 0, 2, 4, 3, 1, 4, 7, 2, 0, 4, 3, 0, 3, 2, 7};
    int pageFaults = 0;
    int frames = 3;
    int pages = sizeof(incomingStream) / sizeof(incomingStream[0]);
    printf("Ref String\tFrame 1\t\tFrame 2\t\tFrame 3\n");
    int temp[frames], frequency[frames], arrivalOrder[frames];
    for (int i = 0; i < frames; i++) {
        temp[i] = -1;
        frequency[i] = 0;
        arrivalOrder[i] = -1;
    }
    for (int i = 0; i < pages; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (temp[j] == incomingStream[i]) {
                frequency[j]++;
                found = 1;
                arrivalOrder[j] = i;
                break;
            }     }
        if (!found) {
            int pos;
            if (i < frames) {
                pos = i; 
            } else {
                pos = LeastFreq(frequency, frames, arrivalOrder);
            }
            temp[pos] = incomingStream[i];
            frequency[pos] = 1;
            arrivalOrder[pos] = i;
            pageFaults++;
        }
        printf("%d\t\t", incomingStream[i]);
        for (int j = 0; j < frames; j++) {
            if (temp[j] != -1) {
                printf("%d\t\t", temp[j]);
            } else {
                printf("-\t\t");
            }        }
        printf("\n");
    }
    printf("Total Page Faults:\t%d\n", pageFaults);
    float pageFaultRatio = ((float)pageFaults / pages) * 100;
    printf("Page Fault Ratio:\t%.2f%%\n", pageFaultRatio);
    return 0;
}