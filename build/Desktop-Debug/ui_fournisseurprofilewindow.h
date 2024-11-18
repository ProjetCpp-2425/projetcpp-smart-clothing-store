/********************************************************************************
** Form generated from reading UI file 'fournisseurprofilewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOURNISSEURPROFILEWINDOW_H
#define UI_FOURNISSEURPROFILEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FournisseurProfileWindow
{
public:
    QLabel *label;
    QLabel *label_3;
    QLabel *nameLabel;
    QLabel *emailLabel;
    QLabel *telephoneLabel;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *achatDateLabel;
    QLabel *label_4;
    QLabel *label_6;

    void setupUi(QWidget *FournisseurProfileWindow)
    {
        if (FournisseurProfileWindow->objectName().isEmpty())
            FournisseurProfileWindow->setObjectName(QString::fromUtf8("FournisseurProfileWindow"));
        FournisseurProfileWindow->resize(400, 300);
        FournisseurProfileWindow->setStyleSheet(QString::fromUtf8("background-color: white;"));
        label = new QLabel(FournisseurProfileWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 401, 301));
        label->setStyleSheet(QString::fromUtf8("background-color: white;"));
        label_3 = new QLabel(FournisseurProfileWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 140, 81, 31));
        label_3->setStyleSheet(QString::fromUtf8("color: black;"));
        nameLabel = new QLabel(FournisseurProfileWindow);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(150, 100, 181, 31));
        nameLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        emailLabel = new QLabel(FournisseurProfileWindow);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));
        emailLabel->setGeometry(QRect(150, 180, 181, 31));
        emailLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        telephoneLabel = new QLabel(FournisseurProfileWindow);
        telephoneLabel->setObjectName(QString::fromUtf8("telephoneLabel"));
        telephoneLabel->setGeometry(QRect(150, 140, 181, 31));
        telephoneLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        label_5 = new QLabel(FournisseurProfileWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 230, 91, 31));
        label_5->setStyleSheet(QString::fromUtf8("color: black;"));
        label_2 = new QLabel(FournisseurProfileWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 20, 121, 41));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79);color: white;\n"
"border-radius: 15px; "));
        achatDateLabel = new QLabel(FournisseurProfileWindow);
        achatDateLabel->setObjectName(QString::fromUtf8("achatDateLabel"));
        achatDateLabel->setGeometry(QRect(150, 230, 181, 31));
        achatDateLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        label_4 = new QLabel(FournisseurProfileWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 180, 63, 31));
        label_4->setStyleSheet(QString::fromUtf8("color: black;"));
        label_6 = new QLabel(FournisseurProfileWindow);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 100, 63, 20));
        label_6->setStyleSheet(QString::fromUtf8("color: black;"));

        retranslateUi(FournisseurProfileWindow);

        QMetaObject::connectSlotsByName(FournisseurProfileWindow);
    } // setupUi

    void retranslateUi(QWidget *FournisseurProfileWindow)
    {
        FournisseurProfileWindow->setWindowTitle(QCoreApplication::translate("FournisseurProfileWindow", "Form", nullptr));
        label->setText(QString());
        label_3->setText(QCoreApplication::translate("FournisseurProfileWindow", "Telephone :", nullptr));
        nameLabel->setText(QString());
        emailLabel->setText(QString());
        telephoneLabel->setText(QString());
        label_5->setText(QCoreApplication::translate("FournisseurProfileWindow", "Date achat :", nullptr));
        label_2->setText(QCoreApplication::translate("FournisseurProfileWindow", " Profile :", nullptr));
        achatDateLabel->setText(QString());
        label_4->setText(QCoreApplication::translate("FournisseurProfileWindow", "Email :", nullptr));
        label_6->setText(QCoreApplication::translate("FournisseurProfileWindow", "Nom :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FournisseurProfileWindow: public Ui_FournisseurProfileWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOURNISSEURPROFILEWINDOW_H
