#ifndef CHATOBJWIDGET_H
#define CHATOBJWIDGET_H

#if _MSC_VER >= 1600
# pragma execution_character_set("utf-8")
#endif // if _MSC_VER >= 1600
#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QListWidget>
#include <QLabel>

// #include "chat.h"
#include "Utils/chatgroupinglistmaker.h"

namespace Ui {
class ChatObjWidget;
}

class ChatObjWidget : public QWidget {
  Q_OBJECT

public:

  int m_userId      = 1;
  QString m_account = "12345678";
  void setAccount(const QString& account);

  ChatGroupingListMaker m_chatGroupingListMaker;

  QList<bool>m_isWidget;             // 列表展开
  QList<QPushButton *>m_btns;        // listbtn分组名
  QList<QListWidget *>m_listWidgets; // listwidget分组列表
  QSignalMapper *m_myMapper;         // 信号管理

  //  QList<Chat *>listchat;                              // 保存聊天窗口

  void onDoubleWidgetClicked(QListWidgetItem *witem); // 好友列表被双击
  void onWidgetClicked(int i);                        // 分组按钮被点击

  // func
  explicit ChatObjWidget(QWidget *parent = nullptr);
  ChatObjWidget(const QString& account,
                QWidget       *parent = nullptr);
  ~ChatObjWidget();

private:

  Ui::ChatObjWidget *ui;
  void innerMake();

signals:

  void sendMess(QString account);
};

#endif // CHATOBJWIDGET_H
