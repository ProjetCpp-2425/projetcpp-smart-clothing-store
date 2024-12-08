#include "mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QSqlQueryModel>
#include <QFileDialog>
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include "mailwindow.h"
#include "qsqlerror.h"
#include "chatbotwindow.h"
#include "ui_mailwindow.h"
#include "FournisseurProfileWindow.h"
#include "convertisseurwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddFournisseurClicked);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateFournisseurClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteFournisseurClicked);
    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::onDisplayFournisseursClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchFournisseurClicked);
    connect(ui->exportPdfButton, &QPushButton::clicked, this, &MainWindow::onExportPdfButtonClicked);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::onSortButtonClicked);
    connect(ui->chatBotButton, &QPushButton::clicked, this, &MainWindow::onChatBotButtonClicked);
    connect(ui->mailButton, &QPushButton::clicked, this, &MainWindow::onMailButtonClicked);
    connect(ui->profileButton, &QPushButton::clicked, this, &MainWindow::onProfileButtonClicked);
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::onConvertButtonClicked);
    connect(ui->browseButton, &QPushButton::clicked, this, &MainWindow::browseLogo);
    connect(ui->refreshStatsButton, &QPushButton::clicked, this, &MainWindow::updateStats);
    onDisplayFournisseursClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddFournisseurClicked()
{
    Fournisseur f;
    int id = ui->idLineEdit->text().toInt();
    QString name = ui->nameLineEdit->text();
    QString telephone = ui->telephoneLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QDate achatDate = ui->achatDateEdit->date();
    QString logo = ui->logoLineEdit->text();
    double prixAchat = ui->prixAchatLineEdit->text().toDouble();

    if (f.addFournisseur(id, name, telephone, email, achatDate, logo, prixAchat)) {
        QMessageBox::information(this, "Success", "Fournisseur added successfully!");
        onDisplayFournisseursClicked();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add fournisseur.");
    }
}

void MainWindow::browseLogo() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select Logo", "", "Images (*.png *.jpg *.jpeg *.bmp *.gif);;All Files (*)");

    if (!filePath.isEmpty()) {
        ui->logoLineEdit->setText(filePath);
    }
}

void MainWindow::onUpdateFournisseurClicked()
{
    Fournisseur f;
    int id = ui->idLineEdit->text().toInt();
    QString name = ui->nameLineEdit->text();
    QString telephone = ui->telephoneLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QDate achatDate = ui->achatDateEdit->date();
    QString logo = ui->logoLineEdit->text(); // Get logo path
    double prixAchat = ui->prixAchatLineEdit->text().toDouble(); // Get purchase price

    if (f.updateFournisseur(id, name, telephone, email, achatDate, logo, prixAchat)) {
        QMessageBox::information(this, "Success", "Fournisseur updated successfully!");
        onDisplayFournisseursClicked();
    } else {
        QMessageBox::warning(this, "Error", "Failed to update fournisseur.");
    }
}

void MainWindow::onDeleteFournisseurClicked()
{
    Fournisseur f;
    int id = ui->idLineEdit->text().toInt();

    if (f.deleteFournisseur(id)) {
        QMessageBox::information(this, "Success", "Fournisseur deleted successfully!");
        onDisplayFournisseursClicked();
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete fournisseur.");
    }
}

void MainWindow::onDisplayFournisseursClicked()
{
    Fournisseur f;

    QSqlQueryModel *model = f.getFournisseurs();
    if (model && model->rowCount() > 0) {
        ui->fournisseurTableWidget->clear();
        ui->fournisseurTableWidget->setRowCount(model->rowCount());
        ui->fournisseurTableWidget->setColumnCount(model->columnCount());

        for (int col = 0; col < model->columnCount(); ++col) {
            QString header = model->headerData(col, Qt::Horizontal).toString();

            // If the column is for prix_achat, set custom header name
            if (header == "Prix d'achat") {
                header = "Purchase Price";
            }

            ui->fournisseurTableWidget->setHorizontalHeaderItem(col, new QTableWidgetItem(header));
        }

        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); ++col) {
                QString cellData = model->data(model->index(row, col)).toString();
                ui->fournisseurTableWidget->setItem(row, col, new QTableWidgetItem(cellData));
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "No fournisseurs found or failed to retrieve data.");
    }
}


