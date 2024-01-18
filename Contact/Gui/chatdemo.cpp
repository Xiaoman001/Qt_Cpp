#include "chatdemo.h"
#include "ui_chatdemo.h"

#if _MSC_VER >= 1600
# pragma execution_character_set("utf-8")
#endif // if _MSC_VER >= 1600

chatdemo::chatdemo(QString  account,
                   QWidget *parent) :
  QWidget(parent),
  ui(new Ui::chatdemo)
{
  ui->setupUi(this);
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

  ui->label_name->setText("今夜无风");

  QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
  item->setSizeHint(QSize(ui->searchLine->width(), 80));

  messageObj *chatobjItem1 = new messageObj(":/Touxiang/9.jpg", "聊天机器人", "hello:)");
  ui->listWidget->addItem(item);
  item->setText("61673228");
  item->setTextColor(QColor(255, 255, 255, 0));
  ui->listWidget->setItemWidget(item, chatobjItem1);
  chatobjItem1->show();

  QListWidgetItem *item1 = new QListWidgetItem(ui->listWidget);
  item1->setSizeHint(QSize(ui->searchLine->width(), 80));
  messageObj *chatobjItem2 = new messageObj(":/Touxiang/8.jpg", "空白集", "morning");
  item1->setText("54781204");
  item1->setTextColor(QColor(255, 255, 255, 0));
  ui->listWidget->setItemWidget(item1, chatobjItem2);
  ui->listWidget->addItem(item1);

  ui->label_name->setText(DataBase.getNameByAccount("61673228"));

  //  机器人
  connect(robot, &robotchat::back, [ = ](){
    reciveDataMessage(robot->gettuing());
  });

  QScrollBar *bar = new QScrollBar();
  bar->setStyleSheet("width:8px;"
                     "background:rgb(97, 94, 240);margin:0px,1px,0px,40px;"
                     "padding-top:0px;padding-bottom:0px;border-radius:4px;"
                     "subcontrol-position: right;"
                     "border-width:0px 0px 0px 0px");

  ui->scrollArea->setVerticalScrollBar(bar);

  ui->scrollArea->move(30, 0);
  ui->scrollArea->setWidgetResizable(true);

  // udp voice 语音通话 >>>
  // call_Button
  m_pUdpVoiceWidget = new UdpVoiceWidget;

  //  m_pUdpVoiceWidget->show();
  connect(ui->call_Button, &QPushButton::clicked,
          this, [this]() {
    //    if (nullptr != m_pUdpVoiceWidget) {
    //      m_pUdpVoiceWidget->deleteLater();
    //    }
    DataBaseOperaterDemo *pDbOperater = nullptr;
    if (!DataBaseOperaterDemo::getInstancePtr_s(pDbOperater)) {
      qDebug() << "连接数据库失败";
    }
    m_pUdpVoiceWidget->setTargetIpByOutside(
      pDbOperater->getIpByAccount(
        m_curAccount));
    auto targetNickname = pDbOperater->getUserNameByAccount(OtherAccount);
    m_pUdpVoiceWidget->setTargetNicknameByOutside(targetNickname);
    auto selfNickname = pDbOperater->getUserNameByAccount(this->myAccount);
    m_pUdpVoiceWidget->setSelfNicknameByOutside(selfNickname);

    // call other
    emit m_pUdpVoiceWidget->signalCallInContact();
  });

  // udp voice 语音通话 <<<

  //  emojo
  emojipicker = new emojipick();
  connect(emojipicker, &emojipick::back, [ = ](){
    ui->textEdit->insertPlainText(emojipicker->getemoji(emojipicker->resulttext));
  });
}

chatdemo::~chatdemo()
{
  delete ui;
}

