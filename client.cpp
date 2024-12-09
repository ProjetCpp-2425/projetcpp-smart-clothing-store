#include "client.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <algorithm>
#include <QMap>
#include <QHash>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QDate>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QDesktopServices>
#include <QMessageBox>

Client::Client()
{
    id=0;
    nom_p="";
    numero=0;
    mail="";
    date_="";
    genre="";
}
Client::Client(int id, QString nom_p, int numero, QString mail, QString date_, QString genre)
{
    this->id=id;
    this->numero=numero;
    this->nom_p=nom_p;
    this->mail=mail;
    this->date_=date_;
    this->genre=genre;
}
bool Client::ajouter()
{
    // Vérifier si le numéro de Client existe déjà
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM Client WHERE id = :id");
    checkQuery.bindValue(":id", id);
    checkQuery.exec();

    if (checkQuery.next()) {
        // Le numéro de Client existe déjà, l'ajout ne peut pas être effectué
        return false;
    } else {
        // Le numéro de Client n'existe pas, procéder à l'ajout
        QString id_string = QString::number(id);
        QString numero_string = QString::number(numero);

        QSqlQuery query;
        query.prepare("INSERT INTO Client (id, nom_p, numero, mail, date_, genre) "
                      "VALUES (:id, :nom_p, :numero, :mail, :date_, :genre)");
        query.bindValue(":id", id_string);
        query.bindValue(":nom_p", nom_p);
        query.bindValue(":numero", numero_string);
        query.bindValue(":mail", mail);
        query.bindValue(":date_", date_);
        query.bindValue(":genre", genre);


        return query.exec();
    }
}

QSqlQueryModel * Client::afficher()const
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from Client");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_p"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("mail"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("numero"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("genre"));

            return model;

}

bool Client::supprimer(int id)
{
    // Vérifier si le numéro de Client existe avant de le supprimer
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM Client WHERE id = :id");
    checkQuery.bindValue(":id", id);
    checkQuery.exec();

    if (!checkQuery.next()) {
        // Le numéro de Client n'existe pas, la suppression ne peut pas être effectuée
        return false;
    }

    // Procéder à la suppression
    QSqlQuery query;
    query.prepare("DELETE FROM Client WHERE id=:id");
    query.bindValue(":id", id);

    return query.exec();
}

