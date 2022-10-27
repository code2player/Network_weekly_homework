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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/un.h>
#include <stddef.h>
#include "../../include/mydaemon.h"
#include "../../include/parameter_process.h"
using namespace std;

int main(int argc, char **argv)
{
    my_daemon();
    /*��ʼ����unix�׽���������ʽserver�˵ı�д*/

    int server_socket;              //������׽���
    int client_socket;              //�ͻ����׽���
    struct sockaddr_un servaddr;    //�����������ַ
    struct sockaddr_un remote_addr; ///�ͻ��˵�ַ
    char send_buf[BUFSIZ];          //���ݴ��ͻ�����
    char recv_buf[BUFSIZ];          //���ݴ��ͻ�����
    socklen_t addr_size;            //�ṹ�峤�ȣ�accept�����иò�������Ϊsocklen_t *

    memset(&servaddr, 0, sizeof(servaddr)); //�ṹ���ʼ������
    servaddr.sun_family = AF_UNIX;          // unix
    strcpy(servaddr.sun_path, "test6-2.socket");

    addr_size = sizeof(struct sockaddr_in);

    //����������׽���
    // 1. create socket
    if ((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        printf("����socketʧ��, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    //ʹ��SO_REUSEADDR���Զ˿ڽ�����������ʹ��
    int optval = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    //���׽��ֵ�ip�Ͷ˿�
    // 2.bind socket & port to server
    int exist_soc = access("test6-2.socket", 0);
    if (exist_soc == 0) //������ɾ��
    {
        unlink("test6-2.socket");
    }
    if (bind(server_socket, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("bind��socketʧ��, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    printf("bind��socket�ɹ�......\n");

    //�����������󣬼������г���Ϊ10
    // 3.listen
    if (listen(server_socket, 10) < 0)
    {
        printf("����������Ч, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    printf("����ȴ�����״̬......\n");

    //�ȴ��ͻ����������󵽴�
    // 4.accept
    if ((client_socket = accept(server_socket, (struct sockaddr *)&remote_addr, &addr_size)) < 0)
    {
        printf("��������ʧ��, %s(errno: %d)", strerror(errno), errno);
        // continue;
    }
    //������
    int flags = fcntl(client_socket, F_GETFL, 0);
    fcntl(client_socket, F_SETFL, flags | O_NONBLOCK);

    cout << "��6-2-2 client�˽�������" << endl;

    strcpy(send_buf, "1953072 Ф���� 6-2-1 to 6-2-2");

    fd_set readset, writeset;
    FD_ZERO(&readset);
    FD_ZERO(&writeset);
    FD_SET(client_socket, &readset);  //���ͻ���socket���뵽������
    FD_SET(client_socket, &writeset); //���ͻ���socket���뵽������

    int rets = select(FD_SETSIZE, 0, &writeset, 0, NULL);
    if (rets < 0)
    {
        printf("select error: %s(errno:%d)\n", strerror(errno), errno);
    }
    if (write(client_socket, send_buf, BUFSIZ) < 0)
    {
        printf("write error, %s(errno: %d)\n", strerror(errno), errno);
        exit(-1);
    }

    rets = select(FD_SETSIZE, &readset, 0, 0, NULL);
    if (rets < 0)
    {
        printf("select error: %s(errno:%d)\n", strerror(errno), errno);
    }
    if (read(client_socket, recv_buf, BUFSIZ) < 0)
    {
        printf("read error, %s(errno: %d)\n", strerror(errno), errno);
        exit(-1);
    }

    cout << "6-2-1 recv: " << recv_buf << endl;
    //�ر��׽���
    close(client_socket);
    close(server_socket);

    return 0;
}