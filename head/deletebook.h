#ifndef DELETEBOOK_H
#define DELETEBOOK_H

#include <QDialog>

namespace Ui {
class deletebook;
}

class deletebook : public QDialog
{
    Q_OBJECT

public:
    explicit deletebook(QWidget *parent = 0);
    ~deletebook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::deletebook *ui;
};


#endif // DELETEBOOK_H
