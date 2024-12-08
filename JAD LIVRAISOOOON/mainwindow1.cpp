#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include "Livraison.h"
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
#include <QSslSocket>
#include <QTimer>
MainWindow1::MainWindow1(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    ui->tableView_r->setModel(l.afficher());



    int ret=A.connect_arduino(); // lancer la connexion Ã  arduino
         switch(ret){
         case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
             break;
         case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
            break;
         case(-1):qDebug() << "arduino is not available";
         }
          //QObject::connect(  a.getserial(),SIGNAL(readyRead()),this,SLOT(handleReadyRead())); // permet de lancer
          //le slot update_label suite Ã  la reception du signal readyRead (reception des donnÃ©es)


          // connect(a.getserial(), &QSerialPort::readyRead, this, &logininterface::handleReadyRead);
         QTimer *repeatingTimer = new QTimer(this);

         // Set the timer to trigger every 30 seconds (30000 milliseconds)
         repeatingTimer->setInterval(200);

         // Connect the timer's timeout() signal to the lambda function
         connect(repeatingTimer, &QTimer::timeout, this, [=]() {
             data = A.read_from_arduino();
             data=data.trimmed();
                 if (!data.isEmpty()) { // Check if RFID card ID is not empty
                     qDebug() << "RFID Card ID:" << data;
                     ui->rfid->setText(data);

                     QSqlQuery query;
                        query.prepare("SELECT COUNT(*) FROM Livraison WHERE IDCARD = :idcard");
                        query.bindValue(":idcard", ui->rfid->text());


                        if (query.exec()) {
                            qDebug()<< query.lastQuery();
                            if (query.next() && query.value(0).toInt() > 0) { // If the card ID exists
                                ui->exist->setText("Exists");
                                 A.write_to_arduino("0");
                                ui->exist->setStyleSheet("color: green;"); // Change label color to green
                            } else { // If the card ID does not exist
                                ui->exist->setText("No, it doesn't exist");
                                ui->exist->setStyleSheet("color: red;"); // Change label color to red
                                 A.write_to_arduino("1");
                            }
                        }
                        }});

         // Start the timer
         repeatingTimer->start();




   }
MainWindow1::~MainWindow1()
{
    delete ui;
}

