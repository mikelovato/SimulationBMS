#ifndef MONTHINFO_H
#define MONTHINFO_H

#include <QDialog>

namespace Ui {
class monthinfo;
}

class monthinfo : public QDialog
{
    Q_OBJECT

public:
    explicit monthinfo(QWidget *parent = 0);
    ~monthinfo();
    void play();
private:
    Ui::monthinfo *ui;
};

#endif // MONTHINFO_H
