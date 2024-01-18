#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QTime>
namespace Ui {
class home;
}

class home : public QWidget {
  Q_OBJECT

public:

  explicit home(QWidget *parent = nullptr);
  ~home();
  void timerEvent(QTimerEvent *event);

private:

  Ui::home *ui;
};

#endif // HOME_H
