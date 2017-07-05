#include "personalinfo.h"
#include "ui_personalinfo.h"
#include "allclass.h"
#include <QString>

personalinfo::personalinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::personalinfo)
{
    ui->setupUi(this);
}

personalinfo::~personalinfo()
{
    delete ui;
}

extern boclient client;
extern book_shelf library;
void personalinfo::play()
{
    QString name = QString::fromStdString(client.name);    //名字
    QString institute = QString::fromStdString(client.institute); //学院
    QString identity;                               //身份
    if(client.client_identity == 2)
        identity = "管理员";
    else if(client.client_identity == 1)
        identity = "学生";
    else
        identity = "教师";
    QString clientID = QString::fromStdString(client.clid);       //ID

    //string honest = inttostring1(client.honestlevel);
    QString honestlevel = QString().setNum(client.honestlevel);     //诚信等级
    double money = 0-client.Arrears_money;
    QString Arrears_money = QString().setNum(money);  //账户余额
    //string money = Arrears_money.toStdString();

    QString creat_time = QString::number(client.creat_time);            //创建时间
    QString borrownum = QString::number(client.borrownum);       //借书数量
    QString orderbooknum = QString::number(client.orderbooknum);  //预约数量
    QString borrow[5];
    for(int i=0;i<client.borrownum;++i)
        borrow[i]=QString::fromStdString(client.borrowid[i]);     //借书ID
    QString order[5];
    for(int i=0;i<client.orderbooknum;++i)
        order[i]=QString::fromStdString(client.orderbookid[i]);   //预约书ID

    ui->textEdit->append("姓名："+name);
    ui->textEdit->append("ID："+clientID);
    ui->textEdit->append("学院："+institute);
    ui->textEdit->append("诚信等级："+honestlevel);
    ui->textEdit->append("身份："+identity);
    ui->textEdit->append("账户余额："+Arrears_money);
    ui->textEdit->append("账户创建时间："+creat_time);
    ui->textEdit->append("借书数量："+borrownum);
    for(int i=0;i<client.borrownum;++i)
        ui->textEdit->append(QString::number(i)+".ID："+borrow[i]
                              +"   书名："+QString::fromStdString(library.id_to_book(client.borrowid[i]).name)
                              +"   作者："+QString::fromStdString(library.id_to_book(client.borrowid[i]).author)
                              +"   出版社："+QString::fromStdString(library.id_to_book(client.borrowid[i]).press));

    ui->textEdit->append("预约数量："+orderbooknum);
    for(int i=0;i<client.orderbooknum;++i)
        ui->textEdit->append(QString::number(i)+".ID："+order[i]
                              +"   书名："+QString::fromStdString(library.id_to_book(client.orderbookid[i]).name)
                              +"   作者："+QString::fromStdString(library.id_to_book(client.orderbookid[i]).author)
                              +"   出版社："+QString::fromStdString(library.id_to_book(client.orderbookid[i]).press));


}
