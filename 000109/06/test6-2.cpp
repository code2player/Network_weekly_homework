
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

void sub(int size)
{
    char *str = (char *)malloc(size * 1024 * 1024 * sizeof(char));
    if (str != NULL)
    {
        cout << "申请成功" << endl;
        int i;
        for (i = 0; i < size * 1024 * 1024 * sizeof(char); i++)
        {
            str[i] = rand() % 256;
        }
        free(str);
    }
    else
    {
        cout << "申请失败" << endl;
    }

    /*while(1){
        ;
    }*/
}

/*统一使用的参数处理函数*/
int parameter_process(int argc, char **argv, para_need &pn)
{
    //argc从1开始算（0处为可执行文件名）
    if (argc != pn.para_num * 2+1)
    {
        cout << "参数缺少或过多" << endl;
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