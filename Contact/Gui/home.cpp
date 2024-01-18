#include "home.h"
#include "ui_home.h"

home::home(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::home)
{
  ui->setupUi(this);
  startTimer(1000);
}

home::~home()
{
  delete ui;
}

void home::timerEvent(QTimerEvent *event)
{
  QTime t = QTime::currentTime();

  QString now_time = t.toString("hh:mm:ss");
  ui->lcdNumber->display(now_time);

  QIcon sign_ico(":/pic/sign.png");
  ui->sign_button->setIcon(sign_ico);
  ui->sign_button->setIconSize(QSize(60, 60));

  QIcon travel_ico(":/pic/bussiness_travel.png");
  ui->travel_button->setIcon(travel_ico);
  ui->travel_button->setIconSize(QSize(60, 60));

  QIcon document_ico(":/pic/document2.png");
  ui->document_button->setIcon(document_ico);
  ui->document_button->setIconSize(QSize(60, 60));
}
