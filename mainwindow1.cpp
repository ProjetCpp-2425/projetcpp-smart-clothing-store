#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include "client.h"
#include<QMessageBox>
#include<QDebug>
#include<QString>
#include<QTextTable>
#include<QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QVBoxLayout>

MainWindow1::MainWindow1(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    ui->tableView_r->setModel(c.afficher());
    int ret=A.connect_arduino(); // lancer la connexion à arduino
                switch(ret){
                case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                    break;
                case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                   break;
                case(-1):qDebug() << "arduino is not available";
                }
                 QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(connect_commande())); // permet de lancer
                 //le slot update_label suite à la reception du signal readyRead (reception des données)
}

MainWindow1::~MainWindow1()
{
    delete ui;
}

void MainWindow1::on_ajout_clicked()
{

    int id=ui->lineEdit_N->text().toInt();
    QString nom_p = ui->lineEdit_date->text();
    int numero=ui->lineEdit_total->text().toInt();
    QString mail=ui->lineEdit_statut->text();
    QString date_ = ui->lineEdit_total_2->text();
    QString genre = ui->lineEdit_total_3->text();

    Client C(id,nom_p,numero,mail,date_,genre);
    bool test=C.ajouter();
    if (test){
        ui->tableView_r->setModel(c.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                QObject::tr("ajouter effectue \n"
                            "click cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("ajout non effectue.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
}


void MainWindow1::on_pushButton_supp_clicked()
{
        int id =ui->lineEdit_N->text().toInt();
        bool test=c.supprimer(id);
        if (test){
            ui->tableView_r->setModel(c.afficher());
            QMessageBox::information(nullptr,QObject::tr("ok"),
                    QObject::tr("suppression  effectue \n"
                                "click cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                  QObject::tr("suppression non effectue.\n"
                                              "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow1::on_modif_clicked()
{

    qDebug();
    int id=ui->lineEdit_N->text().toInt();
    QString nom_p = ui->lineEdit_date->text();
    int numero=ui->lineEdit_total->text().toInt();
    QString mail=ui->lineEdit_statut->text();
    QString date_ = ui->lineEdit_total_2->text();
    QString genre = ui->lineEdit_total_3->text();


    Client c(id,nom_p,numero,mail,date_,genre);

    bool test=c.modifier(id);
    if (test){


        ui->tableView_r->setModel(c.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("modifier avec success.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr(" modifier non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow1::on_recherche_pushButton_clicked()
{
    Client client;
        int id = ui->lineEdit_recherche->text().toInt();


        QSqlQueryModel *result = client.rechercher(id);

        ui->tableView_r->setModel(result);
}

void MainWindow1::on_tri_clicked()
{

        Client client;

        QSqlQueryModel *result = client.tri();

        ui->tableView_r->setModel(result);
}
void MainWindow1::on_pdf_clicked()
{  QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty()) {
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QTextCursor cursor(&doc);

    // En-tête du document
    QTextCharFormat headerFormat;
    headerFormat.setFontPointSize(14);
    headerFormat.setFontWeight(QFont::Bold);
    cursor.setCharFormat(headerFormat);
    cursor.insertText("Liste des clients\n\n");

    // Crée un tableau avec des colonnes pour chaque champ de la table
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignLeft);
    QTextTable *table = cursor.insertTable(1, 7, tableFormat);
    QTextCursor cellCursor;

    // Remplir les en-têtes de colonne
    cellCursor = table->cellAt(0, 0).firstCursorPosition();
    cellCursor.insertText("Id");

    cellCursor = table->cellAt(0, 1).firstCursorPosition();
    cellCursor.insertText("Nom et Prénom");

    cellCursor = table->cellAt(0, 2).firstCursorPosition();
    cellCursor.insertText("Adresse Email");

    cellCursor = table->cellAt(0, 3).firstCursorPosition();
    cellCursor.insertText("Numéro");

    cellCursor = table->cellAt(0, 4).firstCursorPosition();
    cellCursor.insertText("Date de naissance");

    cellCursor = table->cellAt(0, 5).firstCursorPosition();
    cellCursor.insertText("Genre");


    // Obtain the client data from your table model
    QSqlQueryModel *model = static_cast<QSqlQueryModel*>(ui->tableView_r->model());

    // Fill the table data
    for (int row = 0; row < model->rowCount(); ++row) {
        table->appendRows(1);

        for (int col = 0; col < 7; ++col) {
            cellCursor = table->cellAt(row + 1, col).firstCursorPosition();
            cellCursor.insertText(model->data(model->index(row, col)).toString());
        }
    }

    doc.print(&printer);

    QMessageBox::information(this, "Succès", "Liste des clients exportée sous forme de PDF.");
}


void MainWindow1::on_envoyer_clicked()
{
    Client c;
    QString userMessage = ui->lineEdit_chatbot->text();
    std::string botResponse = c.chatbotFunction(userMessage);
       ui->label_chatbot_response->setText(QString::fromStdString(botResponse));
}

void MainWindow1::on_historique_clicked()
{
    Client client;
        QString fileName = QFileDialog::getSaveFileName(this, "Exporter l'historique en texte", "", "Fichiers texte (*.txt)");
        if (!fileName.isEmpty()) {
            client.exporterHistoriqueTexte(fileName);
            QMessageBox::information(this, "Succès", "Historique exporté sous forme de fichier texte.");
        }
}
/*
void MainWindow1::on_statistiques_clicked()
{
    Client client;
    QString statistiques = client.statistiquesParGenre();

       ui->label_stat->setText(statistiques);
}

void MainWindow::on_statistiques_clicked()
{
    QGraphicsScene& scene = c.statistiquesParGenre();
        ui->graphicsView_sta->setScene(&scene);
}
*/
void MainWindow1::connect_Client()
{
    Client c;

    if (c.ClientExists()==true) {
        QByteArray data1;
        data1.append("1");
        A.write_to_arduino(data1);

        qDebug() << "Client avec statut 'annuler' trouvée";
    } else {
    qDebug() << "non trouvée";
    }
}
