/********************************************************************************
** Form generated from reading UI file 'mailwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAILWINDOW_H
#define UI_MAILWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MailWindow
{
public:
    QLabel *label;
    QPushButton *sendMailButton;
    QLineEdit *subjectLineEdit;
    QLabel *label_2;
    QPushButton *browseBtn;
    QLineEdit *recipientLineEdit;
    QTextEdit *messageTextEdit;
    QLineEdit *attachmentLineEdit;

    void setupUi(QWidget *MailWindow)
    {
        if (MailWindow->objectName().isEmpty())
            MailWindow->setObjectName(QString::fromUtf8("MailWindow"));
        MailWindow->resize(730, 510);
        MailWindow->setStyleSheet(QString::fromUtf8("background-color: white;"));
        label = new QLabel(MailWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(2, -1, 731, 511));
        label->setStyleSheet(QString::fromUtf8("background-color: white;"));
        sendMailButton = new QPushButton(MailWindow);
        sendMailButton->setObjectName(QString::fromUtf8("sendMailButton"));
        sendMailButton->setGeometry(QRect(20, 470, 651, 31));
        QFont font;
        font.setBold(true);
        sendMailButton->setFont(font);
        sendMailButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        subjectLineEdit = new QLineEdit(MailWindow);
        subjectLineEdit->setObjectName(QString::fromUtf8("subjectLineEdit"));
        subjectLineEdit->setGeometry(QRect(20, 104, 651, 31));
        label_2 = new QLabel(MailWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 14, 91, 41));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79);color: white;\n"
"border-radius: 15px; "));
        browseBtn = new QPushButton(MailWindow);
        browseBtn->setObjectName(QString::fromUtf8("browseBtn"));
        browseBtn->setGeometry(QRect(597, 139, 75, 31));
        browseBtn->setFont(font);
        browseBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        recipientLineEdit = new QLineEdit(MailWindow);
        recipientLineEdit->setObjectName(QString::fromUtf8("recipientLineEdit"));
        recipientLineEdit->setGeometry(QRect(20, 70, 651, 31));
        messageTextEdit = new QTextEdit(MailWindow);
        messageTextEdit->setObjectName(QString::fromUtf8("messageTextEdit"));
        messageTextEdit->setGeometry(QRect(20, 176, 651, 291));
        attachmentLineEdit = new QLineEdit(MailWindow);
        attachmentLineEdit->setObjectName(QString::fromUtf8("attachmentLineEdit"));
        attachmentLineEdit->setGeometry(QRect(20, 140, 571, 31));

        retranslateUi(MailWindow);

        QMetaObject::connectSlotsByName(MailWindow);
    } // setupUi

    void retranslateUi(QWidget *MailWindow)
    {
        MailWindow->setWindowTitle(QCoreApplication::translate("MailWindow", "Form", nullptr));
        label->setText(QString());
        sendMailButton->setText(QCoreApplication::translate("MailWindow", "Envoyer", nullptr));
        subjectLineEdit->setPlaceholderText(QCoreApplication::translate("MailWindow", "Sujet", nullptr));
        label_2->setText(QCoreApplication::translate("MailWindow", "Mail :", nullptr));
        browseBtn->setText(QCoreApplication::translate("MailWindow", "Browse ...", nullptr));
        recipientLineEdit->setPlaceholderText(QCoreApplication::translate("MailWindow", "Destinataire", nullptr));
        messageTextEdit->setPlaceholderText(QCoreApplication::translate("MailWindow", "tapez votre message ...", nullptr));
        attachmentLineEdit->setPlaceholderText(QCoreApplication::translate("MailWindow", "attachement", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MailWindow: public Ui_MailWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAILWINDOW_H
