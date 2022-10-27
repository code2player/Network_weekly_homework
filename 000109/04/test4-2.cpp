#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/prctl.h>
#include "../../include/mydaemon.h"

int main()
{
    my_daemon();
    /*char *buf = "1953072 肖鹏飞\n";
    int fd;
    while(1){

        if ((fd = open("mydaemon.txt", O_CREAT|O_WRONLY|O_APPEND, 0600)) < 0)
        {
            printf("Open file error\n");
            exit(1);
        }

        write(fd, buf, strlen(buf) + 1);
        sleep(5);
    close(fd);

    }*/

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
            prctl(PR_SET_PDEATHSIG, SIGKILL);//子进程中声明
            while(1)
            {
                pid=getpid();
                ppid = getppid();
                printf("%d %d 1953072 sub\n", ppid, pid);
                fflush(stdout);
                sleep(25);
            }
            
        }
    }

    while(1){
        int pid=getpid();
        int ppid=getppid();
        printf("%d %d 1953072 main\n",ppid,pid);
        fflush(stdout);
        sleep(5);
    }
    
    return 0;
}