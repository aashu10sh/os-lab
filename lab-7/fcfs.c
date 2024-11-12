#include <stdio.h>
#include <math.h>
 int size = 7;
 void FCFS(int arr[],int head)
{
    int seek_count = 0;
      int cur_track, distance;
       for(int i=0;i<size;i++)
       {
        cur_track = arr[i];
        distance = fabs(head - cur_track);
        seek_count += distance;
        head = cur_track;
    }
       printf("Total number of seek operations: %d\n",seek_count);
       printf("Seek Sequence is\n");
         for (int i = 0; i < size; i++) {
        printf("%d\n",arr[i]);
    }
}
int main()
{
    int arr[7] = { 82, 170,43,140,24,16,190};
      int head = 50;
      FCFS(arr,head);
      return 0;
}