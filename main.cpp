#include "mainwindow1.h"
#include <QApplication>
#include <QMessageBox>
#include<QDebug>
#include "conection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Conection c; //une seule instance de la classe connection

    bool test=c.createconnect();//Etablir la onnexion
    MainWindow1 w;
    if (test) //Si la connexion est etablie
    {
    w.show();

    QMessageBox::information(nullptr, QObject::tr("database is open"),
    QObject::tr("connection successful . \n"
                "Click Cancel to exist."), QMessageBox::Cancel);
    }else //si la connexion a echoue
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}