void MainWindow1::on_ajout_clicked()
{
    int id=ui->lineEdit_id_2->text().toInt();
    QString im = ui->lineEdit_imm->text();
    QString carb=ui->lineEdit_carb_2->text();
    QString carteG=ui->lineEdit_carteG->text();
    int poids=ui->lineEdit_poids->text().toInt();
    int assurance=ui->lineEdit_assurance->text().toInt();
    QString card=ui->rfid->text();


    Livraison l(id,im,carb,carteG,poids,assurance);
    bool test=l.ajouter(card);
    if (test){
        ui->tableView_r->setModel(l.afficher());
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
        int id =ui->lineEdit_id_2->text().toInt();
        bool test=l.supprimer(id);
        if (test){
            ui->tableView_r->setModel(l.afficher());
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

    int id=ui->lineEdit_id_2->text().toInt();
    QString im = ui->lineEdit_imm->text();
    QString carb=ui->lineEdit_carb_2->text();
    QString carteG=ui->lineEdit_carteG->text();
    int poids=ui->lineEdit_poids->text().toInt();
    int assurance=ui->lineEdit_assurance->text().toInt();


    Livraison l(id,im,carb,carteG,poids,assurance);

    bool test=l.modifier(id);
    if (test){


        ui->tableView_r->setModel(l.afficher());
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
 Livraison l;
        int id = ui->lineEdit_recherche->text().toInt();


        QSqlQueryModel *result = l.rechercher(id);

        ui->tableView_r->setModel(result);
}

void MainWindow1::on_tri_clicked()
{

        Livraison l;

        QSqlQueryModel *result = l.tri();

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
    cursor.insertText("Liste des vehicule\n\n");

    // Crée un tableau avec des colonnes pour chaque champ de la table
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignLeft);
    QTextTable *table = cursor.insertTable(1, 7, tableFormat);
    QTextCursor cellCursor;

    // Remplir les en-têtes de colonne
    cellCursor = table->cellAt(0, 0).firstCursorPosition();
    cellCursor.insertText("id de vehicule");

    cellCursor = table->cellAt(0, 1).firstCursorPosition();
    cellCursor.insertText("immatriculation de vehicule");

    cellCursor = table->cellAt(0, 2).firstCursorPosition();
    cellCursor.insertText("carburant de vehicule");

    cellCursor = table->cellAt(0, 3).firstCursorPosition();
    cellCursor.insertText("catre grise de vehicule");

    cellCursor = table->cellAt(0, 4).firstCursorPosition();
    cellCursor.insertText("poids de vehicule ");

    cellCursor = table->cellAt(0, 5).firstCursorPosition();
    cellCursor.insertText("numero d'assurance de vehicule");



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

    QMessageBox::information(this, "Succès", "Liste des vehicule exportée sous forme de PDF.");
}




void MainWindow1::on_historique_clicked()
{
Livraison l;
        QString fileName = QFileDialog::getSaveFileName(this, "Exporter l'historique en texte", "", "Fichiers texte (*.txt)");
        if (!fileName.isEmpty()) {
            l.exporterHistoriqueTexte(fileName);
            QMessageBox::information(this, "Succès", "Historique exporté sous forme de fichier texte.");
        }
}
/*
void MainWindow1::on_statistiques_clicked()
{
    Commande commande;
    QString statistiques = commande.statistiquesParStatut();

       ui->label_stat->setText(statistiques);
}*/
/*
void MainWindow::on_statistiques_clicked()
{
    QGraphicsScene& scene = c.statistiquesParStatut();
        ui->graphicsView_sta->setScene(&scene);
}
*/


void MainWindow1::on_sendmail_clicked()
{
    QString serveur = "smtp.gmail.com";
                  int port = 587; // Port pour SMTP avec STARTTLS

                  // Informations de l'expéditeur et du destinataire
                  QString expediteur = "jadchida5@gmail.com";
                  QString destinataire = ui->dest->text();

                  QString subject = "Cher notre client";

                  // Détails du message
                   QString corps = ui->contenu->toPlainText();

                  // Connexion au serveur SMTP
                  QSslSocket socket;
                  socket.connectToHost(serveur, port);
                  if (!socket.waitForConnected()) {
                      qDebug() << "Échec de connexion au serveur SMTP:" << socket.errorString();
                      return;
                  }

                  // Attente de la réponse du serveur
                  if (!socket.waitForReadyRead()) {
                      qDebug() << "Délai d'attente de réponse du serveur SMTP:" << socket.errorString();
                      return;
                  }
                  qDebug() << socket.readAll(); // Afficher la réponse initiale du serveur

                  // Envoi de la commande EHLO
                  socket.write("EHLO localhost\r\n");
                  if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                      qDebug() << "Délai d'attente de réponse du serveur SMTP (EHLO):" << socket.errorString();
                      return;
                  }
                  qDebug() << socket.readAll(); // Afficher la réponse après EHLO

                  // Envoi de la commande STARTTLS
                  socket.write("STARTTLS\r\n");
                  if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                      qDebug() << "Délai d'attente de réponse du serveur SMTP (STARTTLS):" << socket.errorString();
                      return;
                  }
                  qDebug() << socket.readAll(); // Afficher la réponse après STARTTLS

                  // Démarrer le chiffrement
                  socket.startClientEncryption();
                  if (!socket.waitForEncrypted()) {
                      qDebug() << "Échec du chiffrement:" << socket.errorString();
                      return;
                  }

                  // Envoi de la commande AUTH LOGIN
                  socket.write("AUTH LOGIN\r\n");
                  if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                      qDebug() << "Délai d'attente de réponse du serveur SMTP (AUTH LOGIN):" << socket.errorString();
                      return;
                  }
                  qDebug() << socket.readAll(); // Afficher la réponse après AUTH LOGIN

                  // Envoi du nom d'utilisateur encodé en Base64
                  socket.write(QByteArray().append(expediteur.toUtf8()).toBase64() + "\r\n");
                  if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                      qDebug() << "Délai d'attente de réponse du serveur SMTP (Nom d'utilisateur):" << socket.errorString();
                      return;
                  }
                  qDebug() << socket.readAll(); // Afficher la réponse après l'envoi du nom d'utilisateur

                  // Envoi du mot de passe encodé en Base64
                  socket.write(QByteArray().append("hhvo hoen atnv tezd").toBase64() + "\r\n");
                  if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                      qDebug() << "Échec de l'authentification SMTP (Mot de passe):" << socket.errorString();
                      return;
                  }
                  qDebug() << socket.readAll(); // Afficher la réponse après l'envoi du mot de passe

                  // Envoi de la commande MAIL FROM
                  socket.write("MAIL FROM:<" + expediteur.toUtf8() + ">\r\n");
                  if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                      qDebug() << "Délai d'attente de réponse du serveur SMTP (MAIL FROM):" << socket.errorString();
                      return;
                  }
                  qDebug() << socket.readAll(); // Afficher la réponse après MAIL FROM

                  // Envoi de la commande RCPT TO
                  socket.write("RCPT TO:<" + destinataire.toUtf8() + ">\r\n");
                  if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                      qDebug() << "Délai d'attente de réponse du serveur SMTP (RCPT TO):" << socket.errorString();
                      return;
                  }
                  qDebug() << socket.readAll(); // Afficher la réponse après RCPT TO

                  // Envoi de la commande DATA
                  socket.write("DATA\r\n");
                  if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                      qDebug() << "Délai d'attente de réponse du serveur SMTP (DATA):" << socket.errorString();
                      return;
                  }
                  qDebug() << socket.readAll(); // Afficher la réponse après DATA

                  // Envoi des en-têtes et du corps du message
                  socket.write("From: " + expediteur.toUtf8() + "\r\n");
                  socket.write("To: " + destinataire.toUtf8() + "\r\n");
                  socket.write("Subject: " + subject.toUtf8() + "\r\n");
                  socket.write("\r\n");
                  socket.write(corps.toUtf8() + "\r\n");
                  socket.write(".\r\n");
                  if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
                      qDebug() << "Échec d'envoi des données du mail:" << socket.errorString();
                      return;
                  }
                  qDebug() << socket.readAll(); // Afficher la réponse après l'envoi des données du mail

                  // Envoi de la commande QUIT
                  socket.write("QUIT\r\n");
                  if (!socket.waitForBytesWritten()) {
                      qDebug() << "Échec d'envoi de la commande QUIT:" << socket.errorString();
                      return;
                  }

                  // Fermeture de la connexion
                  socket.close();
                  QMessageBox::information(this, "Succès", "L'email a été envoyé avec succès à " + destinataire);

}

