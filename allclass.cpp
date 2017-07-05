#include "allclass.h"
#include<QDebug>
#include "QMessageBox"
#include "studentinterface.h"
#include "borrowbook.h"
#include "backbook.h"
using namespace std;


int Cur_log_denti=0;


int str_dist(const string source,const string target)
{
    //step 1

    int n=source.length();
    int m=target.length();
    if (m==0) return n;
    if (n==0) return m;
    //Construct a matrix
    typedef vector< vector<int> >  Tmatrix;
    Tmatrix matrix(n+1);
    for(int i=0; i<=n; i++)  matrix[i].resize(m+1);

    //step 2 Initialize

    for(int i=1;i<=n;i++) matrix[i][0]=i;
    for(int i=1;i<=m;i++) matrix[0][i]=i;

     //step 3
     for(int i=1;i<=n;i++)
     {
        const char si=source[i-1];
        //step 4
        for(int j=1;j<=m;j++)
        {

            const char dj=target[j-1];
            //step 5
            int cost;
            if(si==dj){
                cost=0;
            }
            else{
                cost=1;
            }
            //step 6
            const int above=matrix[i-1][j]+1;
            const int left=matrix[i][j-1]+1;
            const int diag=matrix[i-1][j-1]+cost;
            matrix[i][j]=min(above,min(left,diag));

        }
     }//step7
      return matrix[n][m];
}

int stringtoint(string s)//基本函数
{
    int num;
    stringstream ss(s);
    ss>>num;
    return num;
}

string inttostring(int i)
{
    stringstream ss;
    ss<<i;
    return ss.str();
}


void introduction(book_singal b)
{
    cout<<"this book has a name of "<<b.name
        <<",wroten by "<<b.author
        <<",type is "<<b.type
        <<",press is "<<b.press<<endl;
}

book_shelf::~book_shelf()                                                                     //析构函数
{
}


book_shelf::book_shelf()                                                             //构造函数
{
}


/*******************************************************************************************************************************/
sinbook & book_shelf::id_to_book(string bokide)        //书的id对应书结构
{
    for(int i=0;i<(int)booklib.size(); i++)
    {
        if(bokide==booklib[i].id)
            return booklib[i];
    }
    cout<<"no book!"<<endl;
}

boclient & book_shelf::id_to_client(string cli_gr)
{
    for(int i=0; i<(int)suclient.size(); i++)
    {
        if(cli_gr==suclient[i].clid)
            return suclient[i];
    }
    cout<<"no body!"<<endl;
}

int book_shelf::judg_ord_suc(string okid,string inid)
{
    for(int i=0; i<id_to_client(inid).orderbooknum; i++)
    {
        if(id_to_client(inid).orderbookid[i]==okid&&(id_to_book(okid).state==3))
            return 1;
    }
    return 0;
}

void book_shelf::statistic()                                       //统计所有信息
{
    int bonum,renum,unret,monu;//统计借书量，还书量，没换书的数目，营业额
    bonum=0;
    renum=0;
    unret=0;
    monu=0;
    for(int i=0;i<(int)bor_record.size();i++)
    {
        if((bor_record[i].type_comm==1)&&(book_system_time-bor_record[i].bor_time<300))
        {
            cout<<id_to_book(bor_record[i].bor_book_id).name<<"被借"<<endl;
            //cout<<bor_record[i].bor_book_id<<endl;
            cout<<"借书人ID："<<bor_record[i].bor_client_id<<endl;
            //cout<<"借书人姓名："<<library.id_to_client(bor_record[i].bor_client_id).name<<endl;
            ++bonum;
        }
        if((bor_record[i].type_comm==1)&&((book_system_time-bor_record[i].retu_book<300)))
        {
            cout<<id_to_book(bor_record[i].bor_book_id).name<<"被还"<<endl;
            //cout<<bor_record[i].bor_book_id<<endl;
            cout<<"还书人ID："<<bor_record[i].bor_client_id<<endl;
            //cout<<"还书人姓名："<<library.id_to_client(bor_record[i].bor_client_id).name<<endl;
            ++renum;
        }
        if(bor_record[i].retu_book==0)
        {
            cout<<id_to_book(bor_record[i].bor_book_id).name<<"未被还"<<endl;
            //cout<<bor_record[i].bor_book_id<<endl;
            cout<<"借书人ID："<<bor_record[i].bor_client_id<<endl;
            //cout<<"借书人姓名："<<library.id_to_client(bor_record[i].bor_client_id).name<<endl;
            ++unret;
        }
        monu=monu+bor_record[i].bookfine;
    }
    cout<<"本月被借走的书的数量:"<<bonum<<endl;
    cout<<"本月被还回的书的数量:"<<renum<<endl;
    cout<<"还未被还回的书的数量:"<<unret<<endl;
    cout<<"本月罚款收入:"<<monu<<endl;
}