void MainWindow::onExportPdfButtonClicked()
{
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Exporter en PDF",
                                                    "",
                                                    "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);

    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(100, 100, "Liste des Fournisseurs");

    int x = 100;
    int y = 200;
    painter.setFont(QFont("Arial", 12));
    painter.drawText(x, y, "ID");
    painter.drawText(x + 100, y, "Nom");
    painter.drawText(x + 300, y, "Téléphone");
    painter.drawText(x + 500, y, "Email");
    painter.drawText(x + 700, y, "Date Achat");
    y += 50;

    Fournisseur F;
    QSqlQueryModel *model = F.getFournisseurs();
    for (int row = 0; row < model->rowCount(); ++row) {
        QString id = model->data(model->index(row, 0)).toString();
        QString name = model->data(model->index(row, 1)).toString();
        QString telephone = model->data(model->index(row, 2)).toString();
        QString email = model->data(model->index(row, 3)).toString();
        QString achatDate = model->data(model->index(row, 4)).toString();

        painter.drawText(x, y, id);
        painter.drawText(x + 100, y, name);
        painter.drawText(x + 300, y, telephone);
        painter.drawText(x + 500, y, email);
        painter.drawText(x + 700, y, achatDate);
        y += 30;
    }

    painter.end();

    QMessageBox::information(this,
                             "Exportation réussie",
                             "Les données ont été exportées en PDF avec succès !");
}

void MainWindow::onSearchFournisseurClicked() {
    qDebug() << "button clicked";
    QString searchQuery = ui->searchLineEdit->text();

    if (searchQuery.isEmpty()) {
        QMessageBox::warning(this, "Recherche vide", "Veuillez entrer un critère de recherche.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM fournisseurs WHERE name LIKE :search OR telephone LIKE :search OR email LIKE :search");
    query.bindValue(":search", "%" + searchQuery + "%");

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur de recherche", "La recherche a échoué : " + query.lastError().text());
        return;
    }

    ui->fournisseurTableWidget->clearContents();
    ui->fournisseurTableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->fournisseurTableWidget->insertRow(row);
        ui->fournisseurTableWidget->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->fournisseurTableWidget->setItem(row, 1, new QTableWidgetItem(query.value("name").toString()));
        ui->fournisseurTableWidget->setItem(row, 2, new QTableWidgetItem(query.value("telephone").toString()));
        ui->fournisseurTableWidget->setItem(row, 3, new QTableWidgetItem(query.value("email").toString()));
        ui->fournisseurTableWidget->setItem(row, 4, new QTableWidgetItem(query.value("achat_date").toString()));
        row++;
    }

    if (row == 0) {
        QMessageBox::information(this, "Aucun résultat", "Aucun fournisseur trouvé pour le critère de recherche.");
    }
}

void MainWindow::onSortButtonClicked() {
    QString sortCriteria;

    if (ui->sortByNameRadioButton->isChecked()) {
        sortCriteria = "name";
    } else if (ui->sortByIdRadioButton->isChecked()) {
        sortCriteria = "id";
    } else {
        QMessageBox::warning(this, "Critère de tri manquant", "Veuillez sélectionner un critère de tri (Nom ou ID).");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM fournisseurs ORDER BY " + sortCriteria);

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur de tri", "Le tri a échoué : " + query.lastError().text());
        return;
    }

    ui->fournisseurTableWidget->clearContents();
    ui->fournisseurTableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->fournisseurTableWidget->insertRow(row);
        ui->fournisseurTableWidget->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->fournisseurTableWidget->setItem(row, 1, new QTableWidgetItem(query.value("name").toString()));
        ui->fournisseurTableWidget->setItem(row, 2, new QTableWidgetItem(query.value("telephone").toString()));
        ui->fournisseurTableWidget->setItem(row, 3, new QTableWidgetItem(query.value("email").toString()));
        ui->fournisseurTableWidget->setItem(row, 4, new QTableWidgetItem(query.value("achat_date").toString()));
        row++;
    }

    QMessageBox::information(this, "Tri effectué", "Les fournisseurs ont été triés par " + QString(sortCriteria == "name" ? "Nom" : "ID"));

}

