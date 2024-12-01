#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QSqlQueryModel>
#include <QString>

class Employe
{

public:
    Employe();
    Employe(QString nom, QString prenom, QString id, QString dateNaissance, QString genre, QString numeroTel, QString adresse, QString poste, QString salaire, QString dateEmbauche);

    bool ajouter(); // Function to add employee to the database
    bool modifier(); // Function to modify employee details in the database
    bool supprimer(QString id); // Function to delete an employee by ID
    QSqlQueryModel* afficher(); // Function to display all employees
    QSqlQueryModel* chercher(QString searchText); // Function to search employees by ID or name
    QSqlQueryModel* tri(QString sortBy, bool ascending);

    void sendSMSNotification(const QString &phoneNumber);

private:
    QString nom;
    QString prenom;
    QString id;
    QString dateNaissance;
    QString genre;
    QString numeroTel;
    QString adresse;
    QString poste;
    QString salaire;
    QString dateEmbauche;
};

#endif // EMPLOYE_H
