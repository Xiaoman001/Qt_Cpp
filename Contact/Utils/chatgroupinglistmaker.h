#ifndef CHATGROUPINGLISTMAKER_H
#define CHATGROUPINGLISTMAKER_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QListWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include "Dbal/databaseoperaterdemo.h"

class ChatGroupingListMaker : public QObject {
  Q_OBJECT

public:

  QLayout *m_groupContent = Q_NULLPTR;
  QLayout *m_userContent  = Q_NULLPTR;
  QWidget *m_mainWindow   = Q_NULLPTR;

  explicit ChatGroupingListMaker(QObject *parent = nullptr);
  void setMainWindow(QWidget *mainThis);
  void appendMainWindow(QList<bool>         & mainIsWidget,
                        QList<QPushButton *>& mainBtns,
                        QList<QListWidget *>& mainlistWidgets);
  void makeFriendList(int userId);

  void makeGroupList(int userId);

  void makeChatObjList(int          userId,
                       QVBoxLayout *pGroupingContentLayout,
                       ChatObjType  type);

  void makeInnerFor(
    int                   groupingId,
    QListWidget          *listwidget,
    DataBaseOperaterDemo *pDbOperater,
    ChatObjType           type,
    int                 & sum);

signals:

private:

  QList<bool>m_isWidget;             // 列表展开
  QList<QPushButton *>m_btns;        // listbtn分组名
  QList<QListWidget *>m_listWidgets; // listwidget分组列表
  QWidget m_UiTab;
};

#endif // CHATGROUPINGLISTMAKER_H
