#include "databaseoperaterdemo.h"
#include <QIcon>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QPixmap>

DataBaseOperaterDemo *DataBaseOperaterDemo::s_pDbOperater = Q_NULLPTR;

// bool DataBaseOperaterDemo::m_isConnect                    = false;

DataBaseOperaterDemo::DataBaseOperaterDemo(QObject *parent) : QObject(parent)
{}

// 连接数据库，参数已定死
bool DataBaseOperaterDemo::connectDataBase() {
  const QString hostName("106.15.55.49");
  const QString dbName("contactsoftware");
  const QString dbUserName("contactsoftware");
  const QString dbUserPwd("4YWcX87SEp6wRH6e");
  if (QSqlDatabase::contains(QSqlDatabase::defaultConnection))
  {
    this->m_db_connect = QSqlDatabase::database(QSqlDatabase::defaultConnection);
  }
  else
  {
    this->m_db_connect = QSqlDatabase::addDatabase("QMYSQL3");
  }
  this->m_db_connect.setHostName(hostName);
  this->m_db_connect.setDatabaseName(dbName);
  if (this->m_db_connect.open(dbUserName, dbUserPwd))
  {
    this->m_query = (QSqlQuery)this->m_db_connect;
    m_isConnect   = true;
  }
  return m_isConnect;
}

/*
 * @breif
 * @param
 * @return
 * @note
 */
QSqlQuery DataBaseOperaterDemo::queryInfoDemo(const QString &userId) {
  QString sqlStr(
    "SELECT \
      `user`.id,\
       user_grouping.grouping_id,\
       user_grouping_list.member_id\
     FROM `user`,user_grouping,user_grouping_list\
     WHERE `user`.id = user_grouping.user_id\
     AND user_grouping.grouping_id = user_grouping_list.grouping_id;");

  m_query.exec(sqlStr);

  return m_query;
}

QList<int>DataBaseOperaterDemo::getUserGroupingIdByUserId(int userId)
{
  QString sqlStr(
    "SELECT user_grouping.grouping_id\
              FROM user_grouping     \
              WHERE %1 = user_grouping.user_id\
              AND user_grouping.is_user = TRUE;");
  sqlStr = sqlStr.arg(QString::number(userId));

  m_query.exec(sqlStr);
  QList<int> GroupingIds;
  while (m_query.next()) {
    GroupingIds.append(m_query.value(0).toInt());
  }

  return GroupingIds;
}

QList<int>DataBaseOperaterDemo::getMemberOfUserGroupingId(int groupingId)
{
  QString sqlStr(
    "SELECT \
       user_grouping_list.member_id\
     FROM user_grouping_list\
     WHERE user_grouping_list.grouping_id = %1;");
  sqlStr = sqlStr.arg(QString::number(groupingId));

  m_query.exec(sqlStr);
  QList<int> memberIds;
  while (m_query.next()) {
    memberIds.append(m_query.value(0).toInt());
  }

  return memberIds;
}

QString DataBaseOperaterDemo::getNameByGroupingId(const QString &groupingId)
{
  QString sqlStr(
    "SELECT `name` FROM user_grouping\
     WHERE user_grouping.grouping_id = %1;");
  sqlStr = sqlStr.arg(groupingId);

  m_query.exec(sqlStr);
  QString groupingName;
  if (m_query.first()) {
    groupingName = m_query.value(0).toString();
  }
  return groupingName;
}

QString DataBaseOperaterDemo::getNameByUserId(const QString &userId)
{
  QString sqlStr(
    "SELECT `name` FROM `user`\
     WHERE `user`.id = %1;");
  sqlStr = sqlStr.arg(userId);

  m_query.exec(sqlStr);
  QString name;
  if (m_query.first()) {
    name = m_query.value(0).toString();
  }
  return name;
}

QList<int>DataBaseOperaterDemo::getGroupGroupingIdByUserId(int userId)
{
  QString sqlStr(
    "SELECT user_grouping.grouping_id\
              FROM user_grouping     \
              WHERE %1 = user_grouping.user_id\
              AND user_grouping.is_user = 0;");
  sqlStr = sqlStr.arg(userId);

  m_query.exec(sqlStr);
  QList<int> GroupingIds;
  while (m_query.next()) {
    GroupingIds.append(m_query.value(0).toInt());
  }

  return GroupingIds;
}

