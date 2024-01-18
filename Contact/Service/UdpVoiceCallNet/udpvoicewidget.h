#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "voicereceiver.h"
#include "voicesender.h"
#include "listendialog.h"
#include "calldialog.h"
#include "selectdialog.h"
#include "PrepareUdpCorrespond.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class UdpVoiceWidget : public QWidget {
  Q_OBJECT

public:

  UdpVoiceWidget(QWidget *parent = nullptr);
  ~UdpVoiceWidget();

  void setTargetIpByOutside(const QString& ip);
  void setTargetNicknameByOutside(const QString& nickname);
  QString m_targetNickname;
  void setRequestorNicknameByUdp(const QString& nickname);
  QString m_requestorNickname;
  void setSelfNicknameByOutside(const QString& nickname);
  QString m_selfNickname;

  QString m_destIp;
  quint16 m_destPort = 10004;
  quint16 m_udpPort  = 10014;

signals:

  void callSomeoneSignal();
  void answerSomeoneSignal();

  void hangUpSelfSignal();
  void hangUpOtherSignal();

  // 点击左侧ui->callBtn关联该信号
  // 该信号产生一个call其他人的udp请求
  void signalCallRequest();

  // 整入Contact后call
  void signalCallInContact();

public slots:

  // signalCallRequest该信号产生一个call其他人的udp请求
  void slotDoCallRequest();

  // 整入Contact后call
  void slotStartCallInContact();

  void callSlot();
  void answerSlot();
  void changeTalkingStateSlot(bool isTalking);
  void hangUp();

private:

  Ui::Widget *ui;

  //
  QLineEdit *m_pHostInput;
  QLineEdit *m_pPortInput;

  //  QPushButton *m_pRefuseBtn;
  QPushButton *m_pHangUpBtn;

  //
  VoiceReceiver *m_pVoiceReceiver = nullptr;
  VoiceSender *m_pVoiceSender     = nullptr;
  bool m_isTalking                = false;
  bool m_isSender                 = false;

  // 通信
  ListenDialog *m_pListenDialog = nullptr;
  CallDialog *m_pCallDialog     = nullptr;
  SelectDialog *m_pSelectDialog = nullptr;
  void buildListenDialog();
  void buildCallDialog();
  void buildSelectDialog();

  // udp 通知 要进行通信
  PrepareUdpCorrespond *m_pUdpCorrespond = nullptr;
};
#endif // WIDGET_H
