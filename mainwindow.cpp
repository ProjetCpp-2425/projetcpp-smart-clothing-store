#include "mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPdfWriter>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QImage>
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
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);

    QColor backgroundColor(250, 250, 250);
    painter.fillRect(0, 0, pdfWriter.width(), pdfWriter.height(), backgroundColor);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20, QFont::Bold));
    painter.drawText(QRect(0, 20, pdfWriter.width(), 50), Qt::AlignCenter, "Master App - Structura");

    QPixmap logo("C:/Users/user/Documents/InterfaceFournisseur/Structura.png");
    QImage logoImage = logo.toImage();
    int logoWidth = 300, logoHeight = 300;
    painter.drawImage(50, 20, logoImage.scaled(logoWidth, logoHeight));

    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(QRect(0, 350, pdfWriter.width(), 30), Qt::AlignCenter, "Liste des Fournisseurs");

    int x = 50, y = 400;
    int columnWidth = 400, rowHeight = 80;

    QColor headerColor(100, 150, 255);
    QColor rowColor(255, 255, 255);
    QColor rowAltColor(240, 240, 240);

    if (y + rowHeight > pdfWriter.height()) {
        pdfWriter.newPage();
        y = 50;
    }

    painter.setBrush(headerColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(x, y, 5 * columnWidth, rowHeight);
    painter.setPen(Qt::white);
    painter.drawText(x + 10, y + 40, "ID");
    painter.drawText(x + columnWidth + 10, y + 40, "Nom");
    painter.drawText(x + 2 * columnWidth + 10, y + 40, "Date Achat");
    painter.drawText(x + 3 * columnWidth + 10, y + 40, "Telephone");
    painter.drawText(x + 4 * columnWidth + 10, y + 40, "Email");

    y += rowHeight;

    Fournisseur F;
    QSqlQueryModel *model = F.getFournisseurs();

    painter.setFont(QFont("Arial", 12));
    for (int row = 0; row < model->rowCount(); ++row) {
        painter.setBrush((row % 2 == 0) ? rowColor : rowAltColor);
        painter.setPen(Qt::NoPen);
        painter.drawRect(x, y, 5 * columnWidth, rowHeight);

        QString id = model->data(model->index(row, 0)).toString();
        QString name = model->data(model->index(row, 1)).toString();
        QString telephone = model->data(model->index(row, 3)).toString();
        QString email = model->data(model->index(row, 4)).toString();
        QString achatDate = model->data(model->index(row, 2)).toDate().toString("yyyy-MM-dd");

        painter.setPen(Qt::black);
        painter.drawText(x + 10, y + 40, id);
        painter.drawText(x + columnWidth + 10, y + 40, name);
        painter.drawText(x + 2 * columnWidth + 10, y + 40, achatDate);
        painter.drawText(x + 3 * columnWidth + 10, y + 40, telephone);
        painter.drawText(x + 4 * columnWidth + 10, y + 40, email);

        y += rowHeight;
    }

    painter.end();
    QMessageBox::information(this, "Exportation réussie", "Les données ont été exportées en PDF avec succès !");
}

void MainWindow::onSearchFournisseurClicked() {
    qDebug() << "button clicked";
    QString searchQuery = ui->searchLineEdit->text();

    if (searchQuery.isEmpty()) {
        QMessageBox::warning(this, "Recherche vide", "Veuillez entrer un critère de recherche.");
        onDisplayFournisseursClicked();
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
        onDisplayFournisseursClicked();
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

    // Prepare the query safely
    QSqlQuery query;
    if (sortCriteria == "name") {
        query.prepare("SELECT * FROM fournisseurs ORDER BY name ASC");
    } else if (sortCriteria == "id") {
        query.prepare("SELECT * FROM fournisseurs ORDER BY id ASC");
    }

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur de tri", "Le tri a échoué : " + query.lastError().text());
        return;
    }

    ui->fournisseurTableWidget->clearContents();
    ui->fournisseurTableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->fournisseurTableWidget->insertRow(row);
        ui->fournisseurTableWidget->setItem(row, 0, new QTableWidgetItem(query.value("name").toString()));
        ui->fournisseurTableWidget->setItem(row, 1, new QTableWidgetItem(query.value("id").toString()));
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

        FournisseurProfileWindow* profileWindow = new FournisseurProfileWindow();
        profileWindow->setFournisseurDetails(name, telephone, email, achatDate);
        profileWindow->setAttribute(Qt::WA_DeleteOnClose);
        profileWindow->show();
    } else {
        QMessageBox::warning(this, "Sélection invalide", "Veuillez sélectionner un fournisseur.");
    }
}

void MainWindow::onConvertButtonClicked() {
    ConvertisseurWindow *convertisseurWindow = new ConvertisseurWindow(this);
    convertisseurWindow->setAttribute(Qt::WA_DeleteOnClose);
    convertisseurWindow->show();
}

void MainWindow::on_updateButton_2_clicked()
{
    QDate filterDate = ui->dateFilterEdit->date();

    QSqlQueryModel* model = Fournisseur::filterByDate(filterDate);
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

        QMessageBox::information(this, "Filter Applied", "Fournisseurs filtered by date: " + filterDate.toString("yyyy-MM-dd"));
    } else {
        QMessageBox::warning(this, "Filter Error", "No fournisseurs found for the selected date.");
    }
}