bool Client::modifier(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    QString res3= QString::number(numero);
    query.prepare("update Client set id=:id,nom_p=:nom_p,numero=:numero,mail=:mail,date_=:date_,genre=:genre WHERE id=:id");
    query.bindValue(":id",res);
    query.bindValue(":nom_p",nom_p);
    query.bindValue(":numero",res3);
    query.bindValue(":mail",mail);
    query.bindValue(":date_",date_);
    query.bindValue(":genre",genre);

    return query.exec();
}
QSqlQueryModel * Client::rechercher(int id)
{
    QSqlQuery query;
    QString id_str = QString::number(id);


    QString queryStr = "SELECT * FROM Client WHERE 1=1";

    if (id > 0) {
        queryStr += " AND id = :id";
    }

    query.prepare(queryStr);

    if (id > 0) {
        query.bindValue(":id", id_str);
    }


    query.exec();

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    return model;
}
QSqlQueryModel * Client::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from Client order by id");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_p"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("mail"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("numero"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("date"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("genre"));


    return model;
}
void Client::exporterPDF(const QString &nomFichier) const
{
    QFile file(nomFichier);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QPdfWriter pdfWriter(&file);
        pdfWriter.setPageSize(QPageSize(QPageSize::A4));
        QPainter painter(&pdfWriter);

        painter.drawText(100, 100, "Liste des Clients");

        painter.drawText(100, 150, "id");
        painter.drawText(200, 150, "numero");
        painter.drawText(300, 150, "nom_p");
        painter.drawText(400, 150, "mail");
        painter.drawText(500, 150, "Date");
        painter.drawText(600, 150, "Genre");



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
std::string Client::chatbotFunction(const QString &userMessage) {
std::string lowerMessage = userMessage.toStdString();
std::transform(lowerMessage.begin(), lowerMessage.end(), lowerMessage.begin(), ::tolower);

    if (lowerMessage.find("bonjour") != std::string::npos) {
        return "Salut! Comment puis-je vous aider aujourd'hui?";

    } else if (lowerMessage.find("comment ça va?") != std::string::npos) {
        return "Je suis un programme, donc je n'ai pas de sentiments mais merci de demander!";

    } else if (lowerMessage.find("ça va?") != std::string::npos) {
        return "Je suis un programme, donc je n'ai pas de sentiments mais merci de demander!";

    } else if (lowerMessage.find("comment choisir un id?") != std::string::npos) {
        return "Un identifiant doit être composé de 7 chiffres";

    } else if (lowerMessage.find("horaire été") != std::string::npos) {
        return "8h30-14h";
    } else if (lowerMessage.find("horaire hiver") != std::string::npos) {
        return "8h-12h 13h30-17h";

    } else if (lowerMessage.find("assistance") != std::string::npos) {
        return "Veuillez contactez le 99000999";

    } else if (lowerMessage.find("urgence") != std::string::npos) {
        return "Veuillez contactez le 12012012";

    } else if (lowerMessage.find("livraison") != std::string::npos) {
        return "Les livraisons arrivent généralement entre 9h00 et 14h00 du lundi au vendredi.";

    } else if (lowerMessage.find("fête") != std::string::npos) {
        return "Pendant les fêtes, la boutique est ouverte tous les jours de 10h00 à 20h00.";

    } else if (lowerMessage.find("quel est ton nom?") != std::string::npos) {
        return "Je suis un chatbot créé par OpenAI.";

    } else if (lowerMessage.find("au revoir") != std::string::npos) {
        return "Au revoir! N'hésitez pas à revenir si vous avez d'autres questions.";

    } else {
        return "Désolé, je ne comprends pas. Pouvez-vous reformuler votre question?";
    }
    return  "Reponse du chatbot";
}
QSqlQueryModel* Client::historique() const
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM Client");
    if (query.exec()) {
        model->setQuery(query);
    }
    return model;
}
void Client::exporterHistoriqueTexte(const QString &nomFichier) const
{
    QFile file(nomFichier);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "Liste des Clients\n\n";

        QSqlQueryModel *model = historique();

        for (int row = 0; row < model->rowCount(); ++row)
        {
            stream << "nom_p: " << model->data(model->index(row, 1)).toString() << "\t";
            stream << "id: " << model->data(model->index(row, 0)).toString() << "\t";
            stream << "numero: " << model->data(model->index(row, 3)).toString() << "\t";
            stream << "mail: " << model->data(model->index(row, 2)).toString() << "\n";
            stream << "date: " << model->data(model->index(row, 4)).toString() << "\n";
            stream << "genre: " << model->data(model->index(row, 5)).toString() << "\n";


        }

        file.close();
    }
    else {
        qDebug() << "Erreur lors de l'ouverture du fichier : " << file.errorString();
    }
}
/*
QString Client::statistiquesParGenre()
{
    int ClientsHomme = getNombreClientsPargenre("Homme");
    int ClientsFemme = getNombreClientsPargenre("Femme");
    int nombreClients = ClientsHomme + ClientsFemme;

    QPieSeries *pieSeries = new QPieSeries();

    QPieSlice *HommeSlice = new QPieSlice();
    QPieSlice *FemmeSlice = new QPieSlice();

    HommeSlice->setBrush(QColor(Qt::red));
    FemmeSlice->setBrush(QColor(Qt::blue));

    if (nombreClients > 0) {
        HommeSlice->setValue(static_cast<double>(ClientsHomme));
        FemmeSlice->setValue(static_cast<double>(ClientsFemme));
    }

    pieSeries->append(HommeSlice);
    pieSeries->append(FemmeSlice);

    HommeSlice->setLabel(QObject::tr("Homme") + ": " + QString::number(HommeSlice->percentage() * 100, 'f', 1) + "%");
    FemmeSlice->setLabel(QObject::tr("Femme") + ": " + QString::number(FemmeSlice->percentage() * 100, 'f', 1) + "%");

    QChart::QChart *chart = new QChart::QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("Statistiques des Clients");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->show();

    QString statistiques = "Statistiques des Clients :\n";
    statistiques += QObject::tr("Homme") + " : " + QString::number(HommeSlice->percentage() * 100, 'f', 1) + "%\n";
    statistiques += QObject::tr("Femme") + " : " + QString::number(FemmeSlice->percentage() * 100, 'f', 1) + "%";

    return statistiques;
}

QGraphicsScene& Client::statistiquesParGenre()
{
    int ClientsHomme = getNombreClientsPargenre("en cours");
    int ClientsFemme = getNombreClientsPargenre("validee");
    int nombreClients = ClientsHomme + ClientsFemme;

    QPieSeries *pieSeries = new QPieSeries();

    QPieSlice *HommeSlice = new QPieSlice();
    QPieSlice *FemmeSlice = new QPieSlice();

    HommeSlice->setBrush(QColor(Qt::red));
    FemmeSlice->setBrush(QColor(Qt::blue));

    if (nombreClients > 0) {
        HommeSlice->setValue(static_cast<double>(ClientsHomme));
        FemmeSlice->setValue(static_cast<double>(ClientsFemme));
    }

    pieSeries->append(HommeSlice);
    pieSeries->append(FemmeSlice);

    HommeSlice->setLabel(QObject::tr("Homme") + ": " + QString::number(HommeSlice->percentage() * 100, 'f', 1) + "%");
    FemmeSlice->setLabel(QObject::tr("Femme") + ": " + QString::number(FemmeSlice->percentage() * 100, 'f', 1) + "%");

    QChart::QChart *chart = new QChart::QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("Statistiques des Clients");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QGraphicsProxyWidget *proxyWidget = new QGraphicsProxyWidget();
    proxyWidget->setWidget(chartView);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(proxyWidget);

    return *scene;
}
*/
int Client::getNombreClientsParGenre(const QString &mail)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Client WHERE genre = :genre");
    query.bindValue(":mail", mail);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }

    return -1; // Une valeur négative indique une erreur
}
bool Client::ClientExists()
{
    QSqlQuery query("SELECT COUNT(*) FROM Client WHERE mail = 'annuler'");

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();

        // If there are commands with state 'annuler', return true
        if (count > 0) {
            return true;
        }
    }

    return false;
}

