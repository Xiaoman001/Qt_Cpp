#include "receivedialog.h"
#include "ui_receivedialog.h"

ReceiveDialog::ReceiveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiveDialog)
{
    ui->setupUi(this);
}

ReceiveDialog::~ReceiveDialog()
{
    delete ui;
}
