#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUMBER       40

sem_t semap_x;

void* WorkerThread(void* arg)
{
    printf("Thread Entry Point TN=%d\n",*(int*)arg);

    sem_wait(&semap_x);
    sleep(1);
    printf("for thread %d\n",*(int*)arg);
    sleep(4);
    sem_post(&semap_x);
    free(arg);

    printf("*****************************************\n");

    return NULL;
}

int main()
{

    pthread_t tid[THREAD_NUMBER];

    if(sem_init(&semap_x,0,20));

    for (size_t i = 0; i < THREAD_NUMBER; i++)
    {
        int *ptr = (int*)malloc(sizeof(int));
        *ptr = i;
        if(pthread_create(&tid[i],NULL,WorkerThread,ptr) != 0)
        {
            printf("Task Create Error = %lu\n",i);
        }
    }
    
    for (size_t i = 0; i < THREAD_NUMBER; i++)
    {
        pthread_join(tid[i],NULL);
    }
    sem_destroy(&semap_x);

    return 0;
}