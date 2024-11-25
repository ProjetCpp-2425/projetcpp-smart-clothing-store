#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "produit.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_suppreime_produit_clicked();
    void loadProduitData();
    void on_ajouter_produit_clicked();
    void on_Modifier_produit_clicked();
    /*
    void on_rechercher_produit_clicked();
*/
    void on_recherhce_produit_clicked();

    void on_trier_produit_clicked();


    void on_expoter_produit_clicked();


    void on_statistique_produit_clicked();



    void on_historique_produit_clicked();
    void addToHistory(const QString &action,int IDP) ;
     void writeHistoryToFile(const QString &fileName);
     void   afficherHistorique();
private:
    Ui::MainWindow *ui;
    Produit Etmp;

    Produit P;
    QList<QString> historyList; // Liste pour stocker l'historique
      QString historiqueFileName = "histo.txt";
};

#endif // MAINWINDOW_H