int owetoomuch=0;                     //为1表示欠款太多
int borrowtoomuch=0;                  //为1表示借书过量
int notpower=0;                       //为1表示没有借书权限
int succeed=0;                        //为1表示借书成功
int nobook=0;                         //为1表示此书不存在或被借走
void book_shelf::borr_book(string bookid,string clinid,int days)
{

    if(id_to_client(clinid).honestlevel>5)                       //决策树
        cout<<"You are on the blacklist!"<<endl;
    else
    {
        if(id_to_client(clinid).Arrears_money>10.0)
        {

            cout<<"你已经欠了太多金额!"<<endl;//此处可以添加还钱链接！以后添加吧！并不是主要程序，不优先
            /*QMessageBox::warning(borrow,"警告！",
                                   "您欠款过多！",
                                   QMessageBox::Yes);*/
            owetoomuch=1;
            qDebug("bb");
        }
        else
        {
            if(id_to_client(clinid).borrownum>4)
            {
                cout<<"你已经借了太多的书!"<<endl;//此处可以添加还书链接！
                /*QMessageBox::warning(borrow, "警告！",
                                       "您借书过多！",
                                       QMessageBox::Yes);*/
                borrowtoomuch=1;
                qDebug("cc");
            }
            else
            {

                //
                if(id_to_book(bookid).state==1)
                {
                    if(id_to_book(bookid).borrowpermission==0&&(id_to_client(clinid).client_identity==1||id_to_client(clinid).client_identity == 2))
                    {
                        cout<<"您没有权限借阅!"<<endl;
                        /*QMessageBox::warning(borrow, "提示！",
                                               "您没有权限借该书！",
                                               QMessageBox::Yes);*/
                        notpower=1;
                        qDebug("dd");
                    }
                    else
                    {
                        qDebug("ee");
                        borrow_mass exml;
                        exml.bor_book_id=bookid;
                        exml.bor_client_id=clinid;
                        exml.bor_time=book_system_time;
                        cout<<"请输入您的借阅时间（天）:";
                        exml.bor_term = days;  //可以加一个输入检查
                        exml.bor_term=exml.bor_term*10;
                        exml.bookfine=0;
                        exml.type_comm = 1;
                        exml.retu_book=0;
                        if (Cur_log_denti == 1)
                            exml.bor_way = "admin";//后期写登陆以后可以写服务类型
                        else
                            exml.bor_way = "yourself";

                        bor_record.push_back(exml);//填写借书记录完毕，开始修改信息


                        QString str = QString::fromStdString(clinid);
                        id_to_client(clinid).borrowid[id_to_client(clinid).borrownum]=bookid;
                        ++(id_to_client(clinid).borrownum);//修改完顾客信息
                        id_to_book(bookid).state=0;
                        succeed=1;
                    }
                   //judg_ord_suc(bookid,clinid)=1;
                }
                else if(judg_ord_suc(bookid,clinid)==1)//预约成功
                {
                    qDebug("ff");
                    borrow_mass exml;
                    exml.bor_book_id=bookid;
                    exml.bor_client_id=clinid;
                    exml.bor_time=book_system_time;
                    cout<<"please input the term you want borrow:";
                    cin>>exml.bor_term;//可以加一个输入检查
                    exml.bookfine=0;
                    exml.retu_book=0;
                    exml.type_comm = 1;
                    if (Cur_log_denti == 1)
                        exml.bor_way = "admin";//后期写登陆以后可以写服务类型
                    else
                        exml.bor_way = "yourself";//后期写登陆以后可以写服务类型
                    bor_record.push_back(exml);//填写借书记录完毕，开始修改信息

                    for(int i=0;i<id_to_client(clinid).orderbooknum;i++)//从预约菜单中删除借的书
                    {
                        if(id_to_client(clinid).orderbookid[i]==bookid)
                            id_to_client(clinid).orderbookid[i]=id_to_client(clinid).orderbookid[id_to_client(clinid).orderbooknum];
                    }
                    --id_to_client(clinid).orderbooknum;
                    id_to_client(clinid).borrowid[id_to_client(clinid).borrownum]=bookid;
                    ++id_to_client(clinid).borrownum;//修改完顾客信息

                    id_to_book(bookid).state=0;
                    cout<<"您已成功借阅此书, 享受生活，享受阅读!"<<endl;
                    /*QMessageBox::warning(borrow, "提示！",
                                           "借书成功！",
                                           QMessageBox::Yes);*/
                    succeed=1;
                }
                else
                    nobook=1;
                   /*QMessageBox::warning(borrow,"警告！",
                                      "该书不存在或已被借走！",
                                      QMessageBox::Yes);*/

            }
        }
    }
}

