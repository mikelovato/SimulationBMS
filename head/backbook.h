#ifndef BACKBOOK_H
#define BACKBOOK_H

#include <QDialog>

namespace Ui {
class backbook;
}

class backbook : public QDialog
{
    Q_OBJECT

public:
    explicit backbook(QWidget *parent = 0);
    ~backbook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::backbook *ui;
};

#endif // BACKBOOK_H
