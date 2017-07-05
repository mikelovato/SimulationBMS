#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <QDialog>

namespace Ui {
class orderbook;
}

class orderbook : public QDialog
{
    Q_OBJECT

public:
    explicit orderbook(QWidget *parent = 0);
    ~orderbook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::orderbook *ui;
};

#endif // ORDERBOOK_H
