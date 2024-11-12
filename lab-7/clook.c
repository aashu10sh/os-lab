#include <stdio.h>
#include <stdlib.h>
int size = 7;
int disk_size = 200;
void CLOOK(int arr[], int head) {
    int seek_count = 0;
    int distance, cur_track;
    int left[size], right[size];
    int left_size = 0, right_size = 0;
    int seek_sequence[size];
    int seq_index = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < head) {
            left[left_size++] = arr[i];
        }
        if (arr[i] > head) {
            right[right_size++] = arr[i];
        } }
    for (int i = 0; i < left_size - 1; i++) {
        for (int j = 0; j < left_size - i - 1; j++) {
            if (left[j] > left[j + 1]) {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }  } }
    for (int i = 0; i < right_size - 1; i++) {
        for (int j = 0; j < right_size - i - 1; j++) {
            if (right[j] > right[j + 1]) {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }  } }
    for (int i = 0; i < right_size; i++) {
        cur_track = right[i];
        seek_sequence[seq_index++] = cur_track;
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }
    if (left_size > 0) {
        seek_count += abs(head - left[0]);
        head = left[0];
        for (int i = 0; i < left_size; i++) {
            cur_track = left[i];
            seek_sequence[seq_index++] = cur_track;
            distance = abs(cur_track - head);
            seek_count += distance;
            head = cur_track;
        }
    }
    printf("Total number of seek operations = %d\n", seek_count);
    printf("Seek Sequence is:\n");
    for (int i = 0; i < seq_index; i++) {
        printf("%d\n", seek_sequence[i]);
    }
}
int main() {
    int arr[] = { 82,170,43,140,24,16,190 };
    int head = 50;
    printf("Initial position of head: %d\n", head);
    CLOOK(arr, head);
    return 0;
}