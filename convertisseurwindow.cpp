#include "convertisseurwindow.h"
#include "ui_convertisseurwindow.h"
#include <QMessageBox>

const double EUR_to_TND = 3.2;
const double USD_to_TND = 3.0;
const double TND_to_EUR = 1 / EUR_to_TND;
const double TND_to_USD = 1 / USD_to_TND;

ConvertisseurWindow::ConvertisseurWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConvertisseurWindow)
{
    ui->setupUi(this);

    connect(ui->convertButton, &QPushButton::clicked, this, &ConvertisseurWindow::convertCurrency);
}

ConvertisseurWindow::~ConvertisseurWindow()
{
    delete ui;
}

void ConvertisseurWindow::convertCurrency()
{
    bool ok;
    double amount = ui->amountLineEdit->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un montant valide.");
        return;
    }

    QString sourceCurrency = ui->sourceCurrencyComboBox->currentText();
    QString targetCurrency = ui->targetCurrencyComboBox->currentText();

    double convertedAmount = 0.0;

    if (sourceCurrency == "EUR" && targetCurrency == "TND") {
        convertedAmount = amount * EUR_to_TND;
    } else if (sourceCurrency == "USD" && targetCurrency == "TND") {
        convertedAmount = amount * USD_to_TND;
    } else if (sourceCurrency == "TND" && targetCurrency == "EUR") {
        convertedAmount = amount * TND_to_EUR;
    } else if (sourceCurrency == "TND" && targetCurrency == "USD") {
        convertedAmount = amount * TND_to_USD;
    }

    ui->resultLabel->setText(QString::number(convertedAmount));
}
