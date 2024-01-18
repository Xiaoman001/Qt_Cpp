#include "uesercenternew.h"
#include "ui_uesercenternew.h"
#include <QGraphicsDropShadowEffect>
uesercenternew::uesercenternew(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::uesercenternew)
{
  ui->setupUi(this);
  setWindowFlags(Qt::FramelessWindowHint);
}

uesercenternew::~uesercenternew()
{
  delete ui;
}

void uesercenternew::on_pushButton_2_clicked()
{
  this->close();
}

void uesercenternew::on_pushButton_4_clicked()
{
  this->close();
}
