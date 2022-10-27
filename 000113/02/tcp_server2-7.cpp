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
#include "../../include/socket_common.h"
using namespace std;

int main(int argc, char **argv)
{
    my_daemon();
    /*server���������*/
    para_need pn;
    pn.para_num = 2;

    pn.set_name_type(0, "port", "int");
    pn.set_range(0, 1, 0, 65535);

    pn.set_name_type(1, "ip", "string");
    pn.set_default(1, 0, 0, "0.0.0.0");

    /*��ʼ���⴦��*/

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;

    /*ip������λ���ж�*/
    int legal = get_local_ip(pn.para[1].para_string);
    if (legal == 0)
    {
        cout << "ip���ڱ���������Χ��" << endl;
        exit(1);
    }

    /*��ʼ����tcp��������ʽserver�˵ı�д*/
    Socket_Accept Socket_Server;
    Socket_Server.fill_ip_port(pn.para[0].para_value,pn.para[1].para_string);
    Socket_Server.create_server_socket();
    Socket_Server.server_socket_NONBLOCK(1);//create������server_socketΪ��������ʽ
    Socket_Server.bind_server_socket();
    Socket_Server.listen_server_socket();

    fd_set readset,testset;                                //�ļ�����
    FD_ZERO(&readset);                             // set��ʼ��Ϊ��
    FD_SET(Socket_Server.server_socket, &readset); //��set�����server��socket
    while (1)
    {
        testset=readset;
        /*select����������*/
        int ret1;
        ret1 = select(FD_SETSIZE, &testset, 0, 0, NULL);
        cout << "select return: " << ret1 << endl;
        printf("select error: %s(errno:%d)\n", strerror(errno), errno);
        if (ret1 <= 0)
        {
            exit(-1);
        }
        //�ȴ��ͻ����������󵽴�
        // 4.accept
        Socket_Server.accept_server_socket();

        // accept������client_socketΪ��������ʽ
        Socket_Server.client_socket_NONBLOCK(1);

        /*�����ӽ���*/
        int pid = fork();
        if (pid == 0) //�ӽ���
        {
            FD_ZERO(&readset);                             // set��ʼ��Ϊ��
            FD_SET(Socket_Server.client_socket, &readset); //��set�����socket
            /*select����������*/
            int ret1;
            ret1 = select(FD_SETSIZE, &readset, 0, 0, NULL);
            cout << "select return: " << ret1 << endl;
            printf("select error: %s(errno:%d)\n", strerror(errno), errno);
            if (ret1 <= 0)
            {
                exit(-1);
            }
            /*����read״̬*/
            int n;
            n = read(Socket_Server.client_socket, Socket_Server.buff, 20);
            if (n <= 0)
            {
                printf("read error: %s(errno:%d)\n", strerror(errno), errno);
                // break;
            }
            cout << "read" << n << "���ֽ�" << endl;
            break;
        }
    }

    //�ر��׽���
    close(Socket_Server.client_socket);
    close(Socket_Server.server_socket);

    return 0;
}