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
    char buff[BUFSIZ];              //数据传输缓冲区
    struct sockaddr_in remote_addr; //服务器端网络地址

    memset(&remote_addr, 0, sizeof(remote_addr));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(port);
    remote_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    //创建客户端套接字
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("创建socket失败, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    /*cout<<"port: "<<port<<endl;
    cout<<"ip: "<<ip<<endl;
    cout<<"myport: "<<myport<<endl;*/


    //bind，指定本机端口号，一般不用
    struct sockaddr_in client_addr; //client绑定网络地址
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(myport);
    client_addr.sin_addr.s_addr = INADDR_ANY;
    if (myport != 0)
    {
        if (bind(client_socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
        {
            printf("bind绑定socket和端口失败, %s(errno: %d)\n", strerror(errno), errno);
            return -1;
        }
    }



    //连接服务器
    if (connect(client_socket, (struct sockaddr *)&remote_addr, sizeof(remote_addr)) < 0)
    {
        printf("连接server端失败, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    printf("已连接到server端\n");

    //接收服务器欢迎消息
   /* if ((n = recv(client_socket, buff, BUFSIZ, 0)) > 0)
    {
        buff[n] = '\0';
        printf("从server端收到信息: %s\n", buff);
    }*/

    /*循环发送接收消息并打印*/
    while (true)
    {
        // receive from server
        if ((n = recv(client_socket, buff, BUFSIZ, 0)) > 0)
        {
            buff[n] = '\0';
            printf("recaeived:%s\n", buff);
        }
        else
        {
            printf("server端主动断开连接, 错误码为%d\n", n);
            break;
        }
    }

    close(client_socket);

    return 0;
}