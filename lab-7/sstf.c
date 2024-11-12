#include <stdio.h>
#include <stdlib.h>
void calculatedifference(int request[], int head, int diff[][2], int n)
{
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = abs(head - request[i]);
    }  }
int findMIN(int diff[][2], int n)
{
    int index = -1;
    int minimum = 1e9;
    for (int i = 0; i < n; i++)
    {
        if (!diff[i][1] && minimum > diff[i][0])
        {
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}
void shortestSeekTimeFirst(int request[], int head, int n)
{
    if (n == 0)
    {
        return;
    }
    int diff[n][2];
    for (int i = 0; i < n; i++)
    {
        diff[i][0] = 0;
        diff[i][1] = 0;
    }
    int seekcount = 0; 
    int seeksequence[n + 1];
    for (int i = 0; i < n; i++)
    {
        seeksequence[i] = head; 
        calculatedifference(request, head, diff, n);
        int index = findMIN(diff, n);
        diff[index][1] = 1; 
        seekcount += diff[index][0];
        head = request[index]; 
    }
    seeksequence[n] = head;
    printf("Total number of seek operations = %d\n", seekcount);
    printf("Seek sequence is : \n");
    for (int i = 0; i <= n; i++)
    {
        printf("%d\n", seeksequence[i]);
    }}
int main()
{
    int n = 7;
    int proc[] = { 82,170,43,140,24,16,190 };
    shortestSeekTimeFirst(proc, 50, n);
    return 0;
}