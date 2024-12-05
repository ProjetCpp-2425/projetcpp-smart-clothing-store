#include "FournisseurProfileWindow.h"
#include <QVBoxLayout>
#include <QLabel>

FournisseurProfileWindow::FournisseurProfileWindow(QWidget *parent)
    : QWidget(parent),
    nameLabel(new QLabel(this)),
    telephoneLabel(new QLabel(this)),
    emailLabel(new QLabel(this)),
    achatDateLabel(new QLabel(this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(telephoneLabel);
    layout->addWidget(emailLabel);
    layout->addWidget(achatDateLabel);
}

void FournisseurProfileWindow::setFournisseurDetails(const QString& name, const QString& telephone, const QString& email, const QString& achatDate)
{
    nameLabel->setText("Nom: " + name);
    telephoneLabel->setText("Téléphone: " + telephone);
    emailLabel->setText("Email: " + email);
    achatDateLabel->setText("Date d'achat: " + achatDate);
}
