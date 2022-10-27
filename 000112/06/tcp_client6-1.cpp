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
    para_need pn;
    pn.para_num=3;
    pn.para[0].para_name="port";
    pn.para[0].para_type="int";
    pn.para[1].para_name="ip";
    pn.para[1].para_type="string";
    pn.para[2].para_name="myport";
    pn.para[2].para_type="int";
    pn.para[2].para_whe_have_default=0;//
    pn.para[2].para_value_default=0;//

    int ret=parameter_process(argc,argv,pn);
    if(ret<0)
    return 0;
    int port=pn.para[0].para_value;
    string ip=pn.para[1].para_string;
    int myport=pn.para[2].para_value;
    if(port<0||port>65535){
        cout<<"port范围有误"<<endl;
        exit(1);
    }
    if(myport<0||myport>65535){
        cout<<"myport范围有误"<<endl;
        exit(1);
    }

    /*开始进行tcp阻塞方式client端的编写*/
    int client_socket; //客户端套接字
    int n;
    char buff[BUF_SIZE];              //数据传输缓冲区
    struct sockaddr_in remote_addr; //服务器端网络地址

    /*client端初始化*/
    init_client(port,ip,myport,client_socket,buff,remote_addr);

    memset(buff, 0, sizeof(buff));
    strcat(buff, "aaaaabbbbbcccccddddd");
    // send to server

    int sumn=0;
    while(1)
    {
        n = write(client_socket, buff, PAC_SIZE);
        sumn+=n;
        if (n < 0)
        {
            printf("write error: %s(errno:%d)\n", strerror(errno), errno);
            break;
        }
        else
        {
            cout << "总共write的字节数: " << sumn << endl;
        }
        sleep(1);
    }



    close(client_socket);

    return 0;
}