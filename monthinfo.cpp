#include "monthinfo.h"
#include "ui_monthinfo.h"
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <math.h>
#include "allclass.h"
using namespace std;
monthinfo::monthinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::monthinfo)
{
    ui->setupUi(this);
}

monthinfo::~monthinfo()
{
    delete ui;
}

extern book_shelf library;

void monthinfo::play()
{
    int bonum,renum,unret,monu;//统计借书量，还书量，没换书的数目，营业额
    bonum=0;
    renum=0;
    unret=0;
    monu=0;
    qDebug("Do there");
    qDebug()<<library.bor_record.size();
    int total=0;
    for(int i=0;i<(int)library.bor_record.size();i++)
    {
        if((library.bor_record[i].type_comm==1)&&(library.book_system_time-library.bor_record[i].bor_time<300))
        {
            cout<<library.id_to_book(library.bor_record[i].bor_book_id).name<<"被借"<<endl;
            ui->textEdit->append(QString::fromStdString(library.id_to_book(library.bor_record[i].bor_book_id).name)+"被借");
            library.id_to_book(library.bor_record[i].bor_book_id).num++;
            total++;
            cout<<"借书人ID："<<library.bor_record[i].bor_client_id<<endl;
            ui->textEdit->append("借书人ID："+QString::fromStdString(library.bor_record[i].bor_client_id)+
                                 "   姓名："+QString::fromStdString(library.id_to_client(library.bor_record[i].bor_client_id).name)+"\n");
            ++bonum;
        }
        if((library.bor_record[i].type_comm==1)&&((library.book_system_time-library.bor_record[i].retu_book<300)))
        {
            cout<<library.id_to_book(library.bor_record[i].bor_book_id).name<<"被还"<<endl;
            ui->textEdit->append(QString::fromStdString(library.id_to_book(library.bor_record[i].bor_book_id).name)+"被还");
            cout<<"还书人ID："<<library.bor_record[i].bor_client_id<<endl;
            ui->textEdit->append("还书人ID："+QString::fromStdString(library.bor_record[i].bor_client_id)+
                                 "   姓名："+QString::fromStdString(library.id_to_client(library.bor_record[i].bor_client_id).name)+"\n");
            ++renum;
        }
        if(library.bor_record[i].retu_book==0 && library.bor_record[i].type_comm == 1)
        {
            cout<<library.id_to_book(library.bor_record[i].bor_book_id).name<<"未被还"<<endl;
            ui->textEdit->append(QString::fromStdString(library.id_to_book(library.bor_record[i].bor_book_id).name)+"未被还");
            cout<<"借书人ID："<<library.bor_record[i].bor_client_id<<endl;
            ui->textEdit->append("借书人ID："+QString::fromStdString(library.bor_record[i].bor_client_id)+
                                 "   姓名："+QString::fromStdString(library.id_to_client(library.bor_record[i].bor_client_id).name)+"\n");
            ++unret;
        }
        monu=monu+library.bor_record[i].bookfine;
    }
    cout<<"本月被借走的书的数量:"<<bonum<<endl;
    cout<<"本月被还回的书的数量:"<<renum<<endl;
    cout<<"还未被还回的书的数量:"<<unret<<endl;
    cout<<"本月罚款收入:"<<monu<<endl;

    ui->textEdit->append("当月被借走的书的数量："+QString::number(bonum));
    ui->textEdit->append("当月被还回的书的数量："+QString::number(renum));
    ui->textEdit->append("当未被还回的书的数量："+QString::number(unret));
    ui->textEdit->append("当月罚款收入："+QString::number(monu)+"\n");

    float rate=0.2;
    qDebug()<<rate;
    QString str;
    for(int i = 0;i<=library.booklib.size();++i)
    {
        if(library.booklib[i].num!=0)
        {
            int num =library.booklib[i].num;
            rate = (float)num/total;
            qDebug()<<library.booklib[i].num;
            qDebug()<<total;
            qDebug()<<rate;
            ui->textEdit->append(QString::fromStdString(library.booklib[i].name)+"被借"+QString::number(library.booklib[i].num)+"次，借阅率："+str.setNum(rate,'g',3));
        }
        library.booklib[i].num=0;
    }
    qDebug()<<total;
    total=0;
}
