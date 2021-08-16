#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


pthread_t tid1 , tid2;
pthread_mutex_t  g_mutex1 = PTHREAD_MUTEX_INITIALIZER
            ,    g_mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *ret1;
void *ret2; 


void* thread1(void *x)
{   
    //deadlock
    /*
    pthread_mutex_lock(&g_mutex1);
    sleep(1);
    pthread_mutex_lock(&g_mutex2);
    for (size_t i = 0; i < 5; i++)
    {
        printf("Thread 1\n");
    }
    pthread_mutex_unlock(&g_mutex1);
    pthread_mutex_unlock(&g_mutex2);*/

    //cozum
    pthread_mutex_lock(&g_mutex1);
    sleep(1);
    pthread_mutex_lock(&g_mutex2);
    for (size_t i = 0; i < 5; i++)
    {
        printf("Thread 1\n");
    }
    pthread_mutex_unlock(&g_mutex1);
    pthread_mutex_unlock(&g_mutex2);

    return (void*)100;
}
void* thread2(void *x)
{
    //deadlock
    /*
    pthread_mutex_lock(&g_mutex2);
    pthread_mutex_lock(&g_mutex1);
    for (size_t i = 0; i < 5; i++)
    {
        printf("Thread 2\n");
    }
    pthread_mutex_unlock(&g_mutex2);
    pthread_mutex_unlock(&g_mutex1);*/

    //cozum
    pthread_mutex_lock(&g_mutex1);
    pthread_mutex_lock(&g_mutex2);
    for (size_t i = 0; i < 5; i++)
    {
        printf("Thread 2\n");
    }
    pthread_mutex_unlock(&g_mutex1);
    pthread_mutex_unlock(&g_mutex2);


    return (void*)150;
}

int main()
{

    if(pthread_create(&tid1,NULL,thread1,NULL) != 0)
    {
        printf("Create Error\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&tid2,NULL,thread2,NULL) != 0)
    {
        printf("Create Error\n");
        exit(EXIT_FAILURE);
    }

    
    pthread_join(tid1,&ret1);
    pthread_join(tid2,&ret2);

    if(ret1 == (void*)100) printf("Thread1 Succes\n");
    if(ret2 == (void*)150) printf("Thread2 Succes\n");


    return 0;
    
}