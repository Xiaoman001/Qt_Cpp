#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <Dbal/DataBase.h>
namespace Ui {
class history;
}

class history : public QWidget {
  Q_OBJECT

public:

  Usersql DataBase;
  explicit history(
    QStringList tem,
    QWidget    *parent = nullptr);
  ~history();

private:

  Ui::history *ui;
};

#endif // HISTORY_H