int temp_c=0;                         //为0代表书ID错误，为1代表还书成功
void book_shelf::back_book(string bookid)
{
    for (int i = 0;i<(int)bor_record.size();i++)
    {
        if (bor_record[i].bor_book_id == bookid&&bor_record[i].type_comm == 1&&bor_record[i].retu_book==0)
        {
            string temp_client = bor_record[i].bor_client_id;
            //修改人
            for (int j = 0;j < id_to_client(temp_client).borrownum;j++)
            {
                if (id_to_client(temp_client).borrowid[j] == bookid)
                {
                    id_to_client(temp_client).borrowid[j] = id_to_client(temp_client).borrowid[id_to_client(temp_client).borrownum - 1];
                    break;
                }
            }
            --(id_to_client(temp_client).borrownum);
            if (((book_system_time - bor_record[i].bor_time) - bor_record[i].bor_term) > 0)
            {++(id_to_client(temp_client).honestlevel);

            id_to_client(temp_client).Arrears_money += ((book_system_time - bor_record[i].bor_time) - (bor_record[i].bor_term))*id_to_book(bookid).price / 50;
            bor_record[i].bookfine = ((book_system_time - bor_record[i].bor_time) - (bor_record[i].bor_term))*id_to_book(bookid).price / 50;
            }//修改书
            id_to_book(bookid).state = 1;

            //修改记录
            bor_record[i].retu_book = book_system_time;

            temp_c=1;
            break;
        }
    }
    if(temp_c==0)
        cout<<"请检查书ID！";
        /*QMessageBox::warning(back,"警告！",
                               "请检查书ID！",
                               QMessageBox::Yes);*/

    else
        cout<<"还书成功！";
        /*QMessageBox::warning(back,"提示！",
                               "还书成功！",
                               QMessageBox::Yes);*/
}


