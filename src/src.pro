CONFIG+=qt

QT+=core gui widgets serialport

TEMPLATE = app
TARGET = QtMarlin
DEPENDPATH += $$PWD $
INCLUDEPATH += $$PWD  

MOC_DIR      = moc
RCC_DIR      = resources
OBJECTS_DIR       = obj

message ( $$OUT_PWD )


DEPENDPATH += $$PWD 
INCLUDEPATH += $$PWD $$PWD/../libs/qwt-6.2/src

LIBS+=$$OUT_PWD/../libs/qwt-6.2/lib/libqwt.a

HEADERS += $$PWD/mainwindow.h \
           $$PWD/tab_pid.h \
           $$PWD/tab_raw.h \
           $$PWD/tab_eeprom.h \
           $$PWD/tab_veltest.h

SOURCES += $$PWD/main.cpp \
           $$PWD/mainwindow.cpp \
           $$PWD/tab_pid.cpp  \
           $$PWD/tab_raw.cpp \
           $$PWD/tab_eeprom.cpp \
           $$PWD/tab_veltest.cpp
