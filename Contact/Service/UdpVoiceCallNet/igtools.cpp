#include "igtools.h"
#include <QHostInfo>
#include <QNetworkInterface>

IgTools::IgTools(QObject *parent) : QObject(parent)
{

}

QString IgTools::getLocalIp()
{
  //获取本机IPv4地址
  QString hostName = QHostInfo::localHostName();//本机主机名
  QHostInfo hostInfo = QHostInfo::fromName(hostName);
  QString localIP = "";
  QList<QHostAddress> addList = hostInfo.addresses();
  if (!addList.isEmpty()) {
    for (auto &aHost : addList) {
      if (QAbstractSocket::IPv4Protocol == aHost.protocol()) {
        localIP = aHost.toString();
        break;
      }
    }
  }
  return localIP;
}

QString IgTools::getWifiIp()
{
  QString text;
  QTextStream out(&text);
  QList<QNetworkInterface> ifaceList = QNetworkInterface::allInterfaces();
  for (int i = 0; i < ifaceList.count(); i++) {
    QNetworkInterface var = ifaceList.at(i);
    qDebug() << var.type() << "  ";
    qDebug() << var.flags() << endl;
    if (!(var.flags() & QNetworkInterface::IsUp) || !(var.flags() & QNetworkInterface::IsRunning)) {
      continue;
    }
    if (var.humanReadableName() != "WLAN" && var.humanReadableName() != "Ethernet") {
      continue;
    }
    // 读取一个IP地址的关联信息列表
    QList<QNetworkAddressEntry> entryList = var.addressEntries();
    for (int j = 0; j < entryList.count(); j++) {
      QNetworkAddressEntry entry = entryList.at(j);
      qDebug() << " IP: " << entry.ip().toString() << endl;
      return entry.ip().toString();
    }
  }
  return "";
}
