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
using namespace std;


 
int get_local_ip(string ip1)
{
    int result=0;//返回值，ip存在则为1，不存在返回0
    char *ip;
    //memset(ip, 0, sizeof(ip));
    //char dev[4]="ens";

    int fd, intrface;
    struct ifreq buf[INET_ADDRSTRLEN];  //这个结构定义在/usr/include/net/if.h，用来配置和获取ip地址，掩码，MTU等接口信息的
    struct ifconf ifc;
 
	/*1 建立socket链接，利用ioctl来自动扫描可用网卡*/
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
    {
 
        ifc.ifc_len = sizeof(buf);
 
        // caddr_t,linux内核源码里定义的：typedef void *caddr_t；
        ifc.ifc_buf = (caddr_t)buf;
 
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))  /*2  这里获取到可用网卡清单，包括网卡ip地址，mac地址*/
        {
            intrface = ifc.ifc_len/sizeof(struct ifreq);  //计算出有效网卡的数量//  
            while (intrface-- > 0)
             {
                if (!(ioctl(fd, SIOCGIFADDR, (char *)&buf[intrface])))  /*3  遍历并索引指定网卡的地址*/
                {
						ip=(inet_ntoa(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr));
						printf("IP:%s\n", ip);
                        string str=ip;
                        if(str==ip1)
                            result = 1;
                }
             }
        }

        close(fd);
        if (ip1 == "0.0.0.0")
            result = 1;
        return result;
    }
    return -1;
}

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

    int server_socket;//服务端套接字
    int client_socket;//客户端套接字
    struct sockaddr_in  servaddr;//服务器网络地址
    struct sockaddr_in  remote_addr;///客户端地址
    char  buff[BUFSIZ];//数据传送缓冲区
    int  n;
    socklen_t addr_size;//结构体长度，accept函数中该参数类型为socklen_t *
 
    memset(&servaddr, 0, sizeof(servaddr));//结构体初始化清零
    servaddr.sin_family = AF_INET;//IPv4
    servaddr.sin_addr.s_addr = inet_addr(ip.c_str());//INADDR_ANY代表0.0.0.0
    servaddr.sin_port = htons(port);
	
    addr_size = sizeof(struct sockaddr_in);
	
	//创建服务端套接字
	//1. create socket
    if( (server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        printf("创建socket失败, %s(errno: %d)\n",strerror(errno),errno);
        return -1;
    }

    //使用SO_REUSEADDR来对端口进行立即重新使用
    int optval = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    //绑定套接字到ip和端口
    // 2.bind socket & port to server
    if (bind(server_socket, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("bind绑定socket和端口失败, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    cout << "已绑定" << ip << "的" << port << "端口" << endl;

    //监听连接请求，监听队列长度为10
    // 3.listen
    if (listen(server_socket, 10) < 0)
    {
        printf("监听请求无效, %s(errno: %d)\n",strerror(errno),errno);
        return -1;
    }

    printf("进入等待连接状态......\n");

    //等待客户端连接请求到达
    // 4.accept
    if ((client_socket = accept(server_socket, (struct sockaddr *)&remote_addr, &addr_size)) < 0)
    {
        printf("建立连接失败, %s(errno: %d)", strerror(errno), errno);
        //continue;
    }

    // printf("与client端建立连接: %s\n", inet_ntoa(remote_addr.sin_addr)); //
    /*struct sockaddr_in  get_clientaddr;
    socklen_t len = sizeof(sockaddr);
    getpeername(client_socket, (struct sockaddr*)&get_clientaddr, &len);*/
    cout<<"与client端建立连接, ip:"<<inet_ntoa(remote_addr.sin_addr)<<" port:"<<htons(remote_addr.sin_port)<<endl;

    while (true)
    {
        //recv:等待另一端传来的数据（默认阻塞）
        //没有所谓的对等，s/c端互相通信时（recv/send），参数均设为c端

        if ((n = recv(client_socket, buff, BUFSIZ, 0)) > 0)
        {
            buff[n] = '\0';
            printf("recaeived:%s\n", buff);
        }
        else
        {
            printf("client端主动断开连接, 错误码为%d\n", n);
            break;
        }

        /*  const char wel[]="已与server端建立连接\n"//发送信息

          if (send(client_socket, wel, sizeof(wel), 0) < 0)
          {
              printf("发送信息失败, %s(errno: %d)", strerror(errno), errno);
              continue;
          }

          // 5.read message from socket
          while ((n = recv(client_socket, buff, BUFSIZ, 0)) > 0)
          {
              buff[n] = '\0';//末尾截断
              printf("从client端收到信息: %s\n", buff);

              if (send(client_socket, buff, strlen(buff), 0) < 0)
              {
                  printf("发送信息失败, %s(errno: %d)", strerror(errno), errno);
                  close(client_socket);
                  close(server_socket);
                  return -1;
              }
          }*/
    }

    //关闭套接字
	close(client_socket);
    close(server_socket);
	
    return 0;
}