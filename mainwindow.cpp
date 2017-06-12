#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "allclass.h"
#include <iostream>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->label->setPixmap(QPixmap("C:\\Users\\lenovo\\Desktop\\library.jpg"));
    this->setFixedSize(1000,600);
    this->setStyleSheet("background-image:url(C:\\Users\\lenovo\\Desktop\\library.jpg)");
    /*QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap("./images/library.jpg"));*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
extern book_shelf library;

int year;
int month;
int day;
void MainWindow::on_pushButton_clicked()
{
    library.booklib.clear();
    library.bor_record.clear();
    library.suclient.clear();

    string str;
    fstream fin1;
    fin1.open("C:\\Users\\lenovo\\Documents\\Test\\document\\time_single.txt",fstream::in);//对时间的保存
    if(fin1.is_open())
        qDebug("succeed");
    int time;
    getline(fin1,str);
    time = QString::fromStdString(str).toInt();
    getline(fin1,str);
    year = QString::fromStdString(str).toInt();
    qDebug()<<year;
    getline(fin1,str);
    month = QString::fromStdString(str).toInt();
    qDebug()<<month;
    getline(fin1,str);
    day = QString::fromStdString(str).toInt();
    qDebug()<<day;
    qDebug()<<"time:"<<time;
    library.book_system_time = time;
    fin1.clear();
    fin1.close();

    fstream fin;
    fin.open("C:\\Users\\lenovo\\Documents\\Test\\document\\book_she_text.txt",fstream::in);                         //读取图书基本信息
    sinbook temmem;
    while(!fin.eof())
    {
        getline(fin,str);
        getline(fin,temmem.type);   //读取图书类型
        getline(fin,str);
        fin>>temmem.buytime;         //读取图书购买时间
        getline(fin,str);
        getline(fin,str);
        getline(fin,temmem.name);   //读取书名
        /*QString str1 = QString::fromStdString(temmem.name);
        qDebug()<<str1;*/

        getline(fin,str);
        getline(fin,temmem.author);  //读取书的作者信息
        getline(fin,str);
        getline(fin,temmem.press);   //读取图书出版社
        getline(fin,str);
        fin>>temmem.price;           //读取图书价格
        //qDebug()<<temmem.price;
        getline(fin,str);
        getline(fin,str);
        fin>>temmem.borrowpermission; //读取图书借阅权限
        getline(fin,str);
        getline(fin,str);
        fin>>temmem.state;           //读取图书借阅状态
        getline(fin,str);
        getline(fin,str);
        getline(fin,temmem.id);      //读取图书ID
        getline(fin,str);
        temmem.num=0;
        library.booklib.push_back(temmem);//memory the information of temp book
    }
    fin.clear();
    fin.close();

    fstream dfin("C:\\Users\\lenovo\\Documents\\Test\\document\\client_he_text.txt",fstream::in);//人员信息
    boclient temclie;

    dfin.seekg(0,ios_base::end);
    int tmp=dfin.tellg();
    if(tmp!=0){
        dfin.seekg(0,ios_base::beg);

        while(!dfin.eof())
        {
            getline(dfin,str);
            getline(dfin,temclie.name);     //读取客户姓名
            getline(dfin,str);
            getline(dfin,temclie.cli_pass_word);//读取客户密码
            //QString str1 = QString::fromStdString(temclie.cli_pass_word);
            //()<<str1;
            getline(dfin,str);
            dfin>>temclie.client_identity;      //读取身份信息

            getline(dfin,str);
            getline(dfin,str);

            getline(dfin,temclie.institute);    //读取所在学院
            getline(dfin,str);
            dfin>>temclie.creat_time;           //读取账号创建时间
            getline(dfin,str);
            getline(dfin,str);
            dfin>>temclie.borrownum;            //读取借书数量
            getline(dfin,str);
            getline(dfin,str);
            if(temclie.borrownum>5||temclie.borrownum<-1)
                temclie.borrownum=0;
            for(int j=0; j<temclie.borrownum; j++)  //读取借书ID
            {
                getline(dfin,temclie.borrowid[j]);
            }
            getline(dfin,str);
            dfin>>temclie.orderbooknum;            //读取预约数量
            getline(dfin,str);
            getline(dfin,str);
            if(temclie.orderbooknum>5||temclie.orderbooknum<-1)
                temclie.orderbooknum=0;
            for(int j=0; j<temclie.orderbooknum; j++) //读取预约ID
               getline(dfin,temclie.orderbookid[j]);
            getline(dfin,str);
            dfin>>temclie.Arrears_money;          //读取客户借书欠款
            getline(dfin,str);
            getline(dfin,str);
            dfin>>temclie.honestlevel;            //读取诚信等级信息
            getline(dfin,str);
            getline(dfin,str);
            getline(dfin,temclie.clid);           //读取客户ID
            getline(dfin,str);
            library.suclient.push_back(temclie);
        }
    }
    dfin.clear();
    dfin.close();
    fstream gfin("C:\\Users\\lenovo\\Documents\\Test\\document\\log_file.txt");
    gfin.seekg(0,ios_base::end);
    int ewmp=gfin.tellg();
    if(ewmp!=0){
        gfin.seekg(0,ios_base::beg);

    borrow_mass temp_log;
    while (!gfin.eof())
    {
        getline(gfin, str);
        getline(gfin, temp_log.bor_book_id);   //读取书的ID
        getline(gfin, str);
        getline(gfin, temp_log.bor_client_id); //读取借书用户/预约用户ID
        getline(gfin, str);
        gfin >> temp_log.bor_time;             //读取借书时间/预约时间
        getline(gfin, str);
        getline(gfin, str);
        gfin >> temp_log.bor_term;             //读取借书时长/预约生效时间
        getline(gfin, str);
        getline(gfin, str);
        getline(gfin, temp_log.bor_way);       //读取借书方式
        getline(gfin, str);
        gfin >> temp_log.bookfine;             //读取产生罚款
        getline(gfin, str);
        getline(gfin, str);
        gfin >> temp_log.retu_book;            //读取书的借还状态
        getline(gfin, str);
        getline(gfin, str);
        gfin >> temp_log.type_comm;            //读取保存类型，借书还是预约
        getline(gfin, str);
        getline(gfin, str);
        //if((temp_log.type_comm==2)&&(temp_log.bor_time-book_system_time>temp_log.bor_term))
        //{
        //    temp_log.retu_book=book_system_time;
        //    cout<<temp_log.bor_client_id<<"order"<<temp_log.bor_book_id<<"have over time!"<<endl;
        //}
        library.bor_record.push_back(temp_log);
    }

    gfin.clear();
    gfin.close();
    }


    Login *lgn = new Login();
    lgn->show();
}
