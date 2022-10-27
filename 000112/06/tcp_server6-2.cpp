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

    int server_socket;              //������׽���
    int client_socket;              //�ͻ����׽���
    struct sockaddr_in servaddr;    //�����������ַ
    struct sockaddr_in remote_addr; ///�ͻ��˵�ַ
    char buff[BUF_SIZE];              //���ݴ��ͻ�����
    int n;
    socklen_t addr_size; //�ṹ�峤�ȣ�accept�����иò�������Ϊsocklen_t *
    addr_size = sizeof(struct sockaddr_in);

    //server�˳�ʼ��
    init_server(port,ip,server_socket,client_socket,servaddr,remote_addr,buff,addr_size);
    cout<<"��client�����ӳɹ�, ��������״̬, ���س�����......"<<endl;
    getchar();//��readǰ��ͣ

    // recv:�ȴ���һ�˴��������ݣ�Ĭ��������
    //û����ν�ĶԵȣ�s/c�˻���ͨ��ʱ��recv/send������������Ϊc��

    int sumn = 0;

    while (1)
    {
        if ((n = recv(client_socket, buff, PAC_SIZE,0)) > 0)
        {
            sumn += n;
            cout << "�������ֽ���: " << sumn << endl;
        }
        else
        {
            printf("client�������Ͽ�����, ������Ϊ%d\n", n);
            break;
        }
        sleep(1);
    }
    //�ر��׽���
    close(client_socket);
    close(server_socket);

    return 0;
}