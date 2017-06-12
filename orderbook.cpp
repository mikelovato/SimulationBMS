#include "orderbook.h"
#include "ui_orderbook.h"
#include "allclass.h"
#include <QString>
#include <QMessageBox>
#include <string>

orderbook::orderbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::orderbook)
{
    ui->setupUi(this);
}

orderbook::~orderbook()
{
    delete ui;
}

bool isClient5(QString clientid);
bool isBook5(QString bookID);

extern book_shelf library;
extern int orderowetoomuch;
extern int orderbookdeleted;
extern int order_succeed;
extern int order_book_in_library;
extern string str;
void orderbook::on_pushButton_clicked()
{
    QString bookID = ui->bookid->text();

    if(bookID == NULL||!isBook5(bookID))
        QMessageBox::warning(this, tr("提示！"),
                           tr("请检查书ID！"),
                           QMessageBox::Yes);
    else
    {
        library.order_book(bookID.toStdString(),str);
        if(orderowetoomuch)
        {
            QMessageBox::warning(this, tr("提示！"),
                                          tr("您欠款过多！"),
                                          QMessageBox::Yes);
            orderowetoomuch=0;
        }
        else if(order_book_in_library)
        {
            QMessageBox::warning(this, tr("提示！"),
                                          tr("该书在馆内，您可以直接借！"),
                                          QMessageBox::Yes);
            order_book_in_library = 0;
        }
        else if(orderbookdeleted)
        {
            QMessageBox::warning(this, tr("提示！"),
                                          tr("该书已不在库！"),
                                          QMessageBox::Yes);
        }
        else if(order_succeed)
        {
            QMessageBox::warning(this, tr("提示！"),
                                          tr("预约成功！"),
                                          QMessageBox::Yes);
            order_succeed = 0;
        }
        this->close();
    }
}

bool isClient5(QString clientid)
{
    for(int i=0; i< library.suclient.size();++i)
    {
        QString q1 = QString::fromStdString(library.suclient[i].clid);
        if(!QString::compare(clientid,q1))
            return true;
    }
    return false;
}

bool isBook5(QString bookID)
{
    for(int i = 0; i<library.booklib.size();++i)
    {
        QString q1 = QString::fromStdString(library.booklib[i].id);
        if(!QString::compare(bookID,q1))
            return true;
    }
    return false;
}
