#include "studentinterface.h"
#include "ui_studentinterface.h"
#include "login.h"
#include "mainwindow.h"
#include "borrowbook.h"
#include "backbook.h"
#include "allbook.h"
#include "orderbook.h"
#include "personalinfo.h"
#include "allclass.h"
#include "changeclient.h"
#include "displayinfo.h"
#include "displaybookinfo.h"
#include "studentborrowbook.h"
#include <QScrollBar>
#include <QMessageBox>
#include <QSlider>
#include <QTextStream>
#include <QLabel>
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QFont>
#include <htmlhelp.h>

extern book_shelf library;
extern int year;
extern int month;
extern int day;

vector<sinbook> computer;
vector<sinbook> math;
vector<sinbook> literature;
vector<sinbook> history;
vector<sinbook> art;
vector<sinbook> communication;
vector<sinbook> medicine;
vector<sinbook> economy;
vector<sinbook> other;


extern string str;                    //当前登录用户账号

StudentInterface::StudentInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentInterface)
{
    ui->setupUi(this);
    this->setFixedSize(1000,600);
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
    //library.order_dele_book(str);
}

StudentInterface::~StudentInterface()
{
    delete ui;
}

string inttostring1(int i);
bool isMylend(string bookID);
void StudentInterface::orderTip(QString str1,int time)
{
    sinbook book;
    boclient client;
    client = library.id_to_client(str1.toStdString());
    for(int i=0;i<(int)client.orderbooknum;i++)
    {
        qDebug()<<i;
        book = library.id_to_book(client.orderbookid[i]);
        qDebug("and here");
        qDebug()<<QString::fromStdString(book.author);
        qDebug()<<book.state;
        if(book.state==1)
        {

            ui->oredertips->append("您预约的书："+QString::fromStdString(book.name)+"  在馆内，您可以借阅");
            qDebug("wtf");
        }
        else if(book.state==0)
        {
            int k=0;
            for(int j=0;j<client.borrownum;++j)
            {
                if(client.borrowid[j]==book.id)
                {
                    ++k;
                    for (int j = 0;j<(int)library.bor_record.size();j++)   //改预约记录
                    {
                        if(library.bor_record[j].bor_book_id == client.orderbookid[i]&&library.bor_record[j].type_comm == 2&&library.bor_record[j].retu_book==0)
                        {
                            library.bor_record[j].retu_book==library.book_system_time;
                            break;
                        }
                    }
                }
            }
            if(k==0)
                ui->oredertips->append("您预约的书："+QString::fromStdString(book.name)+"  仍被借阅");
        }
        else
            ui->oredertips->append("您预约的书："+QString::fromStdString(book.name)+"  已被删除");
    }
    qDebug()<<time;
    ui->time->setText(QString::number(year)+"年"+QString::number(month)+"月"+QString::number(day)+"日");
}

bool isMylend(string bookID)
{
    boclient client;
    client = library.id_to_client(str);
    qDebug()<<QString::fromStdString(str);
    for(int i=0;i<client.borrownum;++i)
    {
        if(client.borrowid[i]==bookID)
            return true;
    }
    return false;
}

void StudentInterface::on_ExitBtn_clicked()
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

void StudentInterface::on_borrowBtn_clicked()                                   //借书功能
{
    studentborrowbook *borrow = new studentborrowbook();
    borrow->setModal(true);
    borrow->show();
}

void StudentInterface::on_backBtn_clicked()
{
    backbook *back = new backbook();
    back->setModal(true);
    back->show();
}

void StudentInterface::on_allbookBtn_clicked()
{
    allbook *all = new allbook();
    all->setModal(true);
    all->show();
}

void StudentInterface::on_orderBtn_clicked()
{
    orderbook *order = new orderbook();
    order->setModal(true);
    order->show();
}

void StudentInterface::on_textBrowser_objectNameChanged(const QString &objectName)
{

}


boclient client;
void StudentInterface::on_personalinfoBtn_clicked()
{
    personalinfo *person = new personalinfo();

    client = library.id_to_client(str);

    person->play();
    person->setModal(true);
    person->show();
}


string inttostring1(int i)
{
    stringstream ss;
    ss<<i;
    return ss.str();
}


extern string id;                   //要修改的ID

void StudentInterface::on_changeMyinfo_clicked()
{
    id = str;
    changeclient *changecli = new changeclient();
    changecli->setModal(true);
    changecli->show();
}

