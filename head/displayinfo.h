#ifndef DISPLAYINFO_H
#define DISPLAYINFO_H

#include <QDialog>

namespace Ui {
class displayinfo;
}

class displayinfo : public QDialog
{
    Q_OBJECT

public:
    explicit displayinfo(QWidget *parent = 0);
    ~displayinfo();

private slots:
    void on_search_clicked();

    void on_allinfo_clicked();

private:
    Ui::displayinfo *ui;
};

#endif // DISPLAYINFO_H
