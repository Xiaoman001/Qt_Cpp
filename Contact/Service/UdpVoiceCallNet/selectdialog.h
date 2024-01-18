#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog {
  Q_OBJECT

public:

  explicit SelectDialog(QWidget *parent = nullptr);
  ~SelectDialog();

  void setNickname(const QString& nickname);

  Ui::SelectDialog *ui;

private:

  //    Ui::SelectDialog *ui;

signals:

  void acceptCorrespond();
  void refuseCorrespond();

public:

  void mousePressEvent(QMouseEvent *event) override;   // 鼠标点击
  void mouseMoveEvent(QMouseEvent *event) override;    // 鼠标移动
  void mouseReleaseEvent(QMouseEvent *event) override; // 鼠标释放

public slots:

  void on_smallest_Button_clicked();
  void on_close_button_clicked();

private:

  QPoint m_last; // 窗口拖动用变量
  bool m_isPressedWidget;
};

#endif // SELECTDIALOG_H
