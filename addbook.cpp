#include "addbook.h"
#include "ui_addbook.h"
#include "allclass.h"
#include <QMessageBox>
#include <QDebug>

AddBook::AddBook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBook)
{
    ui->setupUi(this);
}

AddBook::~AddBook()
{
    delete ui;
}

extern book_shelf library;

void AddBook::on_pushButton_clicked()
{
    QString booktype = ui->booktype->currentText();
    QString bookname = ui->bookname->text();
    QString bookauther = ui->bookauther->text();
    QString booknum = ui->booknum->text();
    QString bookpress = ui->press->text();
    QString bookprice = ui->bookprice->text();
    QString bookpermission = ui->bookpermission->text();

    string type = booktype.toStdString();
    string name = bookname.toStdString();
    string auther = bookauther.toStdString();
    int num = booknum.toInt();
    string press = bookpress.toStdString();
    double price = bookprice.toDouble();
    int permission = bookpermission.toInt();

    if(booktype == NULL)
        QMessageBox::warning(this, tr("提示！"),
                    tr("请输入书类型！"),
                    QMessageBox::Yes);
    else if(bookname == NULL)
        QMessageBox::warning(this, tr("提示！"),
                    tr("请输入书名！"),
                    QMessageBox::Yes);
    else if(bookauther == NULL)
        QMessageBox::warning(this, tr("提示！"),
                    tr("请输入书作者！"),
                    QMessageBox::Yes);
    else if(booknum == NULL)
        QMessageBox::warning(this, tr("提示！"),
                    tr("请输入书数量！"),
                    QMessageBox::Yes);
    else if(bookpress == NULL)
        QMessageBox::warning(this, tr("提示！"),
                    tr("请输入出版社！"),
                    QMessageBox::Yes);
    else if(bookprice == NULL)
        QMessageBox::warning(this, tr("提示！"),
                    tr("请输入书价格！"),
                    QMessageBox::Yes);
    else if(bookpermission == NULL)
        QMessageBox::warning(this, tr("提示！"),
                    tr("请输入书借阅权限！"),
                    QMessageBox::Yes);
    else
    {
        library.buybook(type,name,auther,num,press,price,permission);
        QMessageBox::warning(this, tr("提示！"),
                    tr("添加成功！"),
                    QMessageBox::Yes);
        this->close();
    }

}
