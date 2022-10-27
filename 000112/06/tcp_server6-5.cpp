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
    pn.para_num = 9;

    pn.para[0].para_name = "port";
    pn.para[0].para_type = "int";
    pn.para[0].para_whe_have_range = 1;
    pn.para[0].min_range = 0;
    pn.para[0].max_range = 65535;

    pn.para[1].para_name = "ip";
    pn.para[1].para_type = "string";
    pn.para[1].para_whe_have_default = 0;
    pn.para[1].para_string_default = "0.0.0.0";

    pn.set_name_type(2, "myport", "int");
    pn.set_default(2, 0);

    /*tcp�շ�����������*/
    pn.set_name_type(3, "getrbuf", "int");
    pn.set_value(3, 0);
    pn.set_default(3, 0);
    pn.set_name_type(4, "getwbuf", "int");
    pn.set_value(4, 0);
    pn.set_default(4, 0);

    pn.set_name_type(5, "setrbuf", "int");
    pn.set_default(5, 0, 8);
    pn.set_range(5, 1, 1, 16384);

    pn.set_name_type(6, "setwbuf", "int");
    pn.set_default(6, 0, 8);
    pn.set_range(6, 1, 1, 16384);

    pn.set_name_type(7, "getnrbuf", "int");
    pn.set_value(7, 0);
    pn.set_default(7, 0);
    pn.set_name_type(8, "getnwbuf", "int");
    pn.set_value(8, 0);
    pn.set_default(8, 0);
    /*��ʼ���⴦��*/

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

    /*��tcp_buf�ж��ڻ��������д�ӡ������*/
    int getrbuf = pn.para[3].para_value;
    int getwbuf = pn.para[4].para_value;
    int setrbuf = pn.para[5].para_value;
    int setwbuf = pn.para[6].para_value;
    int getnrbuf = pn.para[7].para_value;
    int getnwbuf = pn.para[8].para_value;
    setrbuf *= 1024;
    setwbuf *= 1024;
    tcp_buf(server_socket,getrbuf, getwbuf, setrbuf, setwbuf, getnrbuf, getnwbuf);
    cout<<"��client�����ӳɹ�, ��������״̬, ���س�����......"<<endl;
    getchar();//��readǰ��ͣ

    // recv:�ȴ���һ�˴��������ݣ�Ĭ��������
    //û����ν�ĶԵȣ�s/c�˻���ͨ��ʱ��recv/send������������Ϊc��

    int sumn = 0;

    while (1)
    {
        if ((n = read(client_socket, buff, PAC_SIZE)) > 0)
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