#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <QDialog>

namespace Ui {
class borrowbook;
}

class borrowbook : public QDialog
{
    Q_OBJECT

public:
    explicit borrowbook(QWidget *parent = 0);
    ~borrowbook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::borrowbook *ui;
};

#endif // BORROWBOOK_H
