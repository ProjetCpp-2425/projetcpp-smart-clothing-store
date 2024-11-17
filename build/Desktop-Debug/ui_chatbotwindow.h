/********************************************************************************
** Form generated from reading UI file 'chatbotwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATBOTWINDOW_H
#define UI_CHATBOTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatBotWindow
{
public:
    QLineEdit *userInputLineEdit;
    QLabel *label;
    QPushButton *sendButton;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *chatbotOutputLineEdit;

    void setupUi(QWidget *ChatBotWindow)
    {
        if (ChatBotWindow->objectName().isEmpty())
            ChatBotWindow->setObjectName(QString::fromUtf8("ChatBotWindow"));
        ChatBotWindow->resize(432, 397);
        userInputLineEdit = new QLineEdit(ChatBotWindow);
        userInputLineEdit->setObjectName(QString::fromUtf8("userInputLineEdit"));
        userInputLineEdit->setGeometry(QRect(20, 100, 261, 51));
        label = new QLabel(ChatBotWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 141, 41));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79);color: white;\n"
"border-radius: 15px; "));
        sendButton = new QPushButton(ChatBotWindow);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(310, 110, 83, 31));
        QFont font1;
        font1.setBold(true);
        sendButton->setFont(font1);
        sendButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        label_2 = new QLabel(ChatBotWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 70, 63, 20));
        label_3 = new QLabel(ChatBotWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 160, 63, 20));
        chatbotOutputLineEdit = new QLineEdit(ChatBotWindow);
        chatbotOutputLineEdit->setObjectName(QString::fromUtf8("chatbotOutputLineEdit"));
        chatbotOutputLineEdit->setGeometry(QRect(20, 190, 391, 181));
        chatbotOutputLineEdit->setReadOnly(true);

        retranslateUi(ChatBotWindow);

        QMetaObject::connectSlotsByName(ChatBotWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatBotWindow)
    {
        ChatBotWindow->setWindowTitle(QCoreApplication::translate("ChatBotWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("ChatBotWindow", "Chat Bot :", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatBotWindow", "Envoyer", nullptr));
        label_2->setText(QCoreApplication::translate("ChatBotWindow", "Entr\303\251e :", nullptr));
        label_3->setText(QCoreApplication::translate("ChatBotWindow", "Sortie :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatBotWindow: public Ui_ChatBotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATBOTWINDOW_H
