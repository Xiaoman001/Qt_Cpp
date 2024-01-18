#include "robotchat.h"
robotchat::robotchat()
{
  tuling_get_ans = "获取失败";
}

void robotchat::sentrobot(QString str) {
  QString Url = "http://api.qingyunke.com/api.php?key=free&appid=0&msg=" + str;
  QUrl    url;
  url.setUrl(Url);
  QNetworkRequest request(url);
  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(Tuling_replyFinish(QNetworkReply*)));
  manager->get(request);
}

QString robotchat::gettuing() {
  return tuling_get_ans;
}

void robotchat::Tuling_replyFinish(QNetworkReply *reply)
{
  QString data = reply->readAll();
  qDebug() << "return " + data;
  QJsonParseError json_error;

  QJsonDocument json = QJsonDocument::fromJson(data.toUtf8(), &json_error);
  if (json_error.error == QJsonParseError::NoError)
  {
    if (json.isObject())
    {
      QJsonObject jsonObj = json.object();

      if (jsonObj.contains("content"))
      {
        qDebug() << "成功获取";
        QJsonValue text_value = jsonObj.take("content");
        if (text_value.isString())
        {
          tuling_get_ans = text_value.toVariant().toString();
          tuling_get_ans.replace("br", "\n");
          qDebug() << "!!!" << tuling_get_ans;
        }
      }
    }
  }
  reply->deleteLater();
  emit back();
}
