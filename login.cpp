/*#include "login.h"
#include "ui_login.h" // Ensure the generated file exists
#include "MainEmploye.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

// Constructor
Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login) // Ensure Ui::Login is defined
{
    ui->setupUi(this);  // Setup UI
}

// Destructor
Login::~Login()
{
    delete ui;  // Clean up UI
}



// Login button clicked handler
void Login::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();  // Get username
    QString password = ui->lineEdit_password->text();  // Get password

    // Admin credentials (hardcoded for now)
    if (username == "admin" && password == "admin") {
        QMessageBox::information(this, "Login", "Admin login successful!");

        MainEmploye *mainEmploye = new MainEmploye();  // Open main window
        mainEmploye->setWindowTitle("Employee Management");
        mainEmploye->show();
        this->close(); // Close login window
        return;
    }

    // Database query for employee credentials
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYE WHERE NOM = :username AND PWD = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            QMessageBox::information(this, "Login", "Login successful!");

            MainEmploye *mainEmploye = new MainEmploye();
            mainEmploye->setWindowTitle("Employee Management");
            mainEmploye->show();
            this->close();
        } else {
            QMessageBox::warning(this, "Login", "Incorrect username or password.");
        }
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to execute query: " + query.lastError().text());
    }
}

// Log messages to a file
void Login::writeLog(const QString &message, const QString &category)
{
    QFile logFile("application.log");
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
            << " - [" << category << "] - " << message << "\n";
        logFile.close();
    } else {
        qDebug() << "Failed to open log file for writing.";
    }
}*/

#include "login.h"
#include "ui_login.h"
#include "MainEmploye.h" // Replace with your main window header file
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTimer>

// Constructor
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->pushButton_login, &QPushButton::clicked, this, &Login::on_pushButton_login_clicked);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

// Destructor
Login::~Login()
{
    delete ui;
}

// Login button clicked handler
/*void Login::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password.");
        return;
    }

    // Query to validate login credentials
    QSqlQuery query;
    query.prepare("SELECT POSTE FROM BOGH.EMPLOYE WHERE PRENOM = :username AND PWD = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        // Login successful
        QMessageBox::information(this, "Login", "Login successful!");

        // Retrieve the role (POSTE)
        QString poste = query.value("POSTE").toString();

        // Navigate to the appropriate interface based on the role
        if (poste == "Employe") {
            MainEmploye *mainEmploye = new MainEmploye();
            mainEmploye->setWindowTitle("Employee Service");
            mainEmploye->show();
        } else {
            QMessageBox::information(this, "Role", "Your role is: " + poste + ". Interface not implemented yet.");
        }

        this->close();  // Close the login dialog
    } else {
        // Login failed
        QMessageBox::warning(this, "Login Error", "Incorrect username or password.");
        qDebug() << "Database Error:" << query.lastError().text();
    }
}*/


#include <QTimer>

void Login::on_pushButton_login_clicked()
{
    // Disable the login button immediately to prevent multiple clicks during the login process
    ui->pushButton_login->setDisabled(true);

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password.");
        ui->pushButton_login->setEnabled(true);  // Re-enable the button
        return;
    }

    // Query to validate login credentials
    QSqlQuery query;
    query.prepare("SELECT POSTE FROM BOGH.EMPLOYE WHERE PRENOM = :username AND PWD = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        // Login successful
        // Avoid multiple login success messages by ensuring the code is executed only once
        QMessageBox::information(this, "Login", "Login successful!");

        // Retrieve the service/role (POSTE)
        QString poste = query.value("POSTE").toString();

        // Check if MainEmploye is already open
        if (poste == "Employe") {
            static MainEmploye *mainEmploye = nullptr;  // Static pointer to ensure only one instance
            if (!mainEmploye) {
                mainEmploye = new MainEmploye();
                mainEmploye->setWindowTitle("Employee Service");
                mainEmploye->show();
            } else {
                mainEmploye->raise();  // Bring the existing window to the front
                mainEmploye->activateWindow();  // Ensure it is focused
            }
        }

        this->close();  // Close the login dialog
    } else {
        // Login failed
        // Ensure this error message is not shown twice
        QMessageBox::warning(this, "Login Error", "Incorrect username or password.");
        qDebug() << "Database Error:" << query.lastError().text();
    }

    // Use QTimer::singleShot to re-enable the button after a short delay
    // This will ensure the button doesn't get re-enabled until the process is complete
    QTimer::singleShot(1000, [this](){
        ui->pushButton_login->setEnabled(true);
    });
}