sinbook book;
int TYPE=0;
void StudentInterface::on_listWidget_doubleClicked(const QModelIndex &index)
{
    displaybookinfo *display = new displaybookinfo();
    switch(TYPE)
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


int searchType = 0;
void StudentInterface::on_name_clicked()
{
    searchType = 1;
}

void StudentInterface::on_auther_clicked()
{
    searchType = 2;
}

void StudentInterface::on_type_clicked()
{
    searchType = 3;
}

void StudentInterface::on_press_clicked()
{
    searchType = 4;
}



void StudentInterface::on_searchBtn_clicked()
{
    QString searchStr = ui->search->text();
    if(searchStr == NULL)
        QMessageBox::warning(this, tr("提示！"),
                             tr("请输入查询内容！"),
                             QMessageBox::Yes);
    switch (searchType){
        case 0:
        if(!(searchStr == NULL))
        QMessageBox::warning(this, tr("提示！"),
                                     tr("请选择查询类型！"),
                                     QMessageBox::Yes);
            break;
        case 1:
            ui->listWidget->clear();
            //QString name = ui->name->text();
            if(TYPE == 0)
                for(int i = 0, j = 0; i<library.booklib.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(library.booklib[i].name)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(library.booklib[i].name));
                        swap(library.booklib[i],library.booklib[j]);
                        ++j;
                    }
                }
            else if(TYPE == 1)
                for(int i = 0,j=0; i<computer.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(computer[i].name)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(computer[i].name));
                        swap(computer[i],computer[j]);
                        ++j;
                    }
                }
            else if(TYPE == 2)
                for(int i = 0,j=0; i<math.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(math[i].name)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(math[i].name));
                        swap(math[i],math[j]);
                        ++j;
                    }
                }
            else if(TYPE == 3)
                for(int i = 0,j=0; i<literature.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(literature[i].name)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(literature[i].name));
                        swap(literature[i],literature[j]);
                        ++j;
                    }
                }
            else if(TYPE == 4)
                for(int i = 0,j=0; i<history.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(history[i].name)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(history[i].name));
                        swap(history[i],history[j]);
                        ++j;
                    }
                }
            else if(TYPE == 5)
                for(int i = 0,j=0; i<art.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(art[i].name)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(art[i].name));
                        swap(art[i],art[j]);
                        ++j;
                    }
                }
            else if(TYPE == 6)
                for(int i = 0,j=0; i<communication.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(communication[i].name)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(communication[i].name));
                        swap(communication[i],communication[j]);
                        ++j;
                    }
                }
            else if(TYPE == 7)
                for(int i = 0,j=0; i<medicine.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(medicine[i].name)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(medicine[i].name));
                        swap(medicine[i],medicine[j]);
                        ++j;
                    }
                }
            else if(TYPE == 8)
                for(int i = 0,j=0; i<economy.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(economy[i].name)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(economy[i].name));
                        swap(economy[i],economy[j]);
                        ++j;
                    }
                }
            else
                for(int i = 0,j=0; i<other.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(other[i].name)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(other[i].name));
                        swap(other[i],other[j]);
                        ++j;
                    }
                }
            break;
        case 2:
            ui->listWidget->clear();
            //QString auther = ui->auther->text();
            if(TYPE == 0)
                for(int i = 0, j = 0; i<library.booklib.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(library.booklib[i].author)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(library.booklib[i].name));
                        swap(library.booklib[i],library.booklib[j]);
                        ++j;
                    }
                }
            else if(TYPE == 1)
                for(int i = 0,j=0; i<computer.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(computer[i].author)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(computer[i].name));
                        swap(computer[i],computer[j]);
                        ++j;
                    }
                }
            else if(TYPE == 2)
                for(int i = 0,j=0; i<math.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(math[i].author)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(math[i].name));
                        swap(math[i],math[j]);
                        ++j;
                    }
                }
            else if(TYPE == 3)
                for(int i = 0,j=0; i<literature.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(literature[i].author)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(literature[i].name));
                        swap(literature[i],literature[j]);
                        ++j;
                    }
                }
            else if(TYPE == 4)
                for(int i = 0,j=0; i<history.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(history[i].author)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(history[i].name));
                        swap(history[i],history[j]);
                        ++j;
                    }
                }
            else if(TYPE == 5)
                for(int i = 0,j=0; i<art.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(art[i].author)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(art[i].name));
                        swap(art[i],art[j]);
                        ++j;
                    }
                }
            else if(TYPE == 6)
                for(int i = 0,j=0; i<communication.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(communication[i].author)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(communication[i].name));
                        swap(communication[i],communication[j]);
                        ++j;
                    }
                }
            else if(TYPE == 7)
                for(int i = 0,j=0; i<medicine.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(medicine[i].author)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(medicine[i].name));
                        swap(medicine[i],medicine[j]);
                        ++j;
                    }
                }
            else if(TYPE == 8)
                for(int i = 0,j=0; i<economy.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(economy[i].author)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(economy[i].name));
                        swap(economy[i],economy[j]);
                        ++j;
                    }
                }
            else
                for(int i = 0,j=0; i<other.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(other[i].author)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(other[i].name));
                        swap(other[i],other[j]);
                        ++j;
                    }
                }
            break;
        case 3:

            break;
        case 4:
            ui->listWidget->clear();
            //QString press = ui->press->text();
            if(TYPE == 0)
                for(int i = 0, j = 0; i<library.booklib.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(library.booklib[i].press)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(library.booklib[i].name));
                        swap(library.booklib[i],library.booklib[j]);
                        ++j;
                    }
                }
            else if(TYPE == 1)
                for(int i = 0,j=0; i<computer.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(computer[i].press)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(computer[i].name));
                        swap(computer[i],computer[j]);
                        ++j;
                    }
                }
            else if(TYPE == 2)
                for(int i = 0,j=0; i<math.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(math[i].press)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(math[i].name));
                        swap(math[i],math[j]);
                        ++j;
                    }
                }
            else if(TYPE == 3)
                for(int i = 0,j=0; i<literature.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(literature[i].press)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(literature[i].name));
                        swap(literature[i],literature[j]);
                        ++j;
                    }
                }
            else if(TYPE == 4)
                for(int i = 0,j=0; i<history.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(history[i].press)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(history[i].name));
                        swap(history[i],history[j]);
                        ++j;
                    }
                }
            else if(TYPE == 5)
                for(int i = 0,j=0; i<art.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(art[i].press)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(art[i].name));
                        swap(art[i],art[j]);
                        ++j;
                    }
                }
            else if(TYPE == 6)
                for(int i = 0,j=0; i<communication.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(communication[i].press)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(communication[i].name));
                        swap(communication[i],communication[j]);
                        ++j;
                    }
                }
            else if(TYPE == 7)
                for(int i = 0,j=0; i<medicine.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(medicine[i].press)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(medicine[i].name));
                        swap(medicine[i],medicine[j]);
                        ++j;
                    }
                }
            else if(TYPE == 8)
                for(int i = 0,j=0; i<economy.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(economy[i].press)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(economy[i].name));
                        swap(economy[i],economy[j]);
                        ++j;
                    }
                }
            else
                for(int i = 0,j=0; i<other.size();++i)
                {
                    if(!searchStr.compare(QString::fromStdString(other[i].press)))
                    {
                        ui->listWidget->addItem(QString::fromStdString(other[i].name));
                        swap(other[i],other[j]);
                        ++j;
                    }
                }
            break;
    }
}

