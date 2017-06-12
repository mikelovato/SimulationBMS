#include "teacherinterface.h"
#include "ui_teacherinterface.h"
#include "login.h"
#include "allbook.h"
#include "allclass.h"
#include "borrowbook.h"
#include "backbook.h"
#include "addbook.h"
#include "deletebook.h"
#include "changebook.h"
#include "monthinfo.h"
#include "creatid.h"
#include "rechargeid.h"
#include "displayinfo.h"
#include "changeclient.h"
#include "idofchangeclient.h"
#include "idofchangebook.h"
#include "displaybookinfo.h"
#include "deleteclient.h"
#include <QTextStream>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QPainter>

extern book_shelf library;
extern int year;
extern int month;
extern int day;

extern vector<sinbook> computer;
extern vector<sinbook> math;
extern vector<sinbook> literature;
extern vector<sinbook> history;
extern vector<sinbook> art;
extern vector<sinbook> communication;
extern vector<sinbook> medicine;
extern vector<sinbook> economy;
extern vector<sinbook> other;

TeacherInterface::TeacherInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherInterface)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
    ui->time->setText(QString::number(year)+"年"+QString::number(month)+"月"+QString::number(day)+"日");
    sinbook book;
    for(int i = 0; i<library.booklib.size();++i)
    {
        QString name = QString::fromStdString(library.booklib[i].name);
        if(library.booklib[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(library.booklib[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");

        if(library.booklib[i].type == "计算机类")
        {
            book = library.booklib[i];
            computer.push_back(book);
        }
        else if(library.booklib[i].type == "数学类")
        {
            book = library.booklib[i];
            math.push_back(book);
        }
        else if(library.booklib[i].type == "文学类")
        {
            book = library.booklib[i];
            literature.push_back(book);
        }
        else if(library.booklib[i].type == "历史类")
        {
            book = library.booklib[i];
            history.push_back(book);
        }
        else if(library.booklib[i].type == "艺术类")
        {
            book = library.booklib[i];
            art.push_back(book);
        }
        else if(library.booklib[i].type == "通信类")
        {
            book = library.booklib[i];
            communication.push_back(book);
        }
        else if(library.booklib[i].type == "医学类")
        {
            book = library.booklib[i];
            medicine.push_back(book);
        }
        else if(library.booklib[i].type == "经济类")
        {
            book = library.booklib[i];
            economy.push_back(book);
        }
        else
        {
            book = library.booklib[i];
            other.push_back(book);
        }
    }
}

TeacherInterface::~TeacherInterface()
{
    delete ui;
}

void TeacherInterface::on_exitBtn_clicked()
{
    computer.clear();
    math.clear();
    literature.clear();
    history.clear();
    art.clear();
    communication.clear();
    medicine.clear();
    economy.clear();
    other.clear();


    ofstream dout("C:\\Users\\lenovo\\Documents\\Test\\document\\book_she_text.txt");//对书的保存
    for(int i=0; i<(int)library.booklib.size(); i++)
    {
        dout<<"类型："<<endl;
        dout<<library.booklib[i].type<<endl;
        dout<<"购入时间："<<endl;
        dout<<library.booklib[i].buytime<<endl;
        dout<<"书名："<<endl;
        dout<<library.booklib[i].name<<endl;
        dout<<"作者："<<endl;
        dout<<library.booklib[i].author<<endl;
        dout<<"出版社："<<endl;
        dout<<library.booklib[i].press<<endl;
        dout<<"价格："<<endl;
        dout<<library.booklib[i].price<<endl;
        dout<<"借阅权限："<<endl;
        dout<<library.booklib[i].borrowpermission<<endl;
        dout<<"状态："<<endl;
        dout<<library.booklib[i].state<<endl;
        dout<<"ID："<<endl;
        dout<<library.booklib[i].id<<endl;
        if(i!=library.booklib.size()-1)
            dout<<endl;
    }
    dout.clear();
    dout.close();

    ofstream gout("C:\\Users\\lenovo\\Documents\\Test\\document\\client_he_text.txt");//对客户的保存
    for(int i=0; i<(int)library.suclient.size(); i++)
    {
        gout<<"姓名："<<endl;
        gout<<library.suclient[i].name<<endl;
        gout<<"密码："<<endl;
        gout<<library.suclient[i].cli_pass_word<<endl;
        gout<<"身份："<<endl;
        gout<<library.suclient[i].client_identity<<endl;
        gout<<"学院："<<endl;
        gout<<library.suclient[i].institute<<endl;
        gout<<"账号创建时间："<<endl;
        gout<<library.suclient[i].creat_time<<endl;
        gout<<"借书数量："<<endl;
        gout<<library.suclient[i].borrownum<<endl;
        gout<<"借书ID："<<endl;
        for(int j=0; j<library.suclient[i].borrownum; j++)
            gout<<library.suclient[i].borrowid[j]<<endl;
        gout<<"预约数量："<<endl;
        gout<<library.suclient[i].orderbooknum<<endl;
        gout<<"预约ID："<<endl;
        for(int j=0; j<library.suclient[i].orderbooknum; j++)
            gout<<library.suclient[i].orderbookid[j]<<endl;
        gout<<"欠款："<<endl;
        gout<<library.suclient[i].Arrears_money<<endl;
        gout<<"诚信等级："<<endl;
        gout<<library.suclient[i].honestlevel<<endl;
        gout<<"ID："<<endl;
        gout<<library.suclient[i].clid<<endl;
        if(i!=library.suclient.size()-1)
            gout<<endl;
    }
    gout.clear();
    gout.close();


    ofstream rout("C:\\Users\\lenovo\\Documents\\Test\\document\\log_file.txt");//交易记录的保存
    for (int i = 0;i<(int)library.bor_record.size();i++)
    {
        rout<<"书ID："<<endl;
        rout << library.bor_record[i].bor_book_id << endl;
        rout<<"用户ID："<<endl;
        rout << library.bor_record[i].bor_client_id << endl;
        rout<<"借书/预约时间："<<endl;
        rout << library.bor_record[i].bor_time << endl;
        rout<<"借书时长/预约生效时间："<<endl;
        rout << library.bor_record[i].bor_term << endl;
        rout<<"借书/预约用户类型："<<endl;
        rout << library.bor_record[i].bor_way << endl;
        rout<<"罚款："<<endl;
        rout << library.bor_record[i].bookfine << endl;
        rout<<"状态："<<endl;
        rout << library.bor_record[i].retu_book << endl;
        rout<<"借书/预约："<<endl;
        rout << library.bor_record[i].type_comm << endl;
        if(i!=library.bor_record.size()-1)
            rout<<endl;
    }
    rout.clear();
    rout.close();

    library.booklib.clear();
    library.bor_record.clear();
    library.suclient.clear();

    this->close();
}

void TeacherInterface::on_borrowBtn_clicked()
{
    borrowbook *borrow = new borrowbook();
    borrow->setModal(true);
    borrow->show();
}

void TeacherInterface::on_backBtn_clicked()
{
    backbook *back = new backbook();
    back->setModal(true);
    back->show();
}

void TeacherInterface::on_addbookBtn_clicked()
{
    AddBook *addbook = new AddBook();
    addbook->setModal(true);
    addbook->show();
}

void TeacherInterface::on_deletebookBtn_clicked()
{
    deletebook *deletebooks = new deletebook();
    deletebooks->setModal(true);
    deletebooks->show();
}

void TeacherInterface::on_changebookBtn_clicked()
{
    idofchangebook *change = new idofchangebook();
    change->setModal(true);
    change->show();
}

void TeacherInterface::on_allbookBtn_clicked()
{
    allbook *all = new allbook();
    all->setModal(true);
    all->show();
}

void TeacherInterface::on_pushButton_clicked()
{
    deleteclient *delet = new deleteclient();
    delet->setModal(true);
    delet->show();
}

void TeacherInterface::on_monthinfoBtn_clicked()
{
    monthinfo *month = new monthinfo();
    month->play();
    month->setModal(true);
    month->show();

}

void TeacherInterface::on_creatidBtn_clicked()
{
    creatid *creat = new creatid();
    creat->setModal(true);
    creat->show();
}

void TeacherInterface::on_rechargeidBtn_clicked()
{
    rechargeid *recharge = new rechargeid();
    recharge->setModal(true);
    recharge->show();
}

void TeacherInterface::on_displayinfoBtn_clicked()
{
    displayinfo *display = new displayinfo();
    display->setModal(true);
    display->show();
}

void TeacherInterface::on_changeClient_clicked()
{
    idofchangeclient *idofclient = new idofchangeclient();
    idofclient->setModal(true);
    idofclient->show();
}


int bookTYPE=0;
void TeacherInterface::on_listView_doubleClicked(const QModelIndex &index)
{
}


int booksearchType = 0;
void TeacherInterface::on_name_clicked()
{
    booksearchType = 1;
}

void TeacherInterface::on_author_clicked()
{
    booksearchType = 2;
}

void TeacherInterface::on_press_clicked()
{
    booksearchType = 3;
}

void TeacherInterface::on_pushButton_3_clicked()
{
    bookTYPE = 0;
    ui->listWidget->clear();
    for(int i = 0; i<library.booklib.size();++i)
    {
        QString name = QString::fromStdString(library.booklib[i].name);
        if(library.booklib[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(library.booklib[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");    }
    //ui->scrollAreaWidgetContents->moveCursor(::Start);
}

void TeacherInterface::on_computerBtn_clicked()
{
    renew();
    bookTYPE = 1;
    ui->listWidget->clear();
    for(int i = 0; i<computer.size();++i)
    {
        QString name = QString::fromStdString(computer[i].name);
        if(computer[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(computer[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");    }
}

void TeacherInterface::on_mathBtn_clicked()
{
    renew();
    bookTYPE = 2;
    ui->listWidget->clear();
    for(int i = 0; i<math.size();++i)
    {
        QString name = QString::fromStdString(math[i].name);
        if(math[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(math[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");     }
}

void TeacherInterface::on_literatureBtn_clicked()
{
    renew();
    bookTYPE = 3;
    ui->listWidget->clear();
    for(int i = 0; i<literature.size();++i)
    {
        QString name = QString::fromStdString(literature[i].name);
        if(literature[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(literature[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");     }
}

void TeacherInterface::on_historyBtn_clicked()
{
    renew();
    bookTYPE = 4;
    ui->listWidget->clear();
    for(int i = 0; i<history.size();++i)
    {
        QString name = QString::fromStdString(history[i].name);
        if(history[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(history[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");    }
}

void TeacherInterface::on_artBtn_clicked()
{
    renew();
    bookTYPE = 5;
    ui->listWidget->clear();
    for(int i = 0; i<art.size();++i)
    {
        QString name = QString::fromStdString(art[i].name);
        if(art[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(art[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");     }
}

void TeacherInterface::on_communicationBtn_clicked()
{
    renew();
    bookTYPE = 6;
    ui->listWidget->clear();
    for(int i = 0; i<communication.size();++i)
    {
        QString name = QString::fromStdString(communication[i].name);
        if(communication[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(communication[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");    }
}

void TeacherInterface::on_medicineBtn_clicked()
{
    renew();
    bookTYPE = 7;
    ui->listWidget->clear();
    for(int i = 0; i<medicine.size();++i)
    {
        QString name = QString::fromStdString(medicine[i].name);
        if(medicine[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(medicine[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");    }
}

void TeacherInterface::on_economyBtn_clicked()
{
    renew();
    bookTYPE = 8;
    ui->listWidget->clear();
    for(int i = 0; i<economy.size();++i)
    {
        QString name = QString::fromStdString(economy[i].name);
        if(economy[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(economy[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");    }
}

void TeacherInterface::on_otherBtn_clicked()
{
    renew();
    bookTYPE = 9;
    ui->listWidget->clear();
    for(int i = 0; i<other.size();++i)
    {
        QString name = QString::fromStdString(other[i].name);
        if(other[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(other[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");    }
}

void TeacherInterface::on_searchBtn_clicked()
{
    QString searchStr = ui->search->text();
    if(searchStr == NULL)
        QMessageBox::warning(this, tr("提示！"),
                             tr("请输入查询内容！"),
                             QMessageBox::Yes);
    switch (booksearchType){
        case 0:
        if(!(searchStr == NULL))
        QMessageBox::warning(this, tr("提示！"),
                                     tr("请选择查询类型！"),
                                     QMessageBox::Yes);
            break;
        case 1:
            ui->listWidget->clear();
            //QString name = ui->name->text();
            if(bookTYPE == 0)
                for(int i = 0, j = 0; i<library.booklib.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(library.booklib[i].name)))
                    {
                        if(library.booklib[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(library.booklib[i].name)+"  (被借)");
                        else if(library.booklib[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(library.booklib[i].name)+"  (在库)");
                        swap(library.booklib[i],library.booklib[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 1)
                for(int i = 0,j=0; i<computer.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(computer[i].name)))
                    {
                        if(computer[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(computer[i].name)+"  (被借)");
                        else if(computer[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(computer[i].name)+"  (在库)");
                        swap(computer[i],computer[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 2)
                for(int i = 0,j=0; i<math.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(math[i].name)))
                    {
                        if(math[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(math[i].name)+"  (被借)");
                        else if(math[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(math[i].name)+"  (在库)");
                        swap(math[i],math[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 3)
                for(int i = 0,j=0; i<literature.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(literature[i].name)))
                    {
                        if(literature[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(literature[i].name)+"  (被借)");
                        else if(literature[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(literature[i].name)+"  (在库)");
                        swap(literature[i],literature[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 4)
                for(int i = 0,j=0; i<history.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(history[i].name)))
                    {
                        if(history[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(history[i].name)+"  (被借)");
                        else if(history[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(history[i].name)+"  (在库)");                        swap(history[i],history[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 5)
                for(int i = 0,j=0; i<art.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(art[i].name)))
                    {
                        if(art[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(art[i].name)+"  (被借)");
                        else if(art[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(art[i].name)+"  (在库)");
                        swap(art[i],art[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 6)
                for(int i = 0,j=0; i<communication.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(communication[i].name)))
                    {
                        if(communication[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(communication[i].name)+"  (被借)");
                        else if(communication[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(communication[i].name)+"  (在库)");
                        swap(communication[i],communication[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 7)
                for(int i = 0,j=0; i<medicine.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(medicine[i].name)))
                    {
                        if(medicine[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(medicine[i].name)+"  (被借)");
                        else if(medicine[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(medicine[i].name)+"  (在库)");
                        swap(medicine[i],medicine[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 8)
                for(int i = 0,j=0; i<economy.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(economy[i].name)))
                    {
                        if(economy[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(economy[i].name)+"  (被借)");
                        else if(economy[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(economy[i].name)+"  (在库)");
                        swap(economy[i],economy[j]);
                        ++j;
                    }
                }
            else
                for(int i = 0,j=0; i<other.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(other[i].name)))
                    {
                        if(other[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(other[i].name)+"  (被借)");
                        else if(other[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(other[i].name)+"  (在库)");
                        swap(other[i],other[j]);
                        ++j;
                    }
                }
            break;
        case 2:
            ui->listWidget->clear();
            //QString auther = ui->auther->text();
            if(bookTYPE == 0)
                for(int i = 0, j = 0; i<library.booklib.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(library.booklib[i].author)))
                    {
                        if(library.booklib[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(library.booklib[i].name)+"  (被借)");
                        else if(library.booklib[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(library.booklib[i].name)+"  (在库)");
                        swap(library.booklib[i],library.booklib[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 1)
                for(int i = 0,j=0; i<computer.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(computer[i].author)))
                    {
                        if(computer[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(computer[i].name)+"  (被借)");
                        else if(computer[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(computer[i].name)+"  (在库)");
                        swap(computer[i],computer[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 2)
                for(int i = 0,j=0; i<math.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(math[i].author)))
                    {
                        if(math[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(math[i].name)+"  (被借)");
                        else if(math[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(math[i].name)+"  (在库)");
                        swap(math[i],math[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 3)
                for(int i = 0,j=0; i<literature.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(literature[i].author)))
                    {
                        if(literature[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(literature[i].name)+"  (被借)");
                        else if(literature[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(literature[i].name)+"  (在库)");
                        swap(literature[i],literature[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 4)
                for(int i = 0,j=0; i<history.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(history[i].author)))
                    {
                        if(history[i].state == 0)
                            ui->listWidget->addItem( QString::fromStdString(history[i].name)+"  (被借)");
                        else if(history[i].state == 1)
                            ui->listWidget->addItem( QString::fromStdString(history[i].name)+"  (在库)");
                        swap(history[i],history[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 5)
                for(int i = 0,j=0; i<art.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(art[i].author)))
                    {
                        if(art[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(art[i].name)+"  (被借)");
                        else if(art[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(art[i].name)+"  (在库)");
                        swap(art[i],art[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 6)
                for(int i = 0,j=0; i<communication.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(communication[i].author)))
                    {
                        if(communication[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(communication[i].name)+"  (被借)");
                        else if(communication[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(communication[i].name)+"  (在库)");
                        swap(communication[i],communication[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 7)
                for(int i = 0,j=0; i<medicine.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(medicine[i].author)))
                    {
                        if(medicine[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(medicine[i].name)+"  (被借)");
                        else if(medicine[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(medicine[i].name)+"  (在库)");
                        swap(medicine[i],medicine[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 8)
                for(int i = 0,j=0; i<economy.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(economy[i].author)))
                    {
                        if(economy[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(economy[i].name)+"  (被借)");
                        else if(economy[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(economy[i].name)+"  (在库)");
                        swap(economy[i],economy[j]);
                        ++j;
                    }
                }
            else
                for(int i = 0,j=0; i<other.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(other[i].author)))
                    {
                        if(other[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(other[i].name)+"  (被借)");
                        else if(other[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(other[i].name)+"  (在库)");
                        swap(other[i],other[j]);
                        ++j;
                    }
                }
            break;
        case 3:
            ui->listWidget->clear();
            //QString press = ui->press->text();
            if(bookTYPE == 0)
                for(int i = 0, j = 0; i<library.booklib.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(library.booklib[i].press)))
                    {
                        if(library.booklib[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(library.booklib[i].name)+"  (被借)");
                        else if(library.booklib[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(library.booklib[i].name)+"  (在库)");
                        swap(library.booklib[i],library.booklib[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 1)
                for(int i = 0,j=0; i<computer.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(computer[i].press)))
                    {
                        if(computer[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(computer[i].name)+"  (被借)");
                        else if(computer[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(computer[i].name)+"  (在库)");
                        swap(computer[i],computer[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 2)
                for(int i = 0,j=0; i<math.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(math[i].press)))
                    {
                        if(math[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(math[i].name)+"  (被借)");
                        else if(math[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(math[i].name)+"  (在库)");                        swap(math[i],math[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 3)
                for(int i = 0,j=0; i<literature.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(literature[i].press)))
                    {
                        if(literature[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(literature[i].name)+"  (被借)");
                        else if(literature[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(literature[i].name)+"  (在库)");
                        swap(literature[i],literature[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 4)
                for(int i = 0,j=0; i<history.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(history[i].press)))
                    {
                        if(history[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(history[i].name)+"  (被借)");
                        else if(history[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(history[i].name)+"  (在库)");
                        swap(history[i],history[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 5)
                for(int i = 0,j=0; i<art.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(art[i].press)))
                    {
                        if(art[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(art[i].name)+"  (被借)");
                        else if(art[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(art[i].name)+"  (在库)");
                        swap(art[i],art[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 6)
                for(int i = 0,j=0; i<communication.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(communication[i].press)))
                    {
                        if(communication[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(communication[i].name)+"  (被借)");
                        else if(communication[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(communication[i].name)+"  (在库)");
                        swap(communication[i],communication[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 7)
                for(int i = 0,j=0; i<medicine.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(medicine[i].press)))
                    {
                        if(medicine[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(medicine[i].name)+"  (被借)");
                        else if(medicine[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(medicine[i].name)+"  (在库)");
                        swap(medicine[i],medicine[j]);
                        ++j;
                    }
                }
            else if(bookTYPE == 8)
                for(int i = 0,j=0; i<economy.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(economy[i].press)))
                    {
                        if(economy[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(economy[i].name)+"  (被借)");
                        else if(economy[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(economy[i].name)+"  (在库)");
                        swap(economy[i],economy[j]);
                        ++j;
                    }
                }
            else
                for(int i = 0,j=0; i<other.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(other[i].press)))
                    {
                        if(other[i].state == 0)
                            ui->listWidget->addItem(QString::fromStdString(other[i].name)+"  (被借)");
                        else if(other[i].state == 1)
                            ui->listWidget->addItem(QString::fromStdString(other[i].name)+"  (在库)");
                        swap(other[i],other[j]);
                        ++j;
                    }
                }
            break;
    }
}

extern sinbook book;
void TeacherInterface::on_listWidget_doubleClicked(const QModelIndex &index)
{
    displaybookinfo *display = new displaybookinfo();
    switch(bookTYPE)
    {
        case 0: book = library.booklib[index.row()]; break;
        case 1: book = computer[index.row()]; break;
        case 2: book = math[index.row()]; break;
        case 3: book = literature[index.row()]; break;
        case 4: book = history[index.row()]; break;
        case 5: book = art[index.row()]; break;
        case 6: book = communication[index.row()]; break;
        case 7: book = medicine[index.row()]; break;
        case 8: book = economy[index.row()]; break;
        case 9: book = other[index.row()]; break;
    }
    display->play();
    display->setModal(true);
    display->show();
}

void TeacherInterface::on_timecontrolBtn_clicked()
{
    library.book_system_time = library.book_system_time+10;
    switch(month)
    {
    case 1:
        if(day<31) day++;
        else{
            month++;
            day=1;
        }
        break;
    case 2:
        if(year%4==0){
            if(day<29) day++;
            else{
                month++;
                day=1;
            }
        }
        else{
            if(day<28) day++;
            else{
                month++;
                day=1;
            }
        }
        break;
    case 3:
        if(day<31) day++;
        else{
            month++;
            day=1;
        }
        break;
    case 4:
        if(day<30) day++;
        else{
            month++;
            day=1;
        }
        break;
    case 5:
        if(day<31) day++;
        else{
            month++;
            day=1;
        }
        break;
    case 6:
        if(day<30) day++;
        else{
            month++;
            day=1;
        }
        break;
    case 7:
        if(day<31) day++;
        else{
            month++;
            day=1;
        }
        break;
    case 8:
        if(day<31) day++;
        else{
            month++;
            day=1;
        }
        break;
    case 9:
        if(day<30) day++;
        else{
            month++;
            day=1;
        }
        break;
    case 10:
        if(day<31) day++;
        else{
            month++;
            day=1;
        }
        break;
    case 11:
        if(day<30) day++;
        else{
            month++;
            day=1;
        }
        break;
    case 12:
        if(day<31) day++;
        else{
            year++;
            month=1;
            day=1;
        }
        break;
    defult:break;
    }

    qDebug()<<library.book_system_time;
    ui->time->setText(QString::number(year)+"年"+QString::number(month)+"月"+QString::number(day)+"日");

    ofstream fout("C:\\Users\\lenovo\\Documents\\Test\\document\\time_single.txt");//对时间的保存
    if(!fout.is_open())
        cout<<"打开失败";
    qDebug()<<library.book_system_time;
    fout<<library.book_system_time<<"\n";
    fout<<year<<"\n";
    fout<<month<<"\n";
    fout<<day;
    fout.clear();
    fout.close();
}

void TeacherInterface::on_renew_clicked()
{
}

void TeacherInterface::renew()
{
    computer.clear();
    math.clear();
    literature.clear();
    history.clear();
    art.clear();
    communication.clear();
    medicine.clear();
    economy.clear();
    other.clear();

    sinbook book;
    for(int i = 0; i<library.booklib.size();++i)
    {
        if(library.booklib[i].type == "计算机类")
        {
            book = library.booklib[i];
            computer.push_back(book);
        }
        else if(library.booklib[i].type == "数学类")
        {
            book = library.booklib[i];
            math.push_back(book);
        }
        else if(library.booklib[i].type == "文学类")
        {
            book = library.booklib[i];
            literature.push_back(book);
        }
        else if(library.booklib[i].type == "历史类")
        {
            book = library.booklib[i];
            history.push_back(book);
        }
        else if(library.booklib[i].type == "艺术类")
        {
            book = library.booklib[i];
            art.push_back(book);
        }
        else if(library.booklib[i].type == "通信类")
        {
            book = library.booklib[i];
            communication.push_back(book);
        }
        else if(library.booklib[i].type == "医学类")
        {
            book = library.booklib[i];
            medicine.push_back(book);
        }
        else if(library.booklib[i].type == "经济类")
        {
            book = library.booklib[i];
            economy.push_back(book);
        }
        else
        {
            book = library.booklib[i];
            other.push_back(book);
        }
    }
}
