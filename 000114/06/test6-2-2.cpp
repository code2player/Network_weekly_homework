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
    /*��ʼ����tcp������ʽclient�˵ı�д*/
    int client_socket;              //�ͻ����׽���
    char send_buf[BUFSIZ];          //���ݴ��仺����
    char recv_buf[BUFSIZ];          //���ݴ��仺����
    struct sockaddr_un remote_addr; //�������������ַ

    memset(&remote_addr, 0, sizeof(remote_addr));
    remote_addr.sun_family = AF_UNIX;
    strcpy(remote_addr.sun_path, "test6-2.socket");

    //�����ͻ����׽���
    if ((client_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        printf("����socketʧ��, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    //���ӷ�����
    if (connect(client_socket, (struct sockaddr *)&remote_addr, sizeof(remote_addr)) < 0)
    {
        printf("����server��ʧ��, %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }
    //������
    int flags = fcntl(client_socket, F_GETFL, 0);
    fcntl(client_socket, F_SETFL, flags | O_NONBLOCK);

    printf("�����ӵ�server��\n");

    strcpy(send_buf, "1953072 Ф���� 6-2-2 to 6-2-1");

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

    cout << "6-2-2 recv: " << recv_buf << endl;
    //�ر��׽���
    close(client_socket);

    return 0;
}