#ifndef CLUSTER_H
#define CLUSTER_H

#include <QMainWindow>
#include <QMessageBox>
#include <Dbal/DataBase.h>
namespace Ui {
class cluster;
}

class cluster : public QMainWindow {
  Q_OBJECT

public:

  explicit cluster(QString  account,
                   QWidget *parent = 0);
  ~cluster();
  Usersql DataBase;

private slots:

  void on_pushButton_clicked();

  void on_pushButton_3_clicked();

private:

  Ui::cluster *ui;
};

#endif // CLUSTER_H
