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
    convertisseurwindow.cpp \
    fournisseurprofilewindow.cpp \
    loginwindow.cpp \
    mailwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    connection.cpp \
    fournisseur.cpp

HEADERS += \
    chatbotwindow.h \
    convertisseurwindow.h \
    fournisseurprofilewindow.h \
    loginwindow.h \
    mailwindow.h \
    mainwindow.h \
    connection.h \
    fournisseur.h

FORMS += chatbotwindow.ui \
         convertisseurwindow.ui \
         fournisseurprofilewindow.ui \
         loginwindow.ui \
         mailwindow.ui \
         mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
