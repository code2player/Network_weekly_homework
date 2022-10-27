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
#include "../../include/socket_common.h"
using namespace std;

void timer(int sig)
{
    if (SIGALRM == sig)
    {
        //alarm(rdelay); //���¼�����ʱ1s
    }

    return;
}

int main(int argc, char **argv)
{
    signal(SIGALRM, timer); //ע�ᰲװ�ź�
    /*client���������*/
    para_need pn;
    pn.para_num = 8;
    pn.set_name_type(0, "port", "int");
    pn.set_range(0, 1, 0, 65535);
    pn.set_name_type(1, "ip", "string");
    pn.set_name_type(2, "myport", "int");
    pn.set_default(2, 0, -1);
    pn.set_range(2, 1, 0, 65535);

    pn.set_name_type(3, "readbyte", "int");
    pn.set_range(3, 1, 1, 65535);
    pn.set_default(3, 0, 1024);

    pn.set_name_type(4, "writebyte", "int");
    pn.set_range(4, 1, 1, 65535);
    pn.set_default(4, 0, 1024);

    pn.set_name_type(5, "rdelay", "int");
    pn.set_range(5, 1, 0, 15);
    pn.set_default(5, 0, 0);

    pn.set_name_type(6, "wdelay", "int");
    pn.set_range(6, 1, 0, 15);
    pn.set_default(6, 0, 0);

    pn.set_name_type(7, "debug", "int");
    pn.set_default(7, 0);
    pn.set_value(7, 0);

    /*��ʼ���⴦��*/

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;

    int readbyte=pn.para[3].para_value;
    int writebyte=pn.para[4].para_value;
    //int rdelay=pn.para[5].para_value;
    int wdelay=pn.para[6].para_value;
    int debug=pn.para[7].para_value;

    /*��ʼ����tcp������ʽclient�˵ı�д*/
    Socket_Connect Socket_Client;
    /*client�˳�ʼ��*/
    Socket_Client.fill_ip_port(pn.para[0].para_value,pn.para[1].para_string,pn.para[2].para_value);
    Socket_Client.create_client_socket();
    Socket_Client.client_socket_NONBLOCK(1);
    Socket_Client.bind_client_socket();
    //Socket_Client.connect_client_socket();

    int errnox=errno;

    
    fd_set readset, writeset;
    while (1)
    {
        int ret2=connect(Socket_Client.client_socket, (struct sockaddr *)&(Socket_Client.remote_addr), sizeof(Socket_Client.remote_addr));
        if (ret2 == 0)
        {
            printf("�����ӵ�server��\n");
            break;
        }
        else if (errno == EINPROGRESS)
        {
            FD_ZERO(&readset);
            FD_ZERO(&writeset);
            FD_SET(Socket_Client.client_socket, &readset);
            FD_SET(Socket_Client.client_socket, &writeset);
            int select_ret = select(FD_SETSIZE, &readset, &writeset, 0, NULL);
            if(select_ret<0)
            {
                printf("select error: %s(errno:%d)\n", strerror(errno), errno);
                exit(-1);
            }
            if (FD_ISSET(Socket_Client.client_socket, &readset) || FD_ISSET(Socket_Client.client_socket, &writeset))
            {
                connect(Socket_Client.client_socket, (struct sockaddr *)&(Socket_Client.remote_addr), sizeof(Socket_Client.remote_addr));
                int err = errno;
                if (err == EISCONN)
                {
                    printf("�����ӵ�server��\n");
                    break;
                }
            }
        }
        else if (errno == EISCONN)
        {
            printf("�����ӵ�server��\n");
            break;
        }
        else{
            ;
        }
        sleep(1);//��ѯʱ��
    }

    //FD_ZERO(&writeset); // set��ʼ��Ϊ��
    errno = errnox;
    alarm(wdelay); //��ʱ��
    while (1)
    {
        FD_SET(Socket_Client.client_socket, &readset); //��set������server��socket
        /*select����������*/
        int ret1;
        ret1 = select(FD_SETSIZE, &readset, 0, 0, NULL);
        cout << "select return: " << ret1 << endl;
        printf("select error: %s(errno:%d)\n", strerror(errno), errno);
        if (ret1 < 0)
        {
            alarm(wdelay);
            int n;
            n = write(Socket_Client.client_socket, Socket_Client.buff, writebyte);
            if (debug == 1)
                cout << "write" << n << "���ֽ�" << endl;
            if (n <= 0)
            {
                printf("write error: %s(errno:%d)\n", strerror(errno), errno);
            }
        }
        else
        {
            if (FD_ISSET(Socket_Client.client_socket, &readset))
            {
                /*����read״̬*/
                int n;
                n = read(Socket_Client.client_socket, Socket_Client.buff, readbyte);
                if (debug == 1)
                    cout << "read" << n << "���ֽ�" << endl;
                if (n <= 0)
                {
                    printf("read error: %s(errno:%d)\n", strerror(errno), errno);
                }
            }
        }
    }

    close(Socket_Client.client_socket);

    return 0;
}