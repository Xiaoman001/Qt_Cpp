#include "contactdirectory.h"
#include "ui_contactdirectory.h"
#include <QPushButton>

contactdirectory::contactdirectory(
  QString  account,
  QWidget *parent) :
  QWidget(parent),
  ui(new Ui::contactdirectory)
{
  ui->setupUi(this);
  chatobj = new ChatObjWidget(account);
  ui->widget_2->layout()->addWidget(chatobj);
  connect(chatobj, SIGNAL(sendMess(QString)), this, SLOT(changeName(QString)));

  robot     = new robotchat();
  myAccount = account;
  setWindowFlags(Qt::FramelessWindowHint | windowFlags());

  //  DataBase
  Usersql a;

  //  QString IpAndPort = a.getIpAndPort(OtherAccount);
  //  qDebug() << IpAndPort;

  // tcp
  tcpSocket = new QTcpSocket;
  tcpSocket->connectToHost("127.0.0.1", 8888);
  connect(tcpSocket, SIGNAL(connected()), this, SLOT(connect_success()));

  //  IpAndPort = a.getIpAndPort(myAccount);
  //  tcpServer = new QTcpServer;
  //  tcpServer->listen(QHostAddress(IpAndPort.split("|")[0]), 8888);
  //  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(new_connect()));

  // 搜索框的图标
  // 一、新建action
  QAction *searchAction = new QAction(ui->searchLine);

  // 二、给action添加icon
  searchAction->setIcon(QIcon(":/pic/search.png"));

  // 三、给空间添加action
  ui->searchLine->addAction(searchAction, QLineEdit::LeadingPosition);

  // call按钮图标
  QIcon phone_ico(":/pic/phone.png");
  ui->call_Button->setIcon(phone_ico);
  ui->call_Button->setIconSize(QSize(18, 18));

  // send按钮图标
  QIcon send_ico(":/pic/send_1.png");
  ui->send_Button->setIcon(send_ico);
  ui->send_Button->setIconSize(QSize(18, 18));

  // fdog
  this->OtherAccount = OtherAccount;
  this->name         = name;
  this->setWindowTitle(name);

  //  tcpClient    = new QTcpSocket(this);
  LabSocketate = new QLabel("Socket状态：");
  LabSocketate->setMinimumWidth(250);
  this->setWindowIcon(QIcon(pixmap));
  this->pixmap   = pixmap;
  this->mypixmap = mypixmap;

  ui->label_name->setText(DataBase.getNameByAccount("61673228"));

  //  机器人
  connect(robot, &robotchat::back, [ = ](){
    reciveDataMessage(robot->gettuing());
  });
}

contactdirectory::~contactdirectory()
{
  delete ui;
}

void contactdirectory::changeName(QString account) {
  OtherAccount = account;
  ui->label_name->setText(DataBase.getNameByAccount(account));
}

// 获取本地IP
QString contactdirectory::getLocalIP()
{
  // 获取本机IPv4地址
  QString   hostName          = QHostInfo::localHostName(); // 本机主机名
  QHostInfo hostInfo          = QHostInfo::fromName(hostName);
  QString   localIP           = "";
  QList<QHostAddress> addList = hostInfo.addresses();
  if (!addList.isEmpty())
  {
    for (int i = 0; i < addList.count(); i++)
    {
      QHostAddress aHost = addList.at(i);
      if (QAbstractSocket::IPv4Protocol == aHost.protocol())
      {
        localIP = aHost.toString();
        break;
      }
    }
  }
  return localIP;
}

