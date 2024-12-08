#include "FournisseurProfileWindow.h"
#include "ui_FournisseurProfileWindow.h"
#include <QPixmap>
#include <QFileInfo>

FournisseurProfileWindow::FournisseurProfileWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FournisseurProfileWindow)
{
    ui->setupUi(this);
}

FournisseurProfileWindow::~FournisseurProfileWindow()
{
    delete ui;
}

void FournisseurProfileWindow::setFournisseurDetails(const QString &name, const QString &telephone, const QString &email, const QString &achatDate, const QString &logoPath)
{
    ui->nameLabel->setText(name);
    ui->telephoneLabel->setText(telephone);
    ui->emailLabel->setText(email);
    ui->achatDateLabel->setText(achatDate);

    // Load the logo
    if (QFileInfo::exists(logoPath)) {
        QPixmap pixmap(logoPath);
        ui->logoLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    } else {
        ui->logoLabel->setText("Logo not available");
    }
}
