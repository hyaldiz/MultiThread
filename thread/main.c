#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* WorkerThread1(void *x)
{
    const char* str = (const char*)x;
    /*workerthread1*/
    for (size_t i = 0; i < 10; i++)
    {
        /* code */
        printf("%s\n",str);
        sleep(1);
    }
}

void* WorkerThread2(void *x)
{
    int* value = (int*)x;

    /*workerthread1*/
    for (size_t i = 0; i < 10; i++)
    {
        /* code */
        printf("Worker Thread val=%d %ld\n",*value,i);
        sleep(1);
    }
}

int main()
{
    /*main thread*/
    pthread_t tid1 , tid2;
    int res;

    res = pthread_create(&tid1,NULL,WorkerThread1,"Selam Ben Worker Thread 2");

    if(res)
    {
        fprintf(stderr,"pthread create error");
        exit(EXIT_FAILURE);
    }

    int val = 30; 

    res = pthread_create(&tid2,NULL,WorkerThread2,&val);

    if(res)
    {
        fprintf(stderr,"pthread create error");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < 10; i++)
    {
        /* code */
        printf("Main Thread %ld\n",i);
        sleep(1);
    }

    
    return 0;
}

/*
Threadlerin stacleri birbirinden ayrılmıştır.
*/