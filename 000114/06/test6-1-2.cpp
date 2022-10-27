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

int main(int argc, char **argv)
{
    my_daemon();
    /*开始进行tcp阻塞方式client端的编写*/
    int client_socket;              //客户端套接字
    char send_buf[BUFSIZ];          //数据传输缓冲区
    char recv_buf[BUFSIZ];          //数据传输缓冲区
    struct sockaddr_un remote_addr; //服务器端网络地址

    memset(&remote_addr, 0, sizeof(remote_addr));
    remote_addr.sun_family = AF_UNIX;
    strcpy(remote_addr.sun_path, "test6-1.socket");

    //创建客户端套接字
    if ((client_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        printf("创建socket失败, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    //连接服务器
    int len=offsetof(struct sockaddr_un,sun_path)+strlen(remote_addr.sun_path);
    if (connect(client_socket, (struct sockaddr *)&remote_addr, len) < 0)
    {
        printf("连接server端失败, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    printf("已连接到server端\n");

    strcpy(send_buf, "1953072 肖鹏飞 6-1-2 to 6-1-1");

    int n;
    n = write(client_socket, send_buf, BUFSIZ);
    //cout << "n: " << n << endl;
    if (n < 0)
    {
        printf("write error, %s(errno: %d)\n", strerror(errno), errno);
        exit(-1);
    }

    if (read(client_socket, recv_buf, BUFSIZ) < 0)
    {
        printf("read error, %s(errno: %d)\n", strerror(errno), errno);
        exit(-1);
    }

    cout << "6-1-2 recv: " << recv_buf << endl;
    //关闭套接字
    close(client_socket);

    return 0;
}