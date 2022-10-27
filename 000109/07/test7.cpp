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
#include "../../include/mydaemon.h"
#include "../../include/parameter_process.h"
using namespace std;

//计数器全局变量
    int fork_process=0;
    int wait_process=0;
    

int sub(int size)
{
    char *str = (char *)malloc(size * 1024 * sizeof(char));
    if(str!=NULL){
        int i;
        for(i=0;i<size * 1024 * sizeof(char);i++){
            str[i]=rand()%256;
        }
    }

    sleep(20);
    exit(0);
}

void handler(int sig)
{
    int stat;
    while(waitpid(-1,&stat,WNOHANG)>0)
    {
        wait_process++;
    }
}


int main(int argc, char **argv)
{
    my_daemon();
    srand(time(0));
    signal(SIGCHLD,handler);
    para_need pn;
    pn.para_num=3;
    pn.para[0].para_name="fnum";
    pn.para[0].para_type="int";
    pn.para[1].para_name="size";
    pn.para[1].para_type="int";
    pn.para[2].para_name="ptime";
    pn.para[2].para_type="int";

    int ret=parameter_process(argc,argv,pn);
    if(ret<0)
    return 0;

/*struct timeval tpstart ,tpend;
double timeuse;
gettimeofday(&tpstart,NULL);
gettimeofday(&tpend ,NULL );
timeuse=1000000* (tpend.tv_sec-tpstart.tv_sec )+tpend.tv_usec - tpstart.tv_usec;
printf("used time :%fus\n" ,timeuse);*/





    int fnum=pn.para[0].para_value;
    int size = pn.para[1].para_value;
    int ptime = pn.para[2].para_value;

    struct timeval tpstart, tpend;
    double timeuse;
    gettimeofday(&tpstart, NULL);
    double itime=0;

    struct sysinfo sys;
    int max_process_num=sysconf(_SC_CHILD_MAX);
    cout<<"maxproc: "<<max_process_num<<endl;
    int nowproc=3;
    

    for (int i = 0; i < fnum; i++)
    {
        int err = sysinfo(&sys);
        nowproc=fork_process-wait_process;//模拟，假设所有进程在此创建，留出系统进程冗余
        if (sys.freeram < 1024 * 1024 * 100||(max_process_num-nowproc)<50)
        {
            // sleep(1);
            i--;
            gettimeofday(&tpend, NULL);
            timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
            if (timeuse / 1000000 > itime * ptime)
            {
                // cout<<pid<<"已经过"<<itime*ptime<<"s"<<endl;
                cout << "已分裂" << fork_process << "个子进程，已回收" << wait_process << "个子进程" << endl;
                itime = itime + 1;
                // sleep(10);
            }
            continue;
        }
        int pid = fork();
        if (pid > 0) //父进程继续
        {
            fork_process++;
        }
        else if (pid < 0) //创建子进程失败
        {
            i--;
        }
        else //子进程
        {
            sub(size);
        }

        gettimeofday(&tpend, NULL);
        timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
        if(timeuse/1000000>itime*ptime){
            //cout<<pid<<"已经过"<<itime*ptime<<"s"<<endl;
            cout<<"已分裂"<<fork_process<<"个子进程，已回收"<<wait_process<<"个子进程"<<endl;
            //cout<<"nowproc: "<<sys.procs<<endl;
            itime=itime+1;
            //sleep(10);
        }
    }

    while (1)
    {
        gettimeofday(&tpend, NULL);
        timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
        if(timeuse/1000000>itime*ptime){
            //cout<<pid<<"已经过"<<itime*ptime<<"s"<<endl;
            cout<<"已分裂"<<fork_process<<"个子进程，已回收"<<wait_process<<"个子进程"<<endl;
            itime=itime+1;
            //sleep(10);
        }
        if (fork_process == fnum && wait_process == fnum)
        {
            gettimeofday(&tpend, NULL);
            timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
            cout << "分裂/回收" << fnum << "个子进程完成，用时" << timeuse / 1000000 << "秒" << endl;
            break;
        }
    }

    return 0;
}