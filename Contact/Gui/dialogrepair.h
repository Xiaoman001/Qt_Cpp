#ifndef DIALOGREPAIR_H
#define DIALOGREPAIR_H

#include <QDialog>

namespace Ui {
class DialogRepair;
}

class DialogRepair : public QDialog {
  Q_OBJECT

public:

  explicit DialogRepair(QWidget *parent = nullptr);
  ~DialogRepair();

private slots:

  void on_submit1_clicked();

  void on_cancel1_clicked();

private:

  Ui::DialogRepair *ui;
};

#endif // DIALOGREPAIR_H
