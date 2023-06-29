#ifndef HEAD_H
#define HEAD_H

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <sys/ipc.h>
#include <semaphore.h>

sem_t sem1, sem2;                    // 声明两个信号量
int fdr, fdw;                        // 文件描述符
char buffer[1024*1024];                   // 缓冲区
int fpos, least;              // 文件位置、计数变量
struct timeval start_time, end_time; // 开始和结束时间

void pthread1(void *arg); // 线程1的入口函数声明
void pthread2(void *arg); // 线程2的入口函数声明
void threadCreate();      // 线程创建函数声明

#endif
