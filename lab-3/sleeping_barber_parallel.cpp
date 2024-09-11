#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define CHAIRS 5

int waitingCustomers = 0;

// Mutex and condition variables for synchronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t customerAvailable = PTHREAD_COND_INITIALIZER;
pthread_cond_t barberAvailable = PTHREAD_COND_INITIALIZER;

void* barber(void* arg)
{
    while (1)
    {
        // Lock the mutex before checking/modifying shared resources
        pthread_mutex_lock(&mutex);

        // Barber sleeps if there are no customers
        while (waitingCustomers == 0)
        {
            printf("The barber is sleeping.\n");
            pthread_cond_wait(&customerAvailable, &mutex); // Wait for a customer
        }

        // Barber is cutting hair
        printf("The barber is cutting hair.\n");
        sleep(3); // Simulate time taken to cut hair
        printf("The barber has finished cutting hair.\n");

        waitingCustomers--; // Decrease the count of waiting customers

        // Signal a waiting customer (if any) that the barber is available
        pthread_cond_signal(&barberAvailable);

        // Unlock the mutex after the barber is done cutting hair
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* customer(void* arg)
{
    int id = *(int*)arg; // Customer ID

    // Lock the mutex before checking/modifying shared resources
    pthread_mutex_lock(&mutex);

    // Check if there are available chairs
    if (waitingCustomers < CHAIRS)
    {
        waitingCustomers++;
        printf("Customer %d is waiting. Customers waiting: %d\n", id, waitingCustomers);

        // Signal the barber that a customer is available
        pthread_cond_signal(&customerAvailable);

        // Wait for the barber to be available if all chairs are taken
        pthread_cond_wait(&barberAvailable, &mutex);
    }
    else
    {
        // No chairs available, the customer leaves
        printf("No chairs available. Customer %d is leaving.\n", id);
    }

    // Unlock the mutex after the customer either takes a seat or leaves
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t barberThread;
    pthread_t customerThreads[10]; // 10 customers
    int customerIds[10];

    // Create the barber thread
    pthread_create(&barberThread, NULL, barber, NULL);

    // Simulate customers arriving over time
    for (int i = 0; i < 10; i++)
    {
        customerIds[i] = i + 1; // Assign customer ID
        sleep(1); // New customer arrives every second
        pthread_create(&customerThreads[i], NULL, customer, &customerIds[i]);
    }

    // Wait for all customer threads to finish
    for (int i = 0; i < 10; i++)
    {
        pthread_join(customerThreads[i], NULL);
    }

    // Wait for the barber thread (which runs infinitely)
    pthread_join(barberThread, NULL);

    // Cleanup
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&customerAvailable);
    pthread_cond_destroy(&barberAvailable);

    return 0;
}


