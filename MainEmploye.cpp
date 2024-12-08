#include "MainEmploye.h"
#include "ui_MainEmploye.h"
#include "employe.h" // Include the employee class header
#include <QMessageBox> // For message dialogs
#include <QDebug>
#include <QWidget>  // Make sure this is included
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QMap>
#include <QDialog>
#include <QVBoxLayout>
#include <QString>
#include <QInputDialog>


MainEmploye::MainEmploye(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainEmploye)
{
    ui->setupUi(this);

    // Connect the "Ajouter" button to the onAjouterClicked() slot
    connect(ui->ajouterButton, &QPushButton::clicked, this, &MainEmploye::onAjouterClicked);

    // Connect the "Modifier" button to the on_modifierbut_clicked() slot
    connect(ui->modifierButton, &QPushButton::clicked, this, &MainEmploye::on_modifierbut_clicked);

    // Connect the "Supprimer" button to its slot
    connect(ui->supprimerButton, &QPushButton::clicked, this, &MainEmploye::on_supprimerClicked);

    // Connect the "Afficherr" button to its slot
    connect(ui->afficherButton, &QPushButton::clicked, this, &MainEmploye::afficherEmployes);

    connect(ui->searchButton, &QPushButton::clicked, this, &MainEmploye::on_searchButton_clicked);

    connect(ui->triButton, &QPushButton::clicked, this, &MainEmploye::on_triButton_clicked);

    // Connect the comboBox for sorting columns
    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainEmploye::on_sortComboBox_currentIndexChanged);

    connect(ui->exportPdfButton, &QPushButton::clicked, this, &MainEmploye::exportToPDF);

    connect(ui->statGenderButton, &QPushButton::clicked, this, &MainEmploye::generateGenderStatistics);






}

MainEmploye::~MainEmploye()
{
    delete ui;
}

// Slot function for the "Ajouter" button
/*void MainEmploye::onAjouterClicked()
{
    QString nom = ui->nomLineEdit->text();
    QString prenom = ui->prenomLineEdit->text();
    QString id = ui->idLineEdit->text();
    QString dateNaissance = ui->dateNaissanceDateEdit->date().toString("yyyy-MM-dd");
    QString genre = ui->genreLineEdit->text();
    QString numeroTel = ui->numeroTelLineEdit->text();
    QString adresse = ui->adresseLineEdit->text();
    QString poste = ui->posteLineEdit->text();
    QString salaire = ui->salaireLineEdit->text();
    QString dateEmbauche = ui->dateEmbaucheDateEdit->date().toString("yyyy-MM-dd");

    if (nom.isEmpty() || prenom.isEmpty() || id.isEmpty() || dateNaissance.isEmpty() ||
        genre.isEmpty() || numeroTel.isEmpty() || adresse.isEmpty() || poste.isEmpty() ||
        salaire.isEmpty() || dateEmbauche.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields before adding.");
        return;
    }

    Employe emp(nom, prenom, id, dateNaissance, genre, numeroTel, adresse, poste, salaire, dateEmbauche);

    if (emp.ajouter()) {
        QMessageBox::information(this, "Success", "Employee added successfully!");
    } else {
        QMessageBox::critical(this, "Error", "ID already used. Please use a unique ID.");
    }
}*/

void MainEmploye::onAjouterClicked()
{
    QString nom = ui->nomLineEdit->text();
    QString prenom = ui->prenomLineEdit->text();
    QString id = ui->idLineEdit->text();
    QString dateNaissance = ui->dateNaissanceDateEdit->date().toString("yyyy-MM-dd");
    QString genre = ui->genreLineEdit->text();
    QString numeroTel = ui->numeroTelLineEdit->text();
    QString adresse = ui->adresseLineEdit->text();
    QString poste = ui->posteLineEdit->text();
    QString salaire = ui->salaireLineEdit->text();
    QString dateEmbauche = ui->dateEmbaucheDateEdit->date().toString("yyyy-MM-dd");

    // Check if any field is empty
    if (nom.isEmpty() || prenom.isEmpty() || id.isEmpty() || dateNaissance.isEmpty() ||
        genre.isEmpty() || numeroTel.isEmpty() || adresse.isEmpty() || poste.isEmpty() ||
        salaire.isEmpty() || dateEmbauche.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields before adding.");
        return;
    }

    // Create the employee object
    Employe emp(nom, prenom, id, dateNaissance, genre, numeroTel, adresse, poste, salaire, dateEmbauche);

    // Attempt to add the employee and handle the result
    if (emp.ajouter()) {
        QMessageBox::information(this, "Success", "Employee added successfully!");
    }
}


