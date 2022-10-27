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
#include "../../include/mydaemon.h"
#include "../../include/parameter_process.h"
using namespace std;

int main(int argc, char **argv)
{
    my_daemon();

    int shmid; // 共享内存标识符，在父进程和子进程之间共享

    // 创建共享内存，键值为0x5005，共1024字节。
    if ((shmid = shmget((key_t)0x5005, 1024, 0666 | IPC_CREAT)) == -1)
    {
        printf("shmat(0x5005) failed\n");
        return -1;
    }

    const char *ch1 = "1953072 肖鹏飞 5-2-1 to 5-2-2";
    char *ptext = 0; // 用于指向共享内存的指针
    // 将共享内存连接到当前进程的地址空间，由ptext指针指向它
    ptext = (char *)shmat(shmid, 0, 0);

    // write
    sprintf(ptext, ch1);
    // read
    while (ptext[100] != '1')
    {
        sleep(1);
    }
    printf("5-2-1 read: %s\n", ptext + 100);

    // 把共享内存从当前进程中分离
    shmdt(ptext);
    sleep(3);
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        printf("shmctl(0x5005) failed\n");
        return -1;
    }

    return 0;
}