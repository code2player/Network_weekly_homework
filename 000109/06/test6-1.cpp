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

/*para_needΪ���صĲ���*/
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

    //pid=0, �ǵ�һ�ӽ��̣���̨����ִ��
    setsid(); //��һ�ӽ��̳�Ϊ�µĻỰ�鳤�ͽ����鳤
    //��������ն˷���
    /*if ((pid = fork()))
        exit(0); //�ǵ�һ�ӽ��̣�������һ�ӽ���
    else if (pid < 0)
        exit(1); // forkʧ�ܣ��˳�*/
    //�ǵڶ��ӽ��̣�����
    //�ڶ��ӽ��̲����ǻỰ�鳤

    /*int i;
    for (i = 0; i < NOFILE; ++i) //�رմ򿪵��ļ���д������
        close(i);*/
    //NOFILE=3,���������ļ��ı�׼/�����������

    //chdir("/tmp"); //�˴����ı乤���ļ��е�/tmp
    //umask(0);      //�����ļ�������ģ
    
    return;
}

/*ͳһʹ�õĲ���������*/
int parameter_process(int argc, char **argv, para_need &pn)
{
    // argc��1��ʼ�㣨0��Ϊ��ִ���ļ�����
    if (argc != pn.para_num * 2 + 1)
    {
        cout << "����ȱ�ٻ����" << endl;
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
                            cout << "��������" << endl;
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
            //�����ϲ�Ӧ�ý��루��һ������һ�ֵ�����£����ܻ�����Ҫ���������������ٽ��д���
            i++;
            cout << "��������" << endl;
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
        cout << "�����ڴ�ʧ��" << endl;
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
        if (pid > 0) //�����̼���
        {
            if (i % pnum == 0)
            {
                printf("�ѷ���%d���ӽ���\n", i);
            }
        }
        else if (pid < 0) //�����ӽ���ʧ��
        {
            printf("�����ӽ���ʧ��\n");
            while (1)
            {
                sleep(1);
            }
        }
        else //�ӽ���
        {
            sub(size, init);
        }
    }

    return 0;
}