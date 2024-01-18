#ifndef SETTINGOBJ_H
#define SETTINGOBJ_H

#include <QWidget>
#include <QLabel>
namespace Ui {
class settingObj;
}

class settingObj : public QWidget {
  Q_OBJECT

public:

  explicit settingObj(QString  name,
                      QWidget *parent = nullptr);
  ~settingObj();

  void setNameLabelStyle();
  void setNameLabelStylelight();
  void translateLabelEn();
  void translateLableCh();

private:

  QLabel *name_label = new QLabel();
  Ui::settingObj *ui;
};

#endif // SETTINGOBJ_H
