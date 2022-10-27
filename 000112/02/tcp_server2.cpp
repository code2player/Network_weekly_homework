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
    pn.para_num=1;
    pn.para[0].para_name="port";
    pn.para[0].para_type="int";

    int ret=parameter_process(argc,argv,pn);
    if(ret<0)
    return 0;
    int port=pn.para[0].para_value;
    if(port<0||port>65535){
        cout<<"port范围有误"<<endl;
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
    servaddr.sin_addr.s_addr = INADDR_ANY;
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
    //2.bind socket & port to server
    if( bind(server_socket, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("bind绑定socket和端口失败, %s(errno: %d)\n",strerror(errno),errno);
        return -1;
    }
 
	//监听连接请求，监听队列长度为10
    //3.listen
    if( listen(server_socket, 10) < 0){
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