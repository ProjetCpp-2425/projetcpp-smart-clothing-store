#include "mailwindow.h"
#include "ui_mailwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MailWindow::MailWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MailWindow)
{
    ui->setupUi(this);

    connect(ui->attachmentLineEdit, &QLineEdit::cursorPositionChanged, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Choisir un fichier", "", "Tous les fichiers (*)");
        if (!filePath.isEmpty()) {
            ui->attachmentLineEdit->setText(filePath);
        }
    });
}

MailWindow::~MailWindow()
{
    delete ui;
}

void MailWindow::onSendMailButtonClicked() {
    QString recipient = ui->recipientLineEdit->text();
    QString subject = ui->subjectLineEdit->text();
    QString attachment = ui->attachmentLineEdit->text();
    QString message = ui->messageTextEdit->toPlainText();

    if (recipient.isEmpty() || subject.isEmpty() || message.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs requis.");
        return;
    }

    qDebug() << "Envoi du mail...";
    qDebug() << "Destinataire :" << recipient;
    qDebug() << "Sujet :" << subject;
    qDebug() << "Pièce jointe :" << attachment;
    qDebug() << "Message :" << message;

    QMessageBox::information(this, "Mail envoyé", "Le mail a été envoyé avec succès !");
}

void MailWindow::onAttachmentBrowseButtonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Sélectionnez une pièce jointe", "", "Tous les fichiers (*.*)");
    if (!filePath.isEmpty()) {
        ui->attachmentLineEdit->setText(filePath);
    }
}
