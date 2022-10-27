
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

void sub(int size)
{
    char *str = (char *)malloc(size * 1024 * 1024 * sizeof(char));
    if (str != NULL)
    {
        cout << "����ɹ�" << endl;
        int i;
        for (i = 0; i < size * 1024 * 1024 * sizeof(char); i++)
        {
            str[i] = rand() % 256;
        }
        free(str);
    }
    else
    {
        cout << "����ʧ��" << endl;
    }

    /*while(1){
        ;
    }*/
}

/*ͳһʹ�õĲ���������*/
int parameter_process(int argc, char **argv, para_need &pn)
{
    //argc��1��ʼ�㣨0��Ϊ��ִ���ļ�����
    if (argc != pn.para_num * 2+1)
    {
        cout << "����ȱ�ٻ����" << endl;
        return -1;
    }

    for (int i = 1; i < argc;i+=2)
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
                        if (strcmp(argv[i + 1], "yes") == 0||strcmp(argv[i + 1], "Yes") == 0)
                        {
                            pn.para[j].para_value = 1;
                        }
                        else if (strcmp(argv[i + 1], "no") == 0||strcmp(argv[i + 1], "No") == 0)
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

int main(int argc, char **argv)
{

    srand(time(0));
    para_need pn;
    pn.para_num=1;
    pn.para[0].para_name="size";
    pn.para[0].para_type="int";

    


    int ret=parameter_process(argc,argv,pn);
    if(ret<0)
    return 0;

    int size=pn.para[0].para_value;

    sub(size);
    
    return 0;
}