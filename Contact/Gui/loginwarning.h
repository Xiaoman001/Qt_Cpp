#ifndef LOGINWARNING_H
#define LOGINWARNING_H

#include <QWidget>

namespace Ui {
class LoginWarning;
}

class LoginWarning : public QWidget {
  Q_OBJECT

public:

  explicit LoginWarning(QWidget *parent = nullptr);
  ~LoginWarning();

private slots:

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_8_clicked();

private:

  Ui::LoginWarning *ui;
};

#endif // LOGINWARNING_H
