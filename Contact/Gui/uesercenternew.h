#ifndef UESERCENTERNEW_H
#define UESERCENTERNEW_H

#include <QWidget>
namespace Ui {
class uesercenternew;
}

class uesercenternew : public QWidget {
  Q_OBJECT

public:

  explicit uesercenternew(QWidget *parent = nullptr);
  ~uesercenternew();

private slots:

  void on_pushButton_2_clicked();

  void on_pushButton_4_clicked();

private:

  Ui::uesercenternew *ui;
};

#endif // UESERCENTERNEW_H
