#include "displayinfo.h"
#include "ui_displayinfo.h"
#include "allclass.h"
#include <QFont>
#include <QString>
#include <QDebug>

extern book_shelf library;

displayinfo::displayinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::displayinfo)
{
    ui->setupUi(this);

    for(int i=0;i<(int)library.suclient.size();i++)
    {
        ui->textEdit->append("\n\n姓名："+QString::fromStdString(library.suclient[i].name));
        if(library.suclient[i].client_identity==0)
            ui->textEdit->append("身份：教师");
        else if(library.suclient[i].client_identity==2)
            ui->textEdit->append("身份：管理员");
        else
            ui->textEdit->append("身份：学生");

        cout<<"\tinstitute:"<<library.suclient[i].institute<<"\tcreattime:"<<library.suclient[i].creat_time
            <<"\tid:"<<library.suclient[i].clid<<"\thonest tevel:"<<library.suclient[i].honestlevel;
        ui->textEdit->append("学院："+QString::fromStdString(library.suclient[i].institute));
        ui->textEdit->append("创建时间："+QString::number(library.suclient[i].creat_time));
        ui->textEdit->append("用户ID："+QString::fromStdString(library.suclient[i].clid));
        ui->textEdit->append("诚信等级："+QString::number(library.suclient[i].honestlevel));
        double money = 0-library.suclient[i].Arrears_money;
        ui->textEdit->append("账户余额："+QString::number(money));
        ui->textEdit->append("借书数量："+QString::number(library.suclient[i].borrownum));
        if(library.suclient[i].borrownum>0)
        {
            for(int k=0; k<library.suclient[i].borrownum; k++)
            {//displaybook(id_to_book(cl_id.borrowid[i]));
                ui->textEdit->append(QString::number(k)+".ID："+QString::fromStdString(library.suclient[i].borrowid[k])
                                      +"   书名："+QString::fromStdString(library.id_to_book(library.suclient[i].borrowid[k]).name)
                                      +"   作者："+QString::fromStdString(library.id_to_book(library.suclient[i].borrowid[k]).author)
                                      +"   出版社："+QString::fromStdString(library.id_to_book(library.suclient[i].borrowid[k]).press));
            }
        }
        ui->textEdit->append("预约数量："+QString::number(library.suclient[i].orderbooknum));
        if(library.suclient[i].orderbooknum>0)
        {
            cout<<"you have ordered "<<library.suclient[i].orderbooknum<<"book,interesting!"<<endl;
            for(int j=0; j<library.suclient[i].orderbooknum; j++)
            {
                if(library.id_to_book(library.suclient[i].orderbookid[j]).state==1)
                    ui->textEdit->append(QString::number(j)+".ID："+QString::fromStdString(library.suclient[i].orderbookid[j])
                                         +"   书名："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).name)
                                         +"   作者："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).author)
                                         +"   出版社："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).press)
                                         +"该书现在在库");
                else if(library.id_to_book(library.suclient[i].orderbookid[j]).state==2)
                    ui->textEdit->append(QString::number(j)+".ID："+QString::fromStdString(library.suclient[i].orderbookid[j])
                                         +"   书名："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).name)
                                         +"   作者："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).author)
                                         +"   出版社："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).press)
                                         +"该书被移出馆内");
                else if(library.id_to_book(library.suclient[i].orderbookid[j]).state==0)
                    ui->textEdit->append(QString::number(j)+".ID："+QString::fromStdString(library.suclient[i].orderbookid[j])
                                         +"   书名："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).name)
                                         +"   作者："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).author)
                                         +"   出版社："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).press)
                                         +"该书被他人借走");
            }
        }
    }
    ui->textEdit->moveCursor(QTextCursor::Start);
}

displayinfo::~displayinfo()
{
    delete ui;
}

