#include "settingobj.h"
#include "ui_settingobj.h"
#include <QLabel>
#include <QVBoxLayout>

#if _MSC_VER >= 1600
# pragma execution_character_set("utf-8")
#endif // if _MSC_VER >= 1600
settingObj::settingObj(QString name, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::settingObj)
{
  ui->setupUi(this);

  QFont font1;
  font1.setFamily("Microsoft");
  font1.setPointSize(9);

  //  name_label = new QLabel();
  name_label->setStyleSheet("background:rgb(0,0,0,0);");
  name_label->setText(name);
  name_label->setFont(font1);
  QVBoxLayout *item = new QVBoxLayout(this);

  item->addWidget(name_label);
}

settingObj::~settingObj()
{
  delete ui;
}

void settingObj::setNameLabelStyle()
{
  name_label->setStyleSheet("color:rgb(255,255,255);");
}

void settingObj::setNameLabelStylelight()
{
  name_label->setStyleSheet("color:rgb(0,0,0);");
}

void settingObj::translateLableCh()
{
  if (name_label->text() == "Language") {
    name_label->setText("多语言");
  }
  else if (name_label->text() == "Appearance") {
    name_label->setText("外观与模式");
  }
  else if (name_label->text() == "Help")
  {
    name_label->setText("帮助");
  }
  else if (name_label->text() == "About App") {
    name_label->setText("关于软件");
  }
}

void settingObj::translateLabelEn()
{
  if (name_label->text() == "多语言") {
    name_label->setText("Language");
  }
  else if (name_label->text() == "外观与模式") {
    name_label->setText("Appearance");
  }
  else if (name_label->text() == "帮助")
  {
    name_label->setText("Help");
  }
  else if (name_label->text() == "关于软件") {
    name_label->setText("About App");
  }
}
