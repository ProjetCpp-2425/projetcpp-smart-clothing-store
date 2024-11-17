/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QRadioButton *sortByNameRadioButton;
    QTableWidget *fournisseurTableWidget;
    QLabel *label_8;
    QPushButton *exportPdfButton;
    QPushButton *searchButton;
    QPushButton *addButton;
    QPushButton *updateButton;
    QLineEdit *searchLineEdit;
    QPushButton *refreshButton;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLineEdit *nameLineEdit;
    QLineEdit *emailLineEdit;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_9;
    QDateEdit *achatDateEdit;
    QLineEdit *telephoneLineEdit;
    QLabel *label_13;
    QLabel *label_11;
    QLineEdit *idLineEdit;
    QLabel *label_15;
    QPushButton *deleteButton;
    QPushButton *sortButton;
    QLabel *label_16;
    QRadioButton *sortByIdRadioButton;
    QLabel *label_14;
    QPushButton *mailButton;
    QPushButton *chatBotButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(942, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sortByNameRadioButton = new QRadioButton(centralwidget);
        sortByNameRadioButton->setObjectName(QString::fromUtf8("sortByNameRadioButton"));
        sortByNameRadioButton->setGeometry(QRect(280, 340, 112, 26));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(0, 0, 0, 128));
        brush2.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        sortByNameRadioButton->setPalette(palette);
        sortByNameRadioButton->setStyleSheet(QString::fromUtf8("color: black;"));
        fournisseurTableWidget = new QTableWidget(centralwidget);
        if (fournisseurTableWidget->columnCount() < 5)
            fournisseurTableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        fournisseurTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        fournisseurTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        fournisseurTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        fournisseurTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        fournisseurTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        if (fournisseurTableWidget->rowCount() < 16)
            fournisseurTableWidget->setRowCount(16);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(4, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(5, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(6, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(7, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(8, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(9, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(10, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(11, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(12, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(13, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(14, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        fournisseurTableWidget->setVerticalHeaderItem(15, __qtablewidgetitem20);
        QFont font;
        font.setPointSize(8);
        font.setBold(false);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        __qtablewidgetitem21->setFont(font);
        fournisseurTableWidget->setItem(0, 0, __qtablewidgetitem21);
        fournisseurTableWidget->setObjectName(QString::fromUtf8("fournisseurTableWidget"));
        fournisseurTableWidget->setGeometry(QRect(470, 140, 421, 361));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        fournisseurTableWidget->setFont(font1);
        fournisseurTableWidget->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
" background: rgb(228,224,223);\n"
" color: black;\n"
"}\n"
"\n"
"QTableWidget {\n"
"	background: rgb(228,224,223);\n"
"	font: 75 10pt \"Arial\";\n"
"}"));
        fournisseurTableWidget->setFrameShape(QFrame::StyledPanel);
        fournisseurTableWidget->setShowGrid(true);
        fournisseurTableWidget->setGridStyle(Qt::SolidLine);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(780, 0, 151, 141));
        label_8->setPixmap(QPixmap(QString::fromUtf8("Structura.png")));
        label_8->setScaledContents(true);
        exportPdfButton = new QPushButton(centralwidget);
        exportPdfButton->setObjectName(QString::fromUtf8("exportPdfButton"));
        exportPdfButton->setGeometry(QRect(270, 450, 101, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        QBrush brush3(QColor(13, 33, 79, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush3);
        QBrush brush4(QColor(255, 255, 255, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        QBrush brush5(QColor(255, 255, 255, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        QBrush brush6(QColor(255, 255, 255, 128));
        brush6.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush6);
#endif
        exportPdfButton->setPalette(palette1);
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(true);
        exportPdfButton->setFont(font2);
        exportPdfButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(360, 210, 91, 31));
        searchButton->setFont(font2);
        searchButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(170, 510, 81, 31));
        addButton->setFont(font2);
        addButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        updateButton = new QPushButton(centralwidget);
        updateButton->setObjectName(QString::fromUtf8("updateButton"));
        updateButton->setGeometry(QRect(790, 510, 91, 31));
        updateButton->setFont(font2);
        updateButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(280, 160, 171, 31));
        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        refreshButton->setGeometry(QRect(20, 510, 90, 31));
        refreshButton->setFont(font2);
        refreshButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 170, 251, 331));
        QPalette palette2;
        QBrush brush7(QColor(228, 224, 223, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush7);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush7);
        frame->setPalette(palette2);
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        frame->setFont(font3);
        frame->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    background-color: rgb(228,224,223); \n"
"    border-radius: 15px;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background-color: rgb(255, 255, 255);\n"
"    color: black;\n"
"}\n"
""));
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        nameLineEdit = new QLineEdit(frame);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        gridLayout->addWidget(nameLineEdit, 0, 1, 1, 2);

        emailLineEdit = new QLineEdit(frame);
        emailLineEdit->setObjectName(QString::fromUtf8("emailLineEdit"));

        gridLayout->addWidget(emailLineEdit, 4, 2, 1, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font3);
        label_10->setStyleSheet(QString::fromUtf8("color: black;"));

        gridLayout->addWidget(label_10, 1, 0, 1, 1);

        label_12 = new QLabel(frame);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font3);
        label_12->setStyleSheet(QString::fromUtf8("color: black;"));

        gridLayout->addWidget(label_12, 3, 0, 1, 1);

        label_9 = new QLabel(frame);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font3);
        label_9->setStyleSheet(QString::fromUtf8("color: black;"));

        gridLayout->addWidget(label_9, 0, 0, 1, 1);

        achatDateEdit = new QDateEdit(frame);
        achatDateEdit->setObjectName(QString::fromUtf8("achatDateEdit"));

        gridLayout->addWidget(achatDateEdit, 2, 2, 1, 1);

        telephoneLineEdit = new QLineEdit(frame);
        telephoneLineEdit->setObjectName(QString::fromUtf8("telephoneLineEdit"));

        gridLayout->addWidget(telephoneLineEdit, 3, 2, 1, 1);

        label_13 = new QLabel(frame);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font3);
        label_13->setStyleSheet(QString::fromUtf8("color: black;"));

        gridLayout->addWidget(label_13, 4, 0, 1, 1);

        label_11 = new QLabel(frame);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font3);
        label_11->setStyleSheet(QString::fromUtf8("color: black;"));

        gridLayout->addWidget(label_11, 2, 0, 1, 1);

        idLineEdit = new QLineEdit(frame);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));

        gridLayout->addWidget(idLineEdit, 1, 2, 1, 1);

        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(20, 120, 211, 31));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        label_15->setFont(font4);
        label_15->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); border-radius: 15px; \n"
