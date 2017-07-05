#ifndef STUDENTBORROWBOOK_H
#define STUDENTBORROWBOOK_H

#include <QDialog>

namespace Ui {
class studentborrowbook;
}

class studentborrowbook : public QDialog
{
    Q_OBJECT

public:
    explicit studentborrowbook(QWidget *parent = 0);
    ~studentborrowbook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::studentborrowbook *ui;
};

#endif // STUDENTBORROWBOOK_H
