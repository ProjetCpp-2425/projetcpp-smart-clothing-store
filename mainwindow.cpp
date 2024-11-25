#include "mainwindow.h"
 #include "ui_mainwindow.h"
#include <QMessageBox>
#include "connection.h"
#include <QFileDialog>
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>
 #include "produit.h"
#include <QDateTime>
#include <QWidget>

#include <QDesktopServices>
#include <QUrl> // Nécessaire pour utiliser QUrl avec QDesktopServices
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadProduitData();
    qDebug() << "Available database drivers: " << QSqlDatabase::drivers();

}

MainWindow::~MainWindow()
{
    delete ui;     // Libérer la mémoire de l'interface utilisateur
  // Libérer la mémoire de l'objet Produit
}

void MainWindow::on_ajouter_produit_clicked()
{
    int Idp = ui->lineEdit_Idp->text().toInt(); // Convertir la chaîne saisie en entier
    QString Nomp = ui->lineEdit_Nomp->text();
    QString Marque = ui->marque->text();
    QString Quantite = ui->lineEditQuantite->text();
    int Prix = ui->lineEditPrix->text().toInt();
    QString categorie = ui->categorie->currentText(); // Get the selected text from QComboBox

    // Instancier un objet de la classe Produit
    Produit P(Nomp,categorie,Marque,  Quantite,  Idp, Prix);

    // Appel de la méthode ajouter()
    bool test = P.ajouter(); // Insérer l'objet Produit instancié dans la table

    // Vérification du résultat de l'ajout
    if (test) {
        addToHistory("Ajout de produit ",Idp);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        loadProduitData();

    } else { // Si la requête échoue
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}



void MainWindow::on_suppreime_produit_clicked()
{
    int id = ui->lineEdit_Idp->text().toInt(); // Assuming `lineEdit_IdpSupp` is where the ID is entered

    // Call the supprimer() method on a Produit object or Etmp (an instance of Produit)
    Produit P;
    bool test = P.supprimer(id); // Attempt to delete the product with the specified ID

    // Check the result of the deletion and display appropriate message
    if (test) {
        addToHistory("Suppression de produit ",id);

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        loadProduitData();

    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::loadProduitData()
{
    // Create a new QSqlQueryModel
    QSqlQueryModel *model = new QSqlQueryModel(this);

    // Set the SQL query to fetch produit data
    model->setQuery("SELECT IDP, CATEGORIE, MARQUE, QUANTITE, PRIX, NOMP FROM PRODUIT");

    // Check if there was an error in the query
    if (model->lastError().isValid()) {
        qDebug() << "Error loading data from database: " << model->lastError().text();
        return;
    }

    // Set the model to the QTableView to display the data
    ui->tableView->setModel(model);

    // Resize the columns to fit the data
    ui->tableView->resizeColumnsToContents();
}
void MainWindow::on_Modifier_produit_clicked()
{
    // Get the updated product data from the input fields
    int Idp = ui->lineEdit_Idp->text().toInt(); // Assuming you have a field for ID
    QString Nomp = ui->lineEdit_Nomp->text();
    QString Marque = ui->marque->text();
    QString Quantite = ui->lineEditQuantite->text();
    int Prix = ui->lineEditPrix->text().toInt();
    QString categorie = ui->categorie->currentText(); // Get selected category from combo box

    // Instantiate a Produit object with the updated data
    Produit P(Nomp, categorie, Marque, Quantite, Idp, Prix);

    // Call the modifier() method
    bool test = P.modifier(Idp); // Update the product with the specified Idp

    // Check the result of the update operation and show an appropriate message
    if (test) {
        addToHistory("Modification de produit ",Idp);

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
        loadProduitData(); // Refresh the table view after modification
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Modification non effectuée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_recherhce_produit_clicked()
{
    QString idText = ui->lineEdit_Idp_2->text().trimmed(); // Get input text and trim whitespace
    QSqlQueryModel* model = nullptr; // Initialize the model

    // Create a Produit object to handle database interactions
    Produit P;

    if (idText.isEmpty()) {
        // If the search bar is empty, fetch all products
        model = P.fetchAll();
    } else {
        bool isNumeric;
        int id = idText.toInt(&isNumeric); // Convert text to integer safely
        if (!isNumeric) {
            QMessageBox::critical(this, "Erreur", "L'ID saisi n'est pas valide. Veuillez entrer un nombre.");
            return;
        }
        model = P.rechercher(id);
    }

    if (!model) {
        // Error handling if the model is invalid
        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la recherche.");
        return;
    }

    // Set the model to the table view
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    if (model->rowCount() > 0) {
        if (!idText.isEmpty()) {
            addToHistory("Recherche de produit", idText.toInt());
            QMessageBox::information(this, "Résultat", "Produit trouvé.");
        }
    } else {
        QMessageBox::information(this, "Résultat", "Aucun produit trouvé.");
        loadProduitData();

    }
}


void MainWindow::on_trier_produit_clicked()
{
    // Instantiate a Produit object to access the trierParPrix method
       Produit P;

       // Call the trierParPrix function to sort in ascending order (true) or descending (false)
       bool ascending = true;  // Change this to false if you want descending order
       QSqlQueryModel* sortedModel = P.trierParPrix(ascending);

       // Check if sorting succeeded
       if (sortedModel->lastError().isValid()) {
           qDebug() << "Erreur lors du tri par prix : " << sortedModel->lastError().text();
           QMessageBox::critical(this, "Erreur", "Erreur lors du tri par prix.");
           return;
       }

       // Set the sorted model to the table view
       ui->tableView->setModel(sortedModel);
       ui->tableView->resizeColumnsToContents();

}


void MainWindow::on_expoter_produit_clicked()
{
    // Open a file dialog to select the save location and filename
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf);;All Files (*)"));

    // Check if the user canceled the file dialog
    if (fileName.isEmpty()) {
        return;
    }

    // Ensure the filename has a .pdf extension
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    // Verify database connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, tr("Database Error"), tr("Database connection is not open. Error: %1").arg(db.lastError().text()));
        return;
    }

    // Create a PDF writer object
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    // Create a QPainter to draw on the PDF
    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        QMessageBox::warning(this, tr("PDF Error"), tr("Failed to initialize the PDF painter."));
        return;
    }

    // Set font for the PDF
    QFont font("Arial", 12);
    painter.setFont(font);

    // Draw title
    painter.drawText(100, 100, "Product Data");

        int yOffset = 150; // Initial y position for the data
        int i = 1;

        // Execute the query
        QSqlQuery query;
        if (!query.exec("SELECT IDP, CATEGORIE, MARQUE, QUANTITE, PRIX, NOMP FROM PRODUIT")) {
            QMessageBox::warning(this, tr("Query Error"), tr("Failed to execute query. Error: %1").arg(query.lastError().text()));
            return;
        }

        // Iterate over each product and print details in the specified format
        while (query.next()) {
            // Print each product's data in a structured format
            painter.drawText(50, yOffset, "Product " + QString::number(i) + ":");
            i++;  // Increment the product count
            yOffset += 60;
            painter.drawText(100, yOffset, "IDP: " + query.value("IDP").toString());
            yOffset += 60;
            painter.drawText(100, yOffset, "Category: " + query.value("CATEGORIE").toString());
            yOffset += 60;
            painter.drawText(100, yOffset, "Brand: " + query.value("MARQUE").toString());
            yOffset += 60;
            painter.drawText(100, yOffset, "Quantity: " + query.value("QUANTITE").toString());
            yOffset += 60;
            painter.drawText(100, yOffset, "Price: " + query.value("PRIX").toString());
            yOffset += 60;
            painter.drawText(100, yOffset, "Product Name: " + query.value("NOMP").toString());

            // Add some space between products
            yOffset += 100;
        }

        // Finalize the PDF
        painter.end();

        // Optionally, show a message box to confirm PDF creation
        QMessageBox::information(this, tr("PDF Generated"), tr("The product data has been saved as a PDF."));
    }






void MainWindow::on_statistique_produit_clicked() {
Produit produit;
QSqlQueryModel* model=produit.afficher();//QSqlQueryModel est une classe qui permet d'afficher des données dans des vues de Qt
produit.genererStatistiquesMarqueQuantite(model);

}
QSqlQueryModel* Produit::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT NOMP, CATEGORIE, MARQUE, QUANTITE, IDP, PRIX FROM PRODUIT");
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des données produits:" << query.lastError().text();
        return nullptr;
    }

    model->setQuery(query);
    return model;
}

