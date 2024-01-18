#include "chatgroupinglistmaker.h"
#include <QScrollArea>
#include "Service/globalobserver.h"
#include <QListWidgetItem>
#include <QListWidget>
#include "Gui/chatobjwidget.h"

// #include "mainwindow.h"
constexpr int LIST_BTN_WIDTH       = 224;
constexpr int LIST_ITEM_WIDTH      = 200;
constexpr int LIST_ITEM_HEIGHT     = 48;
constexpr int LIST_INTERVAL        = 8;
constexpr int LIST_INTERVAL_WIDTH  = 8;
constexpr int LIST_INTERVAL_HEIGHT = 8;

ChatGroupingListMaker::ChatGroupingListMaker(QObject *parent) : QObject(parent)
{}

void ChatGroupingListMaker::setMainWindow(QWidget *mainThis)
{
  this->m_mainWindow = mainThis;
}

void ChatGroupingListMaker::appendMainWindow(QList<bool>         & mainIsWidget,
                                             QList<QPushButton *>& mainBtns,
                                             QList<QListWidget *>& mainlistWidgets)
{
  mainIsWidget.append(m_isWidget);
  mainBtns.append(m_btns);
  mainlistWidgets.append(m_listWidgets);
}

/*
 * @brief 构造好友列表
 * @param void
 * @return void
 * @author ig
 */
void ChatGroupingListMaker::makeInnerFor(
  int                   groupingId,
  QListWidget          *pListWidget,
  DataBaseOperaterDemo *pDbOperater,
  ChatObjType           type,
  int                 & sum) {
  //  // 2022.03.15 >>>>>>>>>>>>>
  //  // 循环开始前初始化分组所占的大小
  //  QWidget *widget = new QWidget(m_mainWindow);

  //  QListWidgetItem *pListItem = new QListWidgetItem(pListWidget);

  //  // 每个好友所占的大小
  //  pListItem->setSizeHint(QSize(LIST_ITEM_WIDTH - LIST_INTERVAL_WIDTH,
  //                               LIST_ITEM_HEIGHT - LIST_INTERVAL_HEIGHT)); // 每次改变Item的高度
  //  pListWidget->setItemWidget(pListItem, widget);
  //  pListWidget->setFixedSize(LIST_ITEM_WIDTH, 0);

  //  // 2022.03.15 <<<<<<<<<<<<<<

  // 此处初始化会忽略长度为0的数据
  sum = -1;
  QList<int> memberIds =  pDbOperater->
                         getMemberIdsOfGroupingByGroupId(groupingId,
                                                         type);
  for (auto& memberId: memberIds) {
    sum++;

    constexpr int width_1 = 2;
    constexpr int height  = 32;

    // unknown
    //    QLabel *l1 = new QLabel();
    //    l1->setFixedSize(width_1, height);

    // unknown
    QPushButton *pIconBtn = new QPushButton();
    pIconBtn->setFixedSize({ 32, height });
    pIconBtn->setIconSize(QSize(32, height));
    {
      // 图标url
      QIcon urlIcon(pDbOperater->getPhotoUrlByIdAndType(memberId, type));
      pIconBtn->setStyleSheet("background:rgba(0,0,0,0)");
      pIconBtn->setIcon(urlIcon);
    }

    //     unknown
    QLabel *la2 = new QLabel(
      QString("%1")
      .arg(QString::number(memberId)));
    la2->setObjectName("label2");
    la2->hide();

    // 分组下单个好友的名称
    QLabel *pChatObjNameLabel = new QLabel(pDbOperater->
                                           getNameByIdAndType(memberId,
                                                              type));

    pChatObjNameLabel->setFixedSize({ 100, 32 });
    pChatObjNameLabel->setObjectName("label3");
    pChatObjNameLabel->setFont(Globalobserver::font2);

    // 放入布局
    // 水平布局
    QHBoxLayout *horLayout = new QHBoxLayout();
    horLayout->setMargin(0);
    horLayout->setContentsMargins(0, 0, 0, 0);
    horLayout->setSpacing(0);

    //    horLayout->addWidget(l1);
    horLayout->addWidget(pIconBtn);

    //    horLayout->addWidget(la2);

    horLayout->addWidget(pChatObjNameLabel);

    QWidget *widget = new QWidget(m_mainWindow);
    widget->setLayout(horLayout);

    // list item 添加阴影
    //    widget->setStyleSheet("background:rgba(232, 255, 149,0);");
    QListWidgetItem *pListItem = new QListWidgetItem(pListWidget);
    pListItem->setText(pDbOperater->getAccountByIdAndType(memberId,
                                                          type));
    pListItem->setSizeHint(QSize(LIST_ITEM_WIDTH - LIST_INTERVAL_WIDTH,
                                 LIST_ITEM_HEIGHT - LIST_INTERVAL_HEIGHT)); // 每次改变Item的高度
    pListWidget->setItemWidget(pListItem, widget);

    //
    pListWidget->setFixedSize(LIST_ITEM_WIDTH, LIST_ITEM_HEIGHT * (sum + 1));
    pListWidget->setStyleSheet("QListWidget::Item{background-color: rgba(203, 203, 203,200);}"
                               "QListWidget::Item:hover{background-color: rgb(193, 193, 193);}"
                               "QListWidget::Item:selected{background-color: rgb(193, 193, 193);}"
                               "QListWidget{outline:0px;}");
  }
}

