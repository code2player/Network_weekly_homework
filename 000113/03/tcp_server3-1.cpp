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
#include "../../include/socket_common.h"
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

    /*ip在网卡位置判断*/
    int legal = get_local_ip(pn.para[1].para_string);
    if (legal == 0)
    {
        cout << "ip不在本机网卡范围内" << endl;
        exit(1);
    }

    /*开始进行tcp非阻塞方式server端的编写*/
    Socket_Accept Socket_Server;
    Socket_Server.fill_ip_port(pn.para[0].para_value, pn.para[1].para_string);
    Socket_Server.create_server_socket();
    Socket_Server.server_socket_NONBLOCK(1); // create后设置server_socket为非阻塞方式
    Socket_Server.bind_server_socket();
    Socket_Server.listen_server_socket();

    fd_set readset;                                //文件集合
    FD_ZERO(&readset);                             // set初始化为空
    FD_SET(Socket_Server.server_socket, &readset); //向set中添加server端socket

    int rets;
    rets = select(FD_SETSIZE, &readset, 0, 0, NULL);
    cout << "select return: " << rets << endl;
    printf("select error: %s(errno:%d)\n", strerror(errno), errno);
    if (rets <= 0)
    {
        exit(-1);
    }
    /*找到相关文件描述符*/
    if (FD_ISSET(Socket_Server.server_socket, &readset))
    {
        //等待客户端连接请求到达
        // 4.accept
        Socket_Server.accept_server_socket();
        // accept后设置client_socket为非阻塞方式
        Socket_Server.client_socket_NONBLOCK(1);
        FD_SET(Socket_Server.client_socket, &readset); //将客户端socket加入到集合中
    }

    fd_set testset;

    while (1)
    {
        testset = readset;

        rets = select(FD_SETSIZE, &testset, 0, 0, NULL);
        cout << "select return: " << rets << endl;
        printf("select error: %s(errno:%d)\n", strerror(errno), errno);
        if (rets <= 0)
        {
            //printf("select error: %s(errno:%d)\n", strerror(errno), errno);
            exit(-1);
        }
        if (FD_ISSET(Socket_Server.client_socket, &testset))
        {
            /*进入read状态*/
            int n;
            n = read(Socket_Server.client_socket, Socket_Server.buff, 100);
            printf("read error: %s(errno:%d)\n", strerror(errno), errno);
            cout << "read" << n << "个字节" << endl;
            if (n <= 0)
            {
                break;
            }       
        }
    }
    //关闭套接字
    close(Socket_Server.client_socket);
    close(Socket_Server.server_socket);

    return 0;
}