#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

Employe::Employe() {}

Employe::Employe(QString nom, QString prenom, QString id, QString dateNaissance, QString genre, QString numeroTel, QString adresse, QString poste, QString salaire, QString dateEmbauche)
    : nom(nom), prenom(prenom), id(id), dateNaissance(dateNaissance), genre(genre), numeroTel(numeroTel), adresse(adresse), poste(poste), salaire(salaire), dateEmbauche(dateEmbauche) {}

/*bool Employe::ajouter()
{
    QSqlQuery query;

    // Check if ID already exists
    query.prepare("SELECT id FROM employe WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        qDebug() << "Error: ID already exists.";
        return false; // ID is already used
    }

    // Insert employee into the database
    query.prepare("INSERT INTO employe (nom, prenom, id, dateNaissance, genre, numeroTel, adresse, poste, salaire, dateEmbauche) "
                  "VALUES (:nom, :prenom, :id, :dateNaissance, :genre, :numeroTel, :adresse, :poste, :salaire, :dateEmbauche)");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":id", id);
    query.bindValue(":dateNaissance", dateNaissance);
    query.bindValue(":genre", genre);
    query.bindValue(":numeroTel", numeroTel);
    query.bindValue(":adresse", adresse);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":dateEmbauche", dateEmbauche);

    if (query.exec()) {
        qDebug() << "Employee added successfully!";
        return true;
    } else {
        qDebug() << "Failed to add employee:" << query.lastError();
        return false;
    }
}*/

bool Employe::ajouter()
{
    QSqlQuery query;

    // Step 1: Check if ID already exists
    query.prepare("SELECT id FROM employe WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) { // ID already exists
        QMessageBox::critical(nullptr, "Error", "ID already exists. Please use a unique ID.");
        return false;
    }

    // Step 2: Validate the genre
    if (genre != "F" && genre != "f" && genre != "M" && genre != "m") {
        QMessageBox::critical(nullptr, "Error", "Invalid genre. Please use 'F' for female or 'M' for male.");
        return false;
    }

    // Step 3: Validate the phone number
    if (!numeroTel.contains(QRegularExpression("^[0-9]+$"))) {
        QMessageBox::critical(nullptr, "Error", "Phone number must contain only digits.");
        return false;
    }

    // Step 4: Insert employee into the database
    query.prepare("INSERT INTO employe (nom, prenom, id, dateNaissance, genre, numeroTel, adresse, poste, salaire, dateEmbauche) "
                  "VALUES (:nom, :prenom, :id, :dateNaissance, :genre, :numeroTel, :adresse, :poste, :salaire, :dateEmbauche)");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":id", id);
    query.bindValue(":dateNaissance", dateNaissance);
    query.bindValue(":genre", genre);
    query.bindValue(":numeroTel", numeroTel);
    query.bindValue(":adresse", adresse);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":dateEmbauche", dateEmbauche);

    if (query.exec()) {
        return true; // Return success, but don't show any message here
    } else {
        QMessageBox::critical(nullptr, "Error", "Failed to add employee: " + query.lastError().text());
        return false;
    }
}


bool Employe::modifier()
{
    QSqlQuery query;

    // Check if ID exists
    query.prepare("SELECT id FROM employe WHERE id = :id");
    query.bindValue(":id", id);
    if (!(query.exec() && query.next())) {
        qDebug() << "Error: Employee with this ID does not exist.";
        return false; // ID not found
    }

    // Update employee details based on the ID
    query.prepare("UPDATE employe SET nom = :nom, prenom = :prenom, dateNaissance = :dateNaissance, genre = :genre, "
                  "numeroTel = :numeroTel, adresse = :adresse, poste = :poste, salaire = :salaire, dateEmbauche = :dateEmbauche "
                  "WHERE id = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":dateNaissance", dateNaissance);
    query.bindValue(":genre", genre);
    query.bindValue(":numeroTel", numeroTel);
    query.bindValue(":adresse", adresse);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire);
    query.bindValue(":dateEmbauche", dateEmbauche);
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Employee details updated successfully!";
        return true;
    } else {
        qDebug() << "Failed to update employee:" << query.lastError();
        return false;
    }
}

