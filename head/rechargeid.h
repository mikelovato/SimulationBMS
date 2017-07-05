#ifndef RECHARGEID_H
#define RECHARGEID_H

#include <QDialog>

namespace Ui {
class rechargeid;
}

class rechargeid : public QDialog
{
    Q_OBJECT

public:
    explicit rechargeid(QWidget *parent = 0);
    ~rechargeid();

private slots:
    void on_pushButton_clicked();

private:
    Ui::rechargeid *ui;
};

#endif // RECHARGEID_H
