#-------------------------------------------------
#
# Project created by QtCreator 2017-07-04T10:26:35
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 409client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += precompile_header
PRECOMPILED_HEADER += order_define.h

SOURCES += \
        main.cpp        \
        mainwindow.cpp  \
        download.cpp    \
        sing_in.cpp     \
        find_dialog.cpp \
    tabnamedialog.cpp \
    myclient.cpp \
    creatdb.cpp

HEADERS += \
        mainwindow.h    \
        download.h      \
        sing_in.h       \
        find_dialog.h \
        order_define.h \
    myclient.h \
    tabnamedialog.h \
    creatdb.h

FORMS += \
        mainwindow.ui   \
        download.ui     \
        sing_in.ui      \
        find_dialog.ui \
    tabnamedialog.ui \
    creatdb.ui

RESOURCES += \
        resource.qrc

LIBS     += -lws2_32
