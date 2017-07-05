#ifndef STUDENTINTERFACE_H
#define STUDENTINTERFACE_H

#include <QDialog>

namespace Ui {
class StudentInterface;
}

class StudentInterface : public QDialog
{
    Q_OBJECT

public:
    explicit StudentInterface(QWidget *parent = 0);
    ~StudentInterface();
    void orderTip(QString str,int time);
private slots:
    void on_ExitBtn_clicked();

    void on_textBrowser_objectNameChanged(const QString &objectName);

    void on_borrowBtn_clicked();

    void on_backBtn_clicked();

    void on_allbookBtn_clicked();

    void on_orderBtn_clicked();

    void on_personalinfoBtn_clicked();

    void on_changeMyinfo_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_name_clicked();

    void on_auther_clicked();

    void on_type_clicked();

    void on_press_clicked();

    void on_searchBtn_clicked();

    void on_pushButton_clicked();

    void on_computerBtn_clicked();

    void on_mathBtn_clicked();

    void on_literatureBtn_clicked();

    void on_historyBtn_clicked();

    void on_artBtn_clicked();

    void on_communicationBtn_clicked();

    void on_medicineBtn_clicked();

    void on_economyBtn_clicked();

    void on_otherBtn_clicked();

    void on_timecontrolBtn_clicked();

    void on_renew_clicked();

private:
    Ui::StudentInterface *ui;
};

#endif // STUDENTINTERFACE_H
