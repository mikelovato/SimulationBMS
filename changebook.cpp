#include "changebook.h"
#include "ui_changebook.h"
#include "allclass.h"
#include <QDebug>
#include "QMessageBox"

extern book_shelf library;
extern string changebookid;

changebook::changebook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changebook)
{
    ui->setupUi(this);
    sinbook book = library.id_to_book(changebookid);
    QString type = QString::fromStdString(book.type);
    ui->type->setCurrentText(type);
    QString ID = QString::fromStdString(book.id);
    ui->ID->setText(ID);
    QString name = QString::fromStdString(book.name);
    ui->name->setText(name);
    QString author = QString::fromStdString(book.author);
    ui->author->setText(author);
    QString press = QString::fromStdString(book.press);
    ui->press->setText(press);
    QString price = QString::number(book.price);
    ui->price->setText(price);
    QString permission = QString::number(book.borrowpermission);
    ui->permission->setText(permission);
}

changebook::~changebook()
{
    delete ui;
}

void changebook::on_pushButton_clicked()
{
    sinbook &book = library.id_to_book(changebookid);
    QString type = ui->type->currentText();
    QString ID = ui->ID->text();
    QString name = ui->name->text();
    QString author = ui->author->text();
    QString press = ui->press->text();
    QString price = ui->price->text();
    QString permission = ui->permission->text();

    if(ID == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查ID！"),
                           QMessageBox::Yes);
    else if(name == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查书名！"),
                           QMessageBox::Yes);
    else if(author == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查作者！"),
                           QMessageBox::Yes);
    else if(press == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查出版社！"),
                           QMessageBox::Yes);
    else if(price == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查价格！"),
                           QMessageBox::Yes);
    else if(permission == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查权限！"),
                           QMessageBox::Yes);
    else
    {
        book.type = type.toStdString();
        QString oldID = QString::fromStdString(book.id);
        book.id = ID.toStdString();
        book.name= name.toStdString();
        book.author = author.toStdString();
        book.press = press.toStdString();
        book.price = price.toDouble();
        book.borrowpermission = permission.toInt();

        for (int i = 0;i<(int)library.bor_record.size();i++)
        {
            if(!oldID.compare(QString::fromStdString(library.bor_record[i].bor_book_id)))
                library.bor_record[i].bor_book_id = ID.toStdString();
        }
        QMessageBox::warning(this, tr("提示！"),
                           tr("修改成功！"),
                           QMessageBox::Yes);
    }
}
#include "changebook.h"
#include "ui_changebook.h"
#include "allclass.h"
#include <QDebug>
#include "QMessageBox"

extern book_shelf library;
extern string changebookid;

changebook::changebook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changebook)
{
    ui->setupUi(this);
    sinbook book = library.id_to_book(changebookid);
    QString type = QString::fromStdString(book.type);
    ui->type->setCurrentText(type);
    QString ID = QString::fromStdString(book.id);
    ui->ID->setText(ID);
    QString name = QString::fromStdString(book.name);
    ui->name->setText(name);
    QString author = QString::fromStdString(book.author);
    ui->author->setText(author);
    QString press = QString::fromStdString(book.press);
    ui->press->setText(press);
    QString price = QString::number(book.price);
    ui->price->setText(price);
    QString permission = QString::number(book.borrowpermission);
    ui->permission->setText(permission);
}

changebook::~changebook()
{
    delete ui;
}

void changebook::on_pushButton_clicked()
{
    sinbook &book = library.id_to_book(changebookid);
    QString type = ui->type->currentText();
    QString ID = ui->ID->text();
    QString name = ui->name->text();
    QString author = ui->author->text();
    QString press = ui->press->text();
    QString price = ui->price->text();
    QString permission = ui->permission->text();

    if(ID == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查ID！"),
                           QMessageBox::Yes);
    else if(name == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查书名！"),
                           QMessageBox::Yes);
    else if(author == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查作者！"),
                           QMessageBox::Yes);
    else if(press == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查出版社！"),
                           QMessageBox::Yes);
    else if(price == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查价格！"),
                           QMessageBox::Yes);
    else if(permission == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查权限！"),
                           QMessageBox::Yes);
    else
    {
        book.type = type.toStdString();
        QString oldID = QString::fromStdString(book.id);
        book.id = ID.toStdString();
        book.name= name.toStdString();
        book.author = author.toStdString();
        book.press = press.toStdString();
        book.price = price.toDouble();
        book.borrowpermission = permission.toInt();

        for (int i = 0;i<(int)library.bor_record.size();i++)
        {
            if(!oldID.compare(QString::fromStdString(library.bor_record[i].bor_book_id)))
                library.bor_record[i].bor_book_id = ID.toStdString();
        }
        QMessageBox::warning(this, tr("提示！"),
                           tr("修改成功！"),
                           QMessageBox::Yes);
    }
}
#include "changebook.h"
#include "ui_changebook.h"
#include "allclass.h"
#include <QDebug>
#include "QMessageBox"

