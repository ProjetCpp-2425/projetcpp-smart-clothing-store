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
    explicit ConvertisseurWindow(QWidget *parent = nullptr);
    ~ConvertisseurWindow();

private slots:
    void convertCurrency();

private:
    Ui::ConvertisseurWindow *ui;
};

#endif // CONVERTISSEURWINDOW_H
