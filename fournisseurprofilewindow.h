#ifndef FOURNISSEURPROFILEWINDOW_H
#define FOURNISSEURPROFILEWINDOW_H

#include <QWidget>
#include <QLabel>

class FournisseurProfileWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FournisseurProfileWindow(QWidget *parent = nullptr);
    void setFournisseurDetails(const QString& name, const QString& telephone, const QString& email, const QString& achatDate);

private:
    QLabel* nameLabel;
    QLabel* telephoneLabel;
    QLabel* emailLabel;
    QLabel* achatDateLabel;
};

#endif // FOURNISSEURPROFILEWINDOW_H
