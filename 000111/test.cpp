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

//����
void my_daemon_nodae();
int read_config();

//ȫ�ֱ������鿴��ǰ����״̬
int whe_fork[25];    //���ӽ��̽��̺�
int fnum = 15; //���fork�ӽ�����
int now_fork = 0;    //��ǰfork�ӽ��̸���

//ps����������޸�
void ps_main(string exename)
{
    string str=exename;
    str+=" [main]";
    prctl(PR_SET_NAME, str.c_str());
}

//ps�����ӽ��̽������޸�
void ps_sub(string exename,int i)
{
    string str=exename;
    str+=" [sub-";
    if(i<10)
    str+="0";
    str+=to_string(i);
    str+="]";
    prctl(PR_SET_NAME, str.c_str());
}

string time_to_string(double timeuse)
{
    //΢��
    int times = timeuse / 1000000;
    int hour;
    int min;
    int sec;

    hour = times / 3600;
    times %= 3600;
    min = times / 60;
    times %= 60;
    sec = times;

    string result = "";
    if (hour < 10)
        result += "0";
    result += to_string(hour);
    result += ":";
    if (min < 10)
        result += "0";
    result += to_string(min);
    result += ":";
    if (sec < 10)
        result += "0";
    result += to_string(sec);

    return result;
}

string sub_name(string exename,int proc_num, char **argv, double timeuse)
{
    string str = "";
    str = exename;
    str += " [Sub-";
    if (proc_num < 10)
    {
        str += "0";
        str += to_string(proc_num);
    }
    else
    {
        str += to_string(proc_num);
    }
    str += " ";
    str += time_to_string(timeuse);
    str += "]";

    return str;
}

string main_name(string exename,char **argv, double timeuse)
{
    string str = "";
    str += exename;
    str += " [main ";
    str += time_to_string(timeuse);
    str += "]";

    return str;
}

int sub(string exename,int proc_num, char **argv)
{
    ps_sub(exename,proc_num);
    prctl(PR_SET_PDEATHSIG, SIGKILL);//�ӽ���������,kill�����̺��ӽ����Զ��˳�
    //���� ��ʱ
    string str;

    struct timeval tpstart, tpend;
    double timeuse;
    gettimeofday(&tpstart, NULL);
    //���Ķ��˴���ʼ��ʱ��

    for (;;)
    {
        gettimeofday(&tpend, NULL);
        timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
        str = sub_name(exename,proc_num, argv, timeuse);
        strcpy(argv[0], str.c_str());
        sleep(1);
    }
}

void handler(int sig)
{
    int stat;
    int result;
    while((result=waitpid(-1,&stat,WNOHANG))>0)
    {
        //cout<<stat<<"over"<<endl;
        //wait_process++;
        now_fork--;
        for(int i=1;i<=fnum;i++){
            if(whe_fork[i]==result){
                whe_fork[i]=0;
                break;
            }
        }
    }
}

void print_info()
{
    int fd;
    fd = open("/home/stu/u1953072/1953072.dat", O_RDWR, 00777);
    if (fd < 0)
    {
        cout << "��ʧ�ܣ�/home/stu/u1953072/1953072.dat�ļ�������" << endl;
        exit(1);
    }
    char buf[50];
    memset(buf, 0, sizeof(buf));
    int size = read(fd, buf, 50);
    if(size==0){
        cout<<"dat�ļ�Ϊ��"<<endl;
        exit(-1);
    }
    cout << buf << endl;
    close(fd);
}

int main(int argc, char **argv, char **env)
{
    my_daemon_nodae();
    signal(SIGCHLD, handler);

    print_info();
    fnum=read_config();

    string exename=argv[0];

    memset(whe_fork, 0, sizeof(whe_fork));

    //���� ��ʱ
    string str;

    //string strmain=exename;
    ps_main(exename);

    struct timeval tpstart, tpend;
    double timeuse;
    gettimeofday(&tpstart, NULL);
    //���Ķ��˴���ʼ��ʱ��

    for (int i = 1; i <= fnum; i++)
    {
        int pid = fork();
        if (pid > 0) //�����̼���
        {
            now_fork++;
            whe_fork[i] = pid;
            gettimeofday(&tpend, NULL);
            timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
            str = main_name(exename,argv, timeuse);
            //cout << str << endl;
            strcpy(argv[0], str.c_str());
        }
        else if (pid < 0) //�����ӽ���ʧ��
        {
            printf("�����ӽ���ʧ��\n");
            exit(1);
        }
        else //�ӽ���
        {
            sub(exename,i, argv);
            exit(1);
        }
        sleep(1);
    }

    for (;;)
    {

        if (now_fork != fnum)
        {
            for (int i = 1; i <= fnum; i++)
            {
                if (whe_fork[i] != 0)
                    continue;
                int pid = fork();
                if (pid > 0) //�����̼���
                {
                    now_fork++;
                    whe_fork[i] = pid;
                    gettimeofday(&tpend, NULL);
                    timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
                    str = main_name(exename,argv, timeuse);
                    strcpy(argv[0], str.c_str());
                }
                else if (pid < 0) //�����ӽ���ʧ��
                {
                    printf("�����ӽ���ʧ��\n");
                    exit(1);
                }
                else //�ӽ���
                {
                    sub(exename,i, argv);
                    exit(1);
                }
                sleep(1);
            }
        }
        else
        {
            gettimeofday(&tpend, NULL);
            timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
            str = main_name(exename,argv, timeuse);
            strcpy(argv[0], str.c_str());
            sleep(1);
        }
    }

    return 0;
}

//  ../common/mydaemon.cpp ../common/parameter_process.cpp