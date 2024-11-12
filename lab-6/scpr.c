#include <stdio.h>  
int main()  
{  
    int incomingStream[] = {5, 3, 5, 1, 5, 2, 4, 5, 3, 2, 3, 5};  
    int pageFaults = 0;  
    int frames = 3;  
    int pointer = 0;  
    int pages = sizeof(incomingStream) / sizeof(incomingStream[0]);   
    int temp[frames], useBit[frames];  
    for(int m = 0; m < frames; m++)  
    {  
        temp[m] = -1;  
        useBit[m] = 0;  
    }  
    printf("Ref String\tFrame 1\t\tFrame 2\t\tFrame 3\n");  
    for(int m = 0; m < pages; m++)  
    {  
        int found = 0;   
        for(int n = 0; n < frames; n++)  
        {  
            if(incomingStream[m] == temp[n])  
            {  
                found = 1;  
                useBit[n] = 1; 
                break; 
            }  
        }  
        if(!found)  
        {  
            while(useBit[pointer] == 1)  
            {  
                useBit[pointer] = 0; 
                pointer = (pointer + 1) % frames; 
            }  
            temp[pointer] = incomingStream[m];  
            useBit[pointer] = 1;  
            pointer = (pointer + 1) % frames;  
            pageFaults++;  
        }  
        printf("%d\t\t", incomingStream[m]);  
        for(int n = 0; n < frames; n++)  
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