QList<int>DataBaseOperaterDemo::getGroupingIdsByUserId(int userId, ChatObjType type)
{
  QString sqlStr(
    "SELECT user_grouping.grouping_id\
              FROM user_grouping     \
              WHERE %2 = user_grouping.user_id\
              AND user_grouping.is_user = %1;");
  switch (type) {
    case ChatObjType::User: {
      sqlStr = sqlStr.arg(true);
      break;
    }
    case ChatObjType::Group: {
      sqlStr = sqlStr.arg(false);
      break;
    }
    default:
      break;
  }
  sqlStr = sqlStr.arg(userId);

  m_query.exec(sqlStr);
  QList<int> GroupingIds;
  while (m_query.next()) {
    GroupingIds.append(m_query.value(0).toInt());
  }

  return GroupingIds;
}

QList<int>DataBaseOperaterDemo::getMemberOfGroupGroupingByGroupId(int groupingId)
{
  QString sqlStr(
    "SELECT member_id \
     FROM group_grouping_list\
     WHERE group_grouping_list.grouping_id = %1");
  sqlStr = sqlStr.arg(groupingId);

  m_query.exec(sqlStr);
  QList<int> memberIds;
  while (m_query.next()) {
    memberIds.append(m_query.value(0).toInt());
  }

  return memberIds;
}

QList<int>DataBaseOperaterDemo::getMemberIdsOfGroupingByGroupId(int groupingId, ChatObjType type)
{
  QString sqlStr;
  switch (type) {
    case ChatObjType::User: {
      sqlStr = QString(
                 "SELECT user_grouping_list.member_id\
       FROM user_grouping_list\
       WHERE user_grouping_list.grouping_id = %1;");
      break;
    }
    case ChatObjType::Group: {
      sqlStr = QString(
                 "SELECT member_id \
       FROM group_grouping_list\
       WHERE group_grouping_list.grouping_id = %1");
      break;
    }
    default:

      break;
  }
  sqlStr = sqlStr.arg(QString::number(groupingId));

  m_query.exec(sqlStr);
  QList<int> memberIds;
  while (m_query.next()) {
    memberIds.append(m_query.value(0).toInt());
  }

  return memberIds;
}

QString DataBaseOperaterDemo::getNameByGroupId(int groupId)
{
  QString sqlStr(
    "SELECT `name` FROM `group`\
     WHERE `group`.id = %1;");
  sqlStr = sqlStr.arg(groupId);

  m_query.exec(sqlStr);
  QString name;
  if (m_query.first()) {
    name = m_query.value(0).toString();
  }
  return name;
}

QString DataBaseOperaterDemo::getNameByIdAndType(int groupId, ChatObjType type)
{
  QString sqlStr;
  switch (type) {
    case ChatObjType::User: {
      sqlStr = QString(
                 "SELECT `name` FROM `user`\
       WHERE `user`.id = %1;");
      break;
    }
    case ChatObjType::Group: {
      sqlStr = QString(
                 "SELECT `name` FROM `group`\
       WHERE `group`.id = %1;");
      break;
    }
    case ChatObjType::Grouping: {
      sqlStr = QString(
                 "SELECT `name` FROM `user_grouping`\
       WHERE `user_grouping`.grouping_id = %1;");
      break;
    }
    default: break;
  }
  sqlStr = sqlStr.arg(groupId);

  m_query.exec(sqlStr);
  QString name;
  if (m_query.first()) {
    name = m_query.value(0).toString();
  }
  return name;
}

