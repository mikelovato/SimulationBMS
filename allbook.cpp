#include "allbook.h"
#include "ui_allbook.h"

allbook::allbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::allbook)
{
    ui->setupUi(this);
}

allbook::~allbook()
{
    delete ui;
}
