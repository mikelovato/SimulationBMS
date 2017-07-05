#ifndef CHANGEBOOK_H
#define CHANGEBOOK_H

#include <QDialog>

namespace Ui {
class changebook;
}

class changebook : public QDialog
{
    Q_OBJECT

public:
    explicit changebook(QWidget *parent = 0);
    ~changebook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::changebook *ui;
};

#endif // CHANGEBOOK_H
