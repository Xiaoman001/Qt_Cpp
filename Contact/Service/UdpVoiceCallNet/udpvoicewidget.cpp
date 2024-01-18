#include "udpvoicewidget.h"
#include "ui_udpvoicewidget.h"

constexpr int LEFT_BORDOR   = 16;
constexpr int TOP_BORDOR    = 16;
constexpr int LABEL_INTEVAL = 64;
constexpr int UP_INTEVAL    = 32;

UdpVoiceWidget::UdpVoiceWidget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget)
{
  ui->setupUi(this);
  m_pUdpCorrespond = new PrepareUdpCorrespond;

  // call request signal slot
  connect(this, &UdpVoiceWidget::signalCallRequest,
          this, &UdpVoiceWidget::slotDoCallRequest);

  // 挂电话
  connect(this, &UdpVoiceWidget::hangUpSelfSignal, this, &UdpVoiceWidget::hangUp);
  connect(this, &UdpVoiceWidget::hangUpOtherSignal,
          this, [this](){
    qDebug() << m_destIp;
    this->m_pUdpCorrespond->sendHangUpToDest(m_destIp);
  });

  // m

  // 收到挂电话信号自己挂掉
  connect(m_pUdpCorrespond, &PrepareUdpCorrespond::signalGotHangUp,
          this, [this](){
    this->m_pListenDialog->deleteLater();
    this->hangUp();
  });

  //  被打电话方通过udp得到拨号人的nickname
  connect(m_pUdpCorrespond, &PrepareUdpCorrespond::signalGotRequestorNickname,
          this, &UdpVoiceWidget::setRequestorNicknameByUdp);

  // 被打电话方
  connect(m_pUdpCorrespond, &PrepareUdpCorrespond::getRequestorIpPort,
          this, [this](QString address) {
    auto addr      = address.split(":");
    this->m_destIp = addr[0];
    this->m_pHostInput->setText(addr[0]);
    this->m_pPortInput->setText(addr[1]);
    this->buildSelectDialog();
    m_pSelectDialog->show();
    connect(m_pSelectDialog, &SelectDialog::acceptCorrespond,
            this, [this, addr]() {
      this->buildListenDialog();
      m_pListenDialog->show();

      // listen dialog 点击hang up按钮，发出hangUpSelfSignal
      // widget 接收到时该信号，主动hang up自己
      connect(m_pListenDialog, &ListenDialog::hangUpSelfSignal,
              this, &UdpVoiceWidget::hangUpSelfSignal);
      connect(m_pListenDialog, &ListenDialog::hangUpSelfSignal,
              this, &UdpVoiceWidget::hangUpOtherSignal);

      // 准备接收对方的音频
      emit this->answerSomeoneSignal();

      // 向对方打电话(向对方传输音频)
      emit this->callSomeoneSignal();

      // m_pUdpCorrespond 向 addr[0]的ip 发送 接受对方通话请求的信号
      emit m_pUdpCorrespond->acceptToDestSignal(addr[0]);
    });
    connect(m_pSelectDialog, &SelectDialog::refuseCorrespond, this, [this, addr]() {
      emit m_pUdpCorrespond->refuseToDestSignal(addr[0]);
    });
  });

  // 打电话方
  // 收到对方同意
  connect(m_pUdpCorrespond, &PrepareUdpCorrespond::gotAcceptSignal, this, [this]() {
    m_pCallDialog->deleteLater();
    this->buildListenDialog();
    m_pListenDialog->show();
    connect(m_pListenDialog, &ListenDialog::hangUpSelfSignal,
            this, &UdpVoiceWidget::hangUpSelfSignal);
    connect(m_pListenDialog, &ListenDialog::hangUpSelfSignal,
            this, &UdpVoiceWidget::hangUpOtherSignal);

    // 准备接收
    emit this->answerSomeoneSignal();

    // 向对方发送
    emit this->callSomeoneSignal();
  });

  // 收到对方拒绝
  connect(m_pUdpCorrespond, &PrepareUdpCorrespond::gotRefuseSignal, this, [this]() {
    this->m_pCallDialog->deleteLater();
  });

  // no name
  auto pCallBtn = new QPushButton(this);
  pCallBtn->setText("call");
  pCallBtn->move(LEFT_BORDOR, TOP_BORDOR);
  auto pHostLabel = new QLabel(this);
  pHostLabel->setText("host: ");
  pHostLabel->move(LEFT_BORDOR, TOP_BORDOR + UP_INTEVAL);
  m_pHostInput = new QLineEdit(this);
  m_pHostInput->move(LEFT_BORDOR + LABEL_INTEVAL, TOP_BORDOR + UP_INTEVAL);
  auto pPortLabel = new QLabel(this);
  pPortLabel->setText("port: ");
  pPortLabel->move(LEFT_BORDOR, TOP_BORDOR + 2 * UP_INTEVAL);
  m_pPortInput = new QLineEdit(this);
  m_pPortInput->move(LEFT_BORDOR + LABEL_INTEVAL, TOP_BORDOR + 2 * UP_INTEVAL);
  auto pReadyBtn = new QPushButton(this);
  pReadyBtn->setText("ready");
  pReadyBtn->move(LEFT_BORDOR, TOP_BORDOR + 3 * UP_INTEVAL);
  m_pHangUpBtn = new QPushButton(this);
  m_pHangUpBtn->setText("hang up");
  m_pHangUpBtn->move(LEFT_BORDOR + 2 * LABEL_INTEVAL, TOP_BORDOR + 4 * UP_INTEVAL);

  // ui callBtn 发起请求
  connect(ui->callBtn, &QPushButton::clicked,
          this, &UdpVoiceWidget::signalCallRequest);

  //
  connect(ui->talkBtn, &QPushButton::clicked, this, [this]() {
    this->buildListenDialog();
    m_pListenDialog->show();
  });
  connect(ui->tokenBtn, &QPushButton::clicked, this, [this]() {
    this->buildSelectDialog();
    m_pSelectDialog->show();
  });

  // call
  connect(pCallBtn, &QPushButton::clicked,
          this, &UdpVoiceWidget::callSomeoneSignal);

  connect(this,     &UdpVoiceWidget::callSomeoneSignal,
          this, &UdpVoiceWidget::callSlot);

  // ready
  connect(pReadyBtn, &QPushButton::clicked,
          this, &UdpVoiceWidget::answerSomeoneSignal);

  connect(this,      &UdpVoiceWidget::answerSomeoneSignal,
          this, &UdpVoiceWidget::answerSlot);

  // 挂断连接，delete 本地的receiver sender
  connect(m_pHangUpBtn, &QPushButton::clicked,
          this, &UdpVoiceWidget::hangUpSelfSignal);

  // 接入Contact后自动开启通话
  connect(this, &UdpVoiceWidget::signalCallInContact,
          this, &UdpVoiceWidget::slotStartCallInContact);
}

