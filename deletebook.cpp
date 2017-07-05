#include "deletebook.h"
#include "ui_deletebook.h"
#include "allclass.h"
#include <QMessageBox>

deletebook::deletebook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletebook)
{
    ui->setupUi(this);
}

deletebook::~deletebook()
{
    delete ui;
}

bool isBook2(QString bookID);

extern book_shelf library;

void deletebook::on_pushButton_clicked()
{
    QString deleteID = ui->IDdelete->text();
    string ID = deleteID.toStdString();
    if(deleteID == NULL)
        QMessageBox::warning(this, tr("提示！"),
                    tr("请检查书ID！"),
                    QMessageBox::Yes);
    else if(!isBook2(deleteID))
        QMessageBox::warning(this, tr("提示！"),
                    tr("该书不存在！"),
                    QMessageBox::Yes);
    else
    {
        library.delet_book(ID);
        QMessageBox::warning(this, tr("提示！"),
                    tr("成功删除图书！"),
                    QMessageBox::Yes);
        this->close();
    }
}

bool isBook2(QString bookID)
{
    for(int i = 0; i<library.booklib.size();++i)
    {
        QString q1 = QString::fromStdString(library.booklib[i].id);
        if(!QString::compare(bookID,q1))
            return true;
    }
    return false;
}
