#include "Livraison.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QFile>
#include<QString>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <algorithm>
#include <QMap>
#include <QHash>

#include <QGraphicsProxyWidget>
#include <QGraphicsScene>



#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QPainter>
#include <QColor>
#include <QObject>

Livraison::Livraison()
{
    id=0;
    im="";
    poids=0;
    carb="";
    carteG="";
    assurance=0;
}
Livraison::Livraison( int id, QString im, QString carb, QString carteG, int poids, int assurance)
{
this->id=id;
this->poids=poids;
this->assurance=assurance;
this->carb=carb;
this->carteG=carteG;
this->im=im;
}
bool Livraison::ajouter(const QString &card)
{
    // Vérifier si le numéro de vehicule existe déjà
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM Livraison WHERE id = :id");
    checkQuery.bindValue(":id", id);
    checkQuery.exec();

    if (checkQuery.next()) {
        // Le numéro de vehicule existe déjà, l'ajout ne peut pas être effectué
        return false;
    } else {
        // Le numéro de livraison n'existe pas, procpoidséder à l'ajout
        QString id_string = QString::number(id);
        QString poids_string = QString::number(poids);
        QString assurance_string = QString::number(assurance);

        QSqlQuery query;
        query.prepare("INSERT INTO LIVRAISON (ID, IMMATRICULATION, CARBURANT, CARTE_GRISE, POIDS, NUM_ASSURANCE, IDCARD) "
                      "VALUES (:id, :im, :carb, :carteG, :poids, :assurance, :idcard)");
        query.bindValue(":id", id_string);
        query.bindValue(":im", im);
        query.bindValue(":carb", carb);
        query.bindValue(":carteG", carteG);
        query.bindValue(":poids", poids_string);
        query.bindValue(":assurance", assurance_string);
        query.bindValue(":idcard", card); // Add the card value



        return query.exec();
    }
}

QSqlQueryModel * Livraison::afficher()const
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM LIVRAISON");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("immatriculation"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("carb"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("carteG"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("poids"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("assurance"));
    return model;

}

bool Livraison::supprimer(int id)
{
    // Vérifier si le numéro de vehicule existe avant de le supprimer
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM Livraison WHERE id = :id");
    checkQuery.bindValue(":id", id);
    checkQuery.exec();

    if (!checkQuery.next()) {
        // Le numéro de vehicule n'existe pas, la suppression ne peut pas être effectuée
        return false;
    }

    // Procéder à la suppression
    QSqlQuery query;
    query.prepare("DELETE FROM Livraison WHERE id=:id");
    query.bindValue(":id", id);

    return query.exec();
}

bool Livraison::modifier(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString res2= QString::number(assurance);
    QString res3= QString::number(poids);

    query.prepare("update Livraison set id=:id,poids=:poids,immatriculation=:im,carburant=:carb,carte_grise=:carteG,num_assurance=:assurance  WHERE id = :id");
    query.bindValue(":id",res);
    query.bindValue(":assurance",res2);
    query.bindValue(":poids",res3);
    query.bindValue(":im",im);
    query.bindValue(":carb",carb);
    query.bindValue(":carteG",carteG);

    return query.exec();
}
QSqlQueryModel * Livraison::rechercher(int id)
{
    QSqlQuery query;
    QString id_str = QString::number(id);


    QString queryStr = "SELECT * FROM Livraison WHERE 1=1";

    if (id > 0) {
        queryStr += " AND id = :id";
    }

    query.prepare(queryStr);

    if (id > 0) {
        query.bindValue(":id", id_str);
    }


    query.exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(std::move(query));
    return model;
}
QSqlQueryModel * Livraison::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from LIVRAISON order by poids");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("immat"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("carb"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("carteG"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("poids"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("assurance"));
    return model;
}
void Livraison::exporterPDF(const QString &nomFichier) const
{
    QFile file(nomFichier);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QPdfWriter pdfWriter(&file);
        pdfWriter.setPageSize(QPageSize(QPageSize::A4));
        QPainter painter(&pdfWriter);

        painter.drawText(100, 100, "Liste des vehicule");

        painter.drawText(100, 150, "id");
        painter.drawText(200, 150, "im");
        painter.drawText(300, 150, "carbe");
        painter.drawText(500, 150, "carteG");
        painter.drawText(600, 150, "poids");
        painter.drawText(700, 150, "assurance");


        QSqlQueryModel *model = afficher();

        for (int row = 0; row < model->rowCount(); ++row)
        {
            for (int col = 0; col < model->columnCount(); ++col)
            {
                QString data = model->data(model->index(row, col)).toString();
                painter.drawText(100 + col * 100, 200 + row * 50, data);
            }
        }

        file.close();
    }
    else {
        qDebug() << "Erreur lors de l'ouverture du fichier : " << file.errorString();
    }
}