bool Employe::supprimer(QString id)
{
    QSqlQuery query;

    // Check if the ID exists
    query.prepare("SELECT id FROM employe WHERE id = :id");
    query.bindValue(":id", id);
    if (!(query.exec() && query.next())) {
        qDebug() << "Error: Employee with this ID does not exist.";
        return false; // ID not found
    }

    // Delete the employee record
    query.prepare("DELETE FROM employe WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Employee deleted successfully!";
        return true;
    } else {
        qDebug() << "Failed to delete employee:" << query.lastError();
        return false;
    }
}

/*QSqlQueryModel* Employe::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT id, nom, prenom, dateNaissance, genre, numeroTel, adresse, poste, salaire, dateEmbauche FROM employe");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Numéro de Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Date d'Embauche"));

    return model; // Returns the model to be displayed in the UI
}*/

QSqlQueryModel* Employe::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Updated query to format ID, Date Naissance, and Date Embauche
    model->setQuery("SELECT TO_CHAR(id) AS id, nom, prenom, "
                    "TO_CHAR(dateNaissance, 'DD-MM-YYYY') AS dateNaissance, genre, "
                    "numeroTel, adresse, poste, TO_NUMBER(salaire) AS salaire, "
                    "TO_CHAR(dateEmbauche, 'DD-MM-YYYY') AS dateEmbauche "
                    "FROM BOGH.EMPLOYE");


    // Format the ID field
    for (int row = 0; row < model->rowCount(); ++row) {
        // Get the 'id' value, convert it to string and set it back
        QString idString = QString::number(model->data(model->index(row, 0)).toInt());
        model->setData(model->index(row, 0), idString); // Update the model with the formatted ID
    }

    // Set the headers for the columns
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Numéro de Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Date d'Embauche"));

    return model; // Return the model to be displayed in the UI
}


QSqlQueryModel* Employe::chercher(QString searchText) {
    QSqlQueryModel *model = new QSqlQueryModel();

    bool isNumber = false;
    int id = searchText.toInt(&isNumber);  // Try to convert the search text to an integer

    QString queryStr;

    if (isNumber) {
        // Search by ID (numeric search)
        queryStr = "SELECT * FROM employe WHERE id = :id";
    } else {
        // Search by name (partial match with LIKE)
        queryStr = "SELECT * FROM employe WHERE nom LIKE :nom";
    }

    QSqlQuery query;
    query.prepare(queryStr);

    if (isNumber) {
        query.bindValue(":id", id);  // Pass the ID as an integer if it's numeric
    } else {
        query.bindValue(":nom", "%" + searchText + "%");  // Use LIKE for name search
    }

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Query failed: " << query.lastError();
        return model;  // Return an empty model if the query fails
    }

    model->setQuery(std::move(query));  // Set the query to the model
    return model;
}


// In Employe class (employe.cpp)
QSqlQueryModel* Employe::tri(QString sortBy, bool ascending) {
    QSqlQueryModel *model = new QSqlQueryModel;

    // Start the query to get all employees
    QString queryStr = "SELECT * FROM EMPLOYE";

    // Determine which column to sort by
    if (sortBy == "SALAIRE") {
        queryStr += " ORDER BY salaire";  // Column for salary
    } else if (sortBy == "DATEEMBAUCHE") {
        queryStr += " ORDER BY dateEmbauche";  // Column for hire date
    }

    // Add ascending or descending order based on the radio button
    queryStr += ascending ? " ASC" : " DESC";

    // Prepare and execute the query
    QSqlQuery query;
    query.prepare(queryStr);

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        return nullptr;  // Return nullptr in case of error
    }

    // Set the query to the model
     model->setQuery(std::move(query));
    return model;
}

void Employe::sendSMSNotification(const QString &phoneNumber) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.sendinblue.com/v3/transactionalSMS/sms"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("api-key","to add later");

    QJsonObject smsData;
    smsData["sender"] = "Structura";
    smsData["recipient"] = phoneNumber;
    smsData["content"] = "Hello from StructuraSys! Your data has been successfully exported as a PDF file. Thank you for using our service!";

    QNetworkReply *reply = manager->post(request, QJsonDocument(smsData).toJson());
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error()) {
            QMessageBox::critical(nullptr, "SMS Error", "Failed to send SMS: " + reply->errorString());
        } else {
            QMessageBox::information(nullptr, "Success", "SMS sent successfully.");
        }
        reply->deleteLater();
    });
}



