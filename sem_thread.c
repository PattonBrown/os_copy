#include "head.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int flag = 0, i = 0;

void filecopy()
{
    if (i < fpos && fpos - i >= sizeof(buffer))
    {
        read(fdr, buffer, sizeof(buffer));
        write(fdw, buffer, sizeof(buffer));
        i = i + sizeof(buffer);
    }

    least = fpos % sizeof(buffer);
    if (least < sizeof(buffer)&&fpos - i < sizeof(buffer) && flag == 0)
    {
        char buffer2[least];
        read(fdr, buffer2, least);
        write(fdw, buffer2, least);
        i = i + least;
        flag = 1;
    }
}

void pthread1(void *arg)
{
    while (i < fpos)
    {
        sem_wait(&sem1);
        printf("This is thread1\n");
        filecopy();
        sem_post(&sem2);
    }
}
void pthread2(void *arg)
{

    while (i < fpos)
    {
        sem_wait(&sem2);
        printf("This is thread2\n");
        filecopy();
        sem_post(&sem1);
    }
}
void threadCreate()
{
    int ret;
    pthread_t id1, id2;

    ret = sem_init(&sem1, 0, 1);

    if (ret != 0)
    {
        perror("sem_init");
    }

    ret = sem_init(&sem2, 0, 0);
    if (ret != 0)
    {
        perror("sem_init");
    }

    ret = pthread_create(&id1, NULL, (void *)pthread1, NULL);
    if (ret != 0)
        perror("pthread cread1");
    ret = pthread_create(&id2, NULL, (void *)pthread2, NULL);
    if (ret != 0)
        perror("pthread cread2");

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    // int n,NUM;
    // printf("How many ")    
	// pthread_t tid[NUM]; 

    printf("compltete\n");
}
