#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <string>
#include <QHash>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QDate>
#include <QObject>

class Client
{

public:
    //constructeurs
    Client();
    Client(int id, QString nom_p, int numero, QString mail, QString date_,QString genre);
    //Getters and setters
           int Getid() { return id; }
           void Setid(int val) { id = val; }
           int Getnumero() { return numero; }
           void Setnumero(int val) { numero = val; }
           QString Getnom_p() { return nom_p; }
           void Setnom_p(QString val) { nom_p = val; }
           QString Getmail() { return mail; }
           void Setmail(QString val) { mail = val; }
           QString Getdate() { return date_; }
           void Setdate(QString val) { date_ = val; }
           QString Getgenre() { return genre; }
           void Setgenre(QString val) { genre = val; }

      //fonctionnalite de base relatives a l'entite Client
       bool ajouter();
       QSqlQueryModel * afficher()const;
       bool supprimer(int);
       bool modifier(int);
       QSqlQueryModel *rechercher(int);
       QSqlQueryModel* tri();
       void exporterPDF(const QString &nomFichier) const;
       std::string chatbotFunction(const QString &userMessage);
       QSqlQueryModel* historique() const;
       void exporterHistoriqueTexte(const QString &nomFichier) const;
       QString statistiquesParGenre();
       int getNombreClientsParGenre(const QString &mail);
       bool ClientExists();


private:
    int id,numero;
    QString nom_p;
    QString mail;
    QString date_;
    QString genre;
};

#endif // CLIENT_H
