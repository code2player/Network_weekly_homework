//mysql_demo.cpp
#include <iostream>	// cin,cout��
#include <iomanip>  // setw��
#include <mysql.h>  // mysql����
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

int sub(MYSQL *mysql)
{

    MYSQL_RES *result;
    MYSQL_ROW row;

    /* ���в�ѯ���ɹ�����0�����ɹ���0
       1����ѯ�ַ��������﷨����
       2����ѯ�����ڵ����ݱ� */
    if (mysql_query(mysql, "select * from student"))
    {
        for (;;)
        {
            sleep(1);
        }
        // cout << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* ����ѯ����洢���������ִ����򷵻�NULL
       ע�⣺��ѯ���ΪNULL�����᷵��NULL */
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        for (;;)
        {
            sleep(1);
        }
        // cout << "mysql_store_result failed" << endl;
        return -1;
    }

    /* ��ӡ��ǰ��ѯ���ļ�¼������ */
    // cout << "select return " << (int)mysql_num_rows(result) << " records" << endl;

    /* ѭ����ȡ�������������ļ�¼
       1�����ص���˳����selectָ������˳����ͬ����row[0]��ʼ
       2���������ݿ�����ʲô���ͣ�C�ж��������ַ��������д�������б�Ҫ����Ҫ�Լ�����ת��
       3�������Լ�����Ҫ��֯�����ʽ */
    while ((row = mysql_fetch_row(result)) != NULL)
    {
        ;
        /* cout << setiosflags(ios::left);             //��������
         cout << "ѧ�ţ�" << setw(12) << row[0];     //���12λ�������
         cout << "������" << setw(8)  << row[1];     //    8
         cout << "�Ա�" << setw(4)  << row[2];     //    4
         cout << "���䣺" << setw(4)  << row[3];     //    4
         cout << "ϵ����" << setw(4)  << row[4];     //    4
         cout << endl;*/
    }

    /* �ͷ�result */
    mysql_free_result(result);

    for (;;)
    {
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    my_daemon();
    MYSQL *mysql;
    /* ��ʼ�� mysql ������ʧ�ܷ���NULL */
    if ((mysql = mysql_init(NULL)) == NULL)
    {
         cout << "mysql_init failed" << endl;
        return -1;
    }

    /* �������ݿ⣬ʧ�ܷ���NULL
       1��mysqldû����
       2��û��ָ�����Ƶ����ݿ���� */
    if (mysql_real_connect(mysql, "127.0.0.1", "root", "root123", "demo", 0, NULL, 0) == NULL)
    {
         cout << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
        return -1;
    }

    /* �����ַ���������������ַ����룬��ʹ/etc/my.cnf������Ҳ���� */
    mysql_set_character_set(mysql, "gbk");

    para_need pn;
    pn.para_num = 2;
    pn.para[0].para_name = "fnum";
    pn.para[0].para_type = "int";
    pn.para[1].para_name = "pnum";
    pn.para[1].para_type = "int";

    int ret = parameter_process(argc, argv, pn);
    if (ret < 0)
        return 0;

    int fnum = pn.para[0].para_value;
    int pnum = pn.para[1].para_value;
    int i;
    for (i = 0; i < fnum; i++)
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
            exit(1);
        }
        else //�ӽ���
        {
            sub(mysql);
        }
    }

    if (i % pnum == 0)
    {
        printf("�ѷ���%d���ӽ���\n", i);
    }

    while (1)
    {
        sleep(1);
    }

    /* �ر��������� */
    mysql_close(mysql);  

    return 0;
}