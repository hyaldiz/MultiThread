#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_SIZE     3

pthread_mutex_t fuelMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  fuelCond  = PTHREAD_COND_INITIALIZER;

u_int32_t fuel , price;

void* taskFuel(void *arg)
{
    printf("Task Fuel Thread\n");

    while (1)
    {
        pthread_mutex_lock(&fuelMutex);
        fuel += 15;
        printf("FUEL->fuel = %u\n",fuel);
        pthread_mutex_unlock(&fuelMutex);
        sleep(1);
        //pthread_cond_signal(&fuelCond); //tum threadlere sinyal gitmesini garanti en az 1 ve değişken sayıda broadcast hepsine sinyal atar.
        pthread_cond_broadcast(&fuelCond);
    }

    return NULL;
}

void* car(void *arg)
{
    printf("Car Thread\n");

    while (1)
    {
        pthread_mutex_lock(&fuelMutex);
        while (fuel < 40)
        {
            printf("No Fuel Waiting\n");
            pthread_cond_wait(&fuelCond,&fuelMutex);
        }
        pthread_mutex_unlock(&fuelMutex);
        fuel -=15;
        printf("CAR->fuel = %u\n",fuel);
    }

    return NULL;
}

void* showBill(void *arg)
{
    printf("Show Bill Thread\n");

    while (1)
    {
        pthread_mutex_lock(&fuelMutex);
        while (fuel < 40)
        {
            printf("No Bill Waiting\n");
            pthread_cond_wait(&fuelCond,&fuelMutex);
        }
        pthread_mutex_unlock(&fuelMutex);
        price = fuel*2;
        printf("Price--> %u\n",price);
    }

    return NULL;
}

int main()
{
    pthread_t tid[THREAD_SIZE];
    int res;

    for (size_t i = 0; i < THREAD_SIZE; i++)
    {
        if(i == 2)
        {
            res = pthread_create(&tid[0],NULL,taskFuel,NULL);
            if (res)
            {
                printf("Thread Create Error\n");
            }
            
        }
        else if (i == 1)
        {
            res = pthread_create(&tid[2],NULL,showBill,NULL);
            if (res)
            {
                printf("Thread Create Error\n");
            }
        }
        else
        {   
            res = pthread_create(&tid[1],NULL,car,NULL);
            if (res)
            {
                printf("Thread Create Error\n");
            }

        }
    }

    for (size_t i = 0; i < THREAD_SIZE; i++)
    {
        pthread_join(tid[i],NULL);  //NULL because i dont care return value
    }

    pthread_mutex_destroy(&fuelMutex);
    pthread_cond_destroy(&fuelCond);

    return 0;
}