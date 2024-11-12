#include <stdio.h>
#include <stdlib.h>
#define SIZE 7
void sortRequests(int requests[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }  } } }
void SCAN(int requests[], int size, int head, int direction, int disk_size) {
    int distance = 0;
    int seek_sequence[SIZE + 2];  
    int index = 0;
    sortRequests(requests, size);
    int i;
    for (i = 0; i < size; i++) {
        if (requests[i] >= head) {
            break;
        }  }
    if (direction == 1) { 
        for (int j = i; j < size; j++) {
            seek_sequence[index++] = requests[j];
        }
        if (i < size) {
            seek_sequence[index++] = disk_size; 
        }
        for (int j = i - 1; j >= 0; j--) {
            seek_sequence[index++] = requests[j];
        }
    } else {
        for (int j = i - 1; j >= 0; j--) {
            seek_sequence[index++] = requests[j];
        }
        if (i >= 0) {
            seek_sequence[index++] = 0;  
        }
        for (int j = i; j < size; j++) {
            seek_sequence[index++] = requests[j];
        } }
    int initial_head = head;
    printf("Seek Sequence: \n");
    for (int i = 0; i < index; i++) {
        distance += abs(seek_sequence[i] - initial_head);
        printf("%d\n", seek_sequence[i]);
        initial_head = seek_sequence[i];
    }
    printf("Total number of seek operations = %d\n", distance);
}
int main() {
    int requests[SIZE] = {82, 170, 43, 140, 24, 16, 190};
    int head = 50;
    int direction = 1;  
    int disk_size = 200;
    printf("Initial position of head: %d\n", head);
    SCAN(requests, SIZE, head, direction, disk_size);    return 0;
}