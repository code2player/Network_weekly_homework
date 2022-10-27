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
#include <sys/msg.h>
#include <sys/ipc.h>
#include "../../include/mydaemon.h"
#include "../../include/parameter_process.h"
using namespace std;

struct mymesg
{
    long int mtype;
    char mtext[512];
};

int main(int argc, char **argv)
{
    my_daemon();

    int pid = fork();
    if (pid < 0)
    {
        cout << "fork�ӽ���ʧ��" << endl;
        exit(-1);
    }
    else if (pid == 0) //�ӽ���
    {
        int id;
        struct mymesg ckxmsg;
        key_t key = ftok("test", 66);
        id = msgget(key, IPC_CREAT | 0666);
        if (id == -1)
        {
            printf("create msg error \n");
            return 0;
        }
        if (msgrcv(id, (void *)&ckxmsg, 512, 1, 0) < 0) //���һ������Ϊ0������
        {
            printf("receive msg error \n");
            return 0;
        }
        printf("child recv: %s\n", ckxmsg.mtext);
    }
    else // father
    {
        int id;
        struct mymesg ckxmsg;
        key_t key = ftok("test", 66);
        id = msgget(key, IPC_CREAT | 0666);
        if (id == -1)
        {
            printf("create msg error \n");
            return 0;
        }
        ckxmsg.mtype = 1;
        strcpy(ckxmsg.mtext, "1953072 Ф���� father to child");

        if (msgsnd(id, (void *)&ckxmsg, 512, 0) < 0) //���һ������Ϊ0������
        {
            printf("send msg error \n");
            return 0;
        }
    }

    return 0;
}