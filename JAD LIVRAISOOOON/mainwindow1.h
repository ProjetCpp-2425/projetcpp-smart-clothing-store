#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Livraison.h"
#include "arduino.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QtCharts/QChartView>
#include "ui_mainwindow1.h"
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow1; }
QT_END_NAMESPACE

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();
private slots:
    void on_ajout_clicked();


    void on_pushButton_supp_clicked();

    void on_modif_clicked();

    void on_recherche_pushButton_clicked();

    void on_pdf_clicked();


    void on_historique_clicked();

    //void on_statistiques_clicked();

    void on_tri_clicked();




    void on_sendmail_clicked();

private:
    Ui::MainWindow1 *ui;
   Livraison l;
       Arduino A;
     QByteArray data;

};
#endif // MAINWINDOW_H
