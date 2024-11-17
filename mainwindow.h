#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fournisseur.h"
#include "./ui_mainwindow.h"

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
    void onAddFournisseurClicked();
    void onUpdateFournisseurClicked();
    void onDeleteFournisseurClicked();
    void onDisplayFournisseursClicked();
    void onExportPdfButtonClicked();
    void onSearchButtonClicked();
    void onSortButtonClicked();
    void onMailButtonClicked();
    void onChatBotButtonClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
