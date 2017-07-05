#ifndef PERSONALINFO_H
#define PERSONALINFO_H

#include <QDialog>

namespace Ui {
class personalinfo;
}

class personalinfo : public QDialog
{
    Q_OBJECT

public:
    explicit personalinfo(QWidget *parent = 0);
    ~personalinfo();
    void play();
private:
    Ui::personalinfo *ui;
};

#endif // PERSONALINFO_H
