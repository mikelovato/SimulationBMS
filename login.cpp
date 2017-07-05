#include "login.h"
#include "ui_login.h"
#include "studentinterface.h"
#include "teacherinterface.h"
#include "QMessageBox"
#include "allclass.h"
#include <QString>
#include <string>
#include <QDebug>
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

bool isTeacher(QString ID, QString password);
bool isStudent(QString ID, QString password);

extern book_shelf library;
string str;                               //当前登录用户名
void Login::on_loginBtn_clicked()
{
    if(isTeacher(ui->usrLineEdit->text(),ui->pwdLineEdit->text()))                      //判断键入的身份信息是否为管理员
    {
        TeacherInterface *teacherinterface = new TeacherInterface();
        QLabel *label = new QLabel(teacherinterface);
        QFont ft;
        ft.setPointSize(13);
        label->setFont(ft);
        str = ui->usrLineEdit->text().toStdString();
        QString str1 = QString::fromStdString(library.id_to_client(str).name);
        label->setText(QObject::tr("欢迎你：")+str1);
        teacherinterface->show();
        this->close();
    }
    else if(isStudent(ui->usrLineEdit->text(),ui->pwdLineEdit->text()))                      //判断键入的身份信息是否为用户
    {
        StudentInterface *studentinterface = new StudentInterface();
        qDebug()<<library.book_system_time;
        studentinterface->orderTip(ui->usrLineEdit->text(),library.book_system_time);
        QLabel *label = new QLabel(studentinterface);
        QFont ft;
        ft.setPointSize(13);
        label->setFont(ft);
        str = ui->usrLineEdit->text().toStdString();
        QString str1 = QString::fromStdString(library.id_to_client(str).name);
        label->setText(QObject::tr("欢迎你：")+str1);
        studentinterface->show();
        this->close();
    }
    else
    {
        QMessageBox::warning(this, tr("警告！"),
                           tr("用户名或密码错误！"),
                           QMessageBox::Yes);
    }
}

bool isTeacher(QString ID, QString password)                                 //判断是否为管理员账号
{
    for(int i=0; i< library.suclient.size();++i)
    {
        QString q1 = QString::fromStdString(library.suclient[i].clid);
        QString q2 = QString::fromStdString(library.suclient[i].cli_pass_word);
        if(!QString::compare(ID,q1) && !QString::compare(password,q2) && library.suclient[i].client_identity == 2)
            return true;
    }
    return false;
}

bool isStudent(QString ID, QString password)                                //判断是否为用户账号
{
    for(int i=0; i< library.suclient.size();++i)
    {
        QString q1 = QString::fromStdString(library.suclient[i].clid);
        QString q2 = QString::fromStdString(library.suclient[i].cli_pass_word);
        if(!QString::compare(ID,q1) && !QString::compare(password,q2) && library.suclient[i].client_identity == 1)
            return true;
    }
    return false;
}

void Login::on_exitBtn_clicked()
{
    library.booklib.clear();
    library.bor_record.clear();
    library.suclient.clear();
}
