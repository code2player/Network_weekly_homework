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
    /*server���������*/
    para_need pn;
    pn.para_num = 7;

    pn.set_name_type(0, "port", "int");
    pn.set_range(0, 1, 0, 65535);

    pn.set_name_type(1, "ip", "string");
    pn.set_default(1, 0, 0, "0.0.0.0");

    pn.set_name_type(2, "readbyte", "int");
    pn.set_range(2, 1, 1, 65535);
    pn.set_default(2, 0, 1024);

    pn.set_name_type(3, "writebyte", "int");
    pn.set_range(3, 1, 1, 65535);
    pn.set_default(3, 0, 1024);

    pn.set_name_type(4, "rdelay", "int");
    pn.set_range(4, 1, 0, 15);
    pn.set_default(4, 0, 0);

    pn.set_name_type(5, "wdelay", "int");
    pn.set_range(5, 1, 0, 15);
    pn.set_default(5, 0, 0);

    pn.set_name_type(6, "debug", "int");
    pn.set_default(6, 0);
    pn.set_value(6, 0);



    /*��ʼ���⴦��*/

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;
    
    int readbyte=pn.para[2].para_value;
    int writebyte=pn.para[3].para_value;
    //int rdelay=pn.para[4].para_value;
    int wdelay=pn.para[5].para_value;
    int debug=pn.para[6].para_value;


    /*ip������λ���ж�*/
    int legal = get_local_ip(pn.para[1].para_string);
    if (legal == 0)
    {
        cout << "ip���ڱ���������Χ��" << endl;
        exit(1);
    }

    /*��ʼ����tcp��������ʽserver�˵ı�д*/
    Socket_Accept Socket_Server;
    Socket_Server.fill_ip_port(pn.para[0].para_value, pn.para[1].para_string);
    Socket_Server.create_server_socket();
    Socket_Server.server_socket_NONBLOCK(1); // create������server_socketΪ��������ʽ
    Socket_Server.bind_server_socket();
    Socket_Server.listen_server_socket();

    /*��һ��socket����client���飬ÿ��write���е�����socket*/
    int client_socket_array[20];
    int client_socket_num = 0;

    fd_set readset, testset;                       //�ļ�����
    FD_ZERO(&readset);                             // set��ʼ��Ϊ��
    FD_SET(Socket_Server.server_socket, &readset); //��set�����server��socket
    /*readset:��׼���ݣ�������select�����ڱ���
    testset:ÿ�α�select�ı�*/

    
    while (1)
    {
        testset = readset; //����
        int rets;
        rets = select(FD_SETSIZE, &testset, 0, 0, NULL);
        cout << "select return: " << rets << endl;
        //printf("select error: %s(errno:%d)\n", strerror(errno), errno);
        if (rets < 0)
        {
            printf("select error: %s(errno:%d)\n", strerror(errno), errno);

            /*����write״̬*/
            if (errno == EINTR)
            {
                alarm(wdelay);
                int n;

                for (int i = 0; i < client_socket_num; i++)
                {
                    n = write(client_socket_array[i], Socket_Server.buff, writebyte);
                    if (debug == 1)
                        cout << "write to socket=" << client_socket_array[i] << " " << n << "���ֽ�" << endl;
                    if (n <= 0)
                    {
                        printf("write error: %s(errno:%d)\n", strerror(errno), errno);
                        // break;
                    }
                }
            }
        }
        else
        {
            int fd;
            for (fd = 0; fd < FD_SETSIZE; fd++)
            {
                /*�ҵ�����ļ�������*/
                if (FD_ISSET(fd, &testset))
                {
                    /*�ж��Ƿ�Ϊ�������׽��֣������ʾΪ�ͻ��������ӡ�*/
                    if (fd == Socket_Server.server_socket)
                    {
                        // cout<<"fd: "<<fd<<endl;
                        //�ȴ��ͻ����������󵽴�
                        //  4.accept
                        Socket_Server.accept_server_socket();
                        // accept������client_socketΪ��������ʽ
                        Socket_Server.client_socket_NONBLOCK(1);
                        // cout<<Socket_Server.client_socket<<endl;
                        FD_SET(Socket_Server.client_socket, &readset); //���ͻ���socket���뵽������
                        if (client_socket_num == 0)
                        {
                            alarm(wdelay);
                        }

                        client_socket_array[client_socket_num]=Socket_Server.client_socket;
                        client_socket_num++;

                        // break;
                    }
                    else //�ͻ���socket������������ʱ
                    {
                        /*����read״̬*/
                        int n;
                        n = read(fd, Socket_Server.buff, readbyte);
                        if (debug == 1)
                            cout << "read from socket=" << fd << " " << n << " "<< "���ֽ�" << endl;
                        if (n <= 0)
                        {
                            printf("read error: %s(errno:%d)\n", strerror(errno), errno);
                        }
                    }
                }
            }
        }
    }

    //�ر��׽���
    close(Socket_Server.client_socket);
    close(Socket_Server.server_socket);

    return 0;
}