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
    // 1�����ж��ļ��Ƿ����
    int ret = access(fifo_path, F_OK);
    if (ret == -1)
    {
        // 2�������ܵ��ļ�
        ret = mkfifo(fifo_path, 0777);
        if (ret == -1)
        {
            cout << "mkfifoʧ��" << endl;
            exit(0);
        }
    }

    char buf[100];
    int buf_len = 100;
    int pid = fork();
    int fd;

    if (pid < 0)
    {
        cout << "fork�ӽ���ʧ��" << endl;
        exit(-1);
    }
    else if (pid == 0) //�ӽ��� �̳������ܵ����ļ�������
    {
        // 3���򿪹ܵ�����ֻд�ķ�ʽ
        fd = open(fifo_path, O_RDONLY);
        if (fd == -1)
        {
            cout << "openFIFOʧ��" << endl;
            exit(0);
        }
        read(fd, buf, buf_len);
        cout << "child read: " << buf << endl;
    }
    else
    {
        // 3���򿪹ܵ�����ֻд�ķ�ʽ
        fd = open(fifo_path, O_WRONLY);
        if (fd == -1)
        {
            cout << "openFIFOʧ��" << endl;
            exit(0);
        }
        strcpy(buf, "1953072 Ф���� father to child");
        write(fd, buf, buf_len);
    }

    close(fd);

    return 0;
}