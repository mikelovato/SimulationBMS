#ifndef IDOFCHANGEBOOK_H
#define IDOFCHANGEBOOK_H

#include <QDialog>

namespace Ui {
class idofchangebook;
}

class idofchangebook : public QDialog
{
    Q_OBJECT

public:
    explicit idofchangebook(QWidget *parent = 0);
    ~idofchangebook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::idofchangebook *ui;
};

#endif // IDOFCHANGEBOOK_H
