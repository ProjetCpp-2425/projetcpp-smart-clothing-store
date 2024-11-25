#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPdfWriter>
#include "commande.h"
#include <QMainWindow>
#include <QPrinter>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_15_clicked();
    void on_lineEdit_recherche_cursorPositionChanged();
    void on_pdf_clicked();
    void on_statistique_clicked();
    void on_ajouterArticle_clicked();

    void on_viderPanier_clicked();

    void on_supprimerArticleButton_clicked();

    void on_calculerPrixTotal_clicked();

    void on_afficherPanier_clicked();

void on_comboBox_3_activated(int index);

private:
    Ui::MainWindow *ui;
    commande Etmp;
    commande a;
    bool verifierCINExist(int cin);
    commande commandeInstance;
};

#endif // MAINWINDOW_H
