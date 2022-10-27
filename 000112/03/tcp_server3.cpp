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
    int result=0;//����ֵ��ip������Ϊ1�������ڷ���0
    char *ip;
    //memset(ip, 0, sizeof(ip));
    //char dev[4]="ens";

    int fd, intrface;
    struct ifreq buf[INET_ADDRSTRLEN];  //����ṹ������/usr/include/net/if.h���������úͻ�ȡip��ַ�����룬MTU�Ƚӿ���Ϣ��
    struct ifconf ifc;
 
	/*1 ����socket���ӣ�����ioctl���Զ�ɨ���������*/
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
    {
 
        ifc.ifc_len = sizeof(buf);
 
        // caddr_t,linux�ں�Դ���ﶨ��ģ�typedef void *caddr_t��
        ifc.ifc_buf = (caddr_t)buf;
 
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))  /*2  �����ȡ�����������嵥����������ip��ַ��mac��ַ*/
        {
            intrface = ifc.ifc_len/sizeof(struct ifreq);  //�������Ч����������//  
            while (intrface-- > 0)
             {
                if (!(ioctl(fd, SIOCGIFADDR, (char *)&buf[intrface])))  /*3  ����������ָ�������ĵ�ַ*/
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
        cout<<"port��Χ����"<<endl;
        exit(1);
    }*/

    int legal = get_local_ip(ip);
    if (legal == 0)
    {
        cout << "ip���ڱ���������Χ��" << endl;
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
    servaddr.sin_addr.s_addr = inet_addr(ip.c_str());//INADDR_ANY����0.0.0.0
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
    // 2.bind socket & port to server
    if (bind(server_socket, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("bind��socket�Ͷ˿�ʧ��, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    cout << "�Ѱ�" << ip << "��" << port << "�˿�" << endl;

    //�����������󣬼������г���Ϊ10
    // 3.listen
    if (listen(server_socket, 10) < 0)
    {
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