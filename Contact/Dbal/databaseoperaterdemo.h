#ifndef DATABASEOPERATERDEMO_H
#define DATABASEOPERATERDEMO_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QUrl>
enum class ChatObjType
{
  Group    = 0,
  User     = 1,
  Grouping = 2
};

class DataBaseOperaterDemo : public QObject {
  Q_OBJECT

public:

  bool      connectDataBase();
  QSqlQuery queryInfoDemo(const QString& userId);

  QList<int>getUserGroupingIdByUserId(int userId);
  QList<int>getGroupGroupingIdByUserId(int userId);
  QList<int>getGroupingIdsByUserId(int         userId,
                                   ChatObjType type);

  QList<int>getMemberOfUserGroupingId(int groupingId);
  QList<int>getMemberOfGroupGroupingByGroupId(int groupingId);
  QList<int>getMemberIdsOfGroupingByGroupId(int         groupingId,
                                            ChatObjType type);

  QString   getNameByGroupingId(const QString& groupingId);
  QString   getNameByUserId(const QString& userId);
  QString   getNameByGroupId(int groupId);
  QString   getNameByIdAndType(int         groupId,
                               ChatObjType type);

  QString   getAccountByIdAndType(int         id,
                                  ChatObjType type);

  QIcon     getPhotoUrlByIdAndType(int         id,
                                   ChatObjType type);

  // 用account 兼容旧的内容
  int     getUserIdByAccount(const QString& account);
  QString getIpByAccount(const QString& account);
  QString getUserNameByAccount(const QString& account);

  //
  //
  bool                         isConnect();
  static DataBaseOperaterDemo* getInstance();
  static void                  buildInstance();
  static void                  destroyInstance();
  static bool                  isExist();
  static bool                  getInstancePtr_s(DataBaseOperaterDemo *&);

protected:

  explicit  DataBaseOperaterDemo(QObject *parent = nullptr);

signals:

private:

  static DataBaseOperaterDemo *s_pDbOperater;
  bool m_isConnect = false;
  QSqlDatabase m_db_connect;
  QSqlQuery m_query;
};

#endif // DATABASEOPERATERDEMO_H
