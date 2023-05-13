QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG += qaxcontainer

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = QtExcel
TEMPLATE = app

SOURCES += \
    about.cpp \
    cashier.cpp \
    doctor.cpp \
    main.cpp \
    mainwindow.cpp \
    manual.cpp \
    med_center.cpp \
    security.cpp \
    worker.cpp

HEADERS += \
    about.h \
    cashier.h \
    doctor.h \
    mainwindow.h \
    manual.h \
    med_center.h \
    security.h \
    worker.h

FORMS += \
    about.ui \
    mainwindow.ui \
    manual.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
