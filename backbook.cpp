#include "backbook.h"
#include "ui_backbook.h"
#include "QMessageBox"
#include "allclass.h"
#include <QApplication>


backbook::backbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::backbook)
{
    ui->setupUi(this);
}

backbook::~backbook()
{
    delete ui;
}

extern book_shelf library;
extern int temp_c;               //为1表示还书成功,0代表书ID不正确
void backbook::on_pushButton_clicked()
{
    QString ID = ui->backBook->text();
    string backID = ID.toStdString();
    library.back_book(backID);
    if(temp_c)
    {
        QMessageBox::warning(this,"提示！",
                                       "还书成功！",
                                       QMessageBox::Yes);
        temp_c = 0;
        this->close();
    }
    else
        QMessageBox::warning(this,"警告！",
                                       "请检查书ID！",
                                       QMessageBox::Yes);
}
