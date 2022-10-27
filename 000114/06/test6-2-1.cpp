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
    /*开始进行unix套接字阻塞方式server端的编写*/

    int server_socket;              //服务端套接字
    int client_socket;              //客户端套接字
    struct sockaddr_un servaddr;    //服务器网络地址
    struct sockaddr_un remote_addr; ///客户端地址
    char send_buf[BUFSIZ];          //数据传送缓冲区
    char recv_buf[BUFSIZ];          //数据传送缓冲区
    socklen_t addr_size;            //结构体长度，accept函数中该参数类型为socklen_t *

    memset(&servaddr, 0, sizeof(servaddr)); //结构体初始化清零
    servaddr.sun_family = AF_UNIX;          // unix
    strcpy(servaddr.sun_path, "test6-2.socket");

    addr_size = sizeof(struct sockaddr_in);

    //创建服务端套接字
    // 1. create socket
    if ((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        printf("创建socket失败, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    //使用SO_REUSEADDR来对端口进行立即重新使用
    int optval = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    //绑定套接字到ip和端口
    // 2.bind socket & port to server
    int exist_soc = access("test6-2.socket", 0);
    if (exist_soc == 0) //存在则删除
    {
        unlink("test6-2.socket");
    }
    if (bind(server_socket, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("bind绑定socket失败, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    printf("bind绑定socket成功......\n");

    //监听连接请求，监听队列长度为10
    // 3.listen
    if (listen(server_socket, 10) < 0)
    {
        printf("监听请求无效, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    printf("进入等待连接状态......\n");

    //等待客户端连接请求到达
    // 4.accept
    if ((client_socket = accept(server_socket, (struct sockaddr *)&remote_addr, &addr_size)) < 0)
    {
        printf("建立连接失败, %s(errno: %d)", strerror(errno), errno);
        // continue;
    }
    //非阻塞
    int flags = fcntl(client_socket, F_GETFL, 0);
    fcntl(client_socket, F_SETFL, flags | O_NONBLOCK);

    cout << "与6-2-2 client端建立连接" << endl;

    strcpy(send_buf, "1953072 肖鹏飞 6-2-1 to 6-2-2");

    fd_set readset, writeset;
    FD_ZERO(&readset);
    FD_ZERO(&writeset);
    FD_SET(client_socket, &readset);  //将客户端socket加入到集合中
    FD_SET(client_socket, &writeset); //将客户端socket加入到集合中

    int rets = select(FD_SETSIZE, 0, &writeset, 0, NULL);
    if (rets < 0)
    {
        printf("select error: %s(errno:%d)\n", strerror(errno), errno);
    }
    if (write(client_socket, send_buf, BUFSIZ) < 0)
    {
        printf("write error, %s(errno: %d)\n", strerror(errno), errno);
        exit(-1);
    }

    rets = select(FD_SETSIZE, &readset, 0, 0, NULL);
    if (rets < 0)
    {
        printf("select error: %s(errno:%d)\n", strerror(errno), errno);
    }
    if (read(client_socket, recv_buf, BUFSIZ) < 0)
    {
        printf("read error, %s(errno: %d)\n", strerror(errno), errno);
        exit(-1);
    }

    cout << "6-2-1 recv: " << recv_buf << endl;
    //关闭套接字
    close(client_socket);
    close(server_socket);

    return 0;
}