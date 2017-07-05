#ifndef TEACHERINTERFACE_H
#define TEACHERINTERFACE_H

#include <QDialog>

namespace Ui {
class TeacherInterface;
}

class TeacherInterface : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherInterface(QWidget *parent = 0);
    ~TeacherInterface();
    void renew();
private slots:
    void on_exitBtn_clicked();

    void on_pushButton_clicked();

    void on_borrowBtn_clicked();

    void on_backBtn_clicked();

    void on_addbookBtn_clicked();

    void on_deletebookBtn_clicked();

    void on_changebookBtn_clicked();

    void on_allbookBtn_clicked();

    void on_monthinfoBtn_clicked();

    void on_creatidBtn_clicked();

    void on_rechargeidBtn_clicked();

    void on_displayinfoBtn_clicked();

    void on_changeClient_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_name_clicked();

    void on_author_clicked();

    void on_press_clicked();

    void on_pushButton_3_clicked();

    void on_computerBtn_clicked();

    void on_mathBtn_clicked();

    void on_literatureBtn_clicked();

    void on_historyBtn_clicked();

    void on_artBtn_clicked();

    void on_communicationBtn_clicked();

    void on_medicineBtn_clicked();

    void on_economyBtn_clicked();

    void on_otherBtn_clicked();

    void on_searchBtn_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_timecontrolBtn_clicked();

    void on_renew_clicked();

private:
    Ui::TeacherInterface *ui;
};

#endif // TEACHERINTERFACE_H
