#include "mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QSqlQueryModel>
#include <QFileDialog>
#include "./ui_mainwindow.h"
#include "fournisseur.h"
#include "mailwindow.h"
#include "qsqlerror.h"
#include "chatbotwindow.h"
#include "ui_mailwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddFournisseurClicked);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateFournisseurClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteFournisseurClicked);
    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::onDisplayFournisseursClicked);
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

    if (f.addFournisseur(id, name, telephone, email, achatDate)) {
        QMessageBox::information(this, "Success", "Fournisseur added successfully!");
        onDisplayFournisseursClicked();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add fournisseur.");
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

    if (f.updateFournisseur(id, name, telephone, email, achatDate)) {
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
    if (model) {
        ui->fournisseurTableWidget->clear();
        ui->fournisseurTableWidget->setRowCount(model->rowCount());
        ui->fournisseurTableWidget->setColumnCount(model->columnCount());

        for (int col = 0; col < model->columnCount(); ++col) {
            ui->fournisseurTableWidget
                ->setHorizontalHeaderItem(col, new QTableWidgetItem(model->headerData(col, Qt::Horizontal).toString()));
        }

        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); ++col) {
                QString cellData = model->data(model->index(row, col)).toString();
                ui->fournisseurTableWidget->setItem(row, col, new QTableWidgetItem(cellData));
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to display fournisseurs.");
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

void MainWindow::onSearchButtonClicked() {
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

void MailWindow::onAttachmentBrowseButtonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Sélectionnez une pièce jointe", "", "Tous les fichiers (*.*)");
    if (!filePath.isEmpty()) {
        ui->attachmentLineEdit->setText(filePath);
    }
}

void MainWindow::onChatBotButtonClicked() {
    ChatBotWindow *chatBotWindow = new ChatBotWindow(this);
    chatBotWindow->setAttribute(Qt::WA_DeleteOnClose);
    chatBotWindow->show();
}
