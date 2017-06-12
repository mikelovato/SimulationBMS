#include "rechargeid.h"
#include "ui_rechargeid.h"
#include "QMessageBox"
#include "allclass.h"
#include <string>

rechargeid::rechargeid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rechargeid)
{
    ui->setupUi(this);
}

rechargeid::~rechargeid()
{
    delete ui;
}


extern book_shelf library;
extern int rechargesucceed;
void rechargeid::on_pushButton_clicked()
{
    QString clientID = ui->clientID->text();
    QString money = ui->money->text();
    string ID = clientID.toStdString();


    if(clientID == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请输入用户ID！"),
                           QMessageBox::Yes);
    else if(money == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请输入充值金额！"),
                           QMessageBox::Yes);
    else
    {
        library.recharge(ID,money.toDouble());
        if(rechargesucceed)
        {
            QMessageBox::warning(this, tr("提示！"),
                               tr("充值成功！"),
                               QMessageBox::Yes);
            rechargesucceed=0;
            this->close();
        }
        else
            QMessageBox::warning(this, tr("提示！"),
                               tr("请检查您的ID！"),
                               QMessageBox::Yes);
    }
}
