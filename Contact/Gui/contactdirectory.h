#ifndef CONTACTDIRECTORY_H
#define CONTACTDIRECTORY_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostInfo>
#include <QDateTime>
#include <QtMath>
#include <QDateTime>
#include <QDebug>
#include <QAction>
#include <QScrollArea>
#include <QScrollBar>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QWidget>
#include <QTcpSocket>
#include <QLabel>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <Dbal/DataBase.h>
#include "messageobj.h"
#include <Service/robotchat.h>
#include <Gui/chatobjwidget.h>
#include <Gui/cluster.h>

// fdog
#include <QWidget>
using namespace std;
namespace Ui {
class contactdirectory;
}

class contactdirectory : public QWidget {
  Q_OBJECT

public:

  robotchat *robot;

  // fdog
  QLabel *LabSocketate;
  QString name; // 对方网名
  bool isread = false;
  int isdown;
  QPixmap pixmap;
  QPixmap mypixmap;
  QPoint last; // 窗口拖动用变量
  bool isPressedWidget;

  bool mouse_press;
  QPoint mousePoint;
  QString lastTime = ""; // 用来保存上一次的发送消息的时间
  Usersql DataBase;
  explicit contactdirectory(
    QString  account,
    QWidget *parent = nullptr);
  ~contactdirectory();

private:

  ChatObjWidget *chatobj;
  Ui::contactdirectory *ui;

private slots:

  void changeName(QString account);

signals:

  void sendData(QString str);
  void sendCount(QString otheraccount);

public:

  QString qunOtheraccount;
  QTcpServer *tcpServer;
  QTcpSocket *tcpSocket;
  vector<QTcpSocket *>socketArr;
  QString myAccount    = "";
  QString OtherAccount = "19070015";
  void     reciveDataMessage(QString str);
  QString  getLocalIP();
  QWidget* CreateWidgetL_R(int     i,
                           QString data);

private slots:

  void on_send_Button_clicked();

  void on_close_button_clicked();

  void on_smallest_Button_clicked();
  void sendMessage(QString msg);
  void connect_success();
  void new_connect();
  void read_data();
  void on_label_name_clicked();
};

#endif // CONTACTDIRECTORY_H