void MainEmploye::on_modifierbut_clicked()
{
    QString id = ui->idLineEdit->text();
    QString nom = ui->nomLineEdit->text();
    QString prenom = ui->prenomLineEdit->text();
    QString dateNaissance = ui->dateNaissanceDateEdit->date().toString("yyyy-MM-dd");
    QString genre = ui->genreLineEdit->text();
    QString numeroTel = ui->numeroTelLineEdit->text();
    QString adresse = ui->adresseLineEdit->text();
    QString poste = ui->posteLineEdit->text();
    QString salaire = ui->salaireLineEdit->text();
    QString dateEmbauche = ui->dateEmbaucheDateEdit->date().toString("yyyy-MM-dd");

    if (id.isEmpty() || nom.isEmpty() || prenom.isEmpty() || dateNaissance.isEmpty() || genre.isEmpty() ||
        numeroTel.isEmpty() || adresse.isEmpty() || poste.isEmpty() || salaire.isEmpty() || dateEmbauche.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields before modifying.");
        return;
    }

    Employe emp(nom, prenom, id, dateNaissance, genre, numeroTel, adresse, poste, salaire, dateEmbauche);

    if (emp.modifier()) {
        QMessageBox::information(this, "Success", "Employee modified successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Employee with this ID does not exist.");
    }
}

void MainEmploye::on_supprimerClicked()
{
    // Get the ID from the input field
    QString id = ui->idLineEdit->text(); // Assuming ID is entered in a specific LineEdit field

    // Validate input
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter the employee ID to delete.");
        return;
    }

    // Ask for confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to delete this employee?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Attempt to delete the employee
        Employe emp; // Create an empty employee object to access the supprimer function
        if (emp.supprimer(id)) {
            QMessageBox::information(this, "Success", "Employee deleted successfully!");
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete employee. Ensure the ID exists.");
        }
    }
}

/*void MainEmploye::afficherEmployes() {
    Employe emp; // Create an instance of Employe
    ui->tableView->setModel(emp.afficher()); // Set the model to the tableView
}*/

void MainEmploye::afficherEmployes() {
    Employe emp; // Create an instance of Employe
    QSqlQueryModel* model = emp.afficher(); // Get the formatted model from the 'afficher' function
    ui->tableView->setModel(model); // Set the model to the tableView
}


void MainEmploye::on_searchButton_clicked() {
    QString searchText = ui->searchLineEdit->text();  // Get the text from the QLineEdit

    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter an ID or a name to search.");
        return;
    }

    Employe emp;  // Create an object of the Employe class
    QSqlQueryModel* model = emp.chercher(searchText);  // Get the search results (both ID and name)

    if (model->rowCount() > 0) {
        ui->tableView->setModel(model);  // Update the table view with the search results
    } else {
        QMessageBox::information(this, "Search Result", "No employee found with this ID or name.");
    }
}


void MainEmploye::on_triButton_clicked() {
    // Get the selected column from the ComboBox (either 'SALAIRE' or 'DATEEMBAUCHE')
    QString sortColumn = ui->sortComboBox->currentText();

    // Determine if the order is ascending or descending
    bool ascending = ui->radioButtonAsc->isChecked();

    // Create an instance of the Employe class
    Employe emp;

    // Call the tri() function to get the sorted model
    QSqlQueryModel *sortedModel = emp.tri(sortColumn, ascending);

    if (sortedModel != nullptr) {
        // Set the sorted model to the table view
        ui->tableView->setModel(sortedModel);
    } else {
        QMessageBox::critical(this, "Error", "Failed to sort employees.");
    }
}



void MainEmploye::on_sortComboBox_currentIndexChanged(int index)
{
      Q_UNUSED(index);
    // The logic for sorting goes here
    QString sortColumn = ui->sortComboBox->currentText();  // Assuming you want to sort based on ComboBox value
    bool ascending = true;  // You can set this based on a toggle or another input (e.g., another checkbox)

    QString queryStr = "SELECT * FROM EMPLOYE ORDER BY " + sortColumn;
    queryStr += ascending ? " ASC" : " DESC";  // Add ASC or DESC based on sorting preference

    qDebug() << "Executing query: " << queryStr;

    QSqlQuery query;
    query.prepare(queryStr);

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
    } else {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(std::move(query));  // Using move to avoid deprecation warning
        ui->tableView->setModel(model);
    }
}