extern vector<sinbook> computer;
extern vector<sinbook> math;
extern vector<sinbook> literature;
extern vector<sinbook> history;
extern vector<sinbook> art;
extern vector<sinbook> communication;
extern vector<sinbook> medicine;
extern vector<sinbook> economy;
extern vector<sinbook> other;
void book_shelf::delet_book(string bookid)
{
    vector<sinbook>::iterator it;
    int i = 0;
    for (it = booklib.begin();it != booklib.end();i++)
    {
        if (booklib[i].id == bookid)
        {
            it = booklib.erase(it);
            break;
        }
        ++it;
    }
    i=0;
    for (it = computer.begin();it != computer.end();i++)
    {
        if (computer[i].id == bookid)
        {
            it = computer.erase(it);
            break;
        }
        ++it;
    }
    i=0;
    for (it = math.begin();it != math.end();i++)
    {
        if (math[i].id == bookid)
        {
            it = math.erase(it);
            break;
        }
        ++it;
    }
    i=0;
    for (it = literature.begin();it != literature.end();i++)
    {
        if (literature[i].id == bookid)
        {
            it = literature.erase(it);
            break;
        }
        ++it;
    }
    i=0;
    for (it = history.begin();it != history.end();i++)
    {
        if (history[i].id == bookid)
        {
            it = history.erase(it);
            break;
        }
        ++it;
    }
    i=0;
    for (it = art.begin();it != art.end();i++)
    {
        if (art[i].id == bookid)
        {
            it = art.erase(it);
            break;
        }
        ++it;
    }
    i=0;
    for (it = communication.begin();it != communication.end();i++)
    {
        if (communication[i].id == bookid)
        {
            it = communication.erase(it);
            break;
        }
        ++it;
    }
    i=0;
    for (it = medicine.begin();it != medicine.end();i++)
    {
        if (medicine[i].id == bookid)
        {
            it = medicine.erase(it);
            break;
        }
        ++it;
    }
    i=0;
    for (it = economy.begin();it != economy.end();i++)
    {
        if (economy[i].id == bookid)
        {
            it = economy.erase(it);
            break;
        }
        ++it;
    }
    i=0;
    for (it = other.begin();it != other.end();i++)
    {
        if (other[i].id == bookid)
        {
            it = other.erase(it);
            break;
        }
        ++it;
    }
}


int orderowetoomuch = 0;
int orderbookdeleted = 0;
int order_book_in_library=0;
int order_succeed = 0;
void book_shelf::order_book(string bookid, string clinid)
{
    if (id_to_client(clinid).honestlevel>5)                       //决策树
        cout << "You are on the blacklist!" << endl;
    else
    {
        if (id_to_client(clinid).Arrears_money > 10.0)
        {
            cout << "You already owe too much money!" << endl;//此处可以添加还钱链接！以后添加吧！并不是主要程序，不优先
            orderowetoomuch = 1;
        }
        else
        {
            if (id_to_book(bookid).state == 1)
            {
                order_book_in_library = 1;
            }
            else
            {
                if (id_to_book(bookid).state == 2)
                    orderbookdeleted = 1;
                else
                {
                    id_to_client(clinid).orderbookid[id_to_client(clinid).orderbooknum] = bookid;
                    ++(id_to_client(clinid).orderbooknum);//对客户的影响

                    borrow_mass exml;//产生一个预约记录
                    exml.bor_book_id = bookid;
                    exml.bor_client_id = clinid;
                    exml.bor_time = book_system_time;
                    exml.bor_term = 300;
                    if (Cur_log_denti == 1)
                        exml.bor_way = "admin";//后期写登陆以后可以写服务类型
                    else
                        exml.bor_way = "yourself";
                    exml.bookfine = 0;
                    exml.retu_book = 0;
                    exml.type_comm = 2;
                    bor_record.push_back(exml);//填写预约记录完毕
                    cout << "order success!" << endl;
                    order_succeed = 1;
                }
            }
        }
    }
}


