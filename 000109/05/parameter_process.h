#pragma once
#include <string>
using namespace std;

//������������������
class st_para{
public:
    string para_name;
    string para_type;

    int para_whe_have_default;//�Ƿ���룬0��������(��default)��1������
    int para_value_default;//int bool��value����(ȱʡ)
    string para_string_default;//string��value����(ȱʡ)

    int para_whe_have_value;//�Ƿ���ֵ��0��û�У�1����
    int para_value;//int bool��value����, ������ֵ�������Ƿ���ڣ�0�������ڣ�1������
    string para_string;//string��value����

    int para_whe_have_range;//�Ƿ��з�Χ��ֻ��int����Ч����0��û�У�1����
    int min_range;//��Сֵ
    int max_range;//���ֵ

    st_para(){
        para_name="";
        para_type="int";
        para_whe_have_default=1;
        para_value_default=0;
        para_string_default="";
        para_whe_have_value=1;
        para_value=0;
        para_string="";
        para_whe_have_range=0;
        min_range=0;
        min_range=0;
    }
};

/*para_needΪ���صĲ���,���в����ļ���*/
class para_need{
public:
    int para_num;
    /*string para_name[3];
    int para[3];*/
    st_para para[20];

    /*һ���趨������num*/
    void set_name_type(int num,string para_name,string para_type);
    void set_default(int num,int para_whe_have_default,int para_value_default,string para_string_default);
    void set_value(int num,int para_whe_have_value,int para_value,string para_string);
    void set_range(int num,int para_whe_have_range,int min_range,int max_range);
};
int parameter_process(int argc, char **argv, para_need &pn);