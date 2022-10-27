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
    int pfd[2]; //�����ܵ�
    int pid;
    char buf[100];

    int ret_pipe = pipe(pfd); //���������ܵ� pfd[0]�� pfd[1]д
    if (ret_pipe < 0)
    {
        cout << "pipeʧ��" << endl;
        exit(-1);
    }

    pid = fork();

    if (pid < 0)
    {
        cout << "fork�ӽ���ʧ��" << endl;
        exit(-1);
    }
    else if (pid == 0) //�ӽ��� �̳������ܵ����ļ�������
    {
        strcpy(buf, "1953072 Ф���� child to father");
        write(pfd[1], buf, 100); //ͨ�������ܵ���д�˽���д����
        //exit(0);
    }
    else
    {
        read(pfd[0], buf, 100); //ͨ�������ܵ��Ķ��˽��ж�����
        cout << "father read: " << buf << endl;
        //exit(0);
    }

    return 0;
}