void book_shelf::order_dele_book(string clinid)
{
    if((int)id_to_client(clinid).orderbooknum==0)
        return;
    cout<<"你已经预约了以下书，以及他们现在的状态："<<endl;
    vector <int> reserve;
    string serbook[(int)id_to_client(clinid).orderbooknum];
    for(int i=0;i<(int)id_to_client(clinid).orderbooknum;i++)
    {
        cout<<"书名"<<id_to_book(id_to_client(clinid).orderbookid[i]).name;
        serbook[i]=id_to_client(clinid).orderbookid[i];
        if(id_to_book(id_to_client(clinid).orderbookid[i]).state==1)
        {
            cout<<"在馆！"<<endl;
            cout<<"输入1，借书，其他，忽略"<<endl;
            int tempp;
            cin>>tempp;
            if(tempp==1)
                borr_book(id_to_client(clinid).orderbookid[i],clinid,0);//人的记录最后清理
            for (int j = 0;j<(int)bor_record.size();j++)
            {
                if(bor_record[j].bor_book_id == id_to_client(clinid).orderbookid[j]&&bor_record[j].type_comm == 2&&bor_record[j].retu_book==0)
                {
                    bor_record[j].retu_book==book_system_time;
                    break;
                }
            }

        }
        else if(id_to_book(id_to_client(clinid).orderbookid[i]).state==0)
             {
                 cout<<"借出！"<<endl;
                 reserve.push_back(i);
             }
        else
            cout<<"书被删除！"<<endl;


        /*if(id_to_book(id_to_client(clinid).orderbookid[i]).state==1)
        {

            cout<<"you order book"<<id_to_client(clinid).orderbookid[i]<<"arrive,input 1 to borrow,others ignore:";
            //清理人

            int tempp;
            cin>>tempp;
            if(tempp==1)
                borr_book(id_to_client(clinid).orderbookid[i],clinid);
            string w;
            w=id_to_client(clinid).orderbookid[i];
            id_to_client(clinid).orderbookid[i]=id_to_client(clinid).orderbookid[id_to_client(clinid).orderbooknum-1];
            --id_to_client(clinid).orderbooknum;

            for(int j=0;j<(int)bor_record.size();j++)
            {
                if(bor_record[j].type_comm==2&&bor_record[j].bor_book_id==w)
                    bor_record[j].retu_book=book_system_time;
            }//销毁所有有关的图书记录
        }
        */
    }
    for(int i=0;i<(int)reserve.size();i++)
    {
        id_to_client(clinid).orderbookid[i]=serbook[reserve[i]];
    }
    id_to_client(clinid).orderbooknum=(int)reserve.size();
    return;
}


void book_shelf::displaybook(sinbook boid)
{
    cout<<"\ntype:"<<boid.type<<"\tbuytime:"<<boid.buytime
        <<"\tname:"<<boid.name<<"\tauthor:"<<boid.author
        <<"\tpress:"<<boid.press<<"\tprice:"<<boid.price
        <<"\tbookid:"<<boid.id<<endl;
}

void book_shelf::displaybook()
{
    int i=0;
    for(i;i<(int)booklib.size();i++)
    {
        displaybook(booklib[i]);
    }
}

void book_shelf::display_client(boclient cl_id)
{
    cout<<"\nname:"<<cl_id.name;
    if(cl_id.client_identity==0)
        cout<<"\ttype:teacher";
    else if(cl_id.client_identity==2)
        cout<<"\ttype:manager";
    else
        cout<<"\ttype:student";
    cout<<"\tinstitute:"<<cl_id.institute<<"\tcreattime:"<<cl_id.creat_time
        <<"\tid:"<<cl_id.clid<<"\thonest tevel:"<<cl_id.honestlevel;
        if(cl_id.Arrears_money<0)
            cout<<"\tmoney:0"<<"   您还有："<<0-cl_id.Arrears_money<<"RMB"<<endl;
        else
            cout<<"\tmoney:"<<cl_id.Arrears_money<<endl;
    if(cl_id.borrownum>0)
    {
        cout<<"you have borrowed "<<cl_id.borrownum<<"book,interesting!"<<endl;
        for(int i=0; i<cl_id.borrownum; i++)
            {//displaybook(id_to_book(cl_id.borrowid[i]));
            cout<<cl_id.borrowid[i]<<endl;}
    }
    else
        cout<<"no borrow information!"<<endl;
    if(cl_id.orderbooknum==0)
        cout<<"no order book information!"<<endl;
    else
    {
        cout<<"you have ordered "<<cl_id.orderbooknum<<"book,interesting!"<<endl;
        for(int i=0; i<cl_id.orderbooknum; i++)
        {
            if(id_to_book(cl_id.orderbookid[i]).state==1)
                cout<<"your order book"<<id_to_book(cl_id.orderbookid[i]).name<<"are ready!"<<endl;
            else if(id_to_book(cl_id.orderbookid[i]).state==2)
                cout<<"your order book"<<id_to_book(cl_id.orderbookid[i]).name<<"have been delete!"<<endl;
            else if(id_to_book(cl_id.orderbookid[i]).state==0)
                cout<<"your order book"<<id_to_book(cl_id.orderbookid[i]).name<<"have been borrow by others!"<<endl;
        }
    }
}

void book_shelf::display_client()
{
    int i=0;
    for(i;i<(int)suclient.size();i++)
    {
        display_client(suclient[i]);
    }
}

