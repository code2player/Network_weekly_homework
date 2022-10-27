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
    const char *fifo_path1 = "test1";

    int ret = access(fifo_path, F_OK);
    if (ret == -1)
    {
        ret = mkfifo(fifo_path, 0777);
        if (ret == -1)
        {
            cout << "mkfifoÊ§°Ü" << endl;
            exit(0);
        }
    }

    ret = access(fifo_path1, F_OK);
    if (ret == -1)
    {
        ret = mkfifo(fifo_path1, 0777);
        if (ret == -1)
        {
            cout << "mkfifo1Ê§°Ü" << endl;
            exit(0);
        }
    }

    char buf[100];
    char buf1[100];
    int buf_len = 100;
    int pid = fork();
    int fd;
    int fd1;

    if (pid < 0) // error
    {
        cout << "fork×Ó½ø³ÌÊ§°Ü" << endl;
        exit(-1);
    }
    else if (pid == 0) // son
    {
        // write
        fd = open(fifo_path, O_WRONLY);
        if (fd == -1)
        {
            cout << "openFIFOÊ§°Ü" << endl;
            exit(0);
        }
        fd1 = open(fifo_path1, O_RDONLY);
        if (fd1 == -1)
        {
            cout << "openFIFOÊ§°Ü" << endl;
            exit(0);
        }

        strcpy(buf, "1953072 Ð¤Åô·É child to father");
        write(fd, buf, buf_len);
        read(fd1, buf1, buf_len);
        cout << "child read: " << buf1 << endl;
    }
    else // father
    {
        // read
        fd = open(fifo_path, O_RDONLY);
        if (fd == -1)
        {
            cout << "openFIFOÊ§°Ü" << endl;
            exit(0);
        }
        fd1 = open(fifo_path1, O_WRONLY);
        if (fd1 == -1)
        {
            cout << "openFIFOÊ§°Ü" << endl;
            exit(0);
        }

        strcpy(buf1, "1953072 Ð¤Åô·É father to child");
        write(fd1, buf1, buf_len);
        read(fd, buf, buf_len);
        cout << "father read: " << buf << endl;
    }

    close(fd);
    close(fd1);

    return 0;
}