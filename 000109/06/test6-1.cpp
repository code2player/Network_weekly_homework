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

using namespace std;



struct st_para{
    string para_name;
    int para_value;
    string para_type;
};

/*para_need为返回的参数*/
struct para_need{
    int para_num;
    /*string para_name[3];
    int para[3];*/
    st_para para[20];
};

void my_daemon()
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

    //pid=0, 是第一子进程，后台继续执行
    setsid(); //第一子进程成为新的会话组长和进程组长
    //并与控制终端分离
    /*if ((pid = fork()))
        exit(0); //是第一子进程，结束第一子进程
    else if (pid < 0)
        exit(1); // fork失败，退出*/
    //是第二子进程，继续
    //第二子进程不再是会话组长

    /*int i;
    for (i = 0; i < NOFILE; ++i) //关闭打开的文件描写叙述符
        close(i);*/
    //NOFILE=3,代表三个文件的标准/错误输入输出

    //chdir("/tmp"); //此处不改变工作文件夹到/tmp
    //umask(0);      //重设文件创建掩模
    
    return;
}

/*统一使用的参数处理函数*/
int parameter_process(int argc, char **argv, para_need &pn)
{
    // argc从1开始算（0处为可执行文件名）
    if (argc != pn.para_num * 2 + 1)
    {
        cout << "参数缺少或过多" << endl;
        return -1;
    }

    for (int i = 1; i < argc; i += 2)
    {
        string str = argv[i];
        if (str.size() > 2 && str.substr(0, 2) == "--")
        {
            string strname = str.substr(2, str.size() - 2);
            for (int j = 0; j < pn.para_num; j++)
            {
                if (pn.para[j].para_name == strname)
                {
                    if (pn.para[j].para_type == "int")
                    {
                        pn.para[j].para_value = atoi(argv[i + 1]);
                    }
                    else if (pn.para[j].para_type == "bool")
                    {
                        if (strcmp(argv[i + 1], "yes") == 0 || strcmp(argv[i + 1], "Yes") == 0)
                        {
                            pn.para[j].para_value = 1;
                        }
                        else if (strcmp(argv[i + 1], "no") == 0 || strcmp(argv[i + 1], "No") == 0)
                        {
                            pn.para[j].para_value = 0;
                        }
                        else
                        {
                            cout << "参数错误" << endl;
                            return -1;
                        }
                    }
                    else
                    {
                        ;
                    }
                }
            }
        }
        else
        {
            //理论上不应该进入（在一个参数一种的情况下，可能会有需要额外参数的情况，再进行处理）
            i++;
            cout << "参数错误" << endl;
            return -1;
        }
    }

    return 1;
}

int sub(int size, int init)
{
    char *str = (char *)malloc(size * 1024 * sizeof(char));
    if (str != NULL && init == 1)
    {
        int i;
        for (i = 0; i < size * 1024 * sizeof(char); i++)
        {
            str[i] = rand() % 256;
        }
    }

    if (str == NULL)
    {
        cout << "申请内存失败" << endl;
    }

    for (;;)
    {
        sleep(1);
    }
}

int main(int argc, char **argv)
{
    my_daemon();
    srand(time(0));
    para_need pn;
    pn.para_num = 4;
    pn.para[0].para_name = "fnum";
    pn.para[0].para_type = "int";
    pn.para[1].para_name = "size";
    pn.para[1].para_type = "int";
    pn.para[2].para_name = "pnum";
    pn.para[2].para_type = "int";
    pn.para[3].para_name = "init";
    pn.para[3].para_type = "bool";

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;

    int fnum = pn.para[0].para_value;
    int size = pn.para[1].para_value;
    int pnum = pn.para[2].para_value;
    int init = pn.para[3].para_value;

    for (int i = 0; i < fnum; i++)
    {
        int pid = fork();
        if (pid > 0) //父进程继续
        {
            if (i % pnum == 0)
            {
                printf("已分裂%d个子进程\n", i);
            }
        }
        else if (pid < 0) //创建子进程失败
        {
            printf("分裂子进程失败\n");
            while (1)
            {
                sleep(1);
            }
        }
        else //子进程
        {
            sub(size, init);
        }
    }

    return 0;
}