#ifndef CALLDIALOG_H
#define CALLDIALOG_H

#include <QDialog>
#include <QMoveEvent>
#include <QDebug>
#include <Dbal/DataBase.h>

namespace Ui {
class CallDialog;
}

class CallDialog : public QDialog {
  Q_OBJECT

public:

  explicit CallDialog(QWidget *parent = nullptr);
  ~CallDialog();

  void mousePressEvent(QMouseEvent *event) override;   // 鼠标点击
  void mouseMoveEvent(QMouseEvent *event) override;    // 鼠标移动
  void mouseReleaseEvent(QMouseEvent *event) override; // 鼠标释放

  void setNickname(const QString& nickname);
  Usersql DataBase;

public slots:

  void on_smallest_Button_clicked();
  void on_close_button_clicked();

private:

  QPoint m_last; // 窗口拖动用变量
  bool m_isPressedWidget;

  Ui::CallDialog *ui;

signals:

  void signalCancelCall();
};

#endif // CALLDIALOG_H
