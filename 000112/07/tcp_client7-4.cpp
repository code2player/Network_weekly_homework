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
using namespace std;

int main(int argc, char **argv)
{
    /*client���������*/
    para_need pn;
    pn.para_num = 7;
    pn.set_name_type(0, "port", "int");
    pn.set_range(0, 1, 0, 65535);
    pn.set_name_type(1, "ip", "string");
    pn.set_name_type(2, "myport", "int");
    pn.set_default(2, 0, 0);
    pn.set_range(2, 1, 0, 65535);

    /*��д�����������*/
    pn.set_name_type(3, "readbyte", "int");
    pn.set_default(3, 0, 1024);
    pn.set_range(3, 1, 1, 65536);

    pn.set_name_type(4, "sendbyte", "int");
    pn.set_default(4, 0, 1024);
    pn.set_range(4, 1, 1, 65536);

    pn.set_name_type(5, "delay", "int");
    pn.set_default(5, 0, 0);
    pn.set_range(5, 1, 0, 5000000);

    pn.set_name_type(6, "debug", "int");
    pn.set_default(6, 0);
    pn.set_value(6, 0);

    /*��ʼ���⴦��*/

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;
    int port = pn.para[0].para_value;
    string ip = pn.para[1].para_string;
    int myport = pn.para[2].para_value;
    int readbyte = pn.para[3].para_value;
    int sendbyte = pn.para[4].para_value;
    int delay = pn.para[5].para_value;
    int debug = pn.para[6].para_value;

    /*��ʼ����tcp������ʽclient�˵ı�д*/
    int client_socket; //�ͻ����׽���
    int n;
    char buff[BUF_SIZE];            //���ݴ��仺����
    struct sockaddr_in remote_addr; //�������������ַ

    /*client�˳�ʼ��*/
    init_client(port, ip, myport, client_socket, buff, remote_addr);

    memset(buff, 0, sizeof(buff));
    strcat(buff, "aaaaabbbbbcccccddddd");
    // send to server

    /*˳��R W D*/
    int sumr = 0;
    int sumw = 0;
    while (1)
    {
        n = write(client_socket, buff, sendbyte);
        if (n < 0)
        {
            printf("write error: %s(errno:%d)\n", strerror(errno), errno);
            break;
        }
        sumw += n;

        n = read(client_socket, buff, readbyte);
        if (n < 0)
        {
            printf("read error: %s(errno:%d)\n", strerror(errno), errno);
            break;
        }
        sumr += n;

        if (debug == 1)
        {
            cout << "read byte  = " << sumr << endl;
            cout << "write byte = " << sumw << endl;
        }
        usleep(delay);
    }

    close(client_socket);

    return 0;
}