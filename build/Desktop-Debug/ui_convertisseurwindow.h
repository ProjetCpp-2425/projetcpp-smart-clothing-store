/********************************************************************************
** Form generated from reading UI file 'convertisseurwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONVERTISSEURWINDOW_H
#define UI_CONVERTISSEURWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConvertisseurWindow
{
public:
    QLabel *label;
    QLabel *label_3;
    QComboBox *sourceCurrencyComboBox;
    QLabel *label_2;
    QLabel *label_4;
    QPushButton *convertButton;
    QLabel *label_5;
    QLabel *resultLabel;
    QComboBox *targetCurrencyComboBox;
    QLineEdit *amountLineEdit;

    void setupUi(QWidget *ConvertisseurWindow)
    {
        if (ConvertisseurWindow->objectName().isEmpty())
            ConvertisseurWindow->setObjectName(QString::fromUtf8("ConvertisseurWindow"));
        ConvertisseurWindow->resize(400, 300);
        ConvertisseurWindow->setStyleSheet(QString::fromUtf8("background-color:white;"));
        label = new QLabel(ConvertisseurWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 401, 301));
        label->setStyleSheet(QString::fromUtf8("background-color: white;"));
        label_3 = new QLabel(ConvertisseurWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 130, 151, 31));
        label_3->setStyleSheet(QString::fromUtf8("color: black;"));
        sourceCurrencyComboBox = new QComboBox(ConvertisseurWindow);
        sourceCurrencyComboBox->addItem(QString());
        sourceCurrencyComboBox->addItem(QString());
        sourceCurrencyComboBox->setObjectName(QString::fromUtf8("sourceCurrencyComboBox"));
        sourceCurrencyComboBox->setGeometry(QRect(200, 130, 82, 28));
        sourceCurrencyComboBox->setStyleSheet(QString::fromUtf8("color: black;"));
        label_2 = new QLabel(ConvertisseurWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 80, 141, 31));
        label_2->setStyleSheet(QString::fromUtf8("color: black;"));
        label_4 = new QLabel(ConvertisseurWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 180, 151, 31));
        label_4->setStyleSheet(QString::fromUtf8("color: black;"));
        convertButton = new QPushButton(ConvertisseurWindow);
        convertButton->setObjectName(QString::fromUtf8("convertButton"));
        convertButton->setGeometry(QRect(40, 240, 101, 31));
        QFont font;
        font.setBold(true);
        convertButton->setFont(font);
        convertButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        label_5 = new QLabel(ConvertisseurWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 20, 341, 41));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79);color: white;\n"
"border-radius: 15px; "));
        resultLabel = new QLabel(ConvertisseurWindow);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        resultLabel->setGeometry(QRect(190, 239, 141, 31));
        resultLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        targetCurrencyComboBox = new QComboBox(ConvertisseurWindow);
        targetCurrencyComboBox->addItem(QString());
        targetCurrencyComboBox->addItem(QString());
        targetCurrencyComboBox->addItem(QString());
        targetCurrencyComboBox->setObjectName(QString::fromUtf8("targetCurrencyComboBox"));
        targetCurrencyComboBox->setGeometry(QRect(200, 180, 82, 28));
        targetCurrencyComboBox->setStyleSheet(QString::fromUtf8("color: black;"));
        amountLineEdit = new QLineEdit(ConvertisseurWindow);
        amountLineEdit->setObjectName(QString::fromUtf8("amountLineEdit"));
        amountLineEdit->setGeometry(QRect(200, 80, 113, 28));

        retranslateUi(ConvertisseurWindow);

        QMetaObject::connectSlotsByName(ConvertisseurWindow);
    } // setupUi

    void retranslateUi(QWidget *ConvertisseurWindow)
    {
        ConvertisseurWindow->setWindowTitle(QCoreApplication::translate("ConvertisseurWindow", "Form", nullptr));
        label->setText(QString());
        label_3->setText(QCoreApplication::translate("ConvertisseurWindow", "Devise source :", nullptr));
        sourceCurrencyComboBox->setItemText(0, QCoreApplication::translate("ConvertisseurWindow", "EUR", nullptr));
        sourceCurrencyComboBox->setItemText(1, QCoreApplication::translate("ConvertisseurWindow", "USD", nullptr));

        label_2->setText(QCoreApplication::translate("ConvertisseurWindow", "Montant \303\240 convertir :", nullptr));
        label_4->setText(QCoreApplication::translate("ConvertisseurWindow", "Devise cible :", nullptr));
        convertButton->setText(QCoreApplication::translate("ConvertisseurWindow", "Convertir", nullptr));
        label_5->setText(QCoreApplication::translate("ConvertisseurWindow", "Convertisseur de Devise :", nullptr));
        resultLabel->setText(QString());
        targetCurrencyComboBox->setItemText(0, QCoreApplication::translate("ConvertisseurWindow", "TND", nullptr));
        targetCurrencyComboBox->setItemText(1, QCoreApplication::translate("ConvertisseurWindow", "EUR", nullptr));
        targetCurrencyComboBox->setItemText(2, QCoreApplication::translate("ConvertisseurWindow", "USD", nullptr));

    } // retranslateUi

};

namespace Ui {
    class ConvertisseurWindow: public Ui_ConvertisseurWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONVERTISSEURWINDOW_H
