#include "chatbotwindow.h"
#include "ui_chatbotwindow.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QSslSocket>
#include <QDebug>

ChatBotWindow::ChatBotWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatBotWindow),
    networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatBotWindow::onSendButtonClicked);
    connect(networkManager, &QNetworkAccessManager::finished, this, &ChatBotWindow::handleApiResponse);
}

ChatBotWindow::~ChatBotWindow()
{
    delete ui;
    delete networkManager;
}

void ChatBotWindow::onSendButtonClicked() {
    QString userMessage = ui->userInputLineEdit->text();

    if (userMessage.isEmpty()) {
        ui->chatbotOutputLineEdit->setText("Veuillez entrer un message.");
        return;
    }

    qDebug() << "Supports SSL:" << QSslSocket::supportsSsl();
    qDebug() << "SSL Library Version:" << QSslSocket::sslLibraryVersionString();
    qDebug() << "SSL Library Build Version:" << QSslSocket::sslLibraryBuildVersionString();


    QUrl apiUrl("https://api.openai.com/v1/completions");
    QNetworkRequest request(apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer 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");

    QJsonObject jsonPayload;
    jsonPayload["model"] = "text-babbage-002";
    jsonPayload["prompt"] = userMessage;
    jsonPayload["max_tokens"] = 100;
    jsonPayload["temperature"] = 0.7;

    QJsonDocument jsonDoc(jsonPayload);
    networkManager->post(request, jsonDoc.toJson());

    ui->userInputLineEdit->clear();
}

void ChatBotWindow::handleApiResponse(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        ui->chatbotOutputLineEdit->setText("Erreur API : " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray choices = jsonObject["choices"].toArray();
    if (!choices.isEmpty()) {
        QString botResponse = choices[0].toObject()["text"].toString().trimmed();
        ui->chatbotOutputLineEdit->setText(botResponse);
    } else {
        ui->chatbotOutputLineEdit->setText("Aucune réponse du chatbot.");
    }

    reply->deleteLater();
}
