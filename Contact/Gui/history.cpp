#include "history.h"
#include "ui_history.h"

history::history(
  QStringList tem,
  QWidget    *parent) :
  QWidget(parent),
  ui(new Ui::history)
{
  ui->setupUi(this);
  setWindowTitle("历史消息");
  for (auto a:tem) {
    auto temList = a.split('|');
    ui->textEdit->append(temList[1]);
    ui->textEdit->append(DataBase.getNameByAccount(temList[0]) + ":" + temList[2]);
  }
}

history::~history()
{
  delete ui;
}
