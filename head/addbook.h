#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>

namespace Ui {
class AddBook;
}

class AddBook : public QDialog
{
    Q_OBJECT

public:
    explicit AddBook(QWidget *parent = 0);
    ~AddBook();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddBook *ui;
};

#endif // ADDBOOK_H
