#ifndef SETTINGS_H
#define SETTINGS_H
#include <QListWidgetItem>
#include <QWidget>
#include <QTranslator>
#include "settingobj.h"
#include "dialogsuggestion.h"
#include "dialogrepair.h"
QT_BEGIN_NAMESPACE
namespace Ui { class settings; }
QT_END_NAMESPACE

class settings : public QWidget {
  Q_OBJECT

public:

  settings(QWidget *parent = nullptr);
  ~settings();
  QTranslator* getTr();
  void         Refresh();

private slots:

  void on_listWidget_itemSelectionChanged();

  void on_confirm_button_clicked();

  void on_dark_radioButton_clicked();

  void on_light_radioButton_clicked();

  void on_submit_su_button_clicked();

  void on_submit_error_button_clicked();

signals:

  void sendMode(int mode);

private:

  QTranslator *m_Translator;
  Ui::settings *ui;

  settingObj *languageObj;
  settingObj *appearenceObj;
  settingObj *helpObj;
  settingObj *appObj;
  DialogSuggestion *dia;
};
#endif // SETTINGS_H
