#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unordered_map>
#include <fcntl.h>
#include "../../include/mydaemon.h"
#include "../../include/parameter_process.h"
using namespace std;

int sub(int size,int init)
{
    char *str = (char *)malloc(size * 1024 * sizeof(char));
    if(str!=NULL&&init==1){
        int i;
        for(i=0;i<size * 1024 * sizeof(char);i++){
            str[i]=rand()%256;
        }
    }

    for (;;)
    {
        sleep(1);
    }
}



int main(int argc, char **argv)
{
    my_daemon();
    srand(time(0));
    para_need pn;
    pn.para_num=4;
    pn.para[0].para_name="fnum";
    pn.para[0].para_type="int";
    pn.para[1].para_name="size";
    pn.para[1].para_type="int";
    pn.para[2].para_name="pnum";
    pn.para[2].para_type="int";
    pn.para[3].para_name="init";
    pn.para[3].para_type="bool";

    int ret=parameter_process(argc,argv,pn);
    if(ret<0)
    return 0;


    int fnum=pn.para[0].para_value;
    int size=pn.para[1].para_value;
    int pnum=pn.para[2].para_value;
    int init=pn.para[3].para_value;

    for (int i = 0; i < fnum; i++)
    {
        int pid = fork();
        if (pid > 0) //父进程继续
        {
            if (i % pnum == 0)
            {
                printf("已分裂%d个子进程\n", i);
            }
        }
        else if (pid < 0) //创建子进程失败
        {
            printf("分裂子进程失败\n");
            exit(1);
        }
        else //子进程
        {
            sub(size, init);
        }
    }

    while(1){
        ;
    }
    
    return 0;
}