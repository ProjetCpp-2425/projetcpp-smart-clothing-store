#include "conection.h"

Conection::Conection(){}

bool Conection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("SmartStore");
db.setUserName("projetcpp2a30");//inserer nom de l'utilisateur
db.setPassword("esprit24");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;

return  test;
}
void Conection::closeconnect(){ db.close(); }
