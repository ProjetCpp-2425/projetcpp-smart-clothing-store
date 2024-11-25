#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection
{
    QSqlDatabase db;
public:
    Connection();
    bool createconnection(); // Modifier la signature de la méthode
    void closeConnection();
};

#endif // CONNECTION_H
