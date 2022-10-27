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

int main(int argc, char **argv)
{
    my_daemon();
    int pfd[2]; //无名管道
    int pid;
    char buf[100];

    int ret_pipe = pipe(pfd); //创建无名管道 pfd[0]读 pfd[1]写
    if (ret_pipe < 0)
    {
        cout << "pipe失败" << endl;
        exit(-1);
    }

    pid = fork();

    if (pid < 0)
    {
        cout << "fork子进程失败" << endl;
        exit(-1);
    }
    else if (pid == 0) //子进程 继承无名管道的文件描述符
    {
        strcpy(buf, "1953072 肖鹏飞 child to father");
        write(pfd[1], buf, 100); //通过无名管道的写端进行写数据
        //exit(0);
    }
    else
    {
        read(pfd[0], buf, 100); //通过无名管道的读端进行读数据
        cout << "father read: " << buf << endl;
        //exit(0);
    }

    return 0;
}