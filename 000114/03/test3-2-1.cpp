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
using namespace std;

#define MY_SIGN_CONTINUE 47
#define MY_SIGN_EXIT 53

int isRunning()
{
    int ret = -1;
    FILE *fstream = NULL;
    char buff[1024] = {0};

    if (NULL == (fstream = popen("ps -aux | grep test3-2-2 | grep -v grep | awk '{print $2}'", "r")))
    {
        fprintf(stderr,"execute command failed: %s", strerror(errno));
        return -1;
    }
    while (NULL != fgets(buff, sizeof(buff), fstream))
    {
        if (strlen(buff) > 0)
        {
            ret = atoi(buff); // string to int
        }
    }
    pclose(fstream);
    return ret;
}

int main(int argc, char **argv)
{
    my_daemon();

    int num47 = 0;
    int num53 = 0;

    while (1)
    {
        int pid = isRunning();
        if (pid < 0)
        {
            cout << "未探测到test3-2-2" << endl;
            sleep(1);
            continue;
        }
        if (num47 < 9)
        {
            num47++;
            kill(pid, MY_SIGN_CONTINUE);
            sleep(1);
            continue;
        }
        else if (num53 < 1)
        {
            num53++;
            kill(pid, MY_SIGN_EXIT);
            cout << "进程test3-2-1退出" << endl;
            break;
        }
        else
        {
            break;
        }
    }

    return 0;
}