// 获取本地IP
QString chatdemo::getLocalIP()
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
QWidget * chatdemo::CreateWidgetL_R(int i, QString data)
{
  QFileInfo file("C:/Users/Dell/Desktop/Contact/Gui/photos/test.jpg");
  if (file.exists() == true) {
    //    qDebug() << "data is picture!!!!!!!!!!!!" << data;
    QImage img("C:/Users/Dell/Desktop/Contact/Gui/photos/test.jpg");

    //    qDebug() << "width!!!" << img.width();
    //    qDebug() << "height!!!" << img.height();
    QFont font1;
    font1.setFamily("Microsoft YaHei");
    font1.setPointSize(10);
    font1.setStyleStrategy(QFont::PreferAntialias);
    QWidget *widget = new QWidget();
    widget->setStyleSheet("background:rgba(0,0,0,0);");
    widget->setFixedSize(660, img.height());
    QHBoxLayout *horLayout = new QHBoxLayout(); // 水平布局
    horLayout->setContentsMargins(0, 0, 0, 0);
    horLayout->setSpacing(0);

    //  QIcon photo_ico(":/pic/emoji.png");
    QPushButton *btnicon1 = new QPushButton();
    btnicon1->setFixedSize(40, 40);

    QString photos;

    //  btnicon1->setStyleSheet("image: url(" + photos + ");background-color: rgb(255, 255, 255);border-radius:7px;");
    if (i == 1) {
      photos = DataBase.getPhotoUrlByAccount(OtherAccount);
      btnicon1->setStyleSheet("image: url(" + photos + ");background:rgba(0,0,0,0);");
    }
    QPushButton *btnicon2 = new QPushButton();
    btnicon2->setFixedSize(40, 40);

    //  btnicon->setIcon(photo_ico);
    //  btnicon->setIconSize(QSize(40, 40));
    photos = DataBase.getPhotoUrlByAccount(myAccount);
    btnicon2->setStyleSheet("image: url(" + photos + ");background:rgba(0,0,0,0);");
    QLabel *label = new QLabel();
    label->setPixmap(QPixmap::fromImage(img));

    QFile fileTemp("C:/Users/Dell/Desktop/Contact/Gui/photos/test.jpg");
    fileTemp.remove();
    label->setFont(font1);
    label->setStyleSheet(
      "background-color: rgb(97, 94, 240);border-style:solid;border-radius:10px;color:rgb(255,255,255);padding:5px");
    label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    label->setMinimumHeight(img.height());
    label->setMinimumWidth(img.width());
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
  } else {
    QFont font1;
    font1.setFamily("Microsoft YaHei");
    font1.setPointSize(10);
    font1.setStyleStrategy(QFont::PreferAntialias);

    QWidget *widget = new QWidget();

    if ((isfile == true) || (data.split(":")[0] == "文件")) {
      widget->setFixedSize(650, 125);
    } else {
      widget->setFixedSize(650, 50);
    }

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
      photos = DataBase.getPhotoUrlByAccount(OtherAccount);
      btnicon1->setStyleSheet("image: url(" + photos + ");background:rgba(0,0,0,0);");
    }
    QPushButton *btnicon2 = new QPushButton();
    btnicon2->setFixedSize(40, 40);

    //  btnicon->setIcon(photo_ico);
    //  btnicon->setIconSize(QSize(40, 40));
    photos = DataBase.getPhotoUrlByAccount(myAccount);
    btnicon2->setStyleSheet("image: url(" + photos + ");background:rgba(0,0,0,0);");
    QLabel *label;
    if ((isfile == true) || (data.split(":")[0] == "文件")) {
      label = new QLabel();
      QLabel *labName = new QLabel(label);
      labName->setObjectName("labName");
      if (data.split(":")[0] == "文件") {
        labName->setText(data.split(":")[1]);
      } else {
        labName->setText(filename + "\n");
      }
      labName->setStyleSheet("color: rgb(255, 255, 255);font-size:20px;");
      labName->move(90, 40);
      label->setMinimumHeight(125); label->setMinimumWidth(300);
      label->setStyleSheet(
        "background-color: rgb(97, 94, 240);border-style:solid;border-radius:10px;font-size:20px;color: rgb(255, 255, 255);");
      QLabel *pic = new QLabel(label);

      pic->setStyleSheet("image: url(:/pic/filepic.png);");
      pic->setMinimumHeight(75); pic->setMinimumWidth(75);
      pic->move(5, 0);
      QLabel *tips        = new QLabel(label);
      double  kb_filesize = 0;
      if (data.split(":")[0] == "文件") {
        QString receivePath =   "D:/Qfile/" + labName->text();
        QFile   receiveFile(receivePath);
        kb_filesize = receiveFile.size() / 1024;
      } else {
        kb_filesize = filesize / 1024;
      }

      tips->setText("文件大小：" + QString::number(kb_filesize, 'f', 2) + "kb");
      tips->setStyleSheet("border-style: flat;background: transparent;color: white;font-size:15px;");
      tips->move(5, 75);
      QPushButton *button1 = new QPushButton(label);
      button1->setText("存网盘");
      button1->move(50, 100);
      button1->setStyleSheet("border-style: flat;background: transparent;color: white;font-size:15px;");
      connect(button1, SIGNAL(clicked(bool)), this, SLOT(jumpToWeb()));
      QPushButton *button2 = new QPushButton(label);
      if (i == 1) {
        button2->setText("下载");
        connect(button2, SIGNAL(clicked(bool)), this, SLOT(download()));
      } else {
        button2->setText("已下载");
      }
      button2->move(130, 100);
      button2->setStyleSheet("border-style: flat;background: transparent;color: white;font-size:15px;");
      QPushButton *button3 = new QPushButton(label);
      button3->setText(" 另存为");
      button3->move(185, 100);
      button3->setStyleSheet("border-style: flat;background: transparent;color: white;font-size:15px;");
      connect(button3, SIGNAL(clicked(bool)), this, SLOT(otherSave()));
      QPushButton *button4 = new QPushButton(label);
      button4->setText("转发");
      button4->move(250, 100);
      button4->setStyleSheet("border-style: flat;background: transparent;color: white;font-size:15px;");
      isfile = false;
    } else {
      label = new QLabel(data); // 显示文本的地方
      label->setFont(font1);
      label->setStyleSheet(
        "background-color: rgb(97, 94, 240);border-style:solid;border-radius:10px;color:rgb(255,255,255);padding:5px");
      label->setTextInteractionFlags(Qt::TextSelectableByMouse);
      label->setMaximumHeight(40);
    }

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
}

