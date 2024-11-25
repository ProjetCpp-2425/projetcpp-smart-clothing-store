#include "connection.h"
#include <QDebug>
Connection::Connection(){}

bool Connection::createconnection() // Modifier la définition de la méthode
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    //db.setHostName("localhost");
    //db.setPort(1521);
    db.setDatabaseName("2a30source");
    db.setUserName("projetcpp2a30"); // Insérer nom de l'utilisateur
    db.setPassword("esprit24"); // Insérer mot de passe de cet utilisateur

    if (db.open()) test=true;
    return test;
}


void Connection::closeConnection(){db.close();}
