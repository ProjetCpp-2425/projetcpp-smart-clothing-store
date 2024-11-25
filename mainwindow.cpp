#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commande.h"
#include <QApplication>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSqlQuery>
#include<iostream>
#include<QDebug>
#include <QSqlTableModel>
#include <QSqlError>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPdfWriter>
#include <QPainter>
#include <QImage>
#include <QFileDialog>
#include <QTextDocument>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPixmap>
#include <QSqlQuery>
#include "mainwindow.h"
#include "commande.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include <QSqlQuery>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include "mainwindow.h"
#include "commande.h"
#include "qprinter.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "connection.h"
#include <QSqlTableModel>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include <QSqlQuery>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QDate>
#include <QMap>
#include <utility>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QImage>
#include <QPixmap>
#include <cmath>
#include <QPair>
#include <QList>
#include <QMap>
#include <QObject>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    commandeInstance()
{
    ui->setupUi(this);
    ui->comboBox_description->addItem("Très bien");
    ui->comboBox_description->addItem("Moyenne");
    ui->comboBox_description->addItem("Mauvaise");
    connect(ui->pushButton_pdf, &QPushButton::clicked, this, &MainWindow::on_pdf_clicked);
    ui->tableView->setModel(Etmp.afficher());




}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_11_clicked()
{
    int code_commande = ui->lineEdit_code_commande->text().toInt();
    int tel = ui->lineEdit_tel->text().toInt();
    QString description = ui->comboBox_description->currentText();
    QString ref = ui->lineEdit_ref->text();
    int quantite = ui->spinBox_quantite->text().toInt();
    int prix = ui->lineEdit_prix->text().toInt();
    QString id = ui->lineEdit_id->text();
    int cin = ui->lineEdit_cin->text().toInt();

    commande a(code_commande, tel, description, ref, quantite, prix, id, cin);

    QString success = a.ajouter();

    if (success == "true")
    {
        QMessageBox::information(this, "Ajout", "Commande ajoutée avec succès !");
        ui->tableView->setModel(Etmp.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Erreur", success);
    }
}

void MainWindow::on_pushButton_12_clicked()
{
    int code_commande = ui->lineEdit_code_commande->text().toInt();
    int tel = ui->lineEdit_tel->text().toInt();
    QString description = ui->comboBox_description->currentText();
    QString ref = ui->lineEdit_ref->text();
    int quantite = ui->spinBox_quantite->value();
    int prix = ui->lineEdit_prix->text().toInt();
    QString id = ui->lineEdit_id->text();
    int cin = ui->lineEdit_cin->text().toInt();

    commande a(code_commande, tel, description, ref, quantite, prix, id, cin);
    bool success = a.mise_a_jour();

    if (success)
    {
        QMessageBox::information(this, "Modification", "Commande modifiée avec succès !");
        ui->tableView->setModel(Etmp.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification de la commande!");
    }
}


void MainWindow::on_pushButton_15_clicked()
{
    // On récupère l'ID de la commande depuis l'interface utilisateur (par exemple, un champ de texte)
    bool ok;
    int code_commande = ui->lineEdit_code_article_sup->text().toInt(&ok);

    if (ok) {
        // On utilise le setter setId pour définir l'ID de la commande
        commandeInstance.setCodecommande(code_commande);

        // Maintenant, vous pouvez utiliser commandeInstance.id_commande (ou getId()) pour gérer la commande
        qDebug() << "code de la commande : " << commandeInstance.getCodecommande();

        // Supposons que vous supprimez cette commande
        if (commandeInstance.supprimer(code_commande)) {
            QMessageBox::information(this, "Succès", "Commande supprimée.");
        } else {
            QMessageBox::warning(this, "Erreur", "Erreur lors de la suppression de la commande.");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID de commande valide.");
    }
}

void MainWindow::on_lineEdit_recherche_cursorPositionChanged()
{
    QString rechercheText = ui->lineEdit_recherche->text();

    // Reset the table if the search field is empty
    if (rechercheText.isEmpty()) {
        ui->tableView->setModel(Etmp.afficher());
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM COMMANDE WHERE ID LIKE :rechercheText");
    query.bindValue(":rechercheText", "%" + rechercheText + "%");

    if (query.exec()) {
        auto *model = new QSqlQueryModel(this);
        model->setQuery(std::move(query));  // Move the query to avoid the deprecation warning

        // Set column headers
        model->setHeaderData(0, Qt::Horizontal, "Code Commande");
        model->setHeaderData(1, Qt::Horizontal, "ID");
        model->setHeaderData(2, Qt::Horizontal, "Téléphone");
        model->setHeaderData(3, Qt::Horizontal, "Référence");
        model->setHeaderData(4, Qt::Horizontal, "Quantité");
        model->setHeaderData(5, Qt::Horizontal, "CIN");
        model->setHeaderData(6, Qt::Horizontal, "Prix");
        model->setHeaderData(7, Qt::Horizontal, "Description");

        ui->tableView->setModel(model);

        // Optional: No results handling
        if (model->rowCount() == 0) {
            QMessageBox::information(this, "Recherche", "Aucun résultat trouvé.");
        }
    } else {
        // Handle query execution failure
        QMessageBox::critical(this, "Erreur",
                              "Échec de la recherche : " + query.lastError().text());
        qDebug() << "Query Error:" << query.lastError().text();
    }
}

void MainWindow::on_pdf_clicked() {
    // Get the QSqlQueryModel from the table view
    qDebug() << "PDF bouton cliqué!";
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());

    if (model) {
        QString content;

        // Title of the document
        content += "<h1 style=\"text-align:center;\">Liste des Commandes</h1>";

        // Table style
        content += "<style>table { border-collapse: collapse; width: 100%; } th, td { border: 1px solid black; padding: 8px; text-align: center; } th { background-color: lightgray; }</style>";
        content += "<table>";

        // Add column headers
        content += "<tr><th>ID Commande</th><th>Fournisseur</th><th>Description</th><th>Quantité</th><th>Prix</th><th>ID</th><th>CIN</th></tr>";

        // Check if the model has any rows
        if (model->rowCount() > 0) {
            // Add data rows from the QSqlQueryModel
            for (int row = 0; row < model->rowCount(); ++row) {
                content += "<tr>";
                content += "<td>" + model->data(model->index(row, 0)).toString() + "</td>";
                content += "<td>" + model->data(model->index(row, 1)).toString() + "</td>";
                content += "<td>" + model->data(model->index(row, 2)).toString() + "</td>";
                content += "<td>" + model->data(model->index(row, 3)).toString() + "</td>";
                content += "<td>" + model->data(model->index(row, 4)).toString() + "</td>";
                content += "<td>" + model->data(model->index(row, 5)).toString() + "</td>";
                content += "<td>" + model->data(model->index(row, 6)).toString() + "</td>";
                content += "</tr>";
            }
        } else {
            content += "<tr><td colspan=\"7\">Aucune donnée disponible</td></tr>";
        }

        // End table
        content += "</table>";

        // Create QTextDocument and set its HTML content
        QTextDocument document;
        document.setHtml(content);

        // Dialog for saving the PDF
        QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "commandes", "Fichiers PDF (*.pdf)");

        if (!fileName.isEmpty()) {
            QPrinter printer(QPrinter::HighResolution); // Use QPrinter for PDF generation
            printer.setOutputFormat(QPrinter::PdfFormat);  // Set the output format to PDF
            printer.setOutputFileName(fileName);  // Specify the output file name

            // Print the document to the printer
            document.print(&printer);

            // Show success message
            QMessageBox::information(this, "Export PDF", "Le PDF a été créé avec succès.");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Le modèle de données est invalide.");
    }
}





void MainWindow::on_statistique_clicked()
{

    // Obtenir les statistiques des commandes
    QMap<QString, int> statistiques = Etmp.statistiquesdescription(); // Remplacez commandeInstance par votre instance

    // États attendus (par exemple, dans la comboBox)
    QStringList description = { "Très bien","Moyenne","Mauvaise" };

    if (!statistiques.isEmpty()) {
        QVector<QPair<QString, int>> chartData;

        // Filtrer les données pour afficher uniquement les états pertinents
        for (const QString &description : description) {
            int count = statistiques.value(description, 0); // Valeur par défaut à 0 si état inexistant
            chartData.append(qMakePair(description, count));
        }

        // Total pour le calcul des pourcentages
        int total = 0;
        for (const auto& item : chartData) {
            total += item.second;
        }

        // Vérifier s'il y a des données
        if (total == 0) {
            QMessageBox::information(this, tr("Aucune donnée"), tr("Aucune commande trouvée pour ces description."));
            return;
        }

        // Palette de couleurs
        QVector<QColor> colorPalette = {
            QColor(255, 99, 71),  // Tomato red
            QColor(70, 130, 180), // Steel blue
            QColor(34, 139, 34)   // Forest green
        };

        // --- Création du graphique en secteurs ---
        const int pieChartWidth = 400;
        const int pieChartHeight = 400;
        QImage pieChartImage(pieChartWidth, pieChartHeight, QImage::Format_ARGB32);
        pieChartImage.fill(Qt::white);

        QPainter pieChartPainter(&pieChartImage);
        pieChartPainter.setRenderHint(QPainter::Antialiasing);

        QRectF pieRect(50, 50, 300, 300);
        int startAngle = 0;
        int colorIndex = 0;

        for (const auto& item : chartData) {
            int spanAngle = (item.second * 360) / total;
            QColor color = colorPalette[colorIndex % colorPalette.size()];
            pieChartPainter.setBrush(color);

            pieChartPainter.drawPie(pieRect, startAngle * 16, spanAngle * 16);

            // Affichage des étiquettes
            int midAngle = startAngle + spanAngle / 2;
            QPointF textPosition(
                pieRect.center().x() + 100 * qCos(midAngle * M_PI / 180),
                pieRect.center().y() - 100 * qSin(midAngle * M_PI / 180)
            );

            pieChartPainter.setPen(Qt::black);
            pieChartPainter.drawText(textPosition, item.first);

            startAngle += spanAngle;
            colorIndex++;
        }

        QPixmap pieChartPixmap = QPixmap::fromImage(pieChartImage);

        // Configuration de tableView_2
        QStandardItemModel* pieChartModel = new QStandardItemModel(1, 1, this);
        QStandardItem* pieChartItem = new QStandardItem();
        pieChartItem->setData(pieChartPixmap, Qt::DecorationRole);
        pieChartModel->setItem(0, 0, pieChartItem);
        ui->tableView_3->setModel(pieChartModel);
        ui->tableView_3->resizeColumnsToContents();
        ui->tableView_3->resizeRowsToContents();

        // --- Création du graphique à barres ---
        const int barChartWidth = 500;
        const int barChartHeight = 300;
        QImage barChartImage(barChartWidth, barChartHeight, QImage::Format_ARGB32);
        barChartImage.fill(Qt::white);

        QPainter barChartPainter(&barChartImage);
        barChartPainter.setRenderHint(QPainter::Antialiasing);

        int barWidth = 50;

        int gap = 20;
        int xOffset = 40;
        int maxBarHeight = barChartHeight - 60;

        int maxValue = 0;
        for (const auto& item : chartData) {
            maxValue = qMax(maxValue, item.second);
        }

        float scaleFactor = static_cast<float>(maxBarHeight) / maxValue;
        colorIndex = 0;

        for (const auto& item : chartData) {
            int barHeight = static_cast<int>(item.second * scaleFactor);
            QRectF barRect(xOffset, barChartHeight - barHeight - 30, barWidth, barHeight);

            QColor barColor = colorPalette[colorIndex % colorPalette.size()];
            barChartPainter.setBrush(barColor);
            barChartPainter.drawRect(barRect);

            barChartPainter.setPen(Qt::black);
            barChartPainter.drawText(
                QPointF(barRect.x() + barWidth / 4, barRect.y() - 5),
                QString::number(item.second)
            );
            barChartPainter.drawText(
                QPointF(barRect.x() + barWidth / 4, barChartHeight - 10),
                item.first
            );

            xOffset += barWidth + gap;
            colorIndex++;
        }

        QPixmap barChartPixmap = QPixmap::fromImage(barChartImage);

        // Configuration de tableView_3
        QStandardItemModel* barChartModel = new QStandardItemModel(1, 1, this);
        QStandardItem* barChartItem = new QStandardItem();
        barChartItem->setData(barChartPixmap, Qt::DecorationRole);
        barChartModel->setItem(0, 0, barChartItem);
        ui->tableView_4->setModel(barChartModel);
        ui->tableView_4->resizeColumnsToContents();
        ui->tableView_4->resizeRowsToContents();
    } else {
        QMessageBox::warning(this, tr("Erreur"), tr("Aucune donnée statistique trouvée."));
    }
}


void MainWindow::on_ajouterArticle_clicked()
{
    // Récupérer les données saisies dans les champs
    QString article = ui->lineEdit_article->text();  // Nom de l'article
    bool ok;
    float prix = ui->lineEdit_prix_2->text().toFloat(&ok);  // Prix de l'article (converti en float)

    // Vérifier si les données sont valides
    if (article.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom de l'article ne peut pas être vide.");
        return;
    }
    if (!ok || prix <= 0) {
        QMessageBox::warning(this, "Erreur", "Le prix doit être un nombre positif.");
        return;
    }

    // Ajouter l'article et son prix au panier
    commandeInstance.ajouterArticle(article, prix);

    // Mettre à jour l'affichage du panier
    ui->textEdit_panier->setPlainText(commandeInstance.afficherPanier());

    // Effacer les champs de saisie pour un nouvel ajout
    ui->lineEdit_article->clear();
    ui->lineEdit_prix->clear();

    // Afficher un message de confirmation
    QMessageBox::information(this, "Succès", "Article ajouté au panier.");
}


void MainWindow::on_viderPanier_clicked()
{    // Vider le panier
    commandeInstance.viderPanier();

    // Mettre à jour l'affichage du panier (affichage vide)
    ui->textEdit_panier->setPlainText("Le panier est maintenant vide.");

    // Afficher un message de confirmation
    QMessageBox::information(this, "Succès", "Le panier a été vidé.");

}


void MainWindow::on_supprimerArticleButton_clicked()
{
    // Récupérer le nom de l'article à supprimer
    QString articleASupprimer = ui->lineEdit_article->text();

    if (articleASupprimer.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir le nom de l'article à supprimer.");
        return;
    }

    // Supprimer l'article du panier
    commandeInstance.supprimerArticleButton(articleASupprimer);

    // Mettre à jour l'affichage du panier après suppression
    QString panierText = commandeInstance.afficherPanier();
    ui->textEdit_panier->setPlainText(panierText);

    // Afficher un message de confirmation
    QMessageBox::information(this, "Succès", QString("L'article '%1' a été supprimé.").arg(articleASupprimer));
}



void MainWindow::on_calculerPrixTotal_clicked()
{
    // Appeler la méthode calculerPrixTotal de la commandeInstance pour obtenir le total
        float total = commandeInstance.calculerPrixTotal();

        // Vérifier si le panier est vide (total égal à 0)
        if (!commandeInstance.afficherPanier().contains("vide")) {
            // Afficher le prix total dans un QLabel ou tout autre widget
            ui->prix->setText(QString("Total : %1 DT").arg(total, 0, 'f', 2));  // Formatage avec 2 décimales
        } else {
            // Si le panier est vide, afficher un message approprié
            ui->prix->setText("Le panier est vide.");
        }
}





void MainWindow::on_afficherPanier_clicked()
{
        QString panierText = commandeInstance.afficherPanier();
        ui->textEdit_panier->setPlainText(panierText);
}

void MainWindow::on_comboBox_3_activated(int index)
{
    // Vérifier si l'index est valide
    if (index < 0) {
        QMessageBox::warning(this, "Erreur", "Aucune option sélectionnée.");
        return;
    }

    // Récupérer l'option sélectionnée dans le QComboBox
    QString option = ui->comboBox_3->itemText(index).toLower().trimmed();

    // Associer les options au tri SQL
    QString query;
    if (option == "ordre croissant prix") {
        query = "SELECT * FROM COMMANDE ORDER BY prix ASC";
    } else if (option == "ordre décroissant prix") {
        query = "SELECT * FROM COMMANDE ORDER BY prix DESC";
    }
    else if (option == "ordre alphabétique  code_commande") {
        query = "SELECT * FROM COMMANDE ORDER BY code_commande ASC";
    } else if (option == "par défaut") {
        query = "SELECT * FROM COMMANDE";
    } else {
        QMessageBox::warning(this, "Erreur", "Option non reconnue.");
        return;
    }

    // Exécuter la requête SQL
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Vérifier si la requête a réussi
    if (model->lastError().isValid()) {
        QMessageBox::critical(this, "Erreur SQL", "Impossible d'exécuter la requête : " + model->lastError().text());
        delete model;
        return;
    }

    // Appliquer le modèle à la tableView
    ui->tableView->setModel(model);

    // Ajuster automatiquement les colonnes et les lignes
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    // Facultatif : Message de débogage pour confirmer l'exécution
    qDebug() << "Requête exécutée avec succès : " << query;
}



