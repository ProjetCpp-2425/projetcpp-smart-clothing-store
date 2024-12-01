#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("CPP_Project"); // Inserting the name of the data source
    db.setUserName("Bogh");            // Inserting username
    db.setPassword("0000");            // Inserting password for the user

    if (db.open()) {
        // Set the NLS_DATE_FORMAT to 'YYYY-MM-DD' to ensure the date format
        QSqlQuery query;
        query.exec("ALTER SESSION SET NLS_DATE_FORMAT = 'YYYY-MM-DD'");

        test = true;
    }

    return test;
}
