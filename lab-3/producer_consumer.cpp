#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int itemCount = 0;

// Mutex and condition variables for synchronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notFull = PTHREAD_COND_INITIALIZER;
pthread_cond_t notEmpty = PTHREAD_COND_INITIALIZER;

void* produce(void* arg)
{
    int itemsToProduce = *(int*)arg;

    for (int i = 0; i < itemsToProduce; i++)
    {
        // Lock the mutex before accessing shared buffer
        pthread_mutex_lock(&mutex);

        // Wait if buffer is full
        while (itemCount == BUFFER_SIZE)
        {
            pthread_cond_wait(&notFull, &mutex);
        }

        // Produce an item
        buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        itemCount++;
        printf("Producer produced: %d\n", i);

        // Signal that buffer is not empty
        pthread_cond_signal(&notEmpty);

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Simulate production time
        usleep(100000); // 0.1 seconds
    }

    return NULL;
}

void* consume(void* arg)
{
    int itemsToConsume = *(int*)arg;

    for (int i = 0; i < itemsToConsume; i++)
    {
        // Lock the mutex before accessing shared buffer
        pthread_mutex_lock(&mutex);

        // Wait if buffer is empty
        while (itemCount == 0)
        {
            pthread_cond_wait(&notEmpty, &mutex);
        }

        // Consume an item
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        itemCount--;
        printf("Consumer consumed: %d\n", item);

        // Signal that buffer is not full
        pthread_cond_signal(&notFull);

        // Unlock the mutex
        pthread_mutex_unlock(&mutex);

        // Simulate consumption time
        usleep(150000); // 0.15 seconds
    }

    return NULL;
}

int main()
{
    pthread_t producerThread, consumerThread;
    int itemsToProduce = 10;

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, produce, &itemsToProduce);
    pthread_create(&consumerThread, NULL, consume, &itemsToProduce);

    // Wait for threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Cleanup
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&notFull);
    pthread_cond_destroy(&notEmpty);

    return 0;
}


