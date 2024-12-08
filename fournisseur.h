#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Fournisseur {
public:
    Fournisseur();
    bool addFournisseur(int id, const QString &name, const QString &telephone, const QString &email, const QDate &achatDate, const QString &logo, double prixAchat);
    bool updateFournisseur(int id, const QString &name, const QString &telephone, const QString &email, const QDate &achatDate, const QString &logo, double prixAchat);
    bool deleteFournisseur(int id);
    QSqlQueryModel* getFournisseurs();

private:
    QString name;
    QString telephone;
    QString email;
    QDate achatDate;
    QString logo;
    double prixAchat;
};

#endif // FOURNISSEUR_H
