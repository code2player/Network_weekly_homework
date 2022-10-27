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
        cout<<"port��Χ����"<<endl;
        exit(1);
    }
    if(myport<0||myport>65535){
        cout<<"myport��Χ����"<<endl;
        exit(1);
    }

    /*��ʼ����tcp������ʽclient�˵ı�д*/
    int client_socket; //�ͻ����׽���
    int n;
    char buff[BUFSIZ];              //���ݴ��仺����
    struct sockaddr_in remote_addr; //�������������ַ

    memset(&remote_addr, 0, sizeof(remote_addr));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(port);
    remote_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    //�����ͻ����׽���
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("����socketʧ��, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    /*cout<<"port: "<<port<<endl;
    cout<<"ip: "<<ip<<endl;
    cout<<"myport: "<<myport<<endl;*/


    //bind��ָ�������˿ںţ�һ�㲻��
    struct sockaddr_in client_addr; //client�������ַ
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(myport);
    client_addr.sin_addr.s_addr = INADDR_ANY;
    if (myport != 0)
    {
        if (bind(client_socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)
        {
            printf("bind��socket�Ͷ˿�ʧ��, %s(errno: %d)\n", strerror(errno), errno);
            return -1;
        }
    }



    //���ӷ�����
    if (connect(client_socket, (struct sockaddr *)&remote_addr, sizeof(remote_addr)) < 0)
    {
        printf("����server��ʧ��, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    printf("�����ӵ�server��\n");

    //���շ�������ӭ��Ϣ
   /* if ((n = recv(client_socket, buff, BUFSIZ, 0)) > 0)
    {
        buff[n] = '\0';
        printf("��server���յ���Ϣ: %s\n", buff);
    }*/

    /*ѭ�����ͽ�����Ϣ����ӡ*/
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
            printf("server�������Ͽ�����, ������Ϊ%d\n", n);
            break;
        }
    }

    close(client_socket);

    return 0;
}