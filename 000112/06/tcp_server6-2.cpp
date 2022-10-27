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
    para_need pn;
    pn.para_num = 2;

    pn.para[0].para_name = "port";
    pn.para[0].para_type = "int";
    pn.para[0].para_whe_have_range = 1;
    pn.para[0].min_range = 0;
    pn.para[0].max_range = 65535;

    pn.para[1].para_name = "ip";
    pn.para[1].para_type = "string";
    pn.para[1].para_whe_have_default = 0;
    pn.para[1].para_string_default = "0.0.0.0";

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;
    int port = pn.para[0].para_value;
    string ip = pn.para[1].para_string;

    /*if(port<0||port>65535){
        cout<<"port范围有误"<<endl;
        exit(1);
    }*/

    int legal = get_local_ip(ip);
    if (legal == 0)
    {
        cout << "ip不在本机网卡范围内" << endl;
        exit(1);
    }

    /*开始进行tcp阻塞方式server端的编写*/

    int server_socket;              //服务端套接字
    int client_socket;              //客户端套接字
    struct sockaddr_in servaddr;    //服务器网络地址
    struct sockaddr_in remote_addr; ///客户端地址
    char buff[BUF_SIZE];              //数据传送缓冲区
    int n;
    socklen_t addr_size; //结构体长度，accept函数中该参数类型为socklen_t *
    addr_size = sizeof(struct sockaddr_in);

    //server端初始化
    init_server(port,ip,server_socket,client_socket,servaddr,remote_addr,buff,addr_size);
    cout<<"与client端连接成功, 进入阻塞状态, 按回车继续......"<<endl;
    getchar();//在read前暂停

    // recv:等待另一端传来的数据（默认阻塞）
    //没有所谓的对等，s/c端互相通信时（recv/send），参数均设为c端

    int sumn = 0;

    while (1)
    {
        if ((n = recv(client_socket, buff, PAC_SIZE,0)) > 0)
        {
            sumn += n;
            cout << "读到的字节数: " << sumn << endl;
        }
        else
        {
            printf("client端主动断开连接, 错误码为%d\n", n);
            break;
        }
        sleep(1);
    }
    //关闭套接字
    close(client_socket);
    close(server_socket);

    return 0;
}