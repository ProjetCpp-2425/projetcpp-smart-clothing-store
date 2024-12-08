/*#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>  // Include QMainWindow instead of QWidget
#include <QSqlDatabase>
#include <QSqlQueryModel>

namespace Ui {
    class Login; // Forward declaration
}

class Login : public QMainWindow  // Inherit from QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);  // Constructor
    ~Login();  // Destructor

private slots:
    void on_pushButton_login_clicked();  // Slot for login button

private:
    Ui::Login *ui;  // Pointer to UI class
    void writeLog(const QString &message, const QString &category);  // Log function declaration
};

#endif // LOGIN_H*/

#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H