// 聊天气泡
QWidget * contactdirectory::CreateWidgetL_R(int i, QString data)
{
  QFont font1;
  font1.setFamily("Microsoft YaHei");
  font1.setPointSize(10);
  font1.setStyleStrategy(QFont::PreferAntialias);
  QWidget *widget = new QWidget();
  widget->setStyleSheet("background:rgba(0,0,0,0);");
  widget->setFixedSize(660, 50);
  QHBoxLayout *horLayout = new QHBoxLayout(); // 水平布局
  horLayout->setContentsMargins(0, 0, 0, 0);
  horLayout->setSpacing(0);

  //  QIcon photo_ico(":/pic/emoji.png");
  QPushButton *btnicon1 = new QPushButton();
  btnicon1->setFixedSize(40, 40);

  //  btnicon->setIcon(photo_ico);
  //  btnicon->setIconSize(QSize(40, 40));

  QString photos;

  //  btnicon1->setStyleSheet("image: url(" + photos + ");background-color: rgb(255, 255, 255);border-radius:7px;");
  if (i == 1) {
    photos = DataBase.getPhotoUrlByAccount(qunOtheraccount);
    btnicon1->setStyleSheet("image: url(" + photos + ");background:rgba(0,0,0,0);");
  }
  QPushButton *btnicon2 = new QPushButton();
  btnicon2->setFixedSize(40, 40);

  //  btnicon->setIcon(photo_ico);
  //  btnicon->setIconSize(QSize(40, 40));
  photos = DataBase.getPhotoUrlByAccount(myAccount);
  btnicon2->setStyleSheet("image: url(" + photos + ");background:rgba(0,0,0,0);");
  QLabel *label = new QLabel(data);
  label->setFont(font1);
  label->setStyleSheet(
    "background-color: rgb(97, 94, 240);border-style:solid;border-radius:10px;color:rgb(255,255,255);padding:5px");
  label->setTextInteractionFlags(Qt::TextSelectableByMouse);
  label->setMaximumHeight(40);
  if (i == 1)
  {
    label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    //    horLayout->addStretch();
    horLayout->addWidget(btnicon1);
    horLayout->addWidget(label);
    horLayout->setSpacing(10);
    QSpacerItem *spacer_h = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    horLayout->addSpacerItem(spacer_h);

    //    QSpacerItem *spacer_h = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    //    horLayout->addSpacerItem(spacer_h);

    //    btnicon->setIcon(this->pixmap);
  }
  else
  {
    label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    horLayout->addStretch();
    horLayout->addWidget(label);
    horLayout->addWidget(btnicon2);
    horLayout->setSpacing(10);

    //    btnicon->setIcon(this->mypixmap);
  }
  widget->setLayout(horLayout);

  ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());
  return widget;
}

void contactdirectory::on_send_Button_clicked()
{
  QDateTime curDateTime = QDateTime::currentDateTime();
  QString   time        = curDateTime.toString("yyyy-MM-dd hh:mm:ss"); // 显示屏幕
  QString   time1       = curDateTime.toString("hh:mm:ss");

  //     数据格式为: 到达方账号，发送方账号，内容
  QString msg = ui->textEdit->toPlainText();

  // 我发送的内容显示在右边
  QWidget *widget = CreateWidgetL_R(2, ui->textEdit->toPlainText());

  if (lastTime == "") {
    lastTime = time;
    QLabel *ltime = new QLabel(time);
    ltime->setStyleSheet("background:rgba(219, 219, 219,0.8);padding:5px;border-radius:4px");
    QHBoxLayout *timespace = new QHBoxLayout();
    QSpacerItem *spacer_h  = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    timespace->addSpacerItem(spacer_h);
    timespace->addWidget(ltime);
    timespace->addSpacerItem(spacer_h);
    QVBoxLayout *verLayout = new QVBoxLayout();
    verLayout->addLayout(timespace);
    verLayout->addWidget(widget);
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setSpacing(0);
    ui->verticalLayout_7->addLayout(verLayout);
  }
  else {
    QDateTime time1 = QDateTime::fromString(lastTime, "yyyy-MM-dd hh:mm:ss");
    QDateTime time2 = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
    int seconds     = time1.secsTo(time2);
    int minutes     = seconds / 60;
    qDebug() << "lastTime" << lastTime;
    qDebug() << "time" << time;
    qDebug() << "minutes" << minutes;
    if (minutes >= 1) {
      lastTime = time;
      QLabel *ltime = new QLabel(time);
      ltime->setStyleSheet("background:rgba(219, 219, 219,0.8);padding:5px;border-radius:4px");
      QHBoxLayout *timespace = new QHBoxLayout();
      QSpacerItem *spacer_h  = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
      timespace->addSpacerItem(spacer_h);
      timespace->addWidget(ltime);
      timespace->addSpacerItem(spacer_h);
      QVBoxLayout *verLayout = new QVBoxLayout();
      verLayout->addLayout(timespace);
      verLayout->addWidget(widget);
      verLayout->setContentsMargins(0, 0, 0, 0);
      verLayout->setSpacing(0);
      ui->verticalLayout_7->addLayout(verLayout);
    }
    else {
      ui->verticalLayout_7->addWidget(widget);
      widget->show();
    }
  }

  ui->textEdit->clear();
  ui->textEdit->setFocus();

  QByteArray str = msg.toUtf8();
  sendMessage(str);
}

