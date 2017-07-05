#include "displaybookinfo.h"
#include "ui_displaybookinfo.h"
#include "allclass.h"
#include <QLabel>
#include <QString>
#include <string>

displaybookinfo::displaybookinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::displaybookinfo)
{
    ui->setupUi(this);
}

displaybookinfo::~displaybookinfo()
{
    delete ui;
}

extern book_shelf library;
extern sinbook book;
void displaybookinfo::play()
{
    QString type = QString::fromStdString(book.type);
    //QString buytime = QString::fromStdString(inttostring1(book.buytime));
    QString name = QString::fromStdString(book.name);
    QString auther = QString::fromStdString(book.author);
    QString press = QString::fromStdString(book.press);
    QString price = QString().setNum(book.price);
    QString permission = QString().setNum(book.borrowpermission);
    QString ID = QString::fromStdString(book.id);

    ui->textEdit->append("ID："+ID);
    ui->textEdit->append("书名："+name);
    ui->textEdit->append("类型："+type);
    ui->textEdit->append("作者："+auther);
    ui->textEdit->append("出版社："+press);
    ui->textEdit->append("借阅权限："+permission);
    ui->textEdit->append("价格："+price);

    int inLibrary = 0;
    int isBorrowed = 0;
    int allBook =0;
    for(int i = 0;i<library.booklib.size();++i)
    {
        if(library.booklib[i].name == book.name && library.booklib[i].author == book.author &&library.booklib[i].press == book.press
                &&library.booklib[i].type == book.type &&library.booklib[i].price == book.price)   //两本书相同
        {
            ++allBook;
            if(library.booklib[i].state == 1)
                ++inLibrary;
            if(library.booklib[i].state == 0)
                ++isBorrowed;
        }
    }

    ui->textEdit->append("该书共有"+QString::number(allBook)+"本");
    ui->textEdit->append("其中有"+QString::number(inLibrary)+"在图书馆， 有"+QString::number(isBorrowed)+"本被借出");
}
