#include "fournisseur.h"
#include "connection.h"
#include <QSqlError>
#include <QDebug>
#include <iostream>

Fournisseur::Fournisseur() {}

bool Fournisseur::addFournisseur(int id, const QString &name, const QString &telephone, const QString &email, const QDate &achatDate) {
    QSqlQuery query;
    query.prepare("INSERT INTO fournisseurs (id, name, telephone, email, achat_date) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(id);
    query.addBindValue(name);
    query.addBindValue(telephone);
    query.addBindValue(email);
    query.addBindValue(achatDate);

    if (!query.exec()) {
        qDebug() << "Error adding fournisseur:" << query.lastError().text();
        qDebug() << "Executed query:" << query.executedQuery();
        qDebug() << "ID:" << id;
        qDebug() << "Name:" << name;
        qDebug() << "Telephone:" << telephone;
        qDebug() << "Email:" << email;
        qDebug() << "Achat Date:" << achatDate.toString("yyyy-MM-dd");
        return false;
    }
    return true;
}

bool Fournisseur::updateFournisseur(int id, const QString &name, const QString &telephone, const QString &email, const QDate &achatDate) {
    QSqlQuery query;
    query.prepare("UPDATE fournisseurs SET name = ?, telephone = ?, email = ?, achat_date = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(telephone);
    query.addBindValue(email);
    query.addBindValue(achatDate);
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Error updating fournisseur:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Fournisseur::deleteFournisseur(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM fournisseurs WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Error deleting fournisseur:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Fournisseur::getFournisseurs() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM fournisseurs");

    if (!query.exec()) {
        qDebug() << "Error retrieving fournisseurs:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    return model;
}

QSqlQueryModel* Fournisseur::filterByDate(const QDate& date) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM fournisseurs WHERE achat_date = :date");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Error filtering fournisseurs by date: " << query.lastError();
    }
    return model;
}
