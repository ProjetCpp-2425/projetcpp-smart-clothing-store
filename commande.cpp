#include "commande.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
commande::commande(int code_commande, int tel, QString description, QString ref, int quantite, int prix, QString id, int cin)
{
    this->code_commande = code_commande;
    this->tel = tel;
    this->description = description;
    this->ref = ref;
    this->quantite = quantite;
    this->prix= prix ;
    this->id = id;
    this->cin = cin;
}

QString commande::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO COMMANDE (CODE_COMMANDE, TEL, DESCRIPTION, REF, QUANTITE, PRIX, ID, CIN) "
                  "VALUES (:code_commande, :tel, :description, :ref, :quantite, :prix , :id, :cin)");
    query.bindValue(":code_commande",this->code_commande );
    query.bindValue(":tel", this->tel);
    query.bindValue(":description", this->description);
    query.bindValue(":ref", this->ref);
    query.bindValue(":quantite", this->quantite);
    query.bindValue(":prix", this->prix);
    query.bindValue(":id", this->id);
    query.bindValue(":cin", this->cin);

    if (!query.exec())
    {
        qDebug() << "Erreur d'ajout :" << query.lastError().text();
        return query.lastError().text();
    }
    else
    {
        return "true";
    }
}

bool commande::mise_a_jour()
{
    QSqlQuery query;
    query.prepare("UPDATE COMMANDE SET TEL = :tel, DESCRIPTION = :description, REF = :ref, QUANTITE = :quantite, PRIX = :prix, ID = :id, CIN = :cin WHERE CODE_COMMANDE = :code_commande");
    query.bindValue(":code_commande", code_commande);
    query.bindValue(":tel", tel);
    query.bindValue(":description", description);
    query.bindValue(":ref", ref);
    query.bindValue(":quantite", quantite);
    query.bindValue(":prix", prix);
    query.bindValue(":id", id);
    query.bindValue(":cin", cin);

    if (!query.exec())
    {
        qDebug() << "Erreur de modification :" << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

bool commande::supprimer(int code_commande)
{
    QSqlQuery query;
    query.prepare("DELETE FROM COMMANDE WHERE CODE_COMMANDE = :code_COMMANDE");
    query.bindValue(":code_COMMANDE", code_commande);

    if (!query.exec())
    {
        qDebug() << "Erreur de suppression :" << query.lastError().text();
        return false;
    }
    else
    {
        return true;
    }
}

QSqlQueryModel* commande::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM COMMANDE ORDER BY PRIX ASC");

    return model;
}

QMap<QString, int> commande::statistiquesdescription() {
    QMap<QString, int> result;

    // Crée une requête SQL pour obtenir les statistiques
    QSqlQuery query;
    query.prepare("SELECT description, COUNT(*) as count FROM COMMANDE GROUP BY description");

    if (query.exec()) {
        // Traite les résultats de la requête
        while (query.next()) {
            QString description = query.value(0).toString();  // La description
            int count = query.value(1).toInt();  // Le nombre d'occurrences
            result.insert(description, count);  // Ajoute à la map
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête statistiquesdescription:" << query.lastError();
    }

    return result;  // Retourne le résultat sous forme de QMap
}
float commande::calculerPrixTotal()
{
    float total = 0.0f;

    if (panier_articles.isEmpty()) {
        qDebug() << "Le panier est vide. Aucun total à calculer.";
        return total;  // Retourne 0 directement si le panier est vide
    }

    // Ajouter les prix des articles
    for (float prix : panier_prix) {
        if (prix >= 0) {  // Vérifie que chaque prix est valide (optionnel)
            total += prix;
        } else {
            qWarning() << "Attention : Un prix invalide détecté (" << prix << "). Ignoré.";
        }
    }

    qDebug() << "Prix total calculé : " << total;
    return total;
}


void commande::ajouterArticle(const QString& article, float prix)
{
    if (article.isEmpty() || prix <= 0) {
        qDebug() << "Erreur : Nom d'article vide ou prix invalide.";
        return;
    }

    panier_articles.append(article);  // Ajouter l'article à la liste des articles
    panier_prix.append(prix);         // Ajouter le prix à la liste des prix
    qDebug() << "Article ajouté :" << article << ", Prix :" << prix;
}

void commande::viderPanier()
{
    // Vider les listes des articles et des prix
    panier_articles.clear();
    panier_prix.clear();
    qDebug() << "Le panier a été vidé.";
}

QString commande::afficherPanier()
{
    QString panierText = "Articles dans le panier :\n";

    if (panier_articles.isEmpty()) {
        panierText += "Le panier est vide.";
    } else {
        for (int i = 0; i < panier_articles.size(); ++i) {
            panierText += QString::number(i + 1) + ". " + panier_articles[i] + " - " + QString::number(panier_prix[i]) + "DT\n";
        }
    }

    qDebug() << "Contenu du panier :\n" << panierText;
    return panierText;
}

void commande::supprimerArticleButton(const QString& article)
{
    if (article.isEmpty()) {
        qDebug() << "Erreur : Nom d'article vide. Impossible de supprimer.";
        return;
    }

    int index = panier_articles.indexOf(article);  // Trouver l'indice de l'article à supprimer
    if (index != -1) {
        panier_articles.removeAt(index);  // Supprimer l'article de la liste
        panier_prix.removeAt(index);      // Supprimer le prix correspondant
        qDebug() << "Article supprimé :" << article;
    } else {
        qDebug() << "Article non trouvé dans le panier :" << article;
    }
}
