HEADERS += \
    $$PWD/globalobserver.h \
    $$PWD/sendfile.h\
    $$PWD/robotchat.h\
    $$PWD/sendemailthread.h
SOURCES += \
    $$PWD/globalobserver.cpp \
    $$PWD/sendfile.cpp\
    $$PWD/robotchat.cpp\
    $$PWD/sendemailthread.cpp
include(UdpVoiceCallNet/UdpVoiceCallNet.pri)       #重要参数
