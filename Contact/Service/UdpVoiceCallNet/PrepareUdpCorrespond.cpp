#include "PrepareUdpCorrespond.h"
#include <QDataStream>
#include "igtools.h"

PrepareUdpCorrespond::PrepareUdpCorrespond(QObject *parent) : QObject(parent)
{
  m_pSender = new QUdpSocket(this);

  //  m_destAddress.setAddress("192.168.3.15");
  //  m_destAddress.setAddress("192.168.3.26");

  m_destAddress.setAddress("127.0.0.1");

  // server 监听10014端口
  m_pReceiver = new QUdpSocket(this);
  m_pReceiver->bind(m_receivePort, QUdpSocket::ShareAddress);

  // 将处理接收信息的函数绑定套接字端口
  connect(m_pReceiver, &QUdpSocket::readyRead, this, &PrepareUdpCorrespond::processReceivedMsg);

  // 手动发消息
  //
  connect(this, &PrepareUdpCorrespond::acceptToDestSignal,
          this, &PrepareUdpCorrespond::sendAcceptToDest);
  connect(this, &PrepareUdpCorrespond::refuseToDestSignal,
          this, &PrepareUdpCorrespond::sendRefuseToDest);
  connect(this, &PrepareUdpCorrespond::hangUpToDestSignal,
          this, &PrepareUdpCorrespond::sendHangUpToDest);
}

void PrepareUdpCorrespond::sendLocalIp()
{
  m_isSender = true;
  QByteArray  datagram;
  QDataStream out(&datagram, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_12);
  auto ip = IgTools::getWifiIp();
  if ("" == ip) {
    ip = IgTools::getLocalIp();
  }
  ip.append(":10004");
  out << ip;
  m_pSender->writeDatagram(datagram, m_destAddress, m_sendPort);
}

void PrepareUdpCorrespond::sendUserInfo(const QString& nickname)
{
  QByteArray  datagram;
  QDataStream out(&datagram, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_12);
  auto info = "info:" + nickname;
  out << info;
  m_pSender->writeDatagram(datagram, m_destAddress, m_sendPort);
}

void PrepareUdpCorrespond::acceptRequestorAddress(const QString& receiveMsg)
{
  auto addr = receiveMsg.split(":");
  m_requestorAddress.setAddress(addr[0]);
  emit this->getRequestorIp(m_requestorAddress);
  emit this->getRequestorPort(addr[1]);
  emit this->getRequestorIpPort(receiveMsg);
}

QString PrepareUdpCorrespond::readOneMsgFromUdp()
{
  QByteArray datagram;
  datagram.resize(m_pReceiver->pendingDatagramSize());
  m_pReceiver->readDatagram(datagram.data(), datagram.size());
  QDataStream in(&datagram, QIODevice::ReadOnly);
  in.setVersion(QDataStream::Qt_5_12);
  QString receiveMsg;
  in >> receiveMsg;
  return receiveMsg;
}

void PrepareUdpCorrespond::sendReact(QString react)
{
  QByteArray  datagram;
  QDataStream out(&datagram, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_12);
  out << react;
  m_pSender->writeDatagram(datagram, m_destAddress, m_sendPort);
}

void PrepareUdpCorrespond::sendAccept()
{
  this->sendReact("accept");
}

void PrepareUdpCorrespond::sendRefuse()
{
  this->sendReact("refuse");
}

void PrepareUdpCorrespond::processReceivedMsg()
{
  auto receiveMsg = readOneMsgFromUdp();
  if (m_isSender) {
    if ("refuse" == receiveMsg) {
      emit this->gotRefuseSignal();
    } else if ("accept" == receiveMsg) {
      emit this->gotAcceptSignal();
    } if ("hang up" == receiveMsg) {
      emit this->signalGotHangUp();
    } else {}
  } else {
    QString msg     = receiveMsg;
    auto    strList = msg.split(":");
    if ("info" == strList.at(0)) {
      emit this->signalGotRequestorNickname(strList.at(1));
    } if ("hang up" == receiveMsg) {
      emit this->signalGotHangUp();
    } else  {
      this->acceptRequestorAddress(receiveMsg);
    }
  }
}

void PrepareUdpCorrespond::sendAcceptToDest(QString address)
{
  this->setDestAddress(address);
  this->sendAccept();
}

void PrepareUdpCorrespond::sendRefuseToDest(QString address)
{
  this->setDestAddress(address);
  this->sendRefuse();
}

void PrepareUdpCorrespond::sendHangUpToDest(QString address)
{
  this->setDestAddress(address);
  this->sendReact("hang up");
}

void PrepareUdpCorrespond::setDestAddress(QString address)
{
  this->m_destAddress.setAddress(address);
}