QString DataBaseOperaterDemo::getAccountByIdAndType(int id, ChatObjType type)
{
  QString sqlStr;
  switch (type) {
    case ChatObjType::User: {
      sqlStr = QString(
                 "SELECT `account` FROM `user`\
       WHERE `user`.id = %1;");
      break;
    }
    case ChatObjType::Group: {
      sqlStr = QString(
                 "SELECT `account` FROM `group`\
       WHERE `group`.id = %1;");
      break;
    }
    default: break;
  }
  sqlStr = sqlStr.arg(id);
  m_query.exec(sqlStr);
  QString account;
  if (m_query.first()) {
    account = m_query.value(0).toString();
  }

  // 确保正确输出
  //  qDebug() << "account "
  //           << (type == ChatObjType::User ? "usr" : "group")
  //           << account;
  return account;
}

QIcon DataBaseOperaterDemo::getPhotoUrlByIdAndType(int id, ChatObjType type)
{
  QString sqlStr;
  switch (type) {
    case ChatObjType::User: {
      sqlStr = QString(
                 "SELECT `photo_url` FROM `user_grouping_list`\
       WHERE `user_grouping_list`.member_id = %1;");
      break;
    }
    case ChatObjType::Group: {
      sqlStr = QString(
                 "SELECT `photo_url` FROM `group_grouping_list`\
       WHERE `group_grouping_list`.member_id = %1;");
      break;
    }
    default: break;
  }
  sqlStr = sqlStr.arg(id);
  m_query.exec(sqlStr);
  QIcon icon;
  if (m_query.first()) {
    QString urlStr = m_query.value(0).toString();
    QUrl    qurl(urlStr);
    QPixmap pixmap;

    if (qurl.isValid()) {
      QNetworkAccessManager manager;
      QEventLoop loop;
      QNetworkReply *reply = manager.get(QNetworkRequest(qurl));
      connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
      loop.exec();
      QByteArray jpegData = reply->readAll();
      pixmap.loadFromData(jpegData);
      icon = QIcon(pixmap);
    } else {
      icon = QIcon(urlStr);
    }
  }
  return icon;
}

int DataBaseOperaterDemo::getUserIdByAccount(const QString &account)
{
  QString sqlStr(
    "SELECT `id` FROM `user`\
     WHERE `user`.account = %1;");
  sqlStr = sqlStr.arg(account);

  QSqlQuery m_query;
  m_query.exec(sqlStr);
  int id;
  if (m_query.first()) {
    id = m_query.value(0).toInt();
  }
  return id;
}

QString DataBaseOperaterDemo::getIpByAccount(const QString &account)
{
  QString sqlStr(
    "SELECT `ip` FROM `state`\
     WHERE `state`.account = %1;");
  sqlStr = sqlStr.arg(account);

  QSqlQuery m_query;
  m_query.exec(sqlStr);
  QString ip;
  if (m_query.first()) {
    ip = m_query.value(0).toString();
  }
  return ip;
}

QString DataBaseOperaterDemo::getUserNameByAccount(const QString &account)
{
  QString sqlStr(
    "SELECT `name` FROM `user`\
     WHERE `user`.account = %1;");
  sqlStr = sqlStr.arg(account);
  QSqlQuery m_query;
  m_query.exec(sqlStr);
  QString name;
  if (m_query.first()) {
    name = m_query.value(0).toString();
  }
  return name;
}

bool DataBaseOperaterDemo::isConnect()
{
  return m_isConnect;
}

DataBaseOperaterDemo *DataBaseOperaterDemo::getInstance()
{
  return s_pDbOperater;
}

void DataBaseOperaterDemo::buildInstance()
{
  s_pDbOperater = new DataBaseOperaterDemo();
}

void DataBaseOperaterDemo::destroyInstance()
{
  delete s_pDbOperater;
}

bool DataBaseOperaterDemo::isExist()
{
  bool exist = Q_NULLPTR != s_pDbOperater;
  return exist;
}

bool DataBaseOperaterDemo::getInstancePtr_s(DataBaseOperaterDemo *&pDbOperater)
{
  if (!DataBaseOperaterDemo::isExist()) {
    DataBaseOperaterDemo::buildInstance();
  }
  pDbOperater = DataBaseOperaterDemo::getInstance();
  if (pDbOperater->connectDataBase()) {
    return true;
  } else {
    return false;
  }
}