void chatdemo::on_send_Button_clicked()
{
  QDateTime curDateTime = QDateTime::currentDateTime();
  QString   time        = curDateTime.toString("yyyy-MM-dd hh:mm:ss"); // 显示屏幕
  QString   time1       = curDateTime.toString("hh:mm:ss");

  //     数据格式为: 到达方账号，发送方账号，内容
  QString msg = ui->textEdit->toPlainText();
  if (isfile == true) {
    msg = "文件:" + filename;
    qDebug() << "242：" << msg;
  }

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

void chatdemo::reciveDataMessage(QString str) {
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

void chatdemo::on_close_button_clicked()
{
  this->close();

  // fdog
  emit sendCount(this->OtherAccount);
}

void chatdemo::on_smallest_Button_clicked()
{
  this->showMinimized();
}

void chatdemo::new_connect()
{
  qDebug("--new connect--");
  QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(read_data()));
  socketArr.push_back(tcpSocket);
}

void chatdemo::sendMessage(QString msg)
{
  if (OtherAccount == "61673228") {
    robot->sentrobot(msg);
    return;
  }

  std::string msg1 =  msg.toStdString();
  msg1 = msg1 + "|" + OtherAccount.toStdString() + "|" + myAccount.toStdString();
  int ret = tcpSocket->write(msg1.c_str(), msg1.size() + 1);

  //  qDebug("--send:%d--", ret);
}

void chatdemo::connect_success()
{
  qDebug("success");
  sendMessage("1|" + myAccount + "|" + getLocalIP());
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(read_data()));
}

void chatdemo::read_data()
{
  char buf[256] = {};
  tcpSocket->read(buf, sizeof(buf));
  QString tems(buf);
  reciveDataMessage(tems.split("|")[0]);
  qDebug() << "收到了" << buf;
}

void chatdemo::read_Alldata()
{
  for (int i = 0; i < socketArr.size(); i++)
  {
    if (socketArr[i]->bytesAvailable())
    {
      char buf[256] = {};
      socketArr[i]->read(buf, sizeof(buf));

      char buf2[256] = {};
      sprintf(buf2, "%d:%s", i, buf);

      for (int j = 0; j < socketArr.size(); j++)
      {
        char buf1[256] = {};
        sprintf(buf1, "%d:%s", i, buf);
        socketArr[j]->write(buf1, sizeof(buf1));
      }
    }
  }
}

void chatdemo::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
  OtherAccount = item->text();

  // udp voice 语音通话 >>>
  m_curAccount = OtherAccount;

  // udp voice 语音通话 <<<
  ui->label_name->setText(DataBase.getNameByAccount(item->text()));
}