void StudentInterface::on_pushButton_clicked()
{
    TYPE = 0;
    ui->listWidget->clear();
    for(int i = 0; i<library.booklib.size();++i)
    {
        QString name = QString::fromStdString(library.booklib[i].name);

        if(library.booklib[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(library.booklib[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");
    }
}

void StudentInterface::on_computerBtn_clicked()
{
    TYPE = 1;
    ui->listWidget->clear();
    for(int i = 0; i<computer.size();++i)
    {
        QString name = QString::fromStdString(computer[i].name);
        if(computer[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(computer[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");
    }
}

void StudentInterface::on_mathBtn_clicked()
{
    TYPE = 2;
    ui->listWidget->clear();
    for(int i = 0; i<math.size();++i)
    {
        QString name = QString::fromStdString(math[i].name);
        if(math[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(math[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");
    }
}

void StudentInterface::on_literatureBtn_clicked()
{
    TYPE = 3;
    ui->listWidget->clear();
    for(int i = 0; i<literature.size();++i)
    {
        QString name = QString::fromStdString(literature[i].name);
        if(literature[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(literature[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");
    }
}

void StudentInterface::on_historyBtn_clicked()
{
    TYPE = 4;
    ui->listWidget->clear();
    for(int i = 0; i<history.size();++i)
    {
        QString name = QString::fromStdString(history[i].name);
        if(history[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(history[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");      }
}

void StudentInterface::on_artBtn_clicked()
{
    TYPE = 5;
    ui->listWidget->clear();
    for(int i = 0; i<art.size();++i)
    {
        QString name = QString::fromStdString(art[i].name);
        if(art[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(art[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");     }
}

void StudentInterface::on_communicationBtn_clicked()
{
    TYPE = 6;
    ui->listWidget->clear();
    for(int i = 0; i<communication.size();++i)
    {
        QString name = QString::fromStdString(communication[i].name);
        if(communication[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(communication[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");    }
}

void StudentInterface::on_medicineBtn_clicked()
{
    TYPE = 7;
    ui->listWidget->clear();
    for(int i = 0; i<medicine.size();++i)
    {
        QString name = QString::fromStdString(medicine[i].name);
        if(medicine[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(medicine[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");     }
}

void StudentInterface::on_economyBtn_clicked()
{
    TYPE = 8;
    ui->listWidget->clear();
    for(int i = 0; i<economy.size();++i)
    {
        QString name = QString::fromStdString(economy[i].name);
        if(economy[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(economy[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");    }
}

void StudentInterface::on_otherBtn_clicked()
{
    TYPE = 9;
    ui->listWidget->clear();
    for(int i = 0; i<other.size();++i)
    {
        QString name = QString::fromStdString(other[i].name);
        if(other[i].state == 0)
            ui->listWidget->addItem(name+"  (被借)");
        else if(other[i].state == 1)
            ui->listWidget->addItem(name+"  (在库)");    }
}

void StudentInterface::on_timecontrolBtn_clicked()
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

void StudentInterface::on_renew_clicked()
{
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
