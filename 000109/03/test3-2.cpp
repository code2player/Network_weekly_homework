#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include "../../include/mydaemon.h"

int main()
{
    my_daemon();

    for (int i = 0; i < 10; i++)
    {
        int ppid;
        int pid = fork();
        if (pid > 0)
        {
            sleep(3);
        }
        else if (pid < 0)
            exit(1);
        else
        {
            for (int j = 0; j < 3; j++)
            {
                pid=getpid();
                ppid = getppid();
                printf("%d %d 1953072 sub\n", ppid, pid);
                fflush(stdout);
                sleep(25);
            }
            exit(0);
        }
    }

    
    int times=0;
    while(1){
        int pid=getpid();
        int ppid=getppid();
        printf("%d %d 1953072 main\n",ppid,pid);
        fflush(stdout);
        sleep(5);
        if (times == -1)
        {
            continue;
        }
        else if (times == 25)
        {
            for (int i = 0; i < 10; i++)
            {
                int status;
                wait(&status);
            }
            times = -1;
        }
        else
        {
            times++;
        }
    }
    
    return 0;
}