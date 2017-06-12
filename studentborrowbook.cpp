#include "studentborrowbook.h"
#include "ui_studentborrowbook.h"
#include "allclass.h"
#include <QApplication>
#include <QMessageBox>

studentborrowbook::studentborrowbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::studentborrowbook)
{
    ui->setupUi(this);
}

studentborrowbook::~studentborrowbook()
{
    delete ui;
}

bool isBook4(QString bookID);


extern book_shelf library;
extern int owetoomuch;                     //为1表示欠款太多
extern int borrowtoomuch;                  //为1表示借书过量
extern int notpower;                       //为1表示没有借书权限
extern int succeed;                        //为1表示借书成功
extern int nobook;                         //为1表示此书不存在或被借走
extern string str;
void studentborrowbook::on_pushButton_clicked()
{
    QString bookid = ui->bookID->text();
    QString days = ui->days->text();

    if(bookid == NULL || !isBook4(bookid))
        QMessageBox::warning(this,"警告！",
                               "请检查书ID！",
                               QMessageBox::Yes);
    else if(days == NULL)
        QMessageBox::warning(this,"警告！",
                               "请输入有效天数！",
                               QMessageBox::Yes);
    else
    {
        library.borr_book(bookid.toStdString(),str,days.toInt());

        if(owetoomuch)
            QMessageBox::warning(this,"警告！",
                                               "您欠款过多！",
                                               QMessageBox::Yes);
        else if(borrowtoomuch)
            QMessageBox::warning(this, "警告！",
                                                "您借书过多！",
                                                QMessageBox::Yes);
        else if(notpower)
            QMessageBox::warning(this, "提示！",
                                                "您没有权限借该书！",
                                                QMessageBox::Yes);
        else if(succeed)
        {
            QMessageBox::warning(this, "提示！",
                                                "借书成功！",
                                                QMessageBox::Yes);
            succeed=0;
            this->close();
        }
        else
            QMessageBox::warning(this,  "警告！",
                                                 "该书不存在或已被借走！",
                                                 QMessageBox::Yes);
    }
}


bool isBook4(QString bookID)
{
    for(int i = 0; i<library.booklib.size();++i)
    {
        QString q1 = QString::fromStdString(library.booklib[i].id);
        if(!QString::compare(bookID,q1))
            return true;
    }
    return false;
}