void contactdirectory::reciveDataMessage(QString str) {
  QDateTime curDateTime = QDateTime::currentDateTime();
  QString   time        = curDateTime.toString("yyyy-MM-dd hh:mm:ss"); // 显示屏幕
  QString   time1       = curDateTime.toString("hh:mm:ss");

  // 我发送的内容显示在右边
  QWidget *widget = CreateWidgetL_R(1, str);

  if (lastTime == "") {
    lastTime = time;
    QLabel *ltime = new QLabel(time);
    ltime->setStyleSheet("background:rgba(219, 219, 219,0.8);padding:5px;border-radius:4px");
    QHBoxLayout *timespace = new QHBoxLayout();
    QSpacerItem *spacer_h  = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    timespace->addSpacerItem(spacer_h);
    timespace->addWidget(ltime);
    timespace->addSpacerItem(spacer_h);
    QVBoxLayout *verLayout = new QVBoxLayout();
    verLayout->addLayout(timespace);
    verLayout->addWidget(widget);
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setSpacing(0);
    ui->verticalLayout_7->addLayout(verLayout);
  }
  else {
    QDateTime time1 = QDateTime::fromString(lastTime, "yyyy-MM-dd hh:mm:ss");
    QDateTime time2 = QDateTime::fromString(time, "yyyy-MM-dd hh:mm:ss");
    int seconds     = time1.secsTo(time2);
    int minutes     = seconds / 60;
    qDebug() << "lastTime" << lastTime;
    qDebug() << "time" << time;
    qDebug() << "minutes" << minutes;
    if (minutes >= 1) {
      lastTime = time;
      QLabel *ltime = new QLabel(time);
      ltime->setStyleSheet("background:rgba(219, 219, 219,0.8);padding:5px;border-radius:4px");
      QHBoxLayout *timespace = new QHBoxLayout();
      QSpacerItem *spacer_h  = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
      timespace->addSpacerItem(spacer_h);
      timespace->addWidget(ltime);
      timespace->addSpacerItem(spacer_h);
      QVBoxLayout *verLayout = new QVBoxLayout();
      verLayout->addLayout(timespace);
      verLayout->addWidget(widget);
      verLayout->setContentsMargins(0, 0, 0, 0);
      verLayout->setSpacing(0);
      ui->verticalLayout_7->addLayout(verLayout);
    }
    else {
      ui->verticalLayout_7->addWidget(widget);
      widget->show();
    }
  }
}

void contactdirectory::on_close_button_clicked()
{
  this->close();

  // fdog
  emit sendCount(this->OtherAccount);
}

void contactdirectory::on_smallest_Button_clicked()
{
  this->showMinimized();
}

void contactdirectory::new_connect()
{
  qDebug("--new connect--");
  QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(read_data()));
  socketArr.push_back(tcpSocket);
}

void contactdirectory::sendMessage(QString msg)
{
  if (OtherAccount == "61673228") {
    qunOtheraccount = "61673228";
    robot->sentrobot(msg);
    return;
  }

  std::string msg1 =  msg.toStdString();
  msg1 = msg1 + "|" + OtherAccount.toStdString() + "|" + myAccount.toStdString();

  int ret = tcpSocket->write(msg1.c_str(), msg1.size() + 1);

  //  qDebug("--send:%d--", ret);
}

void contactdirectory::connect_success()
{
  qDebug("success");
  sendMessage("1|" + myAccount + "|" + getLocalIP());
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(read_data()));
}

void contactdirectory::read_data()
{
  char buf[256] = {};
  tcpSocket->read(buf, sizeof(buf));
  QString tems(buf);
  qDebug() << "recive" << tems;
  qunOtheraccount = tems.split("|")[2];
  reciveDataMessage(tems.split("|")[0]);
}

void contactdirectory::on_label_name_clicked()
{
  cluster *clustermember = new cluster(OtherAccount, this);
  clustermember->show();
}
