#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Chat;
class Globalobserver;
class Verify;
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMouseEvent>
#include <QPoint>
#include <QMovie>
#include <QSize>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QSignalMapper>
#include <QTcpSocket>
#include <QLabel>
#include <QList>
#include <QTimer>
#include <QMenu>
#include <QDebug>
#include <QPainter>
#include <QBitmap>
#include <QSize>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <QMap>
#include <qdrawutil.h>
#include <QGraphicsDropShadowEffect>
#include <QListWidget>
#include <QHostInfo>
#include <QMouseEvent>
#include "Gui/query.h"
#include "Dbal/DataBase.h"
#include "Gui/verify.h"
#include "Gui/traywidget.h"
#include "Gui/addfriend.h"
#include "Gui/chatdemo.h"
#include "Gui/contactdirectory.h"
#include "Gui/frmemailtool.h"
#include "Gui/home.h"
#include "Service/globalobserver.h"
#include "Gui/usercenter.h"
#include "Gui/settings.h"
using namespace std;
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow {
  Q_OBJECT

public:

  explicit MainWindow(
    QString  account,
    QWidget *parent = 0); // 构造函数
  ~MainWindow();          // 析构函数

  void new_connect();
  void read_data();

public:

  Query *query;
  Usersql DataBase;
  QPoint last; // 窗口拖动用变量
  bool isPressedWidget;
  QTcpServer *tcpServer;
  vector<QTcpSocket *>socketArr;
  QString myAccount = "";
  chatdemo *singalchat;
  frmEmailTool *Frmemailtool;
  contactdirectory *contactDirectory;
  home *Home;
  settings *setting;
  Ui::MainWindow *ui;
  vector<QWidget>nowVector;
  QMap<QString, int>nowShow;
  QVector<QString>isShowVector;
  usercenter *myuesercenter;
  void mousePressEvent(QMouseEvent *event);   // 鼠标点击
  void mouseMoveEvent(QMouseEvent *event);    // 鼠标移动
  void mouseReleaseEvent(QMouseEvent *event); // 鼠标释放

private slots:

  void on_chat_Button_clicked();
  void on_smallest_Button_clicked();
  void on_biggest_Button_clicked();
  void on_book_Button_clicked();
  void on_close_button_clicked();
  void on_home_Button_clicked();
  void on_email_Button_clicked();
  void on_add_Button_clicked();
  void on_photo_clicked();
  void on_settings_Button_clicked();
  void modifymode(int mode);
};
#endif // MAINWINDOW_H