void MainWindow::onMailButtonClicked() {
    MailWindow *mailWindow = new MailWindow(this);
    mailWindow->setAttribute(Qt::WA_DeleteOnClose);
    mailWindow->show();
}

void MainWindow::onChatBotButtonClicked() {
    ChatBotWindow *chatBotWindow = new ChatBotWindow(this);
    chatBotWindow->setAttribute(Qt::WA_DeleteOnClose);
    chatBotWindow->show();
}

void MainWindow::onProfileButtonClicked()
{
    QModelIndex selectedIndex = ui->fournisseurTableWidget->currentIndex();
    if (selectedIndex.isValid()) {
        QString name = ui->fournisseurTableWidget->item(selectedIndex.row(), 1)->text();
        QString telephone = ui->fournisseurTableWidget->item(selectedIndex.row(), 2)->text();
        QString email = ui->fournisseurTableWidget->item(selectedIndex.row(), 3)->text();
        QString achatDate = ui->fournisseurTableWidget->item(selectedIndex.row(), 4)->text();
        QString logoPath = ui->fournisseurTableWidget->item(selectedIndex.row(), 5)->text();

        FournisseurProfileWindow *profileWindow = new FournisseurProfileWindow(this);
        profileWindow->setFournisseurDetails(name, telephone, email, achatDate, logoPath);
        profileWindow->setAttribute(Qt::WA_DeleteOnClose);
        profileWindow->show();
    } else {
        QMessageBox::warning(this, "Sélection invalide", "Veuillez sélectionner un fournisseur.");
    }
}

void MainWindow::updateStats()
{
    double totalPrixAchat = 0;
    double minPrixAchat = std::numeric_limits<double>::max();
    double maxPrixAchat = std::numeric_limits<double>::lowest();
    int count = 0;

    // Iterate through all rows in the table to calculate stats
    for (int row = 0; row < ui->fournisseurTableWidget->rowCount(); ++row) {
        QTableWidgetItem *prixAchatItem = ui->fournisseurTableWidget->item(row, 5); // Assuming column 5 holds prix_achat

        // Ensure the item is valid and numeric
        if (prixAchatItem && !prixAchatItem->text().isEmpty()) {
            bool ok;
            double prixAchat = prixAchatItem->text().toDouble(&ok);
            if (ok) {
                totalPrixAchat += prixAchat;
                minPrixAchat = std::min(minPrixAchat, prixAchat);
                maxPrixAchat = std::max(maxPrixAchat, prixAchat);
                count++;
            }
        }
    }

    // Avoid division by zero in case there are no valid rows
    if (count > 0) {
        double averagePrixAchat = totalPrixAchat / count;

        // Update the stats labels with the calculated values
        ui->totalPrixAchatLabel->setText(QString::number(totalPrixAchat));
        ui->averagePrixAchatLabel->setText(QString::number(averagePrixAchat));
        ui->minPrixAchatLabel->setText(QString::number(minPrixAchat));
        ui->maxPrixAchatLabel->setText(QString::number(maxPrixAchat));
    } else {
        // If no valid data is found
        ui->totalPrixAchatLabel->setText("N/A");
        ui->averagePrixAchatLabel->setText("N/A");
        ui->minPrixAchatLabel->setText("N/A");
        ui->maxPrixAchatLabel->setText("N/A");

        QMessageBox::warning(this, "No Data", "No valid data found in 'prix_achat'.");
    }
}

void MainWindow::onConvertButtonClicked()
{
    QModelIndex selectedIndex = ui->fournisseurTableWidget->currentIndex();
    if (!selectedIndex.isValid()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un fournisseur.");
        return;
    }

    // Assuming 'prix_achat' is in column 6 (index 5 in 0-based index)
    QTableWidgetItem* prixItem = ui->fournisseurTableWidget->item(selectedIndex.row(), 5);
    if (!prixItem) {
        QMessageBox::warning(this, "Erreur", "Prix d'achat non trouvé.");
        return;
    }

    bool ok;
    double prixAchat = prixItem->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Prix d'achat invalide.");
        return;
    }

    // Pass the prixAchat to ConvertisseurWindow
    ConvertisseurWindow* convertisseurWindow = new ConvertisseurWindow(prixAchat, this);
    convertisseurWindow->setAttribute(Qt::WA_DeleteOnClose);
    convertisseurWindow->show();
}

