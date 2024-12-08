#ifndef CONVERTISSEURWINDOW_H
#define CONVERTISSEURWINDOW_H

#include <QWidget>

namespace Ui {
class ConvertisseurWindow;
}

class ConvertisseurWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConvertisseurWindow(double prixAchat, QWidget *parent = nullptr);
    ~ConvertisseurWindow();

private slots:
    void convertCurrency();

private:
    Ui::ConvertisseurWindow *ui;
    double prixAchat;
};

#endif // CONVERTISSEURWINDOW_H
