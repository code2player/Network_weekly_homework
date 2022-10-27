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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include "../../include/mydaemon.h"
#include "../../include/parameter_process.h"
using namespace std;

#define MY_SIGN_CONTINUE 47
#define MY_SIGN_EXIT 53

void handler47(int sig)
{
    if (MY_SIGN_CONTINUE == sig)
    {
        cout << "child已收到信号47" << endl;
    }
    return;
}

void handler53(int sig)
{
    if (MY_SIGN_EXIT == sig)
    {
        cout << "child已收到信号53" << endl;
        exit(1);
    }
    return;
}

void handlerfather(int sig)
{
    if (SIGCHLD == sig)
    {
        cout << "father已收到子进程退出信号" << endl;
        exit(1);
    }
    return;
}

int main(int argc, char **argv)
{
    my_daemon();
    signal(MY_SIGN_CONTINUE, handler47);
    signal(MY_SIGN_EXIT, handler53);
    signal(SIGCHLD, handlerfather);
    int pid = fork();

    if (pid < 0)
    {
        cout << "fork子进程失败" << endl;
        exit(-1);
    }
    else if (pid == 0) //子进程
    {
        while (1)
        {
            sleep(1);
        }
    }
    else
    {
        while (1)
        {
            kill(pid, MY_SIGN_CONTINUE); //父进程的pid为子进程序号
            sleep(1);
        }
    }

    return 0;
}