#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddFournisseurClicked();
    void onUpdateFournisseurClicked();
    void onDeleteFournisseurClicked();
    void onDisplayFournisseursClicked();
    void onExportPdfButtonClicked();
    void onSearchFournisseurClicked();
    void onSortButtonClicked();
    void onMailButtonClicked();
    void onChatBotButtonClicked();
    void onProfileButtonClicked();
    void onConvertButtonClicked();
    void updateStats();
    void browseLogo();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
