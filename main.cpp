/*#include "MainEmploye.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainEmploye w;
    Connection c;
    bool test=c.createconnect();
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}*/
#include "login.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Establish database connection
    Connection c;
    bool test = c.createconnect();

    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Database Connection"),
                                 QObject::tr("Connection successful.\n"
                                             "Click OK to proceed."), QMessageBox::Ok);

        // Show the login window
        Login loginWindow;
        loginWindow.setWindowTitle("Login");
        loginWindow.show();

        return a.exec();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Connection"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return -1; // Exit with failure code if the database connection fails
    }
}

