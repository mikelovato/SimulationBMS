#ifndef CREATID_H
#define CREATID_H

#include <QDialog>

namespace Ui {
class creatid;
}

class creatid : public QDialog
{
    Q_OBJECT

public:
    explicit creatid(QWidget *parent = 0);
    ~creatid();

private slots:
    void on_pushButton_clicked();

private:
    Ui::creatid *ui;
};

#endif // CREATID_H
