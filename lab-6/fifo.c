#include <stdio.h>  
int main()  
{  
    int incomingStream[] = {7, 0, 1, 2, 0, 3, 3, 4, 2, 3, 0, 3, 2, 2, 0};  
    int pageFaults = 0;  
    int frames = 3;  
    int m, n, s, pages;   
    pages = sizeof(incomingStream) / sizeof(incomingStream[0]);   
    printf("Ref String\tFrame 1\t\tFrame 2\t\tFrame 3\n");  
    int temp[frames];  
    for(m = 0; m < frames; m++)  
    {  
        temp[m] = -1;  
    }  
    for(m = 0; m < pages; m++)  
    {  
        s = 0;   
        for(n = 0; n < frames; n++)  
        {  
            if(incomingStream[m] == temp[n])  
            {  
                s++;  
                pageFaults--;  
                break; 
            }   
        }  
        pageFaults++;  
        if((pageFaults <= frames) && (s == 0))  
        {  
            temp[m] = incomingStream[m];  
        }  
        else if(s == 0)  
        {  
            temp[(pageFaults - 1) % frames] = incomingStream[m];  
        }  
        printf("%d\t\t", incomingStream[m]);  
        for(n = 0; n < frames; n++)  
        {  
            if(temp[n] != -1)  
                printf("%d\t\t", temp[n]);  
            else  
                printf("-\t\t");  
        }  
        printf("\n");  
    }  
    printf("Total Page Faults:\t%d\n", pageFaults);  
    float pageFaultRatio = ((float)pageFaults / pages) * 100;  
    printf("Page Fault Ratio:\t%.2f%%\n", pageFaultRatio);  
    return 0;
}
