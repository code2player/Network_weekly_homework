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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/un.h>
#include <stddef.h>
#include "../../include/mydaemon.h"
#include "../../include/parameter_process.h"
using namespace std;

int set_lock(int fd, int type)
{
    struct flock lock;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_type = F_WRLCK;
    lock.l_pid = 2;

    int ret = fcntl(fd, F_GETLK, &lock);
    if (ret < 0)
    {
        printf("get lock error, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    if (lock.l_type != F_UNLCK)
    {
        cout << "lock has been set" << endl;
        // return -1;
    }

    lock.l_type = type;
    if ((fcntl(fd, F_SETLKW, &lock)) < 0)
    {
        printf("set lock error, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    return 1;
}

int main(int argc, char **argv)
{
    my_daemon();

    para_need pn;
    pn.para_num = 1;
    pn.set_name_type(0, "file", "string");

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;
    const char *file_path = pn.para[0].para_string.c_str();

    int fd; /* 首先打开文件*/
    fd = open(file_path, O_RDWR | O_CREAT, 0777);
    if (fd < 0)
    {
        printf("Open file error\n");
        exit(1);
    }

    char buf[50];
    strcpy(buf, "1953072 肖鹏飞 7-1-1 to 7-1-2");
    ret = set_lock(fd, F_WRLCK);
    write(fd, buf, 50);
    ret = set_lock(fd, F_UNLCK);

    close(fd);
    return 0;
}