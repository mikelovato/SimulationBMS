
#ifndef ALLCLASS_H
#define ALLCLASS_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <windows.h>
#include <string.h>
#include <vector>

using namespace std;

typedef struct book_singal                   //书结构,全部是静态信息
{
    string type;                             //书的类型
    int buytime;                             //书的购买时间，也就是书被录入图书馆的时间
    string name;                             //书名
    string author;                           //书的作者
    string press;                            //出版社
    double price;                            //书价格
    int borrowpermission;                    //书的借阅权限，1代表老师和学生均可以借阅，0代表只有老师可以借阅
    int state;                               //书的状态，1代表该书还在图书馆中，0代表该书已被借阅,2代表已经删除,3被预约
    string id;                               //书的编号，由code()函数生成
    void introduction();                      //书的简介，生成不用输入
} sinbook;



typedef struct lib_client
{
    //人员结构
    string name;                            //客户姓名
    string cli_pass_word;                    //客户密码
    int client_identity;                    //身份信息用来区分老师和学生，0代表老师，1代表学生,2代表管理员
    string institute;                       //客户所在学院
    int creat_time;                          //账户创建时间
    int borrownum;                          //客户已借阅图书数量
    string borrowid[5];                     //客户已借图书的id
    int orderbooknum;
    string orderbookid[5];                   //预约的图书ID
    double Arrears_money;                     //借书欠款
    int honestlevel;                         //诚信等级
    string clid;                              //id
} boclient;

typedef struct lib_comm_list
{
    string bor_book_id;                       //借书的id/预约的id
    string bor_client_id;                     //借书人的id
    int bor_time;                              //借书的时间/预约时间
    int bor_term;                               //借书时长/预约时间
    string bor_way;                               //借书方式（管理员/用户）/预约方式（管理员/用户自己）
    int bookfine;                               //产生罚款/预约不填
    int retu_book;                              //还书没？还书保存还书时间.没换0/预约过期或者失效了失效时间
    int type_comm;                              //借书还是预约,借书1，预约2
} borrow_mass;


class book_shelf
{
private:


public:
    int book_system_time;           //全局变量，时间，世界通用
    int Cur_log_denti=0;               //全局变量，当前登陆区分，1表示管理员，0表示没有登陆，client登陆值是读者编号的int类型
    book_shelf();                             //构造函数
    ~book_shelf();                            //析构函数
    vector<sinbook> booklib;                 //书的总数量
    void buybook(string booktype,string bookname,string bookauther,int booknum,string bookpress,double bookprice,int bookpermission);                          //图书入库
    //void initializebook();                   //从文件初始化图书
    void renewbook(string renewid,int renew_choice);                        //更新修改信息
    void recharge(string clientID,double money);                               //充值金额
    void search_book_shelf(int num,string inf);         //查询模块
    sinbook & id_to_book(string bokide);            //根据bookid返回book

    vector<boclient> suclient;          //存人员信息
    void new_client(string name,string password,int iden,string institute);                        //加入人员
    //void initializecli();                    //初始化
    void renewclient(string renewid,int renew_choice);                       //更新人员信息
    void search_client_inf(int num,string inf);       //查询模块
    boclient & id_to_client(string cli_gr);             //根据id返回人员

    //借书模块
    vector<borrow_mass> bor_record;                    //交易记录
    void statistic();                                   //交易记录本月统计
    void borr_book(string bookid,string clinid,int days);       //借书
    void back_book(string bookid);                                  //还书
    void order_book(string bookid, string clinid);                                 //预约
    void order_dele_book(string clinid);                            //预约显示
    void delet_book(string bookid);                                         //删除
    int judg_ord_suc(string okid,string inid);      //判断有没有预约书


    //显示模块
    void displaybook(sinbook boid);                      //显示书，一本
    void displaybook();                                  //显示所有书
    void display_client(boclient cl_id);                 //显示顾客
    void display_client();                               //显示所有顾客
};


#endif
