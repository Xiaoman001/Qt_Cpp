#ifndef IGTOOLS_H
#define IGTOOLS_H

#include <QObject>

class IgTools : public QObject
{
  Q_OBJECT
 public:
  explicit IgTools(QObject *parent = nullptr);
  static QString getLocalIp();
  static QString getWifiIp();
 signals:

};

#endif // IGTOOLS_H
