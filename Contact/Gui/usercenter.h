#ifndef USERCENTER_H
#define USERCENTER_H

#include <QWidget>
#include "Gui/uesercenternew.h"
#include "uesercenternew.h"
namespace Ui {
class usercenter;
}

class usercenter : public QWidget {
  Q_OBJECT

public:

  explicit usercenter(QWidget *parent = nullptr);
  ~usercenter();

private slots:

  void on_pushButton_2_clicked();

private:

  Ui::usercenter *ui;

  //  uesercenternew *myuesercenternew;
};

#endif // USERCENTER_H
