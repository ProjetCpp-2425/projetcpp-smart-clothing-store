#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Fournisseur {
public:
    Fournisseur();
    bool addFournisseur(int id, const QString &name, const QString &telephone, const QString &email, const QDate &achatDate);
    bool updateFournisseur(int id, const QString &name, const QString &telephone, const QString &email, const QDate &achatDate);
    bool deleteFournisseur(int id);
    QSqlQueryModel* getFournisseurs();

private:
    QString name;
    QString telephone;
    QString email;
    QDate achatDate;
};

#endif // FOURNISSEUR_H
