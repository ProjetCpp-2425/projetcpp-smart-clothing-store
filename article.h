#ifndef ARTICLE_H
#define ARTICLE_H

#include <QSqlQueryModel>
#include <QString>

class Article
{
private:
    int code_article;
    QString titre;
    QString description;
    QString type;
    int quantite;
    int prix;
    QString image;
    int cin;

public:
    Article() {}
    Article(int, QString, QString, QString, int, int, QString,int );

    int getCodeArticle() const { return code_article; }
    QString getTitre() const { return titre; }
    QString getDescription() const { return description; }
    QString getType() const { return type; }
    int getQuantite() const { return quantite; }
    float getPrix() const { return prix; }
    QString getImage() const { return image; }
    int getCIN() const { return cin; }


    void setCodeArticle(int code) { code_article = code; }
    void setTitre(QString t) { titre = t; }
    void setDescription(QString desc) { description = desc; }
    void setType(QString ty) { type = ty; }
    void setQuantite(int q) { quantite = q; }
    void setPrix(float p) { prix = p; }
    void setImage(QString img) { image = img; }
    void setCIN(int c) {  cin = c; }


    QSqlQueryModel* afficher();
    QString ajouter();
    bool mettre_ajour();
    bool supprimer(int);
};

#endif // ARTICLE_H




