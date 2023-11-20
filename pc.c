#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_SIZE 5

int buffer[BUF_SIZE];
int in = 0, out = 0;
int item_to_produce = 1;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    while (1) {
        sleep(1);

        printf("\nEnter item to produce: ");
        scanf("%d", &item_to_produce);

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item_to_produce;

        printf("\nProduced item %d at position %d by Thread ID %lu", item_to_produce, in, pthread_self());
        in = (in + 1) % BUF_SIZE;

        pthread_mutex_unlock(&mutex);

        sem_post(&full);
        item_to_produce++;
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int consumed_item = buffer[out];
        printf("\nConsumed item %d at position %d by Thread ID %lu.", consumed_item, out, pthread_self());
        out = (out + 1) % BUF_SIZE;

        pthread_mutex_unlock(&mutex);

        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t consumer_thread, producer_thread;
    sem_init(&empty, 0, BUF_SIZE);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_create(&producer_thread, NULL, producer, NULL);

    pthread_join(consumer_thread, NULL);
    pthread_join(producer_thread, NULL);

    return 0;
}

