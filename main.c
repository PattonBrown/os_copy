#include"head.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    double time;

    if (argc != 3)
    {
        printf("Using : %s srcfilename decfilename\n", argv[0]);
        return -1;
    }

    gettimeofday(&start_time, NULL);
    fdr = open(argv[1], O_RDONLY);
    if (fdr < 0)
        exit(0);

    fdw = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fdw < 0)
        exit(0);

    fpos = lseek(fdr, 0, SEEK_END);
    lseek(fdr, 0, SEEK_SET);

    threadCreate();

    close(fdr);
    close(fdw);

    gettimeofday(&end_time, NULL);
    time = (end_time.tv_sec - start_time.tv_sec) * 1000000;
    time = time + (end_time.tv_usec - start_time.tv_usec);
    time = time / 1000000;
    printf("use time= %lf s done\n", time);

    return 0;
}