unsigned int RSHash(string mas)              //hash函数
{
    const char *str = mas.c_str();
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * a + (*str++);
        a *= b;
    }

    return (hash  & 0x3FFF);
}

string code(sinbook bbkk)                    //最大允许有10本相同的书
{
    string exmname;
    exmname=bbkk.name;
    string exmpress;
    exmpress=bbkk.press;
    fstream fin("C:\\Users\\lenovo\\Documents\\Test\\document\\code_dictionary.txt");
    int namecode=0;
    while(!fin.eof())
    {
        string rubbish2;
        string ename;
        string epress;
        string eauthor;
        getline(fin,ename);
        getline(fin,epress);
        getline(fin,eauthor);
        if(ename==exmname&&epress==exmpress&&eauthor==bbkk.author)
        {
            string enumber;
            getline(fin,enumber);
            namecode=stringtoint(enumber)-(stringtoint(enumber)/10)*10+1;
            getline(fin,rubbish2);
        }
        else
            getline(fin,rubbish2);
    }
    fin.close();
    bbkk.id=inttostring(RSHash(exmname))+inttostring(RSHash(exmpress))+inttostring(namecode);
    ofstream fout("C:\\Users\\lenovo\\Documents\\Test\\document\\code_dictionary.txt",ios::out|ios::app);
    fout<<bbkk.name<<endl;
    fout<<bbkk.press<<endl;
    fout<<bbkk.author<<endl;
    fout<<bbkk.id<<endl;
    fout.close();
    return bbkk.id;
}

string codclient(boclient boktemp)           //人员编码函数
{
    string exmname;
    exmname=boktemp.name;//kehuxingming
    string exmins;
    exmins=boktemp.institute;//kehuxueyuan
    fstream fin("C:\\Users\\lenovo\\Documents\\Test\\document\\code_dic_cli.txt");
    int namecode=0;
    while(!fin.eof())
    {
        string rubbish;
        string ename;
        string epress;
        getline(fin,ename);
        getline(fin,epress);
        if(ename==exmname&&epress==exmins)
        {
            string enumber;
            getline(fin,enumber);
            namecode=stringtoint(enumber)-(stringtoint(enumber)/10)*10+1;
        }
        else
            getline(fin,rubbish);
    }
    fin.close();
    boktemp.clid=inttostring(RSHash(exmname))+inttostring(RSHash(exmins))+inttostring(namecode);
    ofstream fout("C:\\Users\\lenovo\\Documents\\Test\\document\\code_dic_cli.txt",ios::out|ios::app);
    fout<<boktemp.name<<endl;
    fout<<boktemp.institute<<endl;
    fout<<boktemp.clid<<endl;
    fout.close();
    return boktemp.clid;
}



void book_shelf::buybook(string booktype,string bookname,string bookauther,int booknum,string bookpress,double bookprice,int bookpermission)                            //买书会存书
{
    sinbook temp_book[booknum];
    for(int i = 0; i<booknum; ++i)
    {
        temp_book[i].type = booktype;
        temp_book[i].name = bookname;
        temp_book[i].author = bookauther;
        temp_book[i].press = bookpress;
        temp_book[i].price = bookprice;
        temp_book[i].borrowpermission = bookpermission;

        temp_book[i].state = 1;
        temp_book[i].buytime = book_system_time;

        temp_book[i].id = QString::number((QString::fromStdString(code(temp_book[i])).toInt()+i)).toStdString();
        //qDebug()<<QString::fromStdString(temp_book[i].id);
    }

    for(int i = 0; i< booknum; ++i)
    {
        booklib.push_back(temp_book[i]);
        if(booktype == "计算机类")
        {
            computer.push_back(temp_book[i]);
        }
        else if(booktype == "数学类")
        {
            math.push_back(temp_book[i]);
        }
        else if(booktype == "文学类")
        {
            literature.push_back(temp_book[i]);
        }
        else if(booktype == "历史类")
        {
            history.push_back(temp_book[i]);
        }
        else if(booktype == "艺术类")
        {
            art.push_back(temp_book[i]);
        }
        else if(booktype == "通信类")
        {
            communication.push_back(temp_book[i]);
        }
        else if(booktype == "医学类")
        {
            medicine.push_back(temp_book[i]);
        }
        else if(booktype == "经济类")
        {
            economy.push_back(temp_book[i]);
        }
        else
        {
            other.push_back(temp_book[i]);
        }
    }
}

