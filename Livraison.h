#ifndef LIVRAISON_H
#define LIVRAISON_H
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


    class Livraison
    {


    public:
        Livraison();
   /*     Livraison(const Livraison &);
        Livraison &operator=(const Livraison &);
        ~Livraison();*/
        Livraison(int,QString,QString,QString , int , int);

          //getters
        QString getim(){return im;}
        QString getcarb(){return carb;}
        QString getcarteG(){return carteG;}

        int getid(){return id;}
        int getpoids(){return poids;}
        int getassurance(){return assurance;}

        // setters
        void setimmat(QString im){this->im=im;}
        void seticarb(QString carb){ this->carb=carb;}
        void seticarteG(QString carteG){this->carteG=carteG;}

        void setpoids(int poids){this->poids=poids;}
        void setid(int id) {this->id=id;}
        void setassurance(int assurance){this->assurance=assurance;}
        // Fonctionnalites de Base relatives a l'entite Etudiant
        bool ajouter(const QString &card);
        QSqlQueryModel* afficher()const;
        bool supprimer(int);
        bool modifier(int);
        QSqlQueryModel *rechercher(int);
        QSqlQueryModel* tri();
        void exporterPDF(const QString &nomFichier) const;
        QSqlQueryModel* historique() const;
        void exporterHistoriqueTexte(const QString &nomFichier) const;
        QString statistiquesParcarburant();
        int getNombrevehiculeParcarteG(const QString &carteG);
        bool vehiculeExists();

    private:
        QString im, carb, carteG;
        int assurance, id , poids;


};

#endif // LIVRAISON_H
