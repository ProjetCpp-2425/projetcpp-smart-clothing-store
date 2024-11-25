#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    //QSqlDatabase db = c.createconnect(); // Appeler la méthode createconnect() pour obtenir la base de données
    bool test=c.createconnection();

    // Vérifier si la connexion a réussi
    MainWindow w;
    if (test) {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database Connection"),
                                 QObject::tr("Connection successful."),
                                 QMessageBox::Ok);

    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Connection"),
                              QObject::tr("Connection failed."),
                              QMessageBox::Ok);
    }
     return a.exec();

}
