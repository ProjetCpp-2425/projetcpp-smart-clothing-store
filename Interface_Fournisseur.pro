QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += widgets sql printsupport
QT += core gui network

TARGET = Atelier_Connexion
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
CONFIG += console

SOURCES += \
    chatbotwindow.cpp \
    mailwindow.cpp \
    mailwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow.cpp \
    mainwindow.cpp \
    connection.cpp \
    fournisseur.cpp

HEADERS += \
    chatbotwindow.h \
    mailwindow.h \
    mailwindow.h \
    mainwindow.h \
    mainwindow.h \
    mainwindow.h \
    connection.h \
    fournisseur.h

FORMS += chatbotwindow.ui \
         mailwindow.ui \
         mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
