#ifndef DISPLAYBOOKINFO_H
#define DISPLAYBOOKINFO_H

#include <QDialog>

namespace Ui {
class displaybookinfo;
}

class displaybookinfo : public QDialog
{
    Q_OBJECT

public:
    explicit displaybookinfo(QWidget *parent = 0);
    ~displaybookinfo();

    void play();
private:
    Ui::displaybookinfo *ui;
};

#endif // DISPLAYBOOKINFO_H
