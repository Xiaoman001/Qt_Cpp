#include "dialogrepair.h"
#include "ui_dialogrepair.h"

DialogRepair::DialogRepair(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogRepair)
{
  ui->setupUi(this);

  //  setWindowFlags(Qt::FramelessWindowHint | windowFlags());
}

DialogRepair::~DialogRepair()
{
  delete ui;
}

void DialogRepair::on_submit1_clicked()
{
  this->close();
}

void DialogRepair::on_cancel1_clicked()
{
  this->close();
}
