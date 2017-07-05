#ifndef ALLBOOK_H
#define ALLBOOK_H

#include <QDialog>

namespace Ui {
class allbook;
}

class allbook : public QDialog
{
    Q_OBJECT

public:
    explicit allbook(QWidget *parent = 0);
    ~allbook();

private:
    Ui::allbook *ui;
};

#endif // ALLBOOK_H
