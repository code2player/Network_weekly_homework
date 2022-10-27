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
#include "../../include/tcp_common.h"
using namespace std;

int main(int argc, char **argv)
{
    /*server端相关设置*/
    para_need pn;
    pn.para_num = 2;

    pn.set_name_type(0, "port", "int");
    pn.set_range(0, 1, 0, 65535);

    pn.set_name_type(1, "ip", "string");
    pn.set_default(1, 0, 0, "0.0.0.0");

    /*开始本题处理*/

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;
    int port = pn.para[0].para_value;
    string ip = pn.para[1].para_string;

    /*ip在网卡位置判断*/
    int legal = get_local_ip(ip);
    if (legal == 0)
    {
        cout << "ip不在本机网卡范围内" << endl;
        exit(1);
    }

    /*开始进行tcp非阻塞方式server端的编写*/

    int server_socket;              //服务端套接字
    int client_socket;              //客户端套接字
    struct sockaddr_in servaddr;    //服务器网络地址
    struct sockaddr_in remote_addr; ///客户端地址
    char buff[BUF_SIZE];              //数据传送缓冲区
    int n;
    socklen_t addr_size; //结构体长度，accept函数中该参数类型为socklen_t *
    addr_size = sizeof(struct sockaddr_in);

    // server端初始化
    //最后一个noaccept参数置为1，不在init中accept
    int init_ret = init_server(port, ip, server_socket, client_socket, servaddr, remote_addr, buff, addr_size, 1);
    if (init_ret == -1)
    {
        return 0;
    }

    while (1)
    {
        //等待客户端连接请求到达
        // 4.accept
        if ((client_socket = accept(server_socket, (struct sockaddr *)&remote_addr, &addr_size)) < 0)
        {
            printf("建立连接失败, %s(errno: %d)", strerror(errno), errno);
            // continue;
        }

        cout << "与client端建立连接, ip:" << inet_ntoa(remote_addr.sin_addr) << " port:" << htons(remote_addr.sin_port) << endl;
        n = read(client_socket, buff, 20);
        if (n <= 0)
        {
            printf("read error: %s(errno:%d)\n", strerror(errno), errno);
            //break;
        }
        cout << "read" << n << "个字节" << endl;
    }

    //关闭套接字
    close(client_socket);
    close(server_socket);

    return 0;
}