void book_shelf::new_client(string name,string password,int iden,string institute)                         //新建人员信息
{
    boclient tempcli;
    cout<<"please input the client name:";
    tempcli.name = name;
    cout<<"please input the client password:";
    tempcli.cli_pass_word = password;
    cout<<"please input the client client_identity:";
    tempcli.client_identity = iden;
    cout<<"please input the client institute:";
    tempcli.institute = institute;
    tempcli.creat_time=book_system_time;
    tempcli.borrownum=0;
    tempcli.orderbooknum=0;
    tempcli.Arrears_money=0.0;
    tempcli.honestlevel=1;
    qDebug("gg");
    tempcli.clid=codclient(tempcli);
    qDebug("is there?");
    cout<<tempcli.clid<<endl;
    suclient.push_back(tempcli);
    ofstream fout("C:\\Users\\lenovo\\Documents\\Test\\document\\client_lar_shelf.txt",ios::out|ios::app);//买书记录
    fout<<tempcli.name<<endl;
    fout<<tempcli.client_identity<<endl;
    fout<<tempcli.institute<<endl;
    fout<<tempcli.creat_time<<endl;
    fout<<tempcli.borrownum<<endl;
    fout<<tempcli.orderbooknum<<endl;
    fout<<tempcli.Arrears_money<<endl;
    fout<<tempcli.honestlevel<<endl;
    fout<<tempcli.clid<<endl;
    fout.close();
}


void book_shelf::renewbook(string renewid,int renew_choice)               //更新图书信息
{
    int searbookinf=-1;
    for(int i=0; (i<(int)booklib.size())&&searbookinf==-1; i++)
    {
        if(booklib[i].id==renewid)
            searbookinf=i;
    }
    if(searbookinf!=-1)
    {
        switch (renew_choice)
        {
        case 1:
        {
            cout<<"请输入新的类型:";
            cin>>booklib[searbookinf].type;
            break;
        }
        case 2:
        {
            cout<<"请输入新的名字:";
            cin>>booklib[searbookinf].name;
            break;

        }
        case 3:
        {
            cout<<"请输入新的作者:";
            cin>>booklib[searbookinf].author;
            break;

        }
        case 4:
        {
            cout<<"请输入新的出版社:";
            cin>>booklib[searbookinf].press;
            break;

        }
        case 5:
        {
            cout<<"请输入新的价格:";
            cin>>booklib[searbookinf].price;
            break;
        }
        }
    }
    else
        cout<<"输入了错误的ID！"<<endl;
}

void book_shelf::renewclient(string renewid,int renew_choice)
{
    int searcliinf=-1;
    for(int i=0; (i<(int)suclient.size())&&(searcliinf==-1); i++)
    {
        if(suclient[i].clid==renewid)
            searcliinf=i;
    }
    if(searcliinf!=-1)
    {
        switch (renew_choice)//有不同的功能
        {
        case 1:
        {
            cout<<"请输入新姓名:";
            cin>>suclient[searcliinf].name;
            cout<<"修改成功！"<<endl;
            break;
        }
        case 2:
        {
            cout<<"请输入新学院:";
            cin>>suclient[searcliinf].institute;
            cout<<"修改成功！"<<endl;
            break;

        }
        case 5:                                //还款，特殊功能
        {
            cout<<"请输入充值金额:";
            int num;
            cin>>num;

            suclient[searcliinf].Arrears_money=suclient[searcliinf].Arrears_money-num;
            cout<<"充值成功！"<<endl;
            break;
        }
        case 4:
        {
            cout<<"请输入新密码:";
            cin>>suclient[searcliinf].cli_pass_word;
            cout<<"修改成功！"<<endl;
            break;
        }
        case 3:
            {
                cout<<"请输入新ID:";
                cin>>suclient[searcliinf].clid;
                cout<<"修改成功！";
            }
        }
    }
    else
        cout<<"错误的ID"<<endl;
}


