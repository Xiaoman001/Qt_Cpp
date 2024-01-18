#include "usercenter.h"
#include "ui_usercenter.h"

usercenter::usercenter(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::usercenter)
{
  ui->setupUi(this);

  //  this->hide();
  //  setWindowFlags(Qt::WindowStaysOnTopHint);
  //  myuesercenternew = new uesercenternew(this);
  //  myuesercenternew->hide();
}

usercenter::~usercenter()
{
  delete ui;
}

void usercenter::on_pushButton_2_clicked()
{
  uesercenternew *myuesercenternew = new uesercenternew();

  //  myuesercenternew->hide();
  myuesercenternew->show();
}
