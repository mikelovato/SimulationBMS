#include "borrowbook.h"
#include "ui_borrowbook.h"
#include "QMessageBox"
#include "allclass.h"
#include <QApplication>

borrowbook::borrowbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrowbook)
{
    ui->setupUi(this);
}

borrowbook::~borrowbook()
{
    delete ui;
}

bool isBook(QString bookID);
bool isClient(QString clientid);

extern book_shelf library;
extern int owetoomuch;                     //为1表示欠款太多
extern int borrowtoomuch;                  //为1表示借书过量
extern int notpower;                       //为1表示没有借书权限
extern int succeed;                        //为1表示借书成功
extern int nobook;                         //为1表示此书不存在或被借走
void borrowbook::on_pushButton_clicked()
{   
    QString str = ui->bookID->text();
    string bookid = str.toStdString();

    QString str1 = ui->clientID->text();
    string clientid = str1.toStdString();

    QString str2 = ui->borrowDay->text();
    int days = str2.toInt();

    if(str==NULL || !isBook(str))
        QMessageBox::warning(this,"警告！",
                               "请检查书ID！",
                               QMessageBox::Yes);



    else if(str1==NULL || !isClient(str1))
        QMessageBox::warning(this,"警告！",
                               "请检查用户ID！",
                               QMessageBox::Yes);



    else if(str2==NULL)
        QMessageBox::warning(this,"警告！",
                               "请输入天数！",
                               QMessageBox::Yes);
    else
    {

        library.borr_book(bookid,clientid,days);                              //调用借书函数

        if(owetoomuch)
        {
            QMessageBox::warning(this,"警告！",
                                               "您欠款过多！",
                                               QMessageBox::Yes);
            owetoomuch=0;
        }
        else if(borrowtoomuch)
        {
            QMessageBox::warning(this, "警告！",
                                                "您借书过多！",
                                                QMessageBox::Yes);
            borrowtoomuch = 0;
        }
        else if(notpower)
        {
            QMessageBox::warning(this, "提示！",
                                                "您没有权限借该书！",
                                                QMessageBox::Yes);
            notpower = 0;
        }
        else if(succeed)
        {
            QMessageBox::warning(this, "提示！",
                                                "借书成功！",
                                                QMessageBox::Yes);
            succeed=0;
            this->close();
        }
        else
            QMessageBox::warning(this,  "警告！",
                                                 "该书不存在或已被借走！",
                                                 QMessageBox::Yes);
    }

}

bool isClient(QString clientid)
{
    for(int i=0; i< library.suclient.size();++i)
    {
        QString q1 = QString::fromStdString(library.suclient[i].clid);
        if(!QString::compare(clientid,q1))
            return true;
    }
    return false;
}

bool isBook(QString bookID)
{
    for(int i = 0; i<library.booklib.size();++i)
    {
        QString q1 = QString::fromStdString(library.booklib[i].id);
        if(!QString::compare(bookID,q1))
            return true;
    }
    return false;
}
