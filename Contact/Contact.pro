#-------------------------------------------------
#
# Project created by QtCreator 2022-03-15T15:09:15
#
#-------------------------------------------------

QT       += core gui

QT +=   sql
QT +=    network
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
TARGET = Contact
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
include(Gui/Gui.pri)         #界面层
include(Service/Service.pri) #业务逻辑层
include(Dbal/Dbal.pri)       #数据访问层-数据库访问层
include(Entity/Entity.pri)   #实体包
include(Utils/Utils.pri)     #工具包
include(Args/Args.pri)       #重要参数
SOURCES += \
        main.cpp

HEADERS +=


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../3rd_smtpclient
include ($$PWD/3rd_smtpclient/3rd_smtpclient.pri)
