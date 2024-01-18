#include "settings.h"
#include "ui_settings.h"
#include "settingobj.h"
#include <QBrush>
#include <QDebug>
#include <QTranslator>
#include <QFile>
#include "dialogsuggestion.h"
#include "ui_dialogsuggestion.h"

#if _MSC_VER >= 1600
# pragma execution_character_set("utf-8")
#endif // if _MSC_VER >= 1600

settings::settings(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::settings)
{
  ui->setupUi(this);

  // 多语言
  QListWidgetItem *languageItem = new QListWidgetItem(ui->listWidget);
  languageItem->setSizeHint(QSize(ui->listWidget->width() - 5, 60));
  languageObj = new settingObj(tr("多语言"));
  ui->listWidget->setItemWidget(languageItem, languageObj);
  ui->listWidget->addItem(languageItem);
  languageObj->show();

  // 外观
  QListWidgetItem *appearenceItem = new QListWidgetItem(ui->listWidget);
  appearenceItem->setSizeHint(QSize(ui->listWidget->width() - 5, 60));
  appearenceObj = new settingObj(tr("外观与模式"));
  ui->listWidget->setItemWidget(appearenceItem, appearenceObj);
  ui->listWidget->addItem(appearenceItem);
  appearenceObj->show();

  // 帮助与反馈
  QListWidgetItem *helpItem = new QListWidgetItem(ui->listWidget);
  helpItem->setSizeHint(QSize(ui->listWidget->width() - 5, 60));
  helpObj = new settingObj(tr("帮助"));
  ui->listWidget->setItemWidget(helpItem, helpObj);
  ui->listWidget->addItem(helpItem);
  helpObj->show();

  // 关于app
  QListWidgetItem *appItem = new QListWidgetItem(ui->listWidget);
  appItem->setSizeHint(QSize(ui->listWidget->width() - 5, 60));
  appObj = new settingObj(tr("关于软件"));
  ui->listWidget->setItemWidget(appItem, appObj);
  ui->listWidget->addItem(appItem);
  appObj->show();

  ui->listWidget->setCurrentRow(0); // 默认设置在第一页

  ui->light_radioButton->click();
  dia = new DialogSuggestion();     // 建议
}

settings::~settings()
{
  delete ui;
}

QTranslator * settings::getTr()
{
  return m_Translator;
}

void settings::on_listWidget_itemSelectionChanged()
{
  QList<QListWidgetItem *> items = ui->listWidget->selectedItems();

  qDebug() << "at is" << ui->listWidget->row(items.at(0));

  ui->stackedWidget->setCurrentIndex(ui->listWidget->row(items.at(0)));
}

void settings::on_confirm_button_clicked()
{
  m_Translator = new QTranslator();
  if (ui->chooseLanguage_box->currentText() == "简体中文") {
    qDebug() << ui->chooseLanguage_box->currentText();
    m_Translator->load(":/translator/Translate_CN.qm");
    qApp->installTranslator(m_Translator);
    ui->retranslateUi(this);
    languageObj->translateLableCh();
    appearenceObj->translateLableCh();
    helpObj->translateLableCh();
    appObj->translateLableCh();
  }
  else if (ui->chooseLanguage_box->currentText() == "English") {
    qDebug() << ui->chooseLanguage_box->currentText();
    m_Translator->load(":/translator/Translate_EN.qm");
    qApp->installTranslator(m_Translator);
    ui->retranslateUi(this);
    languageObj->translateLabelEn();
    appearenceObj->translateLabelEn();
    helpObj->translateLabelEn();
    appObj->translateLabelEn();
  }
}

void settings::on_dark_radioButton_clicked()
{
  QFile file(":/styleSheet/psblack.qss");
  file.open(QIODevice::ReadOnly);
  this->setStyleSheet(file.readAll());
  dia->dialogDark();
  file.close();
  languageObj->setNameLabelStyle();
  appearenceObj->setNameLabelStyle();
  helpObj->setNameLabelStyle();
  appObj->setNameLabelStyle();
  emit sendMode(1);
}

void settings::on_light_radioButton_clicked()
{
  QFile file(":/styleSheet/pslight.qss");
  file.open(QIODevice::ReadOnly);
  this->setStyleSheet(file.readAll());
  file.close();

  //  dia->dialogLight();
  languageObj->setNameLabelStylelight();
  appearenceObj->setNameLabelStylelight();
  helpObj->setNameLabelStylelight();
  appObj->setNameLabelStylelight();
  emit sendMode(0);
}

void settings::on_submit_su_button_clicked()
{
  dia->show();
}

void settings::on_submit_error_button_clicked()
{
  DialogRepair *repair = new DialogRepair();
  repair->show();
}
