#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onLoginClicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username == "myuser" && password == "12345") {
        QMessageBox::information(this, "Login Successful", "Welcome!");
        accept(); // Ferme LoginWindow et renvoie QDialog::Accepted
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password. Please try again.");
    }
}
