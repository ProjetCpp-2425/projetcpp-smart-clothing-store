#include "convertisseurwindow.h"
#include "ui_convertisseurwindow.h"
#include <QMessageBox>

const double EUR_to_TND = 3.2;
const double USD_to_TND = 3.0;
const double TND_to_EUR = 1 / EUR_to_TND;
const double TND_to_USD = 1 / USD_to_TND;

ConvertisseurWindow::ConvertisseurWindow(double prixAchat, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ConvertisseurWindow),
    prixAchat(prixAchat)
{
    ui->setupUi(this);

    ui->amountLineEdit->setText(QString::number(prixAchat));

    connect(ui->convertButton, &QPushButton::clicked, this, &ConvertisseurWindow::convertCurrency);
}

ConvertisseurWindow::~ConvertisseurWindow()
{
    delete ui;
}

void ConvertisseurWindow::convertCurrency()
{
    QString sourceCurrency = ui->sourceCurrencyComboBox->currentText();
    QString targetCurrency = ui->targetCurrencyComboBox->currentText();

    double convertedAmount = 0.0;

    if (sourceCurrency == "EUR" && targetCurrency == "TND") {
        convertedAmount = prixAchat * EUR_to_TND;
    } else if (sourceCurrency == "USD" && targetCurrency == "TND") {
        convertedAmount = prixAchat * USD_to_TND;
    } else if (sourceCurrency == "TND" && targetCurrency == "EUR") {
        convertedAmount = prixAchat * TND_to_EUR;
    } else if (sourceCurrency == "TND" && targetCurrency == "USD") {
        convertedAmount = prixAchat * TND_to_USD;
    } else {
        QMessageBox::warning(this, "Erreur", "Conversion non prise en charge.");
        return;
    }

    // Display the converted amount in a label or message box
    ui->resultLabel->setText(QString::number(convertedAmount, 'f', 2) + " " + targetCurrency);
}
