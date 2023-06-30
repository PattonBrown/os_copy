#include "head.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int flag = 0, i = 0;
sem_t sem_mutex;

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


void *pthread(void *arg)          //线程  
{  
	int k = (int)arg;
    while (i < fpos)
    {
        sem_wait(&sem_mutex);
        printf("i am pthread %d\n",k);
        filecopy();
        sem_post(&sem_mutex);
    }


}  
void threadCreate()
{
    int n,NUM;
    printf("How many duplicators(threads) do you want to create?\n");
    scanf("%d",&NUM);    
	pthread_t tid[NUM]; //创建NUM个线程

    sem_init(&sem_mutex,0,1);

    for(i=0;i<NUM;i++)      
    		pthread_create(&tid[i],NULL,pthread, (void *)i);  
   
	for(i=0;i<NUM;i++)   
    		pthread_join(tid[i],NULL);  

    printf("compltete\n");
}
