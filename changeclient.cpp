#include "changeclient.h"
#include "ui_changeclient.h"
#include "allclass.h"
#include <QDebug>
#include <QMessageBox>

extern book_shelf library;
extern string id;


changeclient::changeclient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeclient)
{
    ui->setupUi(this);
    boclient client = library.id_to_client(id);
    QString name = QString::fromStdString(client.name);
    ui->name->setText(name);
    QString institute = QString::fromStdString(client.institute);
    ui->institute->setCurrentText(institute);
    QString ID = QString::fromStdString(client.clid);
    ui->ID->setText(ID);
}

changeclient::~changeclient()
{
    delete ui;
}

void changeclient::on_pushButton_clicked()
{
    boclient &client = library.id_to_client(id);
    QString clientname = ui->name->text();
    QString clientID = ui->ID->text();
    QString clientinstitute = ui->institute->currentText();
    QString clientoldpassword = ui->oldpassword->text();
    QString clientnewpassword = ui->newpassword->text();
    QString clientpassword = QString::fromStdString(client.cli_pass_word);
    if(clientname == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查用户名！"),
                           QMessageBox::Yes);
    else if(clientID == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查用户ID！"),
                           QMessageBox::Yes);
    else if(clientoldpassword == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请输入原密码！"),
                           QMessageBox::Yes);
    else if(clientnewpassword == NULL)
        QMessageBox::warning(this, tr("提示！"),
                           tr("请输入新密码！"),
                           QMessageBox::Yes);
    else if(clientoldpassword.compare(clientpassword))
        QMessageBox::warning(this, tr("警告！"),
                           tr("原密码输入错误！"),
                           QMessageBox::Yes);
    else
    {
        client.name = clientname.toStdString();
        QString oldID = QString::fromStdString(client.clid);
        client.clid = clientID.toStdString();
        client.institute = clientinstitute.toStdString();
        client.cli_pass_word = clientnewpassword.toStdString();

        for (int i = 0;i<(int)library.bor_record.size();i++)
        {
            if(!oldID.compare(QString::fromStdString(library.bor_record[i].bor_client_id) ) )
                library.bor_record[i].bor_client_id = clientID.toStdString();
        }

        QMessageBox::warning(this, tr("提示！"),
                           tr("修改成功！"),
                           QMessageBox::Yes);
        this->close();
    }
}
