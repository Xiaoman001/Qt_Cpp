#ifndef ROBOTCHAT_H
#define ROBOTCHAT_H

#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include <QMessageBox>
#include <QSettings>

class robotchat : public QWidget {
  Q_OBJECT

public:

  robotchat();
  QString TulingURL;
  QBuffer *JsonBuffer = NULL;
  void    sentrobot(QString str);
  QString gettuing();

private:

  // 显示文本
  QString tuling_get_ans;

signals:

  void back();

public slots:

  // 直接文字识别
  void Tuling_replyFinish(QNetworkReply *reply);
};

#endif // ROBOTCHAT_H
