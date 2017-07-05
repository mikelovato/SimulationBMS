#include "idofchangeclient.h"
#include "ui_idofchangeclient.h"
#include "allclass.h"
#include "changeclient.h"
#include <QMessageBox>

idofchangeclient::idofchangeclient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::idofchangeclient)
{
    ui->setupUi(this);
}

idofchangeclient::~idofchangeclient()
{
    delete ui;
}

bool isClient1(QString clientid);
extern book_shelf library;
string id;
void idofchangeclient::on_pushButton_clicked()
{
    QString idofclient = ui->idofClient->text();
    id = idofclient.toStdString();

    if(!isClient1(idofclient))
        QMessageBox::warning(this,"警告！",
                               "该用户不存在！",
                               QMessageBox::Yes);
    else
    {
        changeclient *changecli = new changeclient();
        changecli->setModal(true);
        changecli->show();
        this->close();
    }
}

bool isClient1(QString clientid)
{
    for(int i=0; i< library.suclient.size();++i)
    {
        QString q1 = QString::fromStdString(library.suclient[i].clid);
        if(!QString::compare(clientid,q1))
            return true;
    }
    return false;
}
