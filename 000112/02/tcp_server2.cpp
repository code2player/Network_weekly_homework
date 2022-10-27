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
        cout<<"port��Χ����"<<endl;
        exit(1);
    }



    /*��ʼ����tcp������ʽserver�˵ı�д*/

    int server_socket;//������׽���
    int client_socket;//�ͻ����׽���
    struct sockaddr_in  servaddr;//�����������ַ
    struct sockaddr_in  remote_addr;///�ͻ��˵�ַ
    char  buff[BUFSIZ];//���ݴ��ͻ�����
    int  n;
    socklen_t addr_size;//�ṹ�峤�ȣ�accept�����иò�������Ϊsocklen_t *
 
    memset(&servaddr, 0, sizeof(servaddr));//�ṹ���ʼ������
    servaddr.sin_family = AF_INET;//IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);
	
    addr_size = sizeof(struct sockaddr_in);
	
	//����������׽���
	//1. create socket
    if( (server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        printf("����socketʧ��, %s(errno: %d)\n",strerror(errno),errno);
        return -1;
    }

    //ʹ��SO_REUSEADDR���Զ˿ڽ�����������ʹ��
    int optval = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
 
	//���׽��ֵ�ip�Ͷ˿�
    //2.bind socket & port to server
    if( bind(server_socket, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("bind��socket�Ͷ˿�ʧ��, %s(errno: %d)\n",strerror(errno),errno);
        return -1;
    }
 
	//�����������󣬼������г���Ϊ10
    //3.listen
    if( listen(server_socket, 10) < 0){
        printf("����������Ч, %s(errno: %d)\n",strerror(errno),errno);
        return -1;
    }

    printf("����ȴ�����״̬......\n");

    //�ȴ��ͻ����������󵽴�
    // 4.accept
    if ((client_socket = accept(server_socket, (struct sockaddr *)&remote_addr, &addr_size)) < 0)
    {
        printf("��������ʧ��, %s(errno: %d)", strerror(errno), errno);
        //continue;
    }

    // printf("��client�˽�������: %s\n", inet_ntoa(remote_addr.sin_addr)); //
    /*struct sockaddr_in  get_clientaddr;
    socklen_t len = sizeof(sockaddr);
    getpeername(client_socket, (struct sockaddr*)&get_clientaddr, &len);*/
    cout<<"��client�˽�������, ip:"<<inet_ntoa(remote_addr.sin_addr)<<" port:"<<htons(remote_addr.sin_port)<<endl;

    while (true)
    {
        //recv:�ȴ���һ�˴��������ݣ�Ĭ��������
        //û����ν�ĶԵȣ�s/c�˻���ͨ��ʱ��recv/send������������Ϊc��

        if ((n = recv(client_socket, buff, BUFSIZ, 0)) > 0)
        {
            buff[n] = '\0';
            printf("recaeived:%s\n", buff);
        }
        else
        {
            printf("client�������Ͽ�����, ������Ϊ%d\n", n);
            break;
        }

        /*  const char wel[]="����server�˽�������\n"//������Ϣ

          if (send(client_socket, wel, sizeof(wel), 0) < 0)
          {
              printf("������Ϣʧ��, %s(errno: %d)", strerror(errno), errno);
              continue;
          }

          // 5.read message from socket
          while ((n = recv(client_socket, buff, BUFSIZ, 0)) > 0)
          {
              buff[n] = '\0';//ĩβ�ض�
              printf("��client���յ���Ϣ: %s\n", buff);

              if (send(client_socket, buff, strlen(buff), 0) < 0)
              {
                  printf("������Ϣʧ��, %s(errno: %d)", strerror(errno), errno);
                  close(client_socket);
                  close(server_socket);
                  return -1;
              }
          }*/
    }

    //�ر��׽���
	close(client_socket);
    close(server_socket);
	
    return 0;
}