extern book_shelf library;
extern string changebookid;

changebook::changebook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changebook)
{
    ui->setupUi(this);
    sinbook book = library.id_to_book(changebookid);
    QString type = QString::fromStdString(book.type);
    ui->type->setCurrentText(type);
    QString ID = QString::fromStdString(book.id);
    ui->ID->setText(ID);
    QString name = QString::fromStdString(book.name);
    ui->name->setText(name);
    QString author = QString::fromStdString(book.author);
    ui->author->setText(author);
    QString press = QString::fromStdString(book.press);
    ui->press->setText(press);
    QString price = QString::number(book.price);
    ui->price->setText(price);
    QString permission = QString::number(book.borrowpermission);
    ui->permission->setText(permission);
}

changebook::~changebook()
{
    delete ui;
}

void changebook::on_pushButton_clicked()
{
    sinbook &book = library.id_to_book(changebookid);
    QString type = ui->type->currentText();
    QString ID = ui->ID->text();
    QString name = ui->name->text();
    QString author = ui->author->text();
    QString press = ui->press->text();
    QString price = ui->price->text();
    QString permission = ui->permission->text();

    if(ID == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查ID！"),
                           QMessageBox::Yes);
    else if(name == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查书名！"),
                           QMessageBox::Yes);
    else if(author == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查作者！"),
                           QMessageBox::Yes);
    else if(press == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查出版社！"),
                           QMessageBox::Yes);
    else if(price == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查价格！"),
                           QMessageBox::Yes);
    else if(permission == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查权限！"),
                           QMessageBox::Yes);
    else
    {
        book.type = type.toStdString();
        QString oldID = QString::fromStdString(book.id);
        book.id = ID.toStdString();
        book.name= name.toStdString();
        book.author = author.toStdString();
        book.press = press.toStdString();
        book.price = price.toDouble();
        book.borrowpermission = permission.toInt();

        for (int i = 0;i<(int)library.bor_record.size();i++)
        {
            if(!oldID.compare(QString::fromStdString(library.bor_record[i].bor_book_id)))
                library.bor_record[i].bor_book_id = ID.toStdString();
        }
        QMessageBox::warning(this, tr("提示！"),
                           tr("修改成功！"),
                           QMessageBox::Yes);
    }
}
#include "changebook.h"
#include "ui_changebook.h"
#include "allclass.h"
#include <QDebug>
#include "QMessageBox"

extern book_shelf library;
extern string changebookid;

changebook::changebook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changebook)
{
    ui->setupUi(this);
    sinbook book = library.id_to_book(changebookid);
    QString type = QString::fromStdString(book.type);
    ui->type->setCurrentText(type);
    QString ID = QString::fromStdString(book.id);
    ui->ID->setText(ID);
    QString name = QString::fromStdString(book.name);
    ui->name->setText(name);
    QString author = QString::fromStdString(book.author);
    ui->author->setText(author);
    QString press = QString::fromStdString(book.press);
    ui->press->setText(press);
    QString price = QString::number(book.price);
    ui->price->setText(price);
    QString permission = QString::number(book.borrowpermission);
    ui->permission->setText(permission);
}

changebook::~changebook()
{
    delete ui;
}

void changebook::on_pushButton_clicked()
{
    sinbook &book = library.id_to_book(changebookid);
    QString type = ui->type->currentText();
    QString ID = ui->ID->text();
    QString name = ui->name->text();
    QString author = ui->author->text();
    QString press = ui->press->text();
    QString price = ui->price->text();
    QString permission = ui->permission->text();

    if(ID == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查ID！"),
                           QMessageBox::Yes);
    else if(name == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查书名！"),
                           QMessageBox::Yes);
    else if(author == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查作者！"),
                           QMessageBox::Yes);
    else if(press == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查出版社！"),
                           QMessageBox::Yes);
    else if(price == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查价格！"),
                           QMessageBox::Yes);
    else if(permission == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查权限！"),
                           QMessageBox::Yes);
    else
    {
        book.type = type.toStdString();
        QString oldID = QString::fromStdString(book.id);
        book.id = ID.toStdString();
        book.name= name.toStdString();
        book.author = author.toStdString();
        book.press = press.toStdString();
        book.price = price.toDouble();
        book.borrowpermission = permission.toInt();

        for (int i = 0;i<(int)library.bor_record.size();i++)
        {
            if(!oldID.compare(QString::fromStdString(library.bor_record[i].bor_book_id)))
                library.bor_record[i].bor_book_id = ID.toStdString();
        }
        QMessageBox::warning(this, tr("提示！"),
                           tr("修改成功！"),
                           QMessageBox::Yes);
    }
}
#include "changebook.h"
#include "ui_changebook.h"
#include "allclass.h"
#include <QDebug>
#include "QMessageBox"