void ChatGroupingListMaker::makeChatObjList(
  int          userId,
  QVBoxLayout *pGroupingContentLayout,
  ChatObjType  type) {
  // 连接数据库
  DataBaseOperaterDemo *pDbOperater = Q_NULLPTR;
  if (!DataBaseOperaterDemo::getInstancePtr_s(pDbOperater)) {
    qDebug() << "连接失败";
    return;
  }
  QList<int> groupingIds = pDbOperater->
                           getGroupingIdsByUserId(userId,
                                                  type);

  // 构造分组
  for (auto& groupingId : groupingIds) {
    // 创建分组信息
    QPushButton *pBtn = new QPushButton(
      QIcon(":/lib/jietou.png"),
      " 分组 "); // xxx
    pBtn->setFont(Globalobserver::font1);
    this->m_btns.append(pBtn);
    this->m_isWidget.append(true);
    pBtn->setFixedSize(LIST_BTN_WIDTH, 38);
    QSize btnsize(36, 36);
    pBtn->setIconSize(btnsize);

    pBtn->setStyleSheet("QPushButton{text-align: left;border-style:solid;}"
                        "QPushButton:hover{text-align: left;border-style:solid;}");

    // 加入分组信息
    pGroupingContentLayout->addWidget(pBtn);

    auto pListWidget = new QListWidget(m_mainWindow);

    //    {
    //      auto ptr = dynamic_cast<MainWindow *>(m_mainWindow);
    //      connect(pListWidget, &QListWidget::itemDoubleClicked,
    //              ptr, &MainWindow::onDoubleWidgetClicked);
    //    }

    {
      auto ptr = dynamic_cast<ChatObjWidget *>(m_mainWindow);
      connect(pListWidget, &QListWidget::itemDoubleClicked,
              ptr, &ChatObjWidget::onDoubleWidgetClicked);
    }
    this->m_listWidgets.append(pListWidget);
    pListWidget->setFrameShape(QListWidget::NoFrame);

    // 构造分组下面的项
    int sum = -1;
    this->makeInnerFor(groupingId, pListWidget, pDbOperater, type, sum);

    // xx
    // 设置分组的内容
    pBtn->setText(pDbOperater->
                  getNameByIdAndType(
                    groupingId,
                    ChatObjType::Grouping)
                  + "     "
                  + QString::number(sum + 1)
                  + "/"
                  + QString::number(sum + 1));
    pGroupingContentLayout->addWidget(pListWidget);
    pListWidget->setObjectName(pDbOperater->
                               getNameByIdAndType(
                                 groupingId,
                                 ChatObjType::Grouping));
  }
}

void ChatGroupingListMaker::makeFriendList(int userId)
{
  QVBoxLayout *pGroupingContentLayout = new QVBoxLayout();

  // 设置边距为0
  pGroupingContentLayout->setMargin(0);
  pGroupingContentLayout->setContentsMargins(0, 0, 0, 0);
  pGroupingContentLayout->setSpacing(0);

  // 显示等级
  //  ui->toolButton_5->setText("   " + m_sqlConnect.getGrade());

  // xxxxxxxxx >>>
  this->makeChatObjList(userId,
                        pGroupingContentLayout,
                        ChatObjType::User);

  // xxxx <<<

  pGroupingContentLayout->addStretch();

  //
  auto pScrollArea = new QScrollArea;
  pScrollArea->setFrameShape(QFrame::NoFrame);
  auto pGridLayout = new QGridLayout;
  pGridLayout->addWidget(pScrollArea);

  //
  pScrollArea->setLayout(pGroupingContentLayout);

  //  this->m_UiTab.setLayout(pGridLayout);
  this->m_userContent = pGridLayout;
}

void ChatGroupingListMaker::makeGroupList(int userId)
{
  // xxxxxxxxx
  QVBoxLayout *pGroupingContentLayout = new QVBoxLayout();

  // 设置边距为0
  pGroupingContentLayout->setContentsMargins(0, 0, 0, 0);
  pGroupingContentLayout->setSpacing(0);

  // xxxxxxxxx >>>
  this->makeChatObjList(userId,
                        pGroupingContentLayout,
                        ChatObjType::Group);

  // xxxx <<<

  pGroupingContentLayout->addStretch();

  //
  auto pScrollArea = new QScrollArea;
  pScrollArea->setFrameShape(QFrame::NoFrame);
  auto pGridLayout = new QGridLayout;
  pGridLayout->addWidget(pScrollArea);
  pScrollArea->setLayout(pGroupingContentLayout);
  this->m_groupContent = pGridLayout;
}
