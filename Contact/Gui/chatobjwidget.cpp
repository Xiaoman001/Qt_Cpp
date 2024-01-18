#include "chatobjwidget.h"
#include "ui_chatobjwidget.h"

void ChatObjWidget::innerMake()
{
  this->setContentsMargins(0, 0, 0, 0);

  this->setWindowFlags(Qt::FramelessWindowHint);

  //    this->setSpacing(0);
  ui->setupUi(this);
  ui->tabWidget->setTabText(0, QString("好友"));
  ui->tabWidget->setTabText(1, QString("群聊"));
  ui->tabWidget->setStyleSheet("border:none;");

  m_chatGroupingListMaker.setMainWindow(this);

  m_chatGroupingListMaker.makeFriendList(m_userId);
  ui->friendTab->setLayout(m_chatGroupingListMaker.m_userContent);

  m_chatGroupingListMaker.makeGroupList(m_userId);
  ui->groupTab->setLayout(m_chatGroupingListMaker.m_groupContent);

  m_chatGroupingListMaker.appendMainWindow(m_isWidget,
                                           m_btns,
                                           m_listWidgets);

  //
  // 初始化QSignalMapper
  // 用QSignalMapper操作 构造的好友/群列表 >>>
  m_myMapper = new QSignalMapper(this);
  {
    using map_int = void (QSignalMapper::*)();
    for (int i = 0; i < this->m_btns.length(); i++) {
      connect(this->m_btns[i], &QPushButton::clicked,
              m_myMapper,
              (map_int) & QSignalMapper::map);
      m_myMapper->setMapping(m_btns[i], i);
    }
  }
  {
    using mapped_int = void (QSignalMapper::*)(int);
    connect(m_myMapper, (mapped_int) & QSignalMapper::mapped,
            this, &ChatObjWidget::onWidgetClicked);
  }
}

ChatObjWidget::ChatObjWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ChatObjWidget)
{
  innerMake();

  // 用QSignalMapper操作 <<<
}

ChatObjWidget::ChatObjWidget(const QString& account, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ChatObjWidget),
  m_account(account)
{
  this->setAccount(account);
  this->innerMake();
}

ChatObjWidget::~ChatObjWidget()
{
  delete ui;
}

// 展开，收起好友列表
void ChatObjWidget::onWidgetClicked(int i) {
  if (this->m_isWidget[i] == true) // 闭合
  {
    this->m_listWidgets[i]->setVisible(false);
    this->m_isWidget[i] = false;
    this->m_btns[i]->setIcon(QIcon(":/lib/jietou2.png"));
    return;
  }

  // 展开
  this->m_listWidgets[i]->setVisible(true);
  this->m_isWidget[i] = true;
  this->m_btns[i]->setIcon(QIcon(":/lib/jietou.png"));
}

// 打开聊天窗口
void ChatObjWidget::setAccount(const QString& account)
{
  m_account = account;
  DataBaseOperaterDemo *pDbOperater = Q_NULLPTR;
  if (!DataBaseOperaterDemo::getInstancePtr_s(pDbOperater)) {
    qDebug() << "连接失败";
    return;
  }
  m_userId = pDbOperater->getUserIdByAccount(m_account);
}

void ChatObjWidget::onDoubleWidgetClicked(QListWidgetItem *witem)
{
  Q_UNUSED(witem);
  qDebug() << witem->text();
  emit(sendMess(witem->text()));

  //  QWidget *pwig = new  Widget(witem);
  //  qDebug() << pwig->findChild<QLabel *>("label2")->text();

  //  qDebug() << "chat obj double clicked";
  //  QWidget *pwig = NULL;
  //  for (int i = 0; i < this->m_listWidgets.length(); i++)
  //  {
  //    pwig = this->m_listWidgets[i]->itemWidget(witem);
  //    if (pwig != NULL) break;
  //  }

  //  // 判断当前窗口在不在
  //  bool isshow = false;
  //  for (int i = 0; i < listchat.length(); i++)
  //  {
  //    if (listchat[i]->getOtheraccount() == pwig->findChild<QLabel *>("label2")->text())
  //    {
  //      isshow = true;
  //      listchat[i]->show();
  //    }
  //  }
  //  if (!isshow)
  //  {
  //    Chat *chat = new Chat(QPixmap(),
  //                          QPixmap(),
  //                          pwig->findChild<QLabel *>("label2")->text(),
  //                          pwig->findChild<QLabel *>("label3")->text(),
  //                          nullptr);
  //    chat->setAccount(m_account);
  //    chat->setAttribute(Qt::WA_DeleteOnClose);
  //    listchat.append(chat);

  //    //    connect(chat, SIGNAL(sendData(QString)),  this, SLOT(MainSendData(QString)));
  //    //    connect(chat, SIGNAL(sendCount(QString)), this, SLOT(listchatcount(QString)));
  //    chat->show();
  //  }
}
