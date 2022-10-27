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
    /*参数定义*/
    para_need pn;
    pn.para_num=9;
    pn.para[0].para_name="port";
    pn.para[0].para_type="int";
    pn.para[1].para_name="ip";
    pn.para[1].para_type="string";
    pn.para[2].para_name="myport";
    pn.para[2].para_type="int";
    pn.para[2].para_whe_have_default=0;//
    pn.para[2].para_value_default=0;//

    /*tcp收发缓冲区设置*/
    pn.set_name_type(3, "getrbuf", "int");
    pn.set_value(3, 0);
    pn.set_default(3, 0);
    pn.set_name_type(4, "getwbuf", "int");
    pn.set_value(4, 0);
    pn.set_default(4, 0);

    pn.set_name_type(5, "setrbuf", "int");
    pn.set_default(5, 0, 8);
    pn.set_range(5, 1, 1, 16384);

    pn.set_name_type(6, "setwbuf", "int");
    pn.set_default(6, 0, 8);
    pn.set_range(6, 1, 1, 16384);

    pn.set_name_type(7, "getnrbuf", "int");
    pn.set_value(7, 0);
    pn.set_default(7, 0);
    pn.set_name_type(8, "getnwbuf", "int");
    pn.set_value(8, 0);
    pn.set_default(8, 0);
    /*开始本题处理*/


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

    /*在tcp_buf中对于缓冲区进行打印和设置*/
    int getrbuf = pn.para[3].para_value;
    int getwbuf = pn.para[4].para_value;
    int setrbuf = pn.para[5].para_value;
    int setwbuf = pn.para[6].para_value;
    int getnrbuf = pn.para[7].para_value;
    int getnwbuf = pn.para[8].para_value;
    setrbuf *= 1024;
    setwbuf *= 1024;
    tcp_buf(client_socket,getrbuf, getwbuf, setrbuf, setwbuf, getnrbuf, getnwbuf);


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