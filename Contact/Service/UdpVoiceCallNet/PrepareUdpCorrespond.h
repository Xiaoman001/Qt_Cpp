#ifndef PREPAREUDPCORRESPOND_H
#define PREPAREUDPCORRESPOND_H

#include <QObject>
#include <QUdpSocket>

class PrepareUdpCorrespond : public QObject {
  Q_OBJECT

public:

  explicit PrepareUdpCorrespond(QObject *parent = nullptr);

  void    setDestAddress(QString address);
  void    acceptRequestorAddress(const QString& receiveMsg);

  QString readOneMsgFromUdp();

public slots:

  void sendReact(QString request);
  void sendAccept();
  void sendRefuse();
  void sendLocalIp();
  void sendUserInfo(const QString& nickname);
  void processReceivedMsg();
  void sendAcceptToDest(QString);
  void sendRefuseToDest(QString);
  void sendHangUpToDest(QString);

private:

  bool m_isSender = false;

  // client 向对方发送自身 ip port
  QUdpSocket *m_pSender = nullptr;
  quint16 m_sendPort    = 10014;
  QHostAddress m_destAddress;

  // server 监听端口 接收对方 ip port
  QUdpSocket *m_pReceiver = nullptr;
  quint16 m_receivePort   = 10014;

  //  quint16 m_receivePort = 10014;
  //
  // Requestor
  QHostAddress m_requestorAddress;

signals:

  void getRequestorIp(QHostAddress address);
  void getRequestorPort(QString port);
  void getRequestorIpPort(QString address);
  void gotRefuseSignal();
  void gotAcceptSignal();

  void acceptToDestSignal(QString);
  void refuseToDestSignal(QString);
  void hangUpToDestSignal(QString);

  //
  void signalGotRequestorNickname(QString);
  void signalGotHangUp();
};

#endif // PREPAREUDPCORRESPOND_H
