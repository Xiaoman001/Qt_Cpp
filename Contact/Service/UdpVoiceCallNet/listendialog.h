#ifndef LISTENDIALOG_H
#define LISTENDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class ListenDialog;
}

class ListenDialog : public QDialog {
  Q_OBJECT

public:

  explicit ListenDialog(QWidget *parent = nullptr);
  ~ListenDialog();

  void setNickname(const QString& nickname);

signals:

  void hangUpSelfSignal();
  void hangUpOtherSignal();

private:

  Ui::ListenDialog *ui;

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

#endif // LISTENDIALOG_H
