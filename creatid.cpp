#include "creatid.h"
#include "ui_creatid.h"
#include "QMessageBox"
#include "allclass.h"
#include <string>
#include <QString>
#include <QDebug>

creatid::creatid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creatid)
{
    ui->setupUi(this);
}

creatid::~creatid()
{
    delete ui;
}

int stringtoint1(string s);

extern book_shelf library;

void creatid::on_pushButton_clicked()
{
    string name = ui->name->text().toStdString();
    string password = ui->password->text().toStdString();
    string identity = ui->identity->text().toStdString();
    string institute = ui->institute->currentText().toStdString();
    QString clientname = ui->name->text();
    QString clientpassword = ui->password->text();
    QString clientidentity = ui->identity->text();
    QString clientinstitute = ui->institute->currentText();

    int iden = stringtoint1(identity);

    if(clientname == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请输入用户名！"),
                           QMessageBox::Yes);

    else if(clientpassword == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请输入用密码！"),
                           QMessageBox::Yes);

    else if(clientidentity == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请输入用户身份信息！"),
                           QMessageBox::Yes);

    else if(clientinstitute == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请输入用户x学院信息！"),
                           QMessageBox::Yes);

    else
    {
        library.new_client(name,password,iden,institute);
        QMessageBox::warning(this, tr("提示！"),
                           tr("用户添加成功！"),
                           QMessageBox::Yes);
        this->close();
    }
}

int stringtoint1(string s)//基本函数
{
    int num;
    stringstream ss(s);
    ss>>num;
    return num;
}