void displayinfo::on_search_clicked()
{
    ui->textEdit->clear();
    QString ID = ui->lineEdit->text();

    boclient client = library.id_to_client(ID.toStdString());

    ui->textEdit->append("\n\n姓名："+QString::fromStdString(client.name));
    if(client.client_identity==0)
        ui->textEdit->append("身份：教师");
    else if(client.client_identity==2)
        ui->textEdit->append("身份：管理员");
    else
        ui->textEdit->append("身份：学生");

    ui->textEdit->append("学院："+QString::fromStdString(client.institute));
    ui->textEdit->append("创建时间："+QString::number(client.creat_time));
    ui->textEdit->append("用户ID："+QString::fromStdString(client.clid));
    ui->textEdit->append("诚信等级："+QString::number(client.honestlevel));
    double money = 0-client.Arrears_money;
    ui->textEdit->append("账户余额："+QString::number(money));
    ui->textEdit->append("借书数量："+QString::number(client.borrownum));
    if(client.borrownum>0)
    {
        for(int k=0; k<client.borrownum; k++)
        {//displaybook(id_to_book(cl_id.borrowid[i]));
            ui->textEdit->append(QString::number(k)+".ID："+QString::fromStdString(client.borrowid[k])
                                  +"   书名："+QString::fromStdString(library.id_to_book(client.borrowid[k]).name)
                                  +"   作者："+QString::fromStdString(library.id_to_book(client.borrowid[k]).author)
                                  +"   出版社："+QString::fromStdString(library.id_to_book(client.borrowid[k]).press));
        }
    }
    ui->textEdit->append("预约数量："+QString::number(client.orderbooknum));
    if(client.orderbooknum>0)
    {
        for(int j=0; j<client.orderbooknum; j++)
        {
            if(library.id_to_book(client.orderbookid[j]).state==1)
                ui->textEdit->append(QString::number(j)+".ID："+QString::fromStdString(client.orderbookid[j])
                                     +"   书名："+QString::fromStdString(library.id_to_book(client.orderbookid[j]).name)
                                     +"   作者："+QString::fromStdString(library.id_to_book(client.orderbookid[j]).author)
                                     +"   出版社："+QString::fromStdString(library.id_to_book(client.orderbookid[j]).press)
                                     +"该书现在在库");
            else if(library.id_to_book(client.orderbookid[j]).state==2)
                ui->textEdit->append(QString::number(j)+".ID："+QString::fromStdString(client.orderbookid[j])
                                     +"   书名："+QString::fromStdString(library.id_to_book(client.orderbookid[j]).name)
                                     +"   作者："+QString::fromStdString(library.id_to_book(client.orderbookid[j]).author)
                                     +"   出版社："+QString::fromStdString(library.id_to_book(client.orderbookid[j]).press)
                                     +"该书被移出馆内");
            else if(library.id_to_book(client.orderbookid[j]).state==0)
                ui->textEdit->append(QString::number(j)+".ID："+QString::fromStdString(client.orderbookid[j])
                                     +"   书名："+QString::fromStdString(library.id_to_book(client.orderbookid[j]).name)
                                     +"   作者："+QString::fromStdString(library.id_to_book(client.orderbookid[j]).author)
                                     +"   出版社："+QString::fromStdString(library.id_to_book(client.orderbookid[j]).press)
                                     +"该书被他人借走");
        }
    }
    ui->textEdit->moveCursor(QTextCursor::Start);
}

void displayinfo::on_allinfo_clicked()
{
    ui->textEdit->clear();
    for(int i=0;i<(int)library.suclient.size();i++)
    {
        ui->textEdit->append("\n\n姓名："+QString::fromStdString(library.suclient[i].name));
        if(library.suclient[i].client_identity==0)
            ui->textEdit->append("身份：教师");
        else if(library.suclient[i].client_identity==2)
            ui->textEdit->append("身份：管理员");
        else
            ui->textEdit->append("身份：学生");

        cout<<"\tinstitute:"<<library.suclient[i].institute<<"\tcreattime:"<<library.suclient[i].creat_time
            <<"\tid:"<<library.suclient[i].clid<<"\thonest tevel:"<<library.suclient[i].honestlevel;
        ui->textEdit->append("学院："+QString::fromStdString(library.suclient[i].institute));
        ui->textEdit->append("创建时间："+QString::number(library.suclient[i].creat_time));
        ui->textEdit->append("用户ID："+QString::fromStdString(library.suclient[i].clid));
        ui->textEdit->append("诚信等级："+QString::number(library.suclient[i].honestlevel));
        double money = 0-library.suclient[i].Arrears_money;
        ui->textEdit->append("账户余额："+QString::number(money));
        ui->textEdit->append("借书数量："+QString::number(library.suclient[i].borrownum));
        if(library.suclient[i].borrownum>0)
        {
            for(int k=0; k<library.suclient[i].borrownum; k++)
            {//displaybook(id_to_book(cl_id.borrowid[i]));
                ui->textEdit->append(QString::number(k)+".ID："+QString::fromStdString(library.suclient[i].borrowid[k])
                                      +"   书名："+QString::fromStdString(library.id_to_book(library.suclient[i].borrowid[k]).name)
                                      +"   作者："+QString::fromStdString(library.id_to_book(library.suclient[i].borrowid[k]).author)
                                      +"   出版社："+QString::fromStdString(library.id_to_book(library.suclient[i].borrowid[k]).press));
            }
        }
        ui->textEdit->append("预约数量："+QString::number(library.suclient[i].orderbooknum));
        if(library.suclient[i].orderbooknum>0)
        {
            cout<<"you have ordered "<<library.suclient[i].orderbooknum<<"book,interesting!"<<endl;
            for(int j=0; j<library.suclient[i].orderbooknum; j++)
            {
                if(library.id_to_book(library.suclient[i].orderbookid[j]).state==1)
                    ui->textEdit->append(QString::number(j)+".ID："+QString::fromStdString(library.suclient[i].orderbookid[j])
                                         +"   书名："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).name)
                                         +"   作者："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).author)
                                         +"   出版社："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).press)
                                         +"该书现在在库");
                else if(library.id_to_book(library.suclient[i].orderbookid[j]).state==2)
                    ui->textEdit->append(QString::number(j)+".ID："+QString::fromStdString(library.suclient[i].orderbookid[j])
                                         +"   书名："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).name)
                                         +"   作者："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).author)
                                         +"   出版社："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).press)
                                         +"该书被移出馆内");
                else if(library.id_to_book(library.suclient[i].orderbookid[j]).state==0)
                    ui->textEdit->append(QString::number(j)+".ID："+QString::fromStdString(library.suclient[i].orderbookid[j])
                                         +"   书名："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).name)
                                         +"   作者："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).author)
                                         +"   出版社："+QString::fromStdString(library.id_to_book(library.suclient[i].orderbookid[j]).press)
                                         +"该书被他人借走");
            }
        }
    }

    ui->textEdit->moveCursor(QTextCursor::Start);
}
