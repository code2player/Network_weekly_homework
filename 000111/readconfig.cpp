#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unordered_map>
#include <fcntl.h>
#include <sys/sysinfo.h>
#include <sys/prctl.h>
using namespace std;

//������ȫ���ػ�����
void my_daemon_nodae()
{
    int pid;
    //int i;
    pid = fork();
    if (pid > 0)
        exit(0);
    else if (pid < 0)
        exit(1);
    else
    {
        ;
    }

    //pid=0, �ǵ�һ�ӽ��̣���̨����ִ��
    //setsid(); //��һ�ӽ��̳�Ϊ�µĻỰ�鳤�ͽ����鳤

    return;
}

int read_config()
{
    int result;
    int fd;
    fd = open("/etc/stu/stu_1953072.conf", O_RDWR, 00777);
    if (fd < 0)
    {
        cout << "��ʧ�ܣ�/etc/stu/stu_1953072.conf�ļ�������" << endl;
        exit(1);
    }

    //string config_name="�ӽ�������";

    int size;
    char buf[2];
    int equal_flag = 0;
    while (1)
    {
        size = read(fd, buf, 1);
        //cout<<(int)(buf[0])<<endl;
        if (size == 1)
        {
            if (buf[0] == ' ' || buf[0] == '\n' || buf[0] == '\r' || buf[0] == '\t')
            {
                continue;
            }
            if (buf[0] == '=')
            {
                equal_flag = 1;
                continue;
            }
            if (equal_flag == 1)
            {
                result = buf[0] - '0';
                size = read(fd, buf, 1);
                if (size == 1 && buf[0] >= '0' && buf[0] <= '9')
                {
                    result = result * 10 + buf[0] - '0';
                }
                close(fd);
                return result;
            }
        }
        else
        {
            close(fd);
            cout << "��ȡ��Ч" << endl;
            exit(1);
        }
    }

    close(fd);
    exit(1);
}
