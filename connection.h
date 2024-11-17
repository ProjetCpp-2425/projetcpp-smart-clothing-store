#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection
{
public:
    static Connection& getInstance();
    bool createConnect();
    void closeConnection();

private:
    Connection();
    ~Connection();
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    QSqlDatabase db;
};

#endif // CONNECTION_H


