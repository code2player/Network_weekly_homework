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
using namespace std;

int main(int argc, char **argv)
{
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
    int port = pn.para[0].para_value;
    string ip = pn.para[1].para_string;

    /*ip������λ���ж�*/
    int legal = get_local_ip(ip);
    if (legal == 0)
    {
        cout << "ip���ڱ���������Χ��" << endl;
        exit(1);
    }

    /*��ʼ����tcp��������ʽserver�˵ı�д*/

    int server_socket;              //������׽���
    int client_socket;              //�ͻ����׽���
    struct sockaddr_in servaddr;    //�����������ַ
    struct sockaddr_in remote_addr; ///�ͻ��˵�ַ
    char buff[BUF_SIZE];              //���ݴ��ͻ�����
    int n;
    socklen_t addr_size; //�ṹ�峤�ȣ�accept�����иò�������Ϊsocklen_t *
    addr_size = sizeof(struct sockaddr_in);

    // server�˳�ʼ��
    //���һ��noaccept������Ϊ1������init��accept
    int init_ret = init_server(port, ip, server_socket, client_socket, servaddr, remote_addr, buff, addr_size, 1);
    if (init_ret == -1)
    {
        return 0;
    }

    while (1)
    {
        //�ȴ��ͻ����������󵽴�
        // 4.accept
        if ((client_socket = accept(server_socket, (struct sockaddr *)&remote_addr, &addr_size)) < 0)
        {
            printf("��������ʧ��, %s(errno: %d)", strerror(errno), errno);
            // continue;
        }

        cout << "��client�˽�������, ip:" << inet_ntoa(remote_addr.sin_addr) << " port:" << htons(remote_addr.sin_port) << endl;
        n = read(client_socket, buff, 20);
        if (n <= 0)
        {
            printf("read error: %s(errno:%d)\n", strerror(errno), errno);
            //break;
        }
        cout << "read" << n << "���ֽ�" << endl;
    }

    //�ر��׽���
    close(client_socket);
    close(server_socket);

    return 0;
}