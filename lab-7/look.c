#include <stdio.h>
#include <stdlib.h>
#define SIZE 7
void sortRequests(int requests[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (requests[i] > requests[j])
            {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
}
void LOOK(int requests[], int size, int head, int direction)
{
    int distance = 0;
    int seek_sequence[SIZE + 1];
    int index = 0;
    sortRequests(requests, size);
    int i;
    for (i = 0; i < size; i++)
    {
        if (requests[i] >= head)
        {
            break;
        }
    }
    if (direction == 1)
    {
        for (int j = i; j < size; j++)
        {
            seek_sequence[index++] = requests[j];
        }
        for (int j = i - 1; j >= 0; j--)
        {
            seek_sequence[index++] = requests[j];
        }
    }
    else
    {
        for (int j = i - 1; j >= 0; j--)
        {
            seek_sequence[index++] = requests[j];
        }
        for (int j = i; j < size; j++)
        {
            seek_sequence[index++] = requests[j];
        }
    }
    int initial_head = head;
    for (int i = 0; i < SIZE; i++)
    {
        distance += abs(seek_sequence[i] - initial_head);
        initial_head = seek_sequence[i];
    }
    printf("Seek Sequence: \n ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d\n", seek_sequence[i]);
    }
    printf("Total number of seek operations = %d\n", distance);
}
int main()
{
    int requests[SIZE] = {82, 170, 43, 140, 24, 16, 190};
    int head = 50;
    int direction = 1;
    printf("Initial position of head: %d\n", head);
    LOOK(requests, SIZE, head, direction);
    return 0;
}