extern book_shelf library;
extern string changebookid;

changebook::changebook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changebook)
{
    ui->setupUi(this);
    sinbook book = library.id_to_book(changebookid);
    QString type = QString::fromStdString(book.type);
    ui->type->setCurrentText(type);
    QString ID = QString::fromStdString(book.id);
    ui->ID->setText(ID);
    QString name = QString::fromStdString(book.name);
    ui->name->setText(name);
    QString author = QString::fromStdString(book.author);
    ui->author->setText(author);
    QString press = QString::fromStdString(book.press);
    ui->press->setText(press);
    QString price = QString::number(book.price);
    ui->price->setText(price);
    QString permission = QString::number(book.borrowpermission);
    ui->permission->setText(permission);
}

changebook::~changebook()
{
    delete ui;
}

void changebook::on_pushButton_clicked()
{
    sinbook &book = library.id_to_book(changebookid);
    QString type = ui->type->currentText();
    QString ID = ui->ID->text();
    QString name = ui->name->text();
    QString author = ui->author->text();
    QString press = ui->press->text();
    QString price = ui->price->text();
    QString permission = ui->permission->text();

    if(ID == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查ID！"),
                           QMessageBox::Yes);
    else if(name == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查书名！"),
                           QMessageBox::Yes);
    else if(author == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查作者！"),
                           QMessageBox::Yes);
    else if(press == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查出版社！"),
                           QMessageBox::Yes);
    else if(price == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查价格！"),
                           QMessageBox::Yes);
    else if(permission == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查权限！"),
                           QMessageBox::Yes);
    else
    {
        book.type = type.toStdString();
        QString oldID = QString::fromStdString(book.id);
        book.id = ID.toStdString();
        book.name= name.toStdString();
        book.author = author.toStdString();
        book.press = press.toStdString();
        book.price = price.toDouble();
        book.borrowpermission = permission.toInt();

        for (int i = 0;i<(int)library.bor_record.size();i++)
        {
            if(!oldID.compare(QString::fromStdString(library.bor_record[i].bor_book_id)))
                library.bor_record[i].bor_book_id = ID.toStdString();
        }
        QMessageBox::warning(this, tr("提示！"),
                           tr("修改成功！"),
                           QMessageBox::Yes);
    }
}
#include "changebook.h"
#include "ui_changebook.h"
#include "allclass.h"
#include <QDebug>
#include "QMessageBox"

extern book_shelf library;
extern string changebookid;

changebook::changebook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changebook)
{
    ui->setupUi(this);
    sinbook book = library.id_to_book(changebookid);
    QString type = QString::fromStdString(book.type);
    ui->type->setCurrentText(type);
    QString ID = QString::fromStdString(book.id);
    ui->ID->setText(ID);
    QString name = QString::fromStdString(book.name);
    ui->name->setText(name);
    QString author = QString::fromStdString(book.author);
    ui->author->setText(author);
    QString press = QString::fromStdString(book.press);
    ui->press->setText(press);
    QString price = QString::number(book.price);
    ui->price->setText(price);
    QString permission = QString::number(book.borrowpermission);
    ui->permission->setText(permission);
}

changebook::~changebook()
{
    delete ui;
}

void changebook::on_pushButton_clicked()
{
    sinbook &book = library.id_to_book(changebookid);
    QString type = ui->type->currentText();
    QString ID = ui->ID->text();
    QString name = ui->name->text();
    QString author = ui->author->text();
    QString press = ui->press->text();
    QString price = ui->price->text();
    QString permission = ui->permission->text();

    if(ID == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查ID！"),
                           QMessageBox::Yes);
    else if(name == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查书名！"),
                           QMessageBox::Yes);
    else if(author == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查作者！"),
                           QMessageBox::Yes);
    else if(press == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查出版社！"),
                           QMessageBox::Yes);
    else if(price == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查价格！"),
                           QMessageBox::Yes);
    else if(permission == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查权限！"),
                           QMessageBox::Yes);
    else
    {
        book.type = type.toStdString();
        QString oldID = QString::fromStdString(book.id);
        book.id = ID.toStdString();
        book.name= name.toStdString();
        book.author = author.toStdString();
        book.press = press.toStdString();
        book.price = price.toDouble();
        book.borrowpermission = permission.toInt();

        for (int i = 0;i<(int)library.bor_record.size();i++)
        {
            if(!oldID.compare(QString::fromStdString(library.bor_record[i].bor_book_id)))
                library.bor_record[i].bor_book_id = ID.toStdString();
        }
        QMessageBox::warning(this, tr("提示！"),
                           tr("修改成功！"),
                           QMessageBox::Yes);
    }
}
