#include "connection.h"
#include <QSqlError>
#include <QDebug>

Connection& Connection::getInstance() {
    static Connection instance;
    return instance;
}

Connection::Connection() {}

Connection::~Connection() {
    closeConnection();
}

bool Connection::createConnect() {
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("myuser");
    db.setPassword("12345");

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return false;
    }
    return true;
}

void Connection::closeConnection() {
    if (db.isOpen()) {
        db.close();
    }
}

