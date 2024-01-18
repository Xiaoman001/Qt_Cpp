#include "dialogsuggestion.h"
#include "ui_dialogsuggestion.h"
#include <QFile>
#include <QMessageBox>
DialogSuggestion::DialogSuggestion(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSuggestion)
{
  ui->setupUi(this);

  //  setWindowFlags(Qt::FramelessWindowHint | windowFlags());
}

DialogSuggestion::~DialogSuggestion()
{
  delete ui;
}

void DialogSuggestion::dialogDark()
{
  QFile file(":/styles/psblack.qss");
  file.open(QIODevice::ReadOnly);
  this->setStyleSheet(file.readAll());

  file.close();
}

void DialogSuggestion::dialogLight()
{
  QFile file(":/styles/pslight.qss");
  file.open(QIODevice::ReadOnly);
  this->setStyleSheet(file.readAll());

  file.close();
}

void DialogSuggestion::on_submit1_clicked()
{
  QMessageBox msgBox;
  msgBox.setText("成功提交");
  msgBox.exec();
  this->close();
}

void DialogSuggestion::on_cancel1_clicked()
{
  this->close();
}