QSqlQueryModel* Livraison::historique() const
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM Livraison ");
    if (query.exec()) {
     model->setQuery(std::move(query));    }
    return model;
}
void Livraison::exporterHistoriqueTexte(const QString &nomFichier) const
{
    QFile file(nomFichier);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "Liste des Livraison\n\n";

        QSqlQueryModel *model = historique();

        for (int row = 0; row < model->rowCount(); ++row)
        {
            stream << "im: " << model->data(model->index(row, 2)).toString() << "\t";
            stream << "id: " << model->data(model->index(row, 1)).toString() << "\t";
            stream << "carb: " << model->data(model->index(row, 0)).toString() << "\t";
            stream << "cartG: " << model->data(model->index(row, 3)).toString() << "\t";
            stream << "poids: " << model->data(model->index(row, 4)).toString() << "\t";
            stream << "assurance: " << model->data(model->index(row, 5)).toString() << "\n";


        }

        file.close();
    }
    else {
        qDebug() << "Erreur lors de l'ouverture du fichier : " << file.errorString();
    }
}
/*
QString Livraison::statistiquesParcarburant()
{
    int livraisonsansplomb = getNombrevehiculeParcarteG("sans plomb");
    int livraisongasoil = getNombrevehiculeParcarteG("gasoil");
    int totallivraison = livraisonsansplomb + livraisongasoil;

    if (totallivraison == 0) {
        return QObject::tr("Aucune donnée disponible pour les statistiques.");
    }

    QtCharts::QPieSeries *pieSeries = new QtCharts::QPieSeries();

    // Ajouter les valeurs au graphique
    pieSeries->append(QObject::tr("Sans plomb"), livraisonsansplomb);
    pieSeries->append(QObject::tr("Gasoil"), livraisongasoil);

    // Modifier les couleurs des tranches
    QtCharts::QPieSlice *sansplombSlice = pieSeries->slices().at(0);
    sansplombSlice->setBrush(QColor(Qt::red));

    QtCharts::QPieSlice *gasoilSlice = pieSeries->slices().at(1);
    gasoilSlice->setBrush(QColor(Qt::blue));

    // Ajouter des étiquettes avec pourcentages
    sansplombSlice->setLabel(QObject::tr("Sans plomb") + ": " +
                             QString::number((livraisonsansplomb / static_cast<double>(totallivraison)) * 100, 'f', 1) + "%");

    gasoilSlice->setLabel(QObject::tr("Gasoil") + ": " +
                          QString::number((livraisongasoil / static_cast<double>(totallivraison)) * 100, 'f', 1) + "%");

    // Configurer le graphique
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(pieSeries);
    chart->setTitle(QObject::tr("Statistiques des véhicules"));
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Configurer la vue du graphique
    QtCharts :: QChartView * chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->show();

    // Générer une chaîne descriptive des statistiques
    QString statistiques = QObject::tr("Statistiques des véhicules :\n");
    statistiques += QObject::tr("Sans plomb") + ": " +
                    QString::number((livraisonsansplomb / static_cast<double>(totallivraison)) * 100, 'f', 1) + "%\n";
    statistiques += QObject::tr("Gasoil") + ": " +
                    QString::number((livraisongasoil / static_cast<double>(totallivraison)) * 100, 'f', 1) + "%";

    return statistiques;
}
*/
/*
QGraphicsScene& Livraison::statistiquesParcarburant()
{
    int livraisonsansplomb = getNombreLivraisonparcarburant("sans plomb");
    int livraisongasoil = getNombreLivraisonparcarburant("gasoil");
    int totallivraison = livraisongasoil + livraisonsansplomb;

    QtCharts::QPieSeries *pieSeries = new QtCharts::QPieSeries();

    QtCharts::QPieSlice *sansplombSlice = new QtCharts::QPieSlice();
    QtCharts::QPieSlice *gasoilSlice = new QtCharts::QPieSlice();

    sansplombSlice->setBrush(QColor(Qt::red));
    gasoillice->setBrush(QColor(Qt::blue));

    if (totalvehicule > 0) {
        sansplombSlice->setValue(static_cast<double>(commandesEnCours));
        gasoilSlice->setValue(static_cast<double>(commandesValidees));
    }

    pieSeries->append(sansplombSlice);
    pieSeries->append(gasoilSlice);

    sansplombSlice->setLabel(QObject::tr("sans polomb") + ": " + QString::number(sansplombSlice->percentage() * 100, 'f', 1) + "%");
    gasoilSlice->setLabel(QObject::tr("gasoil") + ": " + QString::number(gasoilSlice->percentage() * 100, 'f', 1) + "%");

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("Statistiques des vehicule");

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QGraphicsProxyWidget *proxyWidget = new QGraphicsProxyWidget();
    proxyWidget->setWidget(chartView);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(proxyWidget);

    return *scene;
}
*/
int Livraison::getNombrevehiculeParcarteG(const QString &carteG)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Livraison WHERE carteG = :carteG");
    query.bindValue(":cateG", carteG);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }

    return -1; // Une valeur négative indique une erreur
}
bool Livraison::vehiculeExists()
{
    QSqlQuery query("SELECT COUNT(*) FROM Livraison WHERE carteG = 'annuler'");

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();

        // If there are vehicule with state 'annuler', return true
        if (count > 0) {
            return true;
        }
    }

    return false;
}
