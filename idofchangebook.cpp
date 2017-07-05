#include "idofchangebook.h"
#include "ui_idofchangebook.h"
#include "allclass.h"
#include "changebook.h"
#include <QMessageBox>

idofchangebook::idofchangebook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::idofchangebook)
{
    ui->setupUi(this);
}

idofchangebook::~idofchangebook()
{
    delete ui;
}

bool isBook3(QString bookID);
extern book_shelf library;
string changebookid;
void idofchangebook::on_pushButton_clicked()
{
    QString idofbook = ui->changebookID->text();
    changebookid = idofbook.toStdString();

    if(!isBook3(idofbook))
        QMessageBox::warning(this,"警告！",
                               "该书不存在！",
                               QMessageBox::Yes);
    else
    {
        changebook *changeb = new changebook();
        changeb->setModal(true);
        changeb->show();
        this->close();
    }
}

bool isBook3(QString bookID)
{
    for(int i = 0; i<library.booklib.size();++i)
    {
        QString q1 = QString::fromStdString(library.booklib[i].id);
        if(!QString::compare(bookID,q1))
            return true;
    }
    return false;
}