void book_shelf::search_book_shelf(int num,string inf)
{
    switch (num)
    {
    case 1:           //查询类型                               按书的类型查询
    {
        int j=0;
        for(int i=0; i<(int)booklib.size(); i++)
        {
            if(booklib[i].type==inf)
            {
                ++j;
                cout<<booklib[i].id<<endl;
                cout<<booklib[i].name<<endl;
            }
        }
        if(j)
            cout<<"查询成功！"<<endl;
        else
            cout<<"查询失败，该信息不存在。"<<endl;
    }break;
    case 2:                                          //按书的购入时间查询
    {
        int j=0;
        for(int i=0; i<(int)booklib.size(); i++)
        {
            if(booklib[i].buytime==stringtoint(inf))
            {
                ++j;
                cout<<booklib[i].id<<endl;
                cout<<booklib[i].name<<endl;
            }
        }
        if(j)
            cout<<"查询成功！"<<endl;
        else
            cout<<"查询失败，该信息不存在。"<<endl;
    }break;
    case 3:                                                 //按书的名字查询
    {
        int j=0;
        for(int i=0; i<(int)booklib.size(); i++)
        {
            if(str_dist(booklib[i].name,inf)<=4)
            {
                ++j;
                cout<<"ID: "<<booklib[i].id<<"书名："<<booklib[i].name<<endl;
            }
            /*if(booklib[i].name==inf)
            {
                ++j;
                cout<<booklib[i].id<<endl;
            }*/
        }
        if(j)
            cout<<"查询成功！"<<endl;
        else
            cout<<"查询失败，该信息不存在。"<<endl;
    }break;
    case 4:                                                   //按书的作者查询
    {
        int j=0;
        for(int i=0; i<(int)booklib.size(); i++)
        {
            if(booklib[i].author==inf)
            {
                ++j;
                cout<<booklib[i].id<<endl;
                cout<<booklib[i].name<<endl;
            }
        }
        if(j)
            cout<<"查询成功！"<<endl;
        else
            cout<<"查询失败，该信息不存在。"<<endl;
    }break;
    case 5:                                         //按书的出版社查询
    {
        int j=0;
        for(int i=0; i<(int)booklib.size(); i++)
        {
            if(booklib[i].press==inf)
            {
                ++j;
                cout<<booklib[i].id<<endl;
                cout<<booklib[i].name<<endl;
            }
        }
        if(j)
            cout<<"查询成功！"<<endl;
        else
            cout<<"查询失败，该信息不存在。"<<endl;
    }break;
    case 6:                                      //按书的价格查询
    {
        int j=0;
        for(int i=0; i<(int)booklib.size(); i++)
        {
            if(booklib[i].price==stringtoint(inf))
            {
                ++j;
                cout<<booklib[i].id<<endl;
                cout<<booklib[i].name<<endl;
            }
        }
        if(j)
            cout<<"查询成功！"<<endl;
        else
            cout<<"查询失败，该信息不存在。"<<endl;
    }break;
    default:
        cout<<"输入错误！"<<endl;
        break;
    }

    //可以构建查询记录，构建热搜榜，文件
}

void book_shelf::search_client_inf(int num,string inf)
{
    switch (num)
    {
    case 1:
    {
        for(int i=0; i<(int)suclient.size(); i++)
        {
            if(suclient[i].name==inf)
                cout<<suclient[i].clid<<endl;
        }
    }
    case 2:
    {
        for(int i=0; i<(int)suclient.size(); i++)
        {
            if(suclient[i].institute==inf)
                cout<<suclient[i].clid<<endl;
        }
    }
    default:
        cout<<"error choice!"<<endl;
    }
}


int rechargesucceed = 0;
void  book_shelf::recharge(string clientID,double money)
{
    int searcliinf=-1;
    for(int i=0; (i<(int)suclient.size())&&(searcliinf==-1); i++)
    {
        if(suclient[i].clid==clientID)
            searcliinf=i;
    }
    if(searcliinf!=-1)
    {
        suclient[searcliinf].Arrears_money=suclient[searcliinf].Arrears_money-money;
        rechargesucceed=1;
    }
}
