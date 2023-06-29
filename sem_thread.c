#include"head.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int flag = 0, i = 0; 
void pthread1(void *arg)
{
    while (i < fpos)
    {
        sem_wait(&sem1);
        printf("This is thread1\n");
        if (i < fpos && fpos - i >= sizeof(buffer))
        {
            read(fdr, buffer, sizeof(buffer));
            write(fdw, buffer, sizeof(buffer));
            i = i + sizeof(buffer);
        }
        sem_post(&sem2);
        sem_wait(&sem1);

        least = fpos % sizeof(buffer);
        if (least<sizeof(buffer)&&flag==0)
        {
            char buffer2[least];
            read(fdr, buffer2, least);
            write(fdw, buffer2, least);
            i = i + least;
            flag=1;
        }

        sem_post(&sem2);
    }
}
void pthread2(void *arg)
{

    while (i < fpos)
    {
        sem_wait(&sem2);
        printf("This is thread2\n");
        if (i < fpos && fpos - i >= sizeof(buffer))
        {
            
            read(fdr, buffer, sizeof(buffer));
            write(fdw, buffer, sizeof(buffer));
            i = i + sizeof(buffer);
        }
        sem_post(&sem1);
        sem_wait(&sem2);
        least = fpos % sizeof(buffer);
        if (least<sizeof(buffer)&&flag==0)
        {
            char buffer2[least];
            read(fdr, buffer2, least);
            write(fdw, buffer2, least);
            i = i + least;
            flag=1;
        }

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

    printf("compltete\n");
}
