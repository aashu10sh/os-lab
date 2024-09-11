#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CHAIRS 5

int waitingCustomers = 0;

void barber()
{
    while (1)
    {
        if (waitingCustomers == 0)
        {
            printf("The barber is sleeping.\n");
            sleep(1);
        }
        else
        {
            printf("The barber is cutting hair.\n");
            sleep(3);
            printf("The barber has finished cutting hair.\n");
            waitingCustomers--;
        }
    }
}

void customer()
{
    if (waitingCustomers < CHAIRS)
    {
        waitingCustomers++;
        printf("A customer is waiting. Customers waiting: %d\n", waitingCustomers);
    }
    else
    {
        printf("No chairs available. A customer is leaving.\n");
    }
}

int main()
{
    int customersToServe = 10;
    waitingCustomers = customersToServe;

    // Simulate the barber working
    barber();

    for (int i = 0; i < customersToServe; i++)
    {
        sleep(1); // New customer arrives every second
        customer();
    }

    return 0;
}