"color: white;"));
        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(670, 510, 91, 31));
        deleteButton->setFont(font2);
        deleteButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        sortButton = new QPushButton(centralwidget);
        sortButton->setObjectName(QString::fromUtf8("sortButton"));
        sortButton->setGeometry(QRect(280, 300, 101, 31));
        QFont font5;
        font5.setBold(true);
        sortButton->setFont(font5);
        sortButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(480, 90, 241, 31));
        label_16->setFont(font4);
        label_16->setStyleSheet(QString::fromUtf8(" background-color: rgb(5, 16, 66); \n"
"border-radius: 15px; \n"
"color: white;"));
        sortByIdRadioButton = new QRadioButton(centralwidget);
        sortByIdRadioButton->setObjectName(QString::fromUtf8("sortByIdRadioButton"));
        sortByIdRadioButton->setGeometry(QRect(280, 370, 112, 26));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        sortByIdRadioButton->setPalette(palette3);
        sortByIdRadioButton->setStyleSheet(QString::fromUtf8("color: black;"));
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 20, 351, 41));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush3);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Active, QPalette::PlaceholderText, brush8);
#endif
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        QBrush brush9(QColor(255, 255, 255, 128));
        brush9.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        QBrush brush10(QColor(255, 255, 255, 128));
        brush10.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush10);
#endif
        label_14->setPalette(palette4);
        QFont font6;
        font6.setPointSize(16);
        font6.setBold(true);
        label_14->setFont(font6);
        label_14->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79);color: white;\n"
"border-radius: 15px; "));
        mailButton = new QPushButton(centralwidget);
        mailButton->setObjectName(QString::fromUtf8("mailButton"));
        mailButton->setGeometry(QRect(20, 70, 101, 31));
        mailButton->setFont(font2);
        mailButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        chatBotButton = new QPushButton(centralwidget);
        chatBotButton->setObjectName(QString::fromUtf8("chatBotButton"));
        chatBotButton->setGeometry(QRect(150, 70, 83, 29));
        chatBotButton->setFont(font5);
        chatBotButton->setStyleSheet(QString::fromUtf8("background-color: rgb(13, 33, 79); color: white;"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 942, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        sortByNameRadioButton->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem = fournisseurTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = fournisseurTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = fournisseurTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Date d'achat", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = fournisseurTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = fournisseurTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));

        const bool __sortingEnabled = fournisseurTableWidget->isSortingEnabled();
        fournisseurTableWidget->setSortingEnabled(false);
        fournisseurTableWidget->setSortingEnabled(__sortingEnabled);

        label_8->setText(QString());
        exportPdfButton->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "Chercher", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        updateButton->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        refreshButton->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Telephone", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Date d'achat", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Ajouter Fournisseur :", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        sortButton->setText(QCoreApplication::translate("MainWindow", "Tri par", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Liste des Fournisseurs :", nullptr));
        sortByIdRadioButton->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Gestion des Fournisseurs", nullptr));
        mailButton->setText(QCoreApplication::translate("MainWindow", "Envoyer Mail", nullptr));
        chatBotButton->setText(QCoreApplication::translate("MainWindow", "Chat Bot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