void chatdemo::on_document_Button_clicked()
{
  isfile = true;
  QDir *folder = new QDir;
  bool  exist  = folder->exists("D:/Qfile");
  if (exist == false) {
    bool ok = folder->mkdir("D:/Qfile");
    if (ok) {
      qDebug() << "创建文件夹成功";
    } else {
      qDebug() << "创建文件夹失败";
    }
  }

  // 选择上传文件
  QString filepath = QFileDialog::getOpenFileName(this, "选择文件", "../");
  if (filepath.isEmpty() == false)
  {
    filename.clear();
    filesize = 0;

    // 获取文件信息
    QFileInfo info(filepath);
    filename = info.fileName();
    filesize = info.size();
    qDebug() << "path:" << filepath << "filename" << filename << "size" << filesize;

    // 重置已发送大小为0
    sendfilesize = 0;

    // 只读方式打开文件
    file.setFileName(filepath);
    bool isok = file.open(QIODevice::ReadOnly);

    if (isok == false) {
      qDebug() << "只读打开文件失败！495";
      return;
    }

    /*下面开始计算移动文件的名字*/
    QString newpath = "D:/Qfile/" + filename;
    QFile   newfile(newpath);
    int     identify = 1;
    while (newfile.exists() && identify < 5) {
      QList<QString> data_1 = newpath.split(".");
      QString temp          = newpath;
      temp = data_1[0] + "(" + QString::number(identify) + ")." + data_1[1]; // 字符串切割
      newfile.setFileName(temp);
      identify++;
    }
    if (identify != 1) {
      filename = filename.split(".")[0] + "(" + QString::number(identify - 1) + ")." + filename.split(".")[1];
      newpath  = newpath.split(".")[0] + "(" + QString::number(identify - 1) + ")." + newpath.split(".")[1];
    }

    on_send_Button_clicked();

    file.copy(newpath);
  }
  else
  {
    qDebug() << "打开文件错误！";
  }
}

void chatdemo::otherSave()
{
  QLabel *findLabName = (QLabel *)(((QPushButton *)sender())->parentWidget()->findChild<QLabel *>("labName"));

  // 选择另存为的文件路径
  QFileDialog fileDialog;
  QString     strTargetFile = fileDialog.getExistingDirectory(this,
                                                              tr("选择另存为路径"),
                                                              "D:/Qfile/" + findLabName->text());
  qDebug() << "499：" << strTargetFile;
  QDir dir(strTargetFile);
  if (!dir.exists()) {
    qDebug() << "文件路径不存在";
  } else {
    file.copy(strTargetFile + "/" + findLabName->text());
    repaint();
  }
}

void chatdemo::download()
{
  QLabel *findLabName = (QLabel *)(((QPushButton *)sender())->parentWidget()->findChild<QLabel *>("labName"));

  // 选择保存的文件路径
  QFileDialog fileDialog;
  QString     strTargetFile = fileDialog.getExistingDirectory(this,
                                                              tr("选择下载路径"),
                                                              "D:/Qfile/" + findLabName->text());
  qDebug() << "499：" << strTargetFile;
  QDir dir(strTargetFile);
  if (!dir.exists()) {
    qDebug() << "文件路径不存在";
  } else {
    bool successCopy = file.copy(strTargetFile + "/" + findLabName->text());
    if (successCopy) {
      ((QPushButton *)sender())->setText("已下载");
      ((QPushButton *)sender())->setMinimumWidth(50);
      disconnect(((QPushButton *)sender()), SIGNAL(clicked(bool)), this, SLOT(download()));
      repaint();
    }
  }
}

void chatdemo::jumpToWeb()
{
  const QUrl regUrl(QLatin1String("https://pan.baidu.com"));
  QDesktopServices::openUrl(regUrl);
}

void chatdemo::on_history_Button_clicked()
{
  QStringList tem =  DataBase.getRecordByAccount(myAccount);
  History = new history(tem);
  History->show();
}

void chatdemo::on_speak_Button_2_clicked()
{
  //  keybd_event(112, 0, 0, 0);
}

void chatdemo::on_label_name_clicked()
{
  cluster *clustermember = new cluster(myAccount, this);
  clustermember->show();
}

void chatdemo::on_speak_Button_clicked()
{
  QProcess myProcess;
  QString  program;
  program.append("powershell.exe");
  QStringList arguments;

  //    QString filepath = "e:/PythonPrograms/test/env python.py";

  arguments << "python \"C:/Users/Dell/Desktop/Contact/Service/env python.py\"";
  myProcess.start(program, arguments);
  myProcess.waitForFinished();
  QString strTemp = QString::fromLocal8Bit(myProcess.readAllStandardOutput());

  ui->textEdit->setText(strTemp);
}

void chatdemo::on_emoji_Button_clicked()
{
  emojipicker->show();
  emojipicker->move(this->x() + 300, this->y() + 390);
}
