#ifndef IDOFCHANGECLIENT_H
#define IDOFCHANGECLIENT_H

#include <QDialog>

namespace Ui {
class idofchangeclient;
}

class idofchangeclient : public QDialog
{
    Q_OBJECT

public:
    explicit idofchangeclient(QWidget *parent = 0);
    ~idofchangeclient();

private slots:
    void on_pushButton_clicked();

private:
    Ui::idofchangeclient *ui;
};

#endif // IDOFCHANGECLIENT_H
