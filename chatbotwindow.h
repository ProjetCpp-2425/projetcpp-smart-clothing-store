#ifndef CHATBOTWINDOW_H
#define CHATBOTWINDOW_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class ChatBotWindow;
}

class ChatBotWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatBotWindow(QWidget *parent = nullptr);
    ~ChatBotWindow();

private slots:
    void onSendButtonClicked();
    void handleApiResponse(QNetworkReply *reply);

private:
    Ui::ChatBotWindow *ui;
    QNetworkAccessManager *networkManager;
};

#endif // CHATBOTWINDOW_H

