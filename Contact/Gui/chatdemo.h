#ifndef CHATDEMO_H
#define CHATDEMO_H

// fdog
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
#include <Gui/history.h>
#include <Windows.h>
#include <QProcess>
#include <QMessageBox>
#include <Gui/emojipick.h>

// fdog
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
#include <QFileDialog> // < 打开文件对话框
#include <QFileInfo>   // < 获取文件信息
#include <QDebug>
#include <QFileInfo>
#include <Gui/qctextedit.h>
#include <QDir>
#include <QDesktopServices>
#include <Gui/cluster.h>

// udp voice 语音通话 >>>
#include "Service/UdpVoiceCallNet/udpvoicewidget.h"

// 数据库
#include "Dbal/databaseoperaterdemo.h"

// udp voice 语音通话 <<<

// fdog
#include <QWidget>
using namespace std;
namespace Ui {
class chatdemo;
}

class chatdemo : public QWidget {
  Q_OBJECT

private:

  emojipick *emojipicker;
  robotchat *robot;

  // fdog
  history *History;
  QLabel *LabSocketate;
  QString name; // 对方网名
  bool isread = false;
  int isdown;
  QPixmap pixmap;
  QPixmap mypixmap;
  QPoint last; // 窗口拖动用变量
  bool isPressedWidget;

  // fdog
  Usersql DataBase;
  bool mouse_press;
  QPoint mousePoint;
  QString lastTime = ""; // 用来保存上一次的发送消息的时间
  QTimer myTimer;

  bool isfile = false;
  QTcpServer *TcpServer; // < 监听套接字
  QTcpSocket *TcpSocket;
  QFile file;            // *< 文件对象
  QString filename;      // *< 打开的文件名称
  qint64 filesize;       // *< 文件大小信息
  qint64 sendfilesize;   // *< 已发送文件大小

public:

  explicit chatdemo(
    QString  account,
    QWidget *parent = 0);
  ~chatdemo();

  QString  getLocalIP();
  QWidget* CreateWidgetL_R(int     i,
                           QString data);

  //  //  void        paintEvent(QPaintEvent *e);
  //  void    mousePressEvent(QMouseEvent *event);   // 鼠标点击
  //  void    mouseMoveEvent(QMouseEvent *event);    // 鼠标移动
  //  void    mouseReleaseEvent(QMouseEvent *event); // 鼠标释放

  QString getName() const;
  void    setName(const QString& value);

  QString getID() const;
  void    setID(const QString& value);

  bool    getIsread() const;
  void    setIsread(bool value);

  // udp voice 语音通话 >>>
  UdpVoiceWidget *m_pUdpVoiceWidget = nullptr;
  QString m_curAccount;
  QString m_nickname;

  // udp voice 语音通话 <<<

public:

  QTcpServer *tcpServer;
  QTcpSocket *tcpSocket;
  vector<QTcpSocket *>socketArr;
  QString myAccount    = "";
  QString OtherAccount = "54781204";
  void reciveDataMessage(QString str);

signals:

  void sendData(QString str);
  void sendCount(QString otheraccount);

private slots:

  void jumpToWeb();
  void on_send_Button_clicked();

  void on_close_button_clicked();

  void on_smallest_Button_clicked();
  void sendMessage(QString msg);
  void connect_success();
  void new_connect();
  void read_data();
  void read_Alldata();

  void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
  void on_document_Button_clicked();
  void otherSave();
  void download();

  void on_history_Button_clicked();

  void on_speak_Button_2_clicked();

  void on_label_name_clicked();

  void on_speak_Button_clicked();

  void on_emoji_Button_clicked();

private:

  Ui::chatdemo *ui;
};

#endif // CHATDEMO_H
