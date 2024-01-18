#include "loginwarning.h"
#include "ui_loginwarning.h"

LoginWarning::LoginWarning(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LoginWarning)
{
  ui->setupUi(this);
  setWindowFlags(Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);

  //  ui->widget->setStyleSheet(QString::fromUtf8("#widget{border:2px solid blue}"));

  //    this->setStyleSheet("QWidget{border-top-left-radius:15px;border-top-right-radius:5px;}");
}

LoginWarning::~LoginWarning()
{
  delete ui;
}

void LoginWarning::on_pushButton_clicked()
{
  this->hide();
}

void LoginWarning::on_pushButton_2_clicked()
{
  this->hide();
}

void LoginWarning::on_pushButton_8_clicked()
{
  this->hide();
}
