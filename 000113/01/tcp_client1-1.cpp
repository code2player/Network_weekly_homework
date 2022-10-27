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
#include "../../include/mydaemon.h"
#include "../../include/parameter_process.h"
#include "../../include/tcp_common.h"
using namespace std;

int main(int argc, char **argv)
{
    /*client端相关设置*/
    para_need pn;
    pn.para_num = 3;
    pn.set_name_type(0, "port", "int");
    pn.set_range(0, 1, 0, 65535);
    pn.set_name_type(1, "ip", "string");
    pn.set_name_type(2, "myport", "int");
    pn.set_default(2, 0, 0);
    pn.set_range(2, 1, 0, 65535);

    /*开始本题处理*/

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;
    int port = pn.para[0].para_value;
    string ip = pn.para[1].para_string;
    int myport = pn.para[2].para_value;

    /*开始进行tcp阻塞方式client端的编写*/
    int client_socket; //客户端套接字
   // int n;
    char buff[BUF_SIZE];            //数据传输缓冲区
    struct sockaddr_in remote_addr; //服务器端网络地址

    /*client端初始化*/
    int init_ret = init_client(port, ip, myport, client_socket, buff, remote_addr);
    if (init_ret == -1)
    {
        return 0;
    }

    while (1)
    {
        sleep(1);
    }

    close(client_socket);

    return 0;
}