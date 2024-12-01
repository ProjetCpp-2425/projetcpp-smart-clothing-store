#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery> // For executing queries
#include <QSqlQueryModel> // For the query model
#include <QSqlError> // For error handling
#include <QDebug> // For debugging output


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
    void onAjouterClicked(); // Slot for the "Ajouter" button
    void on_modifierbut_clicked(); // Slot for the "Modifier" button
    void on_supprimerClicked(); // Slot for the "Supprimer" button
    void afficherEmployes(); // Slot for displaying employees
    void on_searchButton_clicked(); // Slot for the search button
    void on_triButton_clicked(); // Slot for the "Tri" button
    void on_sortComboBox_currentIndexChanged(int index); // Slot for handling sorting by column
    void exportToPDF();
    void generateGenderStatistics();


private:
    Ui::MainWindow *ui; // New HTML export function

};

#endif // MAINWINDOW_H
