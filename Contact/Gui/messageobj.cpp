#include "messageobj.h"
#include "ui_messageobj.h"
#include <QIcon>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
messageObj::messageObj(QString photoPath, QString name, QString hua, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::messageObj)
{
  ui->setupUi(this);

  QFont font1;
  font1.setFamily("Microsoft YaHei");
  font1.setPointSize(10);
  font1.setStyleStrategy(QFont::PreferAntialias);

  QFont font2;
  font2.setFamily("Microsoft YaHei");
  font2.setPointSize(8);
  font2.setStyleStrategy(QFont::PreferAntialias);
  QIcon photo(photoPath); // 头像
  QPushButton *photobtn = new QPushButton(this);
  photobtn->setIcon(photo);
  photobtn->setIconSize(QSize(50, 50));
  photobtn->setMaximumSize(50, 50);
  QLabel *name_label = new QLabel(); // 姓名
  name_label->setText(name);
  name_label->setFont(font1);
  name_label->setStyleSheet("border:0px solid rgb(243, 243, 243);font: 10pt ;background:rgba(0,0,0,0)");

  //  name_label->setAlignment(Qt::AlignCenter);
  QLabel *hua_label = new QLabel(hua); // 最后一句话
  hua_label->setStyleSheet("border:0px solid rgb(243, 243, 243);background:rgba(0,0,0,0)");
  hua_label->setFont(font2);
  QVBoxLayout *nameandhua = new QVBoxLayout();
  nameandhua->addWidget(name_label);
  nameandhua->addWidget(hua_label);
  nameandhua->setSpacing(0);

  QHBoxLayout *photoandh = new QHBoxLayout(this);
  this->setLayout(photoandh);
  photoandh->addWidget(photobtn);
  photoandh->addLayout(nameandhua);
  photoandh->setSpacing(10);
}

messageObj::~messageObj()
{
  delete ui;
}