UdpVoiceWidget::~UdpVoiceWidget()
{
  if (nullptr != m_pVoiceReceiver) {
    m_pVoiceReceiver->exitRun();
  }
  delete ui;
}

void UdpVoiceWidget::setTargetIpByOutside(const QString& ip)
{
  m_destIp = ip;
  m_pHostInput->setText(ip);
}

void UdpVoiceWidget::setTargetNicknameByOutside(const QString& nickname)
{
  m_targetNickname = nickname;
}

void UdpVoiceWidget::setRequestorNicknameByUdp(const QString& nickname)
{
  m_requestorNickname = nickname;
}

void UdpVoiceWidget::setSelfNicknameByOutside(const QString& nickname)
{
  m_selfNickname = nickname;
}

void UdpVoiceWidget::slotDoCallRequest()
{
  //  // 准备应答
  //  emit this->answerSomeoneSignal();
  // 读取pHostInput的ip
  // 准备向对方发送请求
  m_pUdpCorrespond->setDestAddress(m_pHostInput->text());

  // 获取本地ip并发送
  m_pUdpCorrespond->sendLocalIp();

  // 获取本地self nickname并发送
  m_pUdpCorrespond->sendUserInfo(m_selfNickname);

  // 构造call对方的界面
  this->buildCallDialog();

  // 显示
  m_pCallDialog->show();

  // 设置call对方的端口
  m_pPortInput->setText("10004");
  qDebug() << "target ip:" << m_pHostInput->text();
  qDebug() << "target port:" << m_pPortInput->text();
}

void UdpVoiceWidget::slotStartCallInContact()
{
  // 接入Contact后自动开启通话
  emit this->slotDoCallRequest();
}

void UdpVoiceWidget::callSlot()
{
  if (nullptr != m_pVoiceSender) {
    m_pVoiceSender->deleteLater();
    qDebug() << "delete m_pVoiceSender";
  } else {
    qDebug() << "nullptr m_pVoiceSender";
  }
  m_pVoiceSender = new VoiceSender(this);
  m_pVoiceSender->setAudioFormat(8000, 1, 16);
  auto address = m_pHostInput->text();
  m_pVoiceSender->setDestAddress(address);
  auto port = m_pPortInput->text().toInt();
  m_pVoiceSender->setDestPort(port);
  m_pVoiceSender->myStart();
}

void UdpVoiceWidget::answerSlot()
{
  if (nullptr != m_pVoiceReceiver) {
    m_pVoiceReceiver->exitRun();
  }
  m_pVoiceReceiver = new VoiceReceiver(this);
  connect(m_pVoiceReceiver, &VoiceReceiver::talkingSignal,
          this, &UdpVoiceWidget::changeTalkingStateSlot);
  m_pVoiceReceiver->setCurrentSampleInfo(8000, 1, 16);
  m_pVoiceReceiver->setCurrentVolumn(100);
  m_pVoiceReceiver->start();
  qDebug() << "ready to play";
}

void UdpVoiceWidget::changeTalkingStateSlot(bool isTalking)
{
  m_isTalking = isTalking;
}

void UdpVoiceWidget::hangUp()
{
  if (nullptr != this->m_pVoiceSender) {
    this->m_pVoiceSender->myStop();
    m_pVoiceSender->deleteLater();
    m_pVoiceSender = nullptr;
  }
  if (nullptr != this->m_pVoiceReceiver) {
    this->m_pVoiceReceiver->exitRun();
    m_pVoiceReceiver->disconnect(this);
    m_pVoiceReceiver->deleteLater();
    m_pVoiceReceiver = nullptr;
  }

  // send udp to tell the other one talk is over
}

void UdpVoiceWidget::buildListenDialog()
{
  this->m_pListenDialog = new ListenDialog();
  if (m_isSender) {
    m_pListenDialog->setNickname(m_targetNickname);
  } else {
    m_pListenDialog->setNickname(m_requestorNickname);
  }
}

void UdpVoiceWidget::buildCallDialog()
{
  this->m_pCallDialog = new CallDialog();
  this->m_pCallDialog->setNickname(m_targetNickname);
}

void UdpVoiceWidget::buildSelectDialog()
{
  this->m_pSelectDialog = new SelectDialog();
  m_pSelectDialog->setNickname(m_requestorNickname);
}
