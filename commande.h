#ifndef COMMANDE_H
#define COMMANDE_H

#include <QSqlQueryModel>
#include <QString>
#include "qsqlquerymodel.h"
#include <QString>
#include <QDate>
#include <QList>
#include <QMap>


class commande
{
private:
    int code_commande;
    int tel;
    QString description;
    QString ref;
    int quantite;
    int prix;
    QString id;
    int cin;
    QList<QString> panier_articles; // Liste des noms d'articles
        QList<float> panier_prix;

public:
    commande() {}
    commande(int, int, QString, QString, int, int, QString,int );

    int getCodecommande() const { return code_commande; }
    int getTel() const { return tel; }
    QString getDescription() const { return description; }
    QString getref() const { return ref; }
    int getQuantite() const { return quantite; }
    int  getPrix() const { return prix; }
    QString getId() const { return id; }
    int getCIN() const { return cin; }
    QSqlQueryModel* afficher();
    bool supprimer(int code_commande);



    void setCodecommande(int code) { code_commande = code; }
    void setTel(int t) { tel = t; }
    void setDescription(QString desc) { description = desc; }
    void setref(QString re) { ref = re; }
    void setQuantite(int q) { quantite = q; }
    void setPrix(float p) { prix = p; }
    void setId(QString ide) { id = ide; }
    void setCIN(int c) {  cin = c; }
    void ajouterArticle(const QString& article, float prix);  // Ajouter un article
    void viderPanier();  // Vider le panier
    void supprimerArticleButton(const QString& article);  // Supprimer un article par son nom
    float calculerPrixTotal();

    QString ajouter();
    bool mise_a_jour();
    /*bool supprimer(int);*/
    QMap<QString, int> statistiquesdescription();
    int getPanierArticles();
    QList<QString> getPanierArticles() const { return panier_articles; }
    QString afficherPanier();  // Afficher le contenu du panier

};

#endif // COMMANDE_H




