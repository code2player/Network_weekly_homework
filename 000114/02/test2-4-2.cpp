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

    const char *fifo_path = "test";
    // 1、先判断文件是否存在
    int ret = access(fifo_path, F_OK);
    if (ret == -1)
    {
        // 2、创建管道文件
        ret = mkfifo(fifo_path, 0777);
        if (ret == -1)
        {
            cout << "mkfifo失败" << endl;
            exit(0);
        }
    }

    char buf[100];
    int buf_len = 100;
    int fd;

    fd = open(fifo_path, O_RDONLY);
    if (fd == -1)
    {
        cout << "openFIFO失败" << endl;
        exit(0);
    }
    read(fd, buf, buf_len);
    cout << "2-4-2 read: " << buf << endl;

    while (1)
    {
        sleep(10);
    }

    close(fd);
    return 0;
}