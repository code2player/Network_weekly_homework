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
    pn.para_num = 6;

    pn.set_name_type(0, "port", "int");
    pn.set_range(0, 1, 0, 65535);

    pn.set_name_type(1, "ip", "string");
    pn.set_default(1, 0, 0, "0.0.0.0");

    /*读写测试相关设置*/
    pn.set_name_type(2, "readbyte", "int");
    pn.set_default(2, 0, 1024);
    pn.set_range(2, 1, 1, 65536);

    pn.set_name_type(3, "sendbyte", "int");
    pn.set_default(3, 0, 1024);
    pn.set_range(3, 1, 1, 65536);

    pn.set_name_type(4, "delay", "int");
    pn.set_default(4, 0, 0);
    pn.set_range(4, 1, 0, 5000000);

    pn.set_name_type(5, "debug", "int");
    pn.set_default(5, 0);
    pn.set_value(5, 0);

    /*开始本题处理*/

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;
    int port = pn.para[0].para_value;
    string ip = pn.para[1].para_string;
    int readbyte = pn.para[2].para_value;
    int sendbyte = pn.para[3].para_value;
    int delay = pn.para[4].para_value;
    int debug = pn.para[5].para_value;



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
    //cout<<"与client端连接成功......"<<endl;

    //getchar();//在read前暂停

    // recv:等待另一端传来的数据（默认阻塞）
    //没有所谓的对等，s/c端互相通信时（recv/send），参数均设为c端

    /*顺序：R W D*/
    int sumr = 0;
    int sumw = 0;
    while (1)
    {
        n = write(client_socket, buff, sendbyte);
        if (n < 0)
        {
            printf("write error: %s(errno:%d)\n", strerror(errno), errno);
            break;
        }
        sumw += n;
        
        n = read(client_socket, buff, readbyte);
        if (n < 0)
        {
            printf("read error: %s(errno:%d)\n", strerror(errno), errno);
            break;
        }
        sumr += n;

        if (debug == 1)
        {
            cout << "read byte  = " << sumr << endl;
            cout << "write byte = " << sumw << endl;
        }
        usleep(delay);
    }
    
    //关闭套接字
    close(client_socket);
    close(server_socket);

    return 0;
}