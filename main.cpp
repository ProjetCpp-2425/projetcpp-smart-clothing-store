#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>
#include "connection.h"
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Connection &conn = Connection::getInstance();
    if (!conn.createConnect()) {
        QMessageBox::critical(nullptr, "Database Connection Error", "Failed to connect to the database. Exiting.");
        return -1;
    }

    LoginWindow loginWindow;
    if (loginWindow.exec() == QDialog::Accepted) {
        MainWindow mainWindow;
        mainWindow.show();
        return app.exec();
    }

    return 0;
}
