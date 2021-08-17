#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct dummy{
    int x;
    int y;
};


struct dummy str[2] = {
    [0] = {.x = 20 , .y = 10},
    [1] = {.x = 8 , .y = 16},
};

int main()
{


}