void  MainWindow::afficherHistorique()
{
    // Spécifier le chemin complet du fichier historique
    QString cheminFichier = "C:/Users/HP/Downloads/EmnaBenBader/projet crud/histo.txt";

    // Ouvrir le fichier en écriture (mode Append)
    QFile file(cheminFichier);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique.";
        return;
    }

    // Créer un flux texte pour écrire dans le fichier
    QTextStream out(&file);

    // Obtenir la date et l'heure actuelles
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Écrire dans le fichier
    out << "Actions enregistrées à " << currentDateTime.toString() << "\n";

    // Fermer le fichier
    file.close();

    // Afficher un message pour indiquer que les actions ont été enregistrées dans l'historique
    QMessageBox::information(this, "Historique", "Les actions ont été enregistrées dans l'historique." );
    QDesktopServices::openUrl(QUrl::fromLocalFile(cheminFichier));
}

void MainWindow::on_historique_produit_clicked()
{
    QString cheminFichier ="C:/Users/HP/Downloads/EmnaBenBader/projet crud/histo.txt";
      QFile file( cheminFichier);
      if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      {
          // Afficher un message d'erreur si le fichier ne peut pas être ouvert
          QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier d'historique.");
          return;
      }

      // Lire le contenu du fichier
      QTextStream in(&file);
      QString historique = in.readAll();

      // Fermer le fichier
      file.close();

      // Afficher le contenu de l'historique dans une boîte de dialogue
      QMessageBox msgBox;
      msgBox.setWindowTitle("Historique");
      msgBox.setText(historique);
      msgBox.exec();
}
void MainWindow::addToHistory(const QString &action,int IDP)
{
    // Ouvrir le fichier en écriture
    QString cheminFichier = "C:/Users/HP/Downloads/EmnaBenBader/projet crud/histo.txt";
    QFile file(cheminFichier);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique.";
        return;

    }

    // Créer un flux texte pour écrire dans le fichier
    QTextStream out(&file);

    // Obtenir la date et l'heure actuelles
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Écrire l'action dans le fichier historique avec la date et l'heure
    out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " - " << action;
    if (IDP != 0) {
        out << " de ID  " << IDP;
    }
    out << "\n";

    // Fermer le fichier
    file.close();
}
void MainWindow::writeHistoryToFile(const QString &fileName) {
    // Ouvrir le fichier en écriture
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique.";
        return;
    }

    // Créer un flux texte pour écrire dans le fichier
    QTextStream out(&file);

    // Écrire chaque entrée d'historique dans le fichier
    for (const QString &entry : historyList) {
        out << entry << "\n";
    }

    // Fermer le fichier
    file.close();

    qDebug() << "Historique enregistré dans le fichier historique_patients.txt.";
}
