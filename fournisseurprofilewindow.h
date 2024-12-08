#ifndef FOURNISSEURPROFILEWINDOW_H
#define FOURNISSEURPROFILEWINDOW_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class FournisseurProfileWindow;
}


class FournisseurProfileWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FournisseurProfileWindow(QWidget *parent = nullptr);
    ~FournisseurProfileWindow();
    void setFournisseurDetails(const QString& name, const QString& telephone, const QString& email, const QString& achatDate, const QString& logoPath);

private:
    QLabel* nameLabel;
    QLabel* telephoneLabel;
    QLabel* emailLabel;
    QLabel* achatDateLabel;
    QLabel* logoLabel;  // New label to display the logo image

private:
    Ui::FournisseurProfileWindow *ui;
};

#endif // FOURNISSEURPROFILEWINDOW_H