void MainEmploye::exportToPDF() {
    // Open a file dialog to select the output PDF file
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter au format PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return; // User canceled the file dialog
    }

    // Ensure the file has a .pdf extension
    if (!filePath.endsWith(".pdf")) {
        filePath += ".pdf";
    }

    // Create a QTextDocument for PDF content
    QTextDocument document;

    // Prepare the HTML structure for the PDF
    QString htmlContent;
    htmlContent += "<html><body>";
    htmlContent += "<h1 style='text-align: center;'>Rapport de la base de données des employés</h1>";
    htmlContent += "<table border='1' cellspacing='0' cellpadding='4' style='width: 100%; border-collapse: collapse;'>";
    htmlContent += "<tr style='background-color: #f2f2f2;'>";
    htmlContent += "<th>ID</th><th>Nom</th><th>Date de Naissance</th><th>Genre</th><th>Numéro de Téléphone</th>";
    htmlContent += "<th>Adresse</th><th>Poste</th><th>Salaire</th><th>Date d'Embauche</th>";
    htmlContent += "</tr>";

    // Fetch data from the database
    QSqlQuery query;
    query.prepare("SELECT ID, NOM, PRENOM, DATENAISSANCE, GENRE, NUMEROTEL, ADRESSE, POSTE, SALAIRE, DATEEMBAUCHE FROM BOGH.EMPLOYE");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur de Base de Données", query.lastError().text());
        return;
    }

    // Populate the table with data
    while (query.next()) {
        QString id = query.value(0).toString();
        QString nom = query.value(1).toString() + " " + query.value(2).toString(); // Full name
        QString dateNaissance = query.value(3).toString();
        QString genre = query.value(4).toString();
        QString numTel = query.value(5).toString();
        QString adresse = query.value(6).toString();
        QString poste = query.value(7).toString();
        QString salaire = query.value(8).toString();
        QString dateEmbauche = query.value(9).toString();

        htmlContent += "<tr>";
        htmlContent += "<td>" + id + "</td>";
        htmlContent += "<td>" + nom + "</td>";
        htmlContent += "<td>" + dateNaissance + "</td>";
        htmlContent += "<td>" + genre + "</td>";
        htmlContent += "<td>" + numTel + "</td>";
        htmlContent += "<td>" + adresse + "</td>";
        htmlContent += "<td>" + poste + "</td>";
        htmlContent += "<td>" + salaire + "</td>";
        htmlContent += "<td>" + dateEmbauche + "</td>";
        htmlContent += "</tr>";
    }

    htmlContent += "</table>";
    htmlContent += "</body></html>";

    // Set the content in the QTextDocument
    document.setHtml(htmlContent);

    // Set up a QPrinter to output the PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    // Print the content to the PDF file
    document.print(&printer);

    // Display a success message
    QMessageBox::information(this, "Exportation Réussie", "PDF exporté avec succès à : " + filePath);

    // Prompt for SMS notification
    QString phoneNumber = QInputDialog::getText(this, "Recipient Phone Number", "Enter recipient phone number:");
    if (!phoneNumber.isEmpty()) {
        // Validate phone number format (basic validation)
        QRegularExpression phoneRegex("^\\+?[0-9]{10,15}$");
        QRegularExpressionMatch match = phoneRegex.match(phoneNumber);
        if (!match.hasMatch()) {
            QMessageBox::critical(this, "Invalid Phone Number", "Please enter a valid phone number.");
        } else {
            Employe employe; // Create an Employe instance
            employe.sendSMSNotification(phoneNumber);
        }
    }
}

void MainEmploye::generateGenderStatistics() {
    // Create a QMap to store the gender count
    QMap<QString, int> genderCount;

    // Query the database to get the gender data
    QSqlQuery query("SELECT UPPER(GENRE) AS StandardizedGender FROM BOGH.EMPLOYE");
    while (query.next()) {
        QString gender = query.value(0).toString();

        if (gender == "F") {
            genderCount["Female"]++;
        } else if (gender == "M") {
            genderCount["Male"]++;
        }
    }

    // If no data exists, show a message box
    if (genderCount.isEmpty()) {
        QMessageBox::information(this, "Statistics", "No gender data available.");
        return;
    }

    // Create a dialog to show the pie chart
    QDialog chartDialog(this);
    chartDialog.setWindowTitle("Employee Gender Statistics");

    // Create a custom widget to draw the pie chart
    QWidget* chartWidget = new QWidget(&chartDialog);
    chartWidget->setMinimumSize(400, 400);

    // Define the custom widget for drawing
    class PieChartWidget : public QWidget {
    public:
        PieChartWidget(QWidget* parent, const QMap<QString, int>& data)
            : QWidget(parent), genderCount(data) {}

    protected:
        void paintEvent(QPaintEvent* event) override {
            Q_UNUSED(event);

            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);

            int total = 0;
            for (auto count : genderCount.values()) {
                total += count;
            }

            if (total == 0) return;

            QRectF rect(20, 20, width() - 40, height() - 40);
            int startAngle = 0;

            // Draw each slice
            QMapIterator<QString, int> it(genderCount);
            while (it.hasNext()) {
                it.next();
                int angleSpan = static_cast<int>(360.0 * it.value() / total);
                painter.setBrush(it.key() == "Female" ? Qt::red : Qt::blue); // Assign colors
                painter.drawPie(rect, startAngle * 16, angleSpan * 16);

                startAngle += angleSpan;
            }

            // Add legend
            int legendY = height() - 50;
            painter.setPen(Qt::black);
            painter.setBrush(Qt::red);
            painter.drawRect(20, legendY, 20, 20);
            painter.drawText(45, legendY + 15, "Female");

            painter.setBrush(Qt::blue);
            painter.drawRect(120, legendY, 20, 20);
            painter.drawText(145, legendY + 15, "Male");
        }

    private:
        QMap<QString, int> genderCount;
    };

    // Create the chart widget and add it to the dialog
    PieChartWidget* pieChart = new PieChartWidget(chartWidget, genderCount);
    QVBoxLayout* layout = new QVBoxLayout(&chartDialog);
    layout->addWidget(pieChart);

    // Show the dialog
    chartDialog.resize(500, 500);
    chartDialog.exec();
}

