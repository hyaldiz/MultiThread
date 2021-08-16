#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


pthread_t tid1 , tid2 , tid3;
pthread_mutex_t  g_mutex;

void *ret1;
void *ret2; 
void *ret3;


void* thread1(void *x)
{
    pthread_mutex_lock(&g_mutex);
    for(int i=0;i<100000000;i++)
    {
        printf("T1\n");
        usleep(1);
        pthread_mutex_unlock(&g_mutex);
    }
    

    return (void*)100;
}
void* thread2(void *x)
{
    pthread_mutex_lock(&g_mutex);
    for(int i=0;i<10000000000;i++)
    {
        printf("T2\n");
        usleep(1);
        pthread_mutex_unlock(&g_mutex);
    }
    

    return (void*)150;
}
void* thread3(void *x)
{
    pthread_mutex_lock(&g_mutex);
    for(int i=0;i<1000000000;i++)
    {
        printf("T3\n");
        usleep(1);
        pthread_mutex_unlock(&g_mutex);
    }
    

    return (void*)200;
}

int main()
{
    pthread_mutex_init(&g_mutex,NULL);

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
    if(pthread_create(&tid3,NULL,thread3,NULL) != 0)
    {
        printf("Create Error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        ;
    }
    
    pthread_join(tid1,&ret1);
    pthread_join(tid2,&ret2);
    pthread_join(tid3,&ret3);

    if(ret1 == (void*)100) printf("Thread1 Succes\n");
    if(ret2 == (void*)150) printf("Thread2 Succes\n");
    if(ret3 == (void*)200) printf("Thread3 Succes\n");


    return